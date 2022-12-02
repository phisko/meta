# Meta

[![tests](https://github.com/phisko/meta/workflows/tests/badge.svg)](https://github.com/phisko/meta/actions/workflows/build.yml)

Phisko's metaprogramming utilities.

## Classes

* [type](putils/meta/type.md): object representation of a type
* [table](putils/meta/table.md): map any number of keys of any number of types to any number of values of any number of types. All with compile-time type safety.

## Function-only headers

* [apply](putils/meta/apply.md): C++14 implementation of `std::apply`
* [for_each](putils/meta/for_each.md): call a function for each element in a tuple, or instantiate a template type and call a static function for each type in a list
* [fwd](putils/meta/fwd.md): macro which calls `std::forward` for the correct type
* [has_type](putils/meta/has_type.md): type_trait indicating whether a tuple contains a certain type
* [members](putils/meta/member.md): type_traits and functions for inspecting type members
* [nameof](putils/meta/nameof.md): macro to mimick other languages' `nameof`
* [new_from_tuple](putils/meta/new_from_tuple.md): a make_from_tuple that creates a heap-based object

## Type traits

* [indexed_type](putils/meta/traits/indexed_type.md)
* [is_specialization](putils/meta/traits/is_specialization.md)

## Concepts

* [indexable](putils/meta/concepts/indexable.md)
* [streamable](putils/meta/concepts/streamable.md)
* [unstreamable](putils/meta/concepts/unstreamable.md)

### Function traits

* [is_function](putils/meta/traits/is_function.md)
* [function_signature](putils/meta/traits/function_signature.md)
* [function_arguments](putils/meta/traits/function_arguments.md)
* [function_return_type](putils/meta/traits/function_return_type.md)

### Member function traits

* [is_member_function_ptr](putils/meta/traits/is_member_function_ptr.md)
* [member_function_signature](putils/meta/traits/member_function_signature.md)
* [member_function_arguments](putils/meta/traits/member_function_arguments.md)
* [member_function_return_type](putils/meta/traits/member_function_return_type.md)
