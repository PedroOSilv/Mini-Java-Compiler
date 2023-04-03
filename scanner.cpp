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

                //se for comentario
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
                pos++;
                return tok;

            case 101:
                //se for um comentario
                if (input[pos] == '/')
                    state = 102;
                else if(input[pos] == '*')
                    state = 103;
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
    string tokenNames[18] = {"UNDEF",
                               "ID",
                               "IF",
                               "ELSE",
                               "THEN",
                               "RELOP",
                               "EQ",
                               "NE",
                               "GT",
                               "GE",
                               "LT",
                               "LE",
                               "SEP",
                               "NUMBER",
                               "DOUBLE_LITERAL",
                               "FLOAT_LITERAL",
                               "INTEGER_LITERAL",
                               "END_OF_FILE"};
    return tokenNames[i];
    
}

