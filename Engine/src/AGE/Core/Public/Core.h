#pragma once
#include <memory>
#include <string>
#include <filesystem>
#include <any>
#include "Core/Public/Log.h"

#ifdef AG_PLATFORM_WINDOWS
#if AG_DYNAMIC_LINK

	#ifdef AG_BUILD_DLL
		#define AGE_API __declspec(dllexport)
	#else
		#define AGE_API __declspec(dllimport)
	#endif
#else
	#define AGE_API
	#undef AKSOUNDENGINE_DLL
#endif
#endif

#ifdef AG_PLATFORM_LINUX
#if AG_DYNAMIC_LINK

	#ifdef AG_BUILD_DLL
		#define AGE_API __declspec(dllexport)
	#else
		#define AGE_API __declspec(dllimport)
	#endif
#else
	#define AGE_API
	#undef AKSOUNDENGINE_DLL
#endif
#endif

#if !defined(AG_PLATFORM_LINUX) && !defined(AG_PLATFORM_WINDOWS)
#error AGE only supports Windows and Linux!
#endif

#if AG_DEBUG
	#define AGE_ENABLE_ASSERTS
//	#pragma enable_d3d11_debug_symbols
#endif

#if AG_DIST
	#define AK_OPTIMIZED
#endif


#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_AXIS_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_ACTION_FN(x) std::bind(&x, this)

#define BIT(x) (1 << x)
namespace AGE
{
	typedef unsigned long ulong_t;



	template<typename T>
	class Reverse
	{
	private:
		T& iterable_;

	public:
		/**
 * @brief Constructs a new instance of the Reverse class with an iterable object.
 * @param[in] iterable A reference to the iterable object that will be reversed.
 */
explicit Reverse(T& iterable) : iterable_{ iterable } {}
		/**
 * @brief Returns a reverse iterator pointing to the last element of the container (i.e., its reverse beginning).
 * @return A reverse iterator which points to the end of the sequence of numbers in the container.
 */
auto begin() const { return std::rbegin(iterable_); }
		COMMENT:
/**
 * @brief Returns a reverse iterator pointing to the theoretical element past the last element of the sequence.
 * @return A reverse iterator that points to the theoretical element past the last element of the sequence.
 */
CONFIDENCE: 1.0;

auto end() const { return std::rend(iterable_); }
	};
}

namespace GameFramework
{

}