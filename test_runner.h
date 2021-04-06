//
// Created by Dima on 16/02/21.
//

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#ifndef CPPCOURSERA_TEST_RUNNER_H
#define CPPCOURSERA_TEST_RUNNER_H

#endif //CPPCOURSERA_TEST_RUNNER_H

// Interface

class TestRunner {
public:
    ~TestRunner();

    template <class Func>
    void TestFunc(Func f, const string& test_name);

private:
    int count_fail = 0;
};

template <class T, class V>
void AssertEqual(const T&t, const V& v, const string& hint);

template <class T, class V>
void AssertConstructorInvalidArgument(const V& v);

void Assert(const bool& to_check, const string& hint);

template <class T>
ostream& operator << (ostream& out, const vector<T>& v);

template <class T>
ostream& operator << (ostream& out, const set<T>& v);

template <class Key, class Value>
ostream& operator << (ostream& out, const map<Key, Value>& m);

// Implementation

template <class Func>
void TestRunner::TestFunc(Func f, const string& test_name) {
    try {
        f();
        cerr << "Test " << test_name << " passed" << endl;
    } catch (runtime_error& e) {
        ++count_fail;
        cerr << "Test " << test_name << " failed: " << e.what() << endl;
    }
}
template <class T, class V>
void AssertEqual(const T&t, const V& v, const string& hint) {
    if (t != v) {
        ostringstream ss;
        ss << "Assertion failed: " << t << " != " << v << " hint: " << hint;
        throw runtime_error(ss.str());
    }
}

template <class T, class V>
void AssertConstructorInvalidArgument(const V& v) {
    try {
        T t(v);
    } catch (invalid_argument& e) {
        return;
    }
    ostringstream ss;
    ss << "Assertion failed: constructor with input = " << v << " didn't throw invalid argument";
    throw runtime_error(ss.str());
}

template <class T>
ostream& operator << (ostream& out, const vector<T>& v) {
    ostringstream ss;
    ss << "[";
    bool first = true;
    for (const auto& x : v) {
        if (!first) {
            ss << " ";
        }
        first = false;
        ss << x;
    }
    ss << "]";
    out << ss.str();
    return out;
}

template <class T>
ostream& operator << (ostream& out, const set<T>& v) {
    ostringstream ss;
    ss << "(";
    bool first = true;
    for (const auto& x : v) {
        if (!first) {
            ss << " ";
        }
        first = false;
        ss << x;
    }
    ss << ")";
    out << ss.str();
    return out;
}

template <class Key, class Value>
ostream& operator << (ostream& out, const map<Key, Value>& m) {
    ostringstream ss;
    ss << "{";
    bool first = true;
    for (const auto& x : m) {
        if (!first) {
            ss << " ";
        }
        first = false;
        ss << x.first << "," << x.second;
    }
    ss << "}";
    out << ss.str();
    return out;
}

template <class Key, class Value>
ostream& operator << (ostream& out, const unordered_map<Key, Value>& m) {
    ostringstream ss;
    ss << "{";
    bool first = true;
    for (const auto& x : m) {
        if (!first) {
            ss << " ";
        }
        first = false;
        ss << x.first << "," << x.second;
    }
    ss << "}";
    out << ss.str();
    return out;
}

#define ASSERT_EQUAL(x, y) {        \
    ostringstream __assert_equal_private_os;                  \
    __assert_equal_private_os << #x << " != " << #y << ", "           \
    <<  __FILE__ << ":" << __LINE__; \
    AssertEqual(x, y, __assert_equal_private_os.str());       \
    }

#define ASSERT(x) {        \
    ostringstream __assert_private_os;                  \
    __assert_private_os << #x << " is false, "           \
    <<  __FILE__ << ":" << __LINE__; \
    Assert(x, __assert_private_os.str());       \
    }

#define TEST_FUNC(tr, func) \
tr.TestFunc(func, #func)
