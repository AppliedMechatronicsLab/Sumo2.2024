/*
                                                              * @author [Vuz]
                                                              * @email [luuquangvu2023cv@gmail.com]
                                                              * @create date 2024-04-15 03:26:11
                                                              * @modify date 2024-05-03 07:00:00
                                                              * @desc [Robot SUMO 2024 - AML 2 Phenikaa Uni ]

*/

#include <Arduino.h>
int RPWM1 = 7;
int LPWM1 = 6;
int RPWM = 8;
int LPWM = 9;
int IRR = 2;
int IRL = 3;
int IRB = 21;  // chua test
int trig1 = 4; // SR trướcttttt
int echo1 = 5;
int trig2 = 12; // SR phải
int echo2 = 13;
int trig3 = 10; // SR trái
int echo3 = 11;
int valIRR;
int valIRL;
int valIRB;
#define button_K6 A0 // chay mu 2s ben phai sau do bat cam bien (Pass)
#define button_K7 A1 // delay 3s chay default (Pass)
#define button_K8 A2 // tactics ne (dang hoan thien)
#define button_K5 A3
#define button_K4 A4
#define button_K3 A6 // re trai
#define button_K2 A7 // re phai
unsigned long previousSR_millis = 0;
unsigned long duration1, duration2, duration3;
int distance1;
int distance2;
int distance3;
int lastdistance1 = 0;
int lastdistance2 = 0;
int lastdistance3 = 0;
boolean firstRun = true; // co chay lan dau tien
int time_behind = 0;
void BACKWARD()
{
  analogWrite(LPWM, 0);
  analogWrite(LPWM1, 255);
  analogWrite(RPWM, 255);
  analogWrite(RPWM1, 0);
}

void STOP()
{
  analogWrite(LPWM, 0);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 0);
}
void ROTATER()
{
  analogWrite(LPWM, 175);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 175);
  analogWrite(RPWM1, 0);
  delay(444);
}
void ROTATEL()
{
  analogWrite(LPWM, 0);
  analogWrite(RPWM, 175);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 175);
  delay(444);
}
void RBACKWARD()
{
  analogWrite(LPWM, 0);
  analogWrite(RPWM, 255);
  analogWrite(LPWM1, 230);
  analogWrite(RPWM1, 0);
}
void LBACKWARD()
{
  analogWrite(LPWM, 0);
  analogWrite(LPWM1, 255);
  analogWrite(RPWM, 230);
  analogWrite(RPWM1, 0);
}
void RFORWARD()
{
  analogWrite(LPWM, 255);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 230);
}
void LFORWARD()
{
  analogWrite(LPWM, 230);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 255);
}
void PUSH()
{
  analogWrite(LPWM, 255);
  analogWrite(RPWM, 0);
  analogWrite(LPWM1, 0);
  analogWrite(RPWM1, 255);
}
void read_SRF()
{
  // SR04 truoc
  digitalWrite(trig1, 0);
  delayMicroseconds(2);
  digitalWrite(trig1, 1);
  delayMicroseconds(5);
  digitalWrite(trig1, 0);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = int(duration1 / 2 / 29.412);
}
void read_SRR()
{
  // SR04 phai
  digitalWrite(trig2, 0);
  delayMicroseconds(2);
  digitalWrite(trig2, 1);
  delayMicroseconds(5);
  digitalWrite(trig2, 0);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = int(duration2 / 2 / 29.412);
}
void read_SRL()
{
  // SR04 trai
  digitalWrite(trig3, 0);
  delayMicroseconds(2);
  digitalWrite(trig3, 1);
  delayMicroseconds(5);
  digitalWrite(trig3, 0);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = int(duration3 / 2 / 29.412);
}
void proval()
{
  valIRR = digitalRead(IRR);
  valIRL = digitalRead(IRL);
  valIRB = digitalRead(IRB);

  if (valIRR == 0)
  {
    Serial.println("Lui trai");
    RBACKWARD();
  }
  else if (valIRL == 0)
  {
    Serial.println("Lui phai");
    LBACKWARD();
  }
  else if (valIRL == 0 && valIRR == 0)
  {
    Serial.println("Thoathiem");
    BACKWARD();
  }
  else if (valIRB == 0)
  {
    Serial.println("Tien");
    PUSH();
  }
}
int filterValF()
{
  if (abs(distance1 - lastdistance1) > 50)
  {
    lastdistance1 = distance1;
    return min(lastdistance1, 50);
  }
  else
  {
    return min(distance1, 50);
  }
}
int filterValR()
{
  if (abs(distance2 - lastdistance2) > 35)
  {
    lastdistance2 = distance2;
    return min(lastdistance2, 35);
  }
  else
  {
    return min(distance2, 35);
  }
}
int filterValL()
{
  if (abs(distance3 - lastdistance3) > 35)
  {
    lastdistance3 = distance3;
    return min(lastdistance3, 35);
  }
  else
  {
    return min(distance3, 35);
  }
}
boolean run_deafaul = true;
void tactic_default()
{
  if (run_deafaul == true)
  {
    if (run_deafaul == true)
    {
      if (filterValR() <= 40)
      {
        analogWrite(LPWM, 180);
        analogWrite(RPWM, 0);
        analogWrite(LPWM1, 70);
        analogWrite(RPWM1, 0);
        delay(333);
      }
      else if (filterValL() <= 40)
      {
        analogWrite(LPWM, 0);
        analogWrite(RPWM, 70);
        analogWrite(LPWM1, 0);
        analogWrite(RPWM1, 180);
        delay(333);
      }
      else if (filterValF() <= 45)
      {
        analogWrite(LPWM, 255);
        analogWrite(RPWM, 0);
        analogWrite(LPWM1, 0);
        analogWrite(RPWM1, 255);
      }
      run_deafaul = false;
    }
    else if (run_deafaul == false)
    {
      if (filterValF() <= 45)
      {
        Serial.println("pushF");
        PUSH();
      }
      else if (filterValR() <= 40)
      {
        Serial.println("pushR");
        ROTATER();
      }
      else if (filterValL() <= 40)
      {
        Serial.println("pushL");
        ROTATEL();
      }
      else if (filterValF() <= 20 && filterValR() <= 20)
      {
        Serial.println("chay ne diem mu phai");
        RFORWARD();
      }
      else if (filterValF() <= 20 && filterValL() <= 20)
      {
        Serial.println("chay ne diem mu trai");
        LFORWARD();
      }
      else
      {
        ROTATEL();
      }
    }
  }
}

