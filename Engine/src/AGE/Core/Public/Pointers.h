//
// Created by gdmgp on 2/8/2026.
//
#include <memory>
#ifndef AGE2D_POINTERS_H
#define AGE2D_POINTERS_H
namespace AGE {

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
}
#endif //AGE2D_POINTERS_H