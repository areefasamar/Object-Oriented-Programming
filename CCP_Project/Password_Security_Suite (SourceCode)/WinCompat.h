#ifndef WINCOMPAT_H
#define WINCOMPAT_H

// Must be defined BEFORE windows.h to avoid conflicts with
// C++17 std::byte, min/max macros, and unused headers.
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
  #define NOMINMAX
#endif
#ifndef NOGDI
  #define NOGDI
#endif

#include <windows.h>
#undef byte   // prevent conflict with C++17 std::byte

#endif
