/*
 * usbd_driver.h
 *
 *  Created on: 25-Mar-2021
 *      Author: Raj.S
 */

#ifndef USBD_INC_USBD_DRIVER_H_
#define USBD_INC_USBD_DRIVER_H_

#include <stdint.h>
#include "stm32f4xx.h"

#define 	USB_OTG_HS_GLOBAL 		(USB_OTG_GlobalTypeDef *) (USB_OTG_HS_PERIPH_BASE + USB_OTG_GLOBAL_BASE)
#define 	USB_OTG_HS_DEVICE		(USB_OTG_DeviceTypeDef *) (USB_OTG_HS_PERIPH_BASE + USB_OTG_DEVICE_BASE)
#define 	USB_OTG_HS_PCGCCTL		(uint32_t *) (USB_OTG_HS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE)

//Prototypes
void usb_gpio_init(void);


#endif /* USBD_INC_USBD_DRIVER_H_ */
