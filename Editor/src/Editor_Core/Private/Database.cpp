//
// Created by De'Lano Wilcox on 11/22/2025.
//
#include "Core/Public/AGEpch.hpp"
#include "Editor_Core/Public/Database.h"
#include "GameFramework/GameStructs/Public/GameStructs.h"
#include "Core/Public/Log.h"
#include <string>

#include "Core/Public/Keycodes.h"

#include "glm/gtc/matrix_access.hpp"

namespace AGE
{
	Database::Database()
	{
	}

	Database::~Database()
	{
		for (auto C : m_Connections)
		{
			C.second->close();
		}
	}

	std::vector<std::string> Database::GetDatabaseNames()
	{
		if (bIsLoggedIn)
		{
			std::vector<std::string> DBNames;
			pqxx::work Work(*m_Connections.at("NoDB"));

			pqxx::result DBs = Work.exec("SELECT datname FROM pg_database WHERE datistemplate = false;");
			for (auto R : DBs)
			{
				DBNames.emplace_back(R["datname"].as<std::string>());
			}
			Work.commit();
			return DBNames;
		}

		CoreLogger::Error("No user was not logged in when attempting to get Database Names!\nReturning empty container!");

		return {};
	}

	std::vector<std::string> Database::GetTableNames(const std::string& DBName)
	{
		if (bIsLoggedIn)
		{
			std::vector<std::string> TableNames;
			pqxx::work Work(*m_Connections.at(DBName));

			pqxx::result Tables = Work.exec("SELECT table_schema, table_name FROM information_schema.tables WHERE table_schema NOT IN ('pg_catalog', 'information_schema') AND table_type = 'BASE TABLE' ORDER BY table_schema, table_name;");
			for (auto R : Tables)
			{
				TableNames.emplace_back(R["table_name"].as<std::string>());
			}
			Work.commit();
			return TableNames;
		}
		CoreLogger::Error("No user was not logged in when attempting to get Table Names!\nReturning empty container!");
		return {};
	}

	std::vector<std::string> Database::GetColumnNames(const std::string &DBName, const std::string &TableName)
	{
		if (bIsLoggedIn)
		{
			std::vector<std::string> ColumnNames;
			pqxx::work Work(*m_Connections.at(DBName));

			std::string Query = std::vformat("SELECT column_name, data_type FROM information_schema.columns WHERE table_schema = '{}' AND table_name = '{}';", std::make_format_args("public", TableName));
			pqxx::result Columns = Work.exec(Query.c_str());
			for (auto R : Columns)
			{
				ColumnNames.emplace_back(R["column_name"].as<std::string>());
			}
			Work.commit();
			return ColumnNames;
		}
		CoreLogger::Error("No user was not logged in when attempting to get Column Names!\nReturning empty container!");
		return {};
	}

	std::string Database::GetPrimaryKey(const std::string &DBName, const std::string &TableName)
	{
		if (bIsLoggedIn)
		{
			std::vector<std::string> PrimaryKeys;
			pqxx::work Work(*m_Connections.at(DBName));

			std::string Query = std::vformat("SELECT kcu.column_name FROM information_schema.table_constraints AS tc JOIN information_schema.key_column_usage AS kcu ON tc.constraint_name = kcu.constraint_name AND tc.table_schema = kcu.table_schema AND tc.table_name = kcu.table_name WHERE tc.constraint_type = 'PRIMARY KEY' AND tc.table_name = '{}';", std::make_format_args(TableName));
			pqxx::result Keys = Work.exec(Query.c_str());
			for (auto R : Keys)
			{
				PrimaryKeys.emplace_back(R[0].as<std::string>());
			}
			//Work.commit();
			return PrimaryKeys.front();
		}
		CoreLogger::Error("No user was not logged in when attempting to get Column Names!\nReturning empty container!");
		return {};
	}

	bool Database::Login(const std::string& Username, const std::string& Password, const std::string& Host, uint16_t PortNumber)
	{
		const std::string ConnectionString = std::vformat("user= {} password= {} host= {} port= {}", std::make_format_args(Username, Password,Host, PortNumber));
		m_Connections.emplace("NoDB", CreateRef<pqxx::connection>(ConnectionString));
		if (m_Connections.at("NoDB")->is_open())
		{
			bIsLoggedIn = true;
		}
		else
		{
			bIsLoggedIn = false;
		}
		return bIsLoggedIn;
	}

	bool Database::ConnectToDatabase(const std::string &DBName, const std::string& Username, const std::string& Password, const std::string& Host, uint16_t PortNumber)
	{
		bool Connected = false;
		const std::string ConnectionString = std::vformat("dbname= {} user= {} password= {} host= {} port= {}", std::make_format_args( DBName, Username, Password, Host, PortNumber));
		m_Connections.emplace(DBName, CreateRef<pqxx::connection>(ConnectionString));
		if (m_Connections.at(DBName)->is_open())
		{
			Connected = true;
		}
		else
		{
			Connected = false;
		}
		return Connected;
	}

	bool Database::IsConnectedToDB(const std::string& DBName)
	{
		return m_Connections.contains(DBName);
	}

	bool Database::HasAnyOpenConnections()
	{
		for (auto C : m_Connections)
		{
			if (C.second->is_open())
			{
				return true;
			}
		}
		return false;
	}

	void Database::AddPreppedStatement(const std::string &DBName, StatementType Type,
		const std::string &PreppedStatement)
	{
		m_PreparedStatements[DBName].emplace_back(std::make_pair(Type, PreppedStatement));
	}

