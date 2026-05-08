//
// Created by gdmgp on 2/8/2026.
//
#pragma once
#include <memory>
#ifndef AGE2D_POINTERS_H
#define AGE2D_POINTERS_H
namespace AGE {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    /**
 * @brief Creates a new instance of type T in an owning Scope.
 * 
 * This function creates and returns a new instance of type T, which is managed by the Scope class. The arguments provided are forwarded to the constructor of T.
 *
 * @tparam T Type of object to be created.
 * @tparam Args Types of arguments to be passed to the constructor of T.
 * 
 * @param args Arguments to be passed to the constructor of T.
 *
 * @return A new instance of type T in an owning Scope.
 */
constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    /**
 * @brief Creates a reference to an object of type T.
 *
 * This function creates and returns a reference to an object of type T, using variadic template arguments for the constructor. 
 * The returned reference is managed by std::shared_ptr.
 *
 * @tparam T The type of the object to be created.
 * @tparam Args The types of the arguments to be passed to the constructor of T.
 * @param args The arguments to be forwarded to the constructor of T.
 * @return A reference (std::shared_ptr) to an object of type T, constructed with the provided arguments.
 */
constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    };

    template<typename To, typename From, typename Deleter>
    /**
 * @brief Dynamically casts a unique pointer to another type.
 * 
 * This function attempts to dynamically cast the given unique pointer to the specified type `To`. If the dynamic_cast is successful, it creates and returns a new unique pointer of type `To` that owns the same object as the input pointer. The deleter from the original unique pointer is moved into the new one.
 * 
 * @param p A unique pointer to an object of type `From` with a custom deleter.
 * @return A unique pointer to an object of type `To`, or nullptr if the dynamic_cast fails. The returned unique pointer will have its own deleter.
 */
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
    /**
 * @brief Safely releases a COM object and sets the pointer to null.
 *
 * This function checks if the provided pointer is not null, then it calls the Release() method on the object pointed by the pointer and finally sets the pointer itself to null. 
 *
 * @param ptr A reference to a raw pointer of type T that needs to be released.
 * @return None
 */
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