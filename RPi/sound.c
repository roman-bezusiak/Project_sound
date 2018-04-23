#include "comm.h"
#include "sound.h"
#include "screen.h"
#include <stdio.h>
#include <math.h>

/*
	Fucntion definition of printID()
	
	This function outputs transmitted string
	type IDs char by char, then moves the
	cursor to the next line using "\n".
	
	Arguments: string type ID
	Returns: none
*/
void printID ( char id[] )
{
	int i;
	
	for ( i = 0; i < 4; ++i )
	{
		printf( "%c", id[ i ] );
	}
	
	printf( "\n" );
}

/*
	Fucntion definition of dispWAVHeader()
	
	This function reads the header data from the .wav file
	and displays it in the console window.
	
	Arguments: string type file name
	Returns: none
*/
void dispWAVHeader ( char filename[] )
{
	FILE *fp;     // File handler of the .wav file
	WAVHeader mh; // An instance of WAVHeader struct
	
	// Open the "test.wav" file for reading
	fp = fopen( filename, "r" );
	
	// File absence condition handling
	if ( fp == NULL )
	{
		// Error message
		printf( "Error when open the file" );
		return;
	}
	
	fread( &mh, sizeof( mh ), 1, fp ); // Reading .wav header from the file into mh variable
	fclose( fp );                      // Closing file
	
	// Formated console output of the header
	printf( "\nHeader info:" );
	printf( "\n\n\tChunk ID:           " );                 // Chunk ID
	printID( mh.chunkID );                                  
	printf( "\tChunk size: %13d\n", mh.chunkSize );         // Chunk size
	printf( "\tFormat:             " );                     // Format
	printID( mh.format );
	printf( "\tSubchunk 1 ID:      " );                     // Subchunk 1 ID
	printID( mh.subchunk1ID );
	printf( "\tSubchunk 1 size: %5d\n", mh.subchunk1Size ); // Subchunk 1 size
	printf( "\tAudio format: %7d\n", mh.audioFormat );      // Audio format
	printf( "\tNumber of channels: %d\n", mh.numChannels ); // Number of channels
	printf( "\tSamplerate: %13d\n", mh.sampleRate );        // Samplerate
	printf( "\tByterate: %15d\n", mh.byteRate );            // Byterate
	printf( "\tBlock align: %8d\n", mh.blockAlign );        // Block align
	printf( "\tBits per sample: %5d\n", mh.bitsPerSample ); // Bits per sample
	printf( "\tSubchunk 2 ID:      " );                     // Subchunk 2 ID
	printID( mh.subchunk2ID );
	printf( "\tSubchunk 2 size: %8d\n", mh.subchunk2Size ); // Subchunk 2 size
	printf( "\n" );
}

/*
	Fucntion definition of dispWAVData()
	
	This function reads the sound data from the .wav file,
	displays it in the console window, and sends it to the
	server, depending on conditional compiling.
	
	If DEBUG is defined ( sound.h ), the program will be
	showing the list of 80 RMS values, if it is not, the
	program will be showing coloured bar chart of 80
	decibel values.
	
	If COMM is defined ( comm.h ), the program will
	call sendToServer( double rms[] ), if it is not,
	nothing will happen.
	
	Arguments: string type file name
	Returns: none
*/
void dispWAVData ( char filename[] )
{
	register i, j;				 // Loop counters
	int arr_c1, arr_c2;			 // Array counters
	FILE *fp;					 // File handler of .wav file
	double
		rms[ 80 ],               // 80 pieces of RMS values
		sum;		             // Intermediate sum
	short samples[ SAMPLERATE ]; // Totally 16000 samples in 1 sec
	WAVHeader mh;				 // Just used to skip over the header of .wav file
	double dB;                   // Current sound frame decibel value
	
	// Opening the file
	fp = fopen( filename, "r" );
	
	// File absence condition handling
	if ( fp == NULL )
	{
		// Erroe message
		printf( "Error when open the file\n" );
		return;
	}
	
	fread( &mh, sizeof( mh ), 1, fp );                 // Skipping over the header of .wav file
	fread( samples, sizeof( short ), SAMPLERATE, fp ); // Reading the sound samples
	fclose( fp );                                      // Closing the file
	
	clearScreen(); // Clearing the screen
	
	// Calculating and outputting the sound information
	for ( i = 0; i < 80; ++i )
	{
		arr_c1 = i * SAMPLEFRAME;
		
		for ( j = 0, sum = 0.0; j < SAMPLEFRAME; ++j )
		{
			arr_c2 = arr_c1 + j;
			sum += samples[ arr_c2 ] * samples[ arr_c2 ];
		}
		
		rms[ i ] = sqrt( sum / SAMPLEFRAME ); // RMS value calculation
		dB = 20 * log10( rms[ i ] );          // Decibel value calculation
#ifdef DEBUG
		// RMS data format output in DEBUG mode
		printf( "\tRMS[ %d ]: %10.4f, dB = %10.4f\n", i, rms[ i ], dB );
#else
		// Decibel data format output ( bar chart ) in non-DEBUG mode
		dispBar( i, dB );
#endif
	}
	
	printf( "\n" );
	
#ifdef COMM
	// Sending data to the server in COMM mode
	sendToServer( rms );
#endif
}
