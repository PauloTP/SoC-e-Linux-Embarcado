#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include <io.h> /* Leiutura e escrita no Avalon */

int n = 0;
volatile int edge_capture;
int en =0;
int dir =0;
int vel = 0;

int sleep[] ={100000,70000,35000,10000};

void delay(int n){
      unsigned int delay = 0 ;
      while(delay < n){
          delay++;
      }
}

void handle_button_interrupts(void* context, alt_u32 id){
     /* Cast context to edge_capture's type. It is important that this be
      * declared volatile to avoid unwanted compiler optimization.
      */
     volatile int* edge_capture_ptr = (volatile int*) context;
     /* Store the value in the Button's edge capture register in *context. */
     *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE);
     n++;
     /* Reset the Button's edge capture register. */
     IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);

     // EN liga desliga
     en = (IORD_32DIRECT(PIO_1_BASE,0) & 0x01);

     dir = (IORD_32DIRECT(PIO_1_BASE,0) & 0x02);
     // vel1 vel0 dir en
     // xy01
     // 1100
     //shifita 2 para a direita para tranformar em 0011 (e ficar entre 0 e 3)
     vel = (IORD_32DIRECT(PIO_1_BASE,0) & 0x0C) >> 2;
     printf("vel %d \n",vel);
}

 void init_pio(){
	 /* Recast the edge_capture pointer to match the alt_irq_register() function
	  * prototype. */
	 void* edge_capture_ptr = (void*) &edge_capture;
	 /* Enable first four interrupts. */
	 IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0xf);
	 /* Reset the edge capture register. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0x0);
	 /* Register the interrupt handler. */
	 alt_irq_register( PIO_1_IRQ, edge_capture_ptr,
					   handle_button_interrupts );
}

int main(void){
	n=0;
	int motor = 0;
	int bla = 0;

	printf("Embarcados++ \n");
	//printf("%d",IORD_32DIRECT(PIO_1_BASE,0) & 0x01);
	init_pio();

	while(1){
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, n);



		if (en){
		  //bla = IORD_32DIRECT(PIO_1_BASE,0) & 0x01;
		  //printf("%d",bla);
		  if (dir){

			  if (motor <= 3){
				  IOWR_32DIRECT(PIO_2_BASE, 0, 0x01 << motor++);
				  usleep(sleep[vel]);
			  }
			  else{
				  motor = 0;
			  }
		}
		else{
		  if (motor >= 0){
			  IOWR_32DIRECT(PIO_2_BASE, 0, 0x01 << motor);
			  motor--;
			  usleep(sleep[vel]);
		  }
		  else{
			  motor = 3;
		  }
		}
		}

	};

  return 0;
}
