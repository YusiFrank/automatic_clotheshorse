#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
#include <RainSense.h>
RainSense rs = RainSense(A2);
#include <DHT.h>
#include <DHT_U.h>
DHT dht(13, DHT11);

int mode = 0;
float temp;
int humid;

const byte button1 = 7;  //button
const byte button2 = 8;
const byte button3 = 9;
const byte led1 = 11; //LED
const byte led2 = 12;
const byte sensorf = 5;  //sensor
const byte sensorb = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  dht.begin();
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  //int mode = 0; //1 for rain detection, 0 for manual

  int b1 = digitalRead(button1); //go out
  int b2 = digitalRead(button2); //go in
  int b3 = digitalRead(button3); //mode
  int sf = digitalRead(sensorf);
  int sb = digitalRead(sensorb);
  //Serial.println(mode);
  led(mode);
  switch(mode){
    case(0):
    //Serial.println("mode0");
    if(b1 == 1 and b2 == 0){
        //Serial.println("A1");
        while(1){
          digitalWrite(3, HIGH);
          digitalWrite(2, LOW);
          sf = digitalRead(sensorf);
          if(sf == 0){
            digitalWrite(2, HIGH);
            digitalWrite(3, HIGH);
            break;
          }
        }
        break;
      }
      else if(b1 == 0 and b2 == 1){
        while(1){
          digitalWrite(3, LOW);
          digitalWrite(2, HIGH);
          sb = digitalRead(sensorb);
          if(sb == 0){
            digitalWrite(2, HIGH);
            digitalWrite(3, HIGH);
            break;
          }
        }
        break;
      }
      if(b3 == 1){
        mode = 1;
        //Serial.println("Changed");
        //Serial.println(mode);
        break;
      }
      break;

      case(1):
        //Serial.println("mode1");
        while(1){
          digitalWrite(3, HIGH);
          digitalWrite(2, LOW);
          sf = digitalRead(sensorf);
          if(sf == 0){
            digitalWrite(2, HIGH);
            digitalWrite(3, HIGH);
            break;
          }
        }
        b3 = digitalRead(button3);
        Serial.println(rs.rain(40));
        if(rs.rain(40) or humid > 80){
          while(1){
            digitalWrite(3, LOW);
            digitalWrite(2, HIGH);
            sb = digitalRead(sensorb);
            if(sb == 0){
              digitalWrite(2, HIGH);
              digitalWrite(3, HIGH);
              break;
            }
          }
          mode = 0;
          break;
        }

        if(b3 == 1){
          delay(10);
          mode = 0;
          break;
        }
        break;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Handing Clothes");
  temp = dht.readTemperature();
  humid = dht.readHumidity();
  Serial.println(humid);
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print(" H:");
  lcd.print(humid);
  lcd.print("%");
  //delay(100);
}

void led(int mode){
  if(mode == 0){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    }
    else{
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
    }
}
