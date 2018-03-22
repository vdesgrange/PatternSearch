#include "../../include/test/SearchClosestMatchTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SearchClosestMatchTest );

void SearchClosestMatchTest::testMatriceTraversal() {
    vector<vector<int>> cols = {{255}, {155}, {55}};
    vector<vector<vector<int>>> data(3, cols);
    vector<int> sequence = {155, 155};
    vector<Position> expected_result_vec;
    expected_result_vec.push_back({1, 1, row, 1});
    expected_result_vec.push_back({4, 1, col, 2});
    expected_result_vec.push_back({9, 1, col, 3});
    vector<Position> result_vec;
    SearchClosestMatch search;
    Matrice *mat = new Matrice();
    mat->buildMatrice(data);
    int expected_result = 3;

    int result = search.matriceTraversal(mat, mat->getRoot(), sequence, 0, &result_vec);
    CPPUNIT_ASSERT_EQUAL(expected_result, result);
    CPPUNIT_ASSERT_EQUAL(expected_result_vec.size(), result_vec.size());
    CPPUNIT_ASSERT(expected_result_vec.at(0) == result_vec.at(0));
    CPPUNIT_ASSERT(expected_result_vec.at(1) == result_vec.at(1));
}

void SearchClosestMatchTest::testStringifyResult() {
    // 255 155 55
    // 255 155 55
    // 255 155 55
    stringstream expected_resultA, expected_resultB;
    vector<Position> vecA, vecB;
    vecA.push_back({2, 2, row, 1});
    vecA.push_back({14, 2, col, 1});
    vecB.push_back({13, 2, col, 1});
    vecB.push_back({14, 2, col, 1});

    SearchClosestMatch search;
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

void SearchClosestMatchTest::testSearchOperation() {
    vector<vector<int>> cols = {{255}, {155}, {55}};
    vector<vector<vector<int>>> data(3, cols);
    vector<int> sequence = {255, 55};
    SearchClosestMatch search;
    Matrice *mat = new Matrice();
    mat->buildMatrice(data);

    vector<Position> expected_result, result;
    expected_result.push_back({1, 1, row, 1});
    expected_result.push_back({4, 1, col, 2});
    expected_result.push_back({9, 1, col, 3});
    result = search.searchOperation(mat, sequence);

    CPPUNIT_ASSERT_EQUAL(expected_result.size(), result.size());
    CPPUNIT_ASSERT(expected_result.at(0) == result.at(0));
    CPPUNIT_ASSERT(expected_result.at(1) == result.at(1));

}

void SearchClosestMatchTest::testDoSearch() {
    // 255 155 55
    // 255 155 55
    // 255 155 55
    vector<vector<int>> cols = {{255}, {155}, {55}};
    vector<vector<vector<int>>> data(3, cols);
    vector<int> sequence = {255, 55};
    stringstream expected_result;
    SearchClosestMatch search;
    expected_result << "There are 3 matches.\n"
        << "Found in row 1\n"
        << "Found in row 2\n"
        << "Found in row 3\n";
    Matrice *mat = new Matrice();
    mat->buildMatrice(data);
    CPPUNIT_ASSERT_EQUAL(expected_result.str(), search.doSearch(mat, sequence));
}
