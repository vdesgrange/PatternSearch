#ifndef SearchClosestMatch_hpp
#define SearchClosestMatch_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Matrice.hpp"
#include "Search.hpp"

using namespace std;

class SearchClosestMatch : public Search {
    public:
        SearchClosestMatch();
        string doSearch(Matrice, vector<int>);
    private:
        map<int, vector<int> > searchOperation(Matrice, vector<int>);
        string stringifyResult(map<int, vector<int> >);
};

#endif
