#include"main.h"

extern HANDLE Mutex;
extern int ShareBuf[Buffer_Size];
extern int Counter;
extern int in;
extern int out;

unsigned __stdcall ConProc(void* pArguments)
{
	while (true)
	{
		//���뻥����
		WaitForSingleObject(Mutex, INFINITE);

		//�Ի����������ݽ��в���
		if (Counter != 0)
		{
			cout << "������" << *(int*)pArguments << "ȡ�����֣�" << ShareBuf[out] << endl;
			out = (out + 1) % Buffer_Size;
			Counter--;
			printBuf();
		}

		//�ͷŻ�����
		ReleaseMutex(Mutex);
		Sleep(rand() % 50);
	}

	//�˳��߳�
	_endthreadex(0);
	return 0;
}