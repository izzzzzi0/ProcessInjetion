#include "windows.h"
#include "tchar.h"
#include "stdio.h"

#define DEL_DLL_PATH ("C:\\Users\\Administrator\\source\\repos\\myhack\\Release\\myhack.dll")

DWORD FindProcessID(LPCTSTR ProcessName);
BOOL Inject(DWORD hwPID, LPCTSTR DllPath);


int _tmain(int argc, TCHAR* argv[]) {
	if (argc != 2) {
		_tprintf(L"Please INPUT Process Name!!");
		return 1;
	}

	DWORD dwPID = 0xFFFFFF;

}

add


