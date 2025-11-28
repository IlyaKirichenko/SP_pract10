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
	}
	return 0;
}

volatile int countStress = 0;
DWORD WINAPI StressThread(LPVOID lp) {
	volatile int a = 1;
	bool priorityChanged = false;
	while (run) {
		int a = 1;
		for (int i = 0; i <= 5000; i++) {
			a = a * 3 + 1;
		}
		countStress++;
		Sleep(1);
		if (countStress >= 1000 && !priorityChanged) {
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
			priorityChanged = true;
		}
	}
	return 0;
}

HANDLE hThreadInc = NULL;
HANDLE hThreadFib = NULL;
HANDLE hThreadFact = NULL;
HANDLE hStress = NULL;

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
		cout << "  s - start StressThread\n";
		cout << "  q - exit\n";
		cout << "IncrementThread: " << countInc << "| "<< "Priority: " << GetThreadPriority(hThreadInc) << "\n";
		cout << "FibonachiThread: " << countFib << "| " << "Priority: " << GetThreadPriority(hThreadFib) << "\n";
		cout << "FactorialThread: " << countFact << "| " << "Priority: " << GetThreadPriority(hThreadFact) << "\n";
		cout << "StressThread: ";
		if (hStress != NULL && hStress != INVALID_HANDLE_VALUE) {
			cout << countStress << " | Proirity: " << GetThreadPriority(hStress);
		}
		else {
			cout << "Not running";
		}
		cout << "\n";

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
					
					SetThreadPriority(hThreadInc, priority);
				}
				else if (key == '2') {
					
					SetThreadPriority(hThreadFib, priority);
				}
				else if (key == '3') {
				
					SetThreadPriority(hThreadFact, priority);
				}
				
				}else if (key == 's') {
					if (hStress == NULL || WaitForSingleObject(hStress, 0) == WAIT_OBJECT_0) {
						hStress = CreateThread(NULL, 0, StressThread, NULL, 0, NULL);
						SetThreadPriority(hStress, THREAD_PRIORITY_HIGHEST);
					}
			}
			else if (key == 'q') {
				run = false;
				Sleep(100);
				if (hStress) CloseHandle(hStress);
				CloseHandle(hThreadInc);
				CloseHandle(hThreadFib);
				CloseHandle(hThreadFact);
				return 0;
			}
		}
		Sleep(10);
	}
}

