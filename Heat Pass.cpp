#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int sensorPin = A2;
float temperatura = 0;

int inches = 0;
int cm = 0;

const int ledVerdePin = 9; // Pino do LED verde
const int ledVermelhoPin = 8; // Pino do LED vermelho

unsigned long lcdUpdateTime = 0; // Variável para controlar a atualização do LCD

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledVermelhoPin, OUTPUT);
}

void loop() {
  // Atualiza o LCD a cada 500 milissegundos
  if (millis() - lcdUpdateTime >= 500) {
    updateLCD();
    lcdUpdateTime = millis();
  }
}

void updateLCD() {
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  inches = (cm / 2.54);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");

  int reading = analogRead(sensorPin);
  float voltage = reading * (5000.0 / 1024.0);
  temperatura = (voltage - 500) / 10;

  Serial.print(temperatura);
  Serial.print("\xB0C");
  Serial.println("C");

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(temperatura);
  lcd.setCursor(11, 0);
  lcd.print("C");

  if (cm <= 30) {
    lcd.setCursor(2, 1);
    lcd.print("PORTA ABERTA");
    digitalWrite(ledVerdePin, LOW); // Desliga o LED verde
    digitalWrite(ledVermelhoPin, HIGH); // Liga o LED vermelho
  } else {
    lcd.setCursor(2, 1);
    lcd.print("PORTA FECHADA");
    digitalWrite(ledVerdePin, HIGH); // Liga o LED verde
    digitalWrite(ledVermelhoPin, LOW); // Desliga o LED vermelho
  }
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  pinMode(6, INPUT);
  return pulseIn(6, HIGH);
}
