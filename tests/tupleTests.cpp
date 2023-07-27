#include "tuple.hpp"
#include "assure.h"

using namespace cpputils;

namespace tupleTests
{
    TEST_CASE("tuple", "tuple")
    {
        auto tp = std::make_tuple(1, "1", 2, "2", 3, "3");

        {
            auto subTp = sub_tuple<2, 3>(tp);
            ASSURE_EQ(std::tuple_size<decltype(subTp)>{}, 2);
            ASSURE_EQ(std::get<0>(subTp), 2);
            ASSURE_EQ(std::get<1>(subTp), std::string("2"));
        }

        {
            auto subTp = sub_tuple<2, 2>(tp);
            ASSURE_EQ(std::tuple_size<decltype(subTp)>{}, 1);
            ASSURE_EQ(std::get<0>(subTp), 2);
        }

        {
            auto subTp = sub_tuple<0, 5>(tp);
            ASSURE_EQ(std::tuple_size<decltype(subTp)>{}, 6);
            ASSURE_EQ(std::get<0>(subTp), 1);
            ASSURE_EQ(std::get<1>(subTp), std::string("1"));
            ASSURE_EQ(std::get<2>(subTp), 2);
            ASSURE_EQ(std::get<3>(subTp), std::string("2"));
            ASSURE_EQ(std::get<4>(subTp), 3);
            ASSURE_EQ(std::get<5>(subTp), std::string("3"));
            //static_assert(decltype(std::get<0>(subTp)), decltype(std::get<0>(tp)), "Type different");
        }

        {
            int a = 0;
            int& lra = a;
            int&& rra = std::move(a);
            const int b = 0;
            const int& lrb = b;
            const int&& rrb = std::move(b);
            auto fwdTp = std::forward_as_tuple(a, lra, rra, b, lrb, rrb);
            static_assert(std::is_same_v<decltype(std::get<0>(fwdTp)), int&>, "different type");
            static_assert(std::is_same_v<decltype(std::get<1>(fwdTp)), int&>, "different type");
            static_assert(std::is_same_v<decltype(std::get<2>(fwdTp)), int&>, "different type");
            static_assert(std::is_same_v<decltype(std::get<3>(fwdTp)), const int&>, "different type");
            static_assert(std::is_same_v<decltype(std::get<4>(fwdTp)), const int&>, "different type");
            static_assert(std::is_same_v<decltype(std::get<5>(fwdTp)), const int&>, "different type");
        }
    }
}