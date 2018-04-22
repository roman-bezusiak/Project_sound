# Sound

## Configuration instructions

### 	Required hardware
	
1. Raspberry Pi Model 3 B
2. Sound card
3. Microphone
4. Ethernet cable ( RJ45 )
5. Server
			
## Installation instructions

	

## Operating instructions

	

## Algorithm of the program:

### Mandatory part

1. Recording sound for 1 second
2. Outputting corresponding data in the console window:
	- Header data and list of 80 RMS values ( DEBUG mode )
	- Sound decibel level bar chart ( non-DEBUG mode )
				
### Optional part

1. Sending FastDB data to the server
2. Storing the data on the server side:			
	- All the data with attached dates in .txt file
	- Last received 8 pieces of data in .json file
		
3. Outputting the last obtained data on the webpage real-time chart
	
## File manifest

1. .c:
	- comm.c
	- main.c
	- screen.c
	- sound.c	
2. .h:
	- comm.h
	- screen.h
	- sound.h
3. Other:
	- makefile
	- README.md

## Copyright and licensing information



## Known bugs and troubleshooting

### "The graph is not updating"
	
#### Problem
	
After some time the program may stop getting the data from the server, because there is only
one same request all the time, and returned data from the server is not new, so your browser
just saves it in cache and does not receive any new data.
		
#### Solution
	
1. Clear the browser cache
2. Refresh the page until it updates
		
### "There are some weird symbols changing in the console window"
	
#### Problem
	
The symbols used as bars are some weird ones and completely do not seem to have a bar form.
		
#### Solution
	
The console does not recognize the UTF-8 symbol "\u2590" used as a bar in "screen.c" file, 
it can be fixed by setting your console character set to "UTF-8".
		
##### PuTTY

1. Go to your console settings:		
	- "PuTTY - Configuration" window can be reached when PuTTY is launched
	- "PuTTY - Reconfiguration" window can be reached by right-clicking on the top bar
		of the PuTTY window
2. "Window"               ( window's left side tree )
3. "Translation"          ( window's left side tree )
4. "Remote character set" ( window's right side )
5. Choose "UTF-8"         ( list )