	void Database::MakePreparedStatements(const std::string& TableName)
	{
		for (auto& KV : m_PreparedStatements)
		{
			for (auto& SP : KV.second)
			{
				switch (SP.first)
				{
					case StatementType::UPDATE:
					{
						m_Connections.at(KV.first)->prepare(std::format("{}_Update", TableName),SP.second);
						break;
					}
					case StatementType::INSERT:
					{
						m_Connections.at(KV.first)->prepare(std::format("{}_Insert",TableName),SP.second);
						break;
					}
					case StatementType::CREATETABLE:
					{
						m_Connections.at(KV.first)->prepare(SP.second);
						break;
					}
				}
			}
		}
	}

	void Database::ClearPreparedStatements(const std::string& DBName)
	{
		m_PreparedStatements.at(DBName).clear();
	}

	void Database::CreateTable(const std::string &DBName, const std::string &TableName, const std::vector<std::tuple<std::string,std::string,bool>>& Columns)
	{
		pqxx::transaction<> txn(*m_Connections.at(DBName));

		std::string Query = std::vformat("CREATE TABLE \"{}\"(\n", std::make_format_args(TableName));

		for (int i =0; i < Columns.size(); i++)
		{
			if (i == Columns.size() - 1)
			{
				if (std::get<2>(Columns[i]))
				{
					Query += std::format("\"{}\" {} PRIMARY KEY\n", std::get<0>(Columns[i]), std::get<1>(Columns[i]));
					continue;
				}
				Query += std::format("\"{}\" {}\n", std::get<0>(Columns[i]), std::get<1>(Columns[i]));
				continue;
			}
			if (std::get<2>(Columns[i]))
			{
				Query += std::format("\"{}\" {} PRIMARY KEY,\n", std::get<0>(Columns[i]), std::get<1>(Columns[i]));
				continue;
			}
			Query += std::format("\"{}\" {},\n", std::get<0>(Columns[i]), std::get<1>(Columns[i]));
		}
		Query += ");";

		pqxx::result Result = txn.exec(Query);
		txn.commit();


	}

	template<>
	std::vector<GameFramework::EnemyStats> Database::GetTable(const std::string &TableName, const std::string& DBName)
	{
		pqxx::transaction<> txn(*m_Connections.at(DBName));

		std::string Query = std::vformat("SELECT * FROM  \"{}\"", std::make_format_args(TableName));
		std::vector<GameFramework::EnemyStats> Fields;
		pqxx::result r = txn.exec(Query);
		size_t row = std::size(r);

		for (int i = 0; i < row; i++)
		{
			pqxx::row const Entry = r[i];
			GameFramework::EnemyStats Stats;
			Stats.HP = Entry["\"HP\""].as<uint32_t>();
			Stats.MP = Entry["\"MP\""].as<uint32_t>();
			Stats.Strength = Entry["\"Strength\""].as<uint32_t>();
			Stats.MagicAttack = Entry["\"MagicAttack\""].as<uint32_t>();
			Stats.Attack = Entry["\"Attack\""].as<uint32_t>();
			Stats.Defense = Entry["\"Defense\""].as<uint32_t>();
			Stats.Agility = Entry["\"Agility\""].as<uint32_t>();
			Stats.Speed = Entry["\"Speed\""].as<uint32_t>();
			Stats.Name = Entry["\"Name\""].as<std::string>();
			pqxx::array<uint16_t> Abs = Entry["\"Absorb\""].as_sql_array<uint16_t>();
			for (int i =0; i < Abs.size(); i++)
			{
				Stats.Absorb.emplace_back(Abs[i]);
			}
			pqxx::array<uint16_t> Red = Entry["\"Reduce\""].as_sql_array<uint16_t>();
			for (int i =0; i < Red.size(); i++)
			{
				Stats.Reduce.emplace_back(Red[i]);
			}
			pqxx::array<uint16_t> Weakness = Entry["\"Weak\""].as_sql_array<uint16_t>();
			for (int i =0; i < Weakness.size(); i++)
			{
				Stats.Weak.emplace_back(Weakness[i]);
			}

			Fields.emplace_back(Stats);
		}
		txn.commit();
		return Fields;

	}

	template<>
	void Database::UpdateRow<GameFramework::EnemyStats>(const std::string& DBName, const std::string& TableName, const std::string &RowKey, const GameFramework::EnemyStats &Data)
	{
		pqxx::transaction<> txn(*m_Connections.at(DBName));
		txn.exec(pqxx::prepped{std::format("{}_Update", TableName).c_str()}, pqxx::params{Data.HP, Data.MP, Data.Strength, Data.MagicAttack, Data.Attack, Data.Defense, Data.Agility, Data.Speed, "{1}", "{2}", "{3}", Data.Name, Data.Name});
		txn.commit();
		CoreLogger::Trace("Row Successfully Updated!");
	}

	template<>
	void Database::InsertRow<GameFramework::EnemyStats>(const std::string &DBName, const std::string& TableName,const GameFramework::EnemyStats &Data)
	{
		pqxx::transaction<> txn(*m_Connections.at(DBName));
		txn.exec(pqxx::prepped{std::format("{}_Insert", TableName).c_str()}, pqxx::params{Data.HP, Data.MP, Data.Strength, Data.MagicAttack, Data.Attack, Data.Defense, Data.Agility, Data.Speed, "{1}", "{2}", "{3}", Data.Name});
		txn.commit();
		CoreLogger::Trace("Row Successfully added!");
	}
}

#include "spdlog/fmt/bundled/compile.h"
