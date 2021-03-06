#pragma once

#include "IOModule.h"

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    inline static void OpenIOLuaModule(LuaState state)
    {
        LuaBinding(state).beginModule("SamEngine")
            .addProperty("IO", &GetIO)
            .beginClass<IIO>("IIO")
                .addFunction("SetLocationPlaceholder", &IIO::SetLocationPlaceholder, LUA_ARGS(std::string, std::string))
                .addFunction("Read", &IIO::Read, LUA_ARGS(std::string))
                .addFunction("Write", &IIO::Write, LUA_ARGS(std::string, DataPtr))
                .addFunction("AsyncRead", &IIO::AsyncRead, LUA_ARGS(std::string, IOCallbackFunction))
                .addFunction("AsyncWrite", &IIO::AsyncWrite, LUA_ARGS(std::string, DataPtr, _opt<IOCallbackFunction>))
            .endClass()
       .endModule();
    }
}