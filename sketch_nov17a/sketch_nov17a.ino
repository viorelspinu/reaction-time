#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


long start_time = 0;
int state = 0;

#define BEFORE_ACTIVE_STATE 0
#define BEFORE_BUTTON_STATE 1
#define WAIT_FOR_BUTTON_STATE 2

#define LED_PIN 8
#define BUTTON_PIN 7

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
}


void loop() {
  if (state == BEFORE_ACTIVE_STATE) {    
    int rand_number = random(20000);
    if (rand_number == 1){  
      digitalWrite(LED_PIN, HIGH);
      start_time = millis();
      state = WAIT_FOR_BUTTON_STATE;   
    }       
  }
  
  if (state == WAIT_FOR_BUTTON_STATE){
    int button = digitalRead(BUTTON_PIN);   
    if (button == HIGH){
      digitalWrite(LED_PIN, LOW);
      
      long duration = millis() - start_time;   
      lcd.print(duration);
      delay(10000);
      lcd.clear();
      lcd.print("Get ready !");
      delay(1000);
      lcd.clear();
      state = BEFORE_ACTIVE_STATE;
    }
  }

}

