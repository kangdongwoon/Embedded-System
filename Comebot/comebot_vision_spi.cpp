#include <iostream>
#include <pthread.h>
//#include <mutex>
#include "spi.h"
#include "line_detection.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

//static mutex _oMutex;
uint8_t tx[4];
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
void* function_A(void* num){
	
	uint8_t rx[ARRAY_SIZE(tx)] = {0, };
	while(true){
		spi_main(tx,rx,(int)ARRAY_SIZE(tx));
	}
}
void* function_B(void* num){
	line_main(tx);
	return 0;
}



int main(int argc, char *argv[]){
	pthread_t ptA,ptB;
	cout<<"create Thread A"<<endl;
	pthread_create(&ptA,NULL,function_A,NULL);
	cout<<"create Thread B"<<endl;
	pthread_create(&ptB,NULL,function_B,NULL);
	pthread_join(ptA, NULL);
	pthread_join(ptB, NULL);
	
	return 0;	
}
