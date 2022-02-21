#pragma once

#include <type_traits>

namespace putils {
    namespace detail {
        template<typename F, class Tuple, std::size_t ...Is>
        decltype(auto) apply(F && f, Tuple && tuple, std::index_sequence<Is...>) noexcept {
            return f(std::get<Is>(tuple)...);
        }
    }

    template<typename F, typename ...Args>
    decltype(auto) apply(const std::tuple<Args...> & tuple, F && f) noexcept {
        return detail::apply(std::forward<F>(f), tuple, std::index_sequence_for<Args...>());
    }

    template<typename F, typename ...Args>
    decltype(auto) apply(std::tuple<Args...> & tuple, F && f) noexcept {
        return detail::apply(std::forward<F>(f), tuple, std::index_sequence_for<Args...>());
    }
}
