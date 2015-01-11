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

////////////////////////////////////////////////////////////////////////////////
struct Control
{
    Modifier modifier;
    int key;
    THGROUP_TYPE thruster;
    const char* name;
};

////////////////////////////////////////////////////////////////////////////////
struct Control control[] =
{
    { Shift, VK_NUMPAD2, THGROUP_ATT_PITCHUP,   "PITCHUP  " },
    { Shift, VK_NUMPAD8, THGROUP_ATT_PITCHDOWN, "PITCHDOWN" },
    { Shift, VK_NUMPAD1, THGROUP_ATT_YAWLEFT,   "YAWLEFT  " },
    { Shift, VK_NUMPAD3, THGROUP_ATT_YAWRIGHT,  "YAWRIGHT " },
    { Shift, VK_NUMPAD4, THGROUP_ATT_BANKLEFT,  "BANKLEFT " },
    { Shift, VK_NUMPAD6, THGROUP_ATT_BANKRIGHT, "BANKRIGHT" },
    { Alt  , VK_NUMPAD6, THGROUP_ATT_RIGHT,     "RIGHT    " },
    { Alt  , VK_NUMPAD4, THGROUP_ATT_LEFT,      "LEFT     " },
    { Alt  , VK_NUMPAD9, THGROUP_ATT_UP,        "UP       " },
    { Alt  , VK_NUMPAD3, THGROUP_ATT_DOWN,      "DOWN     " },
    { Alt  , VK_NUMPAD8, THGROUP_ATT_FORWARD,   "FORWARD  " },
    { Alt  , VK_NUMPAD2, THGROUP_ATT_BACK,      "BACK     " },
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
