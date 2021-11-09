#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "TivaES.h"
#include "PE.h"
#include "SYSTICK.h"
#include "ADC.h"
#include "UART.h"
#include "Nokia5110.h"
#include "bitmapPhotos.h"

int main(){
	PE_Inicializa();
	TivaES_Inicializa();
	config_ADC();
	config_SYSTICK();
	config_UART();

}