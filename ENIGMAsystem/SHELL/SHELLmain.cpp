/********************************************************************************\
**                                                                              **
**  Copyright (C) 2008 Josh Ventura                                             **
**                                                                              **
**  This file is a part of the ENIGMA Development Environment.                  **
**                                                                              **
**                                                                              **
**  ENIGMA is free software: you can redistribute it and/or modify it under the **
**  terms of the GNU General Public License as published by the Free Software   **
**  Foundation, version 3 of the license or any later version.                  **
**                                                                              **
**  This application and its source code is distributed AS-IS, WITHOUT ANY      **
**  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS   **
**  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more       **
**  details.                                                                    **
**                                                                              **
**  You should have recieved a copy of the GNU General Public License along     **
**  with this code. If not, see <http://www.gnu.org/licenses/>                  **
**                                                                              **
**  ENIGMA is an environment designed to create games and other programs with a **
**  high-level, fully compilable language. Developers of ENIGMA or anything     **
**  associated with ENIGMA are in no way responsible for its users or           **
**  applications created by its users, or damages caused by the environment     **
**  or programs made in the environment.                                        **
**                                                                              **
\********************************************************************************/

//#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Universal_System/var4.h"

//Before anyone else includes math.h, let's make sure we
//Don't get bitten by those damn bessel functions.
#define y0 bessel_y0
  #define y1 bessel_y1
  #define jn bessel_jn
  #define j0 bessel_j0
  #define j1 bessel_j1
    #include <cmath>
  #undef j1
  #undef j0
  #undef jn
  #undef y1
#undef y0
inline double abs(variant x) { return fabs((double)x); } // cmath introduces a number of overloads for this that will ambiguate variant.
inline double abs(var     x) { return fabs((double)x); } // cmath introduces a number of overloads for this that will ambiguate var.

//#include <vector> //COLLIGMA


#include "API_Switchboard.h"

#include "Universal_System/reflexive_types.h"

#include "Universal_System/GAME_GLOBALS.h"
#include "Universal_System/ENIGMA_GLOBALS.h"

#include "libEGMstd.h"


#include "Preprocessor_Environment_Editable/LIBINCLUDE.h"
#include "Preprocessor_Environment_Editable/GAME_SETTINGS.h"

// Simple Universal libraries
#include "Universal_System/estring.h"
#include "Universal_System/fileio.h"
#include "Universal_System/terminal_io.h"
#include "Universal_System/mathnc.h"

#if ENIGMA_GS_OPENGL
    #include "Graphics_Systems/graphics_mandatory.h"
    #include "Graphics_Systems/OpenGL/OPENGLStd.h"
#endif
#if ENIGMA_WS_WINDOWS != 0
    #include "Platforms/windows/WINDOWSStd.h"
#elif ENIGMA_WS_XLIB != 0
    #include "Platforms/xlib/XLIBwindow.h"
#endif



#include "Preprocessor_Environment_Editable/IDE_EDIT_resourcenames.h"
#include "Universal_System/switch_stuff.h"
#include "Universal_System/CallbackArrays.h"



#if COLLIGMA
    #include "Colligma/colligma_start.h"
    #include "Colligma/colligma_end.h"
#endif

#include "Universal_System/IMGloading.h"
#include "Graphics_Systems/OpenGL/GSsprite.h"


#include "Preprocessor_Environment_Editable/IDE_EDIT_modesenabled.h"

#include "Universal_System/collisions_object.h"

#include "Universal_System/objecttable.h"
#include "Universal_System/object.h"
#include "Universal_System/instance.h"
#include "Universal_System/roomsystem.h"

#include "Universal_System/globalupdate.h"

#include "Preprocessor_Environment_Editable/IDE_EDIT_wildclass.h"
#include "Universal_System/WITHconstruct.h"
#include "Universal_System/OBJaccess.h"

#include "Universal_System/simplecollisions.h"
#if COLLIGMA
    #include "Universal_System/collisions.h"
#endif

#include "Universal_System/instance_system.h"
#include "Platforms/platforms_mandatory.h"

#include "Universal_System/syntax_quirks.h"

#include "Preprocessor_Environment_Editable/IDE_EDIT_globals.h"
#include "Preprocessor_Environment_Editable/IDE_EDIT_evparent.h"
	#include "Graphics_Systems/OpenGL/GSscreen.h" // TODO: Move this declaration to its own header called *mandatory*.h in the root of /Graphics_Systems/.
#include "Preprocessor_Environment_Editable/IDE_EDIT_events.h"
#include "Preprocessor_Environment_Editable/IDE_EDIT_objectdeclarations.h"
#include "Preprocessor_Environment_Editable/IDE_EDIT_objectfunctionality.h"
#include "Preprocessor_Environment_Editable/IDE_EDIT_roomcreates.h"
#include "Preprocessor_Environment_Editable/IDE_EDIT_roomarrays.h"

#if BUILDMODE
	#include "Modes/buildmode.h"
#endif

#include "Universal_System/instance_create.h"

