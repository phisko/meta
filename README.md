# Meta

[![CMake](https://github.com/phisko/meta/actions/workflows/cmake.yml/badge.svg)](https://github.com/phisko/meta/actions/workflows/cmake.yml)

Phisko's metaprogramming utilities.

## Classes

* [type](type.md): object representation of a type
* [table](table.md): map any number of keys of any number of types to any number of values of any number of types. All with compile-time type safety.

## Function-only headers

* [apply](apply.md): C++14 implementation of `std::apply`
* [for_each](for_each.md): call a function for each element in a tuple, or instantiate a template type and call a static function for each type in a list
* [fwd](fwd.md): macro which calls `std::forward` for the correct type
* [has_type](has_type.md): type_trait indicating whether a tuple contains a certain type
* [members](member.mds): type_traits and functions for inspecting type members
* [nameof](nameof.md): macro to mimick other languages' `nameof`
* [new_from_tuple](new_from_tuple.md): a make_from_tuple that creates a heap-based object

## Type traits

* [has_member](traits/has_memer.md)
* [has_nested_type](traits/has_nested_type.md)
* [indexed_type](traits/indexed_type.md)
* [is_indexable](traits/is_indexable.md)
* [is_iterable](traits/is_iterable.md)
* [is_specialization](traits/is_specialization.md)
* [is_streamable](traits/is_streamable.md)
* [is_unstreamable](traits/is_unstreamable.md)

### Function traits

* [is_function](traits/is_function.md)
* [function_signature](traits/function_signature.md)
* [function_arguments](traits/function_arguments.md)
* [function_return_type](traits/function_return_type.md)

### Member function traits

* [is_member_function_ptr](traits/is_member_function_ptr.md)
* [member_function_signature](traits/member_function_signature.md)
* [member_function_arguments](traits/member_function_arguments.md)
* [member_function_return_type](traits/member_function_return_type.md)


