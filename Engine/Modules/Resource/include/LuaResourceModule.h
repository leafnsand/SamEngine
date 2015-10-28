#pragma once

#include "ResourceModule.h"

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    inline static void OpenResourceModule(LuaState state)
    {
        LuaBinding(state).beginModule("SamEngine")
            .addConstant("InvalidResourceID", InvalidResourceID)
        .endModule();
    }
}