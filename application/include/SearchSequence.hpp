#ifndef SearchSequence_hpp
#define SearchSequence_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Matrice.hpp"
#include "Search.hpp"

using namespace std;

class SearchSequence : public Search {
    public:
        string doSearch(Matrice, int[]);
    private:
        map<int, vector<int> > searchOperation(Matrice, int[]);
        string stringifyResult(map<int, vector<int> >);
};

#endif
