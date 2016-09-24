/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
 * File Name          : stm32f10x_vector.c
 * Author             : MCD Tools Team
 * Date First Issued  : 05/14/2007
 * Description        : This file contains the vector table for STM32F10x.
 *                      After Reset the Cortex-M3 processor is in Thread mode,
 *					   priority is Privileged, and the Stack is set to Main.
 ********************************************************************************
 * History:
 * 05/14/2007: V0.2
 *
 ********************************************************************************
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

/* Includes ----------------------------------------------------------------------*/

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void DebugMon_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void __attribute__((weak)) WWDG_IRQHandler(void);
void __attribute__((weak)) PVD_IRQHandler(void);
void __attribute__((weak)) TAMPER_IRQHandler(void);
void __attribute__((weak)) RTC_IRQHandler(void);
void __attribute__((weak)) FLASH_IRQHandler(void);
void __attribute__((weak)) RCC_IRQHandler(void);
void __attribute__((weak)) EXTI0_IRQHandler(void);
void __attribute__((weak)) EXTI1_IRQHandler(void);
void __attribute__((weak)) EXTI2_IRQHandler(void);
void __attribute__((weak)) EXTI3_IRQHandler(void);
void __attribute__((weak)) EXTI4_IRQHandler(void);
void __attribute__((weak)) DMA_Channel1_IRQHandler(void);
void __attribute__((weak)) DMA_Channel2_IRQHandler(void);
void __attribute__((weak)) DMA_Channel3_IRQHandler(void);
void __attribute__((weak)) DMA_Channel4_IRQHandler(void);
void __attribute__((weak)) DMA_Channel5_IRQHandler(void);
void __attribute__((weak)) DMA_Channel6_IRQHandler(void);
void __attribute__((weak)) DMA_Channel7_IRQHandler(void);
void __attribute__((weak)) ADC1_2_IRQHandler(void);
void __attribute__((weak)) USB_HP_CAN_TX_IRQHandler(void);
void __attribute__((weak)) USB_LP_CAN_RX0_IRQHandler(void);
void __attribute__((weak)) CAN_RX1_IRQHandler(void);
void __attribute__((weak)) CAN_SCE_IRQHandler(void);
void __attribute__((weak)) EXTI9_5_IRQHandler(void);
void __attribute__((weak)) TIM1_BRK_IRQHandler(void);
void __attribute__((weak)) TIM1_UP_IRQHandler(void);
void __attribute__((weak)) TIM1_TRG_COM_IRQHandler(void);
void __attribute__((weak)) TIM1_CC_IRQHandler(void);
void __attribute__((weak)) TIM2_IRQHandler(void);
void __attribute__((weak)) TIM3_IRQHandler(void);
void __attribute__((weak)) TIM4_IRQHandler(void);
void __attribute__((weak)) I2C1_EV_IRQHandler(void);
void __attribute__((weak)) I2C1_ER_IRQHandler(void);
void __attribute__((weak)) I2C2_EV_IRQHandler(void);
void __attribute__((weak)) I2C2_ER_IRQHandler(void);
void __attribute__((weak)) SPI1_IRQHandler(void);
void __attribute__((weak)) SPI2_IRQHandler(void);
void __attribute__((weak)) USART1_IRQHandler(void);
void __attribute__((weak)) USART2_IRQHandler(void);
void __attribute__((weak)) USART3_IRQHandler(void);
void __attribute__((weak)) EXTI15_10_IRQHandler(void);
void __attribute__((weak)) RTCAlarm_IRQHandler(void);
void __attribute__((weak)) USBWakeUp_IRQHandler(void);


/* Exported types --------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern unsigned long _etext;
extern unsigned long _sidata;		/* start address for the initialization values of the .data section. defined in linker script */
extern unsigned long _sdata;		/* start address for the .data section. defined in linker script */
extern unsigned long _edata;		/* end address for the .data section. defined in linker script */

