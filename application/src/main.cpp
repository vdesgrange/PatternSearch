#include "../include/Matrice.hpp"
#include "../include/Search.hpp"
#include "../include/SearchSequence.hpp"
#include "../include/Processing.hpp"

int main(int argc, const char * argv[]) {
    Matrice mat;
    vector<MatItem> vec;
    vector<int> pattern;

    vec.push_back({120, false});
    vec.push_back({97, false});
    vec.push_back({98, false});
    vec.push_back({120, false});
    vec.push_back({0, true});
    vec.push_back({97, false});
    vec.push_back({98, false});
    vec.push_back({120, false});
    vec.push_back({98, false});
    vec.push_back({1, true});

    pattern.push_back(98);
    pattern.push_back(120);

    mat.getSuffixTree()->setSentence(vec);
    mat.setRoot(mat.getSuffixTree()->buildSuffixTree());
    mat.getSuffixTree()->printSuffixTree(mat.getSuffixTree()->getRoot(), 0);
    cout << Processing::applySearch("searchSequence", mat, pattern) << endl;

    return 0;
}
