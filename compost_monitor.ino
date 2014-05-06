/*************

  This sketch is for a passive compost monitoring device that measures
  temperature and humidity. 

  It uses the following products:
  
  Adafruit CC3000 Wifi Breakout & Shield 
  https://www.adafruit.com/products/1469

  SHT11 Tempurature and Humidity Sensor 
  http://www.adafruit.com/product/1298
  
  Thanks to Adafruit and Jonathan Oxer for their libraries and examples: 
  https://github.com/adafruit/Adafruit_CC3000_Library
  https://github.com/practicalarduino/SHT1x
  
  Also thanks to Open Home Auotmations for their wifi-weather example: 
  https://github.com/openhomeautomation/wifi-weather-station
  
************/ 
 
/* Todo
    - define wifi connection info 
    - define ip/sitename and directory that we are sending data
    
    - connect to wifi network 
    - check DHCP? 
    
    - measure humidity & temperature 
    - make humidity and temp a string 
    - print the data to serial port 
    - send http request 
    - update every second 
    
    - create send_request function 
    - connect to proper ip/server 
    - send the request 
    - read answer 
    
 */


// Include required libraries 
#include <Adafruit_CC3000.h>
#include <Adafruit_CC3000_Server.h>
#include <ccspi.h>
#include <string.h>
#include <SPI.h>
#include <SHT1x.h>
#include "utility/debug.h"

// define CC3000 pins 
const int ADAFRUIT_CC3000_IRQ  =  3;   // IRQ Must be on an interrupt pin! 
const int ADAFRUIT_CC3000_VBAT =  5;   // Can be any pin 
const int ADAFRUIT_CC3000_CS   =  10;  // Can be any pin 
//The SPI library sets remaining pins, for the uno: SCK = 13, MISO = 12, MOSI = 11  

// define SHT11 pins 
const int DATA_PIN  = 6;  // Blue wire! 
const int CLOCK_PIN = 7;  // Yellow wire! 

//Initialize the CC3000 
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                       SPI_CLOCK_DIVIDER);

//Initialize the SHT11
SHT1x sht1x (DATA_PIN, CLOCK_PIN); 


void setup(void) 
{
  // code goes here 
}

void loop(void)
{
  // code goes here 
}


// This is the function that the wifi weather station used in their example 
void send_request (String request) 
{
  // code goes here 
} 


