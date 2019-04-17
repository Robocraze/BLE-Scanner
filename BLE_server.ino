/*  
 * A BLE Server example 
 *   
 */

#include <BLEDevice.h>
#include <BLEServer.h>
#include <Wire.h>
#include <SH1106Wire.h>

/* Use the following link to install OLED library: 
  https://github.com/vlast3k/Arduino-libraries/tree/master/SSD1306 */

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

SH1106Wire oled(0x3c, 21, 22);

void setup()
{
  Serial.begin(115200);

  Wire.begin(21, 22);

  Serial.println("Starting BLE work!");

  BLEDevice::init("Robocraze - Easter Hunt");

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic->setValue("Easter Hunt");
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);

  BLEDevice::startAdvertising();

  Serial.println("Characteristic defined!");

  // OLED Display Initialization
  oled.init();
  delay(2);
  oled.flipScreenVertically();
  oled.setFont(ArialMT_Plain_16);
  oled.drawString(5, 25, "The CraZy Ones");
  oled.display();
}

void loop()
{
  // Nothing to add here. We only need the ESP to advertise BLE.
}
