/*
thu vien cho Motor*/
#include <Ver2_Motor.h>
#define RPWM1 7 // Trai
#define LPWM1 6 // Trai
#define RPWM 8  // Phai
#define LPWM 9  // Ohai
void Ver2_Motor_PWM(int PWM_L, int PWM_R)
{
    if (PWM_L > 0) // DC L tien
    {
        analogWrite(LPWM1, PWM_L);
        analogWrite(RPWM1, 0);
    }
    else if (PWM_L < 0) // DC L lui
    {
        analogWrite(LPWM1, 0);
        analogWrite(RPWM1, abs(PWM_L));
    }
    else if (PWM_L == 0) // DC Dung yen
    {
        analogWrite(LPWM1, 0);
        analogWrite(RPWM1, 0);
    }

    if (PWM_R > 0) // R tiến
    {
        analogWrite(LPWM, PWM_R);
        analogWrite(RPWM, 0);
    }
    else if (PWM_R < 0) // R lùi
    {
        analogWrite(LPWM, 0);
        analogWrite(RPWM, abs(PWM_R));
    }
    else if (PWM_R == 0) // R đứng yên
    {
        analogWrite(LPWM, 0);
        analogWrite(RPWM, 0);
    }
}

void Ver2_Motor_setupBTS()
{
    pinMode(LPWM1, OUTPUT);
    pinMode(RPWM1, OUTPUT);
    pinMode(LPWM, OUTPUT);
    pinMode(RPWM, OUTPUT);
}