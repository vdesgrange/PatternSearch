#ifndef MatriceTest_hpp
#define MatriceTest_hpp

#include <string>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../SuffixTree.hpp"
#include "../Matrice.hpp"

using namespace std;

class MatriceTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( MatriceTest );
    CPPUNIT_TEST( buildMatriceTest );
    CPPUNIT_TEST_SUITE_END();

    public:
        void buildMatriceTest();
};

#endif
