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
    VESSEL* vessel = oapiGetFocusInterface();
    if(vessel)
    {
        Modifier modifier = None;
        if(getKeyState(VK_MENU))    modifier = static_cast<Modifier>(modifier | Alt);
        if(getKeyState(VK_SHIFT))   modifier = static_cast<Modifier>(modifier | Shift);
        if(getKeyState(VK_CONTROL)) modifier = static_cast<Modifier>(modifier | Control);

        for(int i = 0; i < CONTROL_COUNT; ++i)
        {
            if(control[i].modifier & modifier)
                state[i].current = getKeyState(control[i].key);

            if(state[i].current != state[i].previous)
            {
                double value = state[i].current ? ((modifier & Control) ? 0.1 : 1.0) : 0.0;
                vessel->SetThrusterGroupLevel(control[i].thruster, value);
                state[i].previous = state[i].current;
            }
        }
    }
}
