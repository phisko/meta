# [table](table.hpp)

A constexpr, type-safe association table that maps any key of any type to any value of any type.

For usage examples, see the [unit tests](tests/table.tests.cpp)

### Members

##### make function

```cpp
constexpr auto make_table(KeyValues && ... keyValues);
```
Create a table mapping keyValues two by two.

##### has_key, has_value

```cpp
constexpr bool has_key(auto && table, auto && key);
constexpr bool has_value(auto && table, auto && value);
```

Returns whether the given `key` or `value` is found in the table.

##### get_value, get_key

```cpp
template<typename Ret>
constexpr Ret & get_value(auto && table, auto && key);

template<typename Ret>
constexpr Ret & get_key(auto && table, auto && value);
```

Returns the `key` or `value` associated with the parameter. `asserts` if the parameter is not found.

##### try_get_value, try_get_key

```cpp
template<typename Ret>
constexpr Ret * try_get_value(auto && table, auto && key);

template<typename Ret>
constexpr Ret * try_get_key(auto && table, auto && value);
```

Returns the `key` or `value` associated with the parameter, or `nullptr` if it is not found.

##### Callback variants

```cpp
constexpr void get_value(auto && table, auto && key, auto && func);
constexpr void get_key(auto && table, auto && value, auto && func);

constexpr void try_get_value(auto && table, auto && key, auto && func);
constexpr void try_get_key(auto && table, auto && value, auto && func);
```

Finds the `key` or `value` associated with the parameter and passes it to `func`. The versions without `try` will `assert` if the parameter is not found.