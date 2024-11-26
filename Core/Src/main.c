/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "led_7seg.h"
#include "button.h"
#include "lcd.h"
#include "picture.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void system_init();
void test_LedDebug();
void test_LedY0();
void test_LedY1();
void test_7seg();
void test_button();
void test_lcd();

//--- LAB 3 ---
void DrawTrafficLed(uint8_t mode);
void showTime(uint16_t time);
void toogleLed(uint16_t modeStatus);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
  MX_TIM2_Init();
  MX_SPI1_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */
  system_init();
  lcd_Clear(WHITE);
  test_lcd();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
#define NORMALMODE 1
#define REDMODE 2
#define GREENMODE 3
#define YELLOWMODE 4

	// Variable for LCD
	uint16_t x1 = 30;
	uint16_t x2 = 30;
	uint16_t x3 = 30;
	uint16_t y1 = 20;

	uint16_t xTraffic2 = 20;
	uint16_t yTraffic2_1 = 40;
	uint16_t yTraffic2_2 = 70;
	uint16_t yTraffic2_3 = 90;

	uint16_t xMode = 60;
	uint16_t yMode = 120;

	// Variable for control
	uint8_t modeStatus = 1;
	uint16_t redTime = 5;
	uint16_t redTimeNew = redTime;
	uint16_t greenTime = 3;
	uint16_t greenTimeNew = greenTime;
	uint16_t yellowTime = 2;
	uint16_t yellowTimeNew = yellowTime;
	uint8_t toggle = 1;


	lcd_Clear(WHITE);
	DrawTrafficLed(modeStatus);
  while (1)
  {
	  while(!flag_timer2);
	  flag_timer2 = 0;
	  button_Scan();
	  test_button();

	  if(modeStatus == 1){
		  if(button_count[1] == 1){
			  modeStatus = 2;
			  setLedModifytimer(500);
			  lcd_Clear(WHITE);
			  DrawTrafficLed(modeStatus);
			  showTime(redTime);
			  redTimeNew = redTime;
		  }
		  // Thuc hien chay normal mode

	  }
	  if(modeStatus == 2){
		  if(button_count[1] == 1){
			  modeStatus = 3;
			  setLedModifytimer(500);
			  lcd_Clear(WHITE);
			  DrawTrafficLed(modeStatus);
			  showTime(greenTime);
			  greenTimeNew = greenTime;
		  }
		  if(button_count[2] == 1){
			  redTimeNew = redTimeNew + 1;
			  if(redTimeNew >= 100){
				  redTimeNew = 0;
			  }
		  }
		  if(button_count[3] == 1){
			  redTime = redTimeNew;
		  }
		  if(isFlagModifyTimer() == 1){
			  showTime(redTimeNew);
			  toggle = 1- toggle;
			  toogleLed(modeStatus,toggle);
		  }
	  }
	  if(modeStatus == 3){
		  if(button_count[1] == 1){
			  modeStatus = 4;
			  setLedModifytimer(500);
			  lcd_Clear(WHITE);
			  DrawTrafficLed(modeStatus);
			  showTime(yellowTime);
			  yellowTimeNew = yellowTime;
		  }
		  if(button_count[2] == 1){
			  greenTimeNew = greenTimeNew + 1;
			  if(greenTimeNew >= 100){
				  greenTimeNew = 0;
			  }
		  }
		  if(button_count[3] == 1){
			  greenTime = greenTimeNew;
		  }
		  if(isFlagModifyTimer() == 1){
			  showTime(greenTimeNew);
			  toggle = 1- toggle;
			  toogleLed(modeStatus,toggle);
		  }
	  }
	  if(modeStatus == 2){
		  if(button_count[1] == 1){
			  modeStatus = 1;
			  setLedModifytimer(0);
			  lcd_Clear(WHITE);
			  DrawTrafficLed(modeStatus);
		  }
		  if(button_count[2] == 1){
			  yellowTimeNew = yellowTimeNew + 1;
			  if(yellowTimeNew >= 100){
				  yellowTimeNew = 0;
			  }
		  }
		  if(button_count[3] == 1){
			  yellowTime = yellowTimeNew;
		  }
		  if(isFlagModifyTimer() == 1){
			  showTime(yellowTimeNew);
			  toggle = 1- toggle;
			  toogleLed(modeStatus,toggle);
		  }
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void system_init(){
	  HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 0);
	  HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, 0);
	  HAL_GPIO_WritePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin, 0);
	  timer_init();
	  led7_init();
	  button_init();
	  lcd_init();
	  setTimer2(50);
}

