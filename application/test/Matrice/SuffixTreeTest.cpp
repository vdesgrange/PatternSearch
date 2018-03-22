#include "../../include/test/SuffixTreeTest.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( SuffixTreeTest );

void SuffixTreeTest::testConstructor()
{

    vector<MatItem> vec;
    vec.push_back({97, false});
    vec.push_back({98, false});

    Node* n = nullptr;
    const Node* n2(nullptr);
    SuffixTree tree(vec);

    CPPUNIT_ASSERT_EQUAL(n, tree.getRoot());
    CPPUNIT_ASSERT_EQUAL(0, tree.getRemainder());
    CPPUNIT_ASSERT_EQUAL(0, tree.getEnd());
    CPPUNIT_ASSERT_EQUAL(-1, tree.getSize());
    CPPUNIT_ASSERT_EQUAL(n2, tree.getLastNewNode());
}


void SuffixTreeTest::testCreateNewNode()
{
    SuffixTree tree;
    int start(0), end(0);
    Node *expected_result = new Node();
    expected_result->suffixLink = tree.getRoot();
    expected_result->start = start;
    expected_result->end = &end;
    expected_result->suffixIndex = -1;

    //CPPUNIT_ASSERT_EQUAL(*expected_result, *(tree.createNewNode(start, &end)));
}

void SuffixTreeTest::testGetEdgeLength()
{
    SuffixTree tree;
    Node *node = new Node();
    node->start = 0;
    *(node->end) = 2;
    CPPUNIT_ASSERT_EQUAL(3, tree.getEdgeLength(node));
    CPPUNIT_ASSERT_EQUAL(0, tree.getEdgeLength(tree.getRoot()));
}

void SuffixTreeTest::testWalkDown()
{
    SuffixTree tree;
    Node *node = new Node();
    node->start = 0;
    node->end = new int();
    *(node->end) = 2;

    tree.setActivePoint(tree.getRoot(), 0, 3);
    CPPUNIT_ASSERT_EQUAL(true, tree.walkDown(node));
    CPPUNIT_ASSERT_EQUAL(3, tree.getActivePoint().activeEdge);
    CPPUNIT_ASSERT_EQUAL(0, tree.getActivePoint().activeLength);

    tree.setActivePoint(tree.getRoot(), 0, 1);
    CPPUNIT_ASSERT_EQUAL(false, tree.walkDown(node));
    CPPUNIT_ASSERT_EQUAL(0, tree.getActivePoint().activeEdge);
    CPPUNIT_ASSERT_EQUAL(1, tree.getActivePoint().activeLength);
}

void SuffixTreeTest::testBuildSuffixTree()
{
    vector<MatItem> vec;
    vec.push_back({97, false});
    vec.push_back({98, false});
    vec.push_back({97, false});
    vec.push_back({0, true});

    SuffixTree tree(vec);
    Node *node = tree.buildSuffixTree();

    MatItem a = {0, true};
    MatItem b = {97, false};
    MatItem c = {98, false};
    Node* firstBranch = node->children[a];
    Node* secondBranch = node->children[b];
    Node* thirdBranch = node->children[c];

    CPPUNIT_ASSERT_EQUAL(4, tree.getSize());
    CPPUNIT_ASSERT(node->children.size() == 3);

    CPPUNIT_ASSERT(firstBranch->children.empty());
    CPPUNIT_ASSERT_EQUAL(3, firstBranch->suffixIndex);

    CPPUNIT_ASSERT(secondBranch->children.size() == 2);
    CPPUNIT_ASSERT_EQUAL(-1, secondBranch->suffixIndex);
    CPPUNIT_ASSERT(secondBranch->children[a]->suffixIndex == 2);
    CPPUNIT_ASSERT(secondBranch->children[c]->suffixIndex == 0);
    CPPUNIT_ASSERT(tree.getEdgeLength(secondBranch->children[c]) == 3);
    CPPUNIT_ASSERT(tree.getEdgeLength(thirdBranch) == 3);
}
