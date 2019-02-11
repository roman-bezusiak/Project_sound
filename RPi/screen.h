/*
	This header file defines necessary constants and
	function prototypes related to sound data output.
	In this solution, UTF-8 standart is used
*/

#define UNICODE      // Conditional compiling
#define BAR "\u2590" // Bar symbol (UTF-8)

// Constant definitions
#define ESC 0x1B

// Definition of colours
enum COLORS
{
	BLACK = 30, // 30
	RED,        // 31
	GREEN,      // 32
	YELLOW,     // 33
	BLUE,       // 34
	MAGENTA,    // 35
	CYAN,       // 36
	WHITE       // 37
};

// Function prototypes
void clearScreen ();
void goToXY      (int row, int col);
void setColour   (int id);
void dispBar     (int col, double dB);
