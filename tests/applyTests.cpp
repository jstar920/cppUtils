#include "apply.hpp"
#include "assure.h"
using namespace cpputils;

namespace applyTest
{

    int TestFunc0()
    {
        return 1;
    }

    int TestFunc1(int a)
    {
        return 1;
    }

    int TestFunc2(int a, float b)
    {
        return 2;
    }

    int TestFunc3(int a, float b, double c)
    {
        return 2;
    }

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
        int operator()(int i) {static_cast<void>(i); return 1; };
    };

    class FunctionOp2
    {
    public:
        FunctionOp2() = default;
        int operator()(int i, float j) {static_cast<void>(i); static_cast<void>(j); return 2; };
    };

    class TestClass
    {
    public:
        int f(int, float) { return 0; }
        int changePara(int& a)
        {
            a = 10;
            return 0;
        }
    };

    int changePara(int& a)
    {
        a = 10;
        return 0;
    }

TEST_CASE("apply", "apply")
{
    ASSURE_EQ(apply(TestFunc0, std::tuple<>()), 1);
    ASSURE_EQ(apply(TestFunc1, std::make_tuple<int>(1)), 1);
    ASSURE_EQ(apply(TestFunc2, std::make_tuple<int, float>(1, 1.2f)), 2);
    ASSURE_EQ(apply(TestFunc3, std::make_tuple<int, float, double>(1, 1.2f, 1.2f)), 2);

    ASSURE_EQ(apply(FunctionOp0(), std::tuple<>()), 0);
    ASSURE_EQ(apply(FunctionOp1(), std::make_tuple<int>(1)), 1);
    ASSURE_EQ(apply(FunctionOp2(), std::make_tuple<int, float>(1, 1.2f)), 2);

    TestClass tc;
    int (TestClass::*pCF)(int i, float j) = &TestClass::f;
    ASSURE_EQ(apply(pCF, std::make_tuple(tc, 1, 1.2f)), 0);
    ASSURE_EQ(apply(pCF, std::make_tuple(&tc, 1, 1.2f)), 0);
    ASSURE_EQ(apply(&TestClass::f, std::make_tuple(tc, 1, 1.2f)), 0);
    ASSURE_EQ(apply(&TestClass::f, std::make_tuple(&tc, 1, 1.2f)), 0);

    auto lambdaF = [](int i, float j) {
        return 0;
    };

    ASSURE_EQ(apply(lambdaF, std::make_tuple(1, 1.2f)), 0);

    int a = 0;
    ASSURE_EQ(apply(changePara, std::tuple<int&>(a)), 0);
    ASSURE_EQ(a, 10);

    ASSURE_EQ(apply(&TestClass::changePara, std::make_tuple<TestClass&, int&>(tc, a)), 0);
    ASSURE_EQ(a, 10);

    ASSURE_EQ(apply(&TestClass::changePara, std::make_tuple<TestClass*, int&>(&tc, a)), 0);
    ASSURE_EQ(a, 10);

}

}