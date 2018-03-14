#ifndef Search_hpp
#define Search_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Matrice.hpp"

using namespace std;

class Search {
    public:
        virtual string doSearch(Matrice, int[]);
    private:
        virtual map<int, vector<int> > searchOperation(Matrice, int[]);
        virtual string stringifyResult(map<int, vector<int> >);
};

#endif
