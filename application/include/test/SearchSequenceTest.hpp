#ifndef SearchSequenceTest_hpp
#define SearchSequenceTest_hpp

#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../Matrice.hpp"
#include "../Search.hpp"
#include "../SearchSequence.hpp"

using namespace std;

class SearchSequenceTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( SearchSequenceTest );
    CPPUNIT_TEST( testDoSearch );
    CPPUNIT_TEST( testSearchOperation );
    CPPUNIT_TEST( testStringifyResult );
    CPPUNIT_TEST( testMatriceTraversal );
    CPPUNIT_TEST( testTraverseEdge );
    CPPUNIT_TEST( testDoTraversalToCountLeaf );
    CPPUNIT_TEST_SUITE_END();

    public:
        void testDoSearch();
        void testSearchOperation();
        void testStringifyResult();
        void testMatriceTraversal();
        void testTraverseEdge();
        void testDoTraversalToCountLeaf();
};

#endif
