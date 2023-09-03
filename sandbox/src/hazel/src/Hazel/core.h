#pragma once

#define HAZEL_API __attribute__((visibility("default")))

#define BIT(x) (1 << x)

#ifdef HZ_ENABLE_ASSERTS
    #define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#else
    #define HZ_ASSERT(x, ...)
    #define HZ_CORE_ASSERT(x, ...)
#endif
