/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/

#pragma once

LRESULT CALLBACK					WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool								isKeyDown(uint8_t key);
bool								isKeyPressed(uint8_t key);
bool								isKeyReleased(uint8_t vkey);
int									getMouseWheel(void);

extern WNDPROC						g_origWndProc;
