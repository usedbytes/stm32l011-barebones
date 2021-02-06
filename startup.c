// SPDX-License-Identifier: Unlicense
// Derived from https://github.com/vsergeev/cmsis-templates/blob/lpc13xx/startup.c
// "100% public domain"
#include <stdint.h>

/* Addresses pulled in from the linker script */
extern uint32_t _end_stack;
extern uint32_t _start_data_flash;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

/* Application main() called in reset handler */
extern int main(void);

#define WEAK_ALIAS(x) __attribute__ ((weak, alias(#x)))

/* Cortex M0+ core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void) WEAK_ALIAS(Dummy_Handler);
void HardFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SVC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PendSV_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SysTick_Handler(void) WEAK_ALIAS(Dummy_Handler);

/* STM32L011 specific interrupt handlers */
void WWDG_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void PVD_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void RTC_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void FLASH_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void RCC_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void EXTI0_1_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void EXTI2_3_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void EXTI4_15_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void DMA1_Channel1_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void DMA1_Channel2_3_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void DMA1_Channel4_5_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void ADC1_COMP_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void LPTIM1_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void TIM2_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void TIM21_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void I2C1_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void SPI1_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void USART2_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);
void LPUART1_IRQHandler(void) WEAK_ALIAS(Dummy_Handler);

void Dummy_Handler(void);

/* Stack top and vector handler table */
void *vector_table[] __attribute__ ((section(".vectors"))) = {
	&_end_stack,
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	SVC_Handler,
	0,
	0,
	PendSV_Handler,
	SysTick_Handler,
	WWDG_IRQHandler,
	PVD_IRQHandler,
	RTC_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_1_IRQHandler,
	EXTI2_3_IRQHandler,
	EXTI4_15_IRQHandler,
	0,
	DMA1_Channel1_IRQHandler,
	DMA1_Channel2_3_IRQHandler,
	DMA1_Channel4_5_IRQHandler,
	ADC1_COMP_IRQHandler,
	LPTIM1_IRQHandler,
	0,
	TIM2_IRQHandler,
	0,
	0,
	0,
	0,
	TIM21_IRQHandler,
	0,
	0,
	I2C1_IRQHandler,
	0,
	SPI1_IRQHandler,
	0,
	0,
	USART2_IRQHandler,
	LPUART1_IRQHandler,
	0,
	0,
};

void Reset_Handler(void)
{
	uint8_t *src, *dst;

	/* Copy with byte pointers to obviate unaligned access problems */

	/* Copy data section from Flash to RAM */
	src = (uint8_t *)&_start_data_flash;
	dst = (uint8_t *)&_start_data;
	while (dst < (uint8_t *)&_end_data)
		*dst++ = *src++;

	/* Clear the bss section */
	dst = (uint8_t *)&_start_bss;
	while (dst < (uint8_t *)&_end_bss)
		*dst++ = 0;

	main();
}

void Dummy_Handler(void)
{
	while (1);
}
