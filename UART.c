#include "UART.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"

void configPORTUART (void){
	//Iniciando reloj del UART0
	SYSCTL_RCGC1_R|=SYSCTL_RCGC1_UART0;
	while((SYSCTL_PRUART_R & SYSCTL_PRUART_R0)==0x00);
	//Iniciando reloj del puerto A
	SYSCTL_RCGCGPIO_R|=SYSCTL_RCGCGPIO_R0;
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0)==0x00);
	//Configurando pines PA0(Rx) y PA1(Tx)
	GPIO_PORTA_DIR_R&=~0x01;
	GPIO_PORTA_DIR_R|=0x02;
	GPIO_PORTA_DEN_R|=0x03;
	GPIO_PORTA_PUR_R&=~0x03;
	GPIO_PORTA_PDR_R&=~0x03;
	GPIO_PORTA_AMSEL_R&=~0x03;
	GPIO_PORTA_AFSEL_R|=0x03;
	//Conectar los pines al UART
	GPIO_PORTA_PCTL_R=(GPIO_PORTA_PCTL_R & 0xFFFFFF00)|0x03;
	//Desactivando UART, para su configuración
	UART0_CTL_R&=~UART_CTL_UARTEN;
	//Configurando TRAMA DEL UART
  //1-Configuración de velocidad
	UART0_IBRD_R|=(UART0_IBRD_R & 0xFFFFFF00)+104;
	UART0_FBRD_R|=(UART0_FBRD_R & 0xFFFFFF00)+11;
	//2-Configurando trama y buffers
	UART0_LCRH_R&=~UART_LCRH_WLEN_M; 	//Eliminando cualquier valor, para poder configurar
	//2.1-Configuración de NÚMERO DE BITS POR CARÁCTER
	UART0_LCRH_R|= UART_LCRH_WLEN_8;	
	//2.2-Configuración de BUFFERS
	UART0_LCRH_R|= UART_LCRH_FEN;
	//2.3-Configuración de BITS DE PARADA (8 bits)
	UART0_LCRH_R|= UART_LCRH_STP2;
	//2.4-Configuración de PARIDAD (N-0XX)
	UART0_LCRH_R&=~UART_LCRH_PEN;
	UART0_LCRH_R&=~UART_LCRH_EPS;	
	UART0_LCRH_R&=~UART_LCRH_SPS;
	//2.5-Configuración de TRANSMISIÓN y RECEPCIÓN DE DATOS
	UART0_CTL_R|= UART_CTL_RXE;
	UART0_CTL_R|= UART_CTL_TXE;
	//Activando UART, para su configuración
	UART0_CTL_R|=UART_CTL_UARTEN;
}

uint8_t Rx_CARACTER (void){
	//Mientras FIFO vacío (Empty-INICIA EN 1)
	while((UART0_FR_R & UART_FR_RXFE)!=0);
	//Recibe DATO
	return (UART0_DR_R&0xFF);
}

void Tx_CARACTER (uint8_t caracter){
	//Mientras FIFO lleno(Full-INICIA EN 0)
	while((UART0_FR_R & UART_FR_TXFF)!=0);
	//Transmite DATO
	UART0_DR_R= caracter;
}

uint8_t Hay_Rx (void){
	if((UART0_FR_R & UART_FR_RXFE)!=0)
		return 0;
	else 
		return 1;
}

void Tx_CADENA (uint8_t cadena[]){
	uint8_t i;
	//Transmitir mientras sea diferente a caracter NULL
	for (i=0;cadena[i]!='\0';i++)
	Tx_CARACTER(cadena[i]);
}
