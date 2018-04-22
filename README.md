# Sound

## Configuration instructions

### Required hardware settings

1. 
2.

### Required software settings ( + additional libraries )
	
1. 
2. 

## Installation instructions

### Required hardware
	
1. [Raspberry Pi](https://en.wikipedia.org/wiki/Raspberry_Pi), 
	Model 3B ( further: [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) )
2. External USB sound card
3. Microphone
4. Ethernet cable ( RJ45 )
5. Server

### Required software
	
1. [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) files
2. Server files

## Operating instructions



### Algorithm of the program

#### Mandatory part

1. Recording sound for 1 second
2. Outputting corresponding data in the console window:
	1. Header data and list of 80 RMS values ( DEBUG mode )
	2. Sound decibel level bar chart ( non-DEBUG mode )
				
#### Optional part

1. Sending FastDB data to the server
2. Storing the data on the server side:		
	1. All the data with attached dates in .txt file
	2. Last received 8 pieces of data in .json file		
3. Outputting the last obtained data on the webpage real-time chart
	
## File manifest

1. **_.c_ files**:
	1. comm.c
	2. main.c
	3. screen.c
	4. sound.c	
2. **_.h_ files**:
	1. comm.h
	2. screen.h
	3. sound.h
3. **_Other_ files**:
	1. makefile
	2. README.md

## Copyright and licensing information

This project is licensed under the GNU General Public License - see the LICENSE file for details

## Known bugs and troubleshooting

### "_The graph is not updating on the site_"
	
#### Problem
	
After some time the program **stops getting new data** from the server.
		
#### Solution
	
1. Clear the browser cache
2. Refresh the page until it updates
		
### "_There are some weird symbols changing in the console window_"
	
#### Problem
	
The symbols used as bars are some weird ones and completely do not seem to have a bar form. **The console does not recognize the UTF-8 symbol \u2590** used as a bar in **_screen.c_** file.
		
#### Solution
	
Set your console character set to **UTF-8**.
		
##### _PuTTY_ solution

1. Go to your **_console settings_** ( choose either way )
	- **_PuTTY - Configuration_** window can be reached when PuTTY is launched
	- **_PuTTY - Reconfiguration_** window can be reached by right-clicking on the top bar
		of the PuTTY window
2. **_Window_**               ( window's left side tree )
3. **_Translation_**          ( window's left side tree )
4. **_Remote character set_** ( window's right side )
5. Choose **_UTF-8_**         ( list )

## Credits and acknowledgments

* **Roman Bezusiak** - _Initial work_ - [Roman Bezusiak](https://github.com/roman-bezusiak) 
