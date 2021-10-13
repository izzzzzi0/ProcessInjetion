#include "utils.h" 
#include "default.h"
//C:\\Users\\Administrator\\source\\repos\\myhack\\Release\\myhack.dll"


BOOL DLLInjection(DWORD dwPID, LPCTSTR dllPath) {
	HANDLE hProcess=NULL, hThread=NULL;
	HMODULE hModule = NULL;
	LPVOID lpParameter = NULL;
	LPTHREAD_START_ROUTINE lpStartAddress = NULL;

	//get process Handle
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if(!hProcess) {
		printError(TEXT("OpenProcess"));
		return FALSE;
	}
	//allocate buffer 
	DWORD dwSize = (_tcsclen(dllPath) + 1) * sizeof(TCHAR);
	lpParameter = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);

	//write DLL Path in Process
	if (!lpParameter) {
		printError(TEXT("allocate Buffer"));
		return FALSE;
	}

	WriteProcessMemory(hProcess, lpParameter, dllPath, dwSize, NULL);

	//get Libarary address
	hModule = GetModuleHandle(L"kernel32.dll");


	if (!hModule) {
		printError(TEXT("Get hModule"));
		return FALSE;
	}
	lpStartAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryW");

	//run Thread
	hThread = CreateRemoteThread(hProcess,NULL,0,lpStartAddress,lpParameter,0,NULL);


	if (!hThread) {
		printError(TEXT("Run Thread"));
		return FALSE;
	}

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hProcess);
	CloseHandle(hThread);
	return TRUE;
}
