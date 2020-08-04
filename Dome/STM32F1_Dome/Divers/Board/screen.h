#ifndef SCREEN_H
#define SCREEN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
/* Private macro -------------------------------------------------------------*/
#define RED 0xF800
#define YELLOW 0xFFE0
#define BLACK 0x0000
#define WHITE 0xFFFF

#define NOTIFY_CONTROL             0XB1  //控件更新通知
#define MSG_GET_CURRENT_SCREEN     0X01  //画面ID变化通知
#define NOTIFY_HandShake           0X55  //握手通知

/* Private variables type ---------------------------------------------------------*/
enum CtrlType
{
    kCtrlUnknown=0x0,
    kCtrlButton=0x10,                     //按钮
    kCtrlText=0x11,                       //文本
    kCtrlProgress,                        //进度条
    kCtrlSlider,                          //滑动条
    kCtrlMeter,                           //仪表
    kCtrlDropList,                        //下拉列表
    kCtrlRTC,                             //时间显示
    kCtrlGraph,                           //曲线图控件
    kCtrlTable,                           //表格控件
    kCtrlMenu,                            //菜单控件
    kCtrlSelector,                        //选择控件
    kCtrlQRCode,                          //二维码
};

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint8_t    cmd_head;                    //帧头
    uint8_t    cmd_type;                    //命令类型(UPDATE_CONTROL)   1个字节 
    uint8_t    ctrl_msg;                    //CtrlMsgType-指示消息的类型  1个字节 
    uint16_t   screen_id;                   //产生消息的画面ID  2个字节
    uint16_t   control_id;                  //产生消息的控件ID  2个字节
    uint8_t    control_type;                //控件类型  1个字节
    uint8_t    param[256];                  //可变长度参数，最多256个字节
    uint8_t    cmd_tail[4];                 //帧尾 4个字节
}CTRL_MSG,*PCTRL_MSG;

#pragma pack(pop)
/* Private variables -----------------------------------------------*/
extern QUEUE screen_que;      //指令队列
extern CMD screen_cmd;        //单条指令
extern uint8_t station_order[22];
extern uint16_t current_screen_id;
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  从指令队列中取出一条完整的指令
*  \param  cmd 指令接收缓存区
*  \param  buf_len 指令接收缓存区大小
*  \return  指令长度，0表示队列中无完整指令
*/
uint16_t ScreenQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void memsett(void* s, uint8_t c, uint8_t n);//可用来清空字符数组

void USARTScreenCheck(void);//检测串口屏状态函数

void GetNowScreen_id(void);//获得当前画面号

void ChangePage(uint16_t screen_id);//切换画面

void SetControlCmd(uint16_t screen_id,uint16_t control_id,FunctionalState NewState);//禁止/使能控件

//用于设置显示或者隐藏文本，1为显示0为隐藏
void SetTextDisplayCmd(uint16_t screen_id,uint16_t control_id,FunctionalState NewState);

//用于设置是否更新文本显示，1为使能0为禁止
void TextUpdataEnable(FunctionalState NewState);

void SetTextValue(uint16_t screen_id,uint16_t control_id,int32_t number);//设置文本控件值

void SetTextStrings(uint16_t screen_id,uint16_t control_id,uint8_t *str);//设置文本控件显示字符串

void SetControlForeColor(uint16_t screen_id,uint16_t control_id,uint16_t color);//设置控件前景色 

void SetProgressValue(uint16_t screen_id,uint16_t control_id,uint32_t value);//设置进度值

/*! 
*  \brief     设置按钮状态
*  \param  screen_id 画面ID
*  \param  control_id 控件ID
*  \param  value 按钮状态
*/
void SetButtonValue(uint16_t screen_id,uint16_t control_id,uint8_t state);

void ScreenInitDisplay(void);

void PowerAndIoSensorDataDisplay(void);

void ScreenCMD_Analyze(PCTRL_MSG cmdbuff,uint16_t length);
#endif
