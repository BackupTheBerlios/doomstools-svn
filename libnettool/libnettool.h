// Copyright (C) 2004 Doomsday <doomsday@mailclub.net>

// This file is part of libnettool.

// libnettool is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// libnettool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.

// You should have received a copy of the GNU Lesser Public License
// along with libnettool; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#define _LIBNETTOOL_H_

#pragma once

//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBNETTOOL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBNETTOOL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.#ifdef LIBNETTOOL_EXPORTS
#ifdef LIBNETTOOL_EXPORTS
#define LIBNETTOOL_API __declspec(dllexport)
#else
#define LIBNETTOOL_API __declspec(dllimport)
#endif

#include "libtool/libstdtool.h"
#include "network.h"

#endif