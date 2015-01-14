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
#define VERSION_MINOR 4
#define VERSION_MICRO 0

////////////////////////////////////////////////////////////////////////////////
struct Keymap
{
    std::string name;
    int key;
};

struct Keymap keymap[] =
{
    #include "keymap.inc"
};

#define KEYMAP_COUNT (sizeof(keymap) / sizeof(keymap[0]))

////////////////////////////////////////////////////////////////////////////////
struct Thruster
{
    std::string name;       // name in keymap.cfg
    THGROUP_TYPE thruster;  // thruster group
    double level;           // thrust level
};

////////////////////////////////////////////////////////////////////////////////
struct Thruster thrusters[] =
{
    {   "RCSPitchUpDirect"  , THGROUP_ATT_PITCHUP,   1.0 },
    {   "RCSPitchDownDirect", THGROUP_ATT_PITCHDOWN, 1.0 },
    {   "RCSYawLeftDirect"  , THGROUP_ATT_YAWLEFT,   1.0 },
    {   "RCSYawRightDirect" , THGROUP_ATT_YAWRIGHT,  1.0 },
    {   "RCSBankLeftDirect" , THGROUP_ATT_BANKLEFT,  1.0 },
    {   "RCSBankRightDirect", THGROUP_ATT_BANKRIGHT, 1.0 },

    { "LPRCSPitchUpDirect"  , THGROUP_ATT_PITCHUP,   0.1 },
    { "LPRCSPitchDownDirect", THGROUP_ATT_PITCHDOWN, 0.1 },
    { "LPRCSYawLeftDirect"  , THGROUP_ATT_YAWLEFT,   0.1 },
    { "LPRCSYawRightDirect" , THGROUP_ATT_YAWRIGHT,  0.1 },
    { "LPRCSBankLeftDirect" , THGROUP_ATT_BANKLEFT,  0.1 },
    { "LPRCSBankRightDirect", THGROUP_ATT_BANKRIGHT, 0.1 },

    {   "RCSRightDirect"    , THGROUP_ATT_RIGHT,     1.0 },
    {   "RCSLeftDirect"     , THGROUP_ATT_LEFT,      1.0 },
    {   "RCSUpDirect"       , THGROUP_ATT_UP,        1.0 },
    {   "RCSDownDirect"     , THGROUP_ATT_DOWN,      1.0 },
    {   "RCSForwardDirect"  , THGROUP_ATT_FORWARD,   1.0 },
    {   "RCSBackDirect"     , THGROUP_ATT_BACK,      1.0 },

    { "LPRCSRightDirect"    , THGROUP_ATT_RIGHT,     0.1 },
    { "LPRCSLeftDirect"     , THGROUP_ATT_LEFT,      0.1 },
    { "LPRCSUpDirect"       , THGROUP_ATT_UP,        0.1 },
    { "LPRCSDownDirect"     , THGROUP_ATT_DOWN,      0.1 },
    { "LPRCSForwardDirect"  , THGROUP_ATT_FORWARD,   0.1 },
    { "LPRCSBackDirect"     , THGROUP_ATT_BACK,      0.1 },
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
    int key;
    bool previous;
    bool current;
    Thruster* thruster;
};

typedef std::vector<Control> Controls;

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

    LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

    static Remap* instance;
    static HHOOK hook;
    static LRESULT CALLBACK StaticLowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

////////////////////////////////////////////////////////////////////////////////
#endif // REMAP_HPP
