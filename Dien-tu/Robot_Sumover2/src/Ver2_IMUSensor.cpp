// #include <Arduino.h>
// #include <Ver2_IMUSensor.h>
// #define RE_BUF_SIZE 33
// static uint8_t Re_buf[RE_BUF_SIZE];
// unsigned int counter = 0;
// static bool sign = 0;
// unsigned int g[3];

// void Ver2_IMUSensor_Setup()
// {
//     Serial1.begin(115200);
//     Serial.begin(9600);
// }
// void Ver2_IMUSensor_SerialProcess()
// {
//     while (Serial1.available())
//     {

//         Re_buf[counter] = Serial1.read();
//         if (counter == 0 && Re_buf[0] != 0x55 && Re_buf[1] != 0x51)
//             return;
//         counter++;
//         if (position == 33)
//         {
//             counter = 0;
//             sign = 1;
//         }
//     }
// }
// void Ver2_IMUSensor_Read()
// {
//     if (sign)
//     {
//         sign = 0;
//         if (Re_buf[22] == 0x55)
//         {
//             g[0] = (short(Re_buf[25] << 8 | Re_buf[24])) / 32768.0 * 180;
//             g[1] = (short(Re_buf[27] << 8 | Re_buf[26])) / 32768.0 * 180;
//             g[2] = (short(Re_buf[29] << 8 | Re_buf[28])) / 32768.0 * 180;
//             Serial.print(g[2]);
//             Serial.print("Angle Yaw:");
//             Serial.println();
//         }
//     }
// }
