#ifndef SuffixTree_hpp
#define SuffixTree_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>

using namespace std;

struct MatItem {
    int v = 0;
    bool isSeparator = false;
};

struct MatItemComp {
    bool operator() (const MatItem &l, const MatItem &r) const {
        if (l.isSeparator && !r.isSeparator) {
            return true;
        } else if (!l.isSeparator && r.isSeparator) {
            return false;
        } else if (l.v < r.v) {
            return true;
        } else {
            return false;
        }
    }
};

struct SuffixTreeNode {
    map<MatItem, SuffixTreeNode*, MatItemComp> children;
    struct SuffixTreeNode *suffixLink;
    int start;
    int *end;
    int suffixIndex;

    bool operator==(const SuffixTreeNode& a) const {
        return a.suffixLink == this->suffixLink
            && a.start == this->start
            && *(a.end) == *(this->end)
            && a.suffixIndex == this->suffixIndex;
    }
};

typedef SuffixTreeNode Node;

struct ActivePoint {
    Node *activeNode = nullptr;
    int activeEdge = 0;
    int activeLength = 0;

    bool operator==(const ActivePoint& a) const {
        return a.activeNode == this->activeNode
            && a.activeEdge == this->activeEdge
            && a.activeLength == this->activeLength;
    }
};

class SuffixTree {
    friend class SuffixTreeTest;

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
        Node* buildSuffixTree();
        void printSuffixTree(Node*, int);

        Node* getRoot();
        vector<MatItem> getSentence();
        const Node* getLastNewNode();
        int getRemainder();
        int getEnd();
        ActivePoint getActivePoint();
        const int* getRootEnd();
        const int* getSplitEnd();
        int getSize();
        int getEdgeLength(Node*);
        void setSentence(vector<MatItem>);

    protected:
        void setRoot(Node *node);
        void setLastNewNode(Node *node);
        void setRemainder(int i);
        void setEnd(int i);
        void setActivePoint(Node*, int, int);
        void setSplitEnd(int i);
        void setSize(int i);
        void setRootEnd(int i);

    private:
        Node* createNewNode(int, int*);
        bool walkDown(Node*);
        void extendSuffixTree(int, vector<MatItem>);
        void setSuffixIndex(Node*, int);
        void freeSuffixTreeByPostOrder(Node*);
};

#endif
