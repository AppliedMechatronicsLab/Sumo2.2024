// #include <Arduino.h>
// int RPWM1 = 7;
// int LPWM1 = 6;
// int RPWM = 8;
// int LPWM = 9;
// int IRR = 2;
// int IRL = 3;
// int IRB = 21;  // chua test
// int trig1 = 4; // SR trướcttttt
// int echo1 = 5;
// int trig2 = 12; // SR phải
// int echo2 = 13;
// int trig3 = 10; // SR trái
// int echo3 = 11;
// int valIRR;
// int valIRL;
// int valIRB;
// int a[3];
// uint8_t checking_yprevious = 0; // binh viet
// #define button_K6 A0            // chay mu 2s ben phai sau do bat cam bien (Pass)
// #define button_K7 A1            // delay 3s chay default (Pass)
// #define button_K8 A2            // tactics ne (dang hoan thien)
// #define button_K5 A3
// #define button_K4 A4
// #define button_K1 A7
// #define button_K2 A6 // sap xep nhu buoi`
// #define button_K3 A5
// int val_K1, val_K2, val_K3, val_K4, val_K5, val_K6, val_K7, val_K8, val_key;
// boolean firstRun = true; // co chay lan dau tien
// unsigned long previousSR_millis = 0;
// unsigned long duration1, duration2, duration3;
// int distance1;
// int distance2;
// int distance3;
// int lastdistance1 = 0;
// int lastdistance2 = 0;
// int lastdistance3 = 0;
// int block = 30;
// bool pressbutton = 0;
// void read_SRF()
// {
//     // SR04 truoc
//     digitalWrite(trig1, 0);
//     delayMicroseconds(2);
//     digitalWrite(trig1, 1);
//     delayMicroseconds(5);
//     digitalWrite(trig1, 0);
//     duration1 = pulseIn(echo1, HIGH);
//     distance1 = int(duration1 / 2 / 29.412);

//     if (distance1 < block)
//         a[0] = distance1;
//     else
//         distance1 = 999;
// }
// void read_SRR()
// {
//     // SR04 phai
//     digitalWrite(trig2, 0);
//     delayMicroseconds(2);
//     digitalWrite(trig2, 1);
//     delayMicroseconds(5);
//     digitalWrite(trig2, 0);
//     duration2 = pulseIn(echo2, HIGH);
//     distance2 = int(duration2 / 2 / 29.412);

//     if (distance2 < block)
//         a[1] = distance2;
//     else
//         distance2 = 999;
// }
// void read_SRL()
// {
//     // SR04 trai
//     digitalWrite(trig3, 0);
//     delayMicroseconds(2);
//     digitalWrite(trig3, 1);
//     delayMicroseconds(5);
//     digitalWrite(trig3, 0);
//     duration3 = pulseIn(echo3, HIGH);
//     distance3 = int(duration3 / 2 / 29.412);
//     if (distance3 < block)
//         a[2] = distance3;
//     else
//         distance3 = 999;
// }

// void bubbleSort(int arr[], int n)
// {
//     read_SRF();
//     read_SRR();
//     read_SRL();
//     int i, j, temp;
//     for (i = 0; i < n - 1; i++)
//     {
//         for (j = 0; j < n - i - 1; j++)
//         {
//             if (arr[j] > arr[j + 1])
//             {
//                 // Hoán đổi giá trị của arr[j] và arr[j+1]
//                 temp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = temp;
//             }
//         }
//     }
//     // Serial.print("  read F  ");
//     // Serial.print(distance1);

//     // Serial.print("  read R  ");
//     // Serial.print(distance2);

//     // Serial.print("  read L  ");
//     // Serial.print(distance3);

//     // Serial.print("  a0  ");
//     // Serial.print(a[0]);

//     // Serial.print("  a1  ");
//     // Serial.print(a[1]);

//     // Serial.print("  a2  ");
//     // Serial.print(a[2]);
//     // Serial.println();
// }
// void BACKWARD()
// {
//     analogWrite(LPWM, 0);
//     analogWrite(LPWM1, 255);
//     analogWrite(RPWM, 255);
//     analogWrite(RPWM1, 0);
// }
// void STOP()
// {
//     analogWrite(LPWM, 0);
//     analogWrite(RPWM, 0);
//     analogWrite(LPWM1, 0);
//     analogWrite(RPWM1, 0);
// }
// void ROTATER()
// {
//     analogWrite(LPWM, 255);
//     analogWrite(RPWM, 0);
//     analogWrite(LPWM1, 255);
//     analogWrite(RPWM1, 0);
// }
// void ROTATEL()
// {
//     analogWrite(LPWM, 0);
//     analogWrite(RPWM, 255);
//     analogWrite(LPWM1, 0);
//     analogWrite(RPWM1, 255);
// }
// void RBACKWARD()
// {
//     analogWrite(LPWM, 0);
//     analogWrite(RPWM, 255);
//     analogWrite(LPWM1, 160);
//     analogWrite(RPWM1, 0);
// }
// void LBACKWARD()
// {
//     analogWrite(LPWM, 0);
//     analogWrite(LPWM1, 255);
//     analogWrite(RPWM, 160);
//     analogWrite(RPWM1, 0);
// }
// void RFORWARD() // ben phai
// {
//     analogWrite(LPWM, 205);
//     analogWrite(RPWM, 0);
//     analogWrite(LPWM1, 100); // 0
//     analogWrite(RPWM1, 0);   /// 130
// }
// void LFORWARD()
// {
//     analogWrite(LPWM, 0);   /// 130
//     analogWrite(RPWM, 100); // 0 cai nay bi yeu qua nen phai tang len do khung
//     analogWrite(LPWM1, 0);
//     analogWrite(RPWM1, 205);
// }
// void PUSH()
// {
//     analogWrite(LPWM, 255);
//     analogWrite(RPWM, 0);
//     analogWrite(LPWM1, 0);
//     analogWrite(RPWM1, 255);
// }

