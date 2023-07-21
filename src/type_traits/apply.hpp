#pragma once
#include <type_traits>

namespace cpputils
{
    template<class F, class Tuple, std::size_t... I>
    constexpr decltype(auto) apply_imp(F&& f, Tuple&& t, std::index_sequence<I...>)
    {
        return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
    }

    template<class F, class Tuple>
    constexpr decltype(auto) apply(F&& f, Tuple&& t)
    {
        return apply_imp(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size<Tuple>::value>());
    }
}