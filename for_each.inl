#include "for_each.hpp"

#include <optional>

#include "traits/function_return_type.hpp"
#include "traits/is_specialization.hpp"

namespace putils {
    namespace detail {
        template<typename F, typename Tuple, typename Return = void>
        constexpr auto tuple_for_each(F && f, Tuple && tuple, std::index_sequence<>) noexcept {
            constexpr bool isVoid = std::is_same<Return, void>();
            constexpr bool isOptional = putils::is_specialization<Return, std::optional>();
            constexpr bool isBool = std::is_same<Return, bool>();

            static_assert(isVoid || isOptional || isBool);

            if constexpr (isVoid) {
                return nullptr;
            }
            if constexpr (isOptional) {
                return Return{};
            }
            else if constexpr (isBool) {
                return false;
            }
        }

        template<typename F, typename Tuple, typename Return = void, size_t I, size_t ... Is>
        constexpr auto tuple_for_each(F && f, Tuple && tuple, std::index_sequence<I, Is...>) noexcept {
            using ReturnType = decltype(f(std::get<I>(tuple)));

            constexpr bool isVoid = std::is_same<ReturnType, void>();
            constexpr bool isOptional = putils::is_specialization<ReturnType, std::optional>();
            constexpr bool isBool = std::is_same<ReturnType, bool>();

            static_assert(isVoid || isOptional || isBool, "tuple_for_each callback should return void, std::optional or bool");

            if constexpr (isVoid) {
                f(std::get<I>(tuple));
            }
            else if constexpr (isOptional || isBool) {
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