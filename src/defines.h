#pragma once

#define fn [[nodiscard]]auto
#define static_fn [[nodiscard]]static auto
#define let const auto
#define bg_internal static

using f32 = float;
using f64 = double;

using i8 = signed char;
using i16 = short;
using i32 = int;
using i64 = long long;

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

// #define DEL_COPY_MOVE(TypeName) \
//     TypeName(TypeName const& other) = delete; \
//     void operator=(const TypeName&) = delete; \
//     TypeName(TypeName&& other) noexcept = delete; \
//     TypeName& operator=(TypeName&& other) noexcept = delete


#ifndef _DEBUG //  VS only
#define DEBUG(x) 
#else

#include <iostream>
template <typename ...Ts>
void DEBUG(Ts &&...ts) {
    ((std::cout << std::forward<Ts>(ts)), ...) << std::endl;
}

#endif




#ifdef _MSC_VER
using usize = unsigned __int64;
using isize = __int64;
#endif

#ifdef __GNUC__
using usize = __SIZE_TYPE__;
using isize = __PTRDIFF_TYPE__;
#endif

#ifdef __clang__
using usize = __SIZE_TYPE__;
using isize = __PTRDIFF_TYPE__;
#endif



////////////////////////////////////////////////////////////////
//
// Defer statement
// Akin to D's SCOPE_EXIT or
// similar to Go's defer but scope-based
//
// NOTE: C++11 (and above) only!
//
// NOTE(bill): Stupid fucking templates
template <typename T> struct gbRemoveReference { using Type = T; };
template <typename T> struct gbRemoveReference<T&> { using Type = T; };
template <typename T> struct gbRemoveReference<T&&> { using Type = T; };

/// NOTE(bill): `"Move`" semantics - invented because the C++ committee are idiots (as a collective not as indiviuals (well a least some aren't))
template <typename T> inline auto gb_forward(typename gbRemoveReference<T>::Type& t) -> T&& { return static_cast<T&&>(t); }
template <typename T> inline auto gb_forward(typename gbRemoveReference<T>::Type&& t) -> T&& { return static_cast<T&&>(t); }
template <typename T> inline auto gb_move(T&& t) -> T&& { return static_cast<typename gbRemoveReference<T>::Type&&>(t); }

template <typename F>
struct gbprivDefer {
    F f;
    explicit gbprivDefer(F&& f) : f(gb_forward<F>(f)) {}
    ~gbprivDefer() { f(); }
};

template <typename F>
auto gb__defer_func(F&& f) -> gbprivDefer<F> { return gbprivDefer<F>(gb_forward<F>(f)); }

#define GB_DEFER_1(x, y) x##y
#define GB_DEFER_2(x, y) GB_DEFER_1(x, y)
#define GB_DEFER_3(x)    GB_DEFER_2(x, __COUNTER__)
#define defer(code)      auto GB_DEFER_3(_defer_) = gb__defer_func([&]()->void{(code);})
