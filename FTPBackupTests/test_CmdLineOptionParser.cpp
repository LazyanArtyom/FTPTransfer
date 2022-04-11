#include "pch.h"
#include "../FTPBackup/CmdLineOptionParser.h"

ftp::CmdLineOptionParser cmdParser;

TEST(CmdLineOptionParser, addOption) {
	// Arrange
	cmdParser.addOption("--ftp_host", "");
	cmdParser.addOption("--ftp_port", "");

	// Assert
	ASSERT_FALSE(cmdParser.checkOption("incorrect"));
	ASSERT_TRUE(cmdParser.checkOption("--ftp_host"));
	ASSERT_TRUE(cmdParser.checkOption("--ftp_port"));
}

TEST(CmdLineOptionParser, parseArgs) {
	// Arrange
	int argc = 5;
	char* argv[] = {
		"/path/to/program",
		"--ftp_host",
		"127.0.0.1",
		"--ftp_port",
		"21"
	};

	// Act
	cmdParser.parseArgs(argc, argv);

	// Assert
	ASSERT_EQ(cmdParser.getIntOptionValue("--ftp_port"), 21);
	ASSERT_EQ(cmdParser.getStringOptionValue("--ftp_host"), "127.0.0.1");
}

TEST(CmdLineOptionParser, getIntOptionValue) {
	ASSERT_EQ(cmdParser.getIntOptionValue("--ftp_port"), 21);
}

TEST(CmdLineOptionParser, getStringOptionValue) {
	ASSERT_EQ(cmdParser.getStringOptionValue("--ftp_host"), "127.0.0.1");
}