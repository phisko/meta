#pragma once

// stl
#include <type_traits>

#define putils_member_detector(member)\
	template<typename T, typename = std::void_t<>>\
	struct has_member_##member : std::false_type {};\
\
	template<typename T>\
	struct has_member_##member<T, std::void_t<decltype((void)&T::member)>> : std::true_type {};
