#include "../../include/SearchClosestMatch.hpp"

SearchClosestMatch::SearchClosestMatch() {
}

string SearchClosestMatch::doSearch(Matrice mat, vector<int> sequence) {
    cout << "Make sequence research." << endl;
    vector<Position> result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

/**
 * searchOperation
 */
vector<Position> SearchClosestMatch::searchOperation(Matrice mat, vector<int> pattern) {
    vector<Position> result;
    int numberMatching(0);
    Node *root = mat.getRoot();
    numberMatching = matriceTraversal(mat, root, pattern, 0, &result);
    return result;
}

/**
 * stringifyResult
 * @brief Stringi the result of the pattern search.
 * @param {vector<Position>} vec - list of positions matching.
 * @return {string} Return the stringify result of the pattern search.
 */
string SearchClosestMatch::stringifyResult(vector<Position> vec) {
    stringstream ss;
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
int SearchClosestMatch::matriceTraversal(Matrice mat, Node *node, vector<int> pattern, int index, vector<Position> *result) {
    pq q;
    q.push({node, node, 0, 0});
    int penalty(0);
    Node* bestNode = nullptr;

    if (node == nullptr)
        return -1;

    while (!q.empty() && bestNode == nullptr) {
        ExplorationNode enode = q.top();
        q.pop();
        if (enode.distance >= pattern.size()) {
            bestNode = enode.node;
        } else {
            for (auto &it : enode.node->children) {
                penalty = traverseEdge(&mat, pattern, enode.index, it.second->start, *(it.second->end));
                q.push({it.second, enode.node, enode.distance + penalty, enode.index + mat.getSuffixTree()->getEdgeLength(it.second)});
            }
        }
    }

    cout << "#######################" << endl;
    mat.getSuffixTree()->printSuffixTree(bestNode, 0);
    cout << "#######################" << endl;
    cout << super::stringifyPosition(super::getPositionData(&mat, bestNode)) << endl;;
    return 0;
    /*int res(-1);
    if (node->start != -1) {
        //res = traverseEdge(&mat, pattern, index, node->start, *(node->end));
        if (res == -1)
            return -1;

        if (res == 1) {
            if (node->suffixIndex > -1) {
                result->push_back(super::getPositionData(&mat, node));
            } else {
                //doTraversalToCountLeaf(&mat, node, result);
            }
            return 1;
        }
    }

    index = index + mat.getSuffixTree()->getEdgeLength(node);

    MatItem item = {pattern[index], false};
    if (node->children[item]) {
        return matriceTraversal(mat, node->children[item], pattern, index, result);
    } else {
        return -1;
    }*/
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
int SearchClosestMatch::traverseEdge(Matrice *mat, vector<int> pattern, int idx, int start, int end) {
    int penalty(0);
    vector<MatItem> sentence = mat->getSuffixTree()->getSentence();

    for(int i(start); i <= end && idx < pattern.size(); i++, idx++) {
        if (sentence[i].isSeparator)
                return penalty;
        if (sentence[i].v != pattern[idx])
            penalty++;
     }

    return penalty; // Pattern is bigger than the edge, processing continue later.
}
