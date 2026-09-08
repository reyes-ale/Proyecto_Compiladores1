#include <string>
#include <map>
using namespace std;

class Diccionario{
    private:
    map<string, string> conjunto;

    public:
    Diccionario();
    string buscar(string lexema);

};