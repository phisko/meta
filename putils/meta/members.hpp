#pragma once

// stl
#include <type_traits>

// Use this when member_type alias doesn't work
#define PUTILS_MEMBER_TYPE(T, member_ptr) std::remove_reference_t<decltype(std::declval<T>().*(std::declval<member_ptr>()))>

namespace putils {
	namespace detail {
		template<typename MemberPtr>
		struct member_type_wrapper;

		template<typename T, typename Member>
		struct member_type_wrapper<Member T:: *> {
			using type = Member;
		};
	}

	template<typename MemberPtr>
	using member_type = typename detail::member_type_wrapper<std::decay_t<MemberPtr>>::type;

	namespace detail {
		template<typename MemberPtr>
		struct object_type_wrapper;

		template<typename T, typename Member>
		struct object_type_wrapper<Member T:: *> {
			using type = T;
		};
	}

	template<typename MemberPtr>
	using object_type = typename detail::object_type_wrapper<std::decay_t<MemberPtr>>::type;

	template<typename T, typename U>
	constexpr std::ptrdiff_t member_offset(U T::* member) noexcept {
		return (ptrdiff_t)&(reinterpret_cast<T const volatile*>(NULL)->*member);
	}
}