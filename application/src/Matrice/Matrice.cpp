#include "../../include/Matrice.hpp"

Matrice::Matrice () {
    root = nullptr;
    rows = 0;
    cols = 0;
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
 * getRows
 * @brief  rows getter
 * @return {int} number of rows
 */
int Matrice::getRows() {
    return this->rows;
}

/**
 * setRows
 * @brief  rows setter
 * @param {int} number of rows
 */
void Matrice::setRows(int rows) {
    this->rows = rows;
}

/**
 * getCols
 * @brief  cols getter
 * @return {int} number of cols
 */
int Matrice::getCols() {
    return this->cols;
}

/**
 * setRows
 * @brief  rows setter
 * @param {int} number of rows
 */
void Matrice::setCols(int cols) {
    this->cols = cols;
}

/**
 * buildMatrice
 * @brief Build a Matrice from vvvi.
 * Build a Matrice (generalised suffix tree) from simple
 * data structure vvvi created from file content.
 * In this implementation we consider there is only one value per item.
 * Add both rows and cols.
 * @TODO - Update to handle multiple items.
 * @param {vvvi} content - simple matrix data structure, rows of cols of items.
 */
void Matrice::buildMatrice(vvvi content) {
    vector<MatItem> source;
    vector<vector<MatItem>> source2;
    int index(0);
    int idxColumn(0);

    // Update Matrice number of cols and rows values.
    this->setRows(content.size());
    if (content.size() > 0) {
        this->setCols(content.front().size());
        source2.resize(this->getCols());
    }

    // Concatenate every row to our sentence.
    for (auto &row : content) {
        idxColumn = 0;
        for (auto &col : row) { // We consider only 1 value per item.
            source.push_back({col.front(), false});
            source2[idxColumn].push_back({col.front(), false});
            idxColumn++;
        }
        // Add separator.
        source.push_back({index, true});
        index++;
    }

    // Add columns line to our concatenated sentence.
    for (auto &col : source2) {
        source.insert(source.end(), col.begin(), col.end());
        // Add separator
        source.push_back({index, true});
        index++;
    }

    // Update suffixtree sentence property
    this->tree.setSentence(source);
    // Build generalised suffix tree based on the previous sentence.
    setRoot(this->tree.buildSuffixTree());
}

/**
 * toString
 * @brief Stringify matrice
 * Displaying method.
 */
void Matrice::toString() {
    cout
        << "Matrice ("
        << this->getRows()
        << " x "
        << this->getCols()
        << ")"
        << endl;

    this->tree.printSuffixTree(getRoot(), 0);
}

