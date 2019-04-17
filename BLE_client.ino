/*
 * A BLE client example to look for a particular BLE server
 */

#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define buzzer 12

int beaconInRange = -1;
int scanTime = 5;     // In seconds

BLEScan *pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
  void onResult(BLEAdvertisedDevice advertisedDevice)
  {
    if (advertisedDevice.getName() == "Robocraze - Easter Hunt")
    {
      int ble_rssi = advertisedDevice.getRSSI();
      Serial.println("RSSI: " + String(ble_rssi));

      if (ble_rssi > -85 && ble_rssi < -60)
      {
        beaconInRange = 0;
      }
      else if (ble_rssi > -60 && ble_rssi < -40)
      {
        beaconInRange = 1;
      }
      else if (ble_rssi > -40)
      {
        beaconInRange = 2;
      }
    }
  }
};

void setup()
{
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(10);
  pBLEScan->setWindow(9); // less or equal setInterval value

  pinMode(buzzer, OUTPUT); // set pin to output mode
}

void loop()
{
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  
  Serial.println("Flag: " + String(beaconInRange));
  
  switch (beaconInRange)
  {
  case 0:
    Serial.println("Beacon in Range");

    for (int i = 0; i < 5; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(400);
      digitalWrite(buzzer, LOW);
      delay(400);
    }
    break;
  case 1:
    Serial.println("Beacon is CLOSE!");

    for (int i = 0; i < 10; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
    }
    break;
  case 2:
    Serial.println("Beacon is VERY CLOSE!!!");

    for (int i = 0; i < 20; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
    }
    break;
  default:
    Serial.println("Beacon not in Range");
    break;
  }

  pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
  beaconInRange = -1;
}
