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

// define sht10 pins
const int DATA_PIN  = 6;  // Blue wire!
const int CLOCK_PIN = 7;  // Yellow wire!

//Creates the sht10 instnace
SHT1x sht10 (DATA_PIN, CLOCK_PIN);

// Provide Your Wifi Network Information
const char* WIFI_SSID = "yourWifi"; // must be less than 32 characters
const char* WIFI_PASS = "yourWifiPass";
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2, and I guess it is an int
const int WIFI_SECURITY =  WLAN_SEC_WPA2;

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data
                                   // received before closing the connection.  If you know the server
                                   // you're accessing is quick to respond, you can reduce this value.

// Server settings and info (where you want to send requests)
#define HOST      "weathervane.herokuapp.com"
uint32_t ip;

void setup(void)
{
  Serial.begin(115200);
  Serial.println("If you start me up...");

  // Initialise the CC3000
  Serial.println(F("\nInitialising the CC3000..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while(1);
  }

  // Delete old connection data
  Serial.println(F("Deleting old connection profiles..."));
  if (!cc3000.deleteProfiles()) {
    Serial.println(F("Failed!"));
    while(1);
  }

  // Connect to Wifi
  Serial.print(F("Attempting to connect to ")); Serial.print(WIFI_SSID); Serial.println(F("..."));

  if (!cc3000.connectToAP(WIFI_SSID, WIFI_PASS, WIFI_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }

  Serial.print(F("Connected to ")); Serial.print(WIFI_SSID); Serial.println(F("..."));


  // Wait for DHCP to finish
  Serial.println(F("Request DHCP..."));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }


  // Show the connection details
  while (! displayConnectionDetails()) {
    delay(1000);
  }

 }



void loop(void)
{
  // create variables, get data from the sensor
  float t_f = sht10.readTemperatureF();
  float h = sht10.readHumidity();

  // transform data to a string
  String temperature = String((int) t_f);
  String humidity = String((int) h);

  // print data to serial port
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" F /");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.println("");

  // Create the request.
  String request = "GET /sensor?temp=" + temperature + "&hum=" + humidity + " HTTP/1.1\r\n";
  // Print and Send the request
  Serial.println("About to send: ");
  Serial.print(request);
  Serial.print(F("Host: "));
  Serial.print(HOST);
  Serial.print(F("\r\n"));
  Serial.print(F("User-Agent: Compost Monitor/1.0\r\n"));
  Serial.println();
  send_request(request);

  // include at least a 3.6 second delay between pairs of temperature & humidity measurements.
  delay(4000);

}


/* ########## Other Functions ########## */
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!"));
    return false;
  }
  else
  {
    Serial.println("Connection info...");
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println("\n");
    return true;
  }
}


// This is the function that the wifi weather station used in their example
void send_request (String request)
{

  ip = 0;
  // Try looking up the website's IP address
  Serial.print(HOST); Serial.print(F(" -> "));
  while (ip == 0) {
    if (! cc3000.getHostByName(HOST, &ip)) {
      Serial.println(F("Couldn't resolve!"));
    }
    delay(500);
  }

  cc3000.printIPdotsRev(ip);

  Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);
  if (www.connected()) {
    www.print(request);
    www.print(F("Host: "));
    www.print(HOST);
    www.print(F("\r\n"));
    www.print(F("User-Agent: Compost Monitor/1.0\r\n"));
    www.print(F("\r\n"));
    www.println();
  } else {
    Serial.println(F("Connection failed"));
    return;
  }

  Serial.println(F("-------------------------------------"));

  /* Read data until either the connection is closed, or the idle timeout is reached. */
  unsigned long lastRead = millis();
  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    while (www.available()) {
      char c = www.read();
      Serial.print(c);
      lastRead = millis();
    }
  }
  www.close();
  Serial.println(F("-------------------------------------"));


}
