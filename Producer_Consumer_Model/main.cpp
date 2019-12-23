#include"main.h"
#include<sstream>

HANDLE Mutex;
int ShareBuf[Buffer_Size];
int Counter = 0;
int in = 0;
int out = 0;

int Consumer_Number = 3;
int Producer_Number = 4;

//处理用户输入
void Getarg(int argc, char* argv[])
{
	if (argc == 3)
	{
		stringstream ss;
		ss << argv[1] << ' ' << argv[2];
		ss >> Consumer_Number >> Producer_Number;
	}
}

int main(int argc, char* argv[])
{
	Getarg(argc, argv);
	//cout << Consumer_Number << Producer_Number << endl;
	HANDLE* Cthread = new HANDLE[Consumer_Number];
	HANDLE* Pthread = new HANDLE[Producer_Number];
	int* Cid = new int[Consumer_Number];
	int* Pid = new int[Producer_Number];

	Mutex = CreateMutex(NULL, FALSE, NULL);
	memset(ShareBuf, 0, sizeof(ShareBuf));

	//产生生产者线程
	for (int j = 0; j < Producer_Number; j++)
	{
		Pid[j] = 100 + j;
		Pthread[j] = (HANDLE)_beginthreadex(NULL, 0, ProProc, &Pid[j], 0, NULL);
	}

	//产生消费者线程
	for (int i = 0; i < Consumer_Number; i++)
	{
		Cid[i] = 200 + i;
		Cthread[i] = (HANDLE)_beginthreadex(NULL, 0, ConProc, &Cid[i], 0, NULL);
	}

	//等待所有生产者和消费者线程结束
	WaitForMultipleObjects(Consumer_Number, Cthread, TRUE, INFINITE);
	WaitForMultipleObjects(Producer_Number, Pthread, TRUE, INFINITE);
	for (int i = 0; i < Consumer_Number; i++)
		CloseHandle(Cthread[i]);
	for (int j = 0; j < Producer_Number; j++)
		CloseHandle(Pthread[j]);

	delete[] Cthread;
	delete[] Pthread;
	delete[] Cid;
	delete[] Pid;

	return 0;
}

void printBuf(void)
{
	for (int i = 0; i < Buffer_Size; i++)
	{
		if (i < in && i >= out || i <= in && in <= out && Counter>0 || i >= out && in <= out && Counter > 0)
			cout << ShareBuf[i] << ' ';
		else
			cout << "**" << ' ';
	}
	cout << endl;
}