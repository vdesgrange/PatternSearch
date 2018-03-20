#include "../../include/SearchSequence.hpp"

SearchSequence::SearchSequence() {
}

string SearchSequence::doSearch(Matrice mat, vector<int> sequence) {
    cout << "Make sequence research." << endl;
    map<int, vector<int> > result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

map<int, vector<int> > SearchSequence::searchOperation(Matrice mat, vector<int> pattern) {
    map<int, vector<int> > result;
    Node *root = mat.getRoot();
    matriceTraversal(mat, root, pattern, 0);
    return result;
}

string SearchSequence::stringifyResult(map<int, vector<int> > research) {
    string result = "";
    return result;
}

int SearchSequence::matriceTraversal(Matrice mat, Node *node, vector<int> pattern, int index) {
    if (node == nullptr)
        return -1;

    int res(-1);
    if (node->start != -1) {
        res = traverseEdge(&mat, pattern, index, node->start, *(node->end));
        if (res == -1)
            return -1;

        if (res == 1) {
            if (node->suffixIndex > -1)
                cout << node->suffixIndex << endl;
            else
                cout << countLeaf(node) << endl;
            return 1;
        }
    }

    index = index + mat.getSuffixTree()->getEdgeLength(node);

    MatItem item = {pattern[index], false};
    if (node->children[item]) {
        return matriceTraversal(mat, node->children[item], pattern, index);
    } else {
        return -1;
    }
}

int SearchSequence::traverseEdge(Matrice *mat, vector<int> pattern, int idx, int start, int end) {
    vector<MatItem> sentence = mat->getSuffixTree()->getSentence();

    for(int i(start); i <= end && idx < pattern.size(); i++, idx++) {
         if (sentence[i].v != pattern[idx] || sentence[i].isSeparator == true)
             return -1;
     }

    if(idx >=  pattern.size())
        return 1;

    return 0;
}

int SearchSequence::doTraversalToCountLeaf(Node *node) {
    if (node == nullptr)
        return 0;

    if (node->suffixIndex > -1 ){
        cout << "Found at position " << node->suffixIndex << endl;
        return 1;
    }

    int count(0);
    map<MatItem, SuffixTreeNode*>::iterator it;
    for (auto it : node->children) {
        count += doTraversalToCountLeaf(it.second);
    }

    return count;

}

int SearchSequence::countLeaf(Node *node) {
    if (node == nullptr)
        return 0;
    return doTraversalToCountLeaf(node);
}

