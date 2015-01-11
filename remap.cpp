////////////////////////////////////////////////////////////////////////////////
#include "remap.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DLLCLBK void InitModule(HINSTANCE hModule)
{
    oapiRegisterModule(new Remap(hModule));
}

////////////////////////////////////////////////////////////////////////////////
static inline bool getKeyState(int vkCode)
{
    SHORT value = GetAsyncKeyState(vkCode);
    return value && (1 << (8 * sizeof(SHORT) - 1 ));
}

////////////////////////////////////////////////////////////////////////////////
Remap::Remap(HINSTANCE hDLL):
    oapi::Module(hDLL)
{
}

////////////////////////////////////////////////////////////////////////////////
Remap::~Remap()
{
}

////////////////////////////////////////////////////////////////////////////////
void Remap::clbkPreStep(double simt, double simdt, double mjd)
{
    bool menu    = getKeyState(VK_MENU);
    bool shift   = getKeyState(VK_SHIFT);
    bool control = getKeyState(VK_CONTROL);

    bool right   = getKeyState(VK_NUMPAD6);
    bool left    = getKeyState(VK_NUMPAD4);
    bool up      = getKeyState(VK_NUMPAD9);
    bool down    = getKeyState(VK_NUMPAD3);
    bool forward = getKeyState(VK_NUMPAD8);
    bool back    = getKeyState(VK_NUMPAD2);

    if(menu)    oapiWriteLog("ALT");
    if(shift)   oapiWriteLog("SHIFT");
    if(control) oapiWriteLog("CTRL");

    if(right)   oapiWriteLog("RIGHT");
    if(left)    oapiWriteLog("LEFT");
    if(up)      oapiWriteLog("UP");
    if(down)    oapiWriteLog("DOWN");
    if(forward) oapiWriteLog("FORWARD");
    if(back)    oapiWriteLog("BACK");
}
