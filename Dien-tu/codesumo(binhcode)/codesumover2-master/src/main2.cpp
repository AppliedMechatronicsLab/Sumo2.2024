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
int a[3];
uint8_t checking_yprevious = 0; // binh viet
#define button_K6 A0            // chay mu 2s ben phai sau do bat cam bien (Pass)
#define button_K7 A1            // delay 3s chay default (Pass)
#define button_K8 A2            // tactics ne (dang hoan thien)
#define button_K5 A3
#define button_K4 A4
#define button_K1 A7
#define button_K2 A6 // sap xep nhu buoi`
#define button_K3 A5
int val_K1, val_K2, val_K3, val_K4, val_K5, val_K6, val_K7, val_K8, val_key;
boolean firstRun = true; // co chay lan dau tien
unsigned long previousSR_millis = 0;
unsigned long duration1, duration2, duration3;
int distance1;
int distance2;
int distance3;
int lastdistance1 = 0;
int lastdistance2 = 0;
int lastdistance3 = 0;
int block = 40;
int button_state = 0;
bool chaythang = 0, chaythang1 = 0, chaythang2 = 0;
int position = 0;

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

void Sort()
{
    read_SRF();
    read_SRR();
    read_SRL();
    if (distance1 > block && distance2 > block && distance3 > block)
    {
        position = 0;
    }
    else
    {

        if (distance1 <= distance2 && distance1 <= distance3)
            position = 1;
        else if (distance2 <= distance1 && distance2 <= distance3)
            position = 2;
        else
            position = 3;
    }

    Serial.print("  read F  ");
    Serial.print(distance1);

    Serial.print("  read R  ");
    Serial.print(distance2);

    Serial.print("  read L  ");
    Serial.print(distance3);

    Serial.print("  pos  ");
    Serial.println(position);
}
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
    analogWrite(LPWM, 235);
    analogWrite(RPWM, 0);
    analogWrite(LPWM1, 235);
    analogWrite(RPWM1, 0);
}
void ROTATEL()
{
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 235);
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 235);
}
void RBACKWARD()
{
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 255);
    analogWrite(LPWM1, 130);
    analogWrite(RPWM1, 0);
}
void LBACKWARD()
{
    analogWrite(LPWM, 0);
    analogWrite(LPWM1, 255);
    analogWrite(RPWM, 130);
    analogWrite(RPWM1, 0);
}
void RFORWARD() // ben phai
{

    analogWrite(LPWM, 255);
    analogWrite(RPWM, 0);
    analogWrite(LPWM1, 0);   // 0
    analogWrite(RPWM1, 195); /// 130
}
void LFORWARD()
{

    analogWrite(LPWM, 195); /// 130
    analogWrite(RPWM, 0);   // 0 cai nay bi yeu qua nen phai tang len do khung
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

void search_and_moving()
{
    Sort();
    if (position == 0)
    {
        ROTATEL();
    }

    if (position == 1) // thang truoc mat;
    {
        if (checking_yprevious == 1)
        {
            RFORWARD();
            delay(200);
            checking_yprevious = 0;
        }
        else if (checking_yprevious == 2)

        {
            LFORWARD();
            delay(200);
            checking_yprevious = 0;
        }
        PUSH();
    }
    else if (position == 2) // ben trai
    {
        Serial.println("RRR");
        ROTATER();
        // RFORWARD();
        checking_yprevious = 1;
    }
    else if (position == 3) // ben phai
    {
        Serial.println("LLL");
        ROTATEL();
        // LFORWARD();
        checking_yprevious = 2;
    }
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
    delay(300);
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
    pinMode(button_K3, INPUT_PULLUP);
    pinMode(button_K2, INPUT_PULLUP);
    pinMode(button_K1, INPUT_PULLUP);
    // ngat
    attachInterrupt(0, proval, RISING);
    attachInterrupt(1, proval, RISING);
    attachInterrupt(2, proval, RISING);
}
int readbutton()
{
    val_K6 = digitalRead(button_K6);
    delay(4);
    val_K7 = digitalRead(button_K7);
    delay(4);
    val_K8 = digitalRead(button_K8);
    delay(4);
    val_K5 = digitalRead(button_K5);
    delay(4);
    val_K4 = digitalRead(button_K4);
    delay(4);
    val_K1 = digitalRead(button_K1);
    delay(4);
    val_K2 = digitalRead(button_K2);
    delay(4);
    val_K3 = digitalRead(button_K3);
    delay(4);
    if (val_K6 == 0)
    {
        button_state = 6;
    }
    else if (val_K7 == 0)

        button_state = 7;

    else if (val_K8 == 0)

        button_state = 8;

    else if (val_K5 == 0)

        button_state = 5;
    else if (val_K4 == 0)
        button_state = 4;
    else if (val_K1 == 0)
        button_state = 1;
    else if (val_K2 == 0)
        button_state = 2;
    else if (val_K3 == 0)
        button_state = 3;
}
void basic_run()
{
    proval();
    if (read_SRF == read_SRR && read_SRL == read_SRF)
    {
        ROTATEL();
    }
    else
        search_and_moving();
}
void run_to_center_and_avoid()
{
    if (!chaythang)
    {
        PUSH();
        delay(450);
        chaythang = 1;
    }
    else
        basic_run();
}
void run_to_center_and_avoid1()
{
    if (!chaythang1)
    {

        LFORWARD();
        delay(2000);
        ROTATEL();
        delay(100);
        chaythang1 = 1;
    }
    else
        basic_run();
}
void run_to_center_and_avoid2()
{
    if (!chaythang2)
    {
        RFORWARD();
        delay(2000);
        ROTATER();
        delay(100);
        chaythang2 = 1;
    }
    else
        basic_run();
}

void loop()
{
    readbutton();
    switch (button_state)
    {
    case 1:
        if (firstRun)
        {
            delay(2900);
            firstRun = false;
        }
        else
            basic_run();
        break;
    case 3:
        if (firstRun)
        {
            delay(2900);
            firstRun = false;
        }
        else
            run_to_center_and_avoid();
        break;
    case 5:
        if (firstRun)
        {
            delay(2900);
            firstRun = false;
        }
        else
            run_to_center_and_avoid1();

        break;
    case 7:
        if (firstRun)
        {
            delay(2900);
            firstRun = false;
        }
        else
            run_to_center_and_avoid2();
        break;
    case 6:
        STOP();
        chaythang = 0;
        chaythang1 = 1;
        chaythang2 = 1;
        firstRun = 1;
        break;
    }
}