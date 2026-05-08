//
// Created by gdmgp on 12/5/2025.
//

#ifndef AGE2D_INIWRITER_H
#define AGE2D_INIWRITER_H
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
	class IniWriter
	{
	public:
		IniWriter(const std::filesystem::path &Path);
		/**
 * @brief Destructor for the IniWriter class.
 *
 * This function is responsible for releasing any resources that were acquired by the IniWriter object, such as memory or file handles. It does not return anything and has no parameters.
 */
~IniWriter() = default;

		bool Write(const std::string &Section, const std::string &Key, const std::string &Value);

		bool SaveFile();



	private:
		std::filesystem::path m_IniPath;
		CSimpleIniA m_Ini;
	};


} // AGE

#endif //AGE2D_INIWRITER_H