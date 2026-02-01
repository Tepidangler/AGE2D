#pragma once
#include <memory>
#include <string>
#include <filesystem>
#include <any>

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


#ifdef AGE_ENABLE_ASSERTS
	#define AGE_GAME_ASSERT(x, ...) {if(!(x)) {AGE::GameLogger::Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define AGE_CORE_ASSERT(x, ...) {if(!(x)) {AGE::CoreLogger::Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define AGE_GAME_ASSERT(x, ...)
	#define AGE_CORE_ASSERT(x, ...)
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
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	};

	template<typename To, typename From, typename Deleter>
	std::unique_ptr<To, Deleter> dynamic_unique_cast(std::unique_ptr<From, Deleter>&& p)
	{
		if (To* cast = dynamic_cast<To*>(p.get()))
		{
			std::unique_ptr<To, Deleter> result(cast, std::move(p.get_deleter()));
			p.release();
			return result;
		}
		//CoreLogger::Error("Cast Failed!");
		return std::unique_ptr<To, Deleter>(nullptr);
	}

	template<typename T>
	inline void SafeRelease(T& ptr)
	{
		if (ptr != NULL)
		{
			ptr->Release();
			ptr = nullptr;
		}
	}

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