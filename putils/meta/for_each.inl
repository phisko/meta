#include "for_each.hpp"

// stl
#include <optional>

// meta
#include "putils/meta/concepts/specialization.hpp"
#include "putils/meta/traits/function_return_type.hpp"

namespace putils {
	namespace detail {
		template<typename Tuple, typename F, typename Return = void>
		constexpr auto tuple_for_each(Tuple && tuple, F && f, std::index_sequence<>) noexcept {
			constexpr bool is_void = std::is_same<Return, void>();
			constexpr bool is_optional = putils::specialization<Return, std::optional>;
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

		template<typename Tuple, typename F, typename Return = void, size_t I, size_t... Is>
		constexpr auto tuple_for_each(Tuple && tuple, F && f, std::index_sequence<I, Is...>) noexcept {
			using ReturnType = decltype(f(std::get<I>(tuple)));

			constexpr bool is_void = std::is_same<ReturnType, void>();
			constexpr bool is_optional = putils::specialization<ReturnType, std::optional>;
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

			return detail::tuple_for_each<Tuple, F, ReturnType>(FWD(tuple), FWD(f), std::index_sequence<Is...>());
		}
	}

	template<typename... Args, typename F>
	constexpr auto tuple_for_each(std::tuple<Args...> & tuple, F && f) noexcept {
		return detail::tuple_for_each(tuple, FWD(f), std::index_sequence_for<Args...>());
	}

	template<typename... Args, typename F>
	constexpr auto tuple_for_each(const std::tuple<Args...> & tuple, F && f) noexcept {
		return detail::tuple_for_each(tuple, FWD(f), std::index_sequence_for<Args...>());
	}

	template<typename... Types, typename Func>
	constexpr auto for_each_type(Func && f) noexcept {
		return tuple_for_each(std::tuple<putils::meta::type<Types>...>(), FWD(f));
	}
}