#pragma once
#include "sequence.hpp"
#include <tuple>

namespace cpputils
{
    template <size_t...Indice, typename...Args>
    constexpr auto sub_tuple_imp(std::index_sequence<Indice...> indice, std::tuple<Args...> tp)
    {
        return std::forward_as_tuple(std::forward<decltype(std::get<Indice>(tp))>(std::get<Indice>(tp))...);
    }

    template<size_t N, size_t M, typename...Args>
    constexpr auto sub_tuple(std::tuple<Args...> tp)
    {
        static_assert(N <= M, "sub tuple index N must <= M");
        static_assert(M <= std::tuple_size<std::tuple<Args...>>{}, "sub tuple index M must <= tuple size");
        auto indice = make_index_sequence<N, M>();
        return sub_tuple_imp(indice, tp);
    }
}