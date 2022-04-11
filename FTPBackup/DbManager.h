#ifndef FTP_DBMANAGER_H_
#define FTP_DBMANAGER_H_

#include <string>
#include <vector>
#include <sqlite3.h>
#include <filesystem>

namespace ftp::dbmgr {

	/**
	 * Class container which holds the data that is returned from db.
	 */
	class TableData
	{
	public:
		void print();
		void dumpToFile(const std::string& filePath);
		bool isEmptty() const;

		std::vector<std::vector<std::string>> data;
	};

	/**
	 * Creates a database at the given path.
	 * 
	 * \param dbPath path to database
	 * \param errorMsg if an error occurs then the error text is assigned to this variable
	 * \return true if there is no errors
	 */
	bool init(const std::string& dbPath, std::string& errorMsg);

	/**
	 * Adds data to the database according to the given query.
	 * 
	 * \param errorMsg if an error occurs then the error text is assigned to this variable
	 * \return true if there is no errors
	 */
	bool insertData(const std::string& query, std::string& errorMsg);

	/**
	 * Creates a table in the database according to the given query.
	 * 
	 * \param errorMsg if an error occurs then the error text is assigned to this variable
	 * \return true if there is no errors
	 */
	bool createTable(const std::string& query, std::string& errorMsg);

	/**
	 * Fetches data from the database
	 * 
	 * \param errorMsg if an error occurs then the error text is assigned to this variable
	 */
	TableData selectData(const std::string& query, std::string& errorMsg);

	/**
	 * Removes a database at the given path.
	 * 
	 * \param dbPath path to database
	 * \param errorMsg if an error occurs then the error text is assigned to this variable
	 * \return true if there is no errors
	 */
	bool removeDb(const std::string& dbPath, std::string& errorMsg);

} // end namespace dbmgr
#endif // FTP_LOGGER_H_
