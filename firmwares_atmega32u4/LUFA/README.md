[日本語はこちら](README_ja.md)

## LUFA Switch/XInput hybrid Fightstick firmware

This firmware is a derivative of the awesome [LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick) by [CrazyRedMachine](https://github.com/CrazyRedMachine)

## Acknowledgments

This work is a fork of [LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick) by [CrazyRedMachine](https://github.com/CrazyRedMachine) and
is based on [fluffymadness' ATMega32U4-Switch-Fightstick](https://github.com/fluffymadness/ATMega32U4-Switch-Fightstick)
and [bootsector's XInputPadMicro](https://github.com/bootsector/XInputPadMicro), with a QoL features added by CrazyRedMachine.

This fork is customized for the needs of ergoSHIFT features

* Remapped keys to work with ergoSHIFT layout
* Removed support for analog stick
* reorganized the customization button settings for SOCD and other features
    * SOCD config is now only at startup and only provide three common modes (All Neutral, Hitbox and Gafro)
    * Added feature to configure vertical input inversion.  Useful when using Hitbox layout on non-fighting games.

## Features

### Gamepad modes

Hold "select" as you plug the controller to make it a Nintendo Switch controller.

Hold "start" as you plug the controller to make it an XInput controller.

Gamepad mode is persistent across plugging and unplugging the controller, so if you don't press anything while plugging the controller, it will stay in the last used mode. 

### DPAD modes

You can switch seamlessly between the 3 stick modes by pressing START+SELECT+(LEFT/UP/RIGHT)

- UP: DPAD 
- LEFT: Fake Left Analog (DPad is mapped to L-Analog)
- RIGHT: Fake Right Analog (DPad is mapped to R-Analog)

DPAD mode is also persistent.

### Real analog support

This function has been removed since ergoSHIFT has no plans of adding analog inputs

### Simulated home button

This is also removed since we have custom hardware that support home buttons

### SOCD Cleaning

* HOME at startup = All NEUTRAL
* RS at startup = Hitbox style SOCD cleaning (Up+Down=Up, Left+Right=Neutral)
* LS at startup = Gafro style SOCD cleaning (Up+Down=Up, Left+Right=Last Input)

You can use the Reset button on the ergoSHIFT while holding the buttons above to change mode.

### UP-DOWN inverse

Since ergoSHIFT is a Hitbox style controller, Up and Down button layout is a little convoluted for normal use outside its fighting game use-case.
I have added inverting the UP/DOWN input as a feature so the controller can be used a little easier on normal games... (although it still feels a little unweildy TBH.)

* To invert UP and DOWN inputs, press UP at startup.
* To set to normal mode, press DOWN at startup.

## Building Instructions

- Download Arduino IDE, 
- Download the Bounce2 Library inside the Arduino IDE
- Add `https://github.com/CrazyRedMachine/Arduino-Lufa/raw/master/package_arduino-lufa_index.json` as an Additional Board Manager URL (in `File -> Preferences` menu)
- Install LUFA AVR Boards from the Board Manager
- Select Arduino Leonardo (LUFA) as your board type (Pro-Micro is a compatible board to Leonardo)
- Upload the code and Have Fun

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

## Pinout

Configurable in the .ino

The key config is already setup to match ergoSHIFT wiring.

```C
/* PINOUT (follows Nintendo naming (X=up, B=down)) */
#define PIN_UP    7
#define PIN_DOWN  4
#define PIN_LEFT  3
#define PIN_RIGHT 5
#define PIN_A     MISO         //XBOX B
#define PIN_B     10           //XBOX A  
#define PIN_X     15           //XBOX Y
#define PIN_Y     MOSI         //XBOX X     
#define PIN_L     21           //XBOX LB
#define PIN_R     20           //XBOX RB
#define PIN_ZL    8            //XBOX LT
#define PIN_ZR    19           //XBOX RT
#define PIN_LS    6            //XBOX LS (left analog click)
#define PIN_RS    9            //XBOX RS (right analog click)
#define PIN_PLUS  2            //XBOX START
#define PIN_MINUS 18           //XBOX BACK
#define PIN_HOME  1
```

For southpaw version, swap the PIN_LEFT and PIN_RIGHT definition and recompile.

```C
/* PINOUT (follows Nintendo naming (X=up, B=down)) */
#define PIN_UP    7
#define PIN_DOWN  4
#define PIN_LEFT  5
#define PIN_RIGHT 3
#define PIN_A     MISO         //XBOX B
#define PIN_B     10           //XBOX A  
#define PIN_X     15           //XBOX Y
#define PIN_Y     MOSI         //XBOX X     
#define PIN_L     21           //XBOX LB
#define PIN_R     20           //XBOX RB
#define PIN_ZL    8            //XBOX LT
#define PIN_ZR    19           //XBOX RT
#define PIN_LS    6            //XBOX LS (left analog click)
#define PIN_RS    9            //XBOX RS (right analog click)
#define PIN_PLUS  2            //XBOX START
#define PIN_MINUS 18           //XBOX BACK
#define PIN_HOME  1
```

## Donation

If this project helped you, please consider going to the original works and donate to the source work ;)
