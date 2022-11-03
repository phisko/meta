#pragma once

// stl
#include <type_traits>

namespace putils {
   	namespace detail {
   		template<typename T>
   		class is_indexable {
   			template<typename TT>
   			static auto test(int)
   				-> decltype(std::declval<TT>()[(size_t)0], std::true_type());
   
   			template<typename>
   			static auto test(...) -> std::false_type;
   
   		public:
   			using type = decltype(test<T>(0));
   		};
   	}
   
   	template<typename T>
   	using is_indexable = detail::is_indexable<T>::type;
}