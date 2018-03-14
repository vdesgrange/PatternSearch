#include "../../include/Processing.hpp"

Processing::Processing() {
}

string Processing::applySearch(string searchOperation, Matrice mat, int sequence[]) {
    map<string, Operation> op;
    op["searchSequence"] = Operation::searchSequence;
    op["searchUnordered"] = Operation::searchUnordered;
    op["searchClosestMatch"] = Operation::searchClosestMatch;
    string result = "";
    Search *searchClass;

    switch(op[searchOperation]) {
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
