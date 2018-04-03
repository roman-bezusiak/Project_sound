// This program contains the main fucntion of the project

#include "sound.h"
#include "screen.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main ( void )
{
	int ret;

	printf( "\n" );
	
	while ( 1 ) // Loop forever
	{
		// Run system command "arecord" to record 1 sec of wav
		ret = system( "arecord -q -r16000 -c1 -f S16_LE -d1 test.wav" );
		
		if ( WIFSIGNALED( ret ) && ( WTERMSIG( ret ) == SIGINT ) )
		{
			break;
		}
		
		// Display WAV header
		dispWAVHeader( "test.wav" );
		
		// Display WAV strength as decibel value
		dispWAVData( "test.wav" );
		
		//break;		
	}
	
	printf( "\n" );	
	return 0;
}
