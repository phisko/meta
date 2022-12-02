# [members](members.hpp)

Type traits and functions for attribute introspection.

## member_type

```cpp
template<typename MemberPtr>
using member_type = ...;
```

Alias for the concrete type of a member pointer. For instance:

```cpp
struct a {
    int i = 0;
};
```

`member_type<decltype(&a::i)>` will be `int`.

## object_type

```cpp
template<typename MemberPtr>
using object_type = ...;
```

Alias for the "parent" type of a member pointer. For instance:

```cpp
struct a {
    int i = 0;
};
```

`object_type<decltype(&a::i)>` will be `A`.

## member_offset

```cpp
template<typename T, typename U>
constexpr std::ptrdiff_t member_offset(U T::* member) noexcept;
```

Converts a member pointer to a pointer offset.