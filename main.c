// SPDX-License-Identifier: Unlicense
#include "stm32l011xx.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void)
{
	msTicks++;
}

void delay_ms(uint32_t ms)
{
	uint32_t now = msTicks;
	while ((msTicks - now) < ms);
}

#define LD3_PORT  GPIOB
#define LD3_PIN   (3)
#define LD3_BIT   (1 << LD3_PIN)
#define LD3_ON()  LD3_PORT->ODR |= (LD3_BIT)
#define LD3_OFF() LD3_PORT->ODR &= ~(LD3_BIT)

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	RCC->IOPENR |= RCC_IOPENR_IOPBEN;
	// Output - MODE3[1:0] = 0b01
	LD3_PORT->MODER &= ~(3 << (LD3_PIN * 2));
	LD3_PORT->MODER |=  (1 << (LD3_PIN * 2));

	for (;;) {
		delay_ms(100);
		LD3_ON();
		delay_ms(100);
		LD3_OFF();
	}
}
