
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>


#define SEALEVELPRESSURE_HPA (1013.25)

//Declaration de nos constantes

const char* ssid = "M14"; // ssdi du reseau utilise
const char* password = "KUMDDFML"; // mot de passe du reseau utilise

AsyncWebServer server(80); // Declartion serveur web

Adafruit_BME280 bme; 

void setup() {

  // initialisation moniteur serie

  Serial.begin(115200);

 //initialisation WiFi

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

// initialisation System Fichier SPIFFS

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

//initialisation du bme280

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
// requete lecture de la page Web

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    File file = SPIFFS.open("/index2.html", "r");
    if (!file) {
      Serial.println("Failed to open file");
      request->send(404, "text/plain", "File not found");
      return;
    }
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index2.html", "text/html");
    request->send(response);
  });



// initialisation du serveur

  server.begin();

//affichage adresse du serveur

  Serial.print("Server started at http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
}
