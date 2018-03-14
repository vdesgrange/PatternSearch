#ifndef SuffixTree_hpp
#define SuffixTree_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct MatItem {
    int v = 0;
    bool isSeparator = false;

};

struct MatItemComp {
    bool operator() (MatItem l, MatItem r) const
    { return l.v < r.v; }
};

struct SuffixTreeNode {
    map<MatItem, SuffixTreeNode*, MatItemComp> children;
    struct SuffixTreeNode *suffixLink;
    int start;
    int *end;
    int suffixIndex;
};

typedef SuffixTreeNode Node;

struct ActivePoint {
    Node *activeNode = nullptr;
    int activeEdge = 0;
    int activeLength = 0;
};

class SuffixTree {
    Node *root;
    Node *lastNewNode;
    ActivePoint activePoint;
    int remainder;
    int end;
    int *rootEnd;
    int *splitEnd;
    int size;
    vector<MatItem> sentence;

    public:
        SuffixTree();
        SuffixTree(vector<MatItem>);
        ~SuffixTree();
        void setActivePoint(Node*, int, int);
        void setSentence(vector<MatItem>);
        Node* getRoot();
        Node* buildSuffixTree();
        void printSuffixTree(Node*, int);

    private:
        Node* createNewNode(int, int*);
        int getEdgeLength(Node*);
        bool walkDown(Node*);
        void extendSuffixTree(int, vector<MatItem>);
        void setSuffixIndex(Node*, int);
        void freeSuffixTreeByPostOrder(Node*);
};

#endif
