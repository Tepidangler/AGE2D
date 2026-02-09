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
#else
	#error AGE only supports Windows!
#endif 

#if AG_DEBUG
	#define AGE_ENABLE_ASSERTS
	#pragma enable_d3d11_debug_symbols
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
		explicit Reverse(T& iterable) : iterable_{ iterable } {}
		auto begin() const { return std::rbegin(iterable_); }
		auto end() const { return std::rend(iterable_); }
	};
}

namespace GameFramework
{

}