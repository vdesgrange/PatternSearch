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
        void buildMatrice(vvvi);
        void toString();

    private:
        SuffixTree getSuffixTree();
        void setSuffixTree(SuffixTree);
        void setRoot(Node*);
};

#endif
