/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f3xx_hal.h"

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
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define center_Pin GPIO_PIN_0
#define center_GPIO_Port GPIOA
#define right_Pin GPIO_PIN_1
#define right_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define left_Pin GPIO_PIN_3
#define left_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_4
#define LCD_RS_GPIO_Port GPIOA
#define LCD__CS_Pin GPIO_PIN_6
#define LCD__CS_GPIO_Port GPIOA
#define SWICH1_Pin GPIO_PIN_0
#define SWICH1_GPIO_Port GPIOB
#define BAT_Pin GPIO_PIN_1
#define BAT_GPIO_Port GPIOB
#define R_motor_Pin GPIO_PIN_8
#define R_motor_GPIO_Port GPIOA
#define L_motor_Pin GPIO_PIN_9
#define L_motor_GPIO_Port GPIOA
#define R_CW_CCW_Pin GPIO_PIN_10
#define R_CW_CCW_GPIO_Port GPIOA
#define L_CW_CCW_Pin GPIO_PIN_11
#define L_CW_CCW_GPIO_Port GPIOA
#define SWICH0_Pin GPIO_PIN_12
#define SWICH0_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define senLED_center_Pin GPIO_PIN_4
#define senLED_center_GPIO_Port GPIOB
#define senLED_side_Pin GPIO_PIN_5
#define senLED_side_GPIO_Port GPIOB
#define motor_enable_Pin GPIO_PIN_6
#define motor_enable_GPIO_Port GPIOB
#define motor_reset_Pin GPIO_PIN_7
#define motor_reset_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
