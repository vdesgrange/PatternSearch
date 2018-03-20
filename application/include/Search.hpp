#ifndef Search_hpp
#define Search_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "Matrice.hpp"
#include "SuffixTree.hpp"

using namespace std;

class Search {
    public:
        virtual string doSearch(Matrice, vector<int>) = 0;
        static string stringifyPosition(Matrice*, Node*);

    private:
        virtual map<int, vector<int> > searchOperation(Matrice, vector<int>) = 0;
        virtual string stringifyResult(map<int, vector<int> >) = 0;
};

#endif
