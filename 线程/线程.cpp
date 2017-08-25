// �߳�.cpp : �������̨Ӧ�ó������ڵ㡣
/*���̲߳������ٽ�������Ƶ���ż���ʱֹͣ���޸�system("pause")��ʾ��,�̼߳�ͨ����̬�������ݲ���*/

#include "stdafx.h"
//#include<afxmt.h>     MFC�������ٽ���ʱ���afxmt.hͷ�ļ�

using namespace std;

DWORD WINAPI fun1(LPVOID lpparameter);
DWORD WINAPI fun2(LPVOID lpparameter);
DWORD WINAPI count1(LPVOID lpparameter);
DWORD WINAPI count2(LPVOID lpparameter);
DWORD WINAPI clock(LPVOID lpparameter);

typedef struct mytime{
	int year;
	int month;
    int day;
	int hour;
	int minute;
}mytime;

static mytime clocktime[5];
static int count=0;

CRITICAL_SECTION section1; //CCreaticalSection m_sec     //MFC��ʽ

int main()
{
	HANDLE h1,r1;
	HANDLE c1,c2;
	system("color 0A");
	InitializeCriticalSection(&section1);  //��ʼ���ٽ�������
	EnterCriticalSection(&section1);
	count=0;
	clocktime[count].year=2017;
	clocktime[count].month=6;
	clocktime[count].minute=30;
	clocktime[count].hour=12;
	clocktime[count].day=18;
	LeaveCriticalSection(&section1);
	r1=::CreateThread(NULL,0,clock,NULL,0,NULL);
	c1=::CreateThread(NULL,0,count1,NULL,0,NULL);
	c2=::CreateThread(NULL,0,count2 ,NULL,0,NULL);
	//h1=::CreateThread(NULL,0,fun1,NULL,0,NULL);
	        //printf("process 1 begin \n");
	//h2=::CreateThread(NULL,0,fun2,NULL,0,NULL);
	//printf("process 2 begin \n");
	        //h1=CreateThread(NULL,0,fun1,NULL,0,NULL);
	
   // TerminateThread(h1,1);
	//CloseHandle(h1);
	
	Sleep(11000); 
	system("pause");
	DeleteCriticalSection(&section1);
	
	CloseHandle(c1);
	CloseHandle(c2);
	return 0;
}

DWORD WINAPI fun1(LPVOID lpparameter)
{
	HANDLE h2;
   mciSendString(TEXT("open E:\\a.wav alias ring"),NULL,0,NULL);
	mciSendString(TEXT("play ring"),NULL,0,NULL);
	h2=CreateThread(NULL,0,fun2,NULL,0,NULL);
    system("pause");
	printf("sound  end \n");
	mciSendString(TEXT("stop ring"),NULL,0,NULL);
	mciSendString(TEXT("close ring"),NULL,0,NULL);

	return 1;
}

DWORD WINAPI fun2(LPVOID lpparameter)
{
	Sleep(50);
	for(int i=0;i<=19;i++)
	printf("\b");
	cout << "�밴�����ֹͣ. . . " ;
	return 2;
}

DWORD WINAPI count1(LPVOID lpparameter)
{
    for(int i=0;i<=20;i++)
	{
		EnterCriticalSection(&section1);
		cout << "�߳�1���ڼ���" << ++count <<endl;
		LeaveCriticalSection(&section1);
		Sleep(1);
	}
   return 1;
}
DWORD WINAPI count2(LPVOID lpparameter)
{
	 for(int i=0;i<=20;i++)
	{
		EnterCriticalSection(&section1);        //m_sec.Lock()    //MFC��ʽ
		cout << "�߳�2���ڼ���" << ++count <<endl;
		LeaveCriticalSection(&section1);        //m_sec.Unlock()   //MFC��ʽ
		Sleep(1);
	}
   return 2;
}

DWORD WINAPI clock(LPVOID lpparameter)
{
	EnterCriticalSection(&section1);
	int num=count;
	mytime mtime;
	if(count<5)
      mtime = clocktime[num];
	else
	{
	LeaveCriticalSection(&section1);
	cout << "count error" << endl;
	return 1;
	}
	LeaveCriticalSection(&section1);
	printf("%d %d %d %d",mtime.month,mtime.day,mtime.hour,mtime.minute);
	return 0;
}
