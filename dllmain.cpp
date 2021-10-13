// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"


DWORD WINAPI ThreadProc(LPVOID lParam) {
    MessageBox(NULL, L"You are stupid", L"You are stupid", NULL);
    Sleep(1000);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    HANDLE  hThread = NULL;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
        if (!hThread) {
            break;
        }
        CloseHandle(hThread);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

