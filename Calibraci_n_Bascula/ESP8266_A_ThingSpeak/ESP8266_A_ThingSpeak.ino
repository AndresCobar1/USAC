
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "CasaCS2g"    //access point wifi name (SSID)
#define STAPSK  "FamCobSand"  //access point wifi password
#endif

if(check == '1'){
const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "api.thingspeak.com";
const uint16_t port = 443;

// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "F9:C2:65:6C:F9:EF:7F:66:8B:F7:35:FE:15:EA:82:9F:5F:55:54:3E";
//WiFiClientSecure client;
int data1, data2;


void ESPSendData(int pes, int humid)
{
  char buf[100];
  sprintf(buf, "GET /update?api_key=MWHG1RDQ5IM520KH&field1=%lu&field2=%lu HTTP/1.1\r\nHost: api.thingspeak.com\r\n\r\n", pes, humid);
  //WiFiClient client;
  WiFiClientSecure client;
  //Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);
  if (!client.connect("api.thingspeak.com", 443)) {
    //Serial.println("Failed to connect with 'api.thingspeak.com' !");
  }
  else {
    int timeout = millis() + 5000;
    client.print(buf);
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        
        client.stop();
        return;
      }
    }
    int size;
    while ((size = client.available()) > 0) {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg, size);
      //Serial.write(msg, size);
      free(msg);
    }
  }
}
}

if(check == 2){

  const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "api.thingspeak.com";
const uint16_t port = 443;

// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "F9:C2:65:6C:F9:EF:7F:66:8B:F7:35:FE:15:EA:82:9F:5F:55:54:3E";
//WiFiClientSecure client;
int data1, data2;


void ESPSendData(int pes, int humid)
{
  char buf[100];
  sprintf(buf, "GET /update?api_key=F29XB272MJTPIMOA&field1=%lu&field2=%lu HTTP/1.1\r\nHost: api.thingspeak.com\r\n\r\n", pes, humid);

  WiFiClientSecure client;
 
  client.setFingerprint(fingerprint);
  if (!client.connect("api.thingspeak.com", 443)) {

  }
  else {
    int timeout = millis() + 5000;
    client.print(buf);
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        //Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    int size;
    while ((size = client.available()) > 0) {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg, size);
      //Serial.write(msg, size);
      free(msg);
    }
  }
}
}

void setup() {
  Serial.begin(9600);
  while (!Serial) continue;



  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
 
  }

 
}

void loop() {
  StaticJsonDocument<1000> doc;  
  DeserializationError error = deserializeJson(doc, Serial);
  if (error) return;
  
  data1=doc["peso"];
  data2=doc["hum"];

  if (data1>=0 && data2>=0) {
    ESPSendData(data1, data2);  
  }
  
  delay(30000); 
}
