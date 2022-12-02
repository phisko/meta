# [function_signature](function_signature.hpp)

Type trait which, given a function type, returns the function's "clean" signature, i.e. without `noexcept` or the wrapping `std::function` type.