// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
#include <Windows.h>
#include <stdio.h>

DWORD WINAPI ShowMessage(LPVOID lParam) {
    MessageBox(NULL, TEXT("You are stupid!!"), TEXT("MessageBox"), MB_OK);
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    HANDLE hThread = NULL;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        OutputDebugString(L"myhack.dll Injection!!");
        hThread = CreateThread(NULL, 0, ShowMessage, NULL, 0, NULL);
        CloseHandle(hThread);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


