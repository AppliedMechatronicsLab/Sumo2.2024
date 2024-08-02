#include <Ver2_KeyBoard.h>
int buttonState = 0;
const byte buttonPins[] = {A0, A1, A2, A3, A4, A6, A7};            // Tao mang chua cac chan ket noi nut
const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]); // xac dinh so luong nut

void Ver2_KeyBoard_Setup()
{
    for (int i = 0; i < numButtons; i++) // Setup trang thai pinMode
    {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

void Ver2_KeyBoard_Control()
{
    for (int i = 0; i < numButtons; i++)
    {
        if (digitalRead(buttonPins[i]) == LOW)
        {
            buttonState = i + 2; // Nút bắt đầu từ K2
            break;               // Thoát vòng lặp khi tìm thấy nút được nhấn
        }
    }
}
