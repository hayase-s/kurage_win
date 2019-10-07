/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "move.h"
#include "tim.h"
#include "ad.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update and TIM16 interrupts.
  */
void TIM1_UP_TIM16_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM16_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM16_IRQn 1 */
}

/**
  * @brief This function handles TIM1 capture compare interrupt.
  */
void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */

  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

  /* USER CODE END TIM1_CC_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global and DAC1 underrun error interrupts.
  */
void TIM6_DAC1_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC1_IRQn 0 */

  /* USER CODE END TIM6_DAC1_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC1_IRQn 1 */
  g_timCount++;
  	g_turn.count++;
  	getWallSensorValue();
  	if (g_traAcceleration.Tra == 1) {
  		wallControl();
  		discalPara(&g_targetTrans);
  		if (g_targetTrans.dis < g_traAcceleration.x_acc) {
  			g_targetTrans.vel_r += g_targetTrans.acc * 0.001;
  			g_targetTrans.vel_l += g_targetTrans.acc * 0.001;
  			if (control < 0) { //右に寄ってる時
  				g_targetTrans.wvel_r = g_targetTrans.vel_r + fabsf(control);
  				g_targetTrans.wvel_l = g_targetTrans.vel_l - fabsf(control);
  			} else { //左に寄ってる時
  				g_targetTrans.wvel_r = g_targetTrans.vel_r - fabsf(control);
  				g_targetTrans.wvel_l = g_targetTrans.vel_l + fabsf(control);
  			}
  		} else if (g_targetTrans.dis < (g_traAcceleration.x - g_traAcceleration.x_dec)) {
  			g_targetTrans.vel_r += 0 * 0.001;
  			g_targetTrans.vel_l += 0 * 0.001;
  			if (control < 0) { //右に寄ってる時
  				g_targetTrans.wvel_r = g_targetTrans.vel_r + fabsf(control);
  				g_targetTrans.wvel_l = g_targetTrans.vel_l - fabsf(control);
  			} else { //左に寄ってる時
  				g_targetTrans.wvel_r = g_targetTrans.vel_r - fabsf(control);
  				g_targetTrans.wvel_l = g_targetTrans.vel_l + fabsf(control);
  			}
  		} else {
  			g_targetTrans.vel_r -= g_targetTrans.acc * 0.001;
  			g_targetTrans.vel_l -= g_targetTrans.acc * 0.001;
  			if (control < 0) { //右に寄ってる時
  				g_targetTrans.wvel_r = g_targetTrans.vel_r + fabsf(control);
  				g_targetTrans.wvel_l = g_targetTrans.vel_l - fabsf(control);
  			} else { //左に寄ってる時
  				g_targetTrans.wvel_r = g_targetTrans.vel_r - fabsf(control);
  				g_targetTrans.wvel_l = g_targetTrans.vel_l + fabsf(control);
  			}
  		}

  		uint16_t leftCount, rightCount;

  		if (g_targetTrans.dis < g_traAcceleration.x) {
  			//	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
  			rightCount = rightcalPWMCount(g_targetTrans.wvel_r);
  			__HAL_TIM_SET_AUTORELOAD(&htim1, rightCount);
  			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 50);
  			rightCWCCW(g_targetTrans.wvel_r);
  			//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  			//	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
  			leftCount = leftcalPWMCount(g_targetTrans.wvel_l);
  			__HAL_TIM_SET_AUTORELOAD(&htim2, leftCount);
  			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 50);
  			leftCWCCW(g_targetTrans.wvel_l);
  			//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

  		} else {
  			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
  			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
  		}
  	}

  	if (g_turn.tur == 1) {
  //		g_targetTrans.wvel_r = g_targetTrans.vel_r;
  //		g_targetTrans.wvel_l = g_targetTrans.vel_l;
  		uint16_t leftCount, rightCount;

  		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
  		rightCount = rightcalPWMCount(g_targetTrans.wvel_r);
  		__HAL_TIM_SET_AUTORELOAD(&htim1, rightCount);
  		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 50);
  		rightCWCCW(g_targetTrans.wvel_r);
  		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
  		leftCount = leftcalPWMCount(g_targetTrans.wvel_l);
  		__HAL_TIM_SET_AUTORELOAD(&htim2, leftCount);
  		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 50);
  		leftCWCCW(g_targetTrans.wvel_l);
  		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  	}
  /* USER CODE END TIM6_DAC1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
