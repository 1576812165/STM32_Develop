#ifndef _CMD_QUEUE
#define _CMD_QUEUE

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "crc16.h"
/* Private macro -------------------------------------------------------------*/
#define CMD_MAX_SIZE 64           // 单条指令大小，根据需要调整，尽量设置大一些
#define QUEUE_MAX_SIZE 512        // 指令接收缓冲区大小，根据需要调整，尽量设置大一些
/* Private variables type ---------------------------------------------------------*/
typedef struct _QUEUE    /*  Cmd_queue中数据结构  */                                           
{                                                                 
    uint16_t _head;                    //队列头
    uint16_t _tail;                    //队列尾
    uint8_t _data[QUEUE_MAX_SIZE];     //队列数据缓存区
}QUEUE;

typedef struct _CMD                                             
{                                                                 
    uint8_t data[CMD_MAX_SIZE];        //单条指令内容
    uint16_t size;                 //单条指令大小
}CMD;
/* Private variables -----------------------------------------------*/
//extern uint8_t cmd_buff[CMD_MAX_SIZE];
//extern uint16_t cmd_buff_size;
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  清空指令数据
*/
void queue_reset(QUEUE *que);

/*! 
* \brief  添加指令数据
* \detial 串口接收的数据，通过此函数放入指令队列 
*  \param  _data 指令数据
*/
void queue_push(QUEUE *que,uint8_t _data);

//从队列中取一个数据
void queue_pop(QUEUE *que,uint8_t* _data);

//获取队列中有效数据个数
uint16_t queue_size(QUEUE *que);

///*! 
//*  \brief  从指令队列中取出一条完整的指令
//*  \param  cmd 指令接收缓存区
//*  \param  buf_len 指令接收缓存区大小
//*  \return  指令长度，0表示队列中无完整指令
//*/
//uint16_t queue_find_cmd(QUEUE *que,CMD *cmd,uint32_t cmd_head,uint32_t cmd_tail,uint16_t buf_len,uint8_t CRCState);

#endif
