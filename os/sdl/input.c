//
// os/sdl/input.c: Input device handling functions.
//
// CEN64: Cycle-Accurate Nintendo 64 Emulator.
// Copyright (C) 2015, Tyler J. Stachecki.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#include "os/main.h"
#include "input.h"
#include "os/inputcodes.h"
#include "si/controller.h"

#include "SDL_gamecontrollerdb.h"
#include "CEN_gamecontrollerdb.h"

#include <SDL2/SDL.h>


void controller_map_controllers() {
  const char *mapstring = NULL;

  // Map SDL Controllers
  mapstring = s_ControllerMappings[0];
  for (int i = 0; mapstring; i++) {
    SDL_GameControllerAddMapping(mapstring);
    mapstring = s_ControllerMappings[i];
  }

  // Map CEN Controllers
  mapstring = cen_controller_mappings[0];
  for (int i = 0; mapstring; i++) {
    SDL_GameControllerAddMapping(mapstring);
    mapstring = cen_controller_mappings[i];
  }
}

void controller_initialize_controllers(struct cen64_gl_window *window) {
  if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
  }

  controller_map_controllers();

  // TODO: Add support for multiple controllers
  if (SDL_IsGameController(0)) {
    printf("Using \'%s\' as controller for port %i\n", SDL_GameControllerNameForIndex(0), 1);
    window->controller = SDL_GameControllerOpen(0);
  }
}

void controller_teardown_controllers(struct cen64_gl_window *window) {
  if (window->controller) {
    SDL_GameControllerClose(window->controller);
  }
}

void controller_poll_events(struct vi_controller *vi) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_CONTROLLERAXISMOTION:
        controller_axis_callback(vi->bus, event.caxis.axis, event.caxis.value);
        break;
      case SDL_CONTROLLERBUTTONDOWN:
        controller_press_callback(vi->bus, event.cbutton.button);
        break;
      case SDL_CONTROLLERBUTTONUP:
        controller_release_callback(vi->bus, event.cbutton.button);
        break;
    }
  }
}

void controller_axis_callback(struct bus_controller *bus, unsigned axis, int16_t value) {
  struct si_controller *si = bus->si;
  int8_t stick;

  switch (axis) {
  // Analog stick.
  case CEN64_STICK_AXIS_X:
    stick = (int8_t)(value != 0 ? round(value / 385) : 0);
    si->input[2] = (uint8_t)stick;
    break;

  case CEN64_STICK_AXIS_Y:
    stick = (int8_t)(value != 0 ? round(value / 385) : 0);
    si->input[3] = (uint8_t) -(stick);
    break;

  // C-pad
  case CEN64_CPAD_AXIS_X:
    if (value > 25000) {
      si->input[1] |= 1 << 0;
    } else if (value < -25000) {
      si->input[1] |= 1 << 1;
    } else {
      si->input[1] &= ~(1 << 0);
      si->input[1] &= ~(1 << 1);
    }
    break;
  case CEN64_CPAD_AXIS_Y:
    if (value > 25000) {
      si->input[1] |= 1 << 2;
    } else if (value < -25000) {
      si->input[1] |= 1 << 3;
    } else {
      si->input[1] &= ~(1 << 2);
      si->input[1] &= ~(1 << 3);
    }
    break;

  // Z
  case CEN64_FLP_Z_TRIGGER:
    if (value > 20000) {
      si->input[0] |= 1 << 5;
    } else {
      si->input[0] &= ~(1 << 5);
    }
    break;
  }
}

void controller_press_callback(struct bus_controller *bus, unsigned key) {
  struct si_controller *si = bus->si;

  switch (key) {
    // L/R flippers.
    case CEN64_FLP_L: si->input[1] |= 1 << 5; break;
    case CEN64_FLP_R: si->input[1] |= 1 << 4; break;

      // A/B/Z/S buttons.
    case CEN64_BTN_A: si->input[0] |= 1 << 7; break;
    case CEN64_BTN_B: si->input[0] |= 1 << 6; break;
    case CEN64_BTN_Z: si->input[0] |= 1 << 5; break;
    case CEN64_BTN_START: si->input[0] |= 1 << 4; break;

      // // D-pad. (Left, Right, Up, Down)
    case CEN64_DPAD_LEFT: si->input[0] |= 1 << 1; break;
    case CEN64_DPAD_RIGHT: si->input[0] |= 1 << 0; break;
    case CEN64_DPAD_UP: si->input[0] |= 1 << 3; break;
    case CEN64_DPAD_DOWN: si->input[0] |= 1 << 2; break;
  }
}

void controller_release_callback(struct bus_controller *bus, unsigned key) {
  struct si_controller *si = bus->si;

  switch (key) {

    // L/R flippers.
    case CEN64_FLP_L: si->input[1] &= ~(1 << 5); break;
    case CEN64_FLP_R: si->input[1] &= ~(1 << 4); break;

    // A/B/Z/S buttons.
    case CEN64_BTN_A: si->input[0] &= ~(1 << 7); break;
    case CEN64_BTN_B: si->input[0] &= ~(1 << 6); break;
    case CEN64_BTN_Z: si->input[0] &= ~(1 << 5); break;
    case CEN64_BTN_START: si->input[0] &= ~(1 << 4); break;

    // D-pad. (Left, Right, Up, Down)
    case CEN64_DPAD_LEFT: si->input[0] &= ~(1 << 1); break;
    case CEN64_DPAD_RIGHT: si->input[0] &= ~(1 << 0); break;
    case CEN64_DPAD_UP: si->input[0] &= ~(1 << 3); break;
    case CEN64_DPAD_DOWN: si->input[0] &= ~(1 << 2); break;
  }
}