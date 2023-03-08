/*
 * ws2812b_SPI_DMA.h
 *
 *  Created on: Mar 6, 2023
 *      Author: Santiago Cian
 */

#ifndef INC_WS2812B_SPI_DMA_H_
#define INC_WS2812B_SPI_DMA_H_

#include "stm32f1xx_hal.h"

#define N_pixel 60

#define size_vector_pixel N_pixel*9 + 100

void ws2812b_init(SPI_HandleTypeDef *hspi);
void ws2812b_set_ledRGB(uint16_t N_led, uint8_t value_R, uint8_t value_G, uint8_t value_B);
void ws2812b_set_multi_ledRGB(uint16_t initial_led, uint8_t *p_values_R, uint8_t *p_values_G, uint8_t *p_values_B, uint16_t size_vector);
void ws2812b_set_ledHSV(uint16_t N_led, double value_H, double value_S, double value_V);
void ws2812b_set_multi_ledHSV(uint16_t initial_led, double *p_values_H, double *p_values_S, double *p_values_V, uint16_t size_vector);

#endif /* INC_WS2812B_SPI_DMA_H_ */

