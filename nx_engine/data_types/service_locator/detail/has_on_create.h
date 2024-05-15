#pragma once
#include <type_traits>

namespace service::detail
{
    template <typename, typename T>
    struct has_on_create
    {
        static_assert(
            std::integral_constant<T, false>::value,
            "Second template parameter needs to be of function type.");
    };

    template <typename C, typename Ret, typename... Args>
    struct has_on_create<C, Ret(Args...)>
    {
    private:
        template <typename T>
        static constexpr auto check(T*) ->
            typename std::is_same<
                decltype(std::declval<T>().on_create(std::declval<Args>()...)),
                Ret>::type;

        template <typename>
        static constexpr std::false_type check(...);

        typedef decltype(check<C>(0)) type;

    public:
        static constexpr bool value = type::value;
    };
}
