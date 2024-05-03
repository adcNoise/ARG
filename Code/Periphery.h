#ifndef PERIPHERY_H
#define PERIPHERY_H

#include "stm32g0xx_hal.h"
#include "max31865.h"

typedef enum {
	READY	= 0,			// ������-��� �������, ������� ������
	ALARM					// ������-��� ���������, ������� �� ������, ��������� ���������� ����� 
} ALARM_PIN_STATUS;

typedef enum {
	SYNC_AC_NO = 0,			// ��� ������������� ������ �� ��������� �� ����������
	SYNC_AC_YES				// ��� ������������� ������ �� ���������    ����������
} AC_SYNC_STATUS;

typedef enum {
	MANUAL_STOP	= 0,		// ��� ������� ����� ���������
	MANUAL_START			// ��� ������� ����� �������
} MANUAL_PIN_STATUS;

typedef enum {
	PHOTO_NO_SENSOR = 0,	// ��� 	�������
	PHOTO_FIRE,				// ���� �����
	PHOTO_NO_FIRE			// ��� 	����
} PHOTO_STATUS;

typedef enum {
	OIL_LEVEL_UP = 0,		// ������ ������
	OIL_LEVEL_DOWN,			// ������ �����
} OIL_LEVEL_STATUS;

typedef enum {				// ��������� ��������� ������� ����������� ����� � �����. ���������� 1 ��� ��� ������..
	OIL_TEMP_NONE = 0,		// ��� ����������
	OIL_TEMP_A,				// A
	OIL_TEMP_B,				// B
	OIL_TEMP_AB,			// AB
	OIL_TEMP_C,				// C
	OIL_TEMP_AC,			// AC
	OIL_TEMP_BC,			// BC
	OIL_TEMP_ABC,			// ABC
} OIL_TEMP_JUMPERS;

typedef struct{
	AC_SYNC_STATUS 		AC_Sync;				// ��������� ������������� �� ���������
	uint16_t			AC_Back_Timer;			// �����, ����� ������������� ����� ��������� ����������.
	uint16_t			AC_freq;
}AC_t;

typedef struct{
	AC_t				AC;						// ��������� ������������� �� ���������
	float				TemperatureOil;			// ����������� 	�����
	float				TemperatureCoolant;		// ����������� 	�������������
	OIL_TEMP_JUMPERS	OilTempJumpers;			// �������� �������� ����������� �����
	PHOTO_STATUS		Photosensor;			// ��������� 	�����������
	ALARM_PIN_STATUS	AlarmPin;				// ��������� ���� ������
	MANUAL_PIN_STATUS	ManualPin;				// ��������� ���� ������� �������
	OIL_LEVEL_STATUS	OilLevelPin;			// ��������� ���� ����� � ������
}Periph_t;

extern Periph_t 	Per;
extern Max31865_t  	pt100_a;
extern Max31865_t  	pt100_b;

void AC_Timer(void);
void ReadOilTempJumpers(void);
void ReadAlarmPin(void);
void ReadOilLevelPin(void);
void ReadManualStartPin(void);		// ������ ���� ������� �������
void ReadPhotoSensor(void);			// ��������� �����������
void InitTemperatureSensors(void);	// ������������� 	�������� �����������
void ReadTemperatureSensors(void);	// ������ 			�������� �����������

#endif