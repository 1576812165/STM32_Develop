
/* Includes ------------------------------------------------------------------*/
#include "cmd_queue.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
                             

/*! 
*  \brief  ���ָ������
*/
void queue_reset(QUEUE *que)
{
    que->_head = que->_tail = 0;
//	  que->cmd_pos = que->cmd_state = 0;
}
/*! 
* \brief  ���ָ������
* \detial ���ڽ��յ����ݣ�ͨ���˺�������ָ����� 
*  \param  _data ָ������
*/
void queue_push(QUEUE *que,uint8_t _data)//���Դ��ڽ����ж�
{
    uint16_t pos = (que->_head+1)%QUEUE_MAX_SIZE;
    if(pos!=que->_tail)                                                //����״̬
    {
        que->_data[que->_head] = _data;
        que->_head = pos;
    }
}

//�Ӷ�����ȡһ������
void queue_pop(QUEUE *que,uint8_t* _data)
{
    if(que->_tail!=que->_head)                                          //�ǿ�״̬
    {
        *_data = que->_data[que->_tail];
        que->_tail = (que->_tail+1)%QUEUE_MAX_SIZE;
    }
}

//��ȡ��������Ч���ݸ���
uint16_t queue_size(QUEUE *que)
{
    return ((que->_head+QUEUE_MAX_SIZE-que->_tail)%QUEUE_MAX_SIZE);
}
///*! 
//*  \brief  ��ָ�������ȡ��һ��������ָ��
//*  \param  cmd ָ����ջ�����
//*  \param  buf_len ָ����ջ�������С
//*  \return  ָ��ȣ�0��ʾ������������ָ��
//*/
//uint16_t queue_find_cmd(QUEUE *que,CMD *cmd,uint32_t cmd_head,uint32_t cmd_tail,uint16_t buf_len,uint8_t CRCState)
//{
//    uint8_t _data = 0;
//	
//    while (queue_size(que)>0)
//    {
//        //ȡһ������
//        queue_pop(que,&_data);

//        if (que->cmd_pos==0&&que->cmd_state!=cmd_head)                               //ָ���һ���ֽڱ�����֡ͷ����������
//        {
//            que->cmd_state = ((que->cmd_state<<8)|_data);
//            continue;
//        }
//        
//        if(que->cmd_pos<buf_len)                                           //��ֹ���������
//            cmd->data[que->cmd_pos++] = _data;

//        que->cmd_state = ((que->cmd_state<<8)|_data);                           //ƴ�����2���ֽڣ����һ��16λ����

//        //���4���ֽ���֡βƥ�䣬�õ�����֡
//        if(que->cmd_state==cmd_tail)
//        {
//					  cmd->size = que->cmd_pos;                                       //ָ���ֽڳ���
//            que->cmd_state = 0;                                            //���¼��֡β��
//            que->cmd_pos = 0;
//            if (CRCState == CRC16_ENABLE)
//						{
////              //ȥ��ָ��ͷβEE��βFFFCFFFF����5���ֽڣ�ֻ�������ݲ���CRC
////               if(!CRC16(buffer+1,cmd_pos-5))                      //CRCУ��
////                  return 0;

////               cmd_size -= 2;                                            //ȥ��CRC16��2�ֽڣ�
//						}
//            return cmd->size;
//        }
//    }
//    return 0;                                                         //û���γ�������һ֡
//}

