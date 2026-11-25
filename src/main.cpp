#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* nomeRedeWiFi = "SENAI EDUCACIONAL";
const char* senhaRedeWiFi = "info@134";
const char* BROKER = "ec2-18-205-237-200.compute-1.amazonaws.com";
const int PORTA = 8883;
const char* TOPICO_SUB = "senai134/thiago/teste";
const char* TOPICO_PUB = "senai134/thiago/teste";

void aoReceber(char*, byte*, unsigned int);

WiFiClient clienteWifi;
PubSubClient mqtt(clienteWifi);

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(nomeRedeWiFi, senhaRedeWiFi);

  Serial.println();
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("#");
    delay(500);
  }
  Serial.println();

  mqtt.setServer(BROKER, PORTA);
  mqtt.setCallback(aoReceber);
  String id = "esp32-" + String((uint32_t)ESP.getEfuseMac(), HEX);

  bool conectadoAoBroker = false;
  conectadoAoBroker = mqtt.connect(id.c_str());

  if(conectadoAoBroker)
  {
    Serial.printf("Conectado com sucesso ao Broker %s\n\r", BROKER);
    mqtt.subscribe(TOPICO_SUB);
    Serial.printf("Inscrito no tópico: %s\n\r", TOPICO_SUB);
  }
  else
  {
    Serial.print("Falha ao conectar ao broker %s\n\r");
    Serial.print("Falha: "); Serial.println(mqtt.state());
  }
}

void loop() 
{
  mqtt.loop();
}

void aoReceber(char* topico, uint8_t* payload, unsigned int tamanho)
{
  String mensagem;
  mensagem.reserve(tamanho);

  for(unsigned int i = 0; i < tamanho; i++)
  {
    mensagem += (char)payload[i];
  }

  Serial.printf("Mensagem Recebida no tópico: %s \n\r mensagem: %s\n\r", topico, 
  mensagem.c_str());
}