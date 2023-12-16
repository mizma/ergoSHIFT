[日本語はこちら](README_ja.md)

This is Arduino code for a USB arcade controller, meant to be used with ATmega32U4-based boards like the Arduino Pro Micro.

It works with Flatbox-ACR [rev1.1](../hardware-rev1.1)

## Change Points from [original](https://github.com/jfedor2/flatbox/blob/master/firmware-atmega32u4)

* Implemented SOCD Cleaner with selection of Hitbox style and Gafro-Controller style cleaning
    * Hold R3 when connecting to set to Hitbox Style SOCD Cleaner
    * Hold L3 when connecting to set to Gafro-controller style SOCD Cleaner
    * Hold PS when connecting to set to All Neutral SOCD Cleaner
    * Settings are saved in EEPROM so it will not change after power cycle
* Implement Up/Down Inversion (for playing normal arcade games)
    * Hold DOWN to set to Hitbox style
    * Hold UP to invert Up and Down buttons.
    * Settings are saved in EEPROM

## Building Instructions

- Download Arduino IDE, 
- Download the Bounce2 Library inside the Arduino IDE
- Add `https://github.com/CrazyRedMachine/Arduino-Lufa/raw/master/package_arduino-lufa_index.json` as an Additional Board Manager URL (in `File -> Preferences` menu)
- Install LUFA AVR Boards from the Board Manager
- Select Arduino Leonardo (LUFA) as your board type (Pro-Micro is a compatible board to Leonardo)
- Upload the code and Have Fun

### How to upload

When you reflash AVR boards with USB HID device software, Arduino IDE cannot automatically reset and flash the software.
You will need to press reset button on the AVR board (SW_RST1 on Flatbox ACR) to put it into Bootloader mode to reflash.
When you use Sparkfun Qwiik ProMicro 5V, you will need to double-click the reset button to put it into Bootloader.

I recommend setting up VSCode Arduino plugin.  If you open this directory with VSCode, it is already set up so all you need to do is
run Arduino: Verify from the command pallet (You will still need to install Arduino, Bounce Library and add the LUFA board manager URL before you can run verify).
The .hex file will be created in the Build folder.

Take the .hex file and use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) to flash the .hex file.

In QMK Toolbox, Press OPEN and select the .hex file you just created, (or just use the one in the repository).  Select ATMega32U4 from the dropdown menu at the top right corner.
Click the Reset button on the Pro-Micro (Double-Click on Qwiik ProMicro USB-C variant).  When you see the "Caterina device connected (usbser): ~~~" text, press Flash button.

This method, while requires extra software setups, is more reliable than trying to time the Reset while Arduino IDE is doing it's thing...
