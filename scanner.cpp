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

                pos++;
                break;

            case 1:
                //se for um id:
                if(!isalnum(input[pos]))
                    state = 11;
                pos++;
                break;

            case 11:
                //retorna um id
                tok = new Token(ID);
                pos--;
                return tok;
                
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
                    lexicalError(str);
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
                    state = 0;
                pos++;
                break;
            case 62:
                //comentario de */
                if (input[pos] == '*')
                    state = 63;
                pos++;
                break;
            case 63:
                //comentario de */
                if (input[pos] == '/')
                    state = 0;
                pos++;
                break;
        }
    }   
}

void 
Scanner::lexicalError(string lexeme)
{
    string errorText = "\nCompilation ERROR: \nO lexema " + lexeme + " não faz parte da linguagem MiniJava" + '\n';
    cout << errorText;
    
    exit(EXIT_FAILURE);
}

string
Scanner::returnName(int i){
    string tokenNames[30] = {"UNDEF",
                            "ID",
                            "IF",
                            "ELSE",
                            "THEN",
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

