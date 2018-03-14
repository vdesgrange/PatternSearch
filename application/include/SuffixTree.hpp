#ifndef SuffixTree_hpp
#define SuffixTree_hpp

#define MAXCHARS 256

#include <iostream>
#include <string>

struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAXCHARS];
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

using namespace std;

class SuffixTree {
    Node *root;
    Node *lastNewNode;
    ActivePoint activePoint;
    int remainder;
    int end;
    int *rootEnd;
    int *splitEnd;
    int size;
    string sentence;

    public:
        SuffixTree();
        SuffixTree(string);
        void setActivePoint(Node*, int, int);
        void setSentence(string);
        Node* getRoot();
        Node* buildSuffixTree();
        void printSuffixTree(Node*, int);

    private:
        Node* createNewNode(int, int*);
        int getEdgeLength(Node*);
        bool walkDown(Node*);
        void extendSuffixTree(int, string);
        void setSuffixIndex(Node*, int);
};

#endif
