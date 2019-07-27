#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "ledBanner.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "659afb41-9a5b-468b-8b83-8956358ff09a"
#define CHARACTERISTIC_UUID "f55d3b17-9dc1-4712-b301-e8d8bf50f28d"

BLEServer *pServer = NULL;
BLEService *pService = NULL;
BLECharacteristic *pCharacteristic = NULL;

//String text = "HELLO WORLD!";

void setup()
{
  Serial.begin(115200);
  ledInit();

  Serial.println("Starting BLE Service!");
  BLEDevice::init("Led Matrix");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic( 
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic->setValue("HELLO WORLD!");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined!!");
}

void loop()
{
  ledBanner(pCharacteristic->getValue().c_str());
}
