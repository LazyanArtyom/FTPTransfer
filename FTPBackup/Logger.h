#ifndef FTP_LOGGER_H_
#define FTP_LOGGER_H_

#include <iostream>
#include <string_view>

namespace ftp {

	/**
	 * Siple logger.
	 */
	class Logger 
	{
	public:
		static void error(std::string_view fileName, std::string_view msg)
		{
			std::cerr << "ERROR: in " << fileName << ": " << msg << std::endl;
		}
		
		static void info(std::string_view fileName, std::string_view msg)
		{
			std::cout << "INFO: " << fileName << ": " << msg << std::endl;
		}

	private:
		Logger() = delete;
		~Logger() = delete;
		Logger(const Logger&) = delete;
		void operator=(const Logger&) = delete;
		Logger(Logger&&) noexcept = delete;
		Logger& operator=(Logger&&) noexcept = delete;
	};

} // end namespace ftp
#endif // FTP_LOGGER_H_
