/*
 * u8g_arm.h
 *
 *  Created on: Mar 5, 2020
 *      Author: yelin
 */

#ifndef _U8G_ARM_H
#define _U8G_ARM_H

#include <u8g.h>
#include "stm32f4xx_hal.h"


#define SPI_HANDLER hspi1 // use your SPI handler
extern SPI_HandleTypeDef SPI_HANDLER;
#define RST GPIO_PIN_5
#define DC GPIO_PIN_6
#define CS GPIO_PIN_7
#define PORT GPIOB
uint8_t u8g_com_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);

#endif /* INC_U8G_ARM_H_ */
