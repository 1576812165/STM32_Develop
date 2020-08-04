#ifndef SCREEN_H
#define SCREEN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
/* Private macro -------------------------------------------------------------*/
#define RED 0xF800
#define YELLOW 0xFFE0
#define BLACK 0x0000
#define WHITE 0xFFFF

#define NOTIFY_CONTROL             0XB1  //�ؼ�����֪ͨ
#define MSG_GET_CURRENT_SCREEN     0X01  //����ID�仯֪ͨ
#define NOTIFY_HandShake           0X55  //����֪ͨ

/* Private variables type ---------------------------------------------------------*/
enum CtrlType
{
    kCtrlUnknown=0x0,
    kCtrlButton=0x10,                     //��ť
    kCtrlText=0x11,                       //�ı�
    kCtrlProgress,                        //������
    kCtrlSlider,                          //������
    kCtrlMeter,                           //�Ǳ�
    kCtrlDropList,                        //�����б�
    kCtrlRTC,                             //ʱ����ʾ
    kCtrlGraph,                           //����ͼ�ؼ�
    kCtrlTable,                           //���ؼ�
    kCtrlMenu,                            //�˵��ؼ�
    kCtrlSelector,                        //ѡ��ؼ�
    kCtrlQRCode,                          //��ά��
};

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint8_t    cmd_head;                    //֡ͷ
    uint8_t    cmd_type;                    //��������(UPDATE_CONTROL)   1���ֽ� 
    uint8_t    ctrl_msg;                    //CtrlMsgType-ָʾ��Ϣ������  1���ֽ� 
    uint16_t   screen_id;                   //������Ϣ�Ļ���ID  2���ֽ�
    uint16_t   control_id;                  //������Ϣ�Ŀؼ�ID  2���ֽ�
    uint8_t    control_type;                //�ؼ�����  1���ֽ�
    uint8_t    param[256];                  //�ɱ䳤�Ȳ��������256���ֽ�
    uint8_t    cmd_tail[4];                 //֡β 4���ֽ�
}CTRL_MSG,*PCTRL_MSG;

#pragma pack(pop)
/* Private variables -----------------------------------------------*/
extern QUEUE screen_que;      //ָ�����
extern CMD screen_cmd;        //����ָ��
extern uint8_t station_order[22];
extern uint16_t current_screen_id;
/* Private functions ---------------------------------------------------------*/

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
uint16_t ScreenQueue_Find_Cmd(QUEUE *que,CMD *cmd,uint16_t buf_len);

void memsett(void* s, uint8_t c, uint8_t n);//����������ַ�����

void USARTScreenCheck(void);//��⴮����״̬����

void GetNowScreen_id(void);//��õ�ǰ�����

void ChangePage(uint16_t screen_id);//�л�����

void SetControlCmd(uint16_t screen_id,uint16_t control_id,FunctionalState NewState);//��ֹ/ʹ�ܿؼ�

//����������ʾ���������ı���1Ϊ��ʾ0Ϊ����
void SetTextDisplayCmd(uint16_t screen_id,uint16_t control_id,FunctionalState NewState);

//���������Ƿ�����ı���ʾ��1Ϊʹ��0Ϊ��ֹ
void TextUpdataEnable(FunctionalState NewState);

void SetTextValue(uint16_t screen_id,uint16_t control_id,int32_t number);//�����ı��ؼ�ֵ

void SetTextStrings(uint16_t screen_id,uint16_t control_id,uint8_t *str);//�����ı��ؼ���ʾ�ַ���

void SetControlForeColor(uint16_t screen_id,uint16_t control_id,uint16_t color);//���ÿؼ�ǰ��ɫ 

void SetProgressValue(uint16_t screen_id,uint16_t control_id,uint32_t value);//���ý���ֵ

/*! 
*  \brief     ���ð�ť״̬
*  \param  screen_id ����ID
*  \param  control_id �ؼ�ID
*  \param  value ��ť״̬
*/
void SetButtonValue(uint16_t screen_id,uint16_t control_id,uint8_t state);

void ScreenInitDisplay(void);

void PowerAndIoSensorDataDisplay(void);

void ScreenCMD_Analyze(PCTRL_MSG cmdbuff,uint16_t length);
#endif
