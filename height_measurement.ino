#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1


Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;
float height;


float sensorHeight = 200.0;   

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Wire.begin();

 
  if (!display.begin(0x3C, true)) {
    while (1);   
  }

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Height Measurement");
  display.display();
  delay(2000);
}

void loop() {
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH, 30000); 

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  // Calculate height
  height = sensorHeight - distance;

  // Prevent negative values
  if (height < 0) height = 0;

  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("HEIGHT MEASUREMENT");
  display.println("-----------------");

  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print(height, 1);   // 1 decimal place
  display.println(" cm");

  display.display();

  delay(500);
}
