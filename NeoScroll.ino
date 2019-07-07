#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "ledBanner.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

String text = "HELLO WORLD!";
const char *ssid = "YourSSIDHere";
const char *password = "YourPSKHere";
WebServer server(80);

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void handleRoot()
{
  String message = "Root\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    if (server.argName(i) == "text")
      text = server.arg(i);
    if (server.argName(i) == "Bright")
      ledMatrix.setBrightness((server.arg(i)).toInt());
  }

  server.send(200, "text/plain", message);
}

void setup()
{
  Serial.begin(115200);
  ledInit();
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.print(".");
  // }

  // Serial.println("");
  // Serial.print("Connected to ");
  // Serial.println(ssid);
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());
  // if (MDNS.begin("esp32"))
  // {
  //   Serial.println("MDNS responder started");
  // }
  //Server routes
  server.onNotFound(handleNotFound);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  ledBanner(text);
  server.handleClient();
}
