#ifndef SuffixTreeTest_hpp
#define SuffixTreeTest_hpp

#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../SuffixTree.hpp"

using namespace std;

class SuffixTreeTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( SuffixTreeTest );
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testBuildSuffixTree );
    CPPUNIT_TEST( testCreateNewNode );
    CPPUNIT_TEST( testWalkDown );
    CPPUNIT_TEST_SUITE_END();

    public:
        void testConstructor();
        void testBuildSuffixTree();
        void testCreateNewNode();
        void testWalkDown();
        void testGetEdgeLength();
};

#endif
