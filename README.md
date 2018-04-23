# Sound proj.

## Configuration instructions

### Required hardware:
	
1. [Raspberry Pi](https://en.wikipedia.org/wiki/Raspberry_Pi), 
	Model 3B ( further: [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) )

2. [External USB sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards) 
	( further: [sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards) )

3. Microphone, 3.5 mm headphone jack plug ( further: mic )

4. ["RJ45" Ethernet cable](https://en.wikipedia.org/wiki/Modular_connector#8P8C) 
	( further: [e-cable](https://en.wikipedia.org/wiki/Modular_connector#8P8C) )

5. Power supply for the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) 
	( one of the following ):
	- USB cable + seperate device's USB port ( PC, laptop, etc. )
	- [Common external power supply](https://en.wikipedia.org/wiki/Common_external_power_supply)

6. Server

#### Optional ( for testing sound recording quality ):

Sound playing device, 3.5 mm headphone jack plug ( further: dynamic )

### Required hardware set-up:

1. Connect the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) to the 
	Internet using the [e-cable](https://en.wikipedia.org/wiki/Raspberry_Pi)

2. Connect the [sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards)
	to the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi)

3. Connect the mic to the [sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards)

4. Connect the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) to the power supply

#### Optional ( for testing sound recording quality ):

Connect the dynamic to the 
	[sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards)

## Installation instructions

### Required software and external libraries:
	
1. [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) files ( 
	[RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) )

2. Server files ( Server )

3. [PuTTY](https://en.wikipedia.org/wiki/PuTTY) ( Main operating computer )

4. [Curl library](https://curl.haxx.se/) ( 
	[RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) )

### Required software settings:
	
1. Constant **_URL_** in _comm.h_ file should be changed 
	to the your server's address

2. Check whether **curl** library is already installed on the 
	[RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) by running the following command: 

```
~$ ls /usr/include/curl
```

If it is not, install it by running the following commands:

```
~$ sudo apt-get update
~$ sudo apt-get install libcurl3
~$ sudo apt-get install libcurl4-openssl-dev
```

3. Set the [sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards) as 
Default by performing the following steps:  

Run:

```
~$ lsusb
```

The following should be seen:

```
Bus 001 Device 004: ID 0d8c:000c C-Media Electronics, Inc. Audio Adapter
Bus 001 Device 003: ID 0424:ec00 Standard Microsystems Corp. SMSC9512/9514 Fast Ethernet Adapter
Bus 001 Device 002: ID 0424:9514 Standard Microsystems Corp.
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
```

Run:

```
~$ sudo nano /etc/asound.conf
```

Contents of _asound.conf_ should be changed to the following:

```
pcm.!default
{
	type plug
	slave
	{
		pcm "hw:1,0"
	}
}

ctl.!default
{
	type hw
	card 1
}
```

Go to the home directory of the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi).  
Run:

```
~$ nano .asoundrc
```

Contents of _.asoundrc_ should be identical to ones of _asound.conf_.  
Run:

```
~$ alsamixer
```

In the opened menu [sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards) 
should be seen as a default.

```
	Card: C-Media USB Headphone Set
	Chip: USB Mixer
	View: F3:[Playback] F4: Capture  F5: All
	Item: Headphone [dB gain: -20.13, -20.13]
```

Change sound volume bars of the mic and dynamic according to your preferences:

```
	   ┌──┐           ┌──┐
	   │  │           │  │
	   │  │           │  │
	   │  │           │  │
	   │  │           │  │
	   │  │           │  │
	   │  │           │  │
	   │  │           │▒▒│
	   │▒▒│           │▒▒│
	   │▒▒│           │▒▒│
	   │▒▒│           │▒▒│
	   │▒▒│           │▒▒│
	   │▒▒│           │▒▒│
	   │▒▒│           │▒▒│
	   ├──┤           ├──┤
	   │OO│           │MM│
	   └──┘           └──┘
	  19<>19           52
	Headphone         Mic         

```

4. **alsa-utils** should be version **1.0.25**, in order to make it so, the following 
	steps should be performed:  
  
Run:

```
~$ sudo nano /etc/apt/sources.list
```

Add the following line at the end of _sources.list_:

```
deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi
```

Run:

```
~$ sudo apt-get update
~$ sudo apt-get install alsa-utils=1.0.25-4
```

Reboot ( if necessary ). Optional test of the sound quality:  

Run:

```
~$ arecord -r44100 -c1 -f S16_LE -d5 test.wav
```

Connect dynamic to the 
[sound card](https://en.wikipedia.org/wiki/Sound_card#USB_sound_cards). Run:

```
~$ aplay test.wav
```

## Operating instructions

### Main algorithm

#### I. Mandatory part:

1. Recording **1 second** of audio into _test.wav_ file using 
	[RPi](https://en.wikipedia.org/wiki/Raspberry_Pi)

2. Outputting corresponding data in the console window ( one of the following ):
	- Header data and list of **80 [RMS](https://en.wikipedia.org/wiki/Root_mean_square)** 
		values ( DEBUG mode )
	- Sound decibel level bar chart ( non-DEBUG mode, one of the following ):
		- Displayed using bar ( ▐ ) symbol ( UNICODE mode )
		- Displayed using asterisk ( * ) symbol ( non-UNICODE mode )

```
	Main operating computer ( PuTTY ) =( commands )=> RPi
	RPi =( sound data )=> Main operating computer
```
				
#### II. Optional part ( COMM mode ):

1. Sending FastDB ( 8 decibel values recorded once in every 125 ms ) 
	data to the server

2. Storing the data on the server side ( both of the following ):		
	- All the data with attached dates in _sound_log.txt_ file
	- Last received **8 pieces** of sound data in _last_line.json_ file	

3. Outputting the last obtained data on the webpage real-time chart

```
	...
	RPi =( sound data )=> Server
	Server =( sound data )=> Web site =( sound graph )=> Main operating computer ( browser )
```

### Pre-settings

There are some preset values ruling conditional compiling in the 
	[RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) files:

1. **_DEBUG_** mode   - off ( **DEBUG** undefined )
2. **_UNICODE_** mode - on  ( **UNICODE** defined )
3. **_COMM_** mode    - on  ( **COMM** defined )

#### DEBUG mode

The **_DEBUG_** constant is defined in _sound.h_. In order to set it off / on, add / 
remove two slashes ( // ) respectively in the beginning of the following line:

```
#define DEBUG // Conditional compiling
```

#### UNICODE mode

The **_UNICODE_** constant is defined in _screen.h_. In order to set it off / on, add 
/ remove two slashes ( // ) respectively in the beginning of the following line:

```
#define UNICODE // Unicode usage for making beautiful output
```

#### COMM mode

The **_COMM_** constant is defined in _comm.h_. In order to set it off / on, add / 
remove two slashes ( // ) respectively in the beginning of the following line:

```
#define DEBUG // Conditional compiling
```

When **_COMM_** mode is set, one should change the **_URL_** address in 
_comm.h_ file in the following line:

```
#define URL "http://your.server.com/.../sound.php"
```

### Launching

1. Launch the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi)

2. Connect to the [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) via 
	[PuTTY](https://en.wikipedia.org/wiki/PuTTY)

3. Run:

```
~$ make
~$ ./sound.a
```

4. Go to the server's **_URL_** in the browser using main operating computer

## File manifest

### List:

- [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) ( **_9_** ):
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

### Total: **_14_** files ( **_16_** including optional ones )

#### Remark

Even if there are no optional files, they will be created when the data 
transmission from [RPi](https://en.wikipedia.org/wiki/Raspberry_Pi) to the 
server starts. But, if one runs the program without data transmission from 
[RPi](https://en.wikipedia.org/wiki/Raspberry_Pi), the chart will be drawn 
only if there is _last_line.json_ file with valid data.

##### Valid data example:

```
{"data":"124.00;219.49;317.29;412.53;389.72;256.49;134.82;192.13;"}
```

## Copyright and licensing information

This project is licensed under the 
[**GNU General Public License**](https://en.wikipedia.org/wiki/GNU_General_Public_License). 
See the [_LICENSE_](LICENCE) file for details

## Known bugs and troubleshooting

### "_Some commands are not running_"
	
#### Problem:
	
Some commands can be run only using **_sudo_** prefix, which gives one administrator 
	rights.
		
#### Solution:
	
Write **_sudo_** before the command.

### "_The graph is not updating on the site_"
	
#### Problem:
	
There is only one graph state on the site and it does not change.
		
#### Solution:
	
1. Check the set-up 
2. Check whether the _sound.a_ is running 
3. Refresh the web page 
		
### "_There are some weird symbols changing in the console window_"
	
#### Problem:
	
The symbols used as bars are some weird ones and completely do not seem to have a bar form. 
	**The console does not recognize the [UTF-8](https://en.wikipedia.org/wiki/UTF-8) symbol 
	[U+2590](https://en.wikipedia.org/wiki/Block_Elements)** used as a bar in **_screen.c_** file.
		
#### Solution:
	
Set the console's character set to [**UTF-8**](https://en.wikipedia.org/wiki/UTF-8).
		
##### [_PuTTY_](https://en.wikipedia.org/wiki/PuTTY) solution:

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

### Used resources:
- **[Wikimedia Foundation Inc.](https://wikimediafoundation.org/wiki/Home), 
	Wikipedia** - _Encyclopedia materials_ - 
	[wikipedia.org](https://www.wikipedia.org/)

### Used third party libraries:
- **Chart.js**    - _Graph drawing ( Front-end )_ - 
	[chartjs.org](http://www.chartjs.org/)
- **jQuery.js**   - _AJAX_ - [jquery.com](https://jquery.com/)
- **curl/curl.h** - _Data transmission_ - 
	[curl.haxx.se](https://curl.haxx.se/)
