#pragma once

#include <tuple>

namespace putils {
    template<typename ... KeyValues>
    using table = std::tuple<KeyValues...>;

    template<typename ...KeyValues>
    constexpr auto make_table(KeyValues && ... keyValues) noexcept;

    // Index with key
    template<typename Table, typename Key>
    constexpr bool has_value(Table && table, Key && value) noexcept;
    template<typename Ret, typename Table, typename Key, typename FinalReturn = std::conditional_t<std::is_const_v<std::remove_reference_t<Table>>, const Ret, Ret>>
    constexpr FinalReturn * get_value(Table && table, Key && key) noexcept;
    template<typename Table, typename Key, typename Func>
    constexpr void get_value(Table && table, Key && key, Func && func) noexcept;

    // Index with value
    template<typename Table, typename Key>
    constexpr bool has_key(Table && table, Key && key) noexcept;
    template<typename Ret, typename Table, typename Value, typename FinalReturn = std::conditional_t<std::is_const_v<std::remove_reference_t<Table>>, const Ret, Ret>>
    constexpr FinalReturn * get_key(Table && table, Value && value) noexcept;
    template<typename Table, typename Value, typename Func>
    constexpr void get_key(Table && table, Value && value, Func && func) noexcept;
}

#include "table.inl"