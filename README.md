# Measuring-Temperatures-with-PT1000-Sensor
High accurate Temperature-measures with Adafruits MAX31865 Module and a *small* PT1000-Sensor,
using an ATMega328(Arduino) and an OLED-Module (connected via I2C).

With the MAX31865 Module from Adafruit we can use their description / instructions:
https://learn.adafruit.com/adafruit-max31865-rtd-pt100-amplifier/

I used a *small* PT1000-Sensor from Delta-R (=> https://delta-r.de/de/elemente/pt/pt-1.000/pt-1000-2b/38/2x2-pt1000-2b-7500c),
due to the fact that a PT1000 has more voltage amplitude (to measure) as a PT100, so precision of reading per default has fewer noise
and a small Sensor like this above is much faster in reaching the objects temperature to measure (fewer time-loss waiting for "ready").

The translation isn't analogue, so through SPI-Connection (4 cables + GND/V+) there are not so many possible measuring faults...
The Arduino-Code here is really simple, (see file "Adafruit_MAX31865_PT100-P1000-RTD-Sensor.ino"), using the Adafruit-Library:
https://github.com/adafruit/Adafruit_MAX31865 (download).

