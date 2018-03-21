#ifndef Matrice_hpp
#define Matrice_hpp

#include <iostream>
#include <string>

#include "SuffixTree.hpp"

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

class Matrice {
    Node *root;
    SuffixTree tree;
    int rows, cols;

    public:
        Matrice();
        ~Matrice();
        SuffixTree* getSuffixTree();
        void buildMatrice(vvvi);
        void toString();

        Node* getRoot();
        int getRows();
        int getCols();
        void setRoot(Node*);
        void setRows(int);
        void setCols(int);

    private:
        void setSuffixTree(SuffixTree);
};

#endif
