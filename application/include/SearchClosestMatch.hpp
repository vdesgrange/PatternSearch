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
    Node* parentNode;
    int distance;
    int index;

    bool operator< (const ExplorationNode &n) const {
        return this->distance < n.distance;
    }
};

typedef priority_queue<ExplorationNode, vector<ExplorationNode>> pq;

using namespace std;

class SearchClosestMatch : public Search {
    public:
        SearchClosestMatch();
        string doSearch(Matrice, vector<int>);
    private:
        typedef Search super;
        vector<Position> searchOperation(Matrice, vector<int>);
        string stringifyResult(vector<Position>);
        int matriceTraversal(Matrice mat, Node*, vector<int>, int, vector<Position>*);
        int traverseEdge(Matrice *mat, vector<int>, int, int, int);
};

#endif
