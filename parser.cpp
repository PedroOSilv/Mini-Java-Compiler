#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
	cout << scanner->returnName(lToken->name) + " ";
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

void
Parser::run()
{
	advance();	

	program();
	
	cout << "Compilação encerrada com sucesso!\n";
}

void
Parser::program()
{
	//TODO
    mainClass();
	while(lToken->name == CLASS) {
		classdeclaration();
	}
	match(END_OF_FILE);
}

void
Parser::mainClass()
{	
	match(CLASS);
	match(ID);
	match(OCB);
	match(PUBLIC);
	match(STATIC);
	match(VOID);
	match(MAIN);
	match(OPAR);
	match(STRING);
	match(OSB);
	match(CSB);
	match(ID);
	match(CPAR);
	match(OCB);
	statement();
	match(CCB);
	match(CCB);
}

void
Parser::classdeclaration()
{
    match(CLASS);
	match(ID);
	if(lToken->name == EXTENDS) {
		match(EXTENDS);
		match(ID);
	}
	match(OCB);
	while(lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID) {
		vardeclaration();
	}
	while(lToken->name == PUBLIC) {
		methoddeclaration();
	}
	match(CCB);
}

void
Parser::vardeclaration()
{
	type();
	match(ID);
}

void
Parser::methoddeclaration()
{
	match(PUBLIC);
	type();
	match(ID);
	match(OPAR);
	if(lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID){
		type();
		match(ID);
		while(lToken->name == CM) {
			type();
			match(ID);
		}
	}
	match(CPAR);
	match(OCB);
	while(lToken->name == INT || lToken->name == BOOLEAN || lToken->name == ID){
		vardeclaration();
	}
	while(lToken->name == OCB || lToken->name == IF || lToken->name == WHILE || lToken->name == SYSOUTPRINT || lToken->name == ID){
		statement();
	}
	match(RETURN);
	expression();
	match(SC);
	match(CCB);
}

void
Parser::type()
{
	if(lToken->name == INT) {
		match(INT);
		if(lToken->name == OSB){
			match(OSB);
			match(CSB);
		}
	}
	else if(lToken->name == BOOLEAN) {
		match(BOOLEAN);
	}
	else { // ID
		match(ID);
	}
}

void
Parser::statement()
{
	if(lToken->name == OCB){
		match(OCB);
		while(lToken->name == OCB || lToken->name == IF || lToken->name == WHILE || lToken->name == SYSOUTPRINT || lToken->name == ID)
		{
			statement();
		}
		match(CCB);
	}
	else if(lToken->name == IF){
		match(IF);
		match(OPAR);
		expression();
		match(CPAR);
		statement();
	}
	else if(lToken->name == SYSOUTPRINT){
		match(SYSOUTPRINT);
		match(OPAR);
		expression();
		match(CPAR);
		match(SC);
	}
	else { // ID
		match(ID);
		if(lToken->name == ATTR) {
			match(ATTR);
			expression();
			match(SC);
		}
		else { // ID [
			match(OSB);
			expression();
			match(CSB);
			match(ATTR);
			expression();
			match(SC);
		}
	}
}

void
Parser::expression()
{
	
}

void
Parser::op()
{
	if(lToken->name == AND){
		match(AND);
	}
	else if(lToken->name == LT){
		match(LT);
	}
	else if(lToken->name == GT){
		match(GT);
	}
	else if(lToken->name == EQ){
		match(EQ);
	}
	else if(lToken->name == NE){
		match(NE);
	}
	else if(lToken->name == PLUS){
		match(PLUS);
	}
	else if(lToken->name == MINUS){
		match(MINUS);
	}
	else if(lToken->name == MULTI){
		match(MULTI);
	}
	else { // DIV
		match(DIV);
	}
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
