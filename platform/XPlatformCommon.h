#ifndef			_X_PLATFORM_COMMON_H_
#define			_X_PLATFORM_COMMON_H_

#include <QObject>


// Platform initialization
bool xcc_platform_initialize() noexcept;

// Platform release
bool xcc_platform_release() noexcept;

// Current left mouse button down state
bool xcc_platform_mouse_left_press() noexcept;

#endif
