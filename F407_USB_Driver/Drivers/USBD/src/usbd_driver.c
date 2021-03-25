/*
 * usbd_driver.c
 *
 *  Created on: 25-Mar-2021
 *      Author: Raj.S
 */

#include "usbd_driver.h"

void usb_gpio_init(void)
{
	//Enable GPIOB Clock
	SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);

	//Set PB14(D-) & PB15(D+) as alternate function
	MODIFY_REG(GPIOB->AFR[1], GPIO_AFRH_AFSEL14 | GPIO_AFRH_AFSEL15, _VAL2FLD(GPIO_AFRH_AFSEL14, 0xC) |
			_VAL2FLD(GPIO_AFRH_AFSEL15, 0xC));

	MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE14 | GPIO_MODER_MODE15, _VAL2FLD(GPIO_MODER_MODE14, 2) |
			_VAL2FLD(GPIO_MODER_MODE15, 2));
}