boolean flagrun_attackR = true;
void tactic_attackR()
{
  if (flagrun_attackR == true)
  {
    analogWrite(LPWM, 255);
    analogWrite(RPWM, 0);
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 225);
    delay(1500);
    flagrun_attackR = false;
  }
  else if (flagrun_attackR == false)
  {
    Serial.println("chay mu");
    if (filterValF() <= 10)
    {
      Serial.println("Lock");
      PUSH();
    }
    else
    {
      if (filterValF() <= 60)
      {
        Serial.println("pushF");
        PUSH();
      }
      else if (filterValR() <= 45)
      {
        Serial.println("pushR");
        ROTATER();
      }
      else if (filterValL() <= 45)
      {
        Serial.println("pushL");
        ROTATEL();
      }
      else if (filterValF() <= 20 && filterValR() <= 20)
      {
        Serial.println("chay ne diem mu phai");
        RFORWARD();
      }
      else if (filterValF() <= 20 && filterValL() <= 20)
      {
        Serial.println("chay ne diem mu trai");
        LFORWARD();
      }
      else
      {
        ROTATEL();
      }
    }
  }
}

boolean flagrun_attackL = true;
void tactic_attackL()
{
  if (flagrun_attackL == true)
  {
    analogWrite(LPWM, 255);
    analogWrite(RPWM, 0);
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 225);
    delay(2000);
    flagrun_attackL = false;
  }
  else if (flagrun_attackL == false)
  {
    if (filterValF() <= 10)
    {
      PUSH();
    }
    else
    {
      if (filterValF() <= 60)
      {
        Serial.println("pushF");
        PUSH();
      }
      else if (filterValR() <= 45)
      {
        Serial.println("pushR");
        ROTATER();
      }
      else if (filterValL() <= 45)
      {
        Serial.println("pushL");
        ROTATEL();
      }
      else if (filterValF() <= 20 && filterValR() <= 20)
      {
        Serial.println("chay ne diem mu phai");
        RFORWARD();
      }
      else if (filterValF() <= 20 && filterValL() <= 20)
      {
        Serial.println("chay ne diem mu trai");
        LFORWARD();
      }
      else
      {
        ROTATEL();
      }
    }
  }
}

