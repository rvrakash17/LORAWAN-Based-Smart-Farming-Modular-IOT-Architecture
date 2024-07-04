#include <LoRa.h>
#include <DHT.h>
#define ss 4  
#define rst 5  
#define dio0 2  
#define DO_PIN 15  // ESP32's pin GPIO13 connected to DO pin of the ldr module
#define LED 32
#define DHT_SENSOR_PIN  21 // ESP32 pin GPIO21 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11
#define MOISTURE_PIN 36
#define rainAnalog 35
#define relay 22
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
String outgoing;
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 50;          // interval between sends
int pos1;
int s, li, l;
String lightstate;
String pumpstate;
  void setup() {
  Serial.begin(115200);
  dht_sensor.begin(); 
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6)){
  Serial.println("Starting LoRa failed!");
  delay(500);}
  Serial.println("LoRa init succeeded.");
  pinMode(LED,OUTPUT);
  pinMode(relay,OUTPUT);}
  void loop() {
  if(pumpstate=="0" && s>=90){
  digitalWrite(relay,LOW);  }
  else if(pumpstate=="1" || s<=90){
  digitalWrite(relay,HIGH);  }
  if (millis() - lastSendTime > interval) {
  float h = dht_sensor.readHumidity();
  float t = dht_sensor.readTemperature();
  s = analogRead(MOISTURE_PIN);
  s = map(s,0,4095,0,100);
  s = (s-100)*-1;
  l = digitalRead(DO_PIN);
  if(l==1){
  digitalWrite(LED, HIGH);
  li = 0;}
  if(l==0){
  digitalWrite(LED,LOW);
  li = 1;}
  int r = analogRead(rainAnalog);
  r = map(r,0,4095,0,100);
  r = (r-100)*-1;
  Serial.print("Temperature = ");
  Serial.println(t);
  Serial.print("Humidity = ");
  Serial.println(h);
  Serial.print("Soil = ");
  Serial.println(s);
  Serial.print("Light = ");
  Serial.println(li);
  Serial.print("Rain = ");
  Serial.println(r);
  String message;  
  message = String(t) + "a" + String(h) + "b" + String(s)+ "c" + String(li)+ "d" + String(r);
  sendMessage(message);
  Serial.println("Sending " + message);
  lastSendTime = millis();                 // timestamp the message
  interval = random(50) + 100;    // 2-3 seconds  }
  onReceive(LoRa.parsePacket());}
  void sendMessage(String outgoing) {
  LoRa.beginPacket();                            // start packet
  LoRa.write(destination);                      // add destination address
  LoRa.write(localAddress);                   // add sender address
  LoRa.write(msgCount);                        // add message ID
  LoRa.write(outgoing.length());             // add payload length
  LoRa.print(outgoing);                           // add payload
  LoRa.endPacket();                                // finish packet and send it
  msgCount++; }
  void onReceive(int packetSize) {
  if (packetSize == 0) return;                    // if there's no packet, return
  int recipient = LoRa.read();                    // recipient address
  byte sender = LoRa.read();                     // sender address
  byte incomingMsgId = LoRa.read();      // incoming msg ID
  byte incomingLength = LoRa.read();     // incoming msg length
  Serial.print("Received packet:  ");
  String LoRaData = LoRa.readString();
  Serial.print(LoRaData);
  while (LoRa.available()) {
  Serial.print((char)LoRa.read());}
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
  pos1 = LoRaData.indexOf('a');
  lightstate = LoRaData.substring(0, pos1);
  pumpstate = LoRaData.substring(pos1 + 1, LoRaData.length());
  }