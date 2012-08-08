#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

uint16_t C1 = 46546;
uint16_t C2 = 42845;
uint16_t C3 = 29751;
uint16_t C4 = 29457;
uint16_t C5 = 32745;
uint16_t C6 = 29059;

uint32_t D1 = 4311550; //DIGITAL PRESSURE
uint32_t D2 = 8387300; //DIGITAL TEMPERATUR

int32_t dT = 0;
int32_t TEMP = 0;
int64_t OFF = 0;
int64_t SENS = 0;
int32_t P = 0;

void calculateTemperature(void);
void doSecondOrderTemperatureCompensation(void);
void calculateTemperatureCompensatedPressure(void);

int main(void)
{
	calculateTemperature();
	doSecondOrderTemperatureCompensation();
	calculateTemperatureCompensatedPressure();
	printf("dT %i\n", dT);
	printf("TEMP %i\n", TEMP);
	printf("OFF %" PRId64 "\n", OFF);
	printf("SENS %" PRId64 "\n", SENS);
	printf("P %i\n", P);
	return 0;
}

void calculateTemperature(void)
{
	dT = D2 - C5 * pow(2,8);
	TEMP = 2000 + ((dT * C6) / pow(2,23));
}

void doSecondOrderTemperatureCompensation(void)
{
	int32_t T2;
	int64_t OFF2;
	int64_t SENS2;
	if(TEMP<2000)
	{
		//LOW TEMP
		T2 = 3 * pow(dT,2) / pow(2,33);
		OFF2 = 3 * pow((TEMP - 2000),2) / pow(2,1);
		SENS2 = 5 * pow((TEMP - 2000),2) / pow(2,3);

		if(TEMP < -15000)
		{
			//VERY LOW TEMP
			OFF2 = OFF2 + (7 * pow((TEMP + 1500),2));
			SENS2 = SENS2 + (4 * pow((TEMP + 1500),2));
		}
	}
	else
	{
		//HIGH TEMP
		T2 = 7 * pow(dT, 2) / pow(2,37);
		OFF2 = 1 * pow((TEMP - 2000),2) / pow(2,4);
		SENS2 = 0;
	}

	TEMP = TEMP - T2;
	OFF = OFF - OFF2;
	SENS = SENS - SENS2;
}

void calculateTemperatureCompensatedPressure(void)
{
	OFF = (C2 * pow(2,16)) + ((C4 * dT) / pow(2,7));
	SENS = (C1 * pow(2,15)) + ((C3 * dT) / pow(2,8));
	P = ((D1 * SENS / pow(2,21)) - OFF) / pow(2,15);
}
