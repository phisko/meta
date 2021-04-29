# Meta

Phisko's metaprogramming utilities.

## Classes

* [type](type.md): object representation of a type
* [table](table.md): map any number of keys of any number of types to any number of values of any number of types. All with compile-time type safety.

## Function-only headers

* [apply](apply.md): C++14 implementation of `std::apply`
* [for_each](for_each.md): call a function for each element in a tuple, or instantiate a template type and call a static function for each type in a list
* [has_type](has_type.md): type_trait indicating whether a tuple contains a certain type
* [nameof](nameof.md): macro to mimick other languages' `nameof`
* [new_from_tuple](new_from_tuple.md): a make_from_tuple that creates a heap-based object