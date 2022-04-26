#include<LiquidCrystal.h>
#include<math.h>
#define rs 2
#define en 3
#define d4 4
#define d5 5
#define d6 6
#define d7 7
#define buttonF 8
#define buttonM 9
#define buttonB 10
#define RbuttonF 11
#define RbuttonM 12
#define RbuttonB 13

int numFront = 0, numBack = 0;
double v, a, Time;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.blink();
  pinMode(buttonF, INPUT);
  pinMode(buttonM, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(RbuttonF, INPUT);
  pinMode(RbuttonM, INPUT);
  pinMode(RbuttonB, INPUT);
}

void loop() {
  if (digitalRead(buttonB) == HIGH || digitalRead(RbuttonF) == HIGH)
    processError();
  else if (digitalRead(buttonF) == HIGH)
    processFront();
  else if (digitalRead(RbuttonB) == HIGH)
    processBack();
  
  
  
}

void processFront() {
  numFront++;
  Time = 0;
  double x, y, z;
  x = Time;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("please wait ...");
  while (1)
  { Time++;
    delay(1);
    if (digitalRead(buttonM) == HIGH)
    {
      y = Time;
      break;
    }
  }

  while (1)
  { Time++;
    delay(1);
    if (digitalRead(buttonB) == HIGH)
    { z = Time;
      break;
    }
  }
  process(x, y, z);
  delay(250);
}

void processBack()
{
  numBack++;
  Time = 0;
  double x, y, z;
  x = Time;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("please wait ...");

  while (1)
  { Time++;
    delay(1);
    if (digitalRead(RbuttonM) == HIGH)
    { y = Time;
      break;
    }
  }

  while (1)
  { Time++;
    delay(1);
    if (digitalRead(RbuttonF) == HIGH)
    { z = Time;
      break;
    }
  }

  process(x, y, z);
  delay(250);
}

void processError(){
  lcd.clear();
  lcd.print("ERROR");
}

void process(double x, double y, double z)
{
    x/=1000;
    y/=1000;
    z/=1000;
  double v1, v2;         // V = delta(d)/delta(t)
  v1 = 4.0 / abs(x - y);             // v1 = d1/t1  ; d1=d2=d=4
  v2 = 4.0 / abs(y - z);       // v2 = d2/t2
  v = (v1 + v2) / 2.0;               // V(average)
  a = abs(v1 - v2) / abs(x - z);     // a = delta(v)/delta(t)

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("n=");
  lcd.print(numFront);
  lcd.setCursor(5, 0);
  lcd.print(", ");
  lcd.print("v=");
  lcd.print(v);
  lcd.setCursor(13, 0);
  lcd.print("m/s");

  lcd.setCursor(0, 1);
  lcd.print("a=");
  lcd.print(a);
  lcd.setCursor(6, 1);
  lcd.print("m/s^2 ");
  lcd.print("m=");
  lcd.print(numBack);
  
}
