//
// memory_window.h: Memory view window.
//
// CEN64D: Cycle-Accurate Nintendo 64 Debugger
// Copyright (C) 2014, Tyler J. Stachecki.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef MEMORY_WINDOW_H
#define MEMORY_WINDOW_H

#include "toggle_window.h"

class MemoryWindow : public ToggleWindow {
  Q_OBJECT

public:
  explicit MemoryWindow(QAction *toggleAction, bool initiallyVisible);
  ~MemoryWindow();
};

#endif

