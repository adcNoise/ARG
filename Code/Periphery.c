#include "Periphery.h"
#include "adc.h"

Periph_t 	Per;			// Периферия

Max31865_t  pt100_a;	
Max31865_t  pt100_b;
	
//------------------------------------------------------------------------------
// Функция чтения джамперов температуры подогрева масла
//------------------------------------------------------------------------------
inline void AC_Timer(void){
	if(Per.AC.AC_Back_Timer)			// Таймер автосброса
	{
		Per.AC.AC_Back_Timer--;
	}	
	if(Per.AC.AC_Back_Timer==0)			// Если таймер дотикал до нуля то синхронизации с АС сетью нет
	{
		Per.AC.AC_Sync = SYNC_AC_NO;
	}
	Per.AC.AC_freq = 0;
}

//------------------------------------------------------------------------------
// Функция чтения джамперов температуры подогрева масла
//------------------------------------------------------------------------------
inline void ReadOilTempJumpers(void){
	Per.OilTempJumpers = 	(HAL_GPIO_ReadPin(JA_GPIO_Port, JA_Pin) 	)|
							(HAL_GPIO_ReadPin(JB_GPIO_Port, JB_Pin)<<1 	)|
							(HAL_GPIO_ReadPin(JC_GPIO_Port, JC_Pin)<<2	);
}

//------------------------------------------------------------------------------
// Функция работы с пином уровня масла в бачке подогрева
//------------------------------------------------------------------------------
inline void ReadOilLevelPin(void){
	if(HAL_GPIO_ReadPin(OIL_LEVEL_IN_MCU_GPIO_Port, OIL_LEVEL_IN_MCU_Pin))
		Per.OilLevelPin = OIL_LEVEL_DOWN;
	else
		Per.OilLevelPin = OIL_LEVEL_UP;
}

//------------------------------------------------------------------------------
// Функция работы с пином аппаратной аварии
//------------------------------------------------------------------------------
inline void ReadAlarmPin(void){
	if(HAL_GPIO_ReadPin(NALARM_GPIO_Port, NALARM_Pin))
		Per.AlarmPin = READY;
	else
		Per.AlarmPin = ALARM;
}
//------------------------------------------------------------------------------
// Функция работы с дискретным входом ручного запуска
//------------------------------------------------------------------------------
void ReadManualStartPin(void){
	// В идеале сделать многократную проверку в течении нескольких секунд в обе стороны
	if(HAL_GPIO_ReadPin(MANUAL_START_MCU_GPIO_Port,MANUAL_START_MCU_Pin))
		Per.ManualPin = MANUAL_STOP;
	else
		Per.ManualPin = MANUAL_START;
}
//------------------------------------------------------------------------------
// Функции работы с датчиками температуры
//------------------------------------------------------------------------------
inline void InitTemperatureSensors(void){
	Max31865_init(&pt100_a, &hspi1, SPI1_CSA_GPIO_Port, SPI1_CSA_Pin,4,50);
	Max31865_init(&pt100_b, &hspi1, SPI1_CSB_GPIO_Port, SPI1_CSB_Pin,4,50);
}

inline void ReadTemperatureSensors(void){
	static float CoolantTemperature, OilTemperature;

	if(HAL_GPIO_ReadPin(DRDY_A_GPIO_Port, DRDY_A_Pin)){
		Max31865_readTempC(&pt100_a,&CoolantTemperature);

		Per.TemperatureCoolant = Max31865_Filter(CoolantTemperature, 	CoolantTemperature,	0.1);   //  << фактор усреднения
	}

	if(HAL_GPIO_ReadPin(DRDY_B_GPIO_Port,DRDY_B_Pin)){
		Max31865_readTempC(&pt100_b,&OilTemperature);

		Per.TemperatureOil = Max31865_Filter(OilTemperature, 			Per.TemperatureOil,	0.1);   //  << фактор усреднения
	}
}

//------------------------------------------------------------------------------
// CalcPhotoSensorState
//------------------------------------------------------------------------------

inline void ReadPhotoSensor(){
	uint16_t PhotoSensorADC;
	HAL_ADC_Start(&hadc1);
	
	HAL_ADC_PollForConversion(&hadc1,100); 	//osDelay(5);
	
	PhotoSensorADC = HAL_ADC_GetValue(&hadc1);

	HAL_ADC_Stop(&hadc1);

	//if(OperatingData.PhotoSensorADC==0x0FFF){ // минимальное значение АЦП, при котором будет детекция
	//	OperatingData.PhotoSensor = PHOTO_NO_SENSOR; return;}

//	if(OperatingData.PhotoSensorADC>BurnerParameters.PhotosensorTreshold)
//		OperatingData.PhotoSensor = PHOTO_NO_FIRE; else
//		OperatingData.PhotoSensor = PHOTO_FIRE;

	if(PhotoSensorADC>0xF0)
		Per.Photosensor 	= PHOTO_NO_FIRE; else
		Per.Photosensor  	= PHOTO_FIRE;
}