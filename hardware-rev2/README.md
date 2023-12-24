ergoSHIFT rev2
========================================================================

_**DESIGN NOT VERIFIED**_

This is rev2 of the ergoSHIFT.  In this version, RP2040 circuitry is
implemented on the PCB.

To make one you will need:

* [acrylic shell](./acrylic-shell/)
    * For Standard Layout stackup (From bottom to top)
        * acryl-design-ergoSHIFT-Acrylic-layer-01: 3mm
        * acryl-design-ergoSHIFT-Acrylic-layer-02: 3mm
        * PCB
        * acryl-design-ergoSHIFT-Acrylic-layer-03: 3mm
        * acryl-design-ergoSHIFT-Acrylic-layer-04: 3mm
        * acryl-design-ergoSHIFT-Acrylic-layer-05: 2mm
    * For Reverse Layout (Left handed, from bottom to top)
        * acryl-design-ergoSHIFT-Acrylic-layer-01: 3mm
        * acryl-design-ergoSHIFT-Acrylic-layer-03: 3mm (to compensate for PCB being flipped upside down)
        * PCB
        * acryl-design-ergoSHIFT-Acrylic-layer-03: 3mm
        * acryl-design-ergoSHIFT-Acrylic-layer-04: 3mm
        * acryl-design-ergoSHIFT-Acrylic-layer-05: 2mm
* [the ergoSHIFT PCB](./pcb/)
* 15x Kailh low profile (choc v1) switches of your choice
    * I use Kailh Choc v1 Red Pro (Linear and low activation force: 35±10gf with actuation travel: 1.5±0.5mm)
    * Light Blue (gChoc) can be used for even lower actuation force.
* (optionally) 15x Kailh low profile hotswap sockets
* (optionally) SSD1306 driver based 0.96 inch OLED module with PCB size 26mm x 26mm
    * In this case, R8 and R9 on PCB are not necessary.
