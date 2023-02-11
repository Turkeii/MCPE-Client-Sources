#pragma once
#include "../Module.h"

class NoRender : public IModule {
public:
    bool blockEntities = false;
    bool particles = false;
    bool entities = false;

    virtual const char* getRawModuleName();
    virtual const char* getModuleName();
    NoRender();
};