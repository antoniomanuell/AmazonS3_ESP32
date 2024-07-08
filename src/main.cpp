/* 

Esta é um exemplo de como inserir dados
de sensores com ESP32 em um Bucket no Amazon S3

*/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define LED_BUILTIN 2  // Pino do LED embutido

int sensorPin = 34;    // Pino ADC para leitura analógica
int threshold = 500;  // Limiar para acionar o LED
int sensorValue = 0;   // Variável para armazenar o valor do sensor

// Substitua pelas suas credenciais Wi-Fi
const char* ssid = "nome_da_rede";
const char* password = "palavra_passe";

// Substitua pelo nome do seu bucket e o URL
const char* bucket_name = "nome_do_bucket";
const char* s3_url = "https://nome_do_bucket.s3.regiao.amazonaws.com/";

void setup() {
  Serial.begin(115200);

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  pinMode(LED_BUILTIN, OUTPUT);  // Define o pino do LED como saída
  pinMode(sensorPin, INPUT);     // Define o pino do sensor como entrada (analógica)
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    sensorValue = analogRead(sensorPin);  // Lê o valor analógico do sensor
    Serial.println(sensorValue);          // Imprime o valor lido no monitor serial

    // Quando o valor do sensor excede o limiar, o LED pisca
    if (sensorValue > threshold) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }

  delay(100);  // Atraso para estabilizar a leitura do sensor
    
    String url = String(s3_url) + "audio.txt"; // Nome do arquivo no S3
    String data = "Valor do som: " + String(sensorValue);

    http.begin(url.c_str());
    http.addHeader("Content-Type", "text/plain");

    // Actualiza os dados (substitui)
    int httpResponseCode = http.PUT(data);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Erro no envio HTTP");
    }

    http.end();
  } else {
    Serial.println("WiFi não conectado");
  }

}
