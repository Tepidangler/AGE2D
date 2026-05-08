#include "AGEpch.hpp"
#include "RNG/Public/RNG.h"
#include <limits>

#define ONE_OVER_MAX_UINT (1 / std::numeric_limits<uint32_t>::max())
#define ONE_OVER_MAX_INT (1 / std::numeric_limits<int32_t>::max())
#define ONE_OVER_MIN_UINT (1 /std::numeric_limits<uint32_t>::min())


namespace AGE
{

	 Scope<SquirrelNoise> SquirrelRNG::s_NoiseObj;
	 uint32_t SquirrelRNG::s_Seed;
	 int SquirrelRNG::s_Position; 
	 int SquirrelRNG::s_Rotation;

	/**
 * @brief Initializes the SquirrelRNG with a given seed.
 * 
 * This function sets the initial seed for the random number generator and resets all other variables to their default state.
 * The generated noise object is also created here.
 * 
 * @param Seed The initial seed value for the RNG.
 */
void SquirrelRNG::Init(uint32_t Seed)
	{
		s_Seed = Seed;
		s_Position = 0;
		s_Rotation = 0;
		s_NoiseObj = CreateScope<SquirrelNoise>();
	}

	/**
 * @brief Generates a random uint32 number.
 *
 * This function generates and returns a pseudo-random unsigned integer of type uint32_t. The actual values returned are not truly random, but rather determined by the internal state of the SquirrelRNG object. 
 *
 * @return A randomly generated uint32_t number. In this case, it always returns 0 as per the current implementation.
 */
uint32_t SquirrelRNG::RollRandomUint32()
	{
		return 0;
	}

	/**
 * @brief Generates a random uint16_t value.
 *
 * This function generates and returns a pseudo-random uint16_t number using the SquirrelRNG algorithm. The returned value is uniformly distributed over its entire range of possible values, from 0 to 65535 (inclusive).
 *
 * @return A random uint16_t value.
 */
uint16_t SquirrelRNG::RollRandomUint16()
	{
		return 0;
	}

	/**
 * @brief Generates a random byte using the Squirrel RNG algorithm.
 *
 * This function uses the Squirrel RNG algorithm to generate a random byte. The output is deterministic and can be used for cryptographic purposes if necessary.
 * 
 * @return A randomly generated uint8_t value.
 */
uint8_t SquirrelRNG::RollRandomByte()
	{
		return 0;
	}

	/**
 * @brief Generates a random integer less than the provided maximum value.
 *
 * This function generates a pseudo-random number using SquirrelRNG algorithm, which is then returned as an unsigned 32-bit integer. The generated number will be less than the provided MaxValueNotInclusive parameter. If this value is zero or negative, the behavior of this function is undefined.
 *
 * @param MaxValueNotInclusive An unsigned 32-bit integer specifying the upper limit for the random number to be generated (exclusive). Must be greater than zero.
 * @return A pseudo-randomly generated unsigned 32-bit integer less than MaxValueNotInclusive.
 */
uint32_t SquirrelRNG::RollRandomIntLessThan(uint32_t MaxValueNotInclusive)
	{
		return 0;
	}

	/**
 * @brief Generates a random integer within the specified range.
 *
 * This function generates and returns a pseudo-random number between two given integers (inclusive). The generated number will be in the range [MinValueInclusive, MaxValueInclusive]. 
 * If MinValueInclusive > MaxValueInclusive, an empty range is assumed which always returns MinValueInclusive.
 *
 * @param MinValueInclusive Lower bound of the range (inclusive).
 * @param MaxValueInclusive Upper bound of the range (inclusive).
 * 
 * @return A pseudo-random integer within the specified range.
 */
int SquirrelRNG::RollRandomIntInRange(int MinValueInclusive, int MaxValueInclusive)
	{
		return 0;
	}

	/**
 * @brief This function generates a random float between 0 and 1.
 *
 * The generated number is obtained from the noise object associated with SquirrelRNG class.
 * It uses Get1dNoiseZeroToOne method of the noise object to generate the number, which takes in two parameters: current position (s_Position) and a seed value (s_Seed). 
 * The s_Position is incremented after each call to this function to ensure uniqueness of the generated numbers.
 *
 * @return A float between 0 and 1 representing the random number.
 */
float SquirrelRNG::RollRandomFloatZeroToOne()
	{
		return SquirrelRNG::s_NoiseObj->Get1dNoiseZeroToOne(SquirrelRNG::s_Position++, s_Seed);
	}

