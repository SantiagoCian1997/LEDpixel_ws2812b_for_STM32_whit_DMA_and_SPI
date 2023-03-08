# LEDpixel_ws2812b_for_STM32_whit_DMA_and_SPI

Librería destinada al control de "LED pixel" basados en el integrado ws2812b, haciendo uso del pin MOSI del puerto SPI1 y del DMA de dicho puerto. De este modo se tiene un refresco continuo de los datos enviados a los LEDs directamente desde la memoria sin hacer uso del núcleo del procesador ni de interrupciones, permitiendo destinar el tiempo de procesamiento a diversas tareas.

La ventaja de trabajar con los LED pixel de este modo es que se destina un segmento de la memoria, con el cual trabajara el DMA del puerto SPI1, a la transmisión continua hacia los LEDs. Esta transmisión de datos no ocupara tiempo de ejecución del procesador ya que no hace uso de interrupciones o de funciones de envió de datos y al estar configurado de manera cíclica el DMA constantemente envía la trama. Solo se utilizará tiempo de ejecución al momento de cambiar las componentes de colores de los LEDs ya que estas funciones modifican por software los datos de la memoria que utiliza el DMA.


# Configuración y uso de la librería

##   Configuracion "ws2812b_SPI_DMA.h"
```C
#define N_pixel 60
```
##   Uso de la libreria en "main.c"
```C

#include "ws2812b_SPI_DMA.h"

int main(){
    /* Ejemplo sencillo de uso.
    *   Para mas documentacion vea las definiciones de cada funcion en "ws2812b_SPI_DMA.c"
    */

//void ws2812b_init(SPI_HandleTypeDef *hspi);
    ws2812b_init(&hspi1);   //inicializacion de la libreria

//void ws2812b_set_ledRGB(uint16_t N_led, uint8_t value_R, uint8_t value_G, uint8_t value_B);
    ws2812b_set_ledRGB(4, 255, 0, 0);  //configura el led N 4 en formato "RGB". en este caso ROJO

//void ws2812b_set_ledHSV(uint16_t N_led, double value_H, double value_S, double value_V);
    ws2812b_set_ledHSV(2, 60, 0.5, 1); //configura el led N 2 en formato "HSV". en este caso AMARILLO poco saturado con maximo brillo

//void ws2812b_set_multi_ledRGB(uint16_t initial_led, uint8_t *p_values_R, uint8_t *p_values_G, uint8_t *p_values_B, uint16_t size_vector);
    uint8_t R_v[4]={0, 110, 255, 30};
    uint8_t G_v[4]={0, 32, 50, 200};
    uint8_t B_v[4]={55, 220, 0, 45};
    ws2812b_set_multi_ledRGB(8, R_v, G_v, B_v, 4);  //configura desde el led N 8 hasta el led N 11 las componentes RGB de los vectores

//void ws2812b_set_multi_ledHSV(uint16_t initial_led, double *p_values_H, double *p_values_S, double *p_values_V, uint16_t size_vector);
    double H_v[3]={180, 20, 50, 360};       //rango de 0 a 360
    double S_v[3]={0.5, 1, 0.85, 0.4};      //rango de 0 a 1, saturacion
    double V_v[3]={1, 0.7, 0.4, 1};         //rango de 0 a 1, value
    ws2812b_set_multi_ledHSV(3, H_v, S_v, V_v, 3); //configrua desde el led N 3 hasta el led N 5 las componentes HSV de los vectores
}
```

En el archivo "ws2812b_SPI_DMA.h" se puede configurar la definición de “N_pixel” para modificar la cantidad de pixeles a utilizar. El espacio en memoria que ocupará la librería será de N_pixel*9+100 Bytes ya que se está utilizando 3 ciclos del clock del SPI para enviar cada bit de datos (24 bits por pixel = 3 Bytes por pixel) según el protocolo de comunicación del ws2812b. Mas 100 bytes que permanecerán el blanco para generar el tiempo de reset que el propio protocolo indica (por cuestiones de estabilidad al momento de refrescar se estimó por encima del tiempo mínimo que indica el datasheet).

Solo se utilizará el pin de MOSI (para el SPI1 este es el PA7 en el STM32F103) ya que al ser una transmisión asíncrona no se requiere el pin de CLOCK. Cabe aclarar que estos LEDs no se comunican por SPI, solo se utilizó el periférico SPI para generar la forma de onda requerida para transmitir los datos. 

Se tendrá que tener en cuenta que si se modifica la configuración de clock del archivo .ioc esto modificara el Baud Rate del puerto SPI1. Por esto frente a cualquier configuración que se realice se debe asegurar que el Baud Rate se mantenga en 2.5Mbits/s (idealmente 2.4Mbit/s pero debido a los prescalares que se disponen fue el valor mas cercano para un PCLK2=10MHz).

Este metodo de control solo se puede utilizar para los pixeles basados en el ws2812b ya que es el unico que posee la simetria en envios de datos para los valores logicos de 0 o de 1 que permite encasillarlos en tres ciclos de clock de un puerto SPI a la velocidad adecuada. Los pixeles basados en ws2812 no poseen esta simetria y los ws2811, a pesar de trabajar a una frecuencia mas baja, tampoco poseen la simetria necesaria.
