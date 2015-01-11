////////////////////////////////////////////////////////////////////////////////
#include "remap.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DLLCLBK void InitModule(HINSTANCE hModule)
{
    oapiRegisterModule(new Remap(hModule));
}

////////////////////////////////////////////////////////////////////////////////
#define KEYSTATE_MASK (1 << (8 * sizeof(SHORT) - 1))

static inline bool getKeyState(int vkCode)
{
    return (GetAsyncKeyState(vkCode) & KEYSTATE_MASK) != 0;
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
}

////////////////////////////////////////////////////////////////////////////////
Remap::~Remap()
{
}

////////////////////////////////////////////////////////////////////////////////
void Remap::clbkPreStep(double, double, double)
{
    static char message[256];

    VESSEL* vessel = oapiGetFocusInterface();
    if(vessel)
    {
        Modifier modifier = None;
        if(getKeyState(VK_MENU))    modifier = modifier | Alt;
        if(getKeyState(VK_SHIFT))   modifier = modifier | Shift;
        if(getKeyState(VK_CONTROL)) modifier = modifier | Control;

        for(int i = 0; i < CONTROL_COUNT; ++i)
        {
            state[i].current = (control[i].modifier == modifier)
                 && getKeyState(control[i].key);

            if(state[i].current != state[i].previous)
            {
                double level = state[i].current ? control[i].level : 0.0;
                vessel->SetThrusterGroupLevel(control[i].thruster, level);
                state[i].previous = state[i].current;

#ifndef _NDEBUG
                sprintf(message, "%s = %f", control[i].name, level);
                oapiWriteLog(message);
#endif
            }
        }
    }
}
