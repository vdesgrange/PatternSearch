#include "../../include/SearchUnordered.hpp"

SearchUnordered::SearchUnordered() {
}

string SearchUnordered::doSearch(Matrice mat, int sequence[]) {
    map<int, vector<int> > result = searchOperation(mat, sequence);
    return stringifyResult(result);
}

map<int, vector<int> > SearchUnordered::searchOperation(Matrice mat, int sequence[]) {
    map<int, vector<int> > result;
    return result;
}

string SearchUnordered::stringifyResult(map<int, vector<int> > research) {
    string result = "";
    return result;
}
