#include "../../include/Processing.hpp"

string Processing::applySearch(string searchOperation, Matrice mat, int sequence[]) {
    map<string, Operation> op;
    op["searchSequence"] = Operation::searchSequence;
    op["searchUnordered"] = Operation::searchUnordered;
    op["searchClosestMatch"] = Operation::searchClosestMatch;
    string result = "";
    Search searchClass;

    switch(op[searchOperation]) {
        case 0 :
            searchClass = SearchSequence();
            result = searchClass.doSearch(mat, sequence);
            break;
        case 1 :
            searchClass = SearchUnordered();
            result = searchClass.doSearch(mat, sequence);
            break;
        case 2 :
            searchClass = SearchClosestMatch();
            result = searchClass.doSearch(mat, sequence);
            break;
        default :
            break;
    }

    return result;
}
