//
// Created by gdmgp on 12/5/2025.
//

#ifndef AGE2D_INIREADER_H
#define AGE2D_INIREADER_H
#include "Core/Public/Core.h"
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wmicrosoft-unqualified-friend"
#include "SimpleIni.h"
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#include "SimpleIni.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include "SimpleIni.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif

namespace AGE
{
	class IniReader
	{
	public:
		IniReader(const std::filesystem::path &Path);
		/**
 * @brief Destructor for the IniReader class.
 *
 * This function is responsible for freeing any resources that were allocated during the lifetime of an instance of this class.
 */
~IniReader() = default;

		std::string Read(const std::string &Section, const std::string &Key, bool& HasMultipleValues);

		std::vector<std::string> ReadAll(const std::string &Section, const std::string &Key);
	private:
		std::filesystem::path m_IniPath;
		CSimpleIniA m_Ini;
	};
} // AGE

#endif //AGE2D_INIREADER_H