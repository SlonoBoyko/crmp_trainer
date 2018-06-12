#pragma once

#define BROWS_PROCCESS_NAME			"multiplayer_browser_cr.exe"
#define GAME_PROCCESS_NAME			"grand_theft_auto_san_andreas.dll"
#define DLL_NAME					"CRMP_Trainer.dll"

#include <windows.h>
#include <iostream>
#include <WinInet.h>
#include <tlhelp32.h> 
#include <psapi.h> 
#include <io.h>
#include <Shellapi.h>
#include <ShlObj.h>


DWORD	GetProccessId(char *szProcName);
BOOL	ProccessIsRunning(char * szProcName);
BOOL	LibraryIsInjected(DWORD dwProcId, char *szLibName);
bool	FileExists(const char *fname);
bool	DirExists(const char *dirname);