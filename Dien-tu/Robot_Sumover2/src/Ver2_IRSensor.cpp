/*
Thu vien cua cam bien hong ngoai TCR5000*/

#include <Ver2_IRSensor.h>
#define IR_R 2
#define IR_L 3
#define IR_B 21

// Co ngat

boolean flagInterrupt0 = false;
boolean flagInterrupt1 = false;
boolean flagInterrupt2 = false;
long timer = 0;

void Ver2_IRSensor_Process()
{
    unsigned time_escape = 700;
    // treo va check cac flag
    while (millis() - timer < time_escape)
    {
        if (flagInterrupt0 || flagInterrupt1 || flagInterrupt2)
        {
        }
        else
        {
            break;
        }
        delay(10);
    }
    flagInterrupt0 = false;
    flagInterrupt1 = false;
    flagInterrupt2 = false;
}
void Interrupt_0() // ngat cam bien IR_R
{
    Ver2_Motor_PWM(-155, -155);

    timer = millis();
    // off cac flag con lai
    flagInterrupt1 = false;
    flagInterrupt2 = false;
}
void Interrupt_1() // ngat cam bien IR_L
{
    Ver2_Motor_PWM(-155, -155);
    timer = millis();
    // off cac flag con lai
    flagInterrupt0 = false;
    flagInterrupt2 = false;
}
void Interrupt_2() // ngat cam bien IR_B
{
    Ver2_Motor_PWM(155, 155);
    // off cac flag con lai
    flagInterrupt1 = false;
    flagInterrupt0 = false;
}
void Ver2_IRSensor_Setup()
{
    attachInterrupt(digitalPinToInterrupt(IR_R), Interrupt_0, RISING);
    attachInterrupt(digitalPinToInterrupt(IR_L), Interrupt_1, RISING);
    attachInterrupt(digitalPinToInterrupt(IR_B), Interrupt_2, RISING);
}