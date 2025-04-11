#include <LiquidCrystal.h>

// LCD configuration (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

// Ultrasonic sensor pins
#define trigPin 7
#define echoPin 8

// Output pins
#define redLED 6
#define yellowLED 5
#define greenLED 4
#define buzzer 3

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Garage Parking");
  delay(2000);
  lcd.clear();
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // cm
  return distance;
}

void loop() {
  long distance = getDistance();

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm   ");

  if (distance < 10) {
    // Too close - Red LED + Buzzer
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("STOP! Too Close ");
  } else if (distance >= 10 && distance <= 30) {
    // Medium distance - Yellow LED
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Slow... Be Careful");
  } else {
    // Safe distance - Green LED
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Safe to Park     ");
  }

  delay(300);
}
