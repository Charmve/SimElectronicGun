#include "AnoTc.h"
//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
	
u8 testdatatosend[50];	//�������ݻ���
void TestSendData(u8 *dataToSend , u8 length)//���ݷ��ͺ���
{
	u8 i;
	for(i=0;i<length;i++)
	{
		USART_SendData(USART1,dataToSend[i]);				
		while((USART1->SR&0X40)==0);
	}
}
void Test_Send_User(u16 data1)	//�����û����ݣ�������3�����ݣ��ֱ��Ӧ���̳�3������
{
	u8 _cnt=0;
	u8 sum = 0;	//����Ϊ����sumУ���ֽڣ���0xAAҲ�������ֽڣ�һֱ��sum�ֽ�ǰһ�ֽ�
	u8 i=0;
	testdatatosend[_cnt++]=0xAA;//0xAAΪ֡ͷ
	testdatatosend[_cnt++]=0x05;//0x05Ϊ���ݷ���Դ��������ο�����Э�飬���ֽ��û������������
	testdatatosend[_cnt++]=0xAF;//0xAFΪ����Ŀ�ĵأ�AF��ʾ��λ����������ο�����Э��
	testdatatosend[_cnt++]=0xF1;//0xF1����ʾ��֡ΪF1�û��Զ���֡����Ӧ�߼������F1����֡
	testdatatosend[_cnt++]=0;//���ֽڱ�ʾ���ݳ��ȣ�������=0����������ٸ�ֵ�������Ͳ����˹����㳤����
  
	testdatatosend[_cnt++]=BYTE1(data1);//��Ҫ���͵����ݷ������ͻ�����
	testdatatosend[_cnt++]=BYTE0(data1);
	
	
//	testdatatosend[_cnt++]=BYTE1(data2);//��Ҫ���͵����ݷ������ͻ�����
//	testdatatosend[_cnt++]=BYTE0(data2);
//	
//	testdatatosend[_cnt++]=BYTE1(data3);
//	testdatatosend[_cnt++]=BYTE0(data3);
 
	testdatatosend[4] = _cnt-5;//_cnt�����������ݳ��ȣ���5Ϊ��ȥ֡��ͷ5���������ֽ�
	

	for(i=0;i<_cnt;i++)
		sum += testdatatosend[i];
	testdatatosend[_cnt++]=sum;	//��sumУ�����ݷ������һ�ֽ�
 
	TestSendData(testdatatosend, _cnt);	//���÷������ݺ���
}


