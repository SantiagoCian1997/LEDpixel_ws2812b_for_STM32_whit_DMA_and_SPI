/*
 * ws2812b_SPI_DMA.c
 *
 *  Created on: Mar 6, 2023
 *      Author: Santiago Cian
 *
 * Description:
 * 				Libreria destinada al control de los "LED pixel" basados en el integrado ws2812b, haciendo uso
 * 				del pin MOSI del puerto SPI y del DMA de dicho puerto. De este modo se tiene un refresco continuo
 * 				de los datos enviados a los LEDs directamente desde la memoria SIN HACER USO DEL NUCLEO DEL PROCESADOR
 * 				NI DE INTERRUPCIONES, permitiendo destinar el tiempo de procesamiento del nucleo a diversas tareas.
 */

#include "ws2812b_SPI_DMA.h"

uint8_t vector_ws2812b[size_vector_pixel];

/* Description:
 *				funcion de iniciacion de la libreria, blanquea el vector de datos e inicializa la transmision de SPI mediante el DMA
 * Parameters:
 * 				SPI_HandleTypeDef *hspi: puntero del controlador del puerto SPI
 * Return:
 * 				-
 * Notes:
 *
 */
void ws2812b_init(SPI_HandleTypeDef *hspi){
	for(uint16_t i=0; i<size_vector_pixel; i++) vector_ws2812b[i] = 0b0;

	for(uint16_t led=0; led<N_pixel; led++){
		//G -> 0b00000000
		vector_ws2812b[led*9 + 0] = 0b10010010;
		vector_ws2812b[led*9 + 1] = 0b01001001;
		vector_ws2812b[led*9 + 2] = 0b00100100;
		//R -> 0b00000000
		vector_ws2812b[led*9 + 3] = 0b10010010;
		vector_ws2812b[led*9 + 4] = 0b01001001;
		vector_ws2812b[led*9 + 5] = 0b00100100;
		//B -> 0b00000000
		vector_ws2812b[led*9 + 6] = 0b10010010;
		vector_ws2812b[led*9 + 7] = 0b01001001;
		vector_ws2812b[led*9 + 8] = 0b00100100;
	}

	HAL_SPI_Init(hspi);
	HAL_SPI_Transmit_DMA(hspi, vector_ws2812b, size_vector_pixel);
}

uint16_t offset_led_to_vector=0;
uint8_t aux_logic_or=0;

/* Description:
 *				setea las componentes RGB del led de interes
 * Parameters:
 * 				uint16_t N_led:		indice del led a setear, 	0 <= N_led < N_pixel
 * 				uint8_t value_R:	valor de la componente R, 	0 <= value_R <= 255
 * 				uint8_t value_G:	valor de la componente G, 	0 <= value_G <= 255
 * 				uint8_t value_B:	valor de la componente B, 	0 <= value_B <= 255
 * Return:
 * 				-
 * Notes:
 *
 */
