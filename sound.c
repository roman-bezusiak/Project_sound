#include "sound.h"
#include "screen.h"
#include <stdio.h>
#include <math.h>

// Fucntion definition of printID()
void printID ( char id[] )
{
	int i;
	for ( i = 0; i < 4; ++i )
	{
		printf( "%c", id[ i ] );
	}
	printf( "\n" );
}

// Fucntion definition of dispWAVHeader()
void dispWAVHeader ( char filename[] )
{
	FILE *fp;
	WAVHeader mh;	// An instance of WAVHeader struct
	
	// Open the "test.wav" file for reading
	fp = fopen( filename, "r" );
	if ( fp == NULL )
	{
		printf( "Error when open the file" );
		return;
	}
	
	fread( &mh, sizeof( mh ), 1, fp );
	fclose( fp ); // Close the opened file
	
	printf( "\nHeader info:" );
	printf( "\n\n\tChunk ID:           " );
	printID( mh.chunkID );
	printf( "\tChunk size: %13d\n", mh.chunkSize );
	printf( "\tFormat:             " );
	printID( mh.format );
	printf( "\tSubchunk 1 ID:      " );
	printID( mh.subchunk1ID );
	printf( "\tSubchunk 1 Size: %5d\n", mh.subchunk1Size );
	printf( "\tAudio format: %7d\n", mh.audioFormat );
	printf( "\tNumber of channels: %d\n", mh.numChannels );
	printf( "\tSamplerate: %13d\n", mh.sampleRate );
	printf( "\tByterate: %15d\n", mh.byteRate );
	printf( "\tBlock align: %8d\n", mh.blockAlign );
	printf( "\tBits per sample: %5d\n", mh.bitsPerSample );
	printf( "\tSubchunk 2 ID:      " );
	printID( mh.subchunk2ID );
	printf( "\tSubchunk 2 size: %8d\n", mh.subchunk2Size );
	printf( "\n" );
}

// Fucntion definition of dispWAVData()
void dispWAVData ( char filename[] )
{
	register i, j;				 // Loop counters
	int arr_c1, arr_c2;			 // Array counters
	FILE *fp;					 // File handler to open the file "test.wav"
	double rms[ 80 ], sum;		 // 80 pieces of RMS values
	short samples[ SAMPLERATE ]; // Totally 16000 samples in 1 sec
	WAVHeader mh;				 // Just used to skip over the header of .wav file
	double dB;
	
	fp = fopen( filename, "r" );
	if ( fp == NULL )
	{
		printf( "Error when open the file\n" );
		return;
	}
	
	fread( &mh, sizeof( mh ), 1, fp ); // Skip over the header of .wav file
	fread( samples, sizeof( short ), SAMPLERATE, fp );
	fclose( fp );
	
	printf( "Data info:\n\n" );
	clearScreen();
	for ( i = 0; i < 80; ++i )
	{
		arr_c1 = i * SAMPLEFRAME;
		for ( j = 0, sum = 0.0; j < SAMPLEFRAME; ++j )
		{
			arr_c2 = arr_c1 + j;
			sum += samples[ arr_c2 ] * samples[ arr_c2 ];
		}
		rms[ i ] = sqrt( sum / SAMPLEFRAME );
		dB = 20 * log10( rms[ i ] );
#ifdef DEBUG 
		printf( "\tRMS[ %d ]: %10.4f, dB = %10.4f\n", i, rms[ i ], dB );
#else
		dispBar( i, dB );
#endif
	}
	printf( "\n" );
}
