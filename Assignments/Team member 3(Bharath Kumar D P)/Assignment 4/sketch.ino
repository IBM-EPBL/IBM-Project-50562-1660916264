#include <WiFi.h>
#include "PubSubClient.h"

#define ORG "1bfyv3"
#define DEVICE_TYPE "ESP32_Controller"
#define DEVICE_ID "Node29"

char deviceID[] = "d:"ORG":"DEVICE_TYPE":"DEVICE_ID;
char username[] = "use-token-auth";
char password[] = "XO_J!5Cx?@N0Bt1OkY";
char serverURL[] = ORG".messaging.internetofthings.ibmcloud.com";
int port = 1883;

char publishTopic[] = "iot-2/evt/event_1/fmt/json";
char subscribeTopic[] = "iot-2/cmd/Sub/fmt/String";

String lineBreak = "-----------";

WiFiClient wifiClient;
PubSubClient pubSubClient(serverURL, 
  port, 
  [](char* topic, byte* payload, unsigned int length) {
    Serial.println("Callback Invoked!");
    for (int i = 0; i < length; ++i)
      Serial.print((char)payload[i]);
  },
  wifiClient
);

int trigPin = 21;
int echoPin = 19;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  connectWiFi();
  connectMQTT();
}

void loop() {
  refreshMQTTConn();

  float distance = getUltraSonicDistance();
  if (distance < 100) {
    Serial.print("ALERT! Distance at: ");
    Serial.println(distance);
    publishData(distance);
  }
  
  delay(5000);
}

float getUltraSonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  return (float) pulseIn(echoPin, HIGH) / 58.0f; 
}

void publishData(float distance) {
  refreshMQTTConn();
  String payload = "{";
  payload += "\"Distance\": ";
  payload += distance;
  payload += "}";

  if (pubSubClient.publish(publishTopic, (char*)payload.c_str())) {
    Serial.println("Publish OK");
  }
  else Serial.println("Publish FAILED");
}

void connectWiFi() {
  WiFi.begin("Wokwi-GUEST", "", 6);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println(lineBreak);
}

void connectMQTT() {
  Serial.print("Connecting to IBM Watson @ ");
  Serial.print(serverURL);
  while (!pubSubClient.connect(deviceID, username, password)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to IBM Watson!");  

  if (pubSubClient.subscribe(subscribeTopic)) {
    Serial.println("Subscribed to CMD");
  }
  else {
    Serial.println("Subscribe FAILED");
  }
  Serial.println(lineBreak);
}

void refreshMQTTConn() {
  if (!pubSubClient.loop()) {
    connectMQTT();
  }
}
