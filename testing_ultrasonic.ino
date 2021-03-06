//Ultrasonic setup variable
#include <LiquidCrystal.h>
#define trigPin 9
#define echoPin 10
//lcd pin list
int lcdRS = 2;
int lcdE = 3;
int lcdD4 = 4;
int lcdD5 = 5;
int lcdD6 = 6;
int lcdD7 = 7;
//button setup pin

int buzzerPin = 12;
//led setup pin
int redPin =24;
int y2Pin = 23;
int greenPin = 22;
//variable for statement related
int safeState;
int riskyState;
int dangerState;
//ultrasonic output
long duration, distance;//int value
float distance2;//decimals value
//statement display LCD
String lcdStatement[6] = {"Crash Distance  ", "Risky Distance  ", "Safe Distance   ", "Distance: ", " cm", "  "};


LiquidCrystal lcd(lcdRS, lcdE, lcdD4, lcdD5, lcdD6, lcdD7);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(y2Pin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);


}

void loop() {
  // put your main code here, to run repeatedly:
  final_result();
  delay(200);

}
// main function
void final_result()
{
  noTone(buzzerPin);
  digitalWrite(redPin, dangerState);
  digitalWrite(greenPin, safeState);
  
  digitalWrite(y2Pin, riskyState);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;//integers value
  distance2 = (duration / 2) / 29.1;//decimal value


  if (distance >= 75 || distance <= 0)
  {
    safeState = 1;
    riskyState = 0;
    dangerState = 0;
    displayer(safeState, riskyState, dangerState, distance2);
    
  }
  else if (distance > 25) {
    safeState = 0;
    riskyState = 1;
    dangerState = 0;
    displayer(safeState, riskyState, dangerState, distance2);
  }
  else
  {
    safeState = 0;
    riskyState = 0;
    dangerState = 1;
    displayer(safeState, riskyState, dangerState, distance2);
  }
}// function for simple version of both serial and lcd output display logic
void displayer(int safe, int risky, int danger, float ultradis)
{
  ultradis = ultradis - 1;
  if (safe == 1 && risky == 0 && danger == 0 ) {
    Serial.print(lcdStatement[3]);
    Serial.print(ultradis);
    Serial.print(lcdStatement[4]);
    Serial.println(lcdStatement[5]);
    lcd.setCursor(0, 0);
    lcd.print(lcdStatement[3]);
    lcd.print(ultradis);
    lcd.print(lcdStatement[5]);
    lcd.setCursor(0, 1);
    lcd.print(lcdStatement[2]);
  }
  else if (safe == 0 && risky == 1 && danger == 0) {
    Serial.print(lcdStatement[3]);
    Serial.print(ultradis);
    Serial.print(lcdStatement[4]);
    Serial.println(lcdStatement[5]);
    lcd.setCursor(0, 0);
    lcd.print(lcdStatement[3]);
    lcd.print(ultradis);
    lcd.print(lcdStatement[5]);
    lcd.setCursor(0, 1);
    lcd.print(lcdStatement[1]);
  }
  else if (safe == 0 && risky == 0 && danger == 1)
  {
    Serial.print(lcdStatement[3]);
    Serial.print(ultradis);
    Serial.print(lcdStatement[4]);
    Serial.println(lcdStatement[5]);
    lcd.setCursor(0, 0);
    lcd.print(lcdStatement[3]);
    lcd.print(ultradis);
    lcd.print(lcdStatement[5]);
    lcd.setCursor(0, 1);
    lcd.print(lcdStatement[0]);
    tone(buzzerPin, 1150);
  }
  digitalWrite(redPin, danger);
  digitalWrite(greenPin, safe);
  
  digitalWrite(y2Pin, risky);

}
