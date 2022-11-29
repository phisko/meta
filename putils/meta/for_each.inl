#include "for_each.hpp"

// stl
#include <optional>

// meta
#include "putils/meta/traits/function_return_type.hpp"
#include "putils/meta/traits/is_specialization.hpp"

namespace putils {
    namespace detail {
        template<typename F, typename Tuple, typename Return = void>
        constexpr auto tuple_for_each(F && f, Tuple && tuple, std::index_sequence<>) noexcept {
            constexpr bool is_void = std::is_same<Return, void>();
            constexpr bool is_optional = putils::is_specialization<Return, std::optional>();
            constexpr bool is_bool = std::is_same<Return, bool>();

            static_assert(is_void || is_optional || is_bool);

            if constexpr (is_void) {
                return false;
            }
            if constexpr (is_optional) {
                return Return{};
            }
            else if constexpr (is_bool) {
                return false;
            }
        }

        template<typename F, typename Tuple, typename Return = void, size_t I, size_t ... Is>
        constexpr auto tuple_for_each(F && f, Tuple && tuple, std::index_sequence<I, Is...>) noexcept {
            using ReturnType = decltype(f(std::get<I>(tuple)));

            constexpr bool is_void = std::is_same<ReturnType, void>();
            constexpr bool is_optional = putils::is_specialization<ReturnType, std::optional>();
            constexpr bool is_bool = std::is_same<ReturnType, bool>();

            static_assert(is_void || is_optional || is_bool, "tuple_for_each callback should return void, std::optional or bool");

            if constexpr (is_void) {
                f(std::get<I>(tuple));
            }
            else if constexpr (is_optional || is_bool) {
                const auto ret = f(std::get<I>(tuple));
                if (ret)
                    return ret;
            }

            return detail::tuple_for_each<F, Tuple, ReturnType>(FWD(f), FWD(tuple), std::index_sequence<Is...>());
        }
    }

    template<typename F, typename ... Args>
    constexpr auto tuple_for_each(std::tuple<Args...> & tuple, F && f) noexcept {
        return detail::tuple_for_each(std::forward<F>(f), tuple, std::index_sequence_for<Args...>());
    }

    template<typename F, typename ... Args>
    constexpr auto tuple_for_each(const std::tuple<Args...> & tuple, F && f) noexcept {
        return detail::tuple_for_each(std::forward<F>(f), tuple, std::index_sequence_for<Args...>());
    }

    template<typename ... Types, typename Func>
    constexpr auto for_each_type(Func && f) noexcept {
        return tuple_for_each(std::tuple<putils::meta::type<Types>...>(), FWD(f));
    }
}