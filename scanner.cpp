#include "scanner.h"    

//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input)
{
    
    this->input = input;
    //impressao
    cout << "Entrada: " << input << endl << "Tamanho: " << input.length() << endl;

    pos = 0;
    line = 1;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {   
        this->input = "";
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
            //cout<< line + '\n';
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

    //A próxima linha deve ser comentada posteriormente.
    //Ela é utilizada apenas para verificar se o 
    //preenchimento de input foi feito corretamente.
    //cout << this->input;

}

int
Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    
    Token* tok;
    int state;

    state = 0;

    while (true)
    {
        int inicialPos;
        switch (state)
        {
            /*
                Observação:
                Nós dividimos os tipos de estados de acordo com seu número.

                Identificadores - state começa com o número 1
                Números Inteiros - state começa com o número 2
                Operadoes - state começa com o número 3
                Separadores - state começa com o número 4
                Palavras Reservadas - state começa com o número 5
                Comentários - state começa com o número 6
            */
            case 0:
                inicialPos = pos;
                //se for fim de arquivo
                if (input[pos] == '\0'){
                    tok = new Token(END_OF_FILE);
                    return tok;

                //se for id
                }else if(isalpha(input[pos]))
                    state = 1;

                //se for digito
                else if(isdigit(input[pos]))
                    state = 20;

                // se for operadores
                else if(input[pos] == '&')
                    state = 31;

                else if(input[pos] == '>')
                    state = 33;

                else if(input[pos] == '<')
                    state = 34;

                else if(input[pos] == '+')
                    state = 35;

                else if(input[pos] == '-')
                    state = 36;

                else if(input[pos] == '*')
                    state = 37;

                else if(input[pos] == '=')
                    state = 38;

                else if(input[pos] == '!')
                    state = 301;

                //se for um separador
                else if (input[pos]=='(')
                    state = 40;
                
                else if (input[pos]==')')
                    state = 41;
                
                else if (input[pos]=='[')
                    state = 42;

                else if (input[pos]==']')
                    state = 43;

                else if (input[pos]=='{')
                    state = 44;

                else if (input[pos]=='}')
                    state = 45;

                else if (input[pos]==';')
                    state = 46;
                
                else if (input[pos]=='.')
                    state = 47;
                
                else if (input[pos]==',')
                    state = 48;

                //se for comentario ou o operador '/'
                else if(input[pos]=='/')
                    state = 60;
                
                else if(input[pos] == '\n')
                    line += 1;
                
                else if(input[pos] == '\t' ||
                        input[pos] == '\r' ||
                        input[pos] == '\f' ||
                        input[pos] == ' ')
                        ;
                else
                {
                    string str = "";
                    str += input[pos];
                    lexicalError(str, line);
                }

                pos++;
                break;

            case 1:
                //se for um id:
                if(!isalnum(input[pos]) && input[pos] != '_')
                    state = 11;
                pos++;
                break;

            case 11:
                {
                //retorna um id
                string str = "";
                pos--;
                for (int i = inicialPos; i < pos; i++){
                    str += input[i];
                }
                if(str == "System" && (input.length() - pos + 1) >= 12) // System.out.println
                {
                    // nesse if é verificado se o System aparece no começo e se existe espaço restante na string input para comportar o ".out.println", que no caso ocuparia 12 posições
                    for(int i = 0; i < 12; i++) {
                        str += input[pos + i];
                    }
                    if(str == "System.out.println")
                    {
                        tok = new Token(SYSOUTPRINT);
                        pos += 12;
                    }
                        
                    else
                        tok = new Token(ID);
                }

                else if(str == "boolean")
                    tok = new Token(BOOLEAN);
                
                else if(str == "class")
                    tok = new Token(CLASS);
                
                else if(str == "else")
                    tok = new Token(ELSE);
                
                else if(str == "extends")
                    tok = new Token(EXTENDS);
                
                else if(str == "false")
                    tok = new Token(FALSE);
                
                else if(str == "if")
                    tok = new Token(IF);
                
                else if(str == "int")
                    tok = new Token(INT);
                
                else if(str == "length")
                    tok = new Token(LENGTH);
                
                else if(str == "main")
                    tok = new Token(MAIN);
                
                else if(str == "new")
                    tok = new Token(NEW);
                
                else if(str == "public")
                    tok = new Token(PUBLIC);
                
                else if(str == "return")
                    tok = new Token(RETURN);
                
                else if(str == "static")
                    tok = new Token(STATIC);
                
                else if(str == "String")
                    tok = new Token(STRING);
                
                else if(str == "this")
                    tok = new Token(THIS);

                else if(str == "true")
                    tok = new Token(TRUE);

                else if(str == "void")
                    tok = new Token(VOID);

                else if(str == "while")
                    tok = new Token(WHILE);

                else
                    tok = new Token(ID);
                
                return tok;
                }
            case 20:
                //se  for digito
                if(!isdigit(input[pos]))
                    state = 21;
                pos++;
                break;

            case 21:
                //retorna digito
                tok = new Token(NUMBER);
                pos--;
                return tok;

            case 30:
                // retorna operador '/'
                tok = new Token(DIV);
                pos--;
                return tok;

            case 31:
                // analisa se é o operador &
                if(input[pos] == '&')
                    state = 32;
                else
                {
                    string str = "";
                    str += input[pos - 1];
                    str += input[pos];
                    lexicalError(str, line);
                }
                pos++;
                break;
            
            case 32:
                // retorna token &&(AND)
                tok = new Token(AND);
                return tok;

            case 33:
                // retorna token > (GT)
                tok = new Token(GT);
                return tok;

            case 34:
                // retorna token < (LT)
                tok = new Token(LT);
                return tok;

            case 35:
                // retorna token + (PLUS)
                tok = new Token(PLUS);
                return tok;
            
            case 36:
                // retorna token - (MINUS)
                tok = new Token(MINUS);
                return tok;

            case 37:
                // retorna token * (MULTI)
                tok = new Token(MULTI);
                return tok;

            case 38:
                // analisa se é um lexema = (ATTR) ou um == (EQ)
                if(input[pos] == '=')
                    state = 39;
                else
                    state = 300;
                pos++;
                break;

            case 39:
                // retorna token == (EQ)
                tok = new Token(EQ);
                return tok;

            case 300:
                // retorna token = (ATTR)
                tok = new Token(ATTR);
                pos--;
                return tok;
            
            case 301:
                // analisa se é um lexema ! (NOT) ou um != (NE)
                if(input[pos] == '=')
                    state = 302;
                else
                    state = 303;
                pos++;
                break;

            case 302:
                // retorna token != (NE)
                tok = new Token(NE);
                return tok;

            case 303:
                // retorna token ! (NOT)
                tok = new Token(NOT);
                pos--;
                return tok;

            case 40:
                // retorna token ( (OPAR)
                tok = new Token(SEP, OPAR);
                return tok;

            case 41:
                // retorna token ) (CPAR)
                tok = new Token(SEP, CPAR);
                return tok;

            case 42:
                // retorna token [ (OSB)
                tok = new Token(SEP, OSB);
                return tok;

            case 43:
                // retorna token ] (CSB)
                tok = new Token(SEP, CSB);
                return tok;

            case 44:
                // retorna token { (OCB)
                tok = new Token(SEP, OCB);
                return tok;

            case 45:
                // retorna token } (CCB)
                tok = new Token(SEP, CCB);
                return tok;

            case 46:
                // retorna token ; (SC)
                tok = new Token(SEP, SC);
                return tok;

            case 47:
                // retorna token . (CM)
                tok = new Token(SEP, CM);
                return tok;

            case 48:
                // retorna token , (PN)
                tok = new Token(SEP, PN);
                return tok;

            case 60:
                //se for um comentario ou um operador
                if (input[pos] == '/')
                    state = 61;
                else if(input[pos] == '*')
                    state = 62;
                else
                    state = 30;
                pos++;
                break;

            case 61:
                //quando chega no final do comentario
                if (input[pos] == '\n')
                {
                    line += 1;
                    state = 0;
                }
                pos++;
                break;
            case 62:
                //comentario de */
                if (input[pos] == '*')
                    state = 63;
                else if (input[pos] == '\n')
                    line += 1;
                pos++;
                break;
            case 63:
                //comentario de */
                if (input[pos] == '/')
                    state = 0;
                else
                {
                    if (input[pos] == '\n')
                        line += 1;
                    state = 62;
                }
                pos++;
                break;
        }
    }   
}

