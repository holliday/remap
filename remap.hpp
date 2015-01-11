////////////////////////////////////////////////////////////////////////////////
#ifndef REMAP_HPP
#define REMAP_HPP

////////////////////////////////////////////////////////////////////////////////
#define ORBITER_MODULE
#include "Orbitersdk.h"

////////////////////////////////////////////////////////////////////////////////
enum Modifier
{
    None    = 0x00,
    Alt     = 0x01,
    Shift   = 0x02,
    Control = 0x04,
};

inline Modifier operator|(Modifier x, Modifier y) { return static_cast<Modifier>(static_cast<int>(y) | static_cast<int>(x)); }

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
    {           Shift, VK_NUMPAD2, THGROUP_ATT_PITCHUP,   1.0, "PITCHUP"   },
    {           Shift, VK_NUMPAD8, THGROUP_ATT_PITCHDOWN, 1.0, "PITCHDOWN" },
    {           Shift, VK_NUMPAD1, THGROUP_ATT_YAWLEFT,   1.0, "YAWLEFT"   },
    {           Shift, VK_NUMPAD3, THGROUP_ATT_YAWRIGHT,  1.0, "YAWRIGHT"  },
    {           Shift, VK_NUMPAD4, THGROUP_ATT_BANKLEFT,  1.0, "BANKLEFT"  },
    {           Shift, VK_NUMPAD6, THGROUP_ATT_BANKRIGHT, 1.0, "BANKRIGHT" },

    { Control | Shift, VK_NUMPAD2, THGROUP_ATT_PITCHUP,   0.1, "PITCHUP"   },
    { Control | Shift, VK_NUMPAD8, THGROUP_ATT_PITCHDOWN, 0.1, "PITCHDOWN" },
    { Control | Shift, VK_NUMPAD1, THGROUP_ATT_YAWLEFT,   0.1, "YAWLEFT"   },
    { Control | Shift, VK_NUMPAD3, THGROUP_ATT_YAWRIGHT,  0.1, "YAWRIGHT"  },
    { Control | Shift, VK_NUMPAD4, THGROUP_ATT_BANKLEFT,  0.1, "BANKLEFT"  },
    { Control | Shift, VK_NUMPAD6, THGROUP_ATT_BANKRIGHT, 0.1, "BANKRIGHT" },

    {           Alt  , VK_NUMPAD6, THGROUP_ATT_RIGHT,     1.0, "RIGHT"     },
    {           Alt  , VK_NUMPAD4, THGROUP_ATT_LEFT,      1.0, "LEFT"      },
    {           Alt  , VK_NUMPAD9, THGROUP_ATT_UP,        1.0, "UP"        },
    {           Alt  , VK_NUMPAD3, THGROUP_ATT_DOWN,      1.0, "DOWN"      },
    {           Alt  , VK_NUMPAD8, THGROUP_ATT_FORWARD,   1.0, "FORWARD"   },
    {           Alt  , VK_NUMPAD2, THGROUP_ATT_BACK,      1.0, "BACK"      },

    { Control | Alt  , VK_NUMPAD6, THGROUP_ATT_RIGHT,     0.1, "RIGHT"     },
    { Control | Alt  , VK_NUMPAD4, THGROUP_ATT_LEFT,      0.1, "LEFT"      },
    { Control | Alt  , VK_NUMPAD9, THGROUP_ATT_UP,        0.1, "UP"        },
    { Control | Alt  , VK_NUMPAD3, THGROUP_ATT_DOWN,      0.1, "DOWN"      },
    { Control | Alt  , VK_NUMPAD8, THGROUP_ATT_FORWARD,   0.1, "FORWARD"   },
    { Control | Alt  , VK_NUMPAD2, THGROUP_ATT_BACK,      0.1, "BACK"      },
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
};

////////////////////////////////////////////////////////////////////////////////
#endif // REMAP_HPP
