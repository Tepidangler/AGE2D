#pragma once
#include "Core/Public/Core.h"


namespace AGE
{
	namespace Utils
	{
		class EngineStatics
		{
		public:
			static bool IsBigEndian(void)
			{
				union {
					uint32_t i;
					char c[4];
				} bint = { 0x01020304 };

				return bint.c[0] == 1;
			}

			template<typename T>
			static bool IsBitSet(T Num, T Pos)
			{
				T Mask = 1 << Pos;

				return (Num & Mask) != 0;
			}

			static std::string GetFilename(std::filesystem::path& Name)
			{
				return Name.replace_extension().filename().string();
			}
		};
	}
}