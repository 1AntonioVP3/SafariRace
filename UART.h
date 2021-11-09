#include "tm4c123gh6pm.h"
#include <stdint.h>

/********config_UART********/
//Funci�n que inicializa el UART0,con trama 9600 bps,
//8 bits, N paridad y 1 bit de parada.
void config_UART(void);

/******Rx_CARACTER*****/
//Recepci�n de un car�cter.
uint8_t Rx_CARACTER (void);

/******Tx_CARACTER*****/
//Transmisi�n de un car�cter.
void Tx_CARACTER (uint8_t caracter);

/******Tx_CADENA*****/
//Transmisi�n de una cadena.
void Tx_CADENA (uint8_t cadena[]);


/******Rx_COPADO*****/
//Verifica estado del FIFO de recepci�n.
uint8_t Hay_Rx (void);
