#include "SQLBackup.h"

/*! \mainpage SQL Backup to FTP server
 *
 * \section intro_sec Introduction
 *
 * The app was written by using <b>C++17</b> standart. \n
 * Tests are written by using <b>Google Test</b> framework. \n
 * The app uses <b>sqlite3</b> database and <b>Filezilla</b> FTP server. \n\n
 * 
 *  App command line options: \n
 *  <b>--ftp_host</b>'  - Flag to specify the backup FTP server's host. \n 
 *  <b>--ftp_port</b>   - Flag to specify the backup FTP server's port. \n
 *  <b>--ftp_uname</b>  - Flag to specify the backup FTP server's User name. \n
 *  <b>--ftp_pass</b>   - Flag to specify the backup FTP server's User password. \n
 *  <b>--ftp_dir</b>    - Flag to specify the backup FTP server's copy directory. \n\n
 *
 *  <b>sqlite3</b> doesn't require a <b>connection properties</b> so I didn't add an option to add a db property. \n\n
 *
 * \section use_sec How to use
 *
 * \subsection step1 Step 1: Set up an Filezilla FTP server and create a user in it.
 * \subsection step2 Step 2: Run the program by setting options via the console.
 *                           example: <b>./app --ftp_host 127.0.0.1 --ftp_port 21 --ftp_uname username --ftp_passwd password --ftp_dir ftpDir</b>
 */

int main(int argc, char* argv[])
{
    ftp::SQLBackup app;
    app.start(argc, argv);

    return 0;
}
