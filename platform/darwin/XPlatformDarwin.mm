#include <platform/XPlatformCommon.h>
#import <cocoa/cocoa.h>


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
	NSUInteger	vMask = [NSEvent pressedMouseButtons];
	BOOL		vLeftDown = (vMask & (1 << 0)) != 0;
	// BOOL		vRightDown = (vMask & (1 << 1)) != 0;
	return vLeftDown;
}
