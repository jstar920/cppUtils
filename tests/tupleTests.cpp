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
        }
    }
}