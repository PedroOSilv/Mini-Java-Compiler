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
                Comentárois - state começa com o número 6
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
                    state = 11;

                //se for comentario ou o operador '/'
                else if(input[pos]=='/')
                    state = 101;
                
                //se for um separador
                else if (input[pos]=='(' |
                         input[pos]==')' |
                         input[pos]=='[' |
                         input[pos]==']' |
                         input[pos]=='{' |
                         input[pos]=='}' |
                         input[pos]==';' |
                         input[pos]=='.' |
                         input[pos]==',')
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
                // operador 
                //TODO


                pos++;
                break;

            case 1:
                //se for um id:
                if(!isalnum(input[pos]))
                    state = 2;
                pos++;
                break;

            case 2:
                //retorna um id
                tok = new Token(ID);
                pos--;
                return tok;
                
            case 11:
                //se  for digito
                if(!isdigit(input[pos]))
                    state =12;
                pos++;
                break;

            case 12:
                //retorna digito
                tok = new Token(NUMBER);
                pos--;
                return tok;
            
            case 20:
                //caso seja um reparador
                tok = new Token(SEP);
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
                    lexicalError("Lexema não pertencente à linguagem MiniJava");
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

            case 101:
                //se for um comentario ou um operador
                if (input[pos] == '/')
                    state = 102;
                else if(input[pos] == '*')
                    state = 103;
                else
                    state = 30;
                pos++;
                break;

            case 102:
                //quando chega no final do comentario
                if (input[pos] == '\n')
                    state = 0;
                pos++;
                break;
            case 103:
                //comentario de */
                if (input[pos] == '*')
                    state = 104;
                pos++;
                break;
            case 104:
                //comentario de */
                if (input[pos] == '/')
                    state = 0;
                pos++;
                break;
        }
    }   
}

void 
Scanner::lexicalError(string)
{
    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}

string
Scanner::returnName(int i){
    string tokenNames[22] = {"UNDEF",
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

