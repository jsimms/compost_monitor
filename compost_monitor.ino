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
    - define ip/sitename and directory that we are sending data
    
    - connect to wifi network 
    - check DHCP? 
     
    - make humidity and temp a string 
    - send http request 
    
    - create send_request function 
    - connect to proper ip/server 
    - send the request 
    - read answer 

    - Fix SHT11 hardware (software is a-ok)
    
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
//Create the CC3000 instance (The SPI library sets remaining pins, for the uno: SCK = 13, MISO = 12, MOSI = 11)  
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                       SPI_CLOCK_DIVIDER);

// define SHT11 pins 
const int DATA_PIN  = 6;  // Blue wire! 
const int CLOCK_PIN = 7;  // Yellow wire!
//Creates the SHT11 instnace 
SHT1x sht11 (DATA_PIN, CLOCK_PIN); 


// Provide Your Wifi Network Information
const char* WIFI_SSID = ""; // must be less than 32 characters 
const char* WIFI_PASS = ""; 
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2, and I guess it is an int
const int WLAN_SECURITY =  WLAN_SEC_UNSEC;  





void setup(void) 
{
  Serial.begin(9600); 
  Serial.println("If you start me up..."); 
  
  /* Initialise the CC3000 */
  Serial.println(F("\nInitialising the CC3000 ..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while(1);
  }
  
  /* Delete any old connection data on the module */
  Serial.println(F("\nDeleting old connection profiles"));
  if (!cc3000.deleteProfiles()) {
    Serial.println(F("Failed!"));
    while(1);
  }
  
}

void loop(void)
{  
  // create variables and read values from the sensor  
  float temp_f = sht11.readTemperatureF(); 
  float humidity = sht11.readHumidity();  
  
  // print it to serial port 
  Serial.print("Temperature: ");
  Serial.print(temp_f, DEC); 
  Serial.print(" F /");
  Serial.print("Humidity: ");
  Serial.print(humidity); 
  Serial.print("%"); 
  Serial.println(""); 
  Serial.println(WIFI_SSID); 
  Serial.println(WIFI_PASS);
  Serial.println(WLAN_SECURITY); 
  
  // include at least a 3.6 second delay between pairs of temperature & humidity measurements.
  delay(4000); 
   
}


// This is the function that the wifi weather station used in their example 
void send_request (String request) 
{
  // code goes here 
} 


