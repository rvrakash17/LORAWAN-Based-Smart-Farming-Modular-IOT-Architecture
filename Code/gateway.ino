#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h> //WiFi Library for esp32
#include <LoRa.h> //LoRa Library
#include <HTTPClient.h>
#include<LiquidCrystal_I2C.h>
WiFiClient client;
HTTPClient http;
char ssid[] = "Ash";
char pass[] = "12345678";
const char* SERVER_NAME = "http://192.168.20.132/Agri/sensordata.php";
const char* HOST_NAME = "http://192.168.20.132/Agri/getdatas.php";
StaticJsonDocument<200> jsonBuffer;
unsigned long lastMillis = 0;
long interval = 5000;
LiquidCrystal_I2C lcd(0x27,16,2);
#define ss 4
#define rst 5
#define dio0 2
#define buzzer 32
String outgoing;
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval1 = 50;          // interval between sends
String temprature; // This string hold the temperature data
String humidity; // This string hold the humidity data
String soil;
String light;
String rain;
int pos_1, pos_2,pos_3,pos_4,pos_5,pos_6;
int lightget;
int pumpget;
void setup(){
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(buzzer,OUTPUT);
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(500);}
    Serial.println("LoRa init succeeded.");
     Serial.print("Connecting to WiFi ");
     Serial.println(ssid);
     WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");}}
void loop(){
  if (lightget == 1) {
    digitalWrite(buzzer, HIGH); //--> Turn off Led}
  if (lightget == 0) {
    digitalWrite(buzzer, LOW); //--> Turn off Led}
  if (millis() - lastSendTime > interval1) {
  String message = String(lightget) + "a" + String(pumpget);
  sendMessage(message);
  Serial.println("Sending Data To End Device : " + message);
  lastSendTime = millis();            // timestamp the message
  interval1 = random(50) + 100;    // 2-3 seconds}
  onReceive(LoRa.parsePacket());}
void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;}
void onReceive(int packetSize) {
  if (packetSize == 0) return;
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  Serial.print("Received packet:  ");
  String LoRaData = LoRa.readString();
  Serial.print(LoRaData);
  while (LoRa.available()) {
    Serial.print((char)LoRa.read());}
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
  pos_1 = LoRaData.indexOf('a');
  pos_2 = LoRaData.indexOf('b');
  pos_3 = LoRaData.indexOf('c');
  pos_4 = LoRaData.indexOf('d');
  temprature = LoRaData.substring(0, pos_1);
  humidity = LoRaData.substring(pos_1 + 1, pos_2);
  soil = LoRaData.substring(pos_2 + 1, pos_3);
  light = LoRaData.substring(pos_3 + 1, pos_4);
  rain = LoRaData.substring(pos_4 + 1,LoRaData.length());
  Serial.print("Temperature: ");
  Serial.println(temprature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Soil: ");
  Serial.println(soil);
  Serial.print("Light: ");
  Serial.println(light);
  Serial.print("Rain: ");
  Serial.println(rain);
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temprature);
  lcd.setCursor(8,0);
  lcd.print("H:");
  lcd.print(humidity);
  lcd.setCursor(0,1);
  lcd.print("S:");
  lcd.print(soil);
  lcd.setCursor(8,1);
  lcd.print("R:");
  lcd.print(rain);
  upload_data();
  download_data();}
  void download_data(){
  http.begin(HOST_NAME); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");   
  String getData = "lightstate";
  int httpCodeGet = http.POST(getData); //--> Send the request
  String payloadGet = http.getString(); //--> Get the response payload from server
  deserializeJson(jsonBuffer, payloadGet);
  lightget = jsonBuffer["lightstate"];
  pumpget = jsonBuffer["pumpstate"];
  Serial.print("Receive Data From Cloud: ");
  Serial.print("  Light Status: ");
  Serial.print(lightget);
  Serial.print("  Pump Status: ");
  Serial.println(pumpget);
  http.end();}
void upload_data(){
  String sensor_data;
  sensor_data += "temprature="+temprature;
  sensor_data += "&humidity="+humidity;
  sensor_data += "&rain="+rain;
  sensor_data += "&soil="+soil;
  sensor_data += "&light="+light;
  Serial.print("Send Data To Cloud: ");
  Serial.println(sensor_data);
  http.begin(client, SERVER_NAME);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(sensor_data);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();
}
