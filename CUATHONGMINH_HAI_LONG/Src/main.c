/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rc522.h"
#include "lcd_i2c.h"
#include "keypad_4x4.h"
#include "stdio.h"
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
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
char Name[4][20]={"PNSINH","NQNGHIA","NTHIEU"};
char key_val,buffer[20];
char MATKHAU[4] = {'1', '1', '1', '1'}; // Cài d?t m?t kh?u tùy ý
char NHAPNHATKHAU[4] = {' ', ' ', ' ', ' '};
int i,count=0,TT=0,canhbaokey=0,canhbaobz=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t		str[MFRC522_MAX_LEN];	

void BUZZER(int dl)		// BUZZER CHUYEN CHE DO
{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_SET);	
		HAL_Delay(dl);	
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_RESET);
}
 void chongdoi_bt()
 {
	if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) == 0)
	{
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) == 0)
		{
				TT ++;
				if (TT == 4) TT = 0;
//				HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//				HAL_Delay(1000);
				while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) == 0);		
		}
	}
 }
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
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	MFRC522_Init();
	keypad_init();
  lcd_init ();
	lcd_clear_display ();
	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
	lcd_goto_XY (1, 0);
  lcd_send_string(" __SMART DOOR__ ");
  lcd_goto_XY(2,0);
	lcd_send_string("  __HAI LONG__  ");
	HAL_Delay(2000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	
	chongdoi_bt();
	key_val = keypad_get_key_value();
		
	if( TT == 0)
	{
	lcd_goto_XY (1, 0);
  lcd_send_string("MODE:_PRESS BT_ ");
	lcd_goto_XY (2, 0);	
	lcd_send_string("                ");
	}
	
	if( TT == 1 )
	{

	lcd_goto_XY (1, 5);
  lcd_send_string("__KEYPAD__");
	lcd_goto_XY (2, 0);
	lcd_send_string("PW: ");		
	if (key_val != 0X20 ) // NHAP MAT KHAU
  {
//				lcd_goto_XY (2, 0);
//				sprintf(buffer,"so:%c",key_val);
//				lcd_send_string(buffer);
    if (i == 0)
		{
				NHAPNHATKHAU[0] = key_val;
				lcd_goto_XY (2, 4);
				lcd_send_data(NHAPNHATKHAU[0]);
				HAL_Delay(500);
				lcd_goto_XY (2, 4);
				lcd_send_string("*");
    }
    if (i == 1) 
		{
      NHAPNHATKHAU[1] = key_val;
			lcd_goto_XY (2, 5);
			lcd_send_data(NHAPNHATKHAU[1]);
			HAL_Delay(500);
			lcd_goto_XY (2, 5);
			lcd_send_string("*");
			
    }
    if (i == 2)
		{
      NHAPNHATKHAU[2] = key_val;
			lcd_goto_XY (2, 6);
			lcd_send_data(NHAPNHATKHAU[2]);
			HAL_Delay(500);
			lcd_goto_XY (2, 6);
			lcd_send_string("*");
			
    }
    if (i == 3) 
		{
      NHAPNHATKHAU[3] = key_val;
			lcd_goto_XY (2, 7);
			lcd_send_data(NHAPNHATKHAU[3]);
			HAL_Delay(500);
			lcd_goto_XY (2, 7);
			lcd_send_string("*");
      count = 1;
    }
    i = i + 1;
	}
	
	if (count == 1) 
	{
    if (NHAPNHATKHAU[0] == MATKHAU[0] && NHAPNHATKHAU[1] == MATKHAU[1] && NHAPNHATKHAU[2] == MATKHAU[2] && NHAPNHATKHAU[3] == MATKHAU[3]) 
		{
			
			lcd_goto_XY(2,10);
      lcd_send_string("OK   ");
      HAL_Delay(2000);
			lcd_goto_XY(2,10);
      lcd_send_string("OPEN ");
			
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET); 
			HAL_Delay(2000);
			lcd_goto_XY(2,4);
			lcd_send_string("            ");
      i = 0;
      count = 0;
    } else {
			canhbaokey++;
			if(canhbaokey == 3)
			{
			BUZZER(3000);
			}
		  lcd_goto_XY(2,10);
      lcd_send_string("ERROR");
      HAL_Delay(2000); 
			lcd_goto_XY(2,10);
			lcd_send_string("RETRY");
			HAL_Delay(2000); 
			lcd_goto_XY(2,4);
			lcd_send_string("            ");
      i = 0;
      count = 0;
    }	
	}
//		switch (key_val) // DONG CUA
//		{
//		case 'D':		
//		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
//		lcd_goto_XY(2,10);
//		lcd_send_string("CLOSE");
//    HAL_Delay(2000);
//		lcd_goto_XY(2,10);
//		lcd_send_string("ENTER");
//		lcd_goto_XY(2,4);
//		lcd_send_string("            ");
//		i = 1;
//		break;
//		}
	}
	if( TT == 2) 
	{
	lcd_goto_XY (1, 5);
  lcd_send_string(" __RFID__ ");	
		if (!MFRC522_Request(PICC_REQIDL, str))
			{
					if (!MFRC522_Anticoll(str)) 
						{
							//SINH				
								if((str[0] == 0XD4) && (str[1] == 0XFA) && (str[2] == 0X34) && (str[3] == 0X2A) && (str[4] == 0X30))
								{
										lcd_goto_XY (2, 0);
										sprintf(buffer,"  %s  ",Name[0]);
										lcd_send_string(buffer);
									
										lcd_goto_XY(2,10);
										lcd_send_string("OPEN ");
										HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
										HAL_Delay(2000);
										lcd_goto_XY(2,0);
										lcd_send_string("                 ");
//										HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//										HAL_Delay(1000);
								} else 
							
								if((str[0] == 0XA9) && (str[1] == 0XA1) && (str[2] == 0XEF) && (str[3] == 0X6E) && (str[4] == 0X89))
								{
										lcd_goto_XY (2, 0);
										sprintf(buffer,"  %s  ",Name[1]);
										lcd_send_string(buffer);
									
										lcd_goto_XY(2,10);
										lcd_send_string("OPEN ");
										HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
										HAL_Delay(2000);
										lcd_goto_XY(2,0);
										lcd_send_string("                 ");
								} else 
								if((str[0] == 0XA0) && (str[1] == 0X22) && (str[2] == 0X95) && (str[3] == 0X32) && (str[4] == 0X25))
								{
										lcd_goto_XY (2, 0);
										sprintf(buffer,"  %s  ",Name[2]);
										lcd_send_string(buffer);
									
										lcd_goto_XY(2,10);
										lcd_send_string("OPEN ");
										HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
										HAL_Delay(2000);
										lcd_goto_XY(2,0);
										lcd_send_string("                 ");
								}
								else 
								{
//										canhbaobz++;
//										if(canhbaobz == 3)
//										{
//										BUZZER(3000);
//										}
										lcd_goto_XY(2,0);
										lcd_send_string("  CARD ERROR  ");
										HAL_Delay(1000);
										lcd_goto_XY(2,0);
										lcd_send_string("                 ");
								}
						}
			}	
	}
	if(TT == 3)
	{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
	lcd_goto_XY (1, 5);
  lcd_send_string(" GOOD BYE!");
	lcd_goto_XY(2,10);
  lcd_send_string("CLOSE");
//	HAL_Delay(2000);	
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Relay_Pin|Bz_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : Relay_Pin Bz_Pin */
  GPIO_InitStruct.Pin = Relay_Pin|Bz_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA8 PA9 PA10 
                           PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