	/**
 * @brief RollRandomFloatInRange generates a random float within the specified range.
 * 
 * This function uses a SquirrelRNG to generate a random float between two given values (MinValueInclusive and MaxValueInclusive). The generated number will be inclusive of both end points, meaning it could return either MinValueInclusive or MaxValueInclusive with equal probability.
 * 
 * @param MinValueInclusive the lower limit of the range from which to generate a random float.
 * @param MaxValueInclusive the upper limit of the range from which to generate a random float.
 * 
 * @return A random float within the specified range (MinValueInclusive, MaxValueInclusive]. The return value will be greater than or equal to MinValueInclusive and less than or equal to MaxValueInclusive with equal probability. If MinValueInclusive is greater than MaxValueInclusive, "Unknown" is returned.
 */
float SquirrelRNG::RollRandomFloatInRange(float MinValueInclusive, float MaxValueInclusive)
	{

		// THis implementation is likely always going to return the min value. TODO: Fix to return numbers within the range including the max
		return MinValueInclusive + (MaxValueInclusive - MinValueInclusive) * SquirrelRNG::s_NoiseObj->Get1dNoiseZeroToOne(s_Position++, s_Seed);
	}

	/**
 * @brief This function rolls a random chance based on the given probability.
 * 
 * @param ProbabilityofReturnTrue The probability of returning true, should be between 0 and 1.
 * @return bool Returns true with the provided probability, false otherwise. If the input is not within [0,1], it returns false.
 */
bool SquirrelRNG::RollRandomChance(float ProbabilityofReturnTrue)
	{
		return false;
	}

	/**
 * @brief RollRandomDirection2D generates a random direction in two dimensions.
 * 
 * This function uses the noise object to generate two values between 0 and 1 for x and y coordinates respectively. The generated values are stored in out_x and out_y.
 * 
 * @param[out] out_x Reference to a float where the x coordinate will be stored.
 * @param[out] out_y Reference to a float where the y coordinate will be stored.
 * 
 * @return void
 */
void SquirrelRNG::RollRandomDirection2D(float& out_x, float& out_y)
	{
		out_x = s_NoiseObj->Get2dNoiseZeroToOne(s_Position, s_Position, s_Seed);
		out_y = s_NoiseObj->Get2dNoiseZeroToOne(s_Position, s_Position + 1, s_Seed);
	}

	/**
 * @brief RollRandomRotationFloat generates a random float value for rotation.
 * The function uses Perlin noise to generate a pseudo-random number and cast it to float. 
 * This is used as a means of generating a random float value that can be used for rotation purposes.
 *
 * @return A floating point number between 0 and 1 representing the generated random rotation.
 */
float SquirrelRNG::RollRandomRotationFloat()
	{
		return (float)s_NoiseObj->Get1dNoiseUint(s_Rotation++, s_Seed);
	}

	/**
 * @brief Constructor for SquirrelNoise class.
 * Initializes the position member variable to 0.
 */
SquirrelNoise::SquirrelNoise()
	{
		m_Position = 0;
	}


	/**
 * @brief Generates a pseudorandom 32-bit unsigned integer.
 *
 * This function uses the SquirrelNoise algorithm to generate a pseudorandom number. The generated value is based on the current position in the noise field, which is then incremented for the next call.
 *
 * @return A pseudorandom 32-bit unsigned integer.
 */
uint32_t SquirrelNoise::Rand()
	{
		return Get1dNoiseUint(m_Position++);
	}

