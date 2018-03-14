#include "../../include/SearchSequence.hpp"

string SearchSequence::doSearch(Matrice mat, int sequence[]) {
    map<int, vector<int> > result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

map<int, vector<int> > SearchSequence::searchOperation(Matrice mat, int sequence[]) {
    map<int, vector<int> > result;
    return result;
}

string SearchSequence::stringifyResult(map<int, vector<int> > research) {
    string result = "";
    return result;
}