* Button Caps (Choose one)
    * [MICRO keycap set](https://junkfoodarcades.com/collections/micro-accessories)
        * You will need to buy two sets of Snackbox Micro keycap sets.
    * [3D printed buttoncaps](../3d-printed-buttoncaps)
        * Not yet ready
* 3x 6x6x8.51mm tact switches
    * I Used [TE Connectivity 3-1825910-5](https://www.te.com/ja/product-3-1825910-5.html)
* 2x 3x6x4.3 horizontal tact switch
    * https://www.newegg.com/p/2S7-01KR-035X0
    * https://shop.yushakobo.jp/collections/all-keyboard-parts/products/a1600ed-01-1
    * You can also order from LCSC with part number [C18078123](https://www.lcsc.com/product-detail/Tactile-Switches_Bossie-BX-TS-26-3643ZJ_C18078123.html)
    * [schematics](images/tactile-switch_3x6x4.3.jpg)
* 7x M3 screws (length 20mm)
    * Acryl top 2mm * 2 + 3mm = 7mm
    * PCB 1.6mm
    * Acryl bottom 3mm * 2 = 6mm
    * Rubber feet screw depth = 3mm (using rubber feet below.  adjust for your part)
    * Rubber feet total depth = 8mm (using rubber feet below.  adjust for your part)
    * M3 nut height = 2mm
    * min length = 19.6mm (using rubber feet below.  adjust for your part)
    * max length = 22.6mm (using rubber feet below.  adjust for your part)
* 7x M3 nut and acompanying rubber feet
    * Rubber feet Tochigiya [TM-TK-15](https://www.monotaro.com/p/0933/2486/?displayId=5)
    * The position of the holes are intended for feet radius of less than 8mm
* a soldering iron
    * something with enough power is better 
      (i.e. [Hakko FX 600](https://www.hakko.com/japan/products/hakko_fx600_set.html))
    * I recommend changing tips to D type for most Through-hole soldering, or C type if you plan to
      solder SMT as well. (default B tips are harder to use for most PCB soldering)
    * Use 230C ~ 250C temp recommended (can be changed if you know your way around)

## Assembly Instructions

### Ordering PCB

I used [JLCPCB](https://jlcpcb.com/).  Just upload the gerber files in [pcb](pcb) and keep most parameters default.
You may change PCB Qty and PCB Color if you like.  All other parameters should be kept the same.

#### SMT assembly

You may either order the stencil when ordering PCB and impelemnt the parts yourself, or you can select Part
assembly and use the BOM file and CPL file in [pcb](pcb).  You may need to adjust the rotation, placement
of some parts in CPL, check before you order.  It should look like the following.

![parts placement](./images/parts_placement.png)

### Ordering Buttons

#### Snackbox Micro button caps

ergoSHIFT is compatible with Snackbox Micro button caps.

You can purchase them [HERE](https://junkfoodarcades.com/collections/micro-accessories)

#### 3D printed buttons

_**NOT IMPLEMENTED**_

If you have a 3D printer, print at your own will.  Files are found [here](../3d-printed-buttoncaps/).

* [ergoSHIFT-ButtonCapBig.stl](../3d-printed-buttoncaps/ergoSHIFT-ButtonCapBig.stl) 
  is used for the thumb button. 1 board needs 1 of this button.
* [ergoSHIFT-Buttoncap.stl](../3d-printed-buttoncaps/ergoSHIFT-ButtonCapBig.stl) is used for all ther buttons.
  1 board needs 11 of this button.
* [ergoSHIFT-FullSetButtonCaps.stl](../3d-printed-buttoncaps/ergoSHIFT-FullSetButtonCaps.stl) is an STL file 
  containing 1 full set of buttons (11 small and 1 big.).  If your 3D printing service allows 12 or more shells,
  it may be cheaper to print in one batch using this STL file.
    * Print size needs to be bigger than X：99.0000mm x Y： 93.5000mm x Z： 6.0000mm

Insertion portion may need to be adjusted in size for your 3D Printer and settings to fit snugly to the switch.
You may use some of the printer features but if that doesn't work, you might want to edit the original model.
Model data are found in the same directory in a [FreeCAD](https://www.freecadweb.org/) file format.

Also, since the insertion portion requires a fairly tight tolerance which is not easily achieved by 3D printers.
To that extent, the models are modelled slightly on the larger side.  I have had fairly good results with this model using SLS Nylon print but sometimes it is too large.  Which can be filed down to fit.

#### Materials Consideration

* Nylon
    * May be a good place to start for tensile strength and good chemical stability.
    * can be pretty strong if printed using SLS process at some printing services
    * may be prone to warping.  not good for humid places.
* UV Resin
    * Also pretty strong as a material, and stronger to humidity.
    * Maybe slightly more brittle than Nylon

### Ordering Acrylic cuts

I use [Elecrow](https://www.elecrow.com/acrylic-cutting.html) to cut acrylic.

Upload the .zip file in [acrylic-shell](acrylic-shell/) to the Elecrow Acrylic cut service to order.
.Zip file includes the dxf file and the dimentions.txt file.  PDF is just for reference.

Use the following thickness:

* For Standard Layout stackup (From bottom to top)
    * acryl-design-ergoSHIFT-Acrylic-layer-01: 3mm
    * acryl-design-ergoSHIFT-Acrylic-layer-02: 3mm
    * PCB
    * acryl-design-ergoSHIFT-Acrylic-layer-03: 3mm
    * acryl-design-ergoSHIFT-Acrylic-layer-04: 3mm
    * acryl-design-ergoSHIFT-Acrylic-layer-05: 2mm
* For Reverse Layout (Left handed, from bottom to top)
    * acryl-design-ergoSHIFT-Acrylic-layer-01: 3mm
    * acryl-design-ergoSHIFT-Acrylic-layer-03: 3mm (to compensate for PCB being flipped upside down)
    * PCB
    * acryl-design-ergoSHIFT-Acrylic-layer-03: 3mm
    * acryl-design-ergoSHIFT-Acrylic-layer-04: 3mm
    * acryl-design-ergoSHIFT-Acrylic-layer-05: 2mm

The original design file (FreeCAD file) can be found [here](./design_data/acryl-design/).

The Acrylic should look like the following (with PCB stacked)

![ergoSHIFT-rev2-Acrylic-Stack](./images/acryl-shell-stackup.png)

(*) Above image is for standard layout (right handed)

### Assembly

1. Solder all the Choc v1 switches and the tactile switches.  make sure you populate the side with the logo.
    * If you populate the side with the logo on the left, the parts only goes in in the correct orientation.
        * For reverse layout, implement the buttons on the other side.
    * If you use the hot-swap sockets, those will go on the other side. (see silk screen on back side for orientation)
        * For hotswap sockets, pre-solder one side of the pad on PCB, place the socket, heat the pre-solder while
          pressing down on the socket to attach the socket.  After It is attached, solder the other side fully and then add more solder on the pre-soldered side.
3. stack the Acryl and PCB in following order: Layer 01, Layer 02, PCB, Layer 03, Layer 04 and Layer 05.
    * for reverse layout, stack in the order: Layer 01, Layer 03, PCB, Layer 03, Layer 04 and Layer 05.
4. Screw on the M3 screws with the nut on all 7 locations.  Rubber feet should be inserted at least in the 4 corners between the nut and the acrylic.

It should look like the following when assembled.

![ergoSHIFT-rev2](images/ergoSHIFT-rev2-bare.jpg)

### Pro-Tip 1. Filing the Acrylic Edges

Acrylic Edges after laser cutting can be quite sharp and do not feel good.
You may want to file the edges with sandpaper (#400 is a nice place to start) to remove the edges 
on the top acrylic layer so it does not feel bad.

### Pro-Tip 2. Customizing design

You can also insert some artwork below the top acrylic layer as below:

![ergoSHIFT-rev2_with_artwork1](images/ergoSHIFT-rev2-final01.jpg)
![ergoSHIFT-rev2_with_artwork1](images/ergoSHIFT-rev2-final02.jpg)
![ergoSHIFT-rev2_with_artwork2](images/ergoSHIFT-rev2-final03.jpg)

(*) Above sample Artwork based on a trace of In-Game Screenshot + Official Fan-kit (©ARK SYSTEM WORKS)

Stencil for the artwork can be found below (Page Size set to A4):

* [Stencil SVG](./images/ergoSHIFT-stencil-with-OLED.png)
* [Stencil PNG 300dpi](./images/ergoSHIFT-stencil-with-OLED.png)
* [Southpaw Stencil SVG](./images/ergoSHIFT-stencil-with-OLED-reversed.svg)
* [Southpaw Stencil PNG 300dpi](./images/ergoSHIFT-stencil-with-OLED-reversed.png)

To cut the stencil, use one of the top acrylic plates as cutting guides (don't trust the acuracy
of the printed stencil mark, they are good enough to use as design guide, but not acurate enough for 
final cutting guide).  It is easy to cut if you tape the plate on top of the print.

![Stencil-Cutting](images/Stencil-Cutting.jpg)

## License and Acknowlegements

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a>

PCB design licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) by mizma

Acrylic sandwitching shell heavily inspired by [Mille-Feuille](https://pomegd.booth.pm/items/2685530) 
by [@pomegd](https://twitter.com/pomegd)

PCB design uses the following libraries or derivatives of the design:

* [keyswitches.pretty](https://github.com/daprice/keyswitches.pretty) by [daprice](https://github.com/daprice) ([CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/))
* [Type-C.pretty](https://github.com/ai03-2725/Type-C.pretty) by [ai03-2725](https://github.com/ai03-2725)
* RP2040 library from [Hardware design with RP2040](https://datasheets.raspberrypi.org/rp2040/hardware-design-with-rp2040.pdf) Chapter 2.
  Minimal design example.
