//
// Created by gdmgp on 12/5/2025.
//

#include "Core/Public/AGEpch.hpp"
#include "../Public/IniReader.h"
#include "Core/Public/Log.h"

namespace AGE
{
	IniReader::IniReader(const std::filesystem::path &Path)
		:m_IniPath(Path)
	{
		m_Ini.SetUnicode();

		SI_Error rc = m_Ini.LoadFile(Path.string().c_str());

		if (rc < 0)
		{
			CoreLogger::Error("Unable To Load {}", Path.string());
		}
	}

	std::string IniReader::Read(const std::string &Section, const std::string &Key, bool &HasMultipleValues)
	{
		std::string Result = "";

		Result =  m_Ini.GetValue(Section.c_str(),Key.c_str(),nullptr,&HasMultipleValues);

		if (Result.empty())
		{
			CoreLogger::Error("Unable To Read Value From Key {} in Section {}", Key, Section);
			return Result;
		}

		return Result;

	}

	std::vector<std::string> IniReader::ReadAll(const std::string &Section, const std::string &Key)
	{
		CSimpleIniA::TNamesDepend Values;
		std::vector<std::string> Results;

		m_Ini.GetAllValues(Section.c_str(),Key.c_str(),Values);

		if (Values.empty())
		{
			CoreLogger::Error("Unable To Read Values From Key {} in Section {}", Key, Section);
			return Results;
		}

		Values.sort(CSimpleIniA::Entry::LoadOrder());

		for (const auto& V : Values)
		{
			Results.emplace_back(V.pItem);
		}

		return Results;
	}

} // AGE