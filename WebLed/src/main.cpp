#include <Arduino.h>
#include <WebServer.h>

const char *ssid = "Ron";
const char *password = "0963083131";

WebServer server(80);
const byte LED = 2;

void handleRoot() 
{
  String HTML = "<a href=\"/on\">開啟LED</a> <br>";
  HTML += "<a href=\"/off\">關閉LED</a>";
  server.send(200, "text/html; charset=UTF-8", HTML);
}

void handleNotFound() 
{
  server.send(404, "text/plain; charset=UTF-8", "找不到檔案");
}

void handleLedOn() 
{
  digitalWrite(LED, HIGH);
  server.send(200, "text/html; charset=UTF-8", "已開啟LED<br><a href=\"/off\">關閉LED</a>");
}

void handleLedOff() 
{
  digitalWrite(LED, LOW);
  server.send(200, "text/html; charset=UTF-8", "<a href=\"/on\">開啟LED</a><br>已關閉LED");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(LED, OUTPUT);

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected!!");
  Serial.print("My IP = ");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);
  server.on("/on",handleLedOn);
  server.on("/off", handleLedOff);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server is running...");
}

void loop() {
  server.handleClient();
}
