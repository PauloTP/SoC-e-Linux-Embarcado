#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )
// asd
#define USER_IO_DIR     (0x01000000)
#define BIT_LED         (0x01000000)
#define BUTTON_MASK     (0x02000000)

#define SOCKET_NAME "/tmp/9Lq7BNBnBycd6nxy.socket"

void *virtual_base;
int fd;

void init_hw(void){
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		exit( 1 );
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		exit( 1 );
	}

	alt_setbits_word( ( virtual_base + ( ( uint32_t )( ALT_GPIO1_SWPORTA_DDR_ADDR ) & ( uint32_t )( HW_REGS_MASK ) ) ), USER_IO_DIR );

}

int main(int argc, char *argv[]) {

//    init_hw();

    int sock = 0, connfd = 0;
    char sendBuff[1025];
	char recvBuff[1025];
	memset(sendBuff, '0', sizeof(sendBuff));

    unlink(SOCKET_NAME);
	sock = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un name;
    memset(&name, 0, sizeof(struct sockaddr_un));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
   
    bind(sock, (const struct sockaddr *) &name, sizeof(struct sockaddr_un));

    listen(sock, 20);
    connfd = accept(sock, (struct sockaddr*)NULL, NULL);

    while(1) {
        // snprintf(sendBuff, sizeof(sendBuff), "PING!! \r\n");
        // write(connfd, sendBuff, strlen(sendBuff));fdf 

		// scan_input = alt_read_word( ( virtual_base + ( ( uint32_t )(  ALT_GPIO1_EXT_PORTA_ADDR ) & ( uint32_t )( HW_REGS_MASK ) ) ) );		
		// //usleep(1000*1000);		
		// if(~scan_input&BUTTON_MASK){
		// 	snprintf(sendBuff, sizeof(sendBuff), "BUTTON\r\n");
        //     write(connfd, sendBuff, strlen(sendBuff));
        // }
		
        // read and print
        int n = 0;
        if ((n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
            recvBuff[n] = 0;
	        fputs(recvBuff, stdout);

            if(!strcmp(recvBuff, "LED_ON\n")){
           //     alt_setbits_word( ( virtual_base + ( ( uint32_t )( ALT_GPIO1_SWPORTA_DR_ADDR ) & ( uint32_t )( HW_REGS_MASK ) ) ), BIT_LED );
                printf("led on \n");
                usleep(500*1000);
            }

            if(!strcmp(recvBuff, "LED_OFF\n" )){
                printf("led off \n");
         //       alt_clrbits_word( ( virtual_base + ( ( uint32_t )( ALT_GPIO1_SWPORTA_DR_ADDR ) & ( uint32_t )( HW_REGS_MASK ) ) ), BIT_LED );
                usleep(500*1000);
            }
        }

        sleep(1);
    }

    close(connfd);
    sleep(1);
}
