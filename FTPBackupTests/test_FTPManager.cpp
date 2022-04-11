#include "pch.h"
#include "../FTPBackup/FTPManager.h"

#include <fstream>
#include <filesystem>

ftp::FTPManager mgr(21, "127.0.0.1", "artyom", "1234", "testDir/testDir2");

TEST(FTPManagerTest, startSession) {
	EXPECT_EQ(mgr.startSession(), true) << "please look in the test file maybe you didn't set port, hots, uname, passwd or dirPath right\n";
	ASSERT_TRUE(mgr.getErrorMsg().empty());
}

TEST(FTPManagerTest, transfer) {
	// Arrange
	bool isOk = false;
	std::string dumpFile = "myTestFile.txt";

	// create new test file for transfer
	if (!std::filesystem::exists(dumpFile))
	{
		std::ofstream newFile(dumpFile);
		newFile.close();
	}
	std::string absolutePath = std::filesystem::absolute(std::filesystem::path(dumpFile)).string();

	// Act
	isOk = mgr.transfer(absolutePath, "newName.txt");

	std::filesystem::remove(dumpFile);

	// Assert
	ASSERT_EQ(isOk, true);
	ASSERT_TRUE(mgr.getErrorMsg().empty());
}

TEST(FTPManagerTest, endSession) {
	mgr.endSession();
	ASSERT_TRUE(mgr.getErrorMsg().empty());
}
