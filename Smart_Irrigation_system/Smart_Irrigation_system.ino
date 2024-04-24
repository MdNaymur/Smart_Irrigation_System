#include <Wire.h>
#include <LCD_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11 

#define MOISTURE_SENSOR A0 
#define RELAY_PIN 7 
#define PUMP_THRESHOLD 50
 
LCD_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); 
  dht.begin();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IoT Based Smart");
   lcd.setCursor(0, 1);
  lcd.print("Irrig. System Ok");
  delay(2000);
}

void loop() {
  float moistureValue = analogRead(MOISTURE_SENSOR);
  int moisture= map(moistureValue,0,1023,0,100);
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mois:");
  lcd.print(moisture);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");

  if (moistureValue < PUMP_THRESHOLD) {
    
    digitalWrite(RELAY_PIN, HIGH);
  } else {
   
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(1000); 
}
