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

	void SquirrelRNG::Init(uint32_t Seed)
	{
		s_Seed = Seed;
		s_Position = 0;
		s_Rotation = 0;
		s_NoiseObj = CreateScope<SquirrelNoise>();
	}

	uint32_t SquirrelRNG::RollRandomUint32()
	{
		return 0;
	}

	uint16_t SquirrelRNG::RollRandomUint16()
	{
		return 0;
	}

	uint8_t SquirrelRNG::RollRandomByte()
	{
		return 0;
	}

	uint32_t SquirrelRNG::RollRandomIntLessThan(uint32_t MaxValueNotInclusive)
	{
		return 0;
	}

	int SquirrelRNG::RollRandomIntInRange(int MinValueInclusive, int MaxValueInclusive)
	{
		return 0;
	}

	float SquirrelRNG::RollRandomFloatZeroToOne()
	{
		return SquirrelRNG::s_NoiseObj->Get1dNoiseZeroToOne(SquirrelRNG::s_Position++, s_Seed);
	}

	float SquirrelRNG::RollRandomFloatInRange(float MinValueInclusive, float MaxValueInclusive)
	{

		// THis implementation is likely always going to return the min value. TODO: Fix to return numbers within the range including the max
		return MinValueInclusive + (MaxValueInclusive - MinValueInclusive) * SquirrelRNG::s_NoiseObj->Get1dNoiseZeroToOne(s_Position++, s_Seed);
	}

	bool SquirrelRNG::RollRandomChance(float ProbabilityofReturnTrue)
	{
		return false;
	}

	void SquirrelRNG::RollRandomDirection2D(float& out_x, float& out_y)
	{
		out_x = s_NoiseObj->Get2dNoiseZeroToOne(s_Position, s_Position, s_Seed);
		out_y = s_NoiseObj->Get2dNoiseZeroToOne(s_Position, s_Position + 1, s_Seed);
	}

	float SquirrelRNG::RollRandomRotationFloat()
	{
		return (float)s_NoiseObj->Get1dNoiseUint(s_Rotation++, s_Seed);
	}

	SquirrelNoise::SquirrelNoise()
	{
		m_Position = 0;
	}


	uint32_t SquirrelNoise::Rand()
	{
		return Get1dNoiseUint(m_Position++);
	}

	uint32_t SquirrelNoise::Get1dNoiseUint(int Position, uint32_t Seed)
	{
		constexpr unsigned int BIT_NOISE1 = 0xB5297A4D;
		constexpr unsigned int BIT_NOISE2 = 0x68E31DA4;
		constexpr unsigned int BIT_NOISE3 = 0x1B56C4E9;

		unsigned int mangled = Position;
		mangled *= BIT_NOISE1;
		mangled += Seed;
		mangled ^= (mangled >> 8);
		mangled += BIT_NOISE2;
		mangled ^= (mangled << 8);
		mangled *= BIT_NOISE3;
		mangled ^= (mangled >> 8);

		return mangled;
	}
	uint32_t SquirrelNoise::Get2dNoiseUint(int PositionX, int PositionY, uint32_t Seed)
	{
		constexpr int PRIME_NUMBER = 198491317;
		return Get1dNoiseUint(PositionX + (PRIME_NUMBER * PositionY), Seed);
	}
	uint32_t SquirrelNoise::Get3dNoiseUint(int PositionX, int PositionY, int PositionZ, uint32_t Seed)
	{
		constexpr int PRIME_NUMBER1 = 198491317;
		constexpr int PRIME_NUMBER2 = 6542989;
		return Get1dNoiseUint(PositionX + (PRIME_NUMBER1 * PositionY) + (PRIME_NUMBER2 * PositionZ), Seed);
	}
	uint32_t SquirrelNoise::Get4dNoiseUint(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed)
	{
		constexpr int PRIME_NUMBER1 = 198491317;
		constexpr int PRIME_NUMBER2 = 6542989;
		constexpr int PRIME_NUMBER3 = 73939;
		return Get1dNoiseUint(PositionX + (PRIME_NUMBER1 * PositionY) + (PRIME_NUMBER2 * PositionZ) + (PRIME_NUMBER3 * PositionW), Seed);
	}

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

	float SquirrelNoise::Get2dNoiseZeroToOne(int PositionX, int PositionY, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER = 198491317;
		return (float)(ONE_OVER_MAX_UINT * Get2dNoiseUint(PositionX,PositionY, Seed));
	}

	float SquirrelNoise::Get3dNoiseZeroToOne(int PositionX, int PositionY, int PositionZ, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER1 = 198491317;
		//constexpr int PRIME_NUMBER2 = 6542989;
		return (float)(ONE_OVER_MAX_UINT * Get3dNoiseUint(PositionX, PositionY, Seed));
	}

	float SquirrelNoise::Get4dNoiseZeroToOne(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER1 = 198491317;
		//constexpr int PRIME_NUMBER2 = 6542989;
		//constexpr int PRIME_NUMBER3 = 73939;
		return (float)(ONE_OVER_MAX_UINT * Get4dNoiseUint(PositionX, PositionY, PositionZ, PositionW, Seed));
	}

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

	float SquirrelNoise::Get2dNoiseNegOneToOne(int PositionX, int PositionY, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER = 198491317;
		return (float)(ONE_OVER_MAX_INT * Get2dNoiseUint(PositionX, PositionY, Seed));
	}

	float SquirrelNoise::Get3dNoiseNegOneToOne(int PositionX, int PositionY, int PositionZ, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER1 = 198491317;
		//constexpr int PRIME_NUMBER2 = 6542989;
		return (float)(ONE_OVER_MAX_INT * Get3dNoiseUint(PositionX, PositionY, Seed));
	}

	float SquirrelNoise::Get4dNoiseNegOneToOne(int PositionX, int PositionY, int PositionZ, int PositionW, uint32_t Seed)
	{
		//constexpr int PRIME_NUMBER1 = 198491317;
		//constexpr int PRIME_NUMBER2 = 6542989;
		//constexpr int PRIME_NUMBER3 = 73939;
		return (float)(ONE_OVER_MAX_INT * Get4dNoiseUint(PositionX, PositionY, PositionZ, PositionW, Seed));
	}
	

	float SquirrelNoise::Get1dNoiseForRotation(int Rotation, uint32_t Seed)
	{
		constexpr unsigned int BIT_NOISE1 = 0xB5297A4D;
		constexpr unsigned int BIT_NOISE2 = 0x68E31DA4;
		constexpr unsigned int BIT_NOISE3 = 0x1B56C4E9;

		unsigned int mangled = Rotation;
		mangled *= BIT_NOISE1;
		mangled += Seed;
		mangled ^= (mangled >> 8);
		mangled += BIT_NOISE2;
		mangled ^= (mangled << 8);
		mangled *= BIT_NOISE3;
		mangled ^= (mangled >> 8);

		return (float)std::clamp(mangled, ONE_OVER_MIN_UINT, ONE_OVER_MAX_UINT);
	}

}

