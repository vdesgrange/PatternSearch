#include "../../include/SearchClosestMatch.hpp"

SearchClosestMatch::SearchClosestMatch() {
}

string SearchClosestMatch::doSearch(Matrice mat, int sequence[]) {
    map<int, vector<int> > result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

map<int, vector<int> > SearchClosestMatch::searchOperation(Matrice mat, int sequence[]) {
    map<int, vector<int> > result;
    Node *root = mat.getRoot();
    return result;
}

string SearchClosestMatch::stringifyResult(map<int, vector<int> > research) {
    string result = "";
    return result;
}
