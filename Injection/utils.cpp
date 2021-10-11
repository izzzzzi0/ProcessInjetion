#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <atlstr.h>  

#include "utils.h"

// msdn : https://docs.microsoft.com/ko-kr/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes

DWORD FindProcessID(LPCTSTR ProcessName) {
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
		return 0;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32)) {
		printError(TEXT("Process32Fisrt"));
		CloseHandle(hProcessSnap);
		return 0;
	}

	do
	{
		CString pe32ProccessName = pe32.szExeFile;
		if (!pe32ProccessName.CompareNoCase(ProcessName)) {
			CloseHandle(hProcessSnap);
			return pe32.th32ParentProcessID;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return(0);
}


void printError(LPCTSTR msg)
{
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