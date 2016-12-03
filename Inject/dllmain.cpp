// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#undef UNICODE  
#include <cstdio>  
#include <windows.h>  
#include "../Detours/detours.h"
#pragma comment(lib, "../Detours/detours.lib")

static HANDLE (WINAPI* OLD_CreateMutexA)(
			 __in_opt LPSECURITY_ATTRIBUTES lpMutexAttributes,
			 __in     BOOL bInitialOwner,
			 __in_opt LPCSTR lpName
			 ) = CreateMutexA;  

HANDLE WINAPI NEW_CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)  
{
	HANDLE ret = OLD_CreateMutexA(lpMutexAttributes,bInitialOwner,lpName);  
	return ret;  
}

//the process  
INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)  
{     
	switch(Reason)     
	{     
	case DLL_PROCESS_ATTACH:         
		{             
			DisableThreadLibraryCalls(hDLL);             
			DetourTransactionBegin();             
			DetourUpdateThread(GetCurrentThread());             
			DetourAttach(&(PVOID&)OLD_CreateMutexA, NEW_CreateMutexA);             
			DetourTransactionCommit();         
		}         
		break;     
	case DLL_PROCESS_DETACH:         
		DetourTransactionBegin();         
		DetourUpdateThread(GetCurrentThread());         
		DetourDetach(&(PVOID&)OLD_CreateMutexA, NEW_CreateMutexA);         
		DetourTransactionCommit();         
		break;     
	case DLL_THREAD_ATTACH:     
	case DLL_THREAD_DETACH:         
		break;     
	}     
	return TRUE;  
}  


