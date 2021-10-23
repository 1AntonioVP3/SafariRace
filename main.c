#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "bitmapPhotos.h"
#include "TivaES.h"
#include <stdio.h>

void setupADC(void){
  SYSCTL_RCGCADC_R |= 0x0001;   // 1) activate ADC0
  SYSCTL_RCGCGPIO_R |= 0x10;    // 2) activate clock for Port E
  while((SYSCTL_PRGPIO_R&0x10) != 0x10){};  // 3) for stabilization
  GPIO_PORTE_DIR_R &= ~0x10;    // 4) make PE4 input
  GPIO_PORTE_AFSEL_R |= 0x08;   // 5) enable alternate function on PE3
  GPIO_PORTE_DEN_R &= ~0x08;    // 6) disable digital I/O on PE3
  GPIO_PORTE_AMSEL_R |= 0x08;   // 7) enable analog functionality on PE3
// while((SYSCTL_PRADC_R&0x0001) != 0x0001){}; // good code, but not implemented in simulator
  ADC0_PC_R &= ~0xF;
  ADC0_PC_R |= 0x1;             // 8) configure for 125K samples/sec
  ADC0_SSPRI_R = 0x0123;        // 9) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;      // 10) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;       // 11) seq3 is software trigger
 // ADC0_SSMUX3_R &= ~0x000F;
 // ADC0_SSMUX3_R += 9;           // 12) set channel
  ADC0_SSMUX3_R = 0;           // 12) set channel
  ADC0_SSCTL3_R = 0x0006;       // 13) no TS0 D0, yes IE0 END0
  ADC0_IM_R &= ~0x0008;         // 14) disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0008;       // 15) enable sample sequencer 3
}



/****************************************************************************************/
/***** F U N C I O N E S *****/
/****************************************************************************************/
/****************************************************************************************/
/***** InicializaPtoSerial() *****/
/****************************************************************************************/
/***** Configura el UART0 con los siguientes parámetros de comunicación serial: *****/
/***** 9600, 8, N, 1. Frecuencia del reloj del sistema 16MHz. *****/
/****************************************************************************************/
/***** ENTRADAS: Ninguna *****/
/***** SALIDA: Ninguna *****/
/****************************************************************************************/
void InicializaPtoSerial(void){
  // Activamos el reloj para el UART0
  SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
  while(!(SYSCTL_PRUART_R & SYSCTL_PRUART_R0));
  // Inhabilitamos el UART0
  UART0_CTL_R &= ~UART_CTL_UARTEN;
  // Velocidad 9600bps (Fsysclk = 16MHz)
  UART0_IBRD_R = (UART0_IBRD_R & 0xFFFF0000) | 104;
  UART0_FBRD_R = (UART0_FBRD_R & 0xFFFFFFC0) | 11;
  // 8, N, 1, FIFOs habilitados
  UART0_LCRH_R = (UART0_LCRH_R & 0xFFFFFF00) | 0x70;
  // Habilitamos el UART0, recepción y transmisión
  UART0_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
  // Activamos la señal de reloj para GPIOA
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
  while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0));
  // Activamos funciones alternas para PA0 y PA1
  GPIO_PORTA_AFSEL_R |= 0x03;
  // Conectamos UART0 a PA0 y PA1
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)|0x00000011;
  // Desactivamos funciones analógicas en PA0 y PA1
  GPIO_PORTA_AMSEL_R &= ~(0x03);
  // Activamos funciones digitales en PA0 y PA1
  GPIO_PORTA_DEN_R |= 0x03;
}