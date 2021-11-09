#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "PE.h"
#define PE1 0x02
/*****              CONSTANTES PARA ESTADOS DE PULSADORES                           *****/
#define PRESIONADO      0
#define NO_PRESIONADO   1
void PE_Inicializa(void){
	SYSCTL_RCGCGPIO_R|=SYSCTL_RCGCGPIO_R4;
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4)==0);
	//Configurando como entrada a PE1
	GPIO_PORTE_DIR_R&=~0x02;
	GPIO_PORTE_DEN_R|=0x02;
	GPIO_PORTE_PUR_R&=~0x02;
	GPIO_PORTE_PDR_R&=~0x02;
}

uint8_t PE_LeePulsador(void){
	if((GPIO_PORTE_DATA_R & PE1)==0)
		return PRESIONADO;
	else 
		return NO_PRESIONADO;
}

void PE_EsperaPresionarPulsador(void){
	while((GPIO_PORTE_DATA_R & PE1)!=0);
}

void PE_EsperaSoltarPulsador(void){
	while((GPIO_PORTE_DATA_R & PE1)==0);
}

void PE_EsperaPulsador(void){
	while((GPIO_PORTE_DATA_R & PE1)!=0);
	while((GPIO_PORTE_DATA_R & PE1)==0);
}