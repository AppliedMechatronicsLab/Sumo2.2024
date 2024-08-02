#ifndef Ver2_SRSensor_h
#define Ver2_SRSensor_h

#include <Arduino.h>
void readSensors();
void Ver2_SRSensor_Setup();
void Ver2_SRSensor_FilterValue(int &filteredF, int &filteredL, int &filteredR);
extern int filteredF, filteredL, filteredR;
#endif
