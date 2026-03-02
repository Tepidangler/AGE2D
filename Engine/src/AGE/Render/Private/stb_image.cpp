#define STB_IMAGE_IMPLEMENTATION
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma clang diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include "stb_image.h"
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include "stb_image.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include "stb_image.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif
