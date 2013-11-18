#ifndef __SB_COMMON_HPP__
#define __SB_COMMON_HPP__

#include <wx/wx.h>
#include <SDL.h>
#ifdef _MSC_VER
#include "../config-win32.h"
#else
#include "../config.h"
#endif

#include "resource.h"

class wxBoardFrame;
class wxLCDWindow;
class wxGamePanel;
class wxTeamPanel;

#define N_ELEMENTS(arr) (sizeof(arr) / sizeof((arr)[0]))

#endif  // __SB_COMMON_HPP__
