#include "invocable.hpp"
#include "assure.h"
#include <thread>

using namespace cpputils;
TEST_CASE("invocable", "invocable")
{
    auto f1 = [](){};
    bool ok = is_invocable<std::decltype(f1)>::value;
    ASSURE_TRUE(ok);
}
