#ifndef ledBanner_H
#define ledBanner_H

//Led backend

//Were are we going to send the data to the led matrix
#define ledPin 18
#define matrixLength 32
#define matrixHeight 8

Adafruit_NeoMatrix ledMatrix = Adafruit_NeoMatrix(matrixLength, matrixHeight, ledPin, NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
    ledMatrix.Color(255, 0, 0),
    ledMatrix.Color(0, 255, 0),
    ledMatrix.Color(255, 255, 0),
    ledMatrix.Color(0, 0, 255),
    ledMatrix.Color(255, 0, 255),
    ledMatrix.Color(0, 255, 255),
    ledMatrix.Color(255, 255, 255)};

void ledInit()
{
    ledMatrix.begin();
    ledMatrix.setTextWrap(false);
    ledMatrix.setBrightness(5);
    ledMatrix.setTextColor(colors[0]);
}

int ledPxLength(int strLength)
{
    /*"HELLO WORLD!" Contains 12 caracters and each caracter has a lenght of 5px with 7px of height
   *Each caracter has 1px of padding to separate it from the other.
   *https://cdn-learn.adafruit.com/downloads/pdf/adafruit-gfx-graphics-library.pdf
   *
   *In order to display "Hello world!" we need 60px + 12px of padding on the X axis of the screen.
   */
    int lengthBuffer = strLength;
    strLength = (((-1 * strLength) * 5) + (-1 * lengthBuffer));
    return strLength;
}

int xAxis = ledMatrix.width();
int pass = 0;
long previousTime = 0;
long interval = 35;

void ledBanner(String txtToShow, String brightnss)
{
    ledMatrix.fillScreen(0);
    ledMatrix.setCursor(xAxis, 0);
    ledMatrix.print(txtToShow);
    ledMatrix.setBrightness(brightnss.toInt());

    //Serial.printf("FreeMem:%d %d \n", ESP.getFreeHeap(), xAxis);

    unsigned long currentTime = millis();
    if (currentTime - previousTime > interval)
    {
        previousTime = currentTime;
        if (--xAxis < ledPxLength(txtToShow.length()))
        {
            xAxis = ledMatrix.width();

            if (++pass >= 8)
                pass = 0;
            ledMatrix.setTextColor(colors[pass]);
        }
        ledMatrix.show();
    }
}
#endif