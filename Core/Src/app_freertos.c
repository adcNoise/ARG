/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SSD1306.h"
#include "Periphery.h"
#include "LED.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId LCDTaskHandle;
osThreadId OilHeatTaskHandle;
osThreadId ProcessTaskHandle;
osThreadId SensorsTaskHandle;
osThreadId ModbusTaskHandle;
osThreadId LEDTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLCDTask(void const * argument);
void StartOilHeatTask(void const * argument);
void StartProcessTask(void const * argument);
void StartSensorsTask(void const * argument);
void StartModbusTask(void const * argument);
void StartTaskLED(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of LCDTask */
  osThreadDef(LCDTask, StartLCDTask, osPriorityNormal, 0, 128);
  LCDTaskHandle = osThreadCreate(osThread(LCDTask), NULL);

  /* definition and creation of OilHeatTask */
  osThreadDef(OilHeatTask, StartOilHeatTask, osPriorityNormal, 0, 128);
  OilHeatTaskHandle = osThreadCreate(osThread(OilHeatTask), NULL);

  /* definition and creation of ProcessTask */
  osThreadDef(ProcessTask, StartProcessTask, osPriorityNormal, 0, 128);
  ProcessTaskHandle = osThreadCreate(osThread(ProcessTask), NULL);

  /* definition and creation of SensorsTask */
  osThreadDef(SensorsTask, StartSensorsTask, osPriorityNormal, 0, 128);
  SensorsTaskHandle = osThreadCreate(osThread(SensorsTask), NULL);

  /* definition and creation of ModbusTask */
  osThreadDef(ModbusTask, StartModbusTask, osPriorityNormal, 0, 128);
  ModbusTaskHandle = osThreadCreate(osThread(ModbusTask), NULL);

  /* definition and creation of LEDTask */
  osThreadDef(LEDTask, StartTaskLED, osPriorityLow, 0, 128);
  LEDTaskHandle = osThreadCreate(osThread(LEDTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartLCDTask */
/**
  * @brief  Function implementing the LCDTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartLCDTask */
void StartLCDTask(void const * argument)
{
  /* USER CODE BEGIN StartLCDTask */
	ssd1306_Init();
	osDelay(100);
	ssd1306_UpdateScreen();
	osDelay(10);
	ssd1306_UpdateScreen();
	uint8_t i=0;
  /* Infinite loop */
  for(;;)
  {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(i, i); i++;
	ssd1306_WriteString("3453453", Font_7x10, White);
	ssd1306_UpdateScreen();
	osDelay(1);
	if(i>55) i=0;
}
  /* USER CODE END StartLCDTask */
}

/* USER CODE BEGIN Header_StartOilHeatTask */
/**
* @brief Function implementing the OilHeatTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOilHeatTask */
void StartOilHeatTask(void const * argument)
{
  /* USER CODE BEGIN StartOilHeatTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END StartOilHeatTask */
}

/* USER CODE BEGIN Header_StartProcessTask */
/**
* @brief Function implementing the ProcessTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartProcessTask */
void StartProcessTask(void const * argument)
{
  /* USER CODE BEGIN StartProcessTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartProcessTask */
}

/* USER CODE BEGIN Header_StartSensorsTask */
/**
* @brief Function implementing the SensorsTask thread.
* @param argument: Not used
* @retval None
*/

//float	temperature_oil;
//float	temperature_water;
/* USER CODE END Header_StartSensorsTask */
void StartSensorsTask(void const * argument)
{
  /* USER CODE BEGIN StartSensorsTask */
	InitTemperatureSensors();
	ReadOilTempJumpers();
	/* Infinite loop */
	for(;;)
	{
		AC_Timer();
		ReadAlarmPin();
		ReadOilLevelPin();
		ReadPhotoSensor();
		ReadTemperatureSensors();
		ReadManualStartPin();
		osDelay(100);
	}
  /* USER CODE END StartSensorsTask */
}

/* USER CODE BEGIN Header_StartModbusTask */
/**
* @brief Function implementing the ModbusTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartModbusTask */
void StartModbusTask(void const * argument)
{
  /* USER CODE BEGIN StartModbusTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END StartModbusTask */
}

/* USER CODE BEGIN Header_StartTaskLED */
/**
* @brief Function implementing the LEDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskLED */
void StartTaskLED(void const * argument)
{
  /* USER CODE BEGIN StartTaskLED */
  HAL_GPIO_TogglePin(LED_ERROR_GPIO_Port,LED_ERROR_Pin);
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(LED_MODE_GPIO_Port,LED_MODE_Pin);
	HAL_GPIO_TogglePin(LED_ERROR_GPIO_Port,LED_ERROR_Pin);
	LED_Indicator();
    osDelay(100);
  }
  /* USER CODE END StartTaskLED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

