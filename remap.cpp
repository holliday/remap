////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2015 Dimitry Ishenko
// Distributed under the GNU GPL v2. For full terms please visit:
// http://www.gnu.org/licenses/gpl.html
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com

////////////////////////////////////////////////////////////////////////////////
#include "remap.hpp"

#include <fstream>
#include <sstream>

static char message[256];

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
    readKeymap();

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
void Remap::readKeymap()
{
    controls.clear();

    std::ifstream file("keymap.cfg");
    if(file)
    {
        std::string read;
        while(std::getline(file, read))
        {
            if(read.empty()) continue;

            std::istringstream stream(read);

            std::string name;
            stream >> name;
            if(name.empty()) continue;

            Thruster* thruster = NULL;

            for(int i = 0; i < THRUSTER_COUNT; ++i)
                if(thrusters[i].name == name)
                {
                    thruster = &thrusters[i];
                    break;
                }
            if(!thruster) continue;

            std::string value;
            stream >> value;
            if(value != "=") continue;

            int key = None;
            for(;;)
            {
                value.clear();
                stream >> value;
                if(value.empty()) break;

                if(value == "ALT")
                    key |= Alt;
                else if(value == "SHIFT")
                    key |= Shift;
                else if(value == "CTRL")
                    key |= Ctrl;
                else if(0 == (key & KeyMask))
                {
                    for(int i = 0; i < KEYMAP_COUNT; ++i)
                        if(keymap[i].name == value)
                        {
                            key |= keymap[i].key;
                            break;
                        }
                }
            }
            if(0 == (key & KeyMask)) continue;

            Control control = { key, false, false, thruster };
            controls.push_back(control);

#ifndef NDEBUG
            sprintf(message, "%s: key = 0x%x modifier = 0x%x", thruster->name.data(), key & KeyMask, key & ModMask);
            oapiWriteLog(message);
#endif
        }
        file.close();
    }
    else oapiWriteLog("Remap::readKeymap: failed to open keymap.cfg");
}

////////////////////////////////////////////////////////////////////////////////
#define KEYSTATE_MASK (1 << (8 * sizeof(SHORT) - 1))
static inline bool getKeyState(int vkCode) { return (GetAsyncKeyState(vkCode) & KEYSTATE_MASK) != 0; }

////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK Remap::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* kbd = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

    int key = kbd->scanCode;
    if(getKeyState(VK_MENU))    key |= Alt;
    if(getKeyState(VK_SHIFT))   key |= Shift;
    if(getKeyState(VK_CONTROL)) key |= Ctrl;
    bool press = !(kbd->flags & LLKHF_UP);

    for(Controls::iterator ri = controls.begin(), ri_end = controls.end(); ri != ri_end; ++ri)
    {
        Control& control = *ri;
        if(control.key == key)
        {
            control.current = press;
            break;
        }
    }

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
void Remap::clbkPreStep(double, double, double)
{
    VESSEL* vessel = oapiGetFocusInterface();
    if(vessel)
    {
        for(Controls::iterator ri = controls.begin(), ri_end = controls.end(); ri != ri_end; ++ri)
        {
            Control& control = *ri;
            if(control.current != control.previous)
            {
                double level = control.current ? control.thruster->level : 0.0;
                vessel->SetThrusterGroupLevel(control.thruster->thruster, level);
                control.previous = control.current;

#ifndef NDEBUG
                sprintf(message, "%s = %f", control.thruster->name.data(), level);
                oapiWriteLog(message);
#endif
            }
        }
    }
}
