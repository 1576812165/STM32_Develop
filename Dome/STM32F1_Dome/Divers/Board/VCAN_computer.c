/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2015,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       VCAN_computer.c
 * @brief      ɽ��๦�ܵ���������λ����������
 * @author     ɽ��Ƽ�
 * @version    v5.2.2
 * @date       2015-03-24
 */
//#define USART USART1


/*
 * ����ͷ�ļ�
 */
//#include "common.h"
//#include "MK60_uart.h"
#include "VCAN_computer.h"


float sendware_buffer[4] = {0};

void uart_send_data(uint8_t *buf, uint16_t len,USART_TypeDef *USART)
{
	uint16_t i;
	
	while((USART_GetFlagStatus(USART, USART_FLAG_TC) == RESET));//�ȴ����ڷ�����Ϸ�ֹ��ʧ��һ���ֽ� 
	for(i=0;i<len;i++)
	{  
		USART_SendData(USART,buf[i]);      		//дDR,����1����������
		while((USART_GetFlagStatus(USART, USART_FLAG_TC) == RESET));//�ȴ����ڷ������
	}	
}

/*!
 *  @brief      ɽ��๦�ܵ���������λ��������ͷ��ʾ����
 *  @param      imgaddr    ͼ����ʼ��ַ
 *  @param      imgsize    ͼ��ռ�ÿռ�Ĵ�С
 *  @since      v5.0
*  Sample usage:
             �����÷��ο�������:
            ��ɽ������ͷ��ӥ����λ�����̺�΢��Ч�� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6242&ctid=27
 */
void vcan_sendimg(void *imgaddr, uint32_t imgsize,USART_TypeDef *USART)
{
#define CMD_IMG     1
    uint8_t cmdf[2] = {CMD_IMG, ~CMD_IMG};    //ɽ����λ�� ʹ�õ�����
    uint8_t cmdr[2] = {~CMD_IMG, CMD_IMG};    //ɽ����λ�� ʹ�õ�����

    uart_send_data(cmdf, sizeof(cmdf),USART);    //�ȷ�������

    uart_send_data((uint8_t *)imgaddr, imgsize,USART); //�ٷ���ͼ��

    uart_send_data(cmdr, sizeof(cmdr),USART);    //�ȷ�������
}


/*!
 *  @brief      ɽ��๦�ܵ���������λ��������CCD��ʾ����
 *  @param      ccdaddr    CCDͼ����ʼ��ַ
 *  @param      ccdsize    CCDͼ��ռ�ÿռ�Ĵ�С
 *  @since      v5.0
*  Sample usage:
             �����÷��ο�������:
            ��ɽ������CCD����λ����ʾ���̺ͳ���ǲɼ�Ч�� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6340&ctid=27
 */
void vcan_sendccd(void *ccdaddr, uint32_t ccdsize,USART_TypeDef *USART)
{
#define CMD_CCD     2
    uint8_t cmdf[2] = {CMD_CCD, ~CMD_CCD};    //��ͷ����
    uint8_t cmdr[2] = {~CMD_CCD, CMD_CCD};    //��β����

    uart_send_data(cmdf, sizeof(cmdf),USART);    //�ȷ�������

    uart_send_data((uint8_t *)ccdaddr, ccdsize,USART); //�ٷ���ͼ��

    uart_send_data(cmdr, sizeof(cmdr),USART);    //�ٷ�������
}


/*!
 *  @brief      ɽ��๦�ܵ���������λ��������ʾ������ʾ����
 *  @param      wareaddr    ����������ʼ��ַ
 *  @param      waresize    ��������ռ�ÿռ�Ĵ�С
 *  @since      v5.0
*  Sample usage:
             �����÷��ο�������:
            ��ɽ�����ϡ������Ǻͼ��ٶ� ��λ����ʾ���� - ���ܳ�������
             http://vcan123.com/forum.php?mod=viewthread&tid=6253&ctid=27
 */
void vcan_sendware(void *wareaddr, uint32_t waresize,USART_TypeDef *USART)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //���ڵ��� ʹ�õ�ǰ����
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //���ڵ��� ʹ�õĺ�����

    uart_send_data(cmdf, sizeof(cmdf),USART);    //�ȷ���ǰ����
    uart_send_data((uint8_t *)wareaddr, waresize,USART);    //��������
    uart_send_data(cmdr, sizeof(cmdr),USART);    //���ͺ�����
}
