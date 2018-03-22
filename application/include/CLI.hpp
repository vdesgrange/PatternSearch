#ifndef CLI_hpp
#define CLI_hpp

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <regex>
#include <sstream>
#include <map>

#include "Matrice.hpp"
#include "FileProcessor.hpp"
#include "Processing.hpp"

struct Action {
    Operation op;
    vector<int> sequence;
};

using namespace std;

class CLI {
    Matrice* mat;

    public:
        CLI();
        ~CLI();
        Matrice* getMatrice();
        void setMatrice(Matrice*);
        static Action processUserEntry(string);
        string actionController(Action);
        void displayResult(Action, string);
        void workflow(Matrice*);
};

#endif
