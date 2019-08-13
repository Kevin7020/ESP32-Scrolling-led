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
#define mode_UUID "2393f141-9a8d-4632-9369-a63c4eab29fa"

#define red_UUID "7f4ddf78-0edd-459a-9764-1adc5e10dd1e"
#define green_UUID "3af7e4d0-e842-45ce-bf9d-83eb904495cc"
#define blue_UUID "1b53ff17-2eae-408b-bfe8-6a7eb951d34f"

BLEServer *pServer = NULL;
BLEService *pService = NULL;
BLECharacteristic *textCaracteristic = NULL;
BLECharacteristic *brightnssCaracteristic = NULL;
BLECharacteristic *modeCaracteristic = NULL;

BLECharacteristic *redCaracteristic = NULL;
BLECharacteristic *greenCaracteristic = NULL;
BLECharacteristic *blueCaracteristic = NULL;

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

  modeCaracteristic = pService->createCharacteristic( 
    mode_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE);

  redCaracteristic = pService->createCharacteristic( 
    red_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE);
  greenCaracteristic = pService->createCharacteristic( 
    green_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE);
  blueCaracteristic = pService->createCharacteristic( 
    blue_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE);

  textCaracteristic->setValue("HELLO WORLD!");
  brightnssCaracteristic->setValue("5");
  modeCaracteristic->setValue("1");

  redCaracteristic->setValue("255");
  greenCaracteristic->setValue("0");
  blueCaracteristic->setValue("0");

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
String mode = modeCaracteristic->getValue().c_str();

  if (mode.toInt() == 1)
  {
    ledBanner(
      textCaracteristic->getValue().c_str(), 
      brightnssCaracteristic->getValue().c_str());
  }
  else if (mode.toInt() == 2)
  {
    ledSolidBanner(
        textCaracteristic->getValue().c_str(),
        brightnssCaracteristic->getValue().c_str(),
        redCaracteristic->getValue().c_str(),
        greenCaracteristic->getValue().c_str(),
        blueCaracteristic->getValue().c_str());
  }
}
