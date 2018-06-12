/*
		AUTHOR: SlonoBoyko
		LiteHack.Ru
		21.05.2018
*/


#include <main.h>

WNDPROC		g_origWndProc = NULL;
bool		key_table[0xFF];
short		mouse_scrool;

int getMouseWheel()
{
	return mouse_scrool / WHEEL_DELTA;
}

bool isEventAllowed(uint32_t vkey)
{
	if (vkey == ini.key.dialoghider) return true;
	if (menu.active && ImGui::IsAnyWindowHovered() && vkey != VK_F2) return false;

	if (!pCRMP->getInput() || !pCRMP->getDialog() || !pCRMP->getTextDraw()) return false;
	if (pCRMP->getTextDraw()->isActive || pCRMP->getInput()->iInputEnabled) return false;

	if (pCRMP->getDialog()->iDialogShowed && (pCRMP->getDialog()->iType == 
		DIALOG_STYLE_PASSWORD || pCRMP->getDialog()->iType == DIALOG_STYLE_INPUT)) 
	{
		if (pCRMP->getDialog()->pEditBox && pCRMP->getDialog()->pEditBox->bIsShowed)
		{
			if (pCRMP->getDialog()->pEditBox->bInFocusForEnter)
			{
				if ((vkey > 0xB9 && vkey < 0xDF) || (vkey > VK_HELP && vkey <= VK_DIVIDE) || vkey == VK_BACK)
					return false;
			}

		}
	}
	return true;
}

bool isKeyDown(uint8_t vkey)
{
	if (!isEventAllowed(vkey))
		return false;
	return key_table[vkey];
}

bool isKeyReleased(uint8_t vkey)
{
	if (!isEventAllowed(vkey))
		return false;
	static bool pressed[0xFF];
	if (!key_table[vkey]) {
		if (pressed[vkey])
			return !(pressed[vkey] = false);
	} else pressed[vkey] = true;

	return false;
}

bool isKeyPressed(uint8_t vkey)
{
	if (!isEventAllowed(vkey))
		return false;
	static bool pressed[0xFF];
	if (key_table[vkey]) {
		if (!pressed[vkey])
			return pressed[vkey] = true;
	} else pressed[vkey] = false;

	return false;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (gta_menu_active() || hWnd != GetForegroundWindow()) {
		memset(key_table, 0, sizeof(key_table));
		return CallWindowProc(g_origWndProc, hWnd, msg, wParam, lParam);
	}

	if (menu.active || trainer.update_available)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return 0;
	}

	switch (msg) 
	{
		case WM_MOUSEWHEEL:
			mouse_scrool += GET_WHEEL_DELTA_WPARAM(wParam);
			break;

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			key_table[VK_LBUTTON] = (msg == WM_LBUTTONDOWN);
			break;

		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			key_table[VK_RBUTTON] = (msg == WM_RBUTTONDOWN);
			break;
		
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			key_table[VK_MBUTTON] = (msg == WM_MBUTTONDOWN);
			break;

		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
			key_table[GET_XBUTTON_WPARAM(wParam) + 4] = (msg == WM_XBUTTONDOWN);
			break;

			/* :D */
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			bool			down = (msg == WM_SYSKEYDOWN || msg == WM_KEYDOWN);
			int				vkey = (int)wParam;
			uint32_t		scancode = LOBYTE(HIWORD(lParam));
			
			key_table[vkey] = down;
			
			switch (vkey)
			{
				case VK_SHIFT:
					if (scancode == MapVirtualKey(VK_LSHIFT, 0)) key_table[VK_LSHIFT] = down;
					if (scancode == MapVirtualKey(VK_RSHIFT, 0)) key_table[VK_RSHIFT] = down;
					break;

				case VK_CONTROL:
					if (scancode == MapVirtualKey(VK_LCONTROL, 0)) key_table[VK_LCONTROL] = down;
					if (scancode == MapVirtualKey(VK_RCONTROL, 0)) key_table[VK_RCONTROL] = down;
					break;

				case VK_MENU:
					if (scancode == MapVirtualKey(VK_LMENU, 0)) key_table[VK_LMENU] = down;
					if (scancode == MapVirtualKey(VK_RMENU, 0)) key_table[VK_RMENU] = down;

					break;
			}
			break;
		}

		case WM_KILLFOCUS:
			memset(key_table, 0, sizeof(key_table));
			break;

		case WM_CLOSE:
			ImGui_ImplDX9_Shutdown();
			break;
	}
	return CallWindowProc(g_origWndProc, hWnd, msg, wParam, lParam);
}
