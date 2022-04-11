#ifndef SQLBACKUP_H_
#define SQLBACKUP_H_

#include "CmdLineOptionParser.h"

namespace ftp {

	/**
	 * Class to manage the entire workflow in a project.
	 */
	class SQLBackup
	{
	public:
		SQLBackup();
		
		/**
		 * Creates data for a SQLite database, and then exports the database data to a file 
		 * and sends the file to an FTP server.
		 * 
		 * \param argc argument count
		 * \param argv argument list
		 */
		void start(int argc, char* argv[]);

	private:
		void initArgParser();

		CmdLineOptionParser cmdParser_;
	};

} // end namespace ftp
#endif // SQLBACKUP_H_