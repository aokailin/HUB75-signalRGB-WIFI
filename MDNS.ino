#include <Arduino.h>
//#include <ArduinoJson.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
//#include <FastLED.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ESPmDNS.h>
#include <WebServer.h>
WebServer server(80);
#include "jsondata.h"
WiFiUDP udp;
MatrixPanel_I2S_DMA* dma_display = nullptr;

const char* SSID = "Xiaomi2.4G";
const char* password = "12345678..";
char RGBdata[24580], RGBtemp;
uint16_t x = 0, y = 0, inspects, k, f;
int R, d;

void Task2code(void* parameter) {
  while (1) {
    dma_display->drawPixelRGB888(x % 80, x / 80, RGBdata[(x * 3)], RGBdata[(x * 3) + 1], RGBdata[(x * 3) + 2]);
    x++;
    if (x == 3200) { x = 0; }
    //vTaskDelay(1);
  }
}


void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("AKL-Display", "12345678..");
  Serial.print("WiFi已连接");
  ESPMAC.replace(":", "");  // 去掉冒号
  ESPMAC.toLowerCase();     // 将字母转换成小写

  server.on("/json/info/", esp32message1);
  server.on("/json/", esp32message2);
  server.on("/json/state/", esp32message3);

  String Lastsixdigits = ESPMAC.substring(6);
  MDNS.begin("wled-" + Lastsixdigits);
  server.begin();
  udp.begin(UDPport);
  MDNS.addService("http", "tcp", 80);  // WLED服务
  MDNS.addService("wled", "tcp", 80);  // WLED服务
  MDNS.addServiceTxt("wled", "tcp", "mac", ESPMAC);
  HUB75_I2S_CFG::i2s_pins _pins = { 38, /*R1*/ 39, /*G1*/ 37, /*B1*/ 36, /*R2*/ 40, /*G2*/ 35, /*B2*/
                                    0, /*A*/ 14, /*B*/ 45, /*C*/ 13, /*D*/ 41, /*E*/ 21, /*LAT*/ 47, /*OE*/ 48,
                                    /*CLK*/ };
  HUB75_I2S_CFG mxconfig(80, 40, 1, _pins);
  mxconfig.driver = HUB75_I2S_CFG::FM6124;
  mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_20M;
  //mx_config.clkphase = true;
  //mxconfig.double_buff = true;
  mxconfig.clkphase = false;
  //dma_display->setLatBlanking(2);
  // Display Setup
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->clearScreen();
  dma_display->begin();
  dma_display->setBrightness(128);
  //dma_display->setLatBlanking(2);
  setCpuFrequencyMhz(240);
  //xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 2, NULL, 0);//TaskOne在 0核心
  xTaskCreatePinnedToCore(Task2code, "Task2", 80000, NULL, 1, NULL, 1);  //TaskOne在 1核心
}

void loop() {
  server.handleClient();
  if (udp.parsePacket()) {
    f = udp.read();
    f = udp.read();
    f = udp.read();
    f = udp.read();
    d = udp.read();
    d = udp.available();
    for (unsigned int a = 0, k = 0; a < d; a++) {
      RGBtemp = udp.read();
      RGBdata[(k + (f * 2908))] = ((RGBtemp >> 4) * 16);
      k++;
      RGBdata[(k + (f * 2908))] = ((RGBtemp & 0x0f) * 16);
      k++;
    }
  }
  //Serial.println(udp.parsePacket());
  vTaskDelay(1);
}