void ws2812b_set_ledRGB(uint16_t N_led, uint8_t value_R, uint8_t value_G, uint8_t value_B){
	if(N_led < N_pixel){
		offset_led_to_vector=N_led*9;
		//G -> 0b00000000
		vector_ws2812b[offset_led_to_vector + 0] = 0b10010010;
		vector_ws2812b[offset_led_to_vector + 1] = 0b01001001;
		vector_ws2812b[offset_led_to_vector + 2] = 0b00100100;
		//R -> 0b00000000
		vector_ws2812b[offset_led_to_vector + 3] = 0b10010010;
		vector_ws2812b[offset_led_to_vector + 4] = 0b01001001;
		vector_ws2812b[offset_led_to_vector + 5] = 0b00100100;
		//B -> 0b00000000
		vector_ws2812b[offset_led_to_vector + 6] = 0b10010010;
		vector_ws2812b[offset_led_to_vector + 7] = 0b01001001;
		vector_ws2812b[offset_led_to_vector + 8] = 0b00100100;


		//value_G -> 0bABCDEFGH
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_G >> 1) & 0b01000000;	//aux = 0b0A000000
		aux_logic_or |= (value_G >> 3) & 0b00001000;	//aux = 0b0A00B000
		aux_logic_or |= (value_G >> 5) & 0b00000001;	//aux = 0b0A00B00C
		vector_ws2812b[offset_led_to_vector + 0] |= aux_logic_or;	//0b1A01B01C
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_G << 1) & 0b00100000;	//aux = 0b00D00000
		aux_logic_or |= (value_G >> 1) & 0b00000100;	//aux = 0b00D00E00
		vector_ws2812b[offset_led_to_vector + 1] |= aux_logic_or;	//0b01D01E01
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_G << 5) & 0b10000000;	//aux = 0bF0000000
		aux_logic_or |= (value_G << 3) & 0b00010000;	//aux = 0bF00G0000
		aux_logic_or |= (value_G << 1) & 0b00000010;	//aux = 0bF00G00H0
		vector_ws2812b[offset_led_to_vector + 2] |= aux_logic_or;	//0bF01G01H0

		//value_R -> 0bABCDEFGH
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_R >> 1) & 0b01000000;	//aux = 0b0A000000
		aux_logic_or |= (value_R >> 3) & 0b00001000;	//aux = 0b0A00B000
		aux_logic_or |= (value_R >> 5) & 0b00000001;	//aux = 0b0A00B00C
		vector_ws2812b[offset_led_to_vector + 3] |= aux_logic_or;	//0b1A01B01C
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_R << 1) & 0b00100000;	//aux = 0b00D00000
		aux_logic_or |= (value_R >> 1) & 0b00000100;	//aux = 0b00D00E00
		vector_ws2812b[offset_led_to_vector + 4] |= aux_logic_or;	//0b01D01E01
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_R << 5) & 0b10000000;	//aux = 0bF0000000
		aux_logic_or |= (value_R << 3) & 0b00010000;	//aux = 0bF00G0000
		aux_logic_or |= (value_R << 1) & 0b00000010;	//aux = 0bF00G00H0
		vector_ws2812b[offset_led_to_vector + 5] |= aux_logic_or;	//0bF01G01H0

		//value_B -> 0bABCDEFGH
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_B >> 1) & 0b01000000;	//aux = 0b0A000000
		aux_logic_or |= (value_B >> 3) & 0b00001000;	//aux = 0b0A00B000
		aux_logic_or |= (value_B >> 5) & 0b00000001;	//aux = 0b0A00B00C
		vector_ws2812b[offset_led_to_vector + 6] |= aux_logic_or;	//0b1A01B01C
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_B << 1) & 0b00100000;	//aux = 0b00D00000
		aux_logic_or |= (value_B >> 1) & 0b00000100;	//aux = 0b00D00E00
		vector_ws2812b[offset_led_to_vector + 7] |= aux_logic_or;	//0b01D01E01
		aux_logic_or = 0;						//aux = 0b00000000
		aux_logic_or |= (value_B << 5) & 0b10000000;	//aux = 0bF0000000
		aux_logic_or |= (value_B << 3) & 0b00010000;	//aux = 0bF00G0000
		aux_logic_or |= (value_B << 1) & 0b00000010;	//aux = 0bF00G00H0
		vector_ws2812b[offset_led_to_vector + 8] |= aux_logic_or;	//0bF01G01H0

	}
}

/* Description:
 *				setea mediante vectores un conjunto de leds
 * Parameters:
 * 				uint16_t initial_led:	indice inicial del conjunto de leds a setear, 0 <= initial_led < N_pixel - size_vector
 * 				uint8_t *p_values_R:	puntero del vector de valores de las componentes R a setear
 * 				uint8_t *p_values_G:	puntero del vector de valores de las componentes G a setear
 * 				uint8_t *p_values_B:	puntero del vector de valores de las componentes B a setear
 * 				uint16_t size_vector:	longitud de los vectores
 * Return:
 * 				-
 * Notes:
 *
 */
