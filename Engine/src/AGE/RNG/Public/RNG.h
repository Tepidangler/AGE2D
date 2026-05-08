#pragma once
#include "Core/Public/Core.h"

//Borrowed this from Squirrel Eiserloh
// Video for reference: https://www.youtube.com/watch?v=LWFzPP8ZbdU

namespace AGE
{
	class SquirrelNoise
	{
	public:

		SquirrelNoise();


		uint32_t Rand();
		//Squirrel Noise 3
		uint32_t Get1dNoiseUint(int Position, uint32_t Seed = 0);
		uint32_t Get2dNoiseUint(int PositionX, int PositionY, uint32_t Seed = 0);
		uint32_t Get3dNoiseUint(int PositionX, int PositionY, int PositionZ, uint32_t Seed = 0);
		uint32_t Get4dNoiseUint(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed = 0);

		//Same functions, mapped to floats in [0,1]
		float Get1dNoiseZeroToOne(int Position, uint32_t Seed = 0);
		float Get2dNoiseZeroToOne(int PositionX, int PositionY, uint32_t Seed = 0);
		float Get3dNoiseZeroToOne(int PositionX, int PositionY, int PositionZ, uint32_t Seed = 0);
		float Get4dNoiseZeroToOne(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed = 0);

		///Same Functions, mapped to floats in [-1,1]

		float Get1dNoiseNegOneToOne(int Position, uint32_t Seed = 0);
		float Get2dNoiseNegOneToOne(int PositionX, int PositionY, uint32_t Seed = 0);
		float Get3dNoiseNegOneToOne(int PositionX, int PositionY, int PositionZ, uint32_t Seed = 0);
		float Get4dNoiseNegOneToOne(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed = 0);

		///Same Functions, mapped to floats in [-180,180]
		float Get1dNoiseForRotation(int Rotation, uint32_t Seed = 0);

	private:

		int m_Position;

	};

	class SquirrelRNG
	{
	public:

		static void Init(uint32_t Seed = 0);

		//SRand-like (seed-related) methods
		/**
 * @brief Resets the seed and position for a pseudo-random number generator.
 * 
 * This function sets the global variables `s_Seed` and `s_Position` to the provided values. The new seed is used as the starting point for generating pseudo-random numbers, while the position indicates the current position in the sequence of generated numbers.
 *
 * @param Seed A 32-bit unsigned integer that will be used as the new seed value.
 * @param Position An optional parameter indicating the start position for generating pseudo-random numbers. Defaults to 0 if not provided.
 * @return void
 */
static void ResetSeed(uint32_t Seed, int Position = 0) 
		{	
			s_Seed = Seed; 
			s_Position = Position; 
		}

		/**
 * @brief This function returns the current seed value used for random number generation.
 * @return The current seed value as a uint32_t.
 */
static uint32_t GetSeed() { return s_Seed; }

		/**
 * @brief Sets the current position value.
 *
 * This function sets the 's_Position' variable to a new integer value provided as an argument. It does not return anything, so it is void.
 *
 * @param Position The new integer value that will be set for 's_Position'.
 */
static void SetCurrentPosition(int Position) { s_Position = Position; }

		/**
 * @brief This function returns the current position value stored in 's_Position'.
 * @return The integer value of the current position. If no such variable exists, it will return a default value of 0.
 */
static int GetCurrentPosition() { return s_Position; }

		//Rand-like (sequential random rolls) methods. Each one advances the RNG to it's next Position

		static uint32_t RollRandomUint32();

		static uint16_t RollRandomUint16();

		static uint8_t RollRandomByte();

		static uint32_t RollRandomIntLessThan(uint32_t MaxValueNotInclusive);
		static int RollRandomIntInRange(int MinValueInclusive, int MaxValueInclusive);
		static float RollRandomFloatZeroToOne();
		static float RollRandomFloatInRange(float MinValueInclusive, float MaxValueInclusive);
		static bool RollRandomChance(float ProbabilityofReturnTrue);
		static void RollRandomDirection2D(float& out_x, float& out_y);
		static float RollRandomRotationFloat();
		/** This can probably be of some use if you can figure out how. 
		void RollRandomDirection3D(float& out_x, float& out_y, float& out_z);
		*/

	private:

		static Scope<SquirrelNoise> s_NoiseObj;

		static uint32_t s_Seed;

		 static int s_Position;
		 static int s_Rotation;

	};

	
}