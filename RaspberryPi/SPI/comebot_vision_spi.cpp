#include <iostream>
#include <pthread.h>
#include "spi.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

void* function_A(void* num){
	uint8_t tx[] = {
		0x57, 0x49, 0x43, 0x54, 0x4F, 0x52, 0x60
	};
	uint8_t rx[ARRAY_SIZE(tx)] = {0, };
	while(true){
		spi_main(tx,rx,(int)ARRAY_SIZE(tx));
	}
}

int main(int argc, char *argv[]){
	pthread_t ptA;
	cout<<"create Thread A"<<endl;
	pthread_create(&ptA,NULL,function_A,NULL);
	pthread_join(ptA, NULL);
	
	return 0;	
}
