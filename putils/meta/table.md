# [table](table.hpp)

A constexpr, type-safe association table that maps any key of any type to any value of any type.

For usage examples, see the [unit tests](tests/table.tests.cpp)

### Members

##### make function

```cpp
constexpr auto make_table(KeyValues && ... keyValues);
```
Create a table mapping keyValues two by two.

##### get_value, get_key

```cpp
template<typename Ret>
constexpr Ret * get_value(auto && table, auto && key);
template<typename Ret>
constexpr Ret * get_key(auto && table, auto && value);
```

Returns the `key` or `value` associated with the parameter, or `nullptr` if it is not found or not of the requested type.

##### Callback variants

```cpp
constexpr void get_value(auto && table, auto && key, auto && func);
constexpr void get_key(auto && table, auto && value, auto && func);
```

Finds the `key` or `value` associated with the parameter and passes it to `func` if it is found. Useful when the type is unknown.