#pragma once
#include <type_traits>

namespace service::detail
{
    template <typename, typename TFunc>
    struct has_on_create
    {
        static_assert(
            std::integral_constant<TFunc, false>::value,
            "Second template parameter needs to be of function type.");
    };

    template <typename TClass, typename TFunc, typename... TArgs>
    struct has_on_create<TClass, TFunc(TArgs...)>
    {
        template <typename TInstance>
        static constexpr auto check(TInstance*) ->
            typename std::is_same<
                decltype(std::declval<TInstance>().on_create(std::declval<TArgs>()...)),
                TFunc>::type;

        template <typename>
        static constexpr std::false_type check(...);
    private:
        typedef decltype(check<TClass>(nullptr)) type;

    public:
        static constexpr bool value = type::value;
    };
}
