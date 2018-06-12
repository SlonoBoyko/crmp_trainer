/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#include "main.h"

DWORD WINAPI check_update(LPVOID)
{
	DWORD dwLen;
	int iVersion;
	char szData[260];

	HINTERNET hOpen = InternetOpen("CRMP trainer [Check Version]", INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
	HINTERNET hInetUrl = InternetOpenUrl(hOpen, PATH_TO_CHECKING_SCRIPT, NULL, 0,
		INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_RELOAD, 0);

	if (InternetReadFile(hInetUrl, szData, sizeof(szData) - 1, &dwLen))
	{
		szData[dwLen] = '\0';
		if ((iVersion = atoi(szData)) != NULL)
		{
			if (iVersion > TRAINER_VERSION) {
				trainer.update_available = true;
			}
		}
	}

	InternetCloseHandle(hInetUrl);
	InternetCloseHandle(hOpen);

	ExitThread(EXIT_SUCCESS);
}

void EnableWindowsAero()
{
	CHAR szFile[MAX_PATH]; 
	GetSystemDirectory(szFile, MAX_PATH);
	strcat_s(szFile, "\\dwmapi.dll");

	if (access(szFile, 0) == -1) return;
	HMODULE hDwmApi = LoadLibrary(szFile);
	if (hDwmApi == NULL) return;

	DWORD dwFunc = (DWORD)GetProcAddress(hDwmApi, "DwmEnableComposition");
	HRESULT hResult = func::stdcall<HRESULT>(dwFunc, TRUE);
	if (FAILED(hResult)) return EnableWindowsAero();

	FreeLibrary(hDwmApi);
}

void mainThread(LPVOID hModule)
{ 
	hThisModule = static_cast<HMODULE>(hModule);

	std::string path(szWorkingDirectory);
	path.append("CRMP_Trainer.ini");
	strnset(szIniFileName, 0, MAX_PATH);
	path.copy(szIniFileName, path.size());
	
	get_ini_file_settings();

	BYTE bMajorVersion = LOBYTE(LOWORD(GetVersion()));
	if (menu.restore_aero && bMajorVersion == 6)
		EnableWindowsAero(); 

	pCRMP			= new CCRMP();
	pD3DHook		= new CD3DHook();
	pGame			= new CGameSA();

	// Disable Loading Screen Patch
	mem::copy((PVOID)0x590AC0, "\xC3", 1); 
	mem::copy((PVOID)0x590D9F, "\xC3\x90\x90\x90\x90", 5);

	while (!pCRMP->Init()) Sleep(400);

	pPools = pGame->GetPools();
	pPedSelf = pPools->AddPed(*(DWORD **)ACTOR_POINTER_SELF);
	pPedSelf->SetHealth(100.0f);

	InitSmallGamePools();
	InstallAllHooks();
	InitScripting();

	registerSampCommand();
	
	// Anticrasher
	mem::set((PVOID)(pCRMP->getBase() + 0x5A1D9), 0x90, 5);
	mem::copy((PVOID)0x82C5CC, "\xC9\xC3", 2);

	// Stream memory fix
	MEMORYSTATUS mState; 
	GlobalMemoryStatus(&mState);
	mem::copy((PVOID)0x8A5A80, &mState.dwTotalPhys, 4);
	mem::set((PVOID)0x5BCD50, 0x90, 5);
	mem::set((PVOID)0x5BCD78, 0x90, 5);
	mem::set((PVOID)0x5B8E64, 0x90, 10);

	// Multiproccess
	mem::set((PVOID)0x74872D, 0x90, 9);
	mem::set((PVOID)0x406946, 0x00, 4);

	// Framelimiter patch
	mem::set((PVOID)0xBAB318, 0x0, 1);
	mem::set((PVOID)0x53E94C, 0x0, 1);

	srand(time(NULL));

	pCRMP->getChat()->addMessageToChat(D3DCOLOR_XRGB(0x00, 0x88, 0xFF), "CRMP Trainer by SlonoBoyko for {FFAA00}LiteHack.Ru");

	while (pCRMP->getPlayers()->iLocalPlayerScore) Sleep(400);
	
	Sleep(15000);

	CreateThread(NULL, NULL, check_update, NULL, NULL, NULL);

	
//	pCRMP->getInfo()->showGameText("~r~Lite~b~Hack~y~.Ru", 2000, 5);

	return _endthread();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	switch (dwReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);

		DWORD dwLen = GetModuleFileName(hModule, szWorkingDirectory, MAX_PATH);
		strnset(&szWorkingDirectory[dwLen - strlen(DLL_NAME)], '\0', MAX_PATH);
		_beginthread(mainThread, 0, hModule);
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
