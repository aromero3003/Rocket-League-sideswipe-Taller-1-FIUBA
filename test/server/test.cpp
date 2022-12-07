/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_MyTestSuite_init = false;
#include "footest.h"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "footest.h", 3, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_suite_MyTestSuite_testFoo : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_testFoo() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 5, "testFoo" ) {}
 void runTest() { suite_MyTestSuite.testFoo(); }
} testDescription_suite_MyTestSuite_testFoo;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
