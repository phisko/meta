#pragma once

#include <type_traits>

#define putils_nested_type_detector(member)\
	template<typename T, typename = std::void_t<>>\
	struct has_nested_type_##member : std::false_type {};\
\
	template<typename T>\
	struct has_nested_type_##member<T, std::void_t<typename T::member>> : std::true_type {};
