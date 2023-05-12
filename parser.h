#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;

		void advance();
		void match(int);
		
	public:
		Parser(string);
		void run();
        void program();
        void mainClass();
        void classdeclaration();
		void vardeclaration();
		void methoddeclaration();
		void type();
		void statement();
		void expression();
		void op();
        void error(string);
};