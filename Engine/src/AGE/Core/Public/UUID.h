#pragma once
#ifdef AG_PLATFORM_WINDOWS
#include <xhash>
#else
#include <functional>
#endif
#include <cinttypes>
namespace AGE
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		/**
 * @brief Default copy constructor for the UUID class.
 *
 * This function is used to create a new instance of the UUID class by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this function.
 * 
 * @param uuid The UUID object to be copied.
 */
UUID(const UUID&) = default;


		/**
 * @brief Converts the UUID object to a uint64_t value.
 *
 * This function returns the underlying uint64_t representation of the UUID object, which is its unique identifier.
 *
 * @return The 64-bit unsigned integer representation of the UUID object.
 */
operator uint64_t() const { return m_UUID; }

	private:

		uint64_t m_UUID;
	};

}

namespace std
{
	template<>
	struct hash<AGE::UUID>
	{
		/**
 * @brief Computes a hash value for the given UUID.
 * 
 * This function computes a hash value based on the input UUID using the standard C++ library's `hash` class with `uint64_t` as its template argument. The purpose of this function is to provide a unique identifier for each UUID, which can be useful in certain data structures or algorithms that require unique keys.
 * 
 * @param uuid The UUID to compute the hash value for.
 * @return A size_t representing the computed hash value.
 */
std::size_t operator()(const AGE::UUID& uuid) const noexcept
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}