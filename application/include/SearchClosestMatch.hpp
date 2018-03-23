#ifndef SearchClosestMatch_hpp
#define SearchClosestMatch_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

#include "Matrice.hpp"
#include "Search.hpp"

using namespace std;

struct ExplorationNode {
    Node* node;
    int distance;
    int index;

};

struct Comp {
    bool operator() (const ExplorationNode &a, const ExplorationNode &b) const {
            return (a.index > b.index) && (a.index - a.distance > b.index - b.distance);
    }
};

typedef priority_queue<ExplorationNode, vector<ExplorationNode>, Comp> pq;

class SearchClosestMatch : public Search {
    friend class SearchClosestMatchTest;

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
