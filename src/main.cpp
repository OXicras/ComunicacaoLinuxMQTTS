#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

const char* nomeRedeWiFi = "SENAI EDUCACIONAL";
const char* senhaRedeWiFi = "info@134";
const char* BROKER = "ec2-18-205-237-200.compute-1.amazonaws.com"
const int PORTA = 8883;
const char* TOPICO_SUB = "senai134/thiago/teste";
const char* TOPICO_PUB = "senai134/thiago/teste";

void aoReceber(char*, byte*, unsigned int);

WiFiClient clienteWifi;
PubSubClient mqtt(clienteWifi);

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  
}