	/**
 * @brief Generates a one-dimensional noise value.
 *
 * This function generates a pseudorandom number for the given position and seed using a combination of bitwise operations. 
 * The result is then returned as an unsigned 32-bit integer.
 *
 * @param Position The input position for which to generate the noise.
 * @param Seed A random value used to initialize the noise generation.
 * @return An unsigned 32-bit integer representing the one-dimensional noise at the given position and seed.
 */
uint32_t SquirrelNoise::Get1dNoiseUint(int Position, uint32_t Seed)
	{
		constexpr unsigned int BIT_NOISE1 = 0xB5297A4D;
		constexpr unsigned int BIT_NOISE2 = 0x68E31DA4;
		constexpr unsigned int BIT_NOISE3 = 0x1B56C4E9;

		unsigned int mangled = (uint32_t)Position;
		mangled *= BIT_NOISE1;
		mangled += Seed;
		mangled ^= (mangled >> 8);
		mangled += BIT_NOISE2;
		mangled ^= (mangled << 8);
		mangled *= BIT_NOISE3;
		mangled ^= (mangled >> 8);

		return mangled;
	}
	/**
 * @brief Computes a two-dimensional noise value.
 *
 * This function generates a pseudo-random number based on the input parameters using a prime number (198491317) to create an offset for the x position in combination with the y position. The result is then passed through Get1dNoiseUint() to generate the noise value.
 *
 * @param PositionX The x-coordinate of the point for which to compute the noise.
 * @param PositionY The y-coordinate of the point for which to compute the noise.
 * @param Seed A seed value used to initialize the pseudo-random number generator.
 * 
 * @return A pseudo-random integer between 0 and UINT32_MAX, representing a two-dimensional noise value.
 */
uint32_t SquirrelNoise::Get2dNoiseUint(int PositionX, int PositionY, uint32_t Seed)
	{
		constexpr int PRIME_NUMBER = 198491317;
		return Get1dNoiseUint(PositionX + (PRIME_NUMBER * PositionY), Seed);
	}
	/**
 * @brief This function generates a 3D noise value using the SquirrelNoise algorithm.
 * 
 * The function takes in three positions (PositionX, PositionY, and PositionZ) and a seed for randomness. It uses these inputs to generate a unique hash which is then passed into the Get1dNoiseUint() function. This function returns a uint32_t value representing the noise at the given position.
 * 
 * @param PositionX The x-coordinate of the position in the noise field.
 * @param PositionY The y-coordinate of the position in the noise field.
 * @param PositionZ The z-coordinate of the position in the noise field.
 * @param Seed A seed for randomness, used to generate a unique hash.
 * 
 * @return Returns a uint32_t value representing the noise at the given position.
 */
uint32_t SquirrelNoise::Get3dNoiseUint(int PositionX, int PositionY, int PositionZ, uint32_t Seed)
	{
		constexpr int PRIME_NUMBER1 = 198491317;
		constexpr int PRIME_NUMBER2 = 6542989;
		return Get1dNoiseUint(PositionX + (PRIME_NUMBER1 * PositionY) + (PRIME_NUMBER2 * PositionZ), Seed);
	}
	/**
 * @brief Computes a four-dimensional noise value.
 *
 * This function computes the noise value for a given position in space (x, y, z, w) and with a specific seed. The computation is based on the Get1dNoiseUint() function, which internally uses a prime number to generate pseudo-random values. 
 *
 * @param PositionX The x coordinate of the position for which to compute the noise value.
 * @param PositionY The y coordinate of the position for which to compute the noise value.
 * @param PositionZ The z coordinate of the position for which to compute the noise value.
 * @param PositionW The w coordinate of the position for which to compute the noise value.
 * @param Seed A seed used to initialize the pseudo-random number generator.
 * 
 * @return A 32-bit unsigned integer representing the computed noise value.
 */
uint32_t SquirrelNoise::Get4dNoiseUint(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed)
	{
		constexpr int PRIME_NUMBER1 = 198491317;
		constexpr int PRIME_NUMBER2 = 6542989;
		constexpr int PRIME_NUMBER3 = 73939;
		return Get1dNoiseUint(PositionX + (PRIME_NUMBER1 * PositionY) + (PRIME_NUMBER2 * PositionZ) + (PRIME_NUMBER3 * PositionW), Seed);
	}

	/**
 * @brief Computes a one-dimensional noise value in the range [0, 1] for a given position and seed.
 * 
 * This function uses a hash function to generate a pseudorandom number based on the input parameters. The result is then scaled to the range [0, 1].
 * @param Position The integer position for which to compute the noise value.
 * @param Seed A unique identifier used to seed the random number generator.
 * @return A floating-point value representing the computed noise in the range [0, 1].
 */
float SquirrelNoise::Get1dNoiseZeroToOne(int Position, uint32_t Seed)
	{
		//constexpr unsigned int BIT_NOISE1 = 0xB5297A4D;
		//constexpr unsigned int BIT_NOISE2 = 0x68E31DA4;
		//constexpr unsigned int BIT_NOISE3 = 0x1B56C4E9;
		//
		//unsigned int mangled = Position;
		//mangled *= BIT_NOISE1;
		//mangled += Seed;
		//mangled ^= (mangled >> 8);
		//mangled += BIT_NOISE2;
		//mangled ^= (mangled << 8);
		//mangled *= BIT_NOISE3;
		//mangled ^= (mangled >> 8);

		return (float)(ONE_OVER_MAX_UINT * Get1dNoiseUint(Position, Seed));
	}

