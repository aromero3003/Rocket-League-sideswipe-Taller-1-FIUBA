#ifndef __TESTSNAP_H__
#define __TESTSNAP_H__

#include <cxxtest/TestSuite.h>
#include "../Snap.h"


class TestSnap: public CxxTest::TestSuite {
public:
    void testCreate() {

    }

    void testAlgo() {

        TS_ASSERT_EQUALS(2, 2);
    }
};

#endif