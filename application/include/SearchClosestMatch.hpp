#ifndef SearchClosestMatch_hpp
#define SearchClosestMatch_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

#include "Matrice.hpp"
#include "Search.hpp"

struct ExplorationNode {
    Node* node;
    int distance;
    int index;

};

struct Comp {
    bool operator() (const ExplorationNode &a, const ExplorationNode &b) const {
        return a.distance < b.distance;
    }
};

typedef priority_queue<ExplorationNode, vector<ExplorationNode>, Comp> pq;

using namespace std;

class SearchClosestMatch : public Search {
    public:
        SearchClosestMatch();
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
