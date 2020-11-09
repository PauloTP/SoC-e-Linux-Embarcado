#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> // Leiutura e escrita no Avalon

//#define SIM

// LED Peripheral
#define REG_DATA_OFFSET 1

int motor_init(){
	return 0b0001;
}
int motor_halt(){
	return 0b0000;
}
int motor_en(unsigned int *p_motor){
	return 0;
}

int main(void){
  unsigned int led = 0;
  unsigned int *p_led = (unsigned int *) PERIPHERAL_LED_0_BASE;
  unsigned int *p_motor = (unsigned int *) STEPMOTORMM_0_BASE;


  printf("Embarcados++ \n");

  *(p_motor + REG_DATA_OFFSET) = motor_halt();
  usleep(500000);
  *(p_motor + REG_DATA_OFFSET) = motor_init();


  //*(p_motor + REG_DATA_OFFSET) = 1 << 0;

  while(1){
       if (led < 4){
           *(p_led+REG_DATA_OFFSET) = (0x1 << led++);
           usleep(500000); // remover durante a simulacao
       }
       else{
           led = 0;
       }
   };

  return 0;
}


/*
#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include <io.h> // Leiutura e escrita no Avalon

//#define SIM

// LED Peripheral
#define REG_DATA_OFFSET 1

int main(void){
  unsigned int led = 0;
  unsigned int *p_led = (unsigned int *) PERIPHERAL_LED_0_BASE;

#ifndef SIM
  printf("Embarcados++ \n");
#endif

  while(1){
      if (led < 4){
          *(p_led+REG_DATA_OFFSET) = (0x1 << led++);
#ifndef SIM
          usleep(500000); // remover durante a simulacao
#endif
      }
      else{
          led = 0;
      }
  };

  return 0;
}

*/
