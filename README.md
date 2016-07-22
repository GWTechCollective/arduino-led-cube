# arduino-led-cube
Code for driving the GWTC LED Cube Arduino shield.

![alt tag](https://d1q9wbuypc40mm.cloudfront.net/r8tzliafieq2p6p_710.jpg)

There are two versions of this project. The one named "led-cube" is the original code. This version is compatible with the sample patterns that are provided.

The newer version, named "led-cube-interrupts" is a rewrite of the original code that reduces the memory footprint of the program. The patterns are stored more efficiently, but there are only two patterns provided in the code.

## Creating Patterns

### Old Version
In the original version of the program, the cube state was represented by a 2D char array. Each row of the array corresponds to one layer of the LED cube. A group of three rows represents the entire cube since there are three layers in the cube. Each element in the array represents an LED, so you can create patterns simply by specifying if the LED should be ON (1), or OFF (0).

### New Version
Rather than wasting an entire char to store what is essentially a single bit of information, the newer version compresses each row of the 2D array from the old version into a single 16-bit int. Patterns are made the same way, except now the ON and OFF states are stored as bits in an int. The example pattern uses hexadecimal notation. You may wish to use Arduino's binary notation if you aren't comfortable with hex conversion.
