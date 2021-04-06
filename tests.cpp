//
// Created by Dima on 18/02/21.
//
#include "tests.h"
#include "test_runner.h"

#include "expression_parser.h"

using namespace std;

void TestParser () {
    {
        expression_parser ep1 ("1 + 1");
        ASSERT_EQUAL(ep1.calc(10), 2);
        expression_parser ep2 ("1 + 2*4 + 1*2 - 2*2");
        ASSERT_EQUAL(ep2.calc(17), 7);
        expression_parser ep3 ("x * 1");
        ASSERT_EQUAL(ep3.calc(10), 10);
        expression_parser ep4 ("2 - 2- 2");
        ASSERT_EQUAL(ep4.calc(1234), -2);
        expression_parser ep5 ("x*x+2*2-2-2*x");
        ASSERT_EQUAL(ep5.calc(10), 82);
    }
    {
        expression_parser ep ("x*x + 2*2 - 2 - 2*x +1 + x*1");
        ASSERT_EQUAL(ep.calc(0), 3);
        ASSERT_EQUAL(ep.calc(1), 3);
        ASSERT_EQUAL(ep.calc(-1), 5);
        ASSERT_EQUAL(ep.calc(2), 5);
    }
    {
        expression_parser ep ("x + x*x*x - x*2*x + 17");
        ASSERT_EQUAL(ep.calc(2), 19);
    }
};


void TestAll() {
    TestRunner tr;
    TEST_FUNC(tr, TestParser);
}