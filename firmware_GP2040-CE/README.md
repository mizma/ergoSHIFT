GP2040-CE Firmware
========================================================================

ergoSHIFT rev.2
------------------------------------------------------------------------

rev.2 uses [GP2040-CE firmware](https://gp2040-ce.info/).

Since the firmware build for ergoSHIFT is not available from
the project site, here are the files necessary to make the rev.2 working

### Prebuilt firmware file

If you just want the thing to work, download the
[Prebuilt Firmware](./GP2040-CE_0.7.7_ergoSHIFTRev2.uf2) file, connect
the board to your PC, when you see a USB thumbdrive mounted called `RPI-RP2`,
just drag and drop the firmware file.

If you don't see the `RPI-RP2`, Hold down the `BOOT` button (the side tactile 
switch on the left) and press the `RST` button (the side tactile swith with
`SW_RST1` label).

### Building your own firmware

You can use the [Config files](./ergoSHIFTRev2/) and follow the instructions
in the original [GP2040-CE firmware](https://gp2040-ce.info/) website.

Building instructions should be found under `Contribute -> Firmware Development`

#### Pin assignments of ergoSHIFT Rev.2

Here are the Default Pinout and Button map information.

~~~C
//                          // GP2040 | Xinput | Switch  | PS3/4/5  | Dinput | Arcade |
#define PIN_DPAD_UP     12  // UP     | UP     | UP      | UP       | UP     | UP     |
#define PIN_DPAD_DOWN   9   // DOWN   | DOWN   | DOWN    | DOWN     | DOWN   | DOWN   | 
#define PIN_DPAD_RIGHT  11  // RIGHT  | RIGHT  | RIGHT   | RIGHT    | RIGHT  | RIGHT  | 
#define PIN_DPAD_LEFT   6   // LEFT   | LEFT   | LEFT    | LEFT     | LEFT   | LEFT   | 
#define PIN_BUTTON_B1   18  // B1     | A      | B       | Cross    | 2      | K1     |
#define PIN_BUTTON_B2   19  // B2     | B      | A       | Circle   | 3      | K2     |
#define PIN_BUTTON_R2   23  // R2     | RT     | ZR      | R2       | 8      | K3     |
#define PIN_BUTTON_L2   16  // L2     | LT     | ZL      | L2       | 7      | K4     |
#define PIN_BUTTON_B3   20  // B3     | X      | Y       | Square   | 1      | P1     |
#define PIN_BUTTON_B4   25  // B4     | Y      | X       | Triangle | 4      | P2     |
#define PIN_BUTTON_R1   26  // R1     | RB     | R       | R1       | 6      | P3     |
#define PIN_BUTTON_L1   24  // L1     | LB     | L       | L1       | 5      | P4     |
#define PIN_BUTTON_S1   27  // S1     | Back   | Minus   | Select   | 9      | Coin   |
#define PIN_BUTTON_S2   0   // S2     | Start  | Plus    | Start    | 10     | Start  |
#define PIN_BUTTON_L3   10  // L3     | LS     | LS      | L3       | 11     | LS     |
#define PIN_BUTTON_R3   17  // R3     | RS     | RS      | R3       | 12     | RS     |
#define PIN_BUTTON_A1   2   // A1     | Guide  | Home    | PS       | 13     | ~      |
#define PIN_BUTTON_A2   1   // A2     | ~      | Capture | ~        | 14     | ~      |
#define PIN_BUTTON_FN   -1  // Hotkey Function                                        |

#define HAS_I2C_DISPLAY 1
#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5
#define I2C_BLOCK i2c0
#define I2C_SPEED 400000
#define DISPLAY_FLIP 0      // set to 1 for southpaw
#define DISPLAY_INVERT 0

#define BUTTON_LAYOUT BUTTON_LAYOUT_STICKLESS
#define BUTTON_LAYOUT_RIGHT BUTTON_LAYOUT_STICKLESSB
#define SPLASH_MODE SPLASH_MODE_STATIC
#define SPLASH_CHOICE SPLASH_CHOICE_MAIN
#define SPLASH_DURATION 7500
~~~

![Button Map](./ergoSHIFTRev2/assets/ergoSHIFT-rev2-button-mapping.jpg)

### Setting for southpaw

You will need to change the Pin mapping and a few settings on the OLED Screen.
Using the Web Config is the easiest route.

* To enter Web Config, connect your board to a PC and press `RESET` while holding down `S2`
* Use a browser to access http://192.168.7.1/
    * If your Wifi, LAN or any other network is configured to use 192.168.7.* address,
      you may need to disconnect you Wifi/LAN while you configure your board.
* In the Configuration -> Pin Mapping change the following
    * Set PIN06 to `Right`
    * Set PIN11 to `Left`
* In the Configuration -> Display Configuration
    * Set Flip Display to `Flip and Mirror`

### Resetting firmware

If you have some issues with you firmware, you may want to reset the flash
memory first by dragging and dropping the [flash_nuke.uf2](./flash_nuke.uf2)
to the `RPI-RP2` and wait patiently until the `RPI-RP2` reconnects
