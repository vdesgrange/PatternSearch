#include "../../include/SearchClosestMatch.hpp"

SearchClosestMatch::SearchClosestMatch() {
}

string SearchClosestMatch::doSearch(Matrice *mat, vector<int> sequence) {
    cout << "Make sequence research." << endl;
    vector<Position> result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

/**
 * searchOperation
 */
vector<Position> SearchClosestMatch::searchOperation(Matrice *mat, vector<int> pattern) {
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
string SearchClosestMatch::stringifyResult(vector<Position> vec) {
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
int SearchClosestMatch::matriceTraversal(Matrice *mat, Node *node, vector<int> pattern, int index, vector<Position> *result) {
    pq q;
    q.push({node, 1000000, 0});
    int penalty(0);
    ExplorationNode bestNode = {nullptr, 10000000, 0};

    if (node == nullptr)
        return -1;

    while (!q.empty()) {
        ExplorationNode enode = q.top();
        q.pop();

        // Exploration Node better than what we found earlier
        if (enode.index > bestNode.index && enode.distance <= bestNode.distance) {
            cout << "c" << endl;
            bestNode = enode;
            cout << bestNode.node->children.size() << endl;
        }

        if (enode.index >= pattern.size()) {
            // Shortest path to find pattern
            break;
        } else {
            // Ignore letter, penalty++
            q.push({enode.node,
                    enode.distance + 1,
                    enode.index + 1});
            for (auto &it : enode.node->children) {
                // Compute penalty of taking edge
                penalty = traverseEdge(mat, pattern, enode.index, it.second->start, *(it.second->end));
                q.push({it.second,
                        enode.distance + penalty,
                        enode.index + mat->getSuffixTree()->getEdgeLength(it.second) - penalty});
            }
        }
    }

    cout << "####" << endl;
    mat->getSuffixTree()->printSuffixTree(bestNode.node, 0);
    cout << "####" << endl;

    if (bestNode.node != nullptr && bestNode.node->suffixIndex > -1) {
        result->push_back(super::getPositionData(mat, bestNode.node));
    } else {
        doTraversalToCountLeaf(mat, bestNode.node, result);
    }
    return 0;
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
        // if (sentence[i].isSeparator)
        //         return penalty + (pattern.size() - idx - 1); // Pattern not finished. We add penality for remaining values.
        if (sentence[i].v != pattern[idx])
            penalty++; // hamming distance
     }

    return penalty; // Pattern is bigger than the edge, processing continue later.
}

/**
 * doTraversalToCountLeaf
 * @brief DFS to go to leaf.
 * @param {Matrice*} mat - matrice data structure
 * @param {Node*} node - node currently visited.
 * @return {int} total number of match.
 */
int SearchClosestMatch::doTraversalToCountLeaf(Matrice *mat, Node *node, vector<Position> *result) {
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

