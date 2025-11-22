#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

volatile int countInc = 0;
volatile int countFib = 0;
volatile int countFact = 0;

volatile bool run = true;

DWORD WINAPI IncrementThread(LPVOID lp) {
	while (run) {
		countInc++;
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI FibonachiThread(LPVOID lp) {
	while (run) {
		int f = 0;
		int f1 = 1;
		for (int i = 0; i < 100; i++) {
			int tmp = f + f1;
			f = f1;
			f1 = tmp;
		}
		countFib++;
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI FactorialThread(LPVOID lp) {
	while (run) {
		int a = 1;
		for (int i = 1; i <= 12; i++) {
			a *= i;
		}
		countFact++;
		Sleep(500);
	}
	return 0;
}

HANDLE hThreadInc = NULL;
HANDLE hThreadFib = NULL;
HANDLE hThreadFact = NULL;

int main()
{
	STARTUPINFO Incsi;
	PROCESS_INFORMATION piInc;
	hThreadInc = CreateThread(NULL, 0, IncrementThread, NULL, 0, NULL);
	if (!SetHandleInformation(hThreadInc, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
		cout << "The inhentance is not change\n";
		_getch();
		return GetLastError();
	}
	ZeroMemory(&Incsi, sizeof(STARTUPINFO));
	Incsi.cb = sizeof(STARTUPINFO);

}
