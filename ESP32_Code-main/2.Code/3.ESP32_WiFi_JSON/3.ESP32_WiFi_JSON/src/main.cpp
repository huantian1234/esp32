#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "../lib/ArduinoJson/ArduinoJson.h"
void getBiliBiliFollower();
void getweather();
// 记得解压ArduinoJson文件夹

// JOSN是一种轻量级的数据交换格式，遵循一下规则：
// 1.并列的数据之间用逗号(,)分隔
// 2.映射用冒号(:)表示
// 3.并列数据的集合(数组)用方括号([])表示
// 4.映射的集合(对象)用大括号({})表示
const int LEDA = 2;
const int Button = 15;
bool state = false;
void IRAM_ATTR isr()
{
	state = !state;
	digitalWrite(LEDA, state);
}
//	WiFi的初始化和连接
void WiFi_Connect()
{
	WiFi.begin("wifi", "12345678");
	while (WiFi.status() != WL_CONNECTED)
	{ //这里是阻塞程序，直到连接成功
		delay(300);
		Serial.print(".");
	}
}

void setup()
{

	Serial.begin(115200); // open the serial port at 115200 bps;
	// delay(100);

	// Serial.print("Connecting.. ");

	// WiFi_Connect();

	// Serial.println("WiFi connected");

	// Serial.println("IP address: ");
	// Serial.println(WiFi.localIP());

	pinMode(LEDA, OUTPUT);
	digitalWrite(LEDA, HIGH);
	pinMode(Button, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(Button), isr, FALLING);
}

//	获取粉丝数
void getBiliBiliFollower()
{
	// bilibili api: follower
	String UID = "512670420";
	// String followerUrl = "https://devapi.qweather.com/v7/weather/now?location=101280101&key=41f7d94b8af644999b2b9e8de62bbef7"; // 粉丝数
	String followerUrl = "https://api.seniverse.com/v3/weather/now.json?key=SVHkfwUeMr-YLeiao&location=guangzhou&language=zh-Hans&unit=c";
	String temp = "24"; // 粉丝数

	DynamicJsonDocument doc(1024);
	HTTPClient http;
	http.begin(followerUrl); // HTTP begin
	int httpCode = http.GET();

	if (httpCode > 0)
	{
		// httpCode will be negative on error
		Serial.printf("HTTP Get Code: %d\r\n", httpCode);

		if (httpCode == HTTP_CODE_OK) // 收到正确的内容
		{
			String resBuff = http.getString();
			//	输出示例：{ "mid":123456789,"following":226,"whisper":0,"black":0,"follower":867}}
			//输出示例:
			Serial.println(resBuff);
			Serial.println("广州");
			//	使用ArduinoJson_6.x版本，具体请移步：https://github.com/bblanchon/ArduinoJson
			// deserializeJson(doc, resBuff); //开始使用Json解析
			// Serial.printf("温度: %s \r\n", doc["now"]["temp"]);
		}
	}
	else
	{
		Serial.printf("HTTP Get Error: %s\n", http.errorToString(httpCode).c_str());
	}

	http.end();
}
void getweather()
{
	String weatherUrl = "https://api.seniverse.com/v3/weather/now.json?key=SVHkfwUeMr-YLeiao&location=guangzhou&language=zh-Hans&unit=c";
	DynamicJsonDocument weather(1024);
	HTTPClient weatherHttp;
	weatherHttp.begin(weatherUrl);
	int httpCode = weatherHttp.GET();
	Serial.printf("HTTP Code:%d\r\n", httpCode);
	if (httpCode = HTTP_CODE_OK)
	{
		String res = weatherHttp.getString();
		deserializeJson(weather, res);
		Serial.println(weather["results"][0]["location"]["name"].as<const char *>());
		Serial.print("气温:");
		Serial.println(weather["results"][0]["now"]["temperature"].as<const char *>());
		Serial.print("天气情况:");
		Serial.println(weather["results"][0]["now"]["text"].as<const char *>());
	}
}
void loop()
{

	// getweather();
	// delay(30000);

	// digitalWrite(LEDA, HIGH);
	// delay(500);
	// digitalWrite(LEDA, LOW);
	// delay(500);

	Serial.println(digitalRead(Button));
}
