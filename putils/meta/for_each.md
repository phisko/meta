# [for_each](for_each.hpp)

Helper functions to iterate over things.

## tuple_for_each

```cpp
template<typename F, typename ...Args>
constexpr auto tuple_for_each(std::tuple<Args...> & tuple, F && f) noexcept;

template<typename F, typename ...Args>
constexpr auto tuple_for_each(const std::tuple<Args...> & tuple, F && f) noexcept;
```

For each element `e` in `tuple`, calls `f(e)`. Returns the same value as `f`:

* if `f` returns `bool`, stops iterating once `f` has returned `true`, and returns `true` as well. Otherwise, returns `false`
* if `f` returns an `std::optional`, stops iterating once `f` has returned a non-null `optional` and returns it as well. Otherwise, returns `std::nullopt`
* if `f` returns void, returns `false`

## for_each_type

```cpp
template<typename ...Types, typename Func>
constexpr auto for_each_type(Func && f) noexcept;
```

For each type `T` in `Types...`, calls `f(putils::meta::type<T>)`. Functions can then extract `T` using [putils_wrapped_type](type.md).