#include <DHT.h>

// Definições do sensor DHT11
#define DHTPINO A1
#define DHTTYPE DHT11
DHT dht(DHTPINO, DHTTYPE);

// Variáveis do PIR
const int PIR = 2;
const int ledVermelho = 13;

// Variáveis do MQ135
const int MQ135 = A0;
const int buzzer = 12;

void acenderLEDAoDetectarPresenca() {
    int estadoPIR = digitalRead(PIR);

    if (estadoPIR == HIGH) {
        digitalWrite(ledVermelho, HIGH);
        Serial.println("LED ligado - Movimento detectado!");
        delay(1000); // Mantém o LED ligado por um segundo
        digitalWrite(ledVermelho, LOW);
    } else {
        Serial.println("Nenhum movimento detectado.");
    }
}

void verificarVazamentosDeGas() {
    int estadoMQ135 = analogRead(MQ135);

    Serial.print("Valor MQ135: ");
    Serial.println(estadoMQ135);

    if (estadoMQ135 >= 600) {
        alarme_dois_tons();
    } else {
        noTone(buzzer);
    }
}

void alarme_dois_tons() {
    int freqAlta = 2000;
    int freqBaixa = 800;
    int duracaoTom = 250;

    tone(buzzer, freqAlta, duracaoTom);
    delay(duracaoTom);
    tone(buzzer, freqBaixa, duracaoTom);
    delay(duracaoTom);
}

void verificarTemperaturaEUmidade() {
    float umidade = dht.readHumidity();
    float temperatura = dht.readTemperature();

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println("%");

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");

    delay(7000);
}

void setup() {
    Serial.begin(9600);
    pinMode(ledVermelho, OUTPUT);
    pinMode(MQ135, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(PIR, INPUT);

    dht.begin();

    Serial.println("Calibrando os sensores...");
    delay(10000);
    Serial.println("Sensores calibrados!");
}

void loop() {
    //acenderLEDAoDetectarPresenca();
    //verificarVazamentosDeGas();
    verificarTemperaturaEUmidade();
}
