#ifndef JSONDATA_H
#define JSONDATA_H
#include <ArduinoJson.h>
 extern String ESPMAC = WiFi.macAddress();
 extern IPAddress ESPIP = WiFi.localIP();
 extern int ESPRSSI = WiFi.RSSI();
 extern int LEDNumber = 6400;
 extern int UDPport = 33333;



void esp32message1(){

  ESPIP = WiFi.localIP();
  ESPRSSI = WiFi.RSSI();
StaticJsonDocument<1024> doc;
// 添加各个字段
doc["ver"] = "0.14.0";
doc["vid"] = 2310130;
JsonObject leds = doc.createNestedObject("leds");
leds["count"] = LEDNumber;
leds["pwr"] = 0;
leds["fps"] = 5;
leds["maxpwr"] = 0;
leds["maxseg"] = 32;
leds["seglc"].add(1);
leds["lc"] = 1;
leds["rgbw"] = false;
leds["wv"] = 0;
leds["cct"] = 0;
doc["str"] = false;
doc["name"] = "WLED";
doc["udpport"] = UDPport;
doc["live"] = false;
doc["liveseg"] = -1;
doc["lm"] = "";
doc["lip"] = "";
doc["ws"] = 0;
doc["fxcount"] = 187;
doc["palcount"] = 71;
doc["cpalcount"] = 0;
JsonArray maps = doc.createNestedArray("maps");
JsonObject mapObj = maps.createNestedObject();
mapObj["id"] = 0;
JsonObject wifi = doc.createNestedObject("wifi");
wifi["bssid"] = "EC:6C:9F:C1:B3:46";
wifi["rssi"] = ESPRSSI;
wifi["signal"] = 100;
wifi["channel"] = 5;
JsonObject fs = doc.createNestedObject("fs");
fs["u"] = 12;
fs["t"] = 4063;
fs["pmt"] = 0;
doc["ndc"] = 0;
doc["arch"] = "AKL-ESP";
doc["core"] = "v4.4.3";
doc["lwip"] = 0;
doc["freeheap"] = 138660;
doc["uptime"] = 20;
doc["time"] = "2023-12-12, 00:00:00";
doc["opt"] = 79;
doc["brand"] = "WLED";
doc["product"] = "FOSS";
doc["mac"] = ESPMAC;
doc["ip"] = ESPIP;
String jsonset;
serializeJson(doc, jsonset);
server.send(200,"application/json",jsonset);
}

void esp32message2(){
  ESPIP = WiFi.localIP();
  ESPRSSI = WiFi.RSSI();

  DynamicJsonDocument json(4069);

  JsonObject state = json.createNestedObject("state");
  state["on"] = true;
  state["bri"] = 128;
  state["transition"] = 7;
  state["ps"] = -1;
  state["pl"] = -1;

  JsonObject nl = state.createNestedObject("nl");
  nl["on"] = false;
  nl["dur"] = 60;
  nl["mode"] = 1;
  nl["tbri"] = 0;
  nl["rem"] = -1;

  JsonObject udpn = state.createNestedObject("udpn");
  udpn["send"] = false;
  udpn["recv"] = true;
  udpn["sgrp"] = 1;
  udpn["rgrp"] = 1;

  state["lor"] = 0;
  state["mainseg"] = 0;

  JsonArray seg = state.createNestedArray("seg");
  JsonObject seg_0 = seg.createNestedObject();
  seg_0["id"] = 0;
  seg_0["start"] = 0;
  seg_0["stop"] = LEDNumber;
  seg_0["len"] = LEDNumber;
  seg_0["grp"] = 1;
  seg_0["spc"] = 0;
  seg_0["of"] = 0;
  seg_0["on"] = true;
  seg_0["frz"] = false;
  seg_0["bri"] = 255;
  seg_0["cct"] = 127;
  seg_0["set"] = 0;

  JsonArray col = seg_0.createNestedArray("col");
  JsonArray col_0 = col.createNestedArray();
  col_0.add(255);
  col_0.add(160);
  col_0.add(0);
  JsonArray col_1 = col.createNestedArray();
  col_1.add(0);
  col_1.add(0);
  col_1.add(0);
  JsonArray col_2 = col.createNestedArray();
  col_2.add(0);
  col_2.add(0);
  col_2.add(0);

  seg_0["fx"] = 0;
  seg_0["sx"] = 128;
  seg_0["ix"] = 128;
  seg_0["pal"] = 0;
  seg_0["c1"] = 128;
  seg_0["c2"] = 128;
  seg_0["c3"] = 16;
  seg_0["sel"] = true;
  seg_0["rev"] = false;
  seg_0["mi"] = false;
  seg_0["o1"] = false;
  seg_0["o2"] = false;
  seg_0["o3"] = false;
  seg_0["si"] = 0;
  seg_0["m12"] = 0;

  JsonObject info = json.createNestedObject("info");
  info["ver"] = "0.14.0";
  info["vid"] = 2310130;

  JsonObject leds = info.createNestedObject("leds");
  leds["count"] = LEDNumber;
  leds["pwr"] = 0;
  leds["fps"] = 5;
  leds["maxpwr"] = 0;
  leds["maxseg"] = 32;

  JsonArray seglc = leds.createNestedArray("seglc");
  seglc.add(1);

  leds["lc"] = 1;
  leds["rgbw"] = false;
  leds["wv"] = 0;
  leds["cct"] = 0;

  info["str"] = false;
  info["name"] = "WLED";
  info["udpport"] = UDPport;
  info["live"] = false;
  info["liveseg"] = -1;
  info["lm"] = "";
  info["lip"] = "";
info["lip"] = "";
info["ws"] = 0;
info["fxcount"] = 187;
info["palcount"] = 71;
info["cpalcount"] = 0;
info["fxcount"] = 187;
  JsonArray maps = info.createNestedArray("maps");
  JsonObject maps_0 = maps.createNestedObject();
  maps_0["id"] = 0;

  JsonObject wifi = info.createNestedObject("wifi");
  wifi["bssid"] = "EC:6C:9F:C1:B3:46";
  wifi["rssi"] = ESPRSSI;
  wifi["signal"] = 100;
  wifi["channel"] = 5;
 JsonObject fs = info.createNestedObject("fs");
fs["u"] = 12;
fs["t"] = 4063;
fs["pmt"] = 0;

info["ndc"] = 0;
info["arch"] = "KAL-ESP";
info["core"] = "v4.4.3";
info["lwip"] = 0;
info["freeheap"] = 137012;
info["uptime"] = 20;
info["time"] = "1970-1-1, 00:00:20";
info["brand"] = 20;
info["uptime"] = 20;
info["uptime"] = 20;
info["opt"] = 79;
info["brand"] = "WLED";
info["product"] = "FOSS";
info["mac"] = ESPMAC;
info["ip"] = ESPIP;


  JsonArray effects = json.createNestedArray("effects");
  effects.add("Solid");
  effects.add("Blink");

  JsonArray palettes = json.createNestedArray("palettes");
  palettes.add("Default");
  palettes.add("* Random Cycle");


    String jsonset;
  serializeJson(json, jsonset);


server.send(200,"application/json",jsonset);
}
void esp32message3(){
String jsonset = "{\"success\":true}";
server.send(200,"application/json",jsonset);
}
#endif