// Library inclusions
#include "screen.h"
#include <stdio.h>
#include <math.h>

// Function definition of clearScreen()
void clearScreen ()
{
	printf( "%c[2J", ESC );
	fflush( stdout );
}

// Function definition of goToXY()
void goToXY ( int row, int col )
{
	printf( "%c[%d;%dH", ESC, row, col );
	fflush( stdout );
}

// Function definition of setColour()
void setColour ( int id )
{
	if ( id >= BLACK && id <= WHITE )
	{
		printf( "%c[%d;1m", ESC, id );
		fflush( stdout );
	}
}

/*
	Function definition of dispBar(), this fucntion
	displays a vertical bar for the given dB value.
	The value varies between 30 and 90, so we need to render 3 dB
	for 1 row and 90 dB will be displayed as bar of 30 rows
*/
void dispBar ( int col, double dB )
{
	int
		i,
		decibels = ( int ) floor( dB / 3 ); // Loop counter
	
	
	for ( i = 0; i < decibels; ++i )
	{
		goToXY( 30 - i, col + 1 );	
		
		if ( i <= 50 / 3 )
		{
			setColour( WHITE );
		}
		else if ( i <= 70 / 3  )
		{
			setColour( YELLOW );
		}
		else
		{
			setColour( RED );
		}
		
		// Variation of the output
#ifndef UNICODE // If unicode is not enabled
		printf( "%c", '*' );
#else
		printf( "%s", BAR );
#endif
		setColour( 0 );
	}
}
