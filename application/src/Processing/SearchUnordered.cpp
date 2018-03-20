#include "../../include/SearchUnordered.hpp"

SearchUnordered::SearchUnordered() {
}

string SearchUnordered::doSearch(Matrice mat, vector<int> sequence) {
    cout << "Make sequence research." << endl;
    vector<Position> result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

/**
 * searchOperation
 */
vector<Position> SearchUnordered::searchOperation(Matrice mat, vector<int> pattern) {
    vector<Position> result;
    int numberMatching(0);
    Node *root = mat.getRoot();
    return result;
}

/**
 * stringifyResult
 * @brief Stringi the result of the pattern search.
 * @param {vector<Position>} vec - list of positions matching.
 * @return {string} Return the stringify result of the pattern search.
 */
string SearchUnordered::stringifyResult(vector<Position> vec) {
    stringstream ss;
    return ss.str();
}
