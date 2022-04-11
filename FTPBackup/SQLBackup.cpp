#include "SQLBackup.h"

#include "Logger.h"
#include "DbManager.h"
#include "FTPManager.h"
#include "QueryCollection.h"

#include <ctime>
#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace ftp {

	SQLBackup::SQLBackup()
	{
		initArgParser();
	}

	std::string getDateTime()
	{
		time_t rawtime;
		char buffer[80];
		
		time(&rawtime);
		struct tm timeInfo;
		localtime_s(&timeInfo, &rawtime);
		
		strftime(buffer, 80, "%d-%m-%Y-%H-%M-%S", &timeInfo);
		return std::string(buffer);
	}

	void SQLBackup::start(int argc, char* argv[])
	{
		//
		Logger::info("SQLBackup", "backup start");

		int port;
		std::string host, uname, passwd, dirPath;

		//
		Logger::info("SQLBackup", "parse cmdline options and get");

		try {
			cmdParser_.parseArgs(argc, argv);

			// throws exception if key not found
			port = cmdParser_.getIntOptionValue("--ftp_port");
			host = cmdParser_.getStringOptionValue("--ftp_host");
			uname = cmdParser_.getStringOptionValue("--ftp_uname");
			passwd = cmdParser_.getStringOptionValue("--ftp_passwd");
			dirPath = cmdParser_.getStringOptionValue("--ftp_dir");
		}
		catch (std::exception e)
		{
			Logger::error("CmdLineOptionParser", e.what());
			cmdParser_.printHelp();
			return;
		}

		//
		Logger::info("SQLBackup", "create DB and fill data");

		std::string dbFile = "Backup_" + getDateTime();

		bool isOk = false;
		std::string errorMsg = "";
		
		// create db and fill 
		isOk = dbmgr::init(dbFile, errorMsg);
		if (!isOk)
		{
			Logger::error("DbManager", errorMsg);
			return;
		}

		isOk = dbmgr::createTable(query::createTable, errorMsg);
		if (!isOk)
		{
			Logger::error("DbManager", errorMsg);
			return;
		}

		isOk = dbmgr::insertData(query::insertData, errorMsg);
		if (!isOk)
		{
			Logger::error("DbManager", errorMsg);
			return;
		}
		
		// select data from db and dump to file
		dbmgr::TableData data = dbmgr::selectData(query::selectData, errorMsg);
		if (data.isEmptty())
		{
			Logger::error("DbManager", "empty selected data");
			return;
		}

		std::string dumpFile = dbFile + ".txt";

		//
		Logger::info("SQLBackup", "dump the DB content to the " + dumpFile + " file");

		data.dumpToFile(dumpFile);

		//
		Logger::info("SQLBackup", "transfer " + dumpFile + " file to the FTP server");

		// transfer new created file to FTP server
		FTPManager ftpMgr(port, host, uname, passwd, dirPath);
		ftpMgr.startSession();

		std::string absolutePath = std::filesystem::absolute(std::filesystem::path(dumpFile)).string();
		if (!ftpMgr.transfer(absolutePath, "mytest1.txt"))
		{
			Logger::error("FTPManager", ftpMgr.getErrorMsg());
		}

		if (!ftpMgr.transfer(absolutePath, "mytest2.txt"))
		{
			Logger::error("FTPManager", ftpMgr.getErrorMsg());
		}

		Logger::info("SQLBackup", "successfully transferred to the server");
	}

	void SQLBackup::initArgParser()
	{
		cmdParser_.addOption("--ftp_host", "Flag to specify the backup FTP server's host.");
		cmdParser_.addOption("--ftp_port", "Flag to specify the backup FTP server's port");
		cmdParser_.addOption("--ftp_uname", "Flag to specify the backup FTP server's User name");
		cmdParser_.addOption("--ftp_passwd", "Flag to specify the backup FTP server's User password");
		cmdParser_.addOption("--ftp_dir", "Flag to specify the backup FTP server's copy directory");
	}

} // end namespace ftp
