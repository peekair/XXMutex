// FuckMutex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdio>  
#include <windows.h>  

#include "../Detours/detours.h"
#pragma comment(lib, "../Detours/detours.lib")

int APIENTRY _tWinMain(HINSTANCE hInstance,  
					   HINSTANCE hPrevInstance,  
					   LPTSTR    lpCmdLine,  
					   int       nCmdShow)  
{  
	STARTUPINFOA si;     
	PROCESS_INFORMATION pi;  
	ZeroMemory(&si, sizeof(STARTUPINFO));     
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));     
	si.cb = sizeof(STARTUPINFO);     
	char* DirPath = new char[MAX_PATH];     
	char* DLLPath = new char[MAX_PATH]; //testdll.dll     
	char* DetourPath = new char[MAX_PATH]; //detoured.dll   
	GetCurrentDirectoryA(MAX_PATH, DirPath);     
	//sprintf_s(DLLPath, MAX_PATH, "%s\\testdll.dll", DirPath);     
	sprintf_s(DetourPath, MAX_PATH, "%s\\Inject.dll", DirPath);     
	DetourCreateProcessWithDllA(
		NULL,
		"C:\\Users\\quest\\Desktop\\Flash_Tool\\Flash_Tool\\Flash_tool.exe",
		//NULL, 
		NULL,
		NULL, 
		FALSE, 
		CREATE_DEFAULT_ERROR_MODE, 
		NULL, 
		NULL,
		&si, 
		&pi, 
		"C:\\Users\\quest\\Documents\\Visual Studio 2008\\Projects\\FuckMutex\\Debug\\Inject.dll", 
		//NULL,
		NULL
		);     

	delete [] DirPath;     
	delete [] DLLPath;     
	delete [] DetourPath;     
	return 0;
}  
