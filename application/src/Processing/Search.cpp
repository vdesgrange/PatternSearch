#include "../../include/Search.hpp"

/**
 * stringifyPosition
 * @brief Stringify the position of a research result.
 * When a pattern position is find by research, this method
 * create a string with row col in the matrice and position in the row/col.
 * It is considering that we have a matrice with sentence of same length.
 * @param {Matrice*} mat - object matrice
 * @param {Node*} node - node currently visited in suffix trie.
 * @return {string} Position of the pattern.
*/
string Search::stringifyPosition(Matrice *mat, Node *node) {
    stringstream out;
    int idx = *(node->end);
    int rows = mat->getRows();
    int cols = mat->getCols();
    int idxEndRows = rows * (cols + 1);
    int idxLine = 0;
    // We consider having sentences of same length. Length x for rows and y for cols.
    int position = (node->suffixIndex / idxEndRows == 0) ?
        (node->suffixIndex % rows) :
        ((node->suffixIndex % idxEndRows) % cols );

    if (mat != nullptr && mat->getSuffixTree() != nullptr)
        idxLine = mat->getSuffixTree()->getSentence().at(idx).v;

    out << "Found at position "
        << position + 1;
    if (idxLine < rows) { // Is a row
        out << " in row " << idxLine + 1; // Indexing from 1.
    } else {
        out << " in col " << idxLine - rows + 1;
    }

   return out.str();
}

