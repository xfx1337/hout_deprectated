#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <future>
#include <math.h>
//web server menu
//#include <WinSock2.h>
//#include <WS2tcpip.h>

// self made

#include "Utils.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &margin);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LoCmdLine, INT nCmdShow) {
	ProcessId = Driver.GetTargetPid();
	ClientAddress = Driver.GetClientModule();
	EngineAddress = Driver.GetEngineModule();
	Driver.ParseOffsets(); // parse offsets on driver-side
	Offsets::LoadOffsets(Driver); // parse offsets on local side
	Config::ImportConfig("config.json");

	RECT rc;
	const HWND desktop = GetDesktopWindow();
	if (desktop != nullptr) {
		GetWindowRect(desktop, &rc);
		Config::width = rc.right - rc.left;
		Config::height = rc.bottom - rc.top;
	}
	else {
		ExitProcess(0);
	}
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = HBRUSH(RGB(0, 0, 0));
	wc.lpszClassName = " ";

	RegisterClassEx(&wc);
	//overlay = GetDesktopWindow();
	overlay = CreateWindowEx(0, " ", " ", WS_EX_TOPMOST | WS_POPUP, rc.left, rc.top, Config::width, Config::height, nullptr, nullptr, hInstance, nullptr);
	SetWindowLong(overlay, GWL_EXSTYLE, GetWindowLong(overlay, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetLayeredWindowAttributes(overlay, RGB(0, 0, 0), 255, /*LWA_COLORKEY |*/ LWA_ALPHA);
	ShowWindow(overlay, nCmdShow);

	init3D(overlay);
	MSG msg;


	std::thread lpt(&GetLocalPlayerThread);
	std::thread bhop(&BhopThread);
	std::thread antiflash(&AntiFlashThread);
	std::thread trigger(&TriggerBotThread);
	std::thread rcs(&RCSThread);
	std::thread keys(&ReadKeysThread);


	while (true) {
		SetWindowPos(overlay, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			render();
		}
	}
}