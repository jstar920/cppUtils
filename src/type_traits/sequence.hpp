#pragma once
#include <type_traits>
#include <utility>

namespace cpputils
{
    template <size_t N, size_t...Indice>
    constexpr auto make_index_sequence_imp(std::index_sequence<Indice...> indexSeq)
    {
        return std::index_sequence<(Indice + N)...>();
    }

    template<size_t N, size_t M>
    constexpr auto make_index_sequence()
    {
        static_assert(M >= N, "make_index_sequence template parameter error: M shoud >= N");
        constexpr size_t Count = M - N + 1;
        constexpr auto indice = std::make_index_sequence<Count>();
        return make_index_sequence_imp<N>(indice);
    }
}