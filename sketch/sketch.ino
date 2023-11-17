#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include<DHTesp.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define POWER_PIN 17
#define SIGNAL_PIN 35
#define relayPin1 13
int value = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 14    

#define DHTTYPE    DHT22 
DHTesp dhtSensor;    

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
   dhtSensor.setup(DHTPIN, DHTesp::DHT22);

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  pinMode(POWER_PIN, OUTPUT);   
  digitalWrite(POWER_PIN, LOW);
}

void loop() {
  delay(1000);

  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  delay(1000);
 float t = dht.readTemperature();
  float h = dht.readHumidity();
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: "+ String(data.temperature,2)+ "C");
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.print("Humidity: "+ String(data.humidity, 1) + "%");
  display.display();
  digitalWrite(POWER_PIN, HIGH);
  delay(10);                      
  value = analogRead(SIGNAL_PIN);
  digitalWrite(POWER_PIN, LOW); 
  if( value <= 10){
    digitalWrite(relayPin1,HIGH);
  }
  else if(value>60){
    digitalWrite(relayPin1,LOW);
  }
}