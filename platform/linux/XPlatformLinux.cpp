#include <platform/XPlatformCommon.h>


// Platform initialization
bool xcc_platform_initialize() noexcept
{
	return true;
}

// Platform release
bool xcc_platform_release() noexcept
{
	return true;
}

// Current left mouse button down state
bool xcc_platform_mouse_left_press() noexcept
{
	return false;
}
