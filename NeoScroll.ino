#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "ledBanner.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "659afb41-9a5b-468b-8b83-8956358ff09a"
#define text_UUID "f55d3b17-9dc1-4712-b301-e8d8bf50f28d"
#define brightnss_UUID "981422d7-ae37-4109-b370-a56600f89c92"

BLEServer *pServer = NULL;
BLEService *pService = NULL;
BLECharacteristic *textCaracteristic = NULL;
BLECharacteristic *brightnssCaracteristic = NULL;

void setup()
{
  Serial.begin(115200);
  ledInit();

  Serial.println("Starting BLE Service!");
  BLEDevice::init("Led Matrix");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  textCaracteristic = pService->createCharacteristic( 
    text_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE);

  brightnssCaracteristic = pService->createCharacteristic( 
    brightnss_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE);

  textCaracteristic->setValue("HELLO WORLD!");
  brightnssCaracteristic->setValue("5");

  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristics defined!!");
}

void loop()
{
  ledBanner(textCaracteristic->getValue().c_str(), brightnssCaracteristic->getValue().c_str());
}
