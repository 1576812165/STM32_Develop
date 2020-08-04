#ifndef _CMD_QUEUE
#define _CMD_QUEUE

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "crc16.h"
/* Private macro -------------------------------------------------------------*/
#define CMD_MAX_SIZE 64           // ����ָ���С��������Ҫ�������������ô�һЩ
#define QUEUE_MAX_SIZE 512        // ָ����ջ�������С��������Ҫ�������������ô�һЩ
/* Private variables type ---------------------------------------------------------*/
typedef struct _QUEUE    /*  Cmd_queue�����ݽṹ  */                                           
{                                                                 
    uint16_t _head;                    //����ͷ
    uint16_t _tail;                    //����β
    uint8_t _data[QUEUE_MAX_SIZE];     //�������ݻ�����
}QUEUE;

typedef struct _CMD                                             
{                                                                 
    uint8_t data[CMD_MAX_SIZE];        //����ָ������
    uint16_t size;                 //����ָ���С
}CMD;
/* Private variables -----------------------------------------------*/
//extern uint8_t cmd_buff[CMD_MAX_SIZE];
//extern uint16_t cmd_buff_size;
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  ���ָ������
*/
void queue_reset(QUEUE *que);

/*! 
* \brief  ���ָ������
* \detial ���ڽ��յ����ݣ�ͨ���˺�������ָ����� 
*  \param  _data ָ������
*/
void queue_push(QUEUE *que,uint8_t _data);

//�Ӷ�����ȡһ������
void queue_pop(QUEUE *que,uint8_t* _data);

//��ȡ��������Ч���ݸ���
uint16_t queue_size(QUEUE *que);

///*! 
//*  \brief  ��ָ�������ȡ��һ��������ָ��
//*  \param  cmd ָ����ջ�����
//*  \param  buf_len ָ����ջ�������С
//*  \return  ָ��ȣ�0��ʾ������������ָ��
//*/
//uint16_t queue_find_cmd(QUEUE *que,CMD *cmd,uint32_t cmd_head,uint32_t cmd_tail,uint16_t buf_len,uint8_t CRCState);

#endif
