#pragma once
#include "Core/Public/Core.h"
#include "nlohmann/json.hpp"

namespace AGE
{


	class JsonParser
	{
	public:

		JsonParser() = default;
		JsonParser(const std::string& FilePath);

		template<typename T>
		bool SaveJsonFile(const std::filesystem::path& Filepath, std::vector<T>& Data);

		static nlohmann::json LoadJsonFile(const std::filesystem::path& Filepath);

		static std::string Parse(const std::string& FilePath);

		static std::string ParseString(const std::string& String);

	};



}