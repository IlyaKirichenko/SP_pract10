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
void ShowStats() {
	int startInc = countInc;
	int startFib = countFib;
	int startFact = countFact;

	int incDone = countInc - startInc;
	int fibDone = countFib - startFib;
	int factDone = countFact - startFact;

	cout << "IncrementThread: " << incDone << " итераций\n";
	cout << "FibonachiThread: " << fibDone << " итераций\n";
	cout << "FactorialThread: " << factDone << " итераций\n";
}

HANDLE hThreadInc = NULL;
HANDLE hThreadFib = NULL;
HANDLE hThreadFact = NULL;
int main()
{
	hThreadInc = CreateThread(NULL, 0, IncrementThread, NULL, 0, NULL);
	if (!SetHandleInformation(hThreadInc, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
		cout << "The inhentance is not change\n";
		_getch();
		return GetLastError();
	}
	hThreadFib = CreateThread(NULL, 0, FibonachiThread, NULL, 0, NULL);
	if (!SetHandleInformation(hThreadFib, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
		cout << "The inhentance is not change\n";
		_getch();
		return GetLastError();
	}
	hThreadFact = CreateThread(NULL, 0, FactorialThread, NULL, 0, NULL);
	if (!SetHandleInformation(hThreadFact, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) {
		cout << "The inhentance is not change\n";
		_getch();
		return GetLastError();
	}
	SetThreadPriority(hThreadInc, THREAD_PRIORITY_BELOW_NORMAL);
	SetThreadPriority(hThreadFib, THREAD_PRIORITY_NORMAL);
	SetThreadPriority(hThreadFact, THREAD_PRIORITY_ABOVE_NORMAL);

	cout << "  1 — изменить приоритет IncrementThread\n";
	cout << "  2 — изменить приоритет FibonachiThread\n";
	cout << "  3 — изменить приоритет FactorialThread\n";
	cout << "  q — выход\n";

	while (run) {
		if (_kbhit()) {
			char key = _getch();
			if (key == '1' || key == '2' || key == '3') {
				cout << "\nНовый приоритет (0-5): ";
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
				ShowStats();
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
