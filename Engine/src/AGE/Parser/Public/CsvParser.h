#pragma once
#include "rapidcsv.h"

namespace AGE
{
	class CSVParser
	{
	public:
		template<typename T>
		//Parses a CSV file storing all of the values in a vector by column, returning the number of columns and rows in the csv File
		//It's on the user to know what order this data will be retrieved in and do whatever they like with the data
		static std::pair<int,int> ParseFile(const std::string& FileName, std::vector<T>& OutVec);

	private:

	};
}