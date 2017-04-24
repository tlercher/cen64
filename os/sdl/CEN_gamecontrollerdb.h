//
// os/sdl/CEN_gamecontrollerdb.h: CEN64 gamecontroller database.
//
// CEN64: Cycle-Accurate Nintendo 64 Emulator.
// Copyright (C) 2015, Tyler J. Stachecki.
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

static const char *cen_controller_mappings[] =
        {
#if defined(__LINUX__)
                "0300000057696920552047616d654300,Wii U Gamecube Adapter,a:b0,b:b1,dpdown:b9,dpleft:b10,dpright:b11,dpup:b8,leftshoulder:b4,leftx:a0,lefty:a1,rightshoulder:b5,righttrigger:b6,rightx:a3,righty:a4,start:b7,x:b3,y:b2",
#endif
                NULL
        };