/******************************************************************************


IoT laitteiston ohjelma Timo Karppanen & Isto Kinnunen

*******************************************************************************
*/

#include <SPI.h>
#include <BLEPeripheral.h>
#include <dht11.h>

#define BLE_REQ 10
#define BLE_RDY 2
#define BLE_RST 9

#define DHT11PIN 4

dht11 DHT11;

BLEPeripheral blePeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);

/* Luodaan bluetooth palvelut, merkinnät, sekä muut tiedot sää-asemalle */

BLEService weatherService = BLEService("BBB0");

BLEFloatCharacteristic temperatureCharacteristic = BLEFloatCharacteristic("BBB1", BLERead | BLENotify);
BLEDescriptor          temperatureDescriptor = BLEDescriptor("2901", "Temperature");

BLEFloatCharacteristic humidityCharacteristic = BLEFloatCharacteristic("BBB2", BLERead | BLENotify);
BLEDescriptor          humidityDescriptor = BLEDescriptor("2901", "Humidity");

void setup()
 {

  Serial.begin(9600);
  Serial.println(F("Bluetooth Low Energy Sääasema"));

  /* Asetetaan Bluetooth laitteistolle nimet */

  blePeripheral.setLocalName("hassu-saaasema");
  blePeripheral.setDeviceName("hassu-laitteisto");

  /* Asetetaan palvelut sekä atribuutit  */

  blePeripheral.setAdvertisedServiceUuid(weatherService.uuid());
  blePeripheral.addAttribute(weatherService);
 
  blePeripheral.addAttribute(temperatureCharacteristic);
  blePeripheral.addAttribute(temperatureDescriptor);
  
  blePeripheral.addAttribute(humidityCharacteristic);
  blePeripheral.addAttribute(humidityDescriptor);

  /* Käynnistetään bluetooth */

  blePeripheral.begin();
  Serial.println("Bluetooth on saatu toimimaan.");
  
 }
 
void loop()
{


  
 blePeripheral.poll();

 int chk = DHT11.read(DHT11PIN);

 Serial.print("Humidity (%): ");
 Serial.println((float)DHT11.humidity, 2);

 Serial.print("Temperature (C): ");
 Serial.println((float)DHT11.temperature, 2);




 if (DHT11.temperature > 20)   // Set temperature limit
    {

      delay(2000);

      Serial.println("Hello World");

      delay(500);
    }

   else if (DHT11.humidity > 20) // Set humidity limit
   {
       delay(2000);

      Serial.println("Hello World");

      delay(500);
   }
 
}

  




  
