# Sound

## Configuration instructions

### Required hardware
	
1. [Raspberry Pi](https://en.wikipedia.org/wiki/Raspberry_Pi), 
	Model 3B ( further: [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) )
2. [External USB sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards) 
	( further: [sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards) )
3. Microphone, 3.5 mm Headphone jack ( further: mic )
4. ["RJ45" Ethernet cable](https://en.wikipedia.org/wiki/Modular_connector#8P8C) 
	( further: [e-cable](https://en.wikipedia.org/wiki/Raspberry_Pi) )
5. Power supply for the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) 
	( one of the following ):
	- USB cable + seperate device's USB port ( PC, laptop, etc. )
	- [Common external power supply](https://en.wikipedia.org/wiki/Common_external_power_supply)
6. Server

### Required hardware set-up

1. Connect the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) to the 
	Internet using the [e-cable](https://en.wikipedia.org/wiki/Raspberry_Pi)
2. Connect the [sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards)
	to the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi)
3. Connect the mic to the [sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards)
4. Connect the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) to the power supply

## Installation instructions

### Required software
	
1. [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) files
2. Server files

### Required software settings ( + external libraries )
	
1. Constant **_URL_** in _comm.h_ file should be changed
	to the your server's address  
2. 

## Operating instructions

1.
2.

### Main algorithm

#### I. Mandatory part:

1. Recording **1 second** of audio into _test.wav_ file using 
	[RPi](https://en.wikipedia.org/wiki/Raspberry_Pi)
2. Outputting corresponding data in the console window ( one of the following ):
	- Header data and list of **80 [RMS](https://en.wikipedia.org/wiki/Root_mean_square)** 
		values ( DEBUG mode )
	- Sound decibel level bar chart ( non-DEBUG mode, one of the following ):
		- Displayed using bar symbol ( UNICODE mode )
		- Displayed using asterisk symbol ( non-UNICODE mode )
				
#### II. Optional part:

1. Sending FastDB ( 8 decibel values recorded once in every 125 ms )  
	data to the server
2. Storing the data on the server side:		
	1. All the data with attached dates in .txt file
	2. Last received 8 pieces of data in .json file		
3. Outputting the last obtained data on the webpage real-time chart

## File manifest

- RPi ( **_9_** ):
	- **_.c_ files** ( **_4_** ):
		- comm.c
		- main.c
		- screen.c
		- sound.c	
	- **_.h_ files** ( **_3_** ):
		- comm.h
		- screen.h
		- sound.h
	- **_Other_ files** ( **_2_** ):
		- makefile
		- README.md

- Server ( **_5_** ):
	- **_Front-end_ files** ( **_2_** ):
		- sound.html
		- soundGraph.js
	- **_Back-end_ files** ( **_3_** ):
		- last_line.json
		- sound.php
		- sound_log.php
	- **_Optional_ files** ( **_2_** ):
		- sound_log.txt
		- last_line.json

### Total - **_14_** files ( **_16_** including optional ones )

### Remark

Even if there are no optional files, they will be created when the data 
transmission from [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) to the 
server starts. But, if one runs the program without data transmission from 
[RPi](https://en.wikipedia.org/wiki/Raspberry_Pi), the chart will be drawn 
only if there is _last_line.json_ file with valid data.

#### Valid data example:

```
{"data":"124.00;219.49;317.29;412.53;389.72;256.49;134.82;192.13;"}
```

## Copyright and licensing information

This project is licensed under the 
[GNU General Public License](https://en.wikipedia.org/wiki/GNU_General_Public_License). 
See the [LICENSE](LICENCE) file for details

## Known bugs and troubleshooting

### "_The graph is not updating on the site_"
	
#### Problem
	
There is only one graph state on the site and it does not change.
		
#### Solution
	
1. Check whether [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) is working
2. Refresh the web page
		
### "_There are some weird symbols changing in the console window_"
	
#### Problem
	
The symbols used as bars are some weird ones and completely do not seem to have a bar form. 
	**The console does not recognize the [UTF-8](https://en.wikipedia.org/wiki/UTF-8) symbol 
	[U+2590](https://en.wikipedia.org/wiki/Block_Elements)** used as a bar in **_screen.c_** file.
		
#### Solution
	
Set the console's character set to [**UTF-8**](https://en.wikipedia.org/wiki/UTF-8).
		
##### [_PuTTY_](https://en.wikipedia.org/wiki/PuTTY) solution

1. Go to the **_console settings_** ( choose either way )
	- **_PuTTY - Configuration_** window can be reached when [PuTTY](https://en.wikipedia.org/wiki/PuTTY) 
	is launched
	- **_PuTTY - Reconfiguration_** window can be reached by right-clicking on the top bar
		of the [PuTTY](https://en.wikipedia.org/wiki/PuTTY) window
2. **_Window_**               ( window's left side tree )
3. **_Translation_**          ( window's left side tree )
4. **_Remote character set_** ( window's right side )
5. Choose **_UTF-8_**         ( drop-down list )

## Credits and acknowledgments

### Authors:
- **Roman Bezusiak** - _Initial work_ - [Roman Bezusiak, GitHub profile](https://github.com/roman-bezusiak)

### Special thanks
- **Chao Gao** - _Project supervisor, teacher_ - [Chao Gao](http://www.puv.fi/en/contact/?person=gc)

### Used resources:
- **[Wikimedia Foundation Inc.](https://wikimediafoundation.org/wiki/Home), 
Wikipedia** - _References_ - [wikipedia.org](https://www.wikipedia.org/)

### Used third party libraries:
- **Chart.js** - _Graph drawing ( Front-end )_ - [chartjs.org](http://www.chartjs.org/)
- **curl/curl.h** - _Data transmission_ - [curl.haxx.se](https://curl.haxx.se/)
