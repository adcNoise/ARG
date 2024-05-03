#ifndef PERIPHERY_H
#define PERIPHERY_H

#include "stm32g0xx_hal.h"
#include "max31865.h"

typedef enum {
	READY	= 0,			// Статус-пин замкнут, система готова
	ALARM					// Статус-пин разомкнут, система не готова, требуется аппаратный сброс 
} ALARM_PIN_STATUS;

typedef enum {
	SYNC_AC_NO = 0,			// Пин синхронизации синуса по переменке не установлен
	SYNC_AC_YES				// Пин синхронизации синуса по переменке    установлен
} AC_SYNC_STATUS;

typedef enum {
	MANUAL_STOP	= 0,		// Пин ручного пуска разомкнут
	MANUAL_START			// Пин ручного пуска замкнут
} MANUAL_PIN_STATUS;

typedef enum {
	PHOTO_NO_SENSOR = 0,	// Нет 	датчика
	PHOTO_FIRE,				// Есть огонь
	PHOTO_NO_FIRE			// Нет 	огня
} PHOTO_STATUS;

typedef enum {
	OIL_LEVEL_UP = 0,		// Датчик вверху
	OIL_LEVEL_DOWN,			// Датчик внизу
} OIL_LEVEL_STATUS;

typedef enum {				// Перемычки установки целевой температуры масла в бачке. Измеряется 1 раз при старте..
	OIL_TEMP_NONE = 0,		// Все разомкнуты
	OIL_TEMP_A,				// A
	OIL_TEMP_B,				// B
	OIL_TEMP_AB,			// AB
	OIL_TEMP_C,				// C
	OIL_TEMP_AC,			// AC
	OIL_TEMP_BC,			// BC
	OIL_TEMP_ABC,			// ABC
} OIL_TEMP_JUMPERS;

typedef struct{
	AC_SYNC_STATUS 		AC_Sync;				// Состояние синхронизации по переменке
	uint16_t			AC_Back_Timer;			// Врямя, когда синхронизация будет считаться сброшенной.
	uint16_t			AC_freq;
}AC_t;

typedef struct{
	AC_t				AC;						// Состояние синхронизации по переменке
	float				TemperatureOil;			// Температура 	масла
	float				TemperatureCoolant;		// Температура 	теплоносителя
	OIL_TEMP_JUMPERS	OilTempJumpers;			// Джамперы задающие температуру масла
	PHOTO_STATUS		Photosensor;			// Состояние 	фотодатчика
	ALARM_PIN_STATUS	AlarmPin;				// Состояние пина аварии
	MANUAL_PIN_STATUS	ManualPin;				// Состояние пина ручного запуска
	OIL_LEVEL_STATUS	OilLevelPin;			// Состояние пина бачка с маслом
}Periph_t;

extern Periph_t 	Per;
extern Max31865_t  	pt100_a;
extern Max31865_t  	pt100_b;

void AC_Timer(void);
void ReadOilTempJumpers(void);
void ReadAlarmPin(void);
void ReadOilLevelPin(void);
void ReadManualStartPin(void);		// Чтение пина ручного запуска
void ReadPhotoSensor(void);			// Состояние фотодатчика
void InitTemperatureSensors(void);	// Инициализация 	датчиков температуры
void ReadTemperatureSensors(void);	// Чтение 			датчиков темпреатуры

#endif