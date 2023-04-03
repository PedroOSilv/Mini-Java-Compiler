#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    IF,//2
    ELSE,//3
    THEN,//4
    RELOP,//5
    EQ,//6
    NE,//7
    GT,//8
    GE,//9
    LT,//10
    LE,//11
    SEP,//12
    NUMBER,//13
    DOUBLE_LITERAL,//14
    FLOAT_LITERAL,//15
    INTEGER_LITERAL,//16
    END_OF_FILE//17
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, string l)
        {
            this->name = name;
            attribute = UNDEF;
            lexeme = l;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};
