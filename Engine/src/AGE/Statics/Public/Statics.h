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
static std::string GetFilename(std::filesystem::path& Name)
			{
				return Name.replace_extension().filename().string();
			}
		};
	}
}