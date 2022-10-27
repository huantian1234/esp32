#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#define ENABLE_GxEPD2_GFX 0
#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
#define GxEPD2_DRIVER_CLASS GxEPD2_290 //编号：GDEH029A1 128x296
#define GxEPD2_BW_IS_GxEPD2_BW true
#define IS_GxEPD(c, x) (c##x)
#define IS_GxEPD2_BW(x) IS_GxEPD(GxEPD2_BW_IS_, x)
#define IS_GxEPD2_1248(x) IS_GxEPD(GxEPD2_1248_IS_, x)
#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=*/15, /*DC=*/27, /*RST=*/26, /*BUSY=*/25));
#include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
const char HelloWorld[] = "Hello World! ESP32!!NB666!!";
void helloworld()
{
  display.setRotation(-1); // 1和-1为反方向 0为竖直方向
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  Serial.print("X:");
  Serial.println(x);
  Serial.print("Y:");
  Serial.println(y);
  Serial.printf("tbx:%d,tby:%d,tbw:%d,tbh:%d", tbx, tby, tbw, tbh);
  display.setFullWindow();
  Serial.println("1");
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    Serial.println("2");
    display.setCursor(x, y);
    display.print(HelloWorld);
    Serial.println("3");
  } while (display.nextPage());
}
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  display.init(115200);
  SPI.end();
  SPI.begin(14, 12, 13, 15); // map and init SPI pins SCK(14), MISO(12), MOSI(13), SS(15)
  helloworld();
  display.powerOff();
  Serial.println("setup done");
}
void loop()
{
}