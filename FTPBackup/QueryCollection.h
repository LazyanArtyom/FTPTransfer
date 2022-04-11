#ifndef FTP_QUERYCOLLECTION_H_
#define FTP_QUERYCOLLECTION_H_

#include <string>

namespace ftp::query {

	const std::string createTable = 
		"CREATE TABLE IF NOT EXISTS Person("
		"ID INT PRIMARY KEY     NOT NULL, "
		"NAME           VARCHAR NOT NULL, "
		"AGE            INT     NOT NULL, "
		"ADDRESS        VARCHAR, "
		"SALARY         REAL );";

	const std::string insertData =
		"INSERT INTO Person (ID,NAME,AGE,ADDRESS,SALARY) VALUES (1, 'AAAA', 11, 'Armenia', 10000 ); "
		"INSERT INTO Person (ID,NAME,AGE,ADDRESS,SALARY) VALUES (2, 'BBBB', 22, 'Germany', 20000 ); "
		"INSERT INTO Person (ID,NAME,AGE,ADDRESS,SALARY) VALUES (3, 'CCCC', 33, 'France', 30000 ); "
		"INSERT INTO Person (ID,NAME,AGE,ADDRESS,SALARY) VALUES (4, 'DDDD', 44, 'USA', 40000 ); "
		"INSERT INTO Person (ID,NAME,AGE,ADDRESS,SALARY) VALUES (5, 'EEEE', 55, 'UK', 500000 ); ";

	const std::string selectData = "SELECT * FROM Person;";

}// end namespace ftp::query
#endif // FTP_QUERYCOLLECTION_H_
