#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "SYSTICK.h"

uint16_t contador=1;
void config_SYSTICK(void){
	//Inhabilitar módulo SYSTICK
	NVIC_ST_CTRL_R &=~NVIC_ST_CTRL_ENABLE;
	//Configuración del tiempo deseado (1ms)
	NVIC_ST_RELOAD_R= (NVIC_ST_RELOAD_R & 0xFF000000)|0x00003E7F;
	//Inicialización del contador con cero(escribiendo cualquier valor)
	NVIC_ST_CURRENT_R&=~(0x00FFFFFF);
	//Habilitación del módulo SYSTICK y habilitación del uso del RELOJ DEL SISTEMA
	NVIC_ST_CTRL_R|=(NVIC_ST_CTRL_CLK_SRC|NVIC_ST_CTRL_ENABLE);

}
void Actualiza_CONTADOR(uint16_t periodo){
		//¿Ha pasado 1ms?
	if((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT)){
		if(contador<periodo)
			contador++; 
		}
}
