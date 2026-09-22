#include <iostream>
#include <cstdlib>
#include <vector>
#include "Token.h"
using namespace std;

class Parser {
    private:
        vector<Token> tokens;
        int actual;

    public:
        Parser();
        Parser(vector<Token> t);
        int getActual();
        void siguiente();
        Token actual();
        Token siguiente();
        
};
