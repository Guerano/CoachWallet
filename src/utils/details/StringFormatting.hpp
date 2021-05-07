#pragma once

#include <QString>

#include <type_traits>

namespace Utility::Details
{
    template<bool B, typename T>
    using enable_if_t    = typename std::enable_if<B, T>::type;
    template<typename T1, typename T2, typename R>
    using enable_if_same = enable_if_t<std::is_same<T1, T2>::value, R>;

    template<typename T>
    struct has_to_string
    {
        template<typename C, typename = enable_if_same<decltype(std::declval<C>().toString()), QString, void>>
        static std::true_type  test(int *);
        template<typename C>
        static std::false_type test(...);

        using                 type  = decltype(test<T>(nullptr));
        static constexpr bool value = type::value;
    };

    template<typename T>
    inline enable_if_t<!has_to_string<T>::value, QString>
    _moduloHelper(const QString & s, const T & value)
    { return s.arg(value); }

    // toString function
    template<typename T>
    inline enable_if_t<has_to_string<T>::value, QString>
    _moduloHelper(const QString & s, const T & value)
    { return s.arg(value.toString()); }
} // !namespace Utility::Details
