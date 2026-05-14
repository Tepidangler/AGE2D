#include "AGEpch.hpp"
#include "Parser/Public/CsvParser.h"

namespace AGE
{
	template<typename T>
	/**
 * @brief Parses a CSV file and stores the values in an output vector.
 *
 * This function reads a CSV file specified by its filename, extracts all column names 
 * and row names from it using rapidcsv library. It then iterates over each column, 
 * retrieving the values of that column into a temporary vector. These values are then 
 * pushed back to the output vector. The function finally returns a pair of integers where 
 * the first element is the average number of elements per column and the second one is 
 * the average number of elements per row in the CSV file.
 *
 * @param FileName A constant string reference representing the name of the CSV file to be parsed.
 * @param OutVec An output vector where all values from the CSV file will be stored.
 * @return A pair of integers, where the first element is the average number of elements per column 
 * and the second one is the average number of elements per row in the CSV file.
 */
/**
 * @brief Parses a CSV file and stores the values in an output vector.
 *
 * This function reads a CSV file specified by its filename, extracts all column names 
 * and row names from it using rapidcsv library. It then iterates over each column, 
 * retrieving the corresponding values of type T (template parameter), and pushes them 
 * into the output vector. The function finally returns a pair of integers representing 
 * the average number of elements per column and row in the CSV file.
 *
 * @param FileName A constant string reference to the filename of the CSV file to be parsed.
 * @param OutVec An output vector where the values from the CSV file will be stored.
 * 
 * @return A pair of integers representing the average number of elements per column and row in the CSV file.
 */
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
	/**
 * @brief Parses a CSV file and stores the values in an output vector.
 *
 * This function reads a CSV file specified by its filename, extracts all column names 
 * and row names from it using rapidcsv library, then iterates over each column to get 
 * its values as floats. These float values are pushed back into the provided output vector.
 * The number of columns and rows in the CSV file is returned as a pair.
 *
 * @param FileName A constant string reference representing the filename of the CSV file to be parsed.
 * @param OutVec A reference to an output vector where the extracted float values will be stored.
 * 
 * @return A pair of integers, where the first integer represents the number of columns in the CSV file and the second integer represents the number of rows.
 */
/**
 * @brief Parses a CSV file and stores the values in an output vector.
 * 
 * This function reads a CSV file specified by its filename, extracts all column names and row names from it using rapidcsv library. It then iterates over each column, retrieving the values as floats and pushing them into the provided output vector. The number of columns and rows in the CSV file are returned as a pair.
 * 
 * @param FileName A constant string reference representing the filename of the CSV file to be parsed.
 * @param OutVec A vector of floats that will store all values from the CSV file.
 * @return A pair of integers, where the first value is the number of columns in the CSV file and the second value is the number of rows.
 */
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