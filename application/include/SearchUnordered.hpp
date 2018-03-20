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
        string doSearch(Matrice, vector<int>);
    private:
        typedef Search super;
        vector<Position> searchOperation(Matrice, vector<int>);
        string stringifyResult(vector<Position>);
};

#endif