extern unsigned long _sbss;			/* start address for the .bss section. defined in linker script */
extern unsigned long _ebss;			/* end address for the .bss section. defined in linker script */

extern void _estack(void);		/* init value for the stack pointer. defined in linker script */



/* Private typedef -----------------------------------------------------------*/
/* function prototypes ------------------------------------------------------*/
void Reset_Handler(void);
extern int main(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vTimer2IntHandler( void );
extern void vPortSVCHandler( void );
extern void SystemInit(void);

/******************************************************************************
 *
 * The minimal vector table for a Cortex-M3.  Note that the proper constructs
 * must be placed on this to ensure that it ends up at physical address
 * 0x0000.0000.
 *
 ******************************************************************************/
__attribute__ ((section(".isr_vector"),used))
void (* const g_pfnVectors[])(void) =
{
	&_estack,            // The initial stack pointer
	Reset_Handler,             // The reset handler
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	(void*)0, (void*)0, (void*)0, (void*)0,            /* Reserved */
	SVC_Handler,
	DebugMon_Handler,
	(void*)0,                      /* Reserved */
	PendSV_Handler,
	SysTick_Handler,
	WWDG_IRQHandler,
	PVD_IRQHandler,
	TAMPER_IRQHandler,
	RTC_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_IRQHandler,
	EXTI1_IRQHandler,
	EXTI2_IRQHandler,
	EXTI3_IRQHandler,
	EXTI4_IRQHandler,
	DMA_Channel1_IRQHandler,
	DMA_Channel2_IRQHandler,
	DMA_Channel3_IRQHandler,
	DMA_Channel4_IRQHandler,
	DMA_Channel5_IRQHandler,
	DMA_Channel6_IRQHandler,
	DMA_Channel7_IRQHandler,
	ADC1_2_IRQHandler,
	USB_HP_CAN_TX_IRQHandler,
	USB_LP_CAN_RX0_IRQHandler,
	CAN_RX1_IRQHandler,
	CAN_SCE_IRQHandler,
	EXTI9_5_IRQHandler,
	TIM1_BRK_IRQHandler,
	TIM1_UP_IRQHandler,
	TIM1_TRG_COM_IRQHandler,
	TIM1_CC_IRQHandler,
	TIM2_IRQHandler,
	TIM3_IRQHandler,
	TIM4_IRQHandler,
	I2C1_EV_IRQHandler,
	I2C1_ER_IRQHandler,
	I2C2_EV_IRQHandler,
	I2C2_ER_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
	USART1_IRQHandler,
	USART2_IRQHandler,
	USART3_IRQHandler,
	EXTI15_10_IRQHandler,
	RTCAlarm_IRQHandler,
	USBWakeUp_IRQHandler,
	(void*)0,
	(void*)0,
	(void*)0,
	(void*)0,
	(void*)0,
	(void*)0,
	(void*)0,
	(void*)0xF108F85F //this is a workaround for boot in RAM mode.
};

/*******************************************************************************
 * Function Name  : Reset_Handler
 * Description    : This is the code that gets called when the processor first starts execution
 *		       following a reset event.  Only the absolutely necessary set is performed,
 *		       after which the application supplied main() routine is called.
 * Input          :
 * Output         :
 * Return         :
 *******************************************************************************/
void __attribute__ ((section(".after_vectors"))) Reset_Handler(void)
{
	unsigned long *pulSrc, *pulDest;

	//
	// Copy the data segment initializers from flash to SRAM.
	//
	pulSrc = &_sidata;
	for (pulDest = &_sdata; pulDest < &_edata; ) {
		*(pulDest++) = *(pulSrc++);
	}

	//
	// Zero fill the bss segment.
	//
	for (pulDest = &_sbss; pulDest < &_ebss; ) {
		*(pulDest++) = 0;
	}
	//
	// System Initialization
	//
	SystemInit();

	//
	// Call the application's entry point.
	//
	main();

	for (;;)
		;

}




/********************* (C) COPYRIGHT 2007 STMicroelectronics  *****END OF FILE****/


