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
    friend class SearchSequenceTest;

    public:
        SearchSequence();
        string doSearch(Matrice*, vector<int>);
    private:
        typedef Search super;
        vector<Position> searchOperation(Matrice*, vector<int>);
        string stringifyResult(vector<Position>);
        int matriceTraversal(Matrice*, Node*, vector<int>, int, vector<Position>*);
        int traverseEdge(Matrice*, vector<int>, int, int, int);
        int doTraversalToCountLeaf(Matrice*, Node*, vector<Position>*);
};

#endif
