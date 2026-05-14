#pragma once
#include "Core/Public/Core.h"


namespace AGE
{
	namespace Utils
	{
		class EngineStatics
		{
		public:
			/**
 * @brief This function checks if the system is big endian or not.
 *
 * It does this by creating a union that contains an unsigned integer and four characters. The integer is initialized with a value of 0x01020304. If the first character in the union (c[0]) equals to 1, then it means that the system is little endian. Otherwise, it's big endian.
 *
 * @return Returns true if the system is big endian and false otherwise.
 */
/**
 * @brief This function checks if the system is big endian or not.
 * 
 * The function uses a union to create an instance of a uint32_t and a char array. It then assigns the value 0x01020304 to the uint32_t member, which represents the bytes in memory as 01 02 03 04.
 * The function returns true if the first byte of this union (representing the most significant byte) is equal to 1, indicating a big endian system. Otherwise, it returns false.
 * 
 * @return bool - Returns true if the system is big endian, false otherwise.
 */
static bool IsBigEndian(void)
			{
				union {
					uint32_t i;
					char c[4];
				} bint = { 0x01020304 };

				return bint.c[0] == 1;
			}

			template<typename T>
			/**
 * @brief This function checks if a specific bit is set in the given number.
 *
 * @param Num The number to check for the bit being set.
 * @param Pos The position of the bit to be checked, starting from 0 at the least significant bit.
 * @return True if the specified bit is set (i.e., equals 1), false otherwise.
 */
/**
 * @brief Checks if a specific bit is set in the given number.
 *
 * This function takes two parameters, Num and Pos. It creates a mask by shifting the value 1 to the left by 'Pos' places. Then it checks if any of the bits in the result are set in the binary representation of 'Num'. If so, it returns true; otherwise, false.
 *
 * @param[in] Num The number whose bit is being checked.
 * @param[in] Pos The position of the bit to check from least significant bit (LSB) onwards.
 * 
 * @return True if the specified bit in 'Num' is set, false otherwise.
 */
static bool IsBitSet(T Num, T Pos)
			{
				T Mask = 1 << Pos;

				return (Num & Mask) != 0;
			}

			/**
 * @brief This function returns the filename from a given filesystem path.
 * 
 * The function takes in a std::filesystem::path object and uses it to extract the filename by replacing any extension with an empty string, then returning the resultant filename as a std::string.
 * 
 * @param Name A reference to a std::filesystem::path object representing the path from which we want to extract the filename.
 * @return The function returns a std::string containing the name of the file represented by the input path, without any extension. If the provided path does not represent a valid file, an empty string is returned.
 */
/**
 * @brief This function returns the filename from a given filesystem path.
 * 
 * The function takes in a std::filesystem::path object and uses it to extract the filename by replacing any extension with an empty string, then returning the resultant filename as a std::string.
 * 
 * @param Name A reference to a std::filesystem::path object representing the path from which we want to extract the filename.
 * @return The function returns a std::string containing the filename extracted from the provided filesystem path.
 */
static std::string GetFilename(std::filesystem::path& Name)
			{
				return Name.replace_extension().filename().string();
			}
		};
	}
}