	/**
 * @brief This function returns a two-dimensional noise value between 0 and 1.
 * 
 * The function takes three parameters - the x and y positions for which to generate the noise, and a seed used in the random number generation. It uses the Get2dNoiseUint() function internally to get an unsigned integer noise value, then scales this by ONE_OVER_MAX_UINT to return a float between 0 and 1.
 *
 * @param PositionX The x position for which to generate the noise.
 * @param PositionY The y position for which to generate the noise.
 * @param Seed A seed used in the random number generation.
 *
 * @return A floating-point value between 0 and 1 representing the two-dimensional noise at the given positions with the provided seed.
 */
float SquirrelNoise::Get2dNoiseZeroToOne(int PositionX, int PositionY, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER = 198491317;
		return (float)(ONE_OVER_MAX_UINT * Get2dNoiseUint(PositionX,PositionY, Seed));
	}

	/**
 * @brief This function generates a 3D noise value between 0 and 1.
 * 
 * The function takes in the x, y, z coordinates of the position for which to generate the noise, as well as a seed for random number generation. It uses this information along with some pre-defined constants (like ONE_OVER_MAX_UINT) to calculate and return a noise value between 0 and 1.
 * 
 * @param PositionX The x coordinate of the position for which to generate the noise.
 * @param PositionY The y coordinate of the position for which to generate the noise.
 * @param PositionZ The z coordinate of the position for which to generate the noise.
 * @param Seed A seed value used in random number generation.
 * 
 * @return A float representing a 3D noise value between 0 and 1.
 */
float SquirrelNoise::Get3dNoiseZeroToOne(int PositionX, int PositionY, int PositionZ, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER1 = 198491317;
		//constexpr int PRIME_NUMBER2 = 6542989;
		return (float)(ONE_OVER_MAX_UINT * Get3dNoiseUint(PositionX, PositionY, PositionZ, Seed));
	}

	/**
 * @brief This function generates a four-dimensional noise value between 0 and 1.
 * 
 * The function uses the Get4dNoiseUint() method to generate an unsigned integer noise value. It then converts this value into a float between 0 and 1 by multiplying it with ONE_OVER_MAX_UINT (a constant defined in SquirrelNoise class).
 * 
 * @param PositionX The x-coordinate of the position for which to generate noise.
 * @param PositionY The y-coordinate of the position for which to generate noise.
 * @param PositionZ The z-coordinate of the position for which to generate noise.
 * @param PositionW The w-coordinate of the position for which to generate noise.
 * @param Seed A seed value used to initialize the random number generator.
 * 
 * @return A float representing a four-dimensional noise value between 0 and 1.
 */
float SquirrelNoise::Get4dNoiseZeroToOne(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER1 = 198491317;
		//constexpr int PRIME_NUMBER2 = 6542989;
		//constexpr int PRIME_NUMBER3 = 73939;
		return (float)(ONE_OVER_MAX_UINT * Get4dNoiseUint(PositionX, PositionY, PositionZ, PositionW, Seed));
	}

	/**
 * @brief This function generates a one-dimensional noise value between -1 and 1.
 *
 * The function takes an integer position and a seed as input parameters. It uses the provided position and seed to generate a pseudo-random number using bitwise operations, which is then scaled to fall within the range of -1 to 1.
 *
 * @param Position An integer representing the position for which to generate noise.
 * @param Seed A 32-bit unsigned integer used as a seed for the random number generation.
 *
 * @return A floating-point value between -1 and 1, representing the generated noise value.
 */
float SquirrelNoise::Get1dNoiseNegOneToOne(int Position, uint32_t Seed)
	{
		//constexpr unsigned int BIT_NOISE1 = 0xB5297A4D;
		//constexpr unsigned int BIT_NOISE2 = 0x68E31DA4;
		//constexpr unsigned int BIT_NOISE3 = 0x1B56C4E9;
		//
		//unsigned int mangled = Position;
		//mangled *= BIT_NOISE1;
		//mangled += Seed;
		//mangled ^= (mangled >> 8);
		//mangled += BIT_NOISE2;
		//mangled ^= (mangled << 8);
		//mangled *= BIT_NOISE3;
		//mangled ^= (mangled >> 8);

		return (float)(ONE_OVER_MAX_INT * Get1dNoiseUint(Position, Seed));
	}

