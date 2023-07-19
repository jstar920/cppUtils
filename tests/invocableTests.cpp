#include "invocable.hpp"
#include "assure.h"
#include <thread>

using namespace cpputils;

void testFun0() {}
void testFun1(int i) { static_cast<void>(i);}
void testFun2(int i, float j) { static_cast<void>(i); static_cast<void>(j);}

class FunctionOp0
{
public:
    FunctionOp0() = default;
    void operator()() {};
};

class FunctionOp1
{
public:
    FunctionOp1() = default;
    void operator()(int i) {static_cast<void>(i);};
};

class FunctionOp2
{
public:
    FunctionOp2() = default;
    void operator()(int i, float j) {static_cast<void>(i); static_cast<void>(j);};
};

class TestClass
{
public:
    void f(int, float) {}
};

TEST_CASE("invocable no return value", "invocable")
{
    auto f0 = [](){};
    ASSURE_TRUE(is_invocable<decltype(std::function<void()>(f0))>::value);
    ASSURE_TRUE(is_invocable<decltype(f0)>::value);

    auto f1 = [](int i){static_cast<void>(i);};
    ASSURE_TRUE((is_invocable<decltype(f1), int>::value));
    ASSURE_TRUE((is_invocable<decltype(testFun0)>::value));
    ASSURE_TRUE((is_invocable<decltype(testFun1), int>::value));
    ASSURE_TRUE((is_invocable<decltype(testFun2), int, float>::value));
    ASSURE_TRUE((is_invocable<FunctionOp0>::value));
    ASSURE_TRUE((is_invocable<FunctionOp1, int>::value));
    ASSURE_TRUE((is_invocable<FunctionOp2, int, float>::value));

    void (*pf)(int i, float j);
    ASSURE_TRUE((is_invocable<decltype(pf), int, float>::value));

    TestClass tc;
    void (TestClass::*pCF)(int i, float j);
    ASSURE_TRUE((is_invocable<decltype(pCF), TestClass&, int, float>::value));
    ASSURE_TRUE((is_invocable<decltype(&TestClass::f), TestClass&, int, float>::value));
    ASSURE_TRUE((is_invocable<decltype(&tc.f), TestClass*, int, float>::value));

}
