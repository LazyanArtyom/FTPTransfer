#ifndef FTP_FTPMANAGER_H_
#define FTP_FTPMANAGER_H_

#include <string>
#include <Windows.h>
#include <WinInet.h>

namespace ftp {
	
	/**
	 * Class to manage file transfer between Application and FTP Server.
	 */
	class FTPManager
	{
	public:
		FTPManager(int port, const std::string& host, const std::string& uname,
			const std::string& passwd, const std::string& dirPath);

		~FTPManager();

		/**
		 * Disconnects from the FTP server and from the session.
		 */
		void endSession();

		/**
		 * Establishes a connection with the FTP server and creates a directory dirPath _
		 * if not already created and starts a new session.
		 * 
		 * \return true if everything is ok 
		 */
		bool startSession();

		/**
		 * If one of the functions does not work correctly and there will be an error, 
		 * then each function returns false and assigns the current error to the errorMsg_ variable.
		 *  
		 * \return the current error message
		 */
		std::string getErrorMsg() const;

		/**
		 * Sends a file to specifed FTP Server directory.
		 * 
		 * \param localfilePath local absolute path of a file
		 * \param newremotefile new name of a file
		 * \return true if transfer was succsessful
		 */
		bool transfer(const std::string& localfilePath, const std::string& newRemotefile);

	private:
		bool setCurrentDir(const std::string& path);
		bool createDirIfNotExists(const std::string& path);

		int port_;
		std::string host_;
		std::string uname_;
		std::string passwd_;
		std::string dirPath_;
		std::string errorMsg_;

		HINTERNET session_ = nullptr;
		HINTERNET internet_ = nullptr;
	};

} // end namespace ftp
#endif // FTP_FTPMANAGER_H_