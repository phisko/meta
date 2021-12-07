#pragma once

#include <type_traits>

namespace putils {
   	namespace detail {
   		template<typename S, typename T>
   		class is_unstreamable {
   			template<typename SS, typename TT>
   			static auto test(int)
   				-> decltype(std::declval<SS &>() >> std::declval<TT &>(), std::true_type());
   
   			template<typename, typename>
   			static auto test(...)->std::false_type;
   
   		public:
   			using type = decltype(test<S, T>(0));
   		};
   	}
   
   	template<typename S, typename T>
   	using is_unstreamable = typename detail::is_unstreamable<S, T>::type;
}