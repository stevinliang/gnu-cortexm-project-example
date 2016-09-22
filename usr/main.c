/*********************************************************************************************************
*
* File                : main.c
* Hardware Environment:
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  :
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void GPIO_Configuration(void);
void  Delay (uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	/* Add your application code here
	*/
	uint8_t Key;

	GPIO_Configuration();
	Key = 5;
	/* Infinite loop */
	while (1) {
		if(!(GPIOC->IDR & 0x0001))
			Key=0;
		else if(!(GPIOC->IDR & 0x0002))
			Key=2;
		else if(!(GPIOC->IDR & 0x0008))
			Key=3;
		else if(!(GPIOC->IDR & 0x0004))
			Key=4;
		else if(!(GPIOA->IDR & 0x0002))
			Key=5;
		else if(!(GPIOA->IDR & 0x0001))
			Key=1;

		switch (Key) {
		case 0:
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			GPIO_SetBits(GPIOB , GPIO_Pin_13);
			GPIO_SetBits(GPIOB , GPIO_Pin_14);
			GPIO_SetBits(GPIOB , GPIO_Pin_15);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			GPIO_ResetBits(GPIOB , GPIO_Pin_13);
			GPIO_ResetBits(GPIOB , GPIO_Pin_14);
			GPIO_ResetBits(GPIOB , GPIO_Pin_15);
			Delay(0xfffff);
			break;
		case 1:
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);
			Delay(0xfffff);
			break;
		case 2:
			GPIO_SetBits(GPIOB , GPIO_Pin_13);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_13);
			Delay(0xfffff);
			break;
		case 3:
			GPIO_SetBits(GPIOB , GPIO_Pin_14);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_14);
			Delay(0xfffff);
			break;
		case 4:
			GPIO_SetBits(GPIOB , GPIO_Pin_15);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_15);
			Delay(0xfffff);
			break;
		case 5:
			GPIO_SetBits(GPIOB , GPIO_Pin_12);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_12);

			GPIO_SetBits(GPIOB , GPIO_Pin_13);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_13);

			GPIO_SetBits(GPIOB , GPIO_Pin_14);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_14);

			GPIO_SetBits(GPIOB , GPIO_Pin_15);
			Delay(0xfffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_15);
			break;
		}
	}
}

/*******************************************************************************
 * Function Name  : GPIO_Configuration
 * Description    : Configure GPIO Pin
 * Input          : None
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA , ENABLE);
	/**
	 *  LED1 -> PB15 , LED2 -> PB14 , LED3 -> PB13 , LED4 -> PB12
	 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Key */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
 * Function Name  : Delay
 * Description    : Delay Time
 * Input          : - nCount: Delay Time
 * Output         : None
 * Return         : None
 * Attention		 : None
 *******************************************************************************/
void  Delay (uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}


#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/*************************************** END OF FILE *************************************/
