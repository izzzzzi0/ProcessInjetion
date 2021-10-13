#include "utils.h"
#include "default.h"
#include "injection.h"


int main(int argc, TCHAR* argv[]) {
	if (argc != 2) {
		_tprintf(TEXT("Please INPUT Process Name!!"));
		return 1;
	}

	DWORD dwPID = 0xFFFFFF;
	dwPID = FindProcessID(L"notepad.exe");
	if (dwPID == 0xFFFFFF) {
		_tprintf(TEXT("Don't Find Process!!"));
		return 0;
	}

	if (DLLInjection(dwPID,L"C:\\Users\\Administrator\\source\\repos\\processInjetion\\myhack.dll")) {
		_tprintf(TEXT("InjectionDLL %s sucess!!\n"), L"notepad.exe");
	}
	else {
		_tprintf(TEXT("InjectionDLL %s failed!!\n"), L"notepad.exe");
	}

	return 0;

}