#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "ledBanner.h"

String texto = "HELLO WORLD!";



void setup()
{
  Serial.begin(115200);
  ledInit();
}

void loop()
{
ledBanner(texto);
}
