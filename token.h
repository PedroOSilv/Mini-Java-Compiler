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
    OCB, //11 {
    CCB, //12 }
    OSB, //13 [
    CSB, //14 ]
    OPAR, //15 (
    CPAR, //16 )
    SC, //17 ;
    CM, //18 ,
    PN, //19 .
    NUMBER,//20
    INTEGER_LITERAL,//21
    AND,//22
    PLUS,//23
    MINUS,//24
    MULTI,//25
    DIV,//26
    ATTR,//27
    NOT,//28
    END_OF_FILE//29
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
