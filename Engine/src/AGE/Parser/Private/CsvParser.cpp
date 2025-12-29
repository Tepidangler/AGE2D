#include "AGEpch.hpp"
#include "Parser/Public/CsvParser.h"

namespace AGE
{
	template<typename T>
	std::pair<int, int> CSVParser::ParseFile(const std::string& FileName, std::vector<T>& OutVec)
	{
		std::vector<T> Values;
		rapidcsv::Document Doc(FileName, rapidcsv::LabelParams(0, 0));
		std::vector<std::string> ColumnNames = Doc.GetColumnNames();
		std::vector <std::string> RowNames = Doc.GetRowNames();

		
		for (auto CN : ColumnNames)
		{
			Values.clear();
			Values = Doc.GetColumn<T>(CN);
			for (auto V : Values)
			{
				OutVec.push_back(V);
			}
		}

		return std::pair<int,int>((OutVec.size() / ColumnNames.size()), (OutVec.size()/RowNames.size()));

	}

	template<>
	std::pair<int, int> CSVParser::ParseFile(const std::string& FileName, std::vector<float>& OutVec)
	{
		std::vector<float> Values;
		rapidcsv::Document Doc(FileName, rapidcsv::LabelParams(0, 0));
		std::vector<std::string> ColumnNames = Doc.GetColumnNames();
		std::vector <std::string> RowNames = Doc.GetRowNames();


		for (auto CN : ColumnNames)
		{
			Values.clear();
			Values = Doc.GetColumn<float>(CN);
			for (auto V : Values)
			{
				OutVec.push_back(V);
			}
		}

		return std::pair<int, int>((int)ColumnNames.size(), (int)RowNames.size());

	}
}