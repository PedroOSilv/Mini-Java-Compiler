#include "scanner.cpp"

int main(int argc, char* argv[]) 
{
    //Verifica se foi executado corretamente
    //Essa main espera receber o nome do arquivo a ser
    //executado na linha de comando.
    if (argc != 2){
        
        cout << "Uso: ./principal nome_arquivo.mj\n";
        return 1;
    }

    string input;

    Scanner* scanner = new Scanner(argv[1]);
    
    Token* t;
    
    do{
        t = scanner->nextToken();
        
        cout << scanner->returnName(t->name) + " ";
        
    }while (t->name != END_OF_FILE);

    cout<< "\n";
    delete scanner;
    
    return 0; 
}