#ifndef SearchUnorderedTest_hpp
#define SearchUnorderedTest_hpp

#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../Matrice.hpp"
#include "../Search.hpp"
#include "../SearchUnordered.hpp"

using namespace std;

class SearchUnorderedTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( SearchUnorderedTest );
    CPPUNIT_TEST( testDoSearch );
    CPPUNIT_TEST( testSearchOperation );
    CPPUNIT_TEST( testStringifyResult );
    CPPUNIT_TEST_SUITE_END();

    public:
        void testDoSearch();
        void testSearchOperation();
        void testStringifyResult();
};

#endif
