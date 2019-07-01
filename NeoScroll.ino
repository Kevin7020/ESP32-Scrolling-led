#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 18

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
    matrix.Color(255, 0, 0),
    matrix.Color(0, 255, 0),
    matrix.Color(255, 255, 0),
    matrix.Color(0, 0, 255),
    matrix.Color(255, 0, 255),
    matrix.Color(0, 255, 255),
    matrix.Color(255, 255, 255)};

String texto = "HELLO WORLD!";

int ledPxLength(int strLength)
{
  /*"HELLO WORLD!" Contains 12 caracters and each caracter has a lenght of 5px with 7px of height
   *Each caracter has 1px of padding to separate it from the other.
   *https://cdn-learn.adafruit.com/downloads/pdf/adafruit-gfx-graphics-library.pdf
   *
   *In order to display "Hello world!" we need 60px + 12px of padding on the X axis of the screen.
   */
  //Serial.println(strLength);
  int lengthBuffer = strLength;
  strLength = (((-1 * strLength)*5)+(-1 * lengthBuffer));
  //Serial.println(strLength);
  return strLength;
}

void setup()
{
  Serial.begin(115200);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[0]);
}

int x = matrix.width();
int pass = 0;

void loop()
{
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(texto);

  Serial.printf("FreeMem:%d %d \n", ESP.getFreeHeap(), x);
  if ( --x < ledPxLength(texto.length()) )
  {
    x = matrix.width();

    if (++pass >= 8)
      pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(35);
}