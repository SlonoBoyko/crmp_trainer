
#include "main.h"

void Log(const char *text, ...)
{
	if (text == NULL) return;
	va_list ap; SYSTEMTIME time;
	GetLocalTime(&time);

	FILE *log = fopen("TrainerLoader.log", "a");
	fprintf(log, "[%02d:%02d:%02d.%02d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	va_start(ap, text);
	vfprintf(log, text, ap);
	va_end(ap);

	fprintf(log, "\n");
	fclose(log);

}

DWORD CALLBACK inject_thread(PVOID)
{
	DWORD dwProcessId = 0; HANDLE hGame = NULL; char szPath[MAX_PATH];
	while (true)
	{
		do { Sleep(500); } while (!ProccessIsRunning(GAME_PROCCESS_NAME));

		dwProcessId = GetProccessId(GAME_PROCCESS_NAME); Sleep(500);
		if (LibraryIsInjected(dwProcessId, DLL_NAME)) continue;

		hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

		LPVOID LoadLibAddy = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
		LPVOID RemoteString = VirtualAllocEx(hGame, NULL, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		GetFullPathName(DLL_NAME, MAX_PATH, szPath, NULL);
		WriteProcessMemory(hGame, RemoteString, szPath, MAX_PATH, NULL);
		HANDLE hThread = CreateRemoteThread(hGame, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, RemoteString, NULL, NULL);
		WaitForSingleObject(hThread, INFINITE);
		VirtualFreeEx(hGame, RemoteString, MAX_PATH, MEM_RELEASE);
		CloseHandle(hGame); CloseHandle(hThread);

	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD dwLen = MAX_PATH, dwThreadId = NULL, dwProcessId, dwExitCode;

	if (!FileExists(DLL_NAME))
	{
		return MessageBox(HWND_DESKTOP, "Не найден модуль CRMP_Trainer.dll.", "TrainerLoader: Ошибка!", MB_ICONERROR);
	}

	if (ProccessIsRunning(BROWS_PROCCESS_NAME))
	{
		HWND hBrowsWnd = FindWindow(NULL, "CR-MP Браузер G");
		ShowWindow(hBrowsWnd, SW_SHOWNORMAL);
		SetForegroundWindow(hBrowsWnd);
		return 0;
	}

	if (ProccessIsRunning(GAME_PROCCESS_NAME))
	{
		dwProcessId = GetProccessId(GAME_PROCCESS_NAME);
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
		if (!LibraryIsInjected(dwProcessId, DLL_NAME)) {
			TerminateProcess(hProcess, EXIT_SUCCESS);
			CloseHandle(hProcess);
			dwProcessId = 0;
		}
	}

	std::string path(MAX_PATH, NULL);
	if (RegGetValue(HKEY_CLASSES_ROOT, "crmp\\shell\\Open\\command", NULL, RRF_RT_REG_SZ, NULL, &path.front(), &dwLen) == ERROR_SUCCESS)
	{
		if (path.front() == '\"') {
			path.erase(0, 1);
			path.erase(path.find('\"'));
		}
		if (path.empty() || !FileExists(path.c_str()))
			return MessageBox(HWND_DESKTOP, "Не удалось получить путь к браузеру CR-MP. "
				"Переустановка клиента CR-MP должна решить проблему.",
				"TrainerLoader: Ошибка!", MB_ICONERROR);
	} else if (MessageBox(HWND_DESKTOP, "Не удалось получить путь к папке игры.\nВыбрать путь самостоятельно?",
		"TrainerLoader: Ошибка!", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{

		HKEY hKey;
		while (true)
		{
			BROWSEINFOA bi = { HWND_DESKTOP, NULL, &path.front(), "Выбор папки CR-MP.", NULL, NULL };
			ITEMIDLIST *itls = SHBrowseForFolder(&bi);
			if (SHGetPathFromIDListA(itls, &path.front()))
			{
				path.resize(path.find(char(NULL)));
				if (!FileExists((path + "\\gta_sa.exe").c_str()))
				{
					MessageBox(HWND_DESKTOP, "В данной директории не обнаружено gta_sa.exe", "TrainerLoader: Ошибка!", MB_ICONERROR);
					continue;
				}
				if (!FileExists((path += "\\multiplayer_c\\multiplayer_browser_cr.exe").c_str())) {
					MessageBox(HWND_DESKTOP, "В данной директории не обнаружено файлов CR-MP.", "TrainerLoader: Ошибка!", MB_ICONERROR);
					continue;
				}
				if (RegCreateKey(HKEY_CLASSES_ROOT, "crmp\\shell\\Open\\command", &hKey) == ERROR_SUCCESS) {
					RegSetValue(hKey, NULL, REG_SZ, ("\"" + path + "\" %1").c_str(), MAX_PATH);
					RegCloseKey(hKey);
				}
			} else return 0;

			break;
		}
	} else return 0;

	ShellExecute(HWND_DESKTOP, "open", path.c_str(), lpCmdLine, NULL, SW_SHOWNORMAL);

	do {
		Sleep(500);
		dwProcessId = GetProccessId(BROWS_PROCCESS_NAME);
	} while (!dwProcessId);



	HANDLE hThread = CreateThread(NULL, NULL, inject_thread, NULL, NULL, &dwThreadId);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);


	do {
		Sleep(1000);
		GetExitCodeProcess(hProcess, &dwExitCode);
	} while (dwExitCode == STILL_ACTIVE);

	CloseHandle(hProcess);

	TerminateThread(hThread, EXIT_SUCCESS);
	CloseHandle(hThread);


	return dwExitCode;
}

DWORD GetProccessId(char *szProcName)
{
	HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thSnapShot == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(thSnapShot, &pe)) {
		do {
			if (strstr(pe.szExeFile, szProcName))
				return pe.th32ProcessID;
		} while (Process32Next(thSnapShot, &pe));
	}
	return NULL;
}

BOOL LibraryIsInjected(DWORD dwPID, char *szLibName) {

	HMODULE hMods[1024]; DWORD cbNeeded; BOOL bReturn = FALSE;
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
		for (int i = 0; i < (int)(cbNeeded / sizeof(HMODULE)); i++) {
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(hProcess, hMods[i], szModName, MAX_PATH)) {
				if (strstr(szModName, szLibName)) {
					CloseHandle(hProcess);
					return TRUE;
				}
			}
		}
	}
	CloseHandle(hProcess);
	return bReturn;
}

BOOL ProccessIsRunning(char *szProcName)
{
	HANDLE thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (thSnapShot == INVALID_HANDLE_VALUE) return false;

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(thSnapShot, &pe)) {
		do {
			if (strstr(pe.szExeFile, szProcName))
				return TRUE;
		} while (Process32Next(thSnapShot, &pe));
	}
	return FALSE;
}

bool FileExists(const char *fname)
{
	return _access(fname, 0) != -1;
}

bool DirExists(const char *dirname)
{
	if (dirname == NULL) return false;

	DWORD attr = GetFileAttributes(dirname);
	if (attr == INVALID_FILE_ATTRIBUTES)
		return false;

	return (attr & FILE_ATTRIBUTE_DIRECTORY);
}
