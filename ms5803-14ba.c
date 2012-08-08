/* 
 * File:   ms5803-14ba.c
 * Author: Markus Backes
 *
 * Created on 8. August 2012
 * 
 */

#include "ms5803-14ba.h"

void calculateTemperature(CalibrationData CB_DATA, MeasurementData MM_DATA, CalculatedValues *values) {
    values->dT = MM_DATA.D2 - CB_DATA.C5 * pow(2, 8);
    values->TEMP = 2000 + ((values->dT * CB_DATA.C6) / pow(2, 23));
}

void doSecondOrderTemperatureCompensation(CalculatedValues *values) {
    int32_t T2;
    int64_t OFF2;
    int64_t SENS2;
    if (values->TEMP < 2000) {
        //LOW TEMP
        T2 = 3 * pow(values->dT, 2) / pow(2, 33);
        OFF2 = 3 * pow((values->TEMP - 2000), 2) / pow(2, 1);
        SENS2 = 5 * pow((values->TEMP - 2000), 2) / pow(2, 3);

        if (values->TEMP < -15000) {
            //VERY LOW TEMP
            OFF2 = OFF2 + (7 * pow((values->TEMP + 1500), 2));
            SENS2 = SENS2 + (4 * pow((values->TEMP + 1500), 2));
        }
    } else {
        //HIGH TEMP
        T2 = 7 * pow(values->dT, 2) / pow(2, 37);
        OFF2 = 1 * pow((values->TEMP - 2000), 2) / pow(2, 4);
        SENS2 = 0;
    }

    values->TEMP = values->TEMP - T2;
    values->OFF = values->OFF - OFF2;
    values->SENS = values->SENS - SENS2;
}

void calculateTemperatureCompensatedPressure(CalibrationData CB_DATA, MeasurementData MM_DATA, CalculatedValues *values) {
    values->OFF = (CB_DATA.C2 * pow(2, 16)) + ((CB_DATA.C4 * values->dT) / pow(2, 7));
    values->SENS = (CB_DATA.C1 * pow(2, 15)) + ((CB_DATA.C3 * values->dT) / pow(2, 8));
    values->P = ((MM_DATA.D1 * values->SENS / pow(2, 21)) - values->OFF) / pow(2, 15);
}
