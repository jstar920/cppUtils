#include "invocable.hpp"
#include "assure.h"

using namespace cpputils;

namespace invocableTests
{

namespace withoutR
{
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

}

TEST_CASE("invocable no return value", "invocable")
{
    using namespace withoutR;
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
    ASSURE_TRUE((is_invocable<decltype(&tc.f), int, float>::value));

}

namespace withR
{
    int testFun0() { return 0; }
    int testFun1(int i) { static_cast<void>(i); return 0; }
    int testFun2(int i, float j) { static_cast<void>(i); static_cast<void>(j); return 0;}

    class FunctionOp0
    {
    public:
        FunctionOp0() = default;
        int operator()() { return 0; };
    };

    class FunctionOp1
    {
    public:
        FunctionOp1() = default;
        int operator()(int i) {static_cast<void>(i); return 0; };
    };

    class FunctionOp2
    {
    public:
        FunctionOp2() = default;
        int operator()(int i, float j) {static_cast<void>(i); static_cast<void>(j); return 0; };
    };

    class TestClass
    {
    public:
        int f(int, float) { return 0; }
    };

}
TEST_CASE("invocable return value", "invocable")
{
    using namespace withR;
    auto f0 = []() -> int { return 0; };
    ASSURE_TRUE((is_invocable_r<decltype(std::function<int()>(f0)), int>::value));
    ASSURE_TRUE((is_invocable_r<decltype(f0), int>::value));

    auto f1 = [](int i) -> int {static_cast<void>(i); return 0; };
    ASSURE_TRUE((is_invocable_r<decltype(f1), int, int>::value));
    ASSURE_TRUE((is_invocable_r<decltype(testFun0), int>::value));
    ASSURE_TRUE((is_invocable_r<decltype(testFun1), int, int>::value));
    ASSURE_TRUE((is_invocable_r<decltype(testFun2), int, int, float>::value));
    ASSURE_TRUE((is_invocable_r<FunctionOp0, int>::value));
    ASSURE_TRUE((is_invocable_r<FunctionOp1, int, int>::value));
    ASSURE_TRUE((is_invocable_r<FunctionOp2, int, int, float>::value));

    int (*pf)(int i, float j);
    ASSURE_TRUE((is_invocable_r<decltype(pf), int, int, float>::value));

    TestClass tc;
    int (TestClass::*pCF)(int i, float j);
    ASSURE_TRUE((is_invocable_r<decltype(pCF), int, TestClass&, int, float>::value));
    ASSURE_TRUE((is_invocable_r<decltype(&TestClass::f), int, TestClass&, int, float>::value));
    ASSURE_TRUE((is_invocable_r<decltype(&tc.f), int, int, float>::value));

}

}
