#pragma once
#include <type_traits>
#include <functional>

namespace cpputils
{
    template<typename F, typename... Args>
    //struct is_invocable :  std::is_constructible<std::function<void(Args...)>, std::reference_wrapper<typename std::remove_reference<F>::type >>
    struct is_invocable :  std::is_constructible<std::function<void(Args...)>, F>
    {};
}