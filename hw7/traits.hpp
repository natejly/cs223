#pragma once

#include <type_traits>
#include <iostream>
#include <string>

/**
 * A type trait that determines whether a type has an input operator.
 */
template <typename T>
struct has_input_operator
{
    template <typename U>
    static auto test(U &&u) -> decltype(std::declval<std::istream &>() >>
                                            std::declval<U &>(),
                                        std::true_type{});

    template <typename U>
    static std::false_type test(...);

    static constexpr bool value = decltype(test<T>(std::declval<T>()))::value;
};

/**
 * A type trait that determines whether a type has an output operator.
 */
template <typename T>
struct has_output_operator
{
    template <typename U>
    static auto test(U &&u) -> decltype(std::declval<std::ostream &>()
                                            << std::declval<U>(),
                                        std::true_type{});

    template <typename U>
    static std::false_type test(...);

    static constexpr bool value = decltype(test<T>(std::declval<T>()))::value;
};

/**
 * A type trait that determines whether a type is constructible from a string.
 */
template <typename T>
struct is_string_constructible : std::is_constructible<T, std::string>
{
};
