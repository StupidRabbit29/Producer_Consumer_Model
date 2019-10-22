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
		//WaitForSingleObject(Mutex, INFINITE);

		while (Counter == Buffer_Size)
			;

		ShareBuf[in] = rand() % 1000;
		cout << "生产者" << *(int*)pArguments << "置入数字：" << ShareBuf[in] << endl;
		in = (in + 1) % Buffer_Size;
		Counter++;
		printBuf();

		//ReleaseMutex(Mutex);
		Sleep(rand() % 25);
	}

	_endthreadex(0);
	return 0;
}