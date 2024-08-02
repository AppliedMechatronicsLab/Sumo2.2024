#include <Arduino.h>

#include <Ver2_IRSensor.h>
#include <Ver2_KeyBoard.h>
#include <Ver2_Motor.h>
#include <Ver2_SRSensor.h>
int buttonSate = 0;
boolean firstRun = true; // Tao co chay dau tien

boolean Run_Default = true;

void Ver2_SearchDefault()
{
    Ver2_SRSensor_FilterValue(filteredF, filteredL, filteredR);
    if (Run_Default)
    {
        if (filteredR <= 40)
        {
            // Điều khiển động cơ cho trường hợp cảm biến phải <= 40
            Ver2_Motor_PWM(180, 70);
            delay(333);
        }
        else if (filteredR <= 40)
        {
            // Điều khiển động cơ cho trường hợp cảm biến trái <= 40
            Ver2_Motor_PWM(70, 180);
            delay(333);
        }
        else if (filteredF <= 45)
        {
            // Điều khiển động cơ cho trường hợp cảm biến trước <= 45
            Ver2_Motor_PWM(255, 255);
        }

        Run_Default = false; // Tắt chế độ mặc định sau khi thực hiện xong
    }
    else
    {
        // Chế độ không phải mặc định
        if (filteredF <= 45) // Push
        {
            Ver2_Motor_PWM(255, 255);
        }
        else if (filteredR <= 40)
        {
            Ver2_Motor_PWM(255, 255);
        }
        else if (filteredL <= 40)
        {
            Serial.println("pushL");
            Ver2_Motor_PWM(-175, 175);
        }
        else if (filteredF <= 20 && filteredR <= 20)
        {
            Serial.println("chay ne diem mu phai");
            Ver2_Motor_PWM(230, 255);
        }
        else if (filteredF <= 20 && filteredL <= 20)
        {
            Serial.println("chay ne diem mu trai");
            Ver2_Motor_PWM(255, 230);
        }
        else
        {
            Ver2_Motor_PWM(230, 255);
        }
    }
}
boolean Run_AttackR = true;
void Ver2_SearchAttackR() // Attack Right
{
    Ver2_SRSensor_FilterValue(filteredF, filteredL, filteredR);
    if (Run_AttackR)
    {
        Ver2_Motor_PWM(255, 255);
        delay(1500);
    }
    else
    {
        // Chay mu
        if (filteredF <= 60)
        {
            Ver2_Motor_PWM(255, 255);
        }
        else
        {
            if (filteredR <= 45)
            {
                Ver2_Motor_PWM(-175, 175);
            }
            else if (filteredL <= 45)
            {
                Ver2_Motor_PWM(175, -175);
            }
            else if (filteredF <= 20 && filteredR <= 20)
            {
                Ver2_Motor_PWM(-255, 230);
            }
            else if (filteredF <= 20 && filteredL <= 20)
            {
                Ver2_Motor_PWM(230, -255);
            }
        }
    }
}
boolean Run_AttackL = true;
void Ver2_SearchAttackL()
{
    Ver2_SRSensor_FilterValue(filteredF, filteredL, filteredR);
    switch (Run_AttackL)
    {
    case true:
        Ver2_Motor_PWM(225, 225);
        delay(2000);
        Run_AttackL = false;
        break;
    case false:
        if (filteredF <= 45)
        {
            Ver2_Motor_PWM(255, 255);
        }
        else
        {

            if (filteredR <= 45)
            {
                Ver2_Motor_PWM(-175, 175);
            }
            else if (filteredL <= 45)
            {
                Ver2_Motor_PWM(175, -175);
            }
            else if (filteredF <= 20 && filteredR <= 20)
            {
                Ver2_Motor_PWM(-255, 230);
            }
            else if (filteredF <= 20 && filteredL <= 20)
            {
                Ver2_Motor_PWM(230, -255);
            }
        }
    }
}
boolean Run_Defence = true;
void Ver2_SearchDefence()
{
    Ver2_SRSensor_FilterValue(filteredF, filteredL, filteredR);
    switch (filteredR <= 30)
    {
    case true:
        Serial.println("ne");
        Ver2_Motor_PWM(230, 255); // Ne muc tieu
        break;

    case false:
        switch (filteredL <= 30)
        {
        case true:
            Ver2_Motor_PWM(-230, -255);
            break;

        case false:
            switch (filteredF <= 60)
            {
            case true:
                Ver2_Motor_PWM(255, 255);
                break;

            case false:
                Ver2_Motor_PWM(-255, 255);
                break;
            }
            break;
        }
        break;
    }
}
void setup()
{
    Ver2_Motor_PWM(0, 0);
    Ver2_IRSensor_Setup();
    Ver2_KeyBoard_Setup();
    Ver2_Motor_setupBTS();
    Ver2_SRSensor_Setup();
}
void loop()
{
    readSensors();
    Ver2_SRSensor_FilterValue(filteredF, filteredL, filteredR);
    Ver2_KeyBoard_Control();
    if (firstRun)
    {
        delay(2900);
        firstRun = false;
    }

    switch (buttonSate)
    {
    case 6: // Chạy mù tấn công phải
        Ver2_SearchAttackR();
        Serial.println("tan cong phai");
        break;

    case 7: // Chạy cơ bản < rcm >
        Ver2_SearchDefault();
        Serial.println("chay mac dich");
        break;

    case 8: // Chạy né đối thủ
        Ver2_SearchDefence();
        break;

    case 4: // Chạy mù tấn công trái
        break;
    }
}
