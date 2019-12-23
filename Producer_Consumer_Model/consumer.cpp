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
		//申请互斥锁
		WaitForSingleObject(Mutex, INFINITE);

		//对缓存区内数据进行操作
		if (Counter != 0)
		{
			cout << "消费者" << *(int*)pArguments << "取出数字：" << ShareBuf[out] << endl;
			out = (out + 1) % Buffer_Size;
			Counter--;
			printBuf();
		}

		//释放互斥锁
		ReleaseMutex(Mutex);
		Sleep(rand() % 50);
	}

	//退出线程
	_endthreadex(0);
	return 0;
}