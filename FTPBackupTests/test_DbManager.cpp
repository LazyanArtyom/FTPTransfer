#include "pch.h"
#include "../FTPBackup/DbManager.h"

	static std::string dbFile = "testFile";

TEST(DbManager, init) {
	// Arrange
	bool isOk = false;
	std::string errorMsg;

	// Act
	isOk = ftp::dbmgr::init(dbFile, errorMsg);

	// Assert
	ASSERT_EQ(isOk, true);
	ASSERT_TRUE(errorMsg.empty());
}

TEST(DbManager, createTable) {
	// Arrange
	bool isOk = false;
	std::string errorMsg;
	const std::string query =
		"CREATE TABLE IF NOT EXISTS MyTable("
		"ID INT PRIMARY KEY     NOT NULL, "
		"NAME           VARCHAR NOT NULL, "
		"AGE            INT     NOT NULL );";

	// Act
	isOk = ftp::dbmgr::createTable(query, errorMsg);

	// Assert
	ASSERT_EQ(isOk, true);
	ASSERT_TRUE(errorMsg.empty());
}

TEST(DbManager, insertData) {
	// Arrange
	bool isOk = false;
	std::string errorMsg;
	const std::string query =
		"INSERT INTO MyTable (ID,NAME,AGE) VALUES (1, 'AAAA', 11 ); "
		"INSERT INTO MyTable (ID,NAME,AGE) VALUES (2, 'BBBB', 22 ); ";

	// Act
	isOk = ftp::dbmgr::insertData(query, errorMsg);

	// Assert
	ASSERT_EQ(isOk, true);
	ASSERT_TRUE(errorMsg.empty());
}

TEST(DbManager, selectData) {
	// Arrange
	std::string errorMsg;
	const std::string query = "SELECT * FROM MyTable;";

	// Act
	ftp::dbmgr::TableData data = ftp::dbmgr::selectData(query, errorMsg);

	// Assert
	ASSERT_FALSE(data.isEmptty());
	ASSERT_TRUE(errorMsg.empty());
}

TEST(DbManager, removeDb) {
	// Arrange
	bool isOk = false;
	std::string errorMsg;

	// Act
	isOk = ftp::dbmgr::removeDb(dbFile, errorMsg);

	// Assert
	ASSERT_EQ(isOk, true);
	ASSERT_TRUE(errorMsg.empty());
}