void 
Scanner::lexicalError(string lexeme, int linha)
{
    string errorText1 = "\nCompilation ERROR: \nO lexema " + lexeme + " (linha ";
    cout << errorText1;
    cout << linha;
    string errorText2 = ") NAO faz parte da linguagem MiniJava \n";
    cout << errorText2;
    
    exit(EXIT_FAILURE);
}

string
Scanner::returnName(int i){
    string tokenNames[46] = {"UNDEF",
                            "ID",
                            "BOOLEAN",
                            "CLASS",
                            "ELSE",
                            "EXTENDS",
                            "FALSE",
                            "IF",
                            "INT",
                            "LENGTH",
                            "MAIN",
                            "NEW",
                            "PUBLIC",
                            "RETURN",
                            "STATIC",
                            "STRING",
                            "SYSOUTPRINT",
                            "THIS",
                            "TRUE",
                            "VOID",
                            "WHILE",
                            "RELOP",
                            "EQ",
                            "NE",
                            "GT",
                            "LT",
                            "SEP",
                            "OCB",
                            "CCB",
                            "OSB",
                            "CSB",
                            "OPAR",
                            "CPAR",
                            "SC",
                            "CM",
                            "PN",
                            "NUMBER",
                            "INTEGER_LITERAL",
                            "AND",
                            "PLUS",
                            "MINUS",
                            "MULTI",
                            "DIV",
                            "ATTR",
                            "NOT",
                            "END_OF_FILE"};
    return tokenNames[i];
    
}

