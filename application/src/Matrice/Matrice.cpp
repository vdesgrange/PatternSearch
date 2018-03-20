#include "../../include/Matrice.hpp"

Matrice::Matrice () {
    root = nullptr;
}

Matrice::~Matrice () {
//    delete root;
}

/**
 * getRoot
 * @brief root suffix tree getter
 * @return {Node*} suffix tree node
 */
Node* Matrice::getRoot() {
    return this->root;
}

/**
 * setRoot
 * @brief root suffix tree setter
 * @param {Node*} suffix tree node
 */
void Matrice::setRoot(Node* node) {
    this->root = node;
}

/**
 * getSuffixTree
 * @brief  suffix tree getter
 * @return {SuffixTree} suffix tree
 */
SuffixTree* Matrice::getSuffixTree() {
    return &tree;
}

/**
 * setSuffixTree
 * @brief suffix tree setter
 * @param {SuffixTree} suffix tree
 */
void Matrice::setSuffixTree(SuffixTree tree) {
    this->tree = tree;
}

/**
 * buildMatrice
 * @brief Build a Matrice from vvvi.
 * Build a Matrice (generalised suffix tree) from simple
 * data structure vvvi created from file content.
 * In this implementation we consider there is only one value per item.
 * @TODO - Update to handle multiple items.
 * @param {vvvi} content - simple matrix data structure, rows of cols of items.
 */
void Matrice::buildMatrice(vvvi content) {
    vector<MatItem> source;
    int index(0);

    for (const auto& row : content) {
        for (const auto& col : row) { // We consider only 1 value per item.
            source.push_back({col.front(), false});
        }
        source.push_back({index, true});
        index++;
    }

    this->tree.setSentence(source);
    setRoot(this->tree.buildSuffixTree());
}

/**
 * toString
 * @brief Stringify matrice
 * @TODO
 */
void Matrice::toString() {
    this->tree.printSuffixTree(getRoot(), 0);
}

