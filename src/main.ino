#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0x20);

const int PIN_GAS = A3;
const int LED_1 = 3;
const int LED_2 = 4;
const int LED_3 = 5;
const int LED_4 = 6;
const int LED_5 = 7;
const int BUZZER_PIN = 13;

int pw = 0;

void display(int value)
{
  if (value >= 80)
  {
    if (pw != 5)
    {
      lcd.clear();
      lcd.print("Evacuate Now!");
      pw = 5;
    }
  }
  else if (value >= 60)
  {
    if (pw != 4)
    {
      lcd.clear();
      lcd.print("Danger!");
      pw = 4;
    }
  }
  else if (value >= 40)
  {
    if (pw != 3)
    {
      lcd.clear();
      lcd.print("Warning!");
      pw = 3;
    }
  }
  else if (value >= 20)
  {
    if (pw != 2)
    {
      lcd.clear();
      lcd.print("Low");
      pw = 2;
    }
  }
  else
  {
    if (pw != 1)
    {
      lcd.clear();
      lcd.print("Safe");
      pw = 1;
    }
  }
}

void greetings()
{
  lcd.print("Gas Detector");
  delay(1000);
  lcd.clear();
  char loading_arr[] = {'/', '|', '\\', '-', '|'};
  // 12
  lcd.print("Starting Up  ");

  for (int j = 0; j < 3; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      lcd.setCursor(0, 12);
      lcd.print(loading_arr[i]);
      delay(200);
    }
  }
  lcd.clear();
  // / | \ - |
}

void setup()
{
  lcd.begin(16, 2);
  greetings();
  pinMode(PIN_GAS, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  long frequency;
  int value = map(analogRead(PIN_GAS), 300, 750, 0, 100);
  display(value);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, value >= 20 ? HIGH : LOW);
  digitalWrite(LED_3, value >= 40 ? HIGH : LOW);
  digitalWrite(LED_4, value >= 60 ? HIGH : LOW);
  digitalWrite(LED_5, value >= 80 ? HIGH : LOW);
  frequency = map(value, 0, 1023, 1500, 2500);
  if (value >= 50)
  {
    tone(BUZZER_PIN, frequency, 250);
  }
  Serial.println(value);
  delay(250);
}