// void search_and_moving()
// {
//     if (distance1 == 999 && distance2 == 999 && distance3 == 999)
//     {
//         if (checking_yprevious == 0)
//             ROTATER();
//         else if (checking_yprevious == 1)
//             ROTATER();
//         else if (checking_yprevious == 2)
//             ROTATEL();
//     }
//     bubbleSort(a, sizeof(a) / sizeof(a[0]));
//     if (a[0] == distance1) // thang truoc mat;
//     {
//         if (checking_yprevious == 1)
//         {
//             RFORWARD();
//             delay(200);
//             checking_yprevious = 0;
//         }
//         else if (checking_yprevious == 2)

//         {
//             LFORWARD();
//             delay(200);
//             checking_yprevious = 0;
//         }
//         PUSH();
//         // STOP();
//     }
//     else if (a[0] == distance2) // ben trai
//     {
//         RFORWARD();
//         checking_yprevious = 1;
//     }
//     else if (a[0] == distance3) // ben phai
//     {
//         LFORWARD();
//         checking_yprevious = 2;
//     }
// }
// void proval()
// {
//     valIRR = digitalRead(IRR);
//     valIRL = digitalRead(IRL);
//     valIRB = digitalRead(IRB);

//     if (valIRR == 0)
//     {
//         Serial.println("Lui trai");
//         RBACKWARD();
//     }
//     else if (valIRL == 0)
//     {
//         Serial.println("Lui phai");
//         LBACKWARD();
//     }
//     else if (valIRL == 0 && valIRR == 0)
//     {
//         Serial.println("Thoathiem");
//         BACKWARD();
//     }
//     else if (valIRB == 0)
//     {
//         Serial.println("Tien");
//         PUSH();
//     }
//     // delay(1000);
// }
// void setup()
// {
//     // while (1);
//     Serial.begin(9600);
//     // DC
//     pinMode(RPWM, OUTPUT);
//     pinMode(LPWM, OUTPUT);
//     pinMode(RPWM1, OUTPUT);
//     pinMode(LPWM1, OUTPUT);
//     // IR
//     pinMode(IRR, INPUT);
//     pinMode(IRL, INPUT);
//     pinMode(IRB, INPUT);
//     // SR
//     pinMode(trig1, OUTPUT); // Phat
//     pinMode(trig2, OUTPUT);
//     pinMode(trig3, OUTPUT);

//     pinMode(echo1, INPUT); // Nhan
//     pinMode(echo2, INPUT);
//     pinMode(echo3, INPUT);
//     // nut bam
//     pinMode(button_K6, INPUT_PULLUP);
//     pinMode(button_K7, INPUT_PULLUP);
//     pinMode(button_K8, INPUT_PULLUP);
//     pinMode(button_K5, INPUT_PULLUP);
//     pinMode(button_K4, INPUT_PULLUP);
//     pinMode(button_K3, INPUT_PULLUP);
//     pinMode(button_K2, INPUT_PULLUP);
//     pinMode(button_K1, INPUT_PULLUP);
//     // ngat
//     attachInterrupt(0, proval, RISING);
//     attachInterrupt(1, proval, RISING);
//     attachInterrupt(2, proval, RISING);
// }
// int readbutton()
// {
//     val_K6 = digitalRead(button_K6);
//     delay(10);
//     val_K7 = digitalRead(button_K7);
//     delay(10);
//     val_K8 = digitalRead(button_K8);
//     delay(10);
//     val_K5 = digitalRead(button_K5);
//     delay(10);
//     val_K4 = digitalRead(button_K4);
//     delay(10);
//     val_K1 = digitalRead(button_K1);
//     delay(10);
//     val_K2 = digitalRead(button_K2);
//     delay(10);
//     val_K3 = digitalRead(button_K3);
//     delay(10);
//     if (val_K1 + val_K2 + val_K3 + val_K4 + val_K5 + val_K6 + val_K7 + val_K8 != 8)
//         pressbutton = true;
// }
// void loop()
// {
//     proval();
//     search_and_moving();
// }