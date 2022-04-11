#include "CmdLineOptionParser.h"
#include "Logger.h"

#include <iostream>
#include <string.h>
#include <filesystem>

namespace ftp {

	void CmdLineOptionParser::parseArgs(int argc, char* argv[])
	{
		if (argc == 1)
		{
			Logger::error("CmdLineOptionParser", "you must specify options.");
			printHelp();
			exit(EXIT_FAILURE);
		}

		for (int i = 1; i < argc; i++) 
		{
			if (checkOption(argv[i])) 
			{
				if (argc < i + 1)
				{
					break;
				}

				optionToValueMap_[argv[i]] = argv[i + 1];
				++i;
			}
			else
			{
				Logger::error("CmdLineOptionParser", std::string(argv[i]) + " option does not exist.");
				printHelp();
				exit(EXIT_FAILURE);
			}
		}
		
		for (const auto& [option, value] : optionToValueMap_)
		{
			if (value.empty())
			{
				Logger::error("CmdLineOptionParser", "you must specify value for | " + option + " | option.");
				printHelp();
				exit(EXIT_FAILURE);
			}
		}
	}

	bool CmdLineOptionParser::checkOption(const std::string& option) const
	{
		return optionToValueMap_.find(option) != optionToValueMap_.end();
	}

	void CmdLineOptionParser::addOption(const std::string& option, const std::string& description)
	{
		optionToValueMap_[option] = std::string();
		optionToDescriptionMap_[option] = description;
	}

	int CmdLineOptionParser::getIntOptionValue(const std::string& option) const
	{
		std::string value = optionToValueMap_.at(option);
		return atoi(value.c_str());
	}

	std::string CmdLineOptionParser::getStringOptionValue(const std::string& option) const
	{
		return optionToValueMap_.at(option);
	}

	void CmdLineOptionParser::printHelp() const
	{
		std::cout << "************** HELP ******************************\n";
		for (const auto& [option, description] : optionToDescriptionMap_)
		{
			std::cout << "| " << option << " | " << description << std::endl;
		}
		std::cout << "*************************************************\n";
	}

} // end namespace ftp	


