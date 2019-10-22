#pragma once
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <process.h>
using namespace std;

#define Consumer_Number 2
#define Producer_Number 1

#define Buffer_Size 20


unsigned __stdcall ConProc(void* pArguments);
unsigned __stdcall ProProc(void* pArguments);
void printBuf(void);