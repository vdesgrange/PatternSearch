#include "../../include/test/SearchSequenceTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SearchSequenceTest );

void SearchSequenceTest::testTraverseEdge() {
}

void SearchSequenceTest::testDoTraversalToCountLeaf() {
}

void SearchSequenceTest::testMatriceTraversal() {
}

void SearchSequenceTest::testStringifyResult() {
    // 255 155 55
    // 255 155 55
    // 255 155 55
    stringstream expected_resultA, expected_resultB;
    vector<Position> vecA, vecB;
    vecA.push_back({2, 2, row, 1});
    vecA.push_back({14, 2, col, 1});
    vecB.push_back({13, 2, col, 1});
    vecB.push_back({14, 2, col, 1});

    SearchSequence search;
    expected_resultA << "There are 2 matches.\n"
        << "Found in row 1\n"
        << "Found in col 1\n";
    expected_resultB << "There are 2 matches.\n"
        << "Found in col 1\n"
        << "Found in col 1\n";

    // Check normal case with different rows/cols/
    CPPUNIT_ASSERT_EQUAL(expected_resultA.str(), search.stringifyResult(vecA));
    // Check case with several results find in same row/col.
    CPPUNIT_ASSERT_EQUAL(expected_resultB.str(), search.stringifyResult(vecB));
}

void SearchSequenceTest::testSearchOperation() {
    vector<vector<int>> cols = {{255}, {155}, {55}};
    vector<vector<vector<int>>> data(3, cols);
    vector<int> sequence = {155, 155};
    SearchSequence search;
    Matrice *mat = new Matrice();
    mat->buildMatrice(data);

    vector<Position> expected_result, result;
    expected_result.push_back({17, 3, col, 2});
    expected_result.push_back({16, 2, col, 2});
    result = search.searchOperation(mat, sequence);

    CPPUNIT_ASSERT_EQUAL(expected_result.size(), result.size());
    CPPUNIT_ASSERT(expected_result.at(0) == result.at(0));
    CPPUNIT_ASSERT(expected_result.at(1) == result.at(1));

}

void SearchSequenceTest::testDoSearch() {
    // 255 155 55
    // 255 155 55
    // 255 155 55
    vector<vector<int>> cols = {{255}, {155}, {55}};
    vector<vector<vector<int>>> data(3, cols);
    vector<int> sequence = {155, 155};
    stringstream expected_result;
    SearchSequence search;
    expected_result << "There are 2 matches.\n"
        << "Found in col 2\n"
        << "Found in col 2\n";
    Matrice *mat = new Matrice();
    mat->buildMatrice(data);
    CPPUNIT_ASSERT_EQUAL(expected_result.str(), search.doSearch(mat, sequence));
}