void ws2812b_set_multi_ledRGB(uint16_t initial_led, uint8_t *p_values_R, uint8_t *p_values_G, uint8_t *p_values_B, uint16_t size_vector){
	for(uint16_t led=0; led<size_vector; led++){
		ws2812b_set_ledRGB(led+initial_led, p_values_R[led], p_values_G[led], p_values_B[led]);
	}
}

float aux_p;
float aux_q;
float aux_t;
uint16_t aux_hi;

/* Description:
 *				setea las componentes RGB en formato HSV del led de interes
 * Parameters:
 * 				uint16_t N_led:		indice del led a setear, 	0 <= N_led < N_pixel
 * 				double value_H:		valor de la componente H, 	0 <= value_H <= 360
 * 				double value_S:		valor de la componente S, 	0 <= value_S <= 1
 * 				double value_V:		valor de la componente V, 	0 <= value_V <= 1
 * Return:
 * 				-
 * Notes:
 *
 */
void ws2812b_set_ledHSV(uint16_t N_led, double value_H, double value_S, double value_V){
    while (value_H < 0) value_H += 360;
    while (value_H >= 360) value_H -= 360;
    aux_hi = ((uint16_t)value_H) / 60;
    aux_p 	=	value_V*(1 - value_S);
    aux_q	=	value_V*(1-((value_H / 60) - aux_hi)*value_S);
    aux_t 	=	value_V * (1 - (1 - ((value_H / 60) - aux_hi)) * value_S);
    value_V	*=	255;
    aux_t 	*=	255;
    aux_p 	*=	255;
    aux_q 	*=	255;
    switch (aux_hi){
        case 0:		ws2812b_set_ledRGB(N_led, (uint8_t)value_V, (uint8_t)aux_t, (uint8_t)aux_p);
        break;
        case 1:		ws2812b_set_ledRGB(N_led, (uint8_t)aux_q, (uint8_t)value_V, (uint8_t)aux_p);
        break;
        case 2:		ws2812b_set_ledRGB(N_led, (uint8_t)aux_p, (uint8_t)value_V, (uint8_t)aux_t);
        break;
        case 3:		ws2812b_set_ledRGB(N_led, (uint8_t)aux_p, (uint8_t)aux_q, (uint8_t)value_V);
        break;
        case 4:		ws2812b_set_ledRGB(N_led, (uint8_t)aux_t, (uint8_t)aux_p, (uint8_t)value_V);
        break;
        case 5:		ws2812b_set_ledRGB(N_led, (uint8_t)value_V, (uint8_t)aux_p, (uint8_t)aux_q);
        break;
        default:	ws2812b_set_ledRGB(N_led, (uint8_t)0, (uint8_t)0, (uint8_t)0);
        break;
    }
}

/* Description:
 *				setea mediante vectores un conjunto de leds en formato HSV
 * Parameters:
 * 				uint16_t initial_led:	indice inicial del conjunto de leds a setear, 0 <= initial_led < N_pixel - size_vector
 * 				double *p_values_H:		puntero del vector de valores de las componentes H a setear
 * 				double *p_values_S:		puntero del vector de valores de las componentes S a setear
 * 				double *p_values_V:		puntero del vector de valores de las componentes V a setear
 * 				uint16_t size_vector:	longitud de los vectores
 * Return:
 * 				-
 * Notes:
 *
 */
void ws2812b_set_multi_ledHSV(uint16_t initial_led, double *p_values_H, double *p_values_S, double *p_values_V, uint16_t size_vector){
	for(uint16_t led=0; led<size_vector; led++){
		ws2812b_set_ledHSV(led+initial_led, p_values_H[led], p_values_S[led], p_values_V[led]);
	}
}

