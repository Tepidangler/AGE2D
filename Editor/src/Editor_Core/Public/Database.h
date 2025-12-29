//
// Created by De'Lano Wilcox on 11/22/2025.
//

#ifndef AGE_DATABASE_H
#define AGE_DATABASE_H

#endif //AGE_DATABASE_H

#pragma once
#include "Core/Public/Core.h"
#include <pqxx/pqxx>
namespace AGE
{
	enum class StatementType : uint8_t
	{
		CREATETABLE,
		SELECT,
		INSERT,
		UPDATE
	};
	class Database final
	{
	public:
		Database();
		~Database();

		std::vector<std::string> GetDatabaseNames();
		std::vector<std::string> GetTableNames(const std::string& DBName);
		std::vector<std::string> GetColumnNames(const std::string& DBName, const std::string& TableName);
		std::string GetPrimaryKey(const std::string& DBName, const std::string& TableName);

		bool Login(const std::string& Username, const std::string& Password, const std::string& Host, uint16_t PortNumber);

		bool ConnectToDatabase(const std::string& DBName, const std::string& Username, const std::string& Password, const std::string& Host, uint16_t PortNumber);

		bool IsConnectedToDB(const std::string& DBName);

		bool IsLoggedIn() {return bIsLoggedIn;}
		bool HasAnyOpenConnections();

		template<typename T>
		std::vector<T> GetTable(const std::string& TableName, const std::string& DBName);

		void AddPreppedStatement(const std::string& DBName, StatementType Type, const std::string& PreppedStatement);

		void MakePreparedStatements(const std::string& TableName);

		void ClearPreparedStatements(const std::string& DBName);

		void CreateTable(const std::string& DBName, const std::string& TableName,const std::vector<std::tuple<std::string,std::string,bool>>& Columns);

		template<typename T>
		void UpdateRow(const std::string& DBName, const std::string& TableName, const std::string& RowKey, const T& Data);

		template<typename T>
		void InsertRow(const std::string& DBName, const std::string& TableName, const T& Data);

	private:

	public:
		std::unordered_map<std::string, Ref<pqxx::connection>> m_Connections;
	private:
		std::unordered_map<std::string, std::vector<std::pair<StatementType, std::string>>> m_PreparedStatements;

		bool bIsLoggedIn = false;
	};


}
