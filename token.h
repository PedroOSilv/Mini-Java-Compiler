#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    BOOLEAN,//2
    CLASS,//3
    ELSE,//4
    EXTENDS,//5
    FALSE,//6
    IF,//7
    INT,//8
    LENGTH,//9
    MAIN,//10
    NEW,//11
    PUBLIC,//12
    RETURN,//13
    STATIC,//14
    STRING,//15
    SYSOUTPRINT,//16
    THIS,//17
    TRUE,//18
    VOID,//19
    WHILE,//20
    RELOP,//21
    EQ,//22
    NE,//23
    GT,//24
    LT,//25
    SEP,//26
    OCB, //27 {
    CCB, //28 }
    OSB, //29 [
    CSB, //30 ]
    OPAR, //31 (
    CPAR, //32 )
    SC, //33 ;
    CM, //34 ,
    PN, //35 .
    NUMBER,//36
    INTEGER_LITERAL,//37
    AND,//38
    PLUS,//39
    MINUS,//40
    MULTI,//41
    DIV,//42
    ATTR,//43
    NOT,//44
    END_OF_FILE//45
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
