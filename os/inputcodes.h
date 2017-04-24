//
// os/inputcodes.h
//
// Definitions for input.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef __os_inputcodes_h__
#define __os_inputcodes_h__


#if defined WITH_CONTROLLER_SUPPORT && defined WITH_SDL
#include "os/sdl/inputcodes.h"
#else
#error Cannot use WITH_CONTROLLER_SUPPORT without a backend.
#endif

#endif

