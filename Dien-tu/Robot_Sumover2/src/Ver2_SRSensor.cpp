#include <Ver2_SRSensor.h>

const byte trigPins[] = {4, 12, 10};               // Chân Trigger (phát)
const byte echoPins[] = {5, 13, 11};               // Chân Echo (nhận)
const unsigned long maxDistances[] = {50, 35, 35}; // Khoảng cách tối đa cho từng cảm biến

unsigned long durations[3];           // Mảng lưu thời gian đo được
unsigned long distances[3];           // Mảng lưu khoảng cách tính toán
unsigned long lastDistances[3] = {0}; // Mảng lưu khoảng cách trước đó
int filteredF, filteredL, filteredR;

void Ver2_SRSensor_Setup()
{
    for (int i = 0; i < 3; i++)
    {
        pinMode(trigPins[i], OUTPUT);
        pinMode(echoPins[i], INPUT);
    }
}

void readSensors()
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(trigPins[i], LOW);
        delayMicroseconds(2);

        digitalWrite(trigPins[i], HIGH);
        delayMicroseconds(5);
        digitalWrite(trigPins[i], LOW);

        durations[i] = pulseIn(echoPins[i], HIGH);

        // Tính khoảng cách (cm) và giới hạn bởi maxDistances
        distances[i] = min(durations[i] / 58.82, maxDistances[i]);
    }
}

// Hàm lọc nhiễu
void Ver2_SRSensor_FilterValue(int& filteredF, int& filteredL, int& filteredR)
{
    for (int i = 0; i < 3; i++)
    {
        if (abs(distances[i] - lastDistances[i]) > 5)
        { // Chỉ cập nhật nếu thay đổi lớn hơn 5cm
            lastDistances[i] = distances[i];
        }
        else
        {
            distances[i] = lastDistances[i]; // Giữ nguyên giá trị trước đó
        }
    }
    // Gắn từng giá trị cảm biến cho từng biến
    filteredF = distances[0]; // Cảm biến trước
    filteredL = distances[1]; // Cảm biến trái
    filteredR = distances[2]; // Cảm biến phải
}
