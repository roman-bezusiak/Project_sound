/*
	This header file defines necessary constants and
	function prototypes related to communication. In
	this solution, <curl.h> library is used
*/

#define COMM // Conditional compiling

// Constant definitions
#define URL "http://your.server.com/sound.php"

// Function prototypes
void sendToServer (double rms[]);
