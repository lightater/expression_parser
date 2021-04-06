//
// Created by Dima on 18/02/21.
//

#include "test_runner.h"

void Assert(const bool& to_check, const string& hint) {
    AssertEqual(to_check, true, hint);
}

TestRunner::~TestRunner() {
    if (count_fail > 0) {
        throw runtime_error("tests failed. Terminate");
    }
}

