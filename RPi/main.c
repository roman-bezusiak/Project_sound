// This program contains the main fucntion of the project

#include "sound.h"
#include "screen.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main (void)
{
	int ret; // The system signal variable

	// Console output formatting
	printf("\n");
	
	// Forever loop
	while (1)
	{
		// Run system command "arecord" to record 1 sec of wav
		ret = system("arecord -q -r16000 -c1 -f S16_LE -d1 test.wav");
		
		/*
			Escape algorithm which allows stop the program
			termination by pressing "Ctrl + C" in the console window.
			It is made, because otherwise the program will not
			handle the program interruption signal from the user,
			and will run, until the application is shut down
		*/
		if (WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT))
		{
			break;
		}
		
		// Display WAV header
		dispWAVHeader("test.wav");
		
		// Display WAV strength as decibel value
		dispWAVData("test.wav");		
	}
	
	// Console output formatting
	printf("\n");	
	return 0;
}
