#include <Arduino.h>
#include <WebServer.h>
void WiFi_Connect()
{
  WiFi.begin("wifi", "12345678");
  Serial.print("Wifi connecting");
  while (WiFi.status() != WL_CONNECTED)
  { //这里是阻塞程序，直到连接成功
    delay(300);
    Serial.print(".");
  }
  Serial.println("Connected");
  // Serial.print("Mode:");
  // Serial.println(WiFi.getMode());
  Serial.print("IP LOCAL:");
  Serial.println(WiFi.localIP());
}
WebServer server(80);
void handle_root()
{
  server.send(200, "text/plain", "根页面");
}
void Server_creat()
{
  server.on("/", handle_root);
  server.begin();
  Serial.println("Web服务器已启动!");
}
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi_Connect();
  Server_creat();
}

void loop()
{
  server.handleClient();
  // put your main code here, to run repeatedly:
}