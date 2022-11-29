#include "table.hpp"

// meta
#include "fwd.hpp"
#include "type.hpp"

namespace putils {
    /*
     * Implementation details
     */

    namespace detail {
        enum indices {
            key_pos = 0,
            value_pos = 1
        };
    }
    
    /*
     * get_value implementation
     */

    namespace detail {
    	template<typename T>
    	constexpr bool is_equal(const T & lhs, const T & rhs) noexcept {
    		return lhs == rhs;
    	}

        inline constexpr bool is_equal_strings(std::string_view lhs, std::string_view rhs) noexcept {
            return lhs == rhs;
        }

    	template<>
    	inline constexpr bool is_equal(const char * const & lhs, const char * const & rhs) noexcept {
            return is_equal_strings(lhs, rhs);
    	}

    	template<size_t N, size_t N2>
    	inline constexpr bool is_equal(const char (&lhs)[N], const char (&rhs)[N2]) noexcept {
            return is_equal_strings(lhs, rhs);
    	}

		template<size_t N>
		inline constexpr bool is_equal(const char (&lhs)[N], const char * const & rhs) noexcept {
            return is_equal_strings(lhs, rhs);
		}

		template<size_t N>
		inline constexpr bool is_equal(const char * const & lhs, const char (&rhs)[N]) noexcept {
            return is_equal_strings(lhs, rhs);
		}

        template<std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func, std::size_t ...Is>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<Is...>) noexcept;

        template<std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<>) noexcept {}

        template<std::size_t KPos, std::size_t VPos, typename Key, typename Table, typename Func, std::size_t I, std::size_t ...Is>
        constexpr void get_value(Key && key, Table && table, Func && func, std::index_sequence<I, Is...>) noexcept {
            auto && pair = std::get<I>(table);

			using key_type = putils_typeof(std::get<KPos>(pair));
			if constexpr (std::is_same<key_type, putils_typeof(key)>::value) {
				if (is_equal(std::get<KPos>(pair), key)) {
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
		detail::get_value<detail::key_pos, detail::value_pos>(FWD(key), FWD(table), FWD(func));
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

    template<typename Table, typename Key>
    constexpr bool has_value(Table && table, Key && value) noexcept {
        bool ret = false;
        get_key(FWD(table), FWD(value), [&](auto &&) noexcept {
            ret = true;
        });
        return ret;
    }

	template<typename Table, typename Value, typename Func>
	constexpr void get_key(Table && table, Value && value, Func && func) noexcept {
		detail::get_value<detail::value_pos, detail::key_pos>(FWD(value), FWD(table), FWD(func));
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

    template<typename Table, typename Key>
    constexpr bool has_key(Table && table, Key && key) noexcept {
        bool ret = false;
        get_value(FWD(table), FWD(key), [&](auto &&) noexcept {
            ret = true;
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
    constexpr auto make_table(KeyValues && ... key_values) noexcept {
        return detail::make_table(FWD(key_values)...);
    }
}