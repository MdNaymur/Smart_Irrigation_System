#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 12  // Pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT sensor type

#define MOISTURE_SENSOR 34  // Pin connected to the moisture sensor
#define RELAY_PIN 4  // Pin connected to the relay module
#define PUMP_THRESHOLD 50  // Adjust this threshold value according to your sensor

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address of the I2C LCD display

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("IoT Based Smart");
  lcd.setCursor(0, 1);
  lcd.print("Irrig. System Ok");
  delay(2000);
  lcd.clear();
}

void loop() {
  int pump=digitalRead(RELAY_PIN);
  float moistureValue = analogRead(MOISTURE_SENSOR);
  int moisture=map(moistureValue,0,4895,0,100);
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();

  lcd.setCursor(0, 0);
  lcd.print("Mois:");
  lcd.print(moisture);

  lcd.setCursor(8, 0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum:");
  lcd.print(humidity);
  lcd.print("%");

  if (moisture> PUMP_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH);
    lcd.setCursor(8, 1);
    lcd.print("Pump: ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    lcd.setCursor(8, 1);
    lcd.print("Pump:OFF");
  }
  Serial.println("Pump Status: ");
  Serial.print(pump);

  delay(1000);  // Adjust the delay time as needed
}