	/**
 * @brief This function generates a 2D noise value between -1 and 1.
 * 
 * The function takes in two positions (x and y) and a seed for the random number generation. It uses the Get2dNoiseUint() function to generate an integer noise value, which is then scaled to be between -1 and 1 by multiplying with ONE_OVER_MAX_INT.
 * 
 * @param PositionX The x position in the noise field.
 * @param PositionY The y position in the noise field.
 * @param Seed A seed for the random number generation.
 * 
 * @return A float value representing the 2D noise at the given positions and with the provided seed, between -1 and 1.
 */
float SquirrelNoise::Get2dNoiseNegOneToOne(int PositionX, int PositionY, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER = 198491317;
		return (float)(ONE_OVER_MAX_INT * Get2dNoiseUint(PositionX, PositionY, Seed));
	}

	/**
 * @brief This function generates a 3D noise value between -1 and 1.
 *
 * The function takes in the x, y, z coordinates of the position for which we want to generate noise, as well as a seed for the random number generator. It uses this information along with some pre-defined constants (like ONE_OVER_MAX_INT) to calculate and return a 3D noise value between -1 and 1.
 *
 * @param PositionX The x coordinate of the position for which we want to generate noise.
 * @param PositionY The y coordinate of the position for which we want to generate noise.
 * @param PositionZ The z coordinate of the position for which we want to generate noise.
 * @param Seed A seed for the random number generator used in generating the noise value.
 * 
 * @return Returns a float between -1 and 1 representing the calculated 3D noise value.
 */
float SquirrelNoise::Get3dNoiseNegOneToOne(int PositionX, int PositionY, int PositionZ, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER1 = 198491317;
		//constexpr int PRIME_NUMBER2 = 6542989;
		return (float)(ONE_OVER_MAX_INT * Get3dNoiseUint(PositionX, PositionY, PositionZ, Seed));
	}

	/**
 * @brief This function generates a four-dimensional noise value between -1 and 1.
 * 
 * The function uses the Get4dNoiseUint() method to generate an integer noise value, then scales it by ONE_OVER_MAX_INT to get a float value in the range [0, 1]. This is then scaled by 2 and subtracted from 3 to get a value in the range [-1, 1].
 * 
 * @param PositionX The x-coordinate of the position for which to generate noise.
 * @param PositionY The y-coordinate of the position for which to generate noise.
 * @param PositionZ The z-coordinate of the position for which to generate noise.
 * @param PositionW The w-coordinate of the position for which to generate noise.
 * @param Seed A seed value used to initialize the random number generator.
 * 
 * @return A float value representing the four-dimensional noise at the given position and with the given seed. This will be in the range [-1, 1].
 */
float SquirrelNoise::Get4dNoiseNegOneToOne(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER1 = 198491317;
		//constexpr int PRIME_NUMBER2 = 6542989;
		//constexpr int PRIME_NUMBER3 = 73939;
		return (float)(ONE_OVER_MAX_INT * Get4dNoiseUint(PositionX, PositionY, PositionZ, PositionW, Seed));
	}
	

	/**
 * @brief Computes a one-dimensional noise value for a given rotation and seed.
 *
 * This function uses a combination of bitwise operations to generate a pseudorandom number based on the input parameters. The result is then clamped between 1 and ONE_OVER_MAX_UINT, which are constants defined in the SquirrelNoise class.
 *
 * @param Rotation The rotation value used as an input for the noise generation.
 * @param Seed A seed value to initialize the random number generator.
 * @return A float value representing a one-dimensional noise value.
 */
float SquirrelNoise::Get1dNoiseForRotation(int Rotation, uint32_t Seed)
	{
		constexpr unsigned int BIT_NOISE1 = 0xB5297A4D;
		constexpr unsigned int BIT_NOISE2 = 0x68E31DA4;
		constexpr unsigned int BIT_NOISE3 = 0x1B56C4E9;

		unsigned int mangled = (uint32_t)Rotation;
		mangled *= BIT_NOISE1;
		mangled += Seed;
		mangled ^= (mangled >> 8);
		mangled += BIT_NOISE2;
		mangled ^= (mangled << 8);
		mangled *= BIT_NOISE3;
		mangled ^= (mangled >> 8);

		return (float)std::clamp(mangled, 1u, ONE_OVER_MAX_UINT);
	}

}

