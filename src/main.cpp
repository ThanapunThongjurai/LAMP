#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <AHT10.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "pCL5-F7t3yo3AlA64ojEBudjnGF0dLj8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SOMBAT1";
char pass[] = "0817084733";

AHT10 myAHT10(AHT10_ADDRESS_0X38);
float Temperature = 0;
float Humidity = 0;

void WorldRead()
{
  uint8_t readStatus = myAHT10.readRawData(); //read 6 bytes from AHT10 over I2C
  if (readStatus != AHT10_ERROR)
  {
    Temperature = (float)myAHT10.readTemperature(AHT10_USE_READ_DATA);
    Humidity = (float)myAHT10.readHumidity(AHT10_USE_READ_DATA);
  }
  else
  {
    myAHT10.softReset();
  }
}
void data2comport()
{
  Serial.print(F("Temperature\t: "));
  Serial.print(Temperature);
  Serial.println(F(" +-0.3C"));
  Serial.print(F("Humidity...\t: "));
  Serial.print(Humidity);
  Serial.println(F(" +-2%"));
}

void blynkRead()
{
  Blynk.virtualWrite(V0, Temperature);
  Blynk.virtualWrite(V1, Humidity);
}
void setup()
{
  pinMode(15, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(15, HIGH);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  
  Serial.begin(9600);
  Serial.println("START1");
  myAHT10.begin();
  Serial.println("START2");
  Blynk.begin(auth, ssid, pass);
  Serial.println("START3");
}
void loop()
{
  WorldRead();
  data2comport();
  blynkRead();
  Blynk.run(); 
}