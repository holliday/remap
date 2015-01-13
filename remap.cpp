////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2015 Dimitry Ishenko
// Distributed under the GNU GPL v2. For full terms please visit:
// http://www.gnu.org/licenses/gpl.html
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com

////////////////////////////////////////////////////////////////////////////////
#include "remap.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DLLCLBK void InitModule(HINSTANCE hModule)
{
    oapiRegisterModule(new Remap(hModule));
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Remap* Remap::instance = NULL;
HHOOK Remap::hook = NULL;

////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK Remap::StaticLowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode >= 0 && instance)
        return instance->LowLevelKeyboardProc(nCode, wParam, lParam);

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
Remap::Remap(HINSTANCE hDLL):
    oapi::Module(hDLL)
{
    for(int i = 0; i < CONTROL_COUNT; ++i)
    {
        state[i].previous = false;
        state[i].current = false;
    }

    instance = this;
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, &Remap::StaticLowLevelKeyboardProc, hModule, 0);
    if(!hook)
        oapiWriteLog("Remap::Remap: failed to install keyboard hook");
    else oapiWriteLog("Remap::Remap: installed keyboard hook");
}

////////////////////////////////////////////////////////////////////////////////
Remap::~Remap()
{
    if(hook)
    {
        UnhookWindowsHookEx(hook);
        oapiWriteLog("Remap::Remap: uninstalled keyboard hook");
    }
}

////////////////////////////////////////////////////////////////////////////////
#define KEYSTATE_MASK (1 << (8 * sizeof(SHORT) - 1))
static inline bool getKeyState(int vkCode) { return (GetAsyncKeyState(vkCode) & KEYSTATE_MASK) != 0; }

////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK Remap::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* kbd = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

    Modifier modifier = None;
    if(getKeyState(VK_MENU))    modifier = modifier | Alt;
    if(getKeyState(VK_SHIFT))   modifier = modifier | Shift;
    if(getKeyState(VK_CONTROL)) modifier = modifier | Ctrl;

    for(int i = 0; i < CONTROL_COUNT; ++i)
        state[i].current = !(kbd->flags & LLKHF_UP) && control[i].key == kbd->vkCode && control[i].modifier == modifier;

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
void Remap::clbkPreStep(double, double, double)
{
    static char message[256];

    VESSEL* vessel = oapiGetFocusInterface();
    if(vessel)
    {
        for(int i = 0; i < CONTROL_COUNT; ++i)
        {
            if(state[i].current != state[i].previous)
            {
                double level = state[i].current ? control[i].level : 0.0;
                vessel->SetThrusterGroupLevel(control[i].thruster, level);
                state[i].previous = state[i].current;

#ifndef NDEBUG
                sprintf(message, "%s = %f", control[i].name, level);
                oapiWriteLog(message);
#endif
            }
        }
    }
}
