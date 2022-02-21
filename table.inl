#pragma once

#include "table.hpp"
#include "fwd.hpp"
#include "type.hpp"

namespace putils {
    /*
     * Implementation details
     */

    namespace detail {
        enum Indexes {
            KeyPos = 0,
            ValuePos = 1
        };
    }
    
    /*
     * get_value implementation
     */

    namespace detail {
    	template<typename T>
    	constexpr bool isEqual(const T & lhs, const T & rhs) noexcept {
    		return lhs == rhs;
    	}

        inline constexpr bool isEqualStrings(std::string_view lhs, std::string_view rhs) noexcept {
            return lhs == rhs;
        }

    	template<>
    	inline constexpr bool isEqual(const char * const & lhs, const char * const & rhs) noexcept {
            return isEqualStrings(lhs, rhs);
    	}

    	template<size_t N, size_t N2>
    	inline constexpr bool isEqual(const char (&lhs)[N], const char (&rhs)[N2]) noexcept {
            return isEqualStrings(lhs, rhs);
    	}

		template<size_t N>
		inline constexpr bool isEqual(const char (&lhs)[N], const char * const & rhs) noexcept {
            return isEqualStrings(lhs, rhs);
		}

		template<size_t N>
		inline constexpr bool isEqual(const char * const & lhs, const char (&rhs)[N]) noexcept {
            return isEqualStrings(lhs, rhs);
		}

        template<std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func, std::size_t ...Is>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<Is...>) noexcept;

        template<std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<>) noexcept {}

        template<std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func, std::size_t I, std::size_t ...Is>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<I, Is...>) noexcept {
            auto && pair = std::get<I>(table);

			using KeyType = putils_typeof(std::get<KPos>(pair));
			if constexpr (std::is_same<KeyType, putils_typeof(key)>::value) {
				if (isEqual(std::get<KPos>(pair), key)) {
                    auto && value = std::get<VPos>(pair);
					func(FWD(value));
					return;
				}
			}

            get_value<KPos, VPos>(FWD(key), FWD(table), FWD(func), std::index_sequence<Is...>());
        }

        template<std::size_t KPos, std::size_t VPos, typename Key, typename Func, typename ...Pairs>
        constexpr void get_value(Key && key, const std::tuple<Pairs...> & table, Func && func) noexcept {
            get_value<KPos, VPos>(FWD(key), table, FWD(func), std::index_sequence_for<Pairs...>());
        }

        template<std::size_t KPos, std::size_t VPos, typename Key, typename Func, typename ...Pairs>
        constexpr void get_value(Key && key, std::tuple<Pairs...> & table, Func && func) noexcept {
            get_value<KPos, VPos>(FWD(key), table, FWD(func), std::index_sequence_for<Pairs...>());
        }
    }
	
	template<typename Table, typename Key, typename Func>
	constexpr void get_value(Table && table, Key && key, Func && func) noexcept {
		detail::get_value<detail::KeyPos, detail::ValuePos>(FWD(key), FWD(table), FWD(func));
	}

	template<typename Ret, typename Table, typename Key, typename FinalReturn>
	constexpr FinalReturn * get_value(Table && table, Key && key) noexcept {
		FinalReturn * ret = nullptr;
		get_value(FWD(table), FWD(key), [&](auto && value) noexcept {
            if constexpr (std::is_same_v<decltype(ret), decltype(&value)> || std::is_assignable_v<decltype(ret), decltype(&value)>)
                ret = &value;
		});
		return ret;
	}

	template<typename Table, typename Value, typename Func>
	constexpr void get_key(Table && table, Value && value, Func && func) noexcept {
		detail::get_value<detail::ValuePos, detail::KeyPos>(FWD(value), FWD(table), FWD(func));
	}
   
	template<typename Ret, typename Table, typename Value, typename FinalReturn>
	constexpr FinalReturn * get_key(Table && table, Value && value) noexcept {
		FinalReturn * ret = nullptr;
		get_key(FWD(table), FWD(value), [&](auto && key) noexcept {
            if constexpr (std::is_same_v<decltype(ret), decltype(&key)> || std::is_assignable_v<decltype(ret), decltype(&key)>)
                ret = &key;
		});
		return ret;
	}

    /*
     * make_table implementation
     */

    namespace detail {
        inline constexpr auto make_table() noexcept { return std::make_tuple(); }

		template<typename Key, typename Value, typename ...Args>
		constexpr auto make_table(Key && key, Value && type, Args && ...args) noexcept {
			return std::tuple_cat(
				std::make_tuple(
					std::make_pair(FWD(key), FWD(type))
				),
				detail::make_table(FWD(args)...)
			);
		}
	}

    template<typename ... KeyValues>
    constexpr auto make_table(KeyValues && ... keyValues) noexcept {
        return detail::make_table(FWD(keyValues)...);
    }
}