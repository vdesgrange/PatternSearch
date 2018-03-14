#ifndef Search_hpp
#define Search_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "SuffixTree.hpp"
#include "Matrice.hpp"

using namespace std;

class Search {
    public:
        virtual string doSearch(Matrice, int[]) = 0;
    private:
        virtual map<int, vector<int> > searchOperation(Matrice, int[]) = 0;
        virtual string stringifyResult(map<int, vector<int> >) = 0;
};

#endif
