/***************   writer:shopping.w   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit LED1 = P0^0;
sbit LED2 = P0^3;
sbit K1 = P1^0;	  //����һ������

void Delay(uint x)	 //��ʱ
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void putc_to_SerialPort(uchar c)  //��������
{
 	SBUF = c;	//SBUF�Ĵ��������ڴ洢����
	while(TI == 0);	 //���ݷ��ͳɹ�ʱ��TI��Ӳ���Զ���1
	TI = 0;	  //��Ҫ����ֶ���0���ȴ��´����ݵĵ���
}

void main()
{	//I2CͨѶ��ʼ��
 	uchar Operation_NO = 0;
	SCON = 0x40;
	TMOD = 0x20;
	PCON = 0x00;
	TH1 = 0xfd;	  //���ø߰�λ
	TL1 = 0xfd;	  //���õͰ�λ
	TI = 0;		  //TI���ͱ�־λ��0
	TR1 = 1;	  //������ͨѶ
	while(1)
	{
	 	if(K1 == 0)
		{
		 	while(K1==0);
			Operation_NO=(Operation_NO+1)%4;
		}
		switch(Operation_NO)
		{
		 	case 0:
					LED1=LED2=1; break;
			case 1:
					putc_to_SerialPort('A');
					LED1=~LED1;LED2=1;break;
			case 2:
					putc_to_SerialPort('B');
					LED2=~LED2;LED1=1;break;
			case 3:
					putc_to_SerialPort('C');
					LED1=~LED1;LED2=LED1;break;
		}
		Delay(10);
	}
}