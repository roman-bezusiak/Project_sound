#include "screen.h"
#include <stdio.h>
#include <math.h>

/*
	Function definition of clearScreen()
	
	Clears the console text screen.
	
	Arguments: none
	Returns: none
*/
void clearScreen ()
{
	printf("%c[2J", ESC);
	fflush(stdout);
}

/*
	Function definition of goToXY()
	
	Changes the console text cursor position.
	
	Arguments: console row, console column
	Returns: none
*/
void goToXY (int row, int col)
{
	printf("%c[%d;%dH", ESC, row, col);
	fflush(stdout);
}

/*
	Function definition of setColour()
	
	Changes the console text output colour.
	
	Arguments: colour id
	Returns: none
*/
void setColour (int id)
{
	if (id >= BLACK && id <= WHITE)
	{
		printf("%c[%d;1m", ESC, id);
		fflush(stdout);
	}
}

/*
	Function definition of dispBar()
	
	This fucntion displays a vertical bar corresponding to the
	given dB value. The value varies between 30 and 90, so 3 dB
	are rendered for 1 row and 90 dB will be displayed as bar
	of 30 rows.
	
	All the cells are coloured depending on their value:
	
		1.  0 dB <= dB value <= 50 dB: white
		2.  50 dB < dB value <= 70 dB: yellow
		3.  70 dB < dB value <= 80 dB: red
		
	Arguments: current column, current decibel value
	Returns: none
*/
void dispBar (int col, double dB)
{
	int
		i,
		decibels = (int) floor(dB / 3); // Loop counter
	
	
	for (i = 0; i < decibels; ++i)
	{
		// Changing cursor position
		goToXY(30 - i, col + 1);	
		
		// Setting colour of the drawing symbol
		if (i <= 50 / 3)
		{
			setColour(WHITE);
		}
		else if (i <= 70 / 3 )
		{
			setColour(YELLOW);
		}
		else
		{
			setColour(RED);
		}
		
		// Variation of the output
#ifndef UNICODE
		printf("%c", '*'); // Setting asterisk as a drawing symbol
#else
		printf("%s", BAR); // Setting a vertical half-bar as a drawing symbol
#endif

		// Refreshing the colour
		setColour(0);
	}
}
