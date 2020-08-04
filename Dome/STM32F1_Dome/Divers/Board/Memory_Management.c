
#include "Memory_Management.h"

Speed_Data_type Speed_Data[6] = {0};
Speed_Data_type Speed_Correction_Data[6] = {0};
system_set_type system_set_data = {0};
//Control_Data_type Control_Data = {0};
Line_Data_type Line_Data = {0};
/********************************************************************************************************
                                            EEPROM(AT24C512)内存地址分布

         预留                        PWM波速度参数（原始值，不可改动）              

                    1档         2档          3档                4档          5档            6档
         0-100    101-166     301-366       501-566           701-766      901-966       1101-1166
 
(Byte)   101        66          66            66                66            66            66
          1          2           3             4                 5             6             7
       ************************************************************************************************
                                       PWM控制补偿参数                           

             1档         2档          3档                4档          5档            6档
         1301-1366    1501-1566    1701-1766         1901-1966      2101-2166      2301-2366 
 
(Byte)      66            66           66                66             66              66
            8             9            10                11             12              13
       ************************************************************************************************
         编号等        控制数据       线路管理          线路站点排布          
  
         2501-2513    2701-2800        2901-3500          5001-5500(前250按顺序排布站点，后250按顺序排布线路号)       
 
(Byte)     13            100            200*3=600             500
            14            15              16               17   18  19
       ************************************************************************************************
         货物动作                           
  
         6501-6750                 
 
(Byte)      250             
            21              
*********************************************************************************************************/
void Base_Data_Load(void)
{	
	//系统设置参数加载
	AT24CXX_Read(MEMORY_SYSTEMSETADDR,system_set_data.all,6);
	
	//速度参数及速度修正参数加载
	AT24CXX_Read(MEMORY_SPEED1PIDADDR,Speed_Data[0].all,66);
	AT24CXX_Read(MEMORY_SPEED2PIDADDR,Speed_Data[1].all,66);
	AT24CXX_Read(MEMORY_SPEED3PIDADDR,Speed_Data[2].all,66);
	AT24CXX_Read(MEMORY_SPEED4PIDADDR,Speed_Data[3].all,66);
	AT24CXX_Read(MEMORY_SPEED5PIDADDR,Speed_Data[4].all,66);
	AT24CXX_Read(MEMORY_SPEED6PIDADDR,Speed_Data[5].all,66);
	delay_ms(1000);
	AT24CXX_Read(MEMORY_SPEED1CPIDADDR,Speed_Correction_Data[0].all,66);
	AT24CXX_Read(MEMORY_SPEED2CPIDADDR,Speed_Correction_Data[1].all,66);
	AT24CXX_Read(MEMORY_SPEED3CPIDADDR,Speed_Correction_Data[2].all,66);
	AT24CXX_Read(MEMORY_SPEED4CPIDADDR,Speed_Correction_Data[3].all,66);
	AT24CXX_Read(MEMORY_SPEED5CPIDADDR,Speed_Correction_Data[4].all,66);
	AT24CXX_Read(MEMORY_SPEED6CPIDADDR,Speed_Correction_Data[5].all,66);
  //如果目标站点缓存个数不为0则上报剩余目标站点，并将第一个赋值给Control_Data.bit.terminal_station 
}


