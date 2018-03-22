#ifndef Processing_hpp
#define Processing_hpp

#include <iostream>
#include <vector>
#include <string>

#include "SearchSequence.hpp"
#include "SearchUnordered.hpp"
#include "SearchClosestMatch.hpp"
#include "Matrice.hpp"

using namespace std;

enum Operation {
    searchSequence,
    searchUnordered,
    searchClosestMatch
};

class Processing {
    public:
        Processing();
        static string applySearch(Operation, Matrice*, vector<int>);
};

#endif
