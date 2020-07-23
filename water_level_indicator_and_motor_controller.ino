
const int trig_pin = 6;
const int echo_pin = 7;
const int led = 8;
double duration;
int distance;
long total;
const int relay = 10;

float a;
int percent;

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte line[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000

};
byte smiley1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000

};
byte arrow[8] = {
  0b01000,
  0b00100,
  0b11110,
  0b11111,
  0b11110,
  0b00100,
  0b01000,
  0b00000

};
byte arrow1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000

};
byte arrow2[8] = {
  0b00000,
  0b00000,
  0b10000,
  0b11000,
  0b10000,
  0b00000,
  0b00000,
  0b00000

};
byte arrow3[8] = {
  0b00000,
  0b10000,
  0b11000,
  0b11100,
  0b11000,
  0b10000,
  0b00000,
  0b00000

};
byte arrow4[8] = {
  0b10000,
  0b01000,
  0b11100,
  0b11110,
  0b11100,
  0b01000,
  0b10000,
  0b00000

};
#include<EEPROM.h>
int present = 0;
int past = 0;
int counter = 1;


void setup() {

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  pinMode(13, INPUT);

  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.setTimeout(10);
  lcd.createChar(0, line);
  lcd.createChar(1, smiley);
  lcd.createChar(2, smiley1);
  lcd.createChar(3, arrow);
  lcd.createChar(4, arrow1);
  lcd.createChar(5, arrow2);
  lcd.createChar(6, arrow3);
  lcd.createChar(7, arrow4);
  lcd.setCursor(0, 0);

  lcd.print("hello!!");
  lcd.setCursor(5, 0);
  lcd.write(byte(1));
  delay(1000);
  lcd.setCursor(5, 0);
  lcd.write(byte(2));
  delay(1000);
  lcd.setCursor(5, 0);
  lcd.write(byte(1));
  delay(1000);




  // put your setup code here, to run once:

}

void loop() {
  void show();
  void show1();
  void show2();
  lcd.clear();
  int sensorValue = analogRead(A0);//set the depth of your tank by using the potentiometer
  int val = map(sensorValue, 0, 1023, 0, 500);//convert 0 to 1023 into 0 to 500 cm
 total = val;
 digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = 0.034 * duration / 2;
  a = total - distance;
  percent = ((a / total) * 100) + 8;//8% to avoid over flow and prevent sensor from water
  if (percent > 100)
  {
    percent = 100;
  }
  if (percent < 0)
  {
    percent = 0;
  }



  present = digitalRead(13);

  if (present == HIGH && present != past)
  {
    counter++;

  }
  past = present;
  if (counter % 2 == 0) //if button pressed it enters in to measurement mode to measure the depth of the tank
  { lcd.clear();
    lcd.write("measurement mode");
    Serial.println("\n measurement mode");
    lcd.setCursor(0, 1);
    lcd.print("Distance:");
    Serial.println("distance:");

    lcd.print(distance);
    lcd.print("cm");
    Serial.print(distance);
    Serial.print("cm");
    delay(200);
    lcd.clear();

  }
  else
  {
    if (percent < 20)
    {
      digitalWrite(relay, LOW);
    }
    if (percent >= 95 && present != HIGH)
    {
      digitalWrite(led, HIGH);
      digitalWrite(relay, HIGH);
      Serial.println("alert");
      show();
      show2();
      delay(500);
      lcd.clear();
      show1();
      delay(500);
    }
    else
    { digitalWrite(led, LOW);

    }
    if (percent < 99 && digitalRead(13) != HIGH)
    { show();
      show2();
      delay(200);
      // put your main code here, to run repeatedly:


    }
    counter = 1;
  }
}

void show()
{
  lcd.setCursor(5, 1);
  lcd.print("Depth:");
  lcd.print(total);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print(percent);
  lcd.print("%");


  lcd.setCursor(0, 0);
  lcd.print("level");
  lcd.setCursor(5, 0);
  lcd.write(byte(4));

  lcd.setCursor(5, 0);
  lcd.write(byte(5));

  lcd.setCursor(5, 0);
  lcd.write(byte(6));

  lcd.setCursor(5, 0);
  lcd.write(byte(7));

  lcd.setCursor(5, 0);
  lcd.write(byte(3));

  lcd.setCursor(6, 0);
  lcd.write(byte(4));

  lcd.setCursor(6, 0);
  lcd.write(byte(5));

  lcd.setCursor(6, 0);
  lcd.write(byte(6));

  lcd.setCursor(6, 0);
  lcd.write(byte(7));

  lcd.setCursor(6, 0);
  lcd.write(byte(3));

}
void show2()
{
  if (percent > 10)
  {
    lcd.setCursor(7, 0);
    lcd.write(byte(0));

  }
  if (percent > 20)
  {
    lcd.setCursor(8, 0);
    lcd.write(byte(0));

  }
  if (percent > 30)
  {
    lcd.setCursor(9, 0);
    lcd.write(byte(0));

  }
  if (percent > 40)
  {
    lcd.setCursor(10, 0);
    lcd.write(byte(0));

  }
  if (percent > 50)
  {
    lcd.setCursor(11, 0);
    lcd.write(byte(0));

  }
  if (percent > 60)
  {
    lcd.setCursor(12, 0);
    lcd.write(byte(0));

  }
  if (percent > 70)
  {
    lcd.setCursor(13, 0);
    lcd.write(byte(0));

  }
  if (percent > 80)
  {
    lcd.setCursor(14, 0);
    lcd.write(byte(0));

  }
  if (percent > 90)
  {
    lcd.setCursor(15, 0);
    lcd.write(byte(0));

  }


}
void show1()
{
  lcd.blink();
  lcd.setCursor(5, 1);

  lcd.print("tank full");
  delay(50);
  lcd.noBlink();
}
