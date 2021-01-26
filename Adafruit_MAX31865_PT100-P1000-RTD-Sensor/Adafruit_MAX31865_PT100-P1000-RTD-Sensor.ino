/*************************************************** 
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <Adafruit_MAX31865.h>

#include <Wire.h>               //I2C communication library to communicate with OLED-Display

//+LCD-library:
#include <Adafruit_GFX.h>       //Graphics library
#include <Adafruit_SSD1306.h>   //OLED display library
#include <Fonts/FreeSnBld12pt7b.h> //Include a (selfmade) bigger display-font (12x7pt=17x12px) to display the temperature - see instruction @ the end!

#define OLED_RESET 9            //(free) Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET); //Set OLED display to the present real size

//Prepare the MAX31865 Module:
// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      4300.0  //nl: calibrate this value using a precise Mutltimeter!
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  1000.0

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test!");

  thermo.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary //nl: using *short* wires, sowe need only 2-wires !

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Set the I2C-Adress for the display !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // by default, the high voltage is generated from the 3.3V line internally
  display.begin (SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C or 0x3D (Adafruit-default = 0x3D)
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  display.setTextSize(1);   //Set default font size to the smallest available (default)
  display.setTextColor(WHITE); //Set font to display white color on black background
  display.invertDisplay(0); //Set display to normal video (white fonts and drawings over black background, "1" is viceversa)
  display.setFont(&FreeSnBld12pt7b); //display values with a bigger and fewer RAM consumed font (= modified freefont)
}


void loop() {
  uint16_t rtd = thermo.readRTD();
//============ Prining collecteddata on a Serial-Output ============
Serial.print("RTD value: "); Serial.println(rtd); // Resistance value of the RTD (here PT1000)
//  float ratio = rtd;
//  ratio /= 32768;

//  Serial.print("Ratio = "); Serial.println(ratio,8);
//  Serial.print("Resistance = "); Serial.println(RREF*ratio,8);
  Serial.print("Temperature = "); Serial.println(thermo.temperature(RNOMINAL, RREF));

  // Check and print any faults on a Serial-Line:
  uint8_t fault = thermo.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    thermo.clearFault();
  }
  Serial.println();
//============ End of Serial-Output ============

//************** Display the Temperature on the OLED-Display in gC: **************
  display.clearDisplay(); //Clear display buffer from last cycle to begin drawing new display-values:
  //display.print("RTD value: "); display.println(rtd); //print the read RTD value 
  display.setCursor(20, 40); //Position cursor...
  int i = thermo.temperature(RNOMINAL, RREF); //transform float to int
  if (i < 100) {display.print("  ");} //align the temp. at right-side
  if (i < 1000) {display.print(" ");}
  //display.println(rtd); //nl: not need to display Resistance-value of the RTD (PT1000) here
  display.print(thermo.temperature(RNOMINAL, RREF)); //display the Temperature in gC
  ////display.drawCircle(100,32,1,WHITE); //Draw a degree symbol after temperature
  display.print(";C"); //Display "gC" (modified ttf-library: ';' => 'small circle', "fontconvert.exe FreeSansBold.ttf 12 44 67 > FreeSnBld12pt7b.h" (see aloso Adafruit_GFX_Library)
  //display.print(" C");
  display.display(); //write values in buffer onto the Display
// *********** End OLED-Display ***********
  
  delay(1000);
}
