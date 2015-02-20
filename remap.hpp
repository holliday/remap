////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2015 Dimitry Ishenko
// Distributed under the GNU GPL v2. For full terms please visit:
// http://www.gnu.org/licenses/gpl.html
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com

////////////////////////////////////////////////////////////////////////////////
#ifndef REMAP_HPP
#define REMAP_HPP

////////////////////////////////////////////////////////////////////////////////
#define ORBITER_MODULE
#include "Orbitersdk.h"

#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
#define VERSION_MAJOR 0
#define VERSION_MINOR 5
#define VERSION_MICRO 2

////////////////////////////////////////////////////////////////////////////////
#include "keymap.hpp"

#define KEYMAP_COUNT (sizeof(keymap) / sizeof(keymap[0]))

////////////////////////////////////////////////////////////////////////////////
struct Thruster
{
    std::string name;       // name in keymap.cfg
    THGROUP_TYPE thruster;  // thruster group
};

////////////////////////////////////////////////////////////////////////////////
struct Thruster thrusters[] =
{
    { "RCSPitchUpDirect"  , THGROUP_ATT_PITCHUP   },
    { "RCSPitchDownDirect", THGROUP_ATT_PITCHDOWN },
    { "RCSYawLeftDirect"  , THGROUP_ATT_YAWLEFT   },
    { "RCSYawRightDirect" , THGROUP_ATT_YAWRIGHT  },
    { "RCSBankLeftDirect" , THGROUP_ATT_BANKLEFT  },
    { "RCSBankRightDirect", THGROUP_ATT_BANKRIGHT },

    { "RCSRightDirect"    , THGROUP_ATT_RIGHT     },
    { "RCSLeftDirect"     , THGROUP_ATT_LEFT      },
    { "RCSUpDirect"       , THGROUP_ATT_UP        },
    { "RCSDownDirect"     , THGROUP_ATT_DOWN      },
    { "RCSForwardDirect"  , THGROUP_ATT_FORWARD   },
    { "RCSBackDirect"     , THGROUP_ATT_BACK      },

    { "RCSLowPowerToggle" , THGROUP_USER          }, // hack to add low power toggle
};

#define THRUSTER_COUNT (sizeof(thrusters) / sizeof(thrusters[0]))

////////////////////////////////////////////////////////////////////////////////
enum Modifier
{
    None    = 0x0000,
    Alt     = 0x1000,
    Shift   = 0x2000,
    Ctrl    = 0x4000,

    ModMask = 0xf000,
    KeyMask = 0x0fff,
};

////////////////////////////////////////////////////////////////////////////////
struct Control
{
    int key;            // scan code + modifiers
    bool previous;      // previous state (pressed/released)
    bool current;       // current state
    Thruster* thruster; // thruster to engage
};

typedef std::vector<Control> Controls;

////////////////////////////////////////////////////////////////////////////////
struct LowPowerToggle
{
    int key;
    bool on;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class Remap : public oapi::Module
{
public:
    Remap(HINSTANCE hDLL);
    ~Remap();
    virtual void clbkPreStep(double simt, double simdt, double mjd);

    void readKeymap();

protected:
    Controls controls;
    LowPowerToggle toggle;

    LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    static Remap* instance;
    static HHOOK hook;
    static LRESULT CALLBACK StaticLowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

////////////////////////////////////////////////////////////////////////////////
#endif // REMAP_HPP
