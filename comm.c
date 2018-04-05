#include "comm.h"
#include <stdio.h>
#include <math.h>
#include <curl/curl.h>

/*
	Function definition of sendToServer()
	It takes in 80 pieces of RMS values,
	each is calculated by 200 samples.
	The function should use these values
	to re-calculate 8 pieces of fast
	decibel value. To do so, we need to
	put every 10 pieces of RMS values,
	square them, multiply by 200, accumulate
	to a sum, and then divided by 2000, then
	square-root the result
*/
void sendToServer ( double rms[] )
{
	double
		fast[ 8 ],     // FastdB values
		sum;           // Intermediate sum
	int
		i, j;          // Loop counters
	CURL *curl;
	CURLcode res;      
	char post[ 1000 ]; // String for passing FastdB values
	                   // to the PHP site
	
	
	// Outer loop repeats 8 times for 8
	// pieces of result
	for ( i = 0; i < 8; ++i )
	{
		// Inner loop repeats 10 times
		// To accumulate the sum
		for ( j = 0, sum = 0; j < 10; ++j )
		{
			sum += pow( rms[ j + i * 10 ], 2.0 ) * 200;
		}
		
		fast[ i ] = sqrt( sum / 2000 );
	}
	
	sprintf(
		post,
		"data=%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f",
		fast[ 0 ],
		fast[ 1 ],
		fast[ 2 ],
		fast[ 3 ],
		fast[ 4 ],
		fast[ 5 ],
		fast[ 6 ],
		fast[ 7 ]
	);
	
	curl_global_init( CURL_GLOBAL_ALL );
	curl = curl_easy_init();
	
	if ( curl )
	{
		curl_easy_setopt( curl, CURLOPT_URL, URL );
		curl_easy_setopt( curl, CURLOPT_POSTFIELDS, post );
		
		res = curl_easy_perform( curl );
		
		if ( res != CURLE_OK )
		{
			fprintf(
				stderr,
				"curl_easy_perform() failed: %s\n",
				curl_easy_strerror( res )
			);
			curl_easy_cleanup( curl );
		}
	}
	
	curl_global_cleanup();
}
