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
        SearchSequence();
        string doSearch(Matrice, vector<int>);
    private:
        map<int, vector<int> > searchOperation(Matrice, vector<int>);
        string stringifyResult(map<int, vector<int> >);
        int matriceTraversal(Matrice mat, Node*, vector<int>, int);
        int traverseEdge(Matrice *mat, vector<int>, int, int, int);
        int doTraversalToCountLeaf(Node*);
        int countLeaf(Node*);
};

#endif
