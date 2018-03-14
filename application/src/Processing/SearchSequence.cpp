#include "../../include/SearchSequence.hpp"

SearchSequence::SearchSequence() {
}

string SearchSequence::doSearch(Matrice mat, int sequence[]) {
    map<int, vector<int> > result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

map<int, vector<int> > SearchSequence::searchOperation(Matrice mat, int sequence[]) {
    map<int, vector<int> > result;
    Node *root = mat.getRoot();
    return result;
}

string SearchSequence::stringifyResult(map<int, vector<int> > research) {
    string result = "";
    return result;
}

int SearchSequence::matriceTraversal(Node *node, int sequence[], int index) {
    return 0;
}
