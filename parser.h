#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;

		void advance();
		void match(int, string);
		
	public:
		Parser(string);
		void run();
        void program();
        void mainClass();
        void classdeclaration();
		void vardeclaration();
		void vardeclarionline();
		void methoddeclaration();
		void type();
		void statement();
		void statementline();
		void expression();
		void expressionline();
		void op();
        void error(string);
};