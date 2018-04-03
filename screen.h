#define UNICODE // Uses unicode to make good-looking bars
#define BAR "\u2590" //262D

// Constant definitions
#define ESC 0x1B

enum COLORS
{
	BLACK = 30,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
};

// Function prototypes
void clearScreen ();
void goToXY      ( int row, int col );
void setColour   ( int id );
void dispBar     ( int col, double dB );
