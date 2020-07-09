#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal.h"
   
//uint8_t TxData[7] = {1,0,2,4,5,1,5};
uint8_t RxData[7];
uint8_t Uart_RxData[7];

void Uart_Transmit(UART_HandleTypeDef *huart6, uint8_t *pData, uint16_t Size, uint32_t Timeout){
    HAL_UART_Transmit(huart6, RxData, 7, 50);
    HAL_UART_Transmit(huart6, "\n", 1, 50);
    HAL_Delay(10);
}