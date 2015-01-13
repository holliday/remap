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

////////////////////////////////////////////////////////////////////////////////
#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_MICRO 1

////////////////////////////////////////////////////////////////////////////////
enum Modifier
{
    None  = 0x00,
    Alt   = 0x01,
    Shift = 0x02,
    Ctrl  = 0x04,
};

inline Modifier operator|(Modifier x, Modifier y)
{
    return static_cast<Modifier>(static_cast<int>(y) | static_cast<int>(x));
}

////////////////////////////////////////////////////////////////////////////////
struct Control
{
    Modifier modifier;      // ... with these modifiers ...
    int key;                // when this key is pressed
    THGROUP_TYPE thruster;  // set this thruster
    double level;           // to this value

    const char* name;       // for debugging only
};

////////////////////////////////////////////////////////////////////////////////
struct Control control[] =
{
    {        Shift, OAPI_KEY_NUMPAD2, THGROUP_ATT_PITCHUP,   1.0, "PITCHUP"   },
    {        Shift, OAPI_KEY_NUMPAD8, THGROUP_ATT_PITCHDOWN, 1.0, "PITCHDOWN" },
    {        Shift, OAPI_KEY_NUMPAD1, THGROUP_ATT_YAWLEFT,   1.0, "YAWLEFT"   },
    {        Shift, OAPI_KEY_NUMPAD3, THGROUP_ATT_YAWRIGHT,  1.0, "YAWRIGHT"  },
    {        Shift, OAPI_KEY_NUMPAD4, THGROUP_ATT_BANKLEFT,  1.0, "BANKLEFT"  },
    {        Shift, OAPI_KEY_NUMPAD6, THGROUP_ATT_BANKRIGHT, 1.0, "BANKRIGHT" },

    { Ctrl | Shift, OAPI_KEY_NUMPAD2, THGROUP_ATT_PITCHUP,   0.1, "PITCHUP"   },
    { Ctrl | Shift, OAPI_KEY_NUMPAD8, THGROUP_ATT_PITCHDOWN, 0.1, "PITCHDOWN" },
    { Ctrl | Shift, OAPI_KEY_NUMPAD1, THGROUP_ATT_YAWLEFT,   0.1, "YAWLEFT"   },
    { Ctrl | Shift, OAPI_KEY_NUMPAD3, THGROUP_ATT_YAWRIGHT,  0.1, "YAWRIGHT"  },
    { Ctrl | Shift, OAPI_KEY_NUMPAD4, THGROUP_ATT_BANKLEFT,  0.1, "BANKLEFT"  },
    { Ctrl | Shift, OAPI_KEY_NUMPAD6, THGROUP_ATT_BANKRIGHT, 0.1, "BANKRIGHT" },

    {        Alt  , OAPI_KEY_NUMPAD6, THGROUP_ATT_RIGHT,     1.0, "RIGHT"     },
    {        Alt  , OAPI_KEY_NUMPAD4, THGROUP_ATT_LEFT,      1.0, "LEFT"      },
    {        Alt  , OAPI_KEY_NUMPAD9, THGROUP_ATT_UP,        1.0, "UP"        },
    {        Alt  , OAPI_KEY_NUMPAD3, THGROUP_ATT_DOWN,      1.0, "DOWN"      },
    {        Alt  , OAPI_KEY_NUMPAD8, THGROUP_ATT_FORWARD,   1.0, "FORWARD"   },
    {        Alt  , OAPI_KEY_NUMPAD2, THGROUP_ATT_BACK,      1.0, "BACK"      },

    { Ctrl | Alt  , OAPI_KEY_NUMPAD6, THGROUP_ATT_RIGHT,     0.1, "RIGHT"     },
    { Ctrl | Alt  , OAPI_KEY_NUMPAD4, THGROUP_ATT_LEFT,      0.1, "LEFT"      },
    { Ctrl | Alt  , OAPI_KEY_NUMPAD9, THGROUP_ATT_UP,        0.1, "UP"        },
    { Ctrl | Alt  , OAPI_KEY_NUMPAD3, THGROUP_ATT_DOWN,      0.1, "DOWN"      },
    { Ctrl | Alt  , OAPI_KEY_NUMPAD8, THGROUP_ATT_FORWARD,   0.1, "FORWARD"   },
    { Ctrl | Alt  , OAPI_KEY_NUMPAD2, THGROUP_ATT_BACK,      0.1, "BACK"      },
};

#define CONTROL_COUNT (sizeof(control) / sizeof(control[0]))

////////////////////////////////////////////////////////////////////////////////
struct State
{
    bool previous;
    bool current;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class Remap : public oapi::Module
{
public:
    Remap(HINSTANCE hDLL);
    ~Remap();
    virtual void clbkPreStep(double simt, double simdt, double mjd);

protected:
    State state[CONTROL_COUNT];

    LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    static Remap* instance;
    static HHOOK hook;
    static LRESULT CALLBACK StaticLowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

////////////////////////////////////////////////////////////////////////////////
#endif // REMAP_HPP
