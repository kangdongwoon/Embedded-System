#include "spi.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
/*
 * Data Format : uint8_t
 * TX_Buffer_size = Rx_Buffer_size가 같아 Transfer를 하면서 Read를 동시에 함
 * 
 * void spi_main(uint8_t* tx,uint8_t* rx,uint32_t Array_size)
 * 
 * */
int main(int argc, char *argv[]){
	uint8_t tx[] = {
		0x57, 0x49, 0x43, 0x54, 0x4F, 0x52, 0x60
	};
	uint8_t rx[ARRAY_SIZE(tx)] = {0, };
	
	spi_main(tx,rx,(int)ARRAY_SIZE(tx));
}
