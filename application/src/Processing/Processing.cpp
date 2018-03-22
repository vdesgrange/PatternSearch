#include "../../include/Processing.hpp"

Processing::Processing() {
}

string Processing::applySearch(Operation searchOperation, Matrice *mat, vector<int> sequence) {
    string result = "";
    Search *searchClass;

    switch(searchOperation) {
        case 0 :
            searchClass = new SearchSequence();
            result = searchClass->doSearch(mat, sequence);
            break;
        case 1 :
            searchClass = new SearchUnordered();
            result = searchClass->doSearch(mat, sequence);
            break;
        case 2 :
            searchClass = new SearchClosestMatch();
            result = searchClass->doSearch(mat, sequence);
            break;
        default :
            break;
    }

    return result;
}
