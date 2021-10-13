#include "default.h"
#include "utils.h"

DWORD FindProcessID(LPCTSTR processName) {
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
		return 0xFFFFFF;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32)) {
		printError(TEXT("Process32Fisrt"));
		CloseHandle(hProcessSnap);
		return 0xFFFFFF;
	}
	do{
		LPCTSTR tmp = pe32.szExeFile;
		if (!_tcsicmp(processName, pe32.szExeFile)){
			CloseHandle(hProcessSnap);
			return pe32.th32ProcessID;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return 0xFFFFFF;
}
void printError(LPCTSTR msg){
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}