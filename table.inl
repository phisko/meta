#pragma once

#include "table.hpp"

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
    	bool isEqual(const T & lhs, const T & rhs) noexcept {
    		return lhs == rhs;
    	}

    	template<>
    	inline bool isEqual(const char * const & lhs, const char * const & rhs) noexcept {
    		return strcmp(lhs, rhs) == 0;
    	}

    	template<size_t N, size_t N2>
    	inline bool isEqual(const char (&lhs)[N], const char (&rhs)[N2]) noexcept {
    		return strcmp(lhs, rhs) == 0;
    	}

		template<size_t N>
		inline bool isEqual(const char (&lhs)[N], const char * const & rhs) noexcept {
			return strcmp(lhs, rhs) == 0;
		}

		template<size_t N>
		inline bool isEqual(const char * const & lhs, const char (&rhs)[N]) noexcept {
			return strcmp(lhs, rhs) == 0;
		}

        template<bool ShouldAssert, std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func, std::size_t ...Is>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<Is...>) noexcept;

        template<bool ShouldAssert, std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<>) noexcept {
        	if constexpr (ShouldAssert)
				assert(!"Key not found");
        }

        template<bool ShouldAssert, std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func, std::size_t I, std::size_t ...Is>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<I, Is...>) noexcept {
            const auto & pair = std::get<I>(table);

			using KeyType = putils_typeof(std::get<KPos>(pair));
			if constexpr (std::is_same<KeyType, putils_typeof(key)>::value) {
				if (isEqual(std::get<KPos>(pair), key)) {
					func(std::get<VPos>(pair));
					return;
				}
			}

            get_value<ShouldAssert, KPos, VPos>(key, table, func, std::index_sequence<Is...>());
        }

        template<bool ShouldAssert, std::size_t KPos, std::size_t VPos, typename Key, typename Func, typename ...Pairs>
        constexpr void get_value(Key && key, const std::tuple<Pairs...> & table, Func && func) noexcept {
            get_value<ShouldAssert, KPos, VPos>(FWD(key), table, FWD(func), std::index_sequence_for<Pairs...>());
        }
    }
	
    template<typename Table, typename Key>
    constexpr bool has_key(Table && table, Key && key) noexcept {
    	bool ret = false;
	    try_get_value(FWD(table), FWD(key), [&](auto && value) {
		    ret = true;
	    });
    	return ret;
    }

	template<typename Table, typename Key, typename Func>
	constexpr void try_get_value(Table && table, Key && key, Func && func) noexcept {
		detail::get_value<false, detail::KeyPos, detail::ValuePos>(FWD(key), table, FWD(func));
	}

	template<typename Ret, typename Table, typename Key, typename FinalReturn>
	constexpr FinalReturn * try_get_value(Table && table, Key && key) noexcept {
		FinalReturn * ret = nullptr;
		try_get_value(FWD(table), FWD(key), [&](auto && value) noexcept {
			ret = &value;
		});
		return ret;
	}

    template<typename Table, typename Key, typename Func>
    constexpr void get_value(Table && table, Key && key, Func && func) noexcept {
        detail::get_value<true, detail::KeyPos, detail::ValuePos>(FWD(key), table, FWD(func));
    }
	
    template<typename Ret, typename Table, typename Key, typename FinalReturn>
    constexpr FinalReturn & get_value(Table && table, Key && key) noexcept {
        FinalReturn * ret = nullptr;
        get_value(FWD(table), FWD(key), [&](auto && value) noexcept {
            ret = &value;
        });
        return *ret;
    }

	template<typename Table, typename Value>
	constexpr bool has_value(Table && table, Value && value) noexcept {
		bool ret = false;
		try_get_key(FWD(table), FWD(value), [&](auto && key) {
			ret = true;
		});
		return ret;
	}

	template<typename Table, typename Value, typename Func>
	constexpr void try_get_key(Table && table, Value && value, Func && func) noexcept {
		detail::get_value<false, detail::ValuePos, detail::KeyPos>(FWD(value), table, FWD(func));
	}
   
	template<typename Ret, typename Table, typename Value, typename FinalReturn>
	constexpr FinalReturn * try_get_key(Table && table, Value && value) noexcept {
		FinalReturn * ret = nullptr;
		try_get_key(FWD(table), FWD(value), [&](auto && key) noexcept {
			ret = &key;
		});
		return ret;
	}

    template<typename Table, typename Value, typename Func>
    constexpr void get_key(Table && table, Value && value, Func && func) noexcept {
        detail::get_value<true, detail::ValuePos, detail::KeyPos>(FWD(value), table, FWD(func));
    }
   
    template<typename Ret, typename Table, typename Value, typename FinalReturn>
    constexpr FinalReturn & get_key(Table && table, Value && value) noexcept {
		FinalReturn * ret = nullptr;
		get_key(FWD(table), FWD(value), [&](auto && key) noexcept {
			ret = &key;
		});
		return *ret;
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

    template<typename ...Args>
    constexpr auto make_table(Args && ...args) noexcept {
        return detail::make_table(args...);
    }
}