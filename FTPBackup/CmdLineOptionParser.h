#ifndef FTP_CMDLINEOPTIONPARSER_H_
#define FTP_CMDLINEOPTIONPARSER_H_

#include <unordered_map>

namespace ftp {
	
	/**
	 * Class to parse the application's command line options.
	 */
	class CmdLineOptionParser
	{
		using HashContainerType = std::unordered_map<std::string, std::string>;
	public:

		/**
		 * Parses the arguments and their values and stores them in the map.
		 * 
		 * \param argc argument count
		 * \param argv argument list
		 */
		void parseArgs(int argc, char* argv[]);
		
		/**
		 * Checks if the given option is in the map.
		 * 
		 * \return True if option found
		 */
		bool checkOption(const std::string& option) const;
		
		/**
		 * Adds an option and its description to the map.
		 */
		void addOption(const std::string& option, const std::string& description);

		/**
		 * Returns the value for the given key as an integr.
		 * 
		 * \throw runtime_exception when option not found
		 */
		int getIntOptionValue(const std::string& option) const;
		
		/**
		 * Returns the value for the given key as an string.
		 * 
		 * \throw runtime_exception when option not found
		 *
		 */
		std::string getStringOptionValue(const std::string& option) const;

		/**
		 * Prints help to the console.
		 */
		void printHelp() const;

	private:
		HashContainerType optionToValueMap_;
		HashContainerType optionToDescriptionMap_;
	};

} // end namespace ftp
#endif // FTP_CMDLINEOPTIONPARSER_H_
