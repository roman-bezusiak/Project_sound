/*
	This header file defines necessary constants and
	function prototypes related to calculating and
	outputting the header data and the sound data of
	the .wav file
*/

//#define DEBUG // Conditional compiling

// Constant definitions
#define SAMPLERATE 16000 // Amount of all taken samples
#define SAMPLEFRAME 200  // Base for one RMS value

// Struct definition of .wav file header data
typedef struct
{
	char           chunkID[ 4 ];     // "RIFF"
	unsigned int   chunkSize;        // 4 bytes
	char           format[ 4 ];      // "WAVE"
	char           subchunk1ID[ 4 ]; // "fmt"
	unsigned int   subchunk1Size;
	unsigned short audioFormat;      // 16 for PCM
	unsigned short numChannels;      // 1 for mono
	unsigned int   sampleRate;
	unsigned int   byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char           subchunk2ID[ 4 ]; // "data"
	unsigned int   subchunk2Size;
} WAVHeader;

// Fucntion prototypes
void dispWAVHeader (char filename[]);
void dispWAVData   (char filename[]);
void printID	   (char []);
