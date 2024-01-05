GP2040-CE Firmware
========================================================================

ergoSHIFT rev.2
------------------------------------------------------------------------

rev.2 uses [GP2040-CE firmware](https://gp2040-ce.info/).

Since the firmware build for ergoSHIFT is currently not available from
the project site, here are the files necessary to make the rev.2 working

### Prebuilt firmware file

If you just want the thing to work, download the
[Prebuilt Firmware](./GP2040-CE_0.0.0_ergoSHIFTRev2.uf2) file, connect
the board to your PC, when you see a USB thumbdrive mounted called `RPI-RP2`,
just drag and drop the firmware file.

If you don't see the `RPI-RP2`, Hold down the `BOOT` button (the side tactile 
switch on the left) and press the `RST` button (the side tactile swith with
`SW_RST1` label).

### Building your own firmware

You can use the [Config files](./ergoSHIFTRev2/) and follow the instructions
in the original [GP2040-CE firmware](https://gp2040-ce.info/) website.

Building instructions should be found under `Contribute -> Firmware Development`

### Resetting firmware

If you have some issues with you firmware, you may want to reset the flash
memory first by dragging and dropping the [flash_nuke.uf2](./flash_nuke.uf2)
to the `RPI-RP2` 