#pragma once

// stl
#include <memory>

// meta
#include "fwd.hpp"

namespace putils {
	namespace detail {
		template<class T, class Tuple, std::size_t... I>
		std::unique_ptr<T> new_from_tuple_impl(Tuple && t, std::index_sequence<I...>) noexcept {
			return std::make_unique<T>(std::get<I>(FWD(t))...);
		}
	}

	template<class T, class Tuple>
	std::unique_ptr<T> new_from_tuple(Tuple && t) noexcept {
		return detail::new_from_tuple_impl<T>(
			FWD(t),
			std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple>>>{}
		);
	}
}