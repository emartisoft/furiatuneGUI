# furiatuneGUI
FuriatuneGUI is a graphical user interface for the **furiatune\*** to run on **Amiga 600** with **Furia Expansion Board** only. The interface is very simple and user-friendly, it offers easy access to documented **furiatune\*** parameters without the need for command-line usage. 

(*) furiatune is a simple tool, that handles all the functions of the FuriaEC020 accelerator card. More info at http://www.kuchinka.cz/furia/

### Version (Hi)story
V1.1:
* Bugs Fixed (MAPROM function)
* More faster
* It remembers setting (IDE on/off), Added furiatuneSET file
* Updated command lines to the beginning of the S:Startup-sequence file
	
V1.0: 
* First release

### Requirements
* Amiga 600
* Furia Expansion Board (Furia accelerator CPU 68EC020/33 MHz, FPU 68882, 9.5MB of Fast RAM)
* Amiga OS 2.X/3.X
* furiatune (download file from http://www.kuchinka.cz/furia/ then copy it to C drawer)
### Boot Diskette
In **boot-diskette-adf** folder, you may download **furiatuneGUI_boot_diskette_VX.X.adf** image file then can write image file to disk
### How to Install
If RIGHT mouse button is held upon boot then furiatuneGUI starts. How to do?
* Copy furiatune, GetMouseInput and furiatuneSET to **C** drawer
* Copy furiatuneGUI to **SYS:System** drawer
* Add the following lines to the beginning of the **S:Startup-sequence file** (furiatuneGUI/Startup-Sequence/Startup-Sequence.txt)

In addition you may click icon to execute furiatuneGUI in **SYS:System** drawer.
### S:Startup-Sequence Settings
~~~~ bash
;Remember settings
SYS:C/furiatuneSET

C:GetMouseInput LOCAL
IF $MouseInput EQ 2
  Unset MouseInput
  IF EXISTS SYS:System/furiatuneGUI
	SYS:System/furiatuneGUI
	echo "Rebooting your Amiga ..."
	SYS:C/furiatune reboot
  EndIF
EndIF
Unset MouseInput
~~~~
### Video
Please, Click to watch the video:

V1.0: https://youtu.be/qF_fdg1YnS8

V1.1:

### ScreenShots

![icon](https://github.com/emartisoft/furiatuneGUI/blob/master/screenshots/icon.png?raw=true)
<br><br>
![main](https://github.com/emartisoft/furiatuneGUI/blob/master/screenshots/main.png?raw=true)
<br>furiatuneGUI Main Window<br><br>
![maprom](https://github.com/emartisoft/furiatuneGUI/blob/master/screenshots/maprom.png?raw=true)
<br>furiatuneGUI MapROM File Window<br><br>
![menu](https://github.com/emartisoft/furiatuneGUI/blob/master/screenshots/menu.png?raw=true)
<br>furiatuneGUI Menus<br><br>
![startup1](https://github.com/emartisoft/furiatuneGUI/blob/master/screenshots/startup1.png?raw=true)
<br><br>
![startup2](https://github.com/emartisoft/furiatuneGUI/blob/master/screenshots/startup2.png?raw=true)
