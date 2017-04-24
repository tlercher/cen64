//
// os/common/input.h: Input device handling functions.
//
// CEN64: Cycle-Accurate Nintendo 64 Emulator.
// Copyright (C) 2015, Tyler J. Stachecki.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef CEN64_OS_COMMON_INPUT
#define CEN64_OS_COMMON_INPUT
#include "common.h"

struct bus_controller;
struct cen64_gl_window;

cen64_cold void keyboard_press_callback(struct bus_controller *bus, unsigned key);
cen64_cold void keyboard_release_callback(struct bus_controller *bus, unsigned key);

#ifdef WITH_CONTROLLER_SUPPORT

cen64_cold void controller_initialize_controllers(struct cen64_gl_window *window);
cen64_cold void controller_teardown_controllers(struct cen64_gl_window *window);

cen64_cold void controller_poll_events();

#else // Stubs to avoid macro hell, the optimizer will throw em out for us

static inline void controller_initialize_controllers(struct cen64_gl_window *window) {}
static inline void controller_teardown_controllers(struct cen64_gl_window *window) {}

static inline void controller_poll_events() {}

#endif

#endif

