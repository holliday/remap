////////////////////////////////////////////////////////////////////////////////
#ifndef REMAP_HPP
#define REMAP_HPP

////////////////////////////////////////////////////////////////////////////////
#define ORBITER_MODULE
#include "Orbitersdk.h"

////////////////////////////////////////////////////////////////////////////////
class Remap : public oapi::Module
{
public:
    Remap(HINSTANCE hDLL);
    ~Remap();
    virtual void clbkPreStep(double simt, double simdt, double mjd);
};

////////////////////////////////////////////////////////////////////////////////
#endif // REMAP_HPP
