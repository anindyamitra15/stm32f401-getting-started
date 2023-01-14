/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LUT_LEN 500
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
DMA_HandleTypeDef hdma_tim2_ch1;

/* USER CODE BEGIN PV */
uint32_t pwmLUT[LUT_LEN] = { 0, 50, 101, 151, 201, 251, 302, 352, 402, 452,
		502, 552, 603, 653, 703, 753, 803, 853, 903, 953, 1003, 1053, 1102,
		1152, 1202, 1251, 1301, 1351, 1400, 1450, 1499, 1548, 1598, 1647, 1696,
		1745, 1794, 1843, 1892, 1941, 1990, 2038, 2087, 2135, 2184, 2232, 2280,
		2328, 2376, 2424, 2472, 2520, 2568, 2615, 2663, 2710, 2757, 2804, 2851,
		2898, 2945, 2992, 3038, 3085, 3131, 3177, 3223, 3269, 3315, 3361, 3406,
		3452, 3497, 3542, 3587, 3632, 3677, 3721, 3766, 3810, 3854, 3898, 3942,
		3985, 4029, 4072, 4116, 4159, 4201, 4244, 4287, 4329, 4371, 4413, 4455,
		4497, 4538, 4579, 4621, 4662, 4702, 4743, 4783, 4823, 4863, 4903, 4943,
		4982, 5022, 5061, 5099, 5138, 5176, 5215, 5253, 5290, 5328, 5365, 5403,
		5440, 5476, 5513, 5549, 5585, 5621, 5657, 5692, 5727, 5762, 5797, 5832,
		5866, 5900, 5934, 5968, 6001, 6034, 6067, 6100, 6132, 6164, 6196, 6228,
		6259, 6290, 6321, 6352, 6382, 6413, 6442, 6472, 6502, 6531, 6560, 6588,
		6617, 6645, 6673, 6700, 6728, 6755, 6781, 6808, 6834, 6860, 6886, 6911,
		6937, 6961, 6986, 7010, 7035, 7058, 7082, 7105, 7128, 7151, 7173, 7195,
		7217, 7239, 7260, 7281, 7302, 7322, 7342, 7362, 7381, 7401, 7420, 7438,
		7457, 7475, 7492, 7510, 7527, 7544, 7561, 7577, 7593, 7608, 7624, 7639,
		7654, 7668, 7682, 7696, 7710, 7723, 7736, 7749, 7761, 7773, 7785, 7796,
		7807, 7818, 7829, 7839, 7849, 7858, 7868, 7877, 7885, 7893, 7902, 7909,
		7917, 7924, 7930, 7937, 7943, 7949, 7954, 7960, 7964, 7969, 7973, 7977,
		7981, 7984, 7987, 7990, 7992, 7994, 7996, 7997, 7999, 7999, 8000, 8000,
		8000, 7999, 7999, 7997, 7996, 7994, 7992, 7990, 7987, 7984, 7981, 7977,
		7973, 7969, 7964, 7960, 7954, 7949, 7943, 7937, 7930, 7924, 7917, 7909,
		7902, 7893, 7885, 7877, 7868, 7858, 7849, 7839, 7829, 7818, 7807, 7796,
		7785, 7773, 7761, 7749, 7736, 7723, 7710, 7696, 7682, 7668, 7654, 7639,
		7624, 7608, 7593, 7577, 7561, 7544, 7527, 7510, 7492, 7475, 7457, 7438,
		7420, 7401, 7381, 7362, 7342, 7322, 7302, 7281, 7260, 7239, 7217, 7195,
		7173, 7151, 7128, 7105, 7082, 7058, 7035, 7010, 6986, 6961, 6937, 6911,
		6886, 6860, 6834, 6808, 6781, 6755, 6728, 6700, 6673, 6645, 6617, 6588,
		6560, 6531, 6502, 6472, 6442, 6413, 6382, 6352, 6321, 6290, 6259, 6228,
		6196, 6164, 6132, 6100, 6067, 6034, 6001, 5968, 5934, 5900, 5866, 5832,
		5797, 5762, 5727, 5692, 5657, 5621, 5585, 5549, 5513, 5476, 5440, 5403,
		5365, 5328, 5290, 5253, 5215, 5176, 5138, 5099, 5061, 5022, 4982, 4943,
		4903, 4863, 4823, 4783, 4743, 4702, 4662, 4621, 4579, 4538, 4497, 4455,
		4413, 4371, 4329, 4287, 4244, 4201, 4159, 4116, 4072, 4029, 3985, 3942,
		3898, 3854, 3810, 3766, 3721, 3677, 3632, 3587, 3542, 3497, 3452, 3406,
		3361, 3315, 3269, 3223, 3177, 3131, 3085, 3038, 2992, 2945, 2898, 2851,
		2804, 2757, 2710, 2663, 2615, 2568, 2520, 2472, 2424, 2376, 2328, 2280,
		2232, 2184, 2135, 2087, 2038, 1990, 1941, 1892, 1843, 1794, 1745, 1696,
		1647, 1598, 1548, 1499, 1450, 1400, 1351, 1301, 1251, 1202, 1152, 1102,
		1053, 1003, 953, 903, 853, 803, 753, 703, 653, 603, 552, 502, 452, 402,
		352, 302, 251, 201, 151, 101, 50 };
//uint32_t pwmLUT[60] = { 500, 500, 1000, 1000, 2000, 2000, 3000, 3000, 4000,
//		4000, 5000, 5000, 6000, 6000, 7000, 7000, 8000, 8000, 9000, 9000, 10000,
//		10000, 10000, 10000, 9000, 9000, 9000, 8000, 8000, 8000, 7000, 7000,
//		7000, 6000, 6000, 6000, 5000, 5000, 5000, 4000, 4000, 4000, 3000, 3000,
//		3000, 2000, 2000, 2000, 1000, 1000, 1000, 500, 500, 500 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, pwmLUT, LUT_LEN);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 15 - 1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 10000 - 1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */
	HAL_TIM_MspPostInit(&htim2);

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
