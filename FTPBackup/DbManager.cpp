#include "DbManager.h"

#include "Logger.h"

#include <fstream>
#include <filesystem>
#include <winsqlite/winsqlite3.h>


namespace ftp::dbmgr {

	static std::string DB_PATH;
	static TableData SELECTED_RESULT;

	// static helpers
	static bool checkPath(const std::string& dbPath);
	static int callBack(void* NotUsed, int argc, char** argv, char** azColName);
	static bool exec(const std::string& query, int (*call)(void* NotUsed, int argc, char** argv, char** azColName), std::string& errorMsg);

	bool init(const std::string& dbPath, std::string& errorMsg)
	{
		sqlite3* db = nullptr;

		// if not exists
		if (!checkPath(dbPath))
		{
			std::ofstream newFile(dbPath);
			if (!newFile)
			{
				errorMsg = "could not create file " + dbPath;
				return false;
			}

			newFile.close();
		}

		DB_PATH = dbPath;

		int result = sqlite3_open(dbPath.c_str(), &db);
		if (SQLITE_OK != result)
		{
			errorMsg = std::string(sqlite3_errmsg(db));
			return false;
		}

		sqlite3_close(db);
		return true;
	}

	TableData selectData(const std::string& query, std::string& errorMsg)
	{
		SELECTED_RESULT.data.clear();

		if (exec(query, callBack, errorMsg))
		{
			return SELECTED_RESULT;
		}

		return TableData();
	}

	bool removeDb(const std::string& dbPath, std::string& errorMsg)
	{
		bool bOk = std::filesystem::remove(dbPath);
		if (!bOk)
		{
			errorMsg = "error removing " + dbPath;
		}

		return bOk;
	}

	bool insertData(const std::string& query, std::string& errorMsg)
	{
		return exec(query, nullptr, errorMsg);
	}

	bool createTable(const std::string& query, std::string& errorMsg)
	{
		return exec(query, nullptr, errorMsg);
	}

	// static helper functions
	static int callBack(void* NotUsed, int argc, char** argv, char** azColName)
	{
		SELECTED_RESULT.data.resize(argc);

		if (SELECTED_RESULT.data[0].empty())
		{
			for (int i = 0; i < argc; ++i)
			{
				SELECTED_RESULT.data[i].push_back(azColName[i]);
			}
		}

		std::cout << "\n";
		for (int i = 0; i < argc; ++i)
		{
			SELECTED_RESULT.data[i].push_back(argv[i]);
		}

		// success
		return 0;
	}

	static bool checkPath(const std::string& dbPath)
	{
		return std::filesystem::exists(dbPath);
	}

	static bool exec(const std::string& query, int (*call)(void* NotUsed, int argc, char** argv, char** azColName), std::string& errorMsg)
	{
		sqlite3* db = nullptr;

		if (query.empty())
		{
			errorMsg = "query is empty";
			return false;
		}

		if (!checkPath(DB_PATH))
		{
			errorMsg = DB_PATH + " does not exists. try to call Init() func at first";
			return false;
		}

		int result = sqlite3_open(DB_PATH.c_str(), &db);
		if (SQLITE_OK != result)
		{
			errorMsg = std::string(sqlite3_errmsg(db));
			return false;
		}

		char* execErrorMsg = nullptr;
		result = sqlite3_exec(db, query.c_str(), call, nullptr, &execErrorMsg);

		if (SQLITE_OK != result)
		{
			errorMsg = std::string(execErrorMsg);
			sqlite3_free(execErrorMsg);
			return false;
		}

		sqlite3_close(db);
		return true;
	}

	void TableData::print()
	{
		for (size_t i = 0; i < SELECTED_RESULT.data[0].size(); ++i)
		{
			size_t j = 0;
			for (; j < SELECTED_RESULT.data.size() - 1; ++j)
			{
				std::cout << SELECTED_RESULT.data[j][i] << ", ";
			}
			std::cout << SELECTED_RESULT.data[j][i] << std::endl;
		}
	}

	void TableData::dumpToFile(const std::string& filePath)
	{
		std::fstream out(filePath, std::ios_base::out);

		for (size_t i = 0; i < SELECTED_RESULT.data[0].size(); ++i)
		{
			size_t j = 0;
			for (; j < SELECTED_RESULT.data.size() - 1; ++j)
			{
				out << SELECTED_RESULT.data[j][i] << ",";
			}
			out << SELECTED_RESULT.data[j][i] << std::endl;
		}

		out.close();
	}

	bool TableData::isEmptty() const
	{
		return data.empty();
	}

}// end namespace dbmgr
