#ifndef Search_hpp
#define Search_hpp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "Matrice.hpp"
#include "SuffixTree.hpp"

using namespace std;

enum TypeLine {
    row,
    col
};

struct Position {
    int global;
    int local;
    TypeLine type;
    int index;
};

class Search {
    public:
        virtual string doSearch(Matrice*, vector<int>) = 0;
        static Position getPositionData(Matrice*, Node*);
        static string stringifyPosition(Position);

    private:
        virtual vector<Position> searchOperation(Matrice*, vector<int>) = 0;
        virtual string stringifyResult(vector<Position>) = 0;
};

#endif
