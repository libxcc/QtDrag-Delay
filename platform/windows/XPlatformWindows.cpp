#include <platform/XPlatformCommon.h>
#include <Windows.h>


// Platform initialization
bool xcc_platform_initialize() noexcept
{
	WSADATA		vWsaData;
	WSAStartup(MAKEWORD(2, 2), &vWsaData);
	OleInitialize(nullptr);
	return true;
}

// Platform release
bool xcc_platform_release() noexcept
{
	OleUninitialize();
	WSACleanup();
	return true;
}

// Current left mouse button down state
bool xcc_platform_mouse_left_press() noexcept
{
	return (GetAsyncKeyState(VK_LBUTTON) & 0xFF00) > 0;
}
