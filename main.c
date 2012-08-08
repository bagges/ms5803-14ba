/* 
 * File:   main.c
 * Author: Markus Backes
 *
 * Created on 8. August 2012
 * 
 * this programm only tests the library for correct algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include "ms5803-14ba.h"

int main(int argc, char** argv) {
    CalibrationData CB_DATA = {46546,42845,29751,29457,32745,29059}; //static values from data sheet
    MeasurementData MM_DATA = {4311550,8387300}; //static values from data sheet
    CalculatedValues values;
    
    calculateTemperature(CB_DATA, MM_DATA, &values);
    calculateTemperatureCompensatedPressure(CB_DATA, MM_DATA, &values);
    doSecondOrderTemperatureCompensation(&values);
    
    printf("dT %i\n", values.dT);
    printf("TEMP %i\n", values.TEMP);
    printf("OFF %" PRId64 "\n", values.OFF);
    printf("SENS %" PRId64 "\n", values.SENS);
    printf("P %i\n", values.P);
    
    if(values.dT == 4580 && values.TEMP == 2015 && values.OFF == 2808943914ULL && values.SENS == 1525751591ULL && values.P == 10005) {
        printf("Calculated values are correct.\n");
    } else {
        printf("Check algorithm. Values are incorrect.\n");
    }
    return (EXIT_SUCCESS);
}

