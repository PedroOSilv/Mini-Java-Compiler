#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
	// cout << scanner->returnName(lToken->name) + " ";
}

void
Parser::match(int t, string expected)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro, token esperado " + expected);
}

void
Parser::run()
{
	advance();	

	program();
	
	cout << "Compilacao encerrada com sucesso!\n";
}

void
Parser::program()
{
	//TODO
    mainClass();
	while(lToken->name == CLASS) {
		classdeclaration();
	}
	match(END_OF_FILE, "END_OF_FILE");
}

void
Parser::mainClass()
{	
	match(CLASS, "CLASS");
	match(ID, "ID");
	match(OCB, "{");
	match(PUBLIC, "PUBLIC");
	match(STATIC, "STATIC");
	match(VOID, "VOID");
	match(MAIN, "MAIN");
	match(OPAR, "(");
	match(STRING, "STRING");
	match(OSB, "[");
	match(CSB, "]");
	match(ID, "ID");
	match(CPAR, ")");
	match(OCB, "{");
	statement();
	match(CCB, "}");
	match(CCB, "}");
}

void
Parser::classdeclaration()
{
    match(CLASS, "CLASS");
	match(ID, "ID");
	if(lToken->name == EXTENDS) {
		match(EXTENDS, "EXTENDS");
		match(ID, "ID");
	}
	match(OCB, "{");
	while(lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID) {
		vardeclaration();
	}
	while(lToken->name == PUBLIC) {
		methoddeclaration();
	}
	match(CCB, "}");
}

void
Parser::vardeclaration()
{
	type();
	match(ID, "ID");
	match(SC, "SC");
}

void
Parser::vardeclarionline()
{
	match(ID, "ID");
	match(SC, "SC");
}

void
Parser::methoddeclaration()
{
	match(PUBLIC, "PUBLIC");
	type();
	match(ID, "ID");
	match(OPAR, "(");
	if(lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID){
		type();
		match(ID, "ID");
		while(lToken->attribute == CM) {
			match(CM, ",");
			type();
			match(ID, "ID");
		}
	}
	match(CPAR, ")");
	match(OCB, "{");
	while(lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID){
		if(lToken->name == ID){
			match(ID, "ID");
			if(lToken->name == ID) {
				vardeclarionline();
			}
			else {
				statementline();
				break;
			}
		}
		else {
			vardeclaration();
		}
	}
	while(lToken->attribute == OCB || lToken->name == IF || lToken->name == WHILE || lToken->name == SYSOUTPRINT || lToken->name == ID){
		statement();
	}
	match(RETURN, "RETURN");
	expression();
	match(SC, ";");
	match(CCB, "}");
}

void
Parser::type()
{
	if(lToken->name == INT) {
		match(INT, "INT");
		if(lToken->attribute == OSB){
			match(OSB, "[");
			match(CSB, "]");
		}
	}
	else if(lToken->name == BOOLEAN) {
		match(BOOLEAN, "BOOLEAN");
	}
	else { // ID
		match(ID, "ID");
	}
}

void
Parser::statement()
{
	if(lToken->attribute == OCB){
		match(OCB, "{");
		while(lToken->attribute == OCB || lToken->name == IF || lToken->name == WHILE || lToken->name == SYSOUTPRINT || lToken->name == ID)
		{
			statement();
		}
		match(CCB, "}");
	}
	else if(lToken->name == IF){
		match(IF, "IF");
		match(OPAR, "()");
		expression();
		match(CPAR, ")");
		statement();
		match(ELSE, "ELSE");
		statement();
	}
	else if(lToken->name == WHILE){
		match(WHILE, "WHILE");
		match(OPAR, "(");
		expression();
		match(CPAR, ")");
		statement();
	}
	else if(lToken->name == SYSOUTPRINT){
		match(SYSOUTPRINT, "SYSOUTPRINT");
		match(OPAR, "(");
		expression();
		match(CPAR, ")");
		match(SC, ";");
	}
	else { // ID
		match(ID, "ID");
		if(lToken->name == ATTR) {
			match(ATTR, "=");
			expression();
			match(SC, ";");
		}
		else { // ID [
			match(OSB, "{");
			expression();
			match(CSB, "}");
			match(ATTR, "=");
			expression();
			match(SC, ";");
		}
	}
}

