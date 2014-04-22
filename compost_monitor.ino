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
    - define CC3000 pins
    - define wifi connection info 
    - define SHT11 pins
    - define ip/sitename and directory that we are sending data
    
    - initialize cc3000 and SHT11 
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
#include <SHT1x.h>

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


