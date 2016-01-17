#define WIN32_LEAN_AND_MEAN
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"killstroke";
	if (!RegisterClass(&wc))
		return 1;

	auto hWnd = CreateWindow(wc.lpszClassName, L"", 0, 0, 0, 0, 0, nullptr, nullptr, hInstance, NULL);
	if (hWnd == nullptr)
		return 2;

	if (!RegisterHotKey(hWnd, 1, MOD_ALT | MOD_CONTROL | MOD_SHIFT, 0x4B))  //0x4B is 'k'
		return 3;

	MSG msg = { nullptr };
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
		DispatchMessage(&msg);

	UnregisterHotKey(hWnd, 1);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_HOTKEY:
	{
		auto targetWnd = GetForegroundWindow();
		DWORD windowProcessId = 0;
		GetWindowThreadProcessId(targetWnd, &windowProcessId);
		auto hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, windowProcessId);
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}