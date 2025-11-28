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
		Sleep(10);
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
		Sleep(10);
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
		Sleep(10);
	}
	return 0;
}

HANDLE hThreadInc = NULL;
HANDLE hThreadFib = NULL;
HANDLE hThreadFact = NULL;

int main()
{
	hThreadInc = CreateThread(NULL, 0, IncrementThread, NULL, 0, NULL);
	if (!SetHandleInformation(hThreadInc, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
		cout << "The thread is not change\n";
		_getch();
		return GetLastError();
	}
	hThreadFib = CreateThread(NULL, 0, FibonachiThread, NULL, 0, NULL);
	if (!SetHandleInformation(hThreadFib, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
		cout << "The thread is not change\n";
		_getch();
		return GetLastError();
	}
	hThreadFact = CreateThread(NULL, 0, FactorialThread, NULL, 0, NULL);
	if (!SetHandleInformation(hThreadFact, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
		cout << "The thread is not change\n";
		_getch();
		return GetLastError();
	}
	SetThreadPriority(hThreadInc, THREAD_PRIORITY_LOWEST);
	SetThreadPriority(hThreadFib, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hThreadFact, THREAD_PRIORITY_HIGHEST);

	


	while (run) {
		system("cls");
		cout << "  1 - change IncrementThread\n";
		cout << "  2 - change FibonachiThread\n";
		cout << "  3 - change FactorialThread\n";
		cout << "  q - exit\n";
			cout << "IncrementThread: " << countInc << "\n";
			cout << "FibonachiThread: " << countFib << "\n";
			cout << "FactorialThread: " << countFact << "\n";
			//ShowStats();
			Sleep(1000);
		if (_kbhit()) {
			char key = _getch();
			if (key == '1' || key == '2' || key == '3') {
				cout << "\nNew (0-5): ";
				char p = _getch();
				cout << p << endl;

				int priority;
				if (p == '0') {
					priority = THREAD_PRIORITY_IDLE;
				}
				else if (p == '1') {
					priority = THREAD_PRIORITY_LOWEST;
				}
				else if (p == '2') {
					priority = THREAD_PRIORITY_BELOW_NORMAL;
				}
				else if (p == '3') {
					priority = THREAD_PRIORITY_NORMAL;
				}
				else if (p == '4') {
					priority = THREAD_PRIORITY_ABOVE_NORMAL;
				}
				else if (p == '5') {
					priority = THREAD_PRIORITY_HIGHEST;
				}
				else {
					priority = THREAD_PRIORITY_NORMAL;
				}

				if (key == '1') {
					GetThreadPriorityBoost(hThreadInc,&priority);
					SetThreadPriorityBoost(hThreadInc, priority);
				}
				else if (key == '2') {
					GetThreadPriorityBoost(hThreadFib, &priority);
					SetThreadPriorityBoost(hThreadFib, priority);
				}
				else if (key == '3') {
					GetThreadPriorityBoost(hThreadFact, &priority);
					SetThreadPriorityBoost(hThreadFact, priority);
				}
				//ShowStats();
			}
			else if (key == 'q') {
				run = false;
				Sleep(100);
				CloseHandle(hThreadInc);
				CloseHandle(hThreadFib);
				CloseHandle(hThreadFact);
				return 0;
			}
		}
		Sleep(10);
	}
}


