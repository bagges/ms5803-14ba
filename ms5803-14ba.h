/* 
 * File:   ms5803-14ba.h
 * Author: Markus Backes
 *
 * Created on 8. August 2012
 * 
 * contains functions to calculate pressure and temperature
 */

#ifndef MS5803_14BA_H
#define	MS5803_14BA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <math.h>
#include <inttypes.h>

    struct calibrated {
        uint16_t C1;
        uint16_t C2;
        uint16_t C3;
        uint16_t C4;
        uint16_t C5;
        uint16_t C6;
    };
    
    typedef struct calibrated CalibrationData;

    struct measured {
        uint32_t D1; //DIGITAL PRESSURE
        uint32_t D2; //DIGITAL TEMPERATUR
    };
    
    typedef struct measured MeasurementData;

    struct calculated {
        int32_t dT;
        int32_t TEMP;
        int64_t OFF;
        int64_t SENS;
        int32_t P;
    };
    
    typedef struct calculated CalculatedValues;

    void calculateTemperature(CalibrationData CB_DATA, MeasurementData MM_DATA, CalculatedValues *values);
    void doSecondOrderTemperatureCompensation(CalculatedValues *values);
    void calculateTemperatureCompensatedPressure(CalibrationData CB_DATA, MeasurementData MM_DATA, CalculatedValues *values);



#ifdef	__cplusplus
}
#endif

#endif	/* MS5803_14BA_H */

