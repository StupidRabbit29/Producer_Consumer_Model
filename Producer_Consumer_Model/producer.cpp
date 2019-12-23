#include"main.h"

extern HANDLE Mutex;
extern int ShareBuf[Buffer_Size];
extern int Counter;
extern int in;
extern int out;

unsigned __stdcall ProProc(void* pArguments)
{
	while (true)
	{
		//申请互斥锁
		WaitForSingleObject(Mutex, INFINITE);

		//对缓存区内数据进行操作
		if (Counter != Buffer_Size)
		{
			ShareBuf[in] = rand() % 1000;
			cout << "生产者" << *(int*)pArguments << "置入数字：" << ShareBuf[in] << endl;
			in = (in + 1) % Buffer_Size;
			Counter++;
			printBuf();
		}

		//释放互斥锁
		ReleaseMutex(Mutex);
		Sleep(rand() % 25);
	}

	//退出线程
	_endthreadex(0);
	return 0;
}