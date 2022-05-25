# Measuring Temperatures with PT1000-Sensor v1.1
High accurate Temperature-measures (down to ±0.1°C) with Adafruits MAX31865 Module and a *small* PT1000-Sensor,
using an ATMega328(Arduino) and an OLED-Module (connected via I2C) to view Reults in °C.

A description + instructions of the MAX31865 Module from Adafruit we can read on their site:
https://learn.adafruit.com/adafruit-max31865-rtd-pt100-amplifier/

I used a *small* PT1000-Sensor from Delta-R (=> https://delta-r.de/de/elemente/pt/pt-1.000/pt-1000-2b/38/2x2-pt1000-2b-7500c),
due to the fact that a PT1000 has more voltage amplitude (to measure) as a PT100, so precision of reading per default is more precise
and has fewer noise and resistances (on cables). A small Sensor like this above is also much faster reaching the objects temperature
to measure (fewer time-loss waiting for "ready").
But preciseness of reading the real temp. also depends on how we connect the Sensor physically to the measured Object.
I use a small bit of Thermal Paste between the PT1000-Sensor and the measuring-object (Att.: Sensor connected before heating the object ;-).

The translation of the small read voltage isn't analogue as used often in old boards with PTCs (PositiveTemperatureCoefficient Sensor)
obtaining bad results because "noise", added resistances and offset-voltages from cables, etc. as described above.
So through SPI-Connection (4 cables + GND/V+) and short connections there are not so many possible measuring faults...
The Arduino-Code from Adafruit is really simple, (see file "Adafruit_MAX31865_PT100-P1000-RTD-Sensor.ino"), using the Adafruit-Library:
https://github.com/adafruit/Adafruit_MAX31865 (download).

Converting the Readings (measured values) for the small I2C-OLED-Output (128x64px):
I choosed Temperature in °C to be the only value from interest. So for good readability I used a bigger and (IMHO) nicer font as the
default fonts provided from Adafruit-GFX-library.
Downloaded "FreeSansBold.ttf", modified with the (free) App "FontForge" using therein only the essential necessary letters: number
44 to 67 from ASCII-Table) to minify RAM-consumption in the ATMega328.
I compiled this resulted .ttf-font with "fontconvert.exe" to a usable Bitmap-font, named "FreeSnBld12pt7b.h" to use for the OLED.
If you like it, feel free to use it without restrictions besides the licensing of the original font ("FreeSansBold.ttf"), which is
(IMHO) a nicer Sans-Serif font on a small OLED as used.
