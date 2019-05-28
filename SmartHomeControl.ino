#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOU";
const char* password = "sbvizag2019";

#define ORG "1uwrf4"
#define DEVICE_TYPE "Charan_IoT"
#define DEVICE_ID "iam_charan"
#define TOKEN "IBMCloud123"
String command;
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/cmd/home/fmt/String";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
//Serial.println(clientID);

WiFiClient wifiClient;
void callback(char* topic, byte* payload, unsigned int payloadLength);
PubSubClient client(server, 1883, callback, wifiClient);

void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  wifiConnect();
  mqttConnect();
}

void loop() {
  if (!client.loop()) {
    mqttConnect();
  }
delay(100);
}

void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("nWiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

void mqttConnect() {
  if (!client.connected()) {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}
void initManagedDevice() {
  if (client.subscribe(topic)) {
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  Serial.print("callback invoked for topic: "); Serial.println(topic);

  for (int i = 0; i < payloadLength; i++) {
    //Serial.println((char)payload[i]);
    command += (char)payload[i];
  }
  Serial.println(command);
  if(command == "LED 1 ON"){
    digitalWrite(D1,HIGH);
    Serial.println("Light 1 is Switched ON");
  }
  else if(command == "LED 1 OFF"){
    digitalWrite(D1,LOW);
    Serial.println("Light 1 is Switched OFF");
  }
  Serial.println(command);
  if(command == "LED 2 ON"){
    digitalWrite(D2,HIGH);
    Serial.println("Light 2 is Switched ON");
  }
  else if(command == "LED 2 OFF"){
    digitalWrite(D2,LOW);
    Serial.println("Light 2 is Switched OFF");
  }
  command ="";
}
