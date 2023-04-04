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
    LT,//9
    SEP,//10
    NUMBER,//11
    INTEGER_LITERAL,//12
    AND,//13
    PLUS,//14
    MINUS,//15
    MULTI,//16
    DIV,//17
    ATTR,//18
    NOT,//19
    END_OF_FILE//20
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
