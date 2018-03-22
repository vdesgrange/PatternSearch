#include "../../include/Search.hpp"

/**
 * getPositionData
 * @brief Get details of the position of a research result.
 * @param {Matrice*} mat - object matrice
 * @param {Node*} node - node currently visited in suffix trie.
 */
Position Search::getPositionData(Matrice *mat, Node *node) {
    Position data;
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

    if (idxLine < rows) { // Is a row
        data.type = TypeLine::row;
        data.index = idxLine + 1; // Indexing from 1.
    } else {
        data.type = TypeLine::col;
        data.index = idxLine - rows + 1;
    }

    data.global = node->suffixIndex;
    data.local = position + 1;

    return data;
}

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
string Search::stringifyPosition(Position pos) {
    stringstream out;
   // out << "Found at position " << pos.local; // Not local position working well.
    if (pos.type == row) {
        out << "Found in row " << pos.index;
    } else if (pos.type == col){
        out << "Found in col " << pos.index;
    }

   return out.str();
}

