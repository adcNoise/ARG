/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DRDY_B_Pin GPIO_PIN_11
#define DRDY_B_GPIO_Port GPIOC
#define SPI1_CSB_Pin GPIO_PIN_12
#define SPI1_CSB_GPIO_Port GPIOC
#define ALARM_OUT_Pin GPIO_PIN_13
#define ALARM_OUT_GPIO_Port GPIOC
#define DRDY_A_Pin GPIO_PIN_0
#define DRDY_A_GPIO_Port GPIOC
#define PHOTO_Pin GPIO_PIN_0
#define PHOTO_GPIO_Port GPIOA
#define SPI1_CSA_Pin GPIO_PIN_3
#define SPI1_CSA_GPIO_Port GPIOA
#define DE1_NSS_Pin GPIO_PIN_0
#define DE1_NSS_GPIO_Port GPIOB
#define LED_ERROR_Pin GPIO_PIN_11
#define LED_ERROR_GPIO_Port GPIOB
#define LED_MODE_Pin GPIO_PIN_12
#define LED_MODE_GPIO_Port GPIOB
#define AC_OK_Pin GPIO_PIN_13
#define AC_OK_GPIO_Port GPIOB
#define AC_OK_EXTI_IRQn EXTI4_15_IRQn
#define JD_Pin GPIO_PIN_1
#define JD_GPIO_Port GPIOD
#define JC_Pin GPIO_PIN_2
#define JC_GPIO_Port GPIOD
#define JB_Pin GPIO_PIN_3
#define JB_GPIO_Port GPIOD
#define JA_Pin GPIO_PIN_4
#define JA_GPIO_Port GPIOD
#define CL1C_Pin GPIO_PIN_5
#define CL1C_GPIO_Port GPIOD
#define AIR_MCU_Pin GPIO_PIN_6
#define AIR_MCU_GPIO_Port GPIOD
#define OIL_LEVEL_IN_MCU_Pin GPIO_PIN_3
#define OIL_LEVEL_IN_MCU_GPIO_Port GPIOB
#define IGNITION_Pin GPIO_PIN_4
#define IGNITION_GPIO_Port GPIOB
#define MANUAL_START_MCU_Pin GPIO_PIN_5
#define MANUAL_START_MCU_GPIO_Port GPIOB
#define CL2C_Pin GPIO_PIN_6
#define CL2C_GPIO_Port GPIOB
#define CL3C_Pin GPIO_PIN_7
#define CL3C_GPIO_Port GPIOB
#define PUMPC_Pin GPIO_PIN_8
#define PUMPC_GPIO_Port GPIOB
#define OILC_Pin GPIO_PIN_9
#define OILC_GPIO_Port GPIOB
#define NALARM_Pin GPIO_PIN_10
#define NALARM_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
