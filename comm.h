/*
	This header file defines necessary constants and
	function prototypes for communicatio. In our
	solution, <curl.h> library is used
*/

#define COMM // Conditional compiling

// Constant definitions
#define URL "http://www.cc.puv.fi/~e1700684/sound.php"

// Function prototypes
void sendToServer ( double rms[] );
