#include "../../include/test/SuffixTreeTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SuffixTreeTest );

void SuffixTreeTest::testConstructor()
{

    vector<MatItem> vec;
    vec.push_back({97, false});
    vec.push_back({98, false});

    ActivePoint ap;
    ap.activeNode = nullptr;
    ap.activeEdge = 0;
    ap.activeLength = 0;
    Node* n = nullptr;
    const Node* n2(nullptr);
    SuffixTree tree(vec);

    CPPUNIT_ASSERT_EQUAL(n, tree.getRoot());
    CPPUNIT_ASSERT_EQUAL(0, tree.getRemainder());
    CPPUNIT_ASSERT_EQUAL(0, tree.getEnd());
    CPPUNIT_ASSERT_EQUAL(-1, tree.getSize());
    // CPPUNIT_ASSERT_EQUAL(ap, tree.getActivePoint());
    CPPUNIT_ASSERT_EQUAL(n2, tree.getLastNewNode());
}


void SuffixTreeTest::testCreateNewNode()
{
    SuffixTree tree;
    int start(0), end(0);
    Node *expected_result = nullptr;
    expected_result->suffixLink = tree.getRoot();
    expected_result->start = start;
    expected_result->end = &end;
    expected_result->suffixIndex = -1;

    //CPPUNIT_ASSERT_EQUAL(expected_result, tree.createNewNode(start, &end));
}

void SuffixTreeTest::testBuildSuffixTree()
{
}

void SuffixTreeTest::testWalkDown()
{
}

void SuffixTreeTest::testExtendSuffixTree()
{
}

void SuffixTreeTest::testSetSuffixIndex()
{
}
