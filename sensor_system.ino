#include <dht.h>
#include <NewPing.h>
#include <LiquidCrystal.h>
#include <Event.h>
#include <Timer.h>
#include <string.h>
#define DHT11_PIN 12

/****ULTRASONIC DEFINITIONS ****/
#define TRIGGER_PIN 10
#define ECHO_PIN 8
#define MAX_DISTANCE 20
#define uppertemp 25
#define lowertemp 5
dht DHT;
unsigned int distance = 0;
unsigned int min_distance = 7;


int i = 0;

/****TIMER DEFINITONS****/
Timer t;
int ten_sec;
int two_sec;
int two_sec_ext;
int five_sec;

#define greenpin A3
#define yellowpin A2
#define redpin A1
#define bluepin A0


float sum = 0;
float meantemp = 0;
float extreme = 0;

boolean flag_mean = false;
boolean flag_extreme = false;
boolean flag_random = false;
boolean flag_distance = false;

//screen initialization
const int numRows = 2;
const int numCols = 16;
char object[16]; // to show a message
LiquidCrystal lcd(3, 2, 4, 5, 6, 7); //pins to the screen


float randomtemp = 20; //intermediate value

// NewPing setup of pins and maximum distance, constructor 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(bluepin, OUTPUT);
  pinMode(redpin, OUTPUT);
  pinMode(yellowpin, OUTPUT);
  pinMode(greenpin, OUTPUT);

  //initialize LED's
  digitalWrite(bluepin, LOW);
  digitalWrite(redpin, LOW);
  digitalWrite(yellowpin, LOW);
  digitalWrite(greenpin, LOW);

  //use of every function
  t.every(5000, readtemp);
  lcd.clear();
  lcd.begin(numCols, numRows);
  lcd.print("Good Morning");
  delay(2000);
  lcd.clear();

}

void loop() {
  t.update();
  distance = sonar.ping_cm();
  if (distance > 0 && distance < 10) {
  flag_distance = true;
  lcd.setCursor(0, 1);
  lcd.print("distance:");
  lcd.setCursor(0, 0);
  lcd.print("mean:");
  digitalWrite(greenpin, HIGH);
    
  delay(600);
  
  lcd.setCursor(0, 1);
  lcd.print("         ");
  lcd.setCursor(0, 0);
  lcd.print("         ");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.setCursor(0, 0);
  lcd.print(meantemp);
  Serial.println(object);
  }
  digitalWrite(greenpin, LOW);
}

void readtemp() {
  int j;
  int chk = DHT.read11(DHT11_PIN);

  if (DHT.temperature > 0) {
    sum = sum + DHT.temperature;
    Serial.println(DHT.temperature);
    if (DHT.temperature > uppertemp) {
      digitalWrite(redpin, HIGH);
      flag_extreme = true;
      extreme = DHT.temperature;
      if (i == 24) {
        lcd.setCursor(0, 0);
        lcd.write("mean value:");
        delay(2000);
      }
      else {
        lcd.setCursor(8, 0);
        lcd.write("extreme: ");
        delay(1000);
        two_sec_ext = t.after(2000, lcd_extreme);
      }
    }
    else if (DHT.temperature < lowertemp) {
      digitalWrite(bluepin, HIGH);
      extreme = DHT.temperature;
      lcd.setCursor(8, 0);
      lcd.write("extreme: ");
      delay(1000);
      two_sec_ext = t.after(2000, lcd_extreme);
    }

    if (DHT.temperature > randomtemp) {
      digitalWrite(yellowpin, HIGH);
    } else {
      digitalWrite(yellowpin, LOW);
    }
    }

i = i + 1;
if (i == 24) {
    meantemp = (float)sum / i;
    i = 0;
    sum = 0;
    Serial.println(meantemp);

    // memset(dht_temp, 0, 24);
    lcd.setCursor(0, 0);
    lcd.write("mean: ");
    delay(1000);
    two_sec = t.after(2000, lcd_mean);
    flag_mean = true;
    ten_sec = t.after(10000, clearlcd_mean);
    Serial.println("mean found:   ");
    Serial.print(meantemp);
}

}

void lcd_mean() {
  lcd.setCursor(0, 0);
  lcd.write("        ");
  lcd.setCursor(0, 0);
  lcd.print(meantemp);
  t.stop(two_sec);
  ten_sec = t.after(10000, clearlcd_mean);
}

void clearlcd_mean() {
  lcd.setCursor(0, 0);
  lcd.write("        ");
  t.stop(ten_sec);
  flag_mean = false;
}

void lcd_extreme() {
  if (i == 24) {
    lcd.setCursor(0, 0);
    lcd.write("        ");
    lcd.setCursor(0, 0);
    lcd.print(meantemp);
    t.stop(two_sec);
    five_sec = t.after(5000, clearlcd_ext);
  }

  lcd.setCursor(8, 0);
  lcd.write("        ");
  lcd.setCursor(8, 0);
  lcd.print(extreme);
  flag_extreme = false;
  t.stop(two_sec_ext);

  five_sec = t.after(5000, clearlcd_ext);
}


void clearlcd_ext() {
  lcd.setCursor(8, 0);
  lcd.write("        ");
  t.stop(five_sec);
  digitalWrite(bluepin, LOW);
  digitalWrite(redpin, LOW);
}