void Car_Move_Parametr_Init(void)
{
	Speed_Data_type test_speed_data[6] = {0};
/********************************速度值及PID参数初始化********************************************/
	
	//第1档速度（此为最低速度，其它档位数值越大，速度越快）
  test_speed_data[0].bit.speed_value = 10;
	
	/*****************************直道所需PID**********************/
	//该档速度下偏差大区PID参数
	test_speed_data[0].bit.PID[0][0].f = 30.0;//14.0     11.5  16.5
	test_speed_data[0].bit.PID[0][1].f = 0.0;//         0.5    0.0
	test_speed_data[0].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //偏差中区PID参数	
	test_speed_data[0].bit.PID[1][0].f = 37.0;//8.5      8.5     15.5
	test_speed_data[0].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[0].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//临时停车PID参数
	test_speed_data[0].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[0].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[0].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************弯道所需PID**********************/
	test_speed_data[0].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[0].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[0].bit.PID[3][2].f = 1.5;//     	
	
	/*****************************停车所需PID**********************/
	test_speed_data[0].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[0].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[0].bit.PID[4][2].f = 1.5;//     		
	
	/*****************************减速至其他速度所需减速程度(共5个：0-4)**********************/
	test_speed_data[0].bit.speed_change_value[0] = 1;     //停车所用减速缓冲	

	test_speed_data[0].bit.speed_change_value[1] = 0;     //未用
	
	test_speed_data[0].bit.speed_change_value[2] = 0;     //未用
	
	test_speed_data[0].bit.speed_change_value[3] = 0;     //未用
	
	test_speed_data[0].bit.speed_change_value[4] = 0;     //未用


	AT24CXX_Write(MEMORY_SPEED1PIDADDR,test_speed_data[0].all,66);
	
	
	//第2档速度
  test_speed_data[1].bit.speed_value = 50;
	
	/*****************************直道所需PID**********************/
	//该档速度下偏差大区PID参数
	test_speed_data[1].bit.PID[0][0].f = 18.0;//14.0     11.5  16.5
	test_speed_data[1].bit.PID[0][1].f = 0.0;//          0.5    0.0
	test_speed_data[1].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //偏差中区PID参数	
	test_speed_data[1].bit.PID[1][0].f = 17.0;//8.5      8.5     15.5
	test_speed_data[1].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[1].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//临时停车PID参数
	test_speed_data[1].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[1].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[1].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************弯道所需PID**********************/
	test_speed_data[1].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[1].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[1].bit.PID[3][2].f = 1.5;//    

	/*****************************停车所需PID**********************/
	test_speed_data[1].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[1].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[1].bit.PID[4][2].f = 1.5;// 
	
	/*****************************减速至其他速度所需减速程度(共5个：0-4)**********************/
	test_speed_data[1].bit.speed_change_value[0] = 2;     //停车所用减速缓冲	

	test_speed_data[1].bit.speed_change_value[1] = 1;     //减速到第1挡速度所用减速缓冲
	
	test_speed_data[1].bit.speed_change_value[2] = 0;     //未用
	
	test_speed_data[1].bit.speed_change_value[3] = 0;     //未用
	
	test_speed_data[1].bit.speed_change_value[4] = 0;     //未用

	AT24CXX_Write(MEMORY_SPEED2PIDADDR,test_speed_data[1].all,66);
	


	//第3档速度
  test_speed_data[2].bit.speed_value = 60;
	
	/*****************************直道所需PID**********************/
	//该档速度下偏差大区PID参数
	test_speed_data[2].bit.PID[0][0].f = 18.0;//14.0     11.5  16.5
	test_speed_data[2].bit.PID[0][1].f = 0.0;//         0.5    0.0
	test_speed_data[2].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //偏差中区PID参数	
	test_speed_data[2].bit.PID[1][0].f = 17.0;//8.5      8.5     15.5
	test_speed_data[2].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[2].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//临时停车PID参数
	test_speed_data[2].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[2].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[2].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************弯道所需PID**********************/
	test_speed_data[2].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[2].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[2].bit.PID[3][2].f = 1.5;//     	
	
	/*****************************停车所需PID**********************/
	test_speed_data[2].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[2].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[2].bit.PID[4][2].f = 1.5;// 


	/*****************************减速至其他速度所需减速程度(共5个：0-4)**********************/
	test_speed_data[2].bit.speed_change_value[0] = 3;     //停车所用减速缓冲	

	test_speed_data[2].bit.speed_change_value[1] = 2;     //减速到第1挡速度所用减速缓冲
	
	test_speed_data[2].bit.speed_change_value[2] = 1;     //减速到第2挡速度所用减速缓冲
	
	test_speed_data[2].bit.speed_change_value[3] = 0;     //未用
	
	test_speed_data[2].bit.speed_change_value[4] = 0;     //未用


	AT24CXX_Write(MEMORY_SPEED3PIDADDR,test_speed_data[2].all,66);
	
	
	
	//第4档速度
  test_speed_data[3].bit.speed_value = 60;
	
	/*****************************直道所需PID**********************/
	//该档速度下偏差大区PID参数
	test_speed_data[3].bit.PID[0][0].f = 18.0; //14.0     11.5  16.5
	test_speed_data[3].bit.PID[0][1].f = 0.0;  //          0.5    0.0
	test_speed_data[3].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //偏差中区PID参数	
	test_speed_data[3].bit.PID[1][0].f = 17.0;//8.5      8.5     15.5
	test_speed_data[3].bit.PID[1][1].f = 4.0; //         0.2      3.0
	test_speed_data[3].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//临时停车PID参数
	test_speed_data[3].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[3].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[3].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************弯道所需PID**********************/
	test_speed_data[3].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[3].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[3].bit.PID[3][2].f = 1.5;//    

	/*****************************停车所需PID**********************/
	test_speed_data[3].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[3].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[3].bit.PID[4][2].f = 1.5;// 

	/*****************************减速至其他速度所需减速程度(共5个：0-4)**********************/
	test_speed_data[3].bit.speed_change_value[0] = 4;     //停车所用减速缓冲	

	test_speed_data[3].bit.speed_change_value[1] = 3;     //减速到第1挡速度所用减速缓冲
	
	test_speed_data[3].bit.speed_change_value[2] = 2;     //减速到第2挡速度所用减速缓冲
	
	test_speed_data[3].bit.speed_change_value[3] = 1;     //减速到第3挡速度所用减速缓冲
	
	test_speed_data[3].bit.speed_change_value[4] = 0;     //未用

	AT24CXX_Write(MEMORY_SPEED4PIDADDR,test_speed_data[3].all,66);
	


	//第5档速度
  test_speed_data[4].bit.speed_value = 60;
	
	/*****************************直道所需PID**********************/
	//该档速度下偏差大区PID参数
	test_speed_data[4].bit.PID[0][0].f = 18.0;//14.0     11.5  16.5
	test_speed_data[4].bit.PID[0][1].f = 0.0;//         0.5    0.0
	test_speed_data[4].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //偏差中区PID参数	
	test_speed_data[4].bit.PID[1][0].f = 17.0;//8.5      8.5     15.5
	test_speed_data[4].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[4].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//临时停车PID参数
	test_speed_data[4].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[4].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[4].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************弯道所需PID**********************/
	test_speed_data[4].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[4].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[4].bit.PID[3][2].f = 1.5;//     	

	/*****************************停车所需PID**********************/
	test_speed_data[4].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[4].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[4].bit.PID[4][2].f = 1.5;// 

	/*****************************减速至其他速度所需减速程度(共5个：0-4)**********************/
	test_speed_data[4].bit.speed_change_value[0] = 5;     //停车所用减速缓冲	

	test_speed_data[4].bit.speed_change_value[1] = 4;     //减速到第1挡速度所用减速缓冲
	
	test_speed_data[4].bit.speed_change_value[2] = 3;     //减速到第2挡速度所用减速缓冲
	
	test_speed_data[4].bit.speed_change_value[3] = 2;     //减速到第3挡速度所用减速缓冲
	
	test_speed_data[4].bit.speed_change_value[4] = 1;     //减速到第4挡速度所用减速缓冲


	AT24CXX_Write(MEMORY_SPEED5PIDADDR,test_speed_data[4].all,66);
	
	
	
	//第6档速度
  test_speed_data[5].bit.speed_value = 30;
	
	/*****************************直道所需PID**********************/
	//该档速度下偏差大区PID参数
	test_speed_data[5].bit.PID[0][0].f = 20.0;//14.0     11.5  16.5
	test_speed_data[5].bit.PID[0][1].f = 0.0;//          0.5    0.0
	test_speed_data[5].bit.PID[0][2].f = 0.005;//         2.5  0.025	
	
  //偏差中区PID参数	
	test_speed_data[5].bit.PID[1][0].f = 25.0;//8.5      8.5     15.5
	test_speed_data[5].bit.PID[1][1].f = 4.0;//         0.2      3.0
	test_speed_data[5].bit.PID[1][2].f = 14.0;//           0.5   14.0
	
	//临时停车PID参数
	test_speed_data[5].bit.PID[2][0].f = 0.0;//         0.0        0 
	test_speed_data[5].bit.PID[2][1].f = 5.0;//        0.08       4.0
	test_speed_data[5].bit.PID[2][2].f = 1.5;//         0.8       1.0
	
	/*****************************弯道所需PID**********************/
	test_speed_data[5].bit.PID[3][0].f = 30.0;//         0.0        0 
	test_speed_data[5].bit.PID[3][1].f = 5.0;//        0.08       4.0
	test_speed_data[5].bit.PID[3][2].f = 1.5;//    

	/*****************************停车所需PID**********************/
	test_speed_data[5].bit.PID[4][0].f = 30.0;//         0.0        0 
	test_speed_data[5].bit.PID[4][1].f = 5.0;//        0.08       4.0
	test_speed_data[5].bit.PID[4][2].f = 1.5;// 

	/*****************************减速至其他速度所需减速程度(共5个：0-4)**********************/
	test_speed_data[5].bit.speed_change_value[0] = 5;     //减速到第1挡速度所用减速缓冲	

	test_speed_data[5].bit.speed_change_value[1] = 4;     //减速到第2挡速度所用减速缓冲
	
	test_speed_data[5].bit.speed_change_value[2] = 3;     //减速到第3挡速度所用减速缓冲
	
	test_speed_data[5].bit.speed_change_value[3] = 2;     //减速到第4挡速度所用减速缓冲
	
	test_speed_data[5].bit.speed_change_value[4] = 1;     //减速到第5挡速度所用减速缓冲

	AT24CXX_Write(MEMORY_SPEED6PIDADDR,test_speed_data[5].all,66);
	
}


