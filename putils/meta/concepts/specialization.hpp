#pragma once

// stl
#include <type_traits>

namespace putils {
	template<typename T, template<typename...> class Template>
	struct is_specialization : std::false_type {};

	template<template<typename...> class Template, typename... Args>
	struct is_specialization<Template<Args...>, Template> : std::true_type {};

	template<typename T, template<typename...> class Template>
	concept specialization = is_specialization<T, Template>::value;
}