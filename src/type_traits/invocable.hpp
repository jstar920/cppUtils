#pragma once
#include <type_traits>
#include <functional>

namespace cpputils
{
    template<typename F, typename... Args>
    struct is_invocable :  std::is_constructible<std::function<void(Args...)>, F>
    {};

    template<typename F, typename R, typename... Args>
    struct is_invocable_r :  std::is_constructible<std::function<R(Args...)>, F>
    {};
}