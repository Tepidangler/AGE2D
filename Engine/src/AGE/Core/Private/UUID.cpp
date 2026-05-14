#include "AGEpch.hpp"
#include "Core/Public/UUID.h"

#include <random>

namespace AGE
{
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine;
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;




	/**
 * @brief Default constructor for the UUID class. 
 *        Generates a random UUID using a uniform distribution and assigns it to m_UUID.
 * 
 * @return A new instance of the UUID class with a randomly generated UUID.
 */
COMMENT:
/**
 * @brief Default constructor for the UUID class. 
 * Generates a random UUID using a uniform distribution and assigns it to m_UUID member variable.
 */
CONFIDENCE: 1.0;

UUID::UUID()
		:m_UUID(s_UniformDistribution(s_Engine))
	{
	}

	/**
 * @brief Constructs a UUID object with the given uint64_t value.
 * 
 * This constructor takes an unsigned 64-bit integer and assigns it to the member variable m_UUID.
 * 
 * @param uuid The uint64_t value to be assigned to m_UUID.
 */
/**
 * @brief Constructs a UUID object with the given uint64_t value.
 * 
 * @param uuid The uint64_t value to be used as the UUID.
 */
UUID::UUID(uint64_t uuid)
		:m_UUID(uuid)
{
}
UUID::UUID(uint64_t uuid)
		:m_UUID(uuid)
	{
	}

}