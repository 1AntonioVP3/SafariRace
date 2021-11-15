//#include <stdint.h>
//#include <stdio.h>
//#include "tm4c123gh6pm.h"
//#include "TivaES.h"
//#include "PE.h"
//#include "SYSTICK.h"
//#include "ADC.h"
//#include "UART.h"
//#include "Nokia5110.h"
//#include "bitmapPhotos.h"

//int main(){
//	//Inicialización de periféricos y puertos GPIO:
//	Nokia5110_Init();
//	PE_Inicializa();
//	TivaES_Inicializa();
//	config_ADC();
//	config_SYSTICK();
//	config_UART();
//	
//}

////Hola carlote

////                         .-.
////                        |/`\\.._
////     _..._,,--.         `\ /.--.\ _.-. 
////  ,/'  ..:::.. \     .._.-'/    \` .\/ 
//// /       ...:::.`\ ,/:..| |(o)  / /o)|
////|:..   |  ..:::::'|:..  ;\ `---'. `--'
////;::... |   .::::,/:..    .`--.   .:.`\_
//// |::.. ;  ..::'/:..   .--'    ;\   :::.`\
//// ;::../   ..::|::.  /'          ;.  ':'.---.
////  `--|    ..::;\:.  `\,,,____,,,/';\. (_)  |)
////     ;     ..::/:\:.`\|         ,__,/`;----'
////     `\       ;:.. \: `-..      `-._,/,_,/
////       \      ;:.   ). `\ `>     _:\
////        `\,  ;:..    \ \ _>     >'

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "bitmapPhotos.h"
#include "TivaES.h"

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


int main(void) {
	unsigned char sw1,sw2;
  unsigned char* frames[] = {player_car_keil,player_car_keil,player_car_keil,player_car_keil,player_car_keil,player_car_keil,player_car_keil,player_car_keil,player_car_keil,player_car_keil};
  Nokia5110_Init();
  Nokia5110_Clear();
  TivaES_Inicializa();
	setupADC();
	
  TivaES_EsperaPulsador(SW1);   
  Nokia5110_DrawFullImage((char*)titulo);

	while(1){
		sw1 = TivaES_LeePulsador(SW1);
		sw2 = TivaES_LeePulsador(SW2);
		
		if( sw1 == PRESIONADO && sw2 == NO_PRESIONADO){
			Nokia5110_TestFunctions(player_car); //editado
			while(1){
				sw1 = TivaES_LeePulsador(SW1);
				if( sw1 == NO_PRESIONADO ){
					Nokia5110_Clear();
					break;
				}
			}
		}	

		if( sw1 == NO_PRESIONADO && sw2 == PRESIONADO )
			Nokia5110_Runner(frames,30,15,27,30);
  }
} // fin de main

