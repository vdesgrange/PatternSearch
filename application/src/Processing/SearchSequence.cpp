#include "../../include/SearchSequence.hpp"

SearchSequence::SearchSequence() {
}

/**
 * doSearch
 */
string SearchSequence::doSearch(Matrice *mat, vector<int> sequence) {
    cout << "Make sequence research." << endl;
    vector<Position> result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

/**
 * searchOperation
 */
vector<Position> SearchSequence::searchOperation(Matrice *mat, vector<int> pattern) {
    vector<Position> result;
    int numberMatching(0);
    Node *root = mat->getRoot();
    numberMatching = matriceTraversal(mat, root, pattern, 0, &result);
    return result;
}

/**
 * stringifyResult
 * @brief Stringi the result of the pattern search.
 * @param {vector<Position>} vec - list of positions matching.
 * @return {string} Return the stringify result of the pattern search.
 */
string SearchSequence::stringifyResult(vector<Position> vec) {
    stringstream ss;
    ss << "There are " << vec.size() << " matches.\n";

    for (auto &it : vec) {
        ss << super::stringifyPosition(it) << "\n";
    };

    return ss.str();
}

/**
 * matriceTraversal
 * @brief  Go through generalised suffix tree to match pattern.
 * It go through the branch of the generalised suffix tree in order to match the pattern
 * into different position.
 * Method will print every position where pattern have been located of the suffix trie.
 * Print method is integrated.
 * @param {Matrice} mat - Matrice data structure.
 * @param {Node} node - node currently visited
 * @param {vector<int>} pattern - pattern of integer we are looking into our tree.
 * @param {int} index - current index into pattern
 * @return {int} Number of matching.
 */
int SearchSequence::matriceTraversal(Matrice *mat, Node *node, vector<int> pattern, int index, vector<Position> *result) {
    if (node == nullptr)
        return -1;

    int res(-1);
    if (node->start != -1) {
        res = traverseEdge(mat, pattern, index, node->start, *(node->end));
        if (res == -1)
            return -1;

        if (res == 1) {
            if (node->suffixIndex > -1) {
                result->push_back(super::getPositionData(mat, node));
            } else {
                doTraversalToCountLeaf(mat, node, result);
            }
            return 1;
        }
    }

    index = index + mat->getSuffixTree()->getEdgeLength(node);

    MatItem item = {pattern[index], false};
    if (node->children[item]) {
        return matriceTraversal(mat, node->children[item], pattern, index, result);
    } else {
        return -1;
    }
}

/**
 * traverseEdge
 * @brief Go through the edge of the suffix trie.
 * It goes through the edge of the suffix trie (getting with start and end from the suffix tree sentence).
 * It try to match every value of the pattern.
 * @param {Matrice*} mat - matrice data structure
 * @param {vector<int>} pattern - pattern we are researching.
 * @param {int} idx - position index in the pattern.
 * @param {int} start - starting index of the suffix trie sentence.
 * @param {int} end - end index of the suffix trie sentence.
 */
int SearchSequence::traverseEdge(Matrice *mat, vector<int> pattern, int idx, int start, int end) {
    vector<MatItem> sentence = mat->getSuffixTree()->getSentence();

    for(int i(start); i <= end && idx < pattern.size(); i++, idx++) {
         if (sentence[i].v != pattern[idx] || sentence[i].isSeparator == true)
             return -1; // Pattern doesn't correspond
     }

    if(idx >=  pattern.size())
        return 1; // We arrive at the end of the pattern. It is a match.

    return 0; // Pattern is bigger than the edge, processing continue later.
}

/**
 * doTraversalToCountLeaf
 * @brief DFS to count leaf.
 * Method used to find full list of match and a pattern has been found
 * and severals branch/leafs are under it (so matchs in different sentences)..
 * @param {Matrice*} mat - matrice data structure
 * @param {Node*} node - node currently visited.
 * @return {int} total number of match.
 */
int SearchSequence::doTraversalToCountLeaf(Matrice *mat, Node *node, vector<Position> *result) {
    if (node == nullptr)
        return 0;

    if (node->suffixIndex > -1 ){
        result->push_back(super::getPositionData(mat, node));
        return 1;
    }

    int count(0);
    map<MatItem, SuffixTreeNode*>::iterator it;
    for (auto it : node->children) {
        count += doTraversalToCountLeaf(mat, it.second, result);
    }

    return count;

}

