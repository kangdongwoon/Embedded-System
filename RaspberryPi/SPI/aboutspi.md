**SPI MASTER**
-
- 데이터 통신 채널을 동기화하기 위한 클럭을 정의한다
- CS선을 loW로 함으로써 클라이언트를 활성화한다
- 전송이 완료되면 CS선을 high로 해서 비활성화한다

**SPI MODE**
-
CPOL(극성)        CPHA(위상)  
0(idle에서 low)   0(clk의 rising edge에서 capture)  
0(idle에서 low)   1(clk의 falling edge에서 capture)  
1(idle에서 high)  0(clk의 rising edge에서 capture)  
1(idle에서 high)  1(clk의 falling edge에서 capture)  

**MEMO**
-
- SPI 프로토콜 자체에 최대 전송률, 전송제어, 통신 확인 응답이 정의되어 있지 않다.  
    - **구현이 장치에 따라 달라지기 때문에 Slave 장치의 Datasheet를 확인하는 것이 중요하다**  
