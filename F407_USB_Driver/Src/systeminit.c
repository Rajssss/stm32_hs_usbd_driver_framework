/*
 * systeminit.c
 *
 *  Created on: 06-Feb-2021
 *      Author: Rajssss@Github.com
 */


#include <stdint.h>
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"
#include "logger.h"

LogLevel system_log_level = LOG_LEVEL_DEBUG;
uint32_t SystemCoreClock = 72000000;	//72MHz

//Prototypes
void clock_config(void);
void clock_config_mco(void);

void SystemInit(void)
{
//	clock_config_mco();
	clock_config();
}

void clock_config(void)
{
	/*
	 * HCLK = 72MHz
	 * PLL: M = 4, N = 72, P = 2, Q = 3
	 * AHB Prescalar = 1
	 * APB Prescalar1 = 2, Prescalar2 = 1
	 * MCO1 Prescalar = 2
	 */

	//Setup Flash Latency
	MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY,
			//FLASH_ACR_LATENCY_2WS << FLASH_ACR_LATENCY_Pos
			//or
			_VAL2FLD(FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2WS));

	//Enable HSE
	SET_BIT(RCC->CR, RCC_CR_HSEON);

	//Wait till HSE gets stable
	while(!READ_BIT(RCC->CR, RCC_CR_HSERDY));

	//Configure PLL
	MODIFY_REG(RCC->PLLCFGR,
			RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLSRC,
			_VAL2FLD(RCC_PLLCFGR_PLLM, 4) | _VAL2FLD(RCC_PLLCFGR_PLLN, 72) | _VAL2FLD(RCC_PLLCFGR_PLLQ, 3) |
			RCC_PLLCFGR_PLLSRC_HSE);

	//enable PLL
	SET_BIT(RCC->CR, RCC_CR_PLLON);

	//Wait for PLL to get stable
	while(!READ_BIT(RCC->CR, RCC_CR_PLLRDY));

	//Set PLL as SYSCLK
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, _VAL2FLD(RCC_CFGR_SW, RCC_CFGR_SW_PLL));

	//Configure AHB and APB Prescalars
	//APB2 and AHB Prescalar values are already 1 by def
	MODIFY_REG(RCC->CFGR,  RCC_CFGR_PPRE1, _VAL2FLD(RCC_CFGR_PPRE1, 4));

	//wait till PLL is selected
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	//disable HSI
	CLEAR_BIT(RCC->CR, RCC_CR_HSION);
}

void clock_config_mco(void)
{
	//NOTE: Configuration must be done before clocks are enabled

	//set MCO Source as PLLCLK and MCO1PRE = 2
	MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO1 | RCC_CFGR_MCO1PRE, _VAL2FLD(RCC_CFGR_MCO1, 3) | _VAL2FLD(RCC_CFGR_MCO1PRE, 4));

	//configure PA8 as MCO1
	//enable clock for GPIOA
	SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);

	//PA8 as Medium speed
	MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR8, _VAL2FLD(GPIO_OSPEEDR_OSPEED8, 1));

	//PA8 as Alternate mode
	MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER8, _VAL2FLD(GPIO_MODER_MODER8, 2));
}