uint8_t count_led_debug = 0;
uint8_t count_led_Y0 = 0;
uint8_t count_led_Y1 = 0;

void test_LedDebug(){
	count_led_debug = (count_led_debug + 1)%20;
	if(count_led_debug == 0){
		HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
	}
}

void test_LedY0(){
	count_led_Y0 = (count_led_Y0+ 1)%100;
	if(count_led_Y0 > 40){
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 1);
	} else {
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 0);
	}
}

void test_LedY1(){
	count_led_Y1 = (count_led_Y1+ 1)%40;
	if(count_led_Y1 > 10){
		HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, 0);
	} else {
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y1_Pin, 1);
	}
}

void test_7seg(){
	led7_SetDigit(0, 0, 0);
	led7_SetDigit(5, 1, 0);
	led7_SetDigit(4, 2, 0);
	led7_SetDigit(7, 3, 0);
}
void test_button(){
	for(int i = 0; i < 16; i++){
		if(button_count[i] == 1){
			lcd_ShowIntNum(140, 105, i, 2, BRED, WHITE, 32);
		}
	}
}
void test_lcd(){
	lcd_Fill(0, 0, 240, 20, BLUE);
	lcd_StrCenter(0, 2, "Hello World !!!", RED, BLUE, 16, 1);
	lcd_ShowStr(20, 30, "Test lcd screen", WHITE, RED, 24, 0);
	lcd_DrawCircle(60, 120, GREEN, 40, 1);
	lcd_DrawCircle(160, 120, BRED, 40, 0);
	lcd_ShowPicture(80, 200, 90, 90, gImage_logo);
}


// ------ LAB 3 ------
void DrawTrafficLed(uint8_t mode)
{
	// Xmax = 240
	// Ymax = ??
	// Traffic led 1
	lcd_DrawCircle(x1, y1, GREEN, 10, 0);
	lcd_DrawCircle(x2, y1, YELLOW, 10, 0);
	lcd_DrawCircle(x3, y1, RED, 10, 0);

	// Traffic led 2
	lcd_DrawCircle(xTraffic2, yTraffic2_1, GREEN, 10, 0);
	lcd_DrawCircle(xTraffic2, yTraffic2_2, YELLOW, 10, 0);
	lcd_DrawCircle(xTraffic2, yTraffic2_3, RED, 10, 0);

	// Hien thi che do
	lcd_ShowStr(xMode, yMode, "Mode: ", BLACK, WHITE, 24, 0);
	lcd_ShowIntNum(xMode + 50, yMode, mode, 1, BLACK, WHITE, 24);
}

void showTime(uint16_t time)
{
	lcd_ShowStr(xMode, yMode + 20, "Time: ", BLACK, WHITE, 24, 0);
	lcd_ShowIntNum(xMode, yMode + 40, time, 2, BLACK, WHITE, 24);
}

void toogleLed(uint16_t modeStatus, uint8_t toggle)

{
	if(modeStatus == 3)
	{
		lcd_DrawCircle(xTraffic2, yTraffic2_1, GREEN, 10, toggle);
		lcd_DrawCircle(xTraffic2, yTraffic2_2, YELLOW, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_3, RED, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_1, GREEN, 10, toggle);
		lcd_DrawCircle(xTraffic2, yTraffic2_2, YELLOW, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_3, RED, 10, 0);
	}
	else if(modeStatus == 2)
	{
		lcd_DrawCircle(xTraffic2, yTraffic2_1, GREEN, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_2, YELLOW, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_3, RED, 10, toggle);
		lcd_DrawCircle(xTraffic2, yTraffic2_1, GREEN, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_2, YELLOW, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_3, RED, 10, toggle);
	}else if(modeStatus == 4)
	{
		lcd_DrawCircle(xTraffic2, yTraffic2_1, GREEN, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_2, YELLOW, 10, toggle);
		lcd_DrawCircle(xTraffic2, yTraffic2_3, RED, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_1, GREEN, 10, 0);
		lcd_DrawCircle(xTraffic2, yTraffic2_2, YELLOW, 10, toggle);
		lcd_DrawCircle(xTraffic2, yTraffic2_3, RED, 10, 0);
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
