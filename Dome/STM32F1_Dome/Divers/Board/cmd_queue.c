
/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
                             

/*! 
*  \brief  清空指令数据
*/
void queue_reset(QUEUE *que)
{
    que->_head = que->_tail = 0;
//	  que->cmd_pos = que->cmd_state = 0;
}
/*! 
* \brief  添加指令数据
* \detial 串口接收的数据，通过此函数放入指令队列 
*  \param  _data 指令数据
*/
void queue_push(QUEUE *que,uint8_t _data)//来自串口接收中断
{
    uint16_t pos = (que->_head+1)%QUEUE_MAX_SIZE;
    if(pos!=que->_tail)                                                //非满状态
    {
        que->_data[que->_head] = _data;
        que->_head = pos;
    }
}

//从队列中取一个数据
void queue_pop(QUEUE *que,uint8_t* _data)
{
    if(que->_tail!=que->_head)                                          //非空状态
    {
        *_data = que->_data[que->_tail];
        que->_tail = (que->_tail+1)%QUEUE_MAX_SIZE;
    }
}

//获取队列中有效数据个数
uint16_t queue_size(QUEUE *que)
{
    return ((que->_head+QUEUE_MAX_SIZE-que->_tail)%QUEUE_MAX_SIZE);
}
///*! 
//*  \brief  从指令队列中取出一条完整的指令
//*  \param  cmd 指令接收缓存区
//*  \param  buf_len 指令接收缓存区大小
//*  \return  指令长度，0表示队列中无完整指令
//*/
//uint16_t queue_find_cmd(QUEUE *que,CMD *cmd,uint32_t cmd_head,uint32_t cmd_tail,uint16_t buf_len,uint8_t CRCState)
//{
//    uint8_t _data = 0;
//	
//    while (queue_size(que)>0)
//    {
//        //取一个数据
//        queue_pop(que,&_data);

//        if (que->cmd_pos==0&&que->cmd_state!=cmd_head)                               //指令第一个字节必须是帧头，否则跳过
//        {
//            que->cmd_state = ((que->cmd_state<<8)|_data);
//            continue;
//        }
//        
//        if(que->cmd_pos<buf_len)                                           //防止缓冲区溢出
//            cmd->data[que->cmd_pos++] = _data;

//        que->cmd_state = ((que->cmd_state<<8)|_data);                           //拼接最后2个字节，组成一个16位整数

//        //最后4个字节与帧尾匹配，得到完整帧
//        if(que->cmd_state==cmd_tail)
//        {
//					  cmd->size = que->cmd_pos;                                       //指令字节长度
//            que->cmd_state = 0;                                            //重新检测帧尾巴
//            que->cmd_pos = 0;
//            if (CRCState == CRC16_ENABLE)
//						{
////              //去掉指令头尾EE，尾FFFCFFFF共计5个字节，只计算数据部分CRC
////               if(!CRC16(buffer+1,cmd_pos-5))                      //CRC校验
////                  return 0;

////               cmd_size -= 2;                                            //去掉CRC16（2字节）
//						}
//            return cmd->size;
//        }
//    }
//    return 0;                                                         //没有形成完整的一帧
//}

