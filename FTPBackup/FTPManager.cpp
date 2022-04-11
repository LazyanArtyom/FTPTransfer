#pragma comment (lib, "WinInet.lib")
#pragma comment (lib, "urlmon")

#include "FTPManager.h"
#include "Logger.h"


namespace ftp {

	FTPManager::FTPManager(int port, const std::string& host, const std::string& uname, const std::string& passwd, const std::string& dirPath)
		: port_(port), host_(host), uname_(uname), passwd_(passwd), dirPath_(dirPath) {}

	FTPManager::~FTPManager()
	{
		endSession();
	}

	bool FTPManager::transfer(const std::string& localfilePath, const std::string& newRemoteFile)
	{
		if (!FtpPutFileA(session_, localfilePath.c_str(), newRemoteFile.c_str(), FTP_TRANSFER_TYPE_BINARY, 0))
		{
			errorMsg_ = "failed to send file";
			return false;
		}

		return true;
	}

	bool FTPManager::startSession()
	{
		internet_ = InternetOpen(nullptr, INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
		if (internet_ == nullptr)
		{
			errorMsg_ = "can't open internet";
			return false;
		}

		session_ = InternetConnectA(internet_, host_.c_str(), port_, uname_.c_str(), passwd_.c_str(), INTERNET_SERVICE_FTP, 0, 0);
		if (session_ == nullptr)
		{
			errorMsg_ = "can't connect to ftp server";
			return false;
		}

		if (!createDirIfNotExists(dirPath_))
		{
			return false;
		}

		if (!setCurrentDir(dirPath_))
		{
			errorMsg_ = "can't set current folder " + dirPath_;
			return false;
		}

		return true;
	}

	void FTPManager::endSession()
	{
		InternetCloseHandle(session_);
		InternetCloseHandle(internet_);

		session_ = nullptr;
		internet_ = nullptr;
	}

	std::string FTPManager::getErrorMsg() const
	{
		
		return errorMsg_;
	}

	bool FTPManager::createDirIfNotExists(const std::string& path)
	{
		if (!FtpCreateDirectoryA(session_, dirPath_.c_str()))
		{
			// if dir exists then return true
			if (GetLastError() == 12003)
			{
				return true;
			}

			errorMsg_ = "can't create folder " + path;
			return false;
		}

		return true;
	}

	bool FTPManager::setCurrentDir(const std::string& path)
	{
		return FtpSetCurrentDirectoryA(session_, path.c_str());
	}

} // end namespace ftp
