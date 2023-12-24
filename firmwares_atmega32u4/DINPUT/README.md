[日本語はこちら](README_ja.md)

This is Arduino code for a USB arcade controller, meant to be used with ATmega32U4-based boards like the Arduino Pro Micro.
This firmware is based off of [jfedor2/flatbox](https://github.com/jfedor2/flatbox/) ATmega32u4 firmware.

It works with ergoSHIFT [rev1](../hardware-rev1)

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
- Add `https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json` as an Additional Board Manager URL (in `File -> Preferences` menu)
- Install SparkFun AVR Boards from the Board Manager
- Select SparkFun Pro Micro (SparkFun AVR Boards) as your board type and select ATmega32U4 (5V, 16MHz) as your processor.
- Upload the code and Have Fun

### Pinout

Configurable in the .ino

The key config is already setup to match ergoSHIFT wiring.

```C
#define PIN_UP        7
#define PIN_DOWN      4
#define PIN_LEFT      3
#define PIN_RIGHT     5
#define PIN_CROSS     10
#define PIN_CIRCLE    14
#define PIN_TRIANGLE  15
#define PIN_SQUARE    16
#define PIN_L1        21
#define PIN_L2        8
#define PIN_R1        20
#define PIN_R2        19
#define PIN_SELECT    18
#define PIN_START     2
#define PIN_L3        6
#define PIN_R3        9
#define PIN_PS        1
```

For southpaw bersion, swap the PIN_LEFT and PIN_RIGHT definition and recompile.

```C
#define PIN_UP        7
#define PIN_DOWN      4
#define PIN_LEFT      5
#define PIN_RIGHT     3
#define PIN_CROSS     10
#define PIN_CIRCLE    14
#define PIN_TRIANGLE  15
#define PIN_SQUARE    16
#define PIN_L1        21
#define PIN_L2        8
#define PIN_R1        20
#define PIN_R2        19
#define PIN_SELECT    18
#define PIN_START     2
#define PIN_L3        6
#define PIN_R3        9
#define PIN_PS        1
```

### How to upload

When you reflash AVR boards with USB HID device software, Arduino IDE cannot automatically reset and flash the software.
You will need to press reset button on the AVR board (SW_RST1 on ergoSHIFT) to put it into Bootloader mode to reflash.
When you use Sparkfun Qwiik ProMicro 5V, you will need to double-click the reset button to put it into Bootloader.

I recommend setting up VSCode Arduino plugin.  If you open this directory with VSCode, it is already set up so all you need to do is
run Arduino: Verify from the command pallet (You will still need to install Arduino, Bounce Library and add the LUFA board manager URL before you can run verify).
The .hex file will be created in the Build folder.

Take the .hex file and use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) to flash the .hex file.

In QMK Toolbox, Press OPEN and select the .hex file you just created, (or just use the one in the repository).  Select ATMega32U4 from the dropdown menu at the top right corner.
Click the Reset button on the Pro-Micro (Double-Click on Qwiik ProMicro USB-C variant).  When you see the "Caterina device connected (usbser): ~~~" text, press Flash button.

This method, while requires extra software setups, is more reliable than trying to time the Reset while Arduino IDE is doing it's thing...
