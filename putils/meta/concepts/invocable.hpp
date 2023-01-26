#pragma once

// stl
#include <concepts>

// meta
#include "putils/meta/traits/function_arguments.hpp"
#include "putils/meta/traits/function_return_type.hpp"

namespace putils {
	template<typename T, typename Signature>
	concept invocable = requires(T && func, putils::function_arguments<Signature> && args) {
		{ std::apply(std::move(func), std::move(args)) } -> std::convertible_to<putils::function_return_type<Signature>>;
	};
}