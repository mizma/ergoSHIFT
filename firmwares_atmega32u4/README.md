# ATMEGA32U4 Firmwares

[日本語はこちら](README_ja.md)

There are currently two firmwares that is customized to work with ATMEGA32U4 5V AVR version of the Flatbox ACR boards (3.3V board are not supported).

Both controllers should work similarly in terms of SOCD cleaning configuration and Up/Down inversion configuration.

Firmware            | [DINPUT](DINPUT)      | [LUFA](LUFA)          |
------------------- | :-------------------: | :-------------------: |
DInput              | **YES**               | NO                    |
XInput              | NO                    | **YES**               |
PS3                 | **YES**               | NO                    |
Switch              | NO                    | **YES**               |
SOCD                | Hitbox,Gafro,NEUTRAL  | Hitbox,Gafro,NEUTRAL  |
Vertical Inversion  | **YES**               | **YES**               |
DPAD emulation      | **YES**               | **YES**               |
Fake Left Stick     | NO                    | **YES**               |
Fake Right Stick    | NO                    | **YES**               |

## Configuration

All following settings are persistent and will be kept over power cycles or resets.

| Firmware          |                       | DINPUT            | LUFA                  |
| :---------------- | :-------------------: | :---------------: | :-------------------: |
| Up/Down Inversion | Normal                | Down + Reset      | Down + Reset          |
|                   | Invert                | Up + Reset        | Up + Reset            |
| SOCD Cleaning     | Hitbox mode           | R3(RS) + Reset    | R3(RS) + Reset        |
|                   | Gafro Mode            | L3(LS) + Reset    | L3(LS) + Reset        |
|                   | Neutral Mode          | PS(HOME) + Reset  | PS(HOME) + Reset      |
| Change Input Mode | Xinput                | Not Supported     | "Start" + Reset       |
|                   | Switch                | Not Supported     | "Select" + Reset      |
|                   | DInput/PS3            | Default           | Not Supported         |
| Direction Mode    | DPAD                  | Default           | UP+START+SELECT       |
|                   | Left Analog Stick     | Not Supported     | LEFT+START+SELECT     |
|                   | Right Analog Stick    | Not Supported     | RIGHT+START+SELECT    |

For Key Combos using Reset, Reset should be clicked once while holding the other input.
Wait for the controller to reset and connect to the PC/Console before releasing the input.

You can print [this cheat sheet](ergoSHIFT_Hotkey_Cheatsheet.pdf) to insert in the back
of your ergoSHIFT (PageSize: B5)

## [DINPUT](./DINPUT/)

This firmware is based on the original Flatbox firmware and is configured to work as Dinput device.
Simple firmware to work on if you only need Dinput support or want to connect it to PS3 
(Should work as PC Dinput and PS3 controller).

## [LUFA](./LUFA/)

This firmware is based on the [LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick) by [CrazyRedMachine](https://github.com/CrazyRedMachine)
and supports XInput mode and Switch controller mode (gets detected as Pokken Controller).

This firmware can be switched between Xinput (consoles not supported, only PCs) mode and Switch controller mode.
