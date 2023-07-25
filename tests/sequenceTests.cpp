#include "sequence.hpp"
#include "assure.h"

using namespace cpputils;

namespace sequenceTests
{
    TEST_CASE("sequence", "sequence")
    {
        {
            auto indice = make_index_sequence<2, 5>();
            static_assert(std::is_same_v<decltype(indice), std::index_sequence<2,3,4,5>>, "");
        }

        {
            auto indice = make_index_sequence<2, 2>();
            static_assert(std::is_same_v<decltype(indice), std::index_sequence<2>>, "");
        }
    }
}