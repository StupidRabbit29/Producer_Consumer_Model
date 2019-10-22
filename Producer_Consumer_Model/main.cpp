#include"main.h"

HANDLE Mutex;
int ShareBuf[Buffer_Size];
int Counter = 0;
int in = 0;
int out = 0;

int main()
{
	HANDLE Cthread[Consumer_Number];
	HANDLE Pthread[Producer_Number];

	Mutex = CreateMutex(NULL, FALSE, NULL);
	memset(ShareBuf, 0, sizeof(ShareBuf));

	for (int j = 0; j < Producer_Number; j++)
		Pthread[j] = (HANDLE) _beginthreadex(NULL, 0, ProProc, &j, 0, NULL);

	for (int i = 0; i < Consumer_Number; i++)
		Cthread[i] = (HANDLE) _beginthreadex(NULL, 0, ConProc, &i, 0, NULL);

	WaitForMultipleObjects(Consumer_Number, Cthread, TRUE, INFINITE);
	WaitForMultipleObjects(Producer_Number, Pthread, TRUE, INFINITE);
	for (int i = 0; i < Consumer_Number; i++)
		CloseHandle(Cthread[i]);

	for (int j = 0; j < Producer_Number; j++)
		CloseHandle(Pthread[j]);

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