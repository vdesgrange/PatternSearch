#ifndef Processing_hpp
#define Processing_hpp

#include <iostream>
#include <map>
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
        static string applySearch(string, Matrice, int[]);
};

#endif
