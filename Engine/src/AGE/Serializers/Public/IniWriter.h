//
// Created by gdmgp on 12/5/2025.
//

#ifndef AGE2D_INIWRITER_H
#define AGE2D_INIWRITER_H
#include "Core/Public/Core.h"
#include "SimpleIni.h"

namespace AGE
{
	class IniWriter
	{
	public:
		IniWriter(const std::filesystem::path &Path);
		~IniWriter() = default;

		bool Write(const std::string &Section, const std::string &Key, const std::string &Value);

		bool SaveFile();



	private:
		std::filesystem::path m_IniPath;
		CSimpleIniA m_Ini;
	};


} // AGE

#endif //AGE2D_INIWRITER_H