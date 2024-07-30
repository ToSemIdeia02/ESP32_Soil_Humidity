/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-plot-chart-web-server/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <LittleFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <LittleFS.h>
  #include <FS.h>
#endif
#include <Wire.h>

// Replace with your network credentials
const char* ssid = "umidade";
const char* password = "umidade";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


String readBME280Humidity() {

  sensor_analog_moisture = analogRead(sensor_pin_moisture);
  moisture = ( 100 - ( (sensor_analog_moisture/4095.00) * 100 ) );
  
  if (isnan(h)) {
    Serial.println("Failed to read from sensor!");
    return "";
  }
  else {
    Serial.println(moisture);
    return String(moisture);
  }
}



void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  bool status; 
  // default settings
  // (you can also pass in a Wire library object like &Wire2) 
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // Initialize LittleFS
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
        return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html");
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Humidity().c_str());
  });


  // Start server
  server.begin();
}
 
void loop(){
  
}