void tactic_defence()
{

  if (filterValR() <= 30)
  {
    Serial.println("ne");
    RFORWARD();
  }
  else if (filterValL() <= 30)
  {
    Serial.println("ne");
    LBACKWARD();
  }
  else
  {
    if (filterValF() <= 60)
    {
      PUSH();
      Serial.println("PushF");
    }
    else
    {
      ROTATER();
    }
  }
}
boolean run_farDefault = true;
void tactic_farDefault()
{
  if (run_farDefault == true)
  {
    if (filterValR() <= 45)
    {
      analogWrite(LPWM, 225);
      analogWrite(RPWM, 0);
      analogWrite(LPWM1, 100);
      analogWrite(RPWM1, 0);
      delay(333);
    }
    else if (filterValL() <= 45)
    {
      analogWrite(LPWM, 0);
      analogWrite(RPWM, 100);
      analogWrite(LPWM1, 0);
      analogWrite(RPWM1, 225);
      delay(333);
    }
    else if (filterValF() <= 60)
    {
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 0);
      analogWrite(LPWM1, 0);
      analogWrite(RPWM1, 255);
    }
    run_farDefault = false;
  }
  else if (run_farDefault == false)
  {
    if (filterValF() <= 60)
    {
      Serial.println("pushF");
      PUSH();
    }
    else if (filterValR() <= 45)
    {
      Serial.println("pushR");
      ROTATER();
    }
    else if (filterValL() <= 45)
    {
      Serial.println("pushL");
      ROTATEL();
    }
    else if (filterValF() <= 20 && filterValR() <= 20)
    {
      Serial.println("chay ne diem mu phai");
      RFORWARD();
    }
    else if (filterValF() <= 20 && filterValL() <= 20)
    {
      Serial.println("chay ne diem mu trai");
      LFORWARD();
    }
    else
    {
      ROTATEL();
    }
  }
}
int button_state = 0;
void Button_Control()
{
  int val_K6 = digitalRead(button_K6);
  int val_K7 = digitalRead(button_K7);
  int val_K8 = digitalRead(button_K8);
  int val_K5 = digitalRead(button_K5);
  int val_K4 = digitalRead(button_K4);
  int val_K2 = digitalRead(button_K2);
  int val_K3 = digitalRead(button_K3);

  if (val_K6 == 0)
  {
    button_state = 6;
  }
  else if (val_K7 == 0)
  {
    button_state = 7;
  }
  else if (val_K8 == 0)
  {
    button_state = 8;
  }
  else if (val_K5 == 0)
  {
    button_state = 5;
  }
  else if (val_K4 == 0)
  {
    button_state = 4;
  }
  else if (val_K2 == 0)
  {
    button_state = 2;
  }
  else if (val_K3 == 0)
  {
    button_state = 3;
  }
}

void setup()
{
  // while (1);
  Serial.begin(9600);
  // DC
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  // IR
  pinMode(IRR, INPUT);
  pinMode(IRL, INPUT);
  pinMode(IRB, INPUT);
  // SR
  pinMode(trig1, OUTPUT); // Phat
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);

  pinMode(echo1, INPUT); // Nhan
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  // nut bam
  pinMode(button_K6, INPUT_PULLUP);
  pinMode(button_K7, INPUT_PULLUP);
  pinMode(button_K8, INPUT_PULLUP);
  pinMode(button_K5, INPUT_PULLUP);
  pinMode(button_K4, INPUT_PULLUP);
  // ngat
  attachInterrupt(0, proval, RISING);
  attachInterrupt(1, proval, RISING);
  attachInterrupt(2, proval, RISING);
}

void loop()
{
  read_SRF(); //* doc cam bien SR
  read_SRL();
  read_SRR();

  filterValF(); //* chay qua bo loc
  filterValL();
  filterValR();
  Button_Control();
  if (button_state == 6) // Chay mu tan cong phai
  {
    if (firstRun == true)
    {
      delay(2900);
      firstRun = false;
    }
    else
    {
      tactic_attackR();
      Serial.println("tan cong phai");
    }
  }
  else if (button_state == 7) // chay co ban < rcm>
  {
    if (firstRun == true)
    {
      delay(2900);
      firstRun = false; 
    }
    else
    {
      tactic_default();
      Serial.println("chay mac dich");
    }
  }
  else if (button_state == 8) // Chay ne doi thu
  {
    if (firstRun == true)
    {
      delay(2900);
      firstRun = false;
    }
    else
    {
      tactic_defence();
      Serial.println("Chay trien thuat phong ngu");
    }
  }
  else if (button_state == 5)
  {
    if (firstRun == true)
    {
      delay(2900);
      firstRun = false; //
    }
    else
    {
      tactic_farDefault();
      Serial.println("chay mac dich quet tam xa ");
    }
  }
  else if (button_state == 4) // Chay mu tan cong trai
  {
    if (firstRun == true)
    {
      delay(2900);
      firstRun = false;
    }
    else
    {
      tactic_attackL();
      Serial.println("chien thuat tan cong trai");
    }
  }
}