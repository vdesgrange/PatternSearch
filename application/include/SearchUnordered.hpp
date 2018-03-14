#ifndef SearchUnordered_hpp
#define SearchUnordered_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Matrice.hpp"
#include "Search.hpp"

using namespace std;

class SearchUnordered : public Search {
    public:
        SearchUnordered();
        string doSearch(Matrice, int[]);
    private:
        map<int, vector<int> > searchOperation(Matrice, int[]);
        string stringifyResult(map<int, vector<int> >);
};

#endif
