//
// Created by gdmgp on 12/5/2025.
//

#ifndef AGE2D_INIREADER_H
#define AGE2D_INIREADER_H
#include "Core/Public/Core.h"
#include "SimpleIni.h"

namespace AGE
{
	class IniReader
	{
	public:
		IniReader(const std::filesystem::path &Path);
		~IniReader() = default;

		std::string Read(const std::string &Section, const std::string &Key, bool& HasMultipleValues);

		std::vector<std::string> ReadAll(const std::string &Section, const std::string &Key);
	private:
		std::filesystem::path m_IniPath;
		CSimpleIniA m_Ini;
	};
} // AGE

#endif //AGE2D_INIREADER_H