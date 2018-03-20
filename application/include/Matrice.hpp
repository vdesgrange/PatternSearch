#ifndef Matrice_hpp
#define Matrice_hpp

#include <iostream>
#include <string>

#include "SuffixTree.hpp"

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

using namespace std;

class Matrice {
    Node *root;
    SuffixTree tree;

    public:
        Matrice();
        ~Matrice();
        Node* getRoot();
        SuffixTree* getSuffixTree();
        void buildMatrice(vvvi);
        void toString();
        void setRoot(Node*);

    private:
        void setSuffixTree(SuffixTree);
};

#endif
