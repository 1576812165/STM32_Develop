#include "crc16.h"
unsigned short CRC16(unsigned char *puchMsg,unsigned short usDataLen)//CRC���ļ��㺯��
{
	unsigned char uchCRCHi = 0xFF; 
	unsigned char uchCRCLo = 0xFF;
	unsigned uIndex ; 
		while (usDataLen--) 
			{
			uIndex = uchCRCLo ^ *puchMsg++;
			uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
			uchCRCHi = auchCRCLo[uIndex];
			}
	return (uchCRCHi << 8 | uchCRCLo);//����һ��unsigned short CRC ��ֵ
}
