#pragma once

// meta
#include "type.hpp"
#include "fwd.hpp"

namespace putils {
	// For each `e` element in `tuple`, call `f(e)`
	// For instance:
	// ```
	//      std::tuple<int, std::string, int> t(42, "test", 1);
	//      putils::tuple_for_each(t, [](auto &attr) {
	//			std::cout << attr << std::endl;
	//		});
	// ```
	// Will print
	//      42
	//      test
	//      1
	//
	// `f` may return:
	//      - void: will be called for each element
	//      - bool: will stop iterating when `f` returns true. Returns the result
	//      - std::optional: will stop iterating when `f` returns a valid optional. Returns the result

	template<typename F, typename... Args>
	constexpr auto tuple_for_each(std::tuple<Args...> & tuple, F && f) noexcept;

	template<typename F, typename... Args>
	constexpr auto tuple_for_each(const std::tuple<Args...> & tuple, F && f) noexcept;

	// For each `T` in `Types` call `f(putils::meta::type<T>)`
	// `T` can then be recovered by using putils_wrapped_type
	// For instance:
	// ```
	//		putils::for_each_type<int, double>([](auto && t) {
	//			using T = putils_wrapped_type(t);
	//			std::cout << typeid(T).name() << std::endl;
	//		});
	// ```
	// Will print something similar to:
	//		int
	//		double
	//
	// Same behavior as `tuple_for_each`

	template<typename... Types, typename Func>
	constexpr auto for_each_type(Func && f) noexcept;
}

#include "for_each.inl"