void
Parser::statementline()
{
	if(lToken->name == ATTR) {
			match(ATTR, "=");
			expression();
			match(SC, ";");
		}
		else { // ID [
			match(OSB, "{");
			expression();
			match(CSB, "}");
			match(ATTR, "=");
			expression();
			match(SC, ";");
		}
}
// Antes com recursão a esquerda:

// Expression → Expression Op Expression
// | Expression [ Expression ]
// | Expression . length
// | Expression . ID ( ( Expression (, Expression )∗)? )
// | INTEGER_LITERAL
// | true
// | false
// | ID
// | this
// | new int [ Expression ]
// | new ID ( )
// | ! Expression
// | ( Expression )

// Depois sem recursão a esquerda:

// Expression → INTEGER_LITERAL ExpressionLine
// | true ExpressionLine
// | false ExpressionLine
// | ID ExpressionLine
// | this ExpressionLine
// | new int [ Expression ] ExpressionLine
// | new ID ( ) ExpressionLine
// | ! Expression ExpressionLine
// | ( Expression ) ExpressionLine

//  ExpressionLine → Op Expression ExpressionLine 
// | [ Expression ] ExpressionLine
// | . length ExpressionLine
// | . ID ( ( Expression (, Expression )∗)? ) ExpressionLine
// | PalavraVazia


void
Parser::expression()
{
	if(lToken->name == INTEGER_LITERAL){
		match(INTEGER_LITERAL, "INTEGER_LITERAL");
		expressionline();
	}
	else if(lToken->name == TRUE){
		match(TRUE, "TRUE");
		expressionline();
	}
	else if(lToken->name == FALSE){
		match(FALSE, "FALSE");
		expressionline();
	}
	else if(lToken->name == ID){
		match(ID, "ID");
		expressionline();
	}
	else if(lToken->name == THIS){
		match(THIS, "THIS");
		expressionline();
	}
	else if(lToken->name == NEW){
		match(NEW, "NEW");
		if(lToken->name == INT){
			match(INT, "INT");
			match(OSB, "{");
			expression();
			match(CSB, "}");
			expressionline();
		}
		else{
			match(ID, "ID");
			match(OPAR, "(");
			match(CPAR, ")");
			expressionline();
		}
	}
	else if(lToken->name == NOT){
		match(NOT, "!");
		expression();
		expressionline();
	}
	else {
		match(OPAR, "(");
		expression();
		match(CPAR, ")");
		expressionline();
	}
}

void
Parser::expressionline()
{
	if(lToken->name == AND || lToken->name == GT || lToken->name == LT || lToken->name == EQ ||
	lToken->name == NE || lToken->name == PLUS || lToken->name == MINUS || lToken->name == MULTI || lToken->name == DIV){
		op();
		expression();
		expressionline();
	}
	else if(lToken->attribute == OSB){
		match(OSB, "[");
		expression();
		match(CSB, "]");
		expressionline();
	}
	else if(lToken->attribute == PN){
		match(PN, ".");
		if(lToken->name == LENGTH){
			match(LENGTH, "LENGTH");
		}
		else {
			match(ID, "ID");
			match(OPAR, "(");
			if(lToken->name == INTEGER_LITERAL || lToken->name == TRUE || lToken->name == FALSE || lToken->name == ID ||
			lToken->name == THIS || lToken->name == NEW || lToken->name == NOT || lToken->attribute == OPAR){
				expression();
				while(lToken->attribute == CM){
					match(CM, ",");
					expression();
				}
			}
			match(CPAR, ")");
		}
		expressionline();
	}
	// Palara vazia implementada por meio do uso de 'else if' no final ao invés de 'else'
}

void
Parser::op()
{
	if(lToken->name == AND){
		match(AND, "AND");
	}
	else if(lToken->name == LT){
		match(LT, "<");
	}
	else if(lToken->name == GT){
		match(GT, ">");
	}
	else if(lToken->name == EQ){
		match(EQ, "==");
	}
	else if(lToken->name == NE){
		match(NE, "!=");
	}
	else if(lToken->name == PLUS){
		match(PLUS, "+");
	}
	else if(lToken->name == MINUS){
		match(MINUS, "-");
	}
	else if(lToken->name == MULTI){
		match(MULTI, "*");
	}
	else { // DIV
		match(DIV, "/");
	}
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
