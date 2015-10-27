#pragma once

#include "ILuaLauncher.h"

#include <CoreModule.h>

#include <lua.hpp>
#include <LuaIntf.h>

#include <functional>

using namespace LuaIntf;

namespace SamEngine
{
    class LuaLogRecorder : public ILogRecorder
    {
    public:
        LOG_RECORDER_CREAE_FUNC_DECLARE(LuaLogRecorder)

        LuaLogRecorder();

        ~LuaLogRecorder();

        void Assert(const char *condition, const char *message, const char *filename, int32 line, const char *function) override;

        void Record(LogLevel mask, const char *message, va_list args) override;

    private:
        FILE *mFile{ nullptr };
    };

    class LuaLauncher : public ILuaLauncher, public ITick
    {
    public:
        void Create(const std::string &initialize, const std::string &finalize, const std::string &draw, const std::string &tick, int32 width, int32 height, const std::string &title) override;

        void Destroy() override;

        ApplicationState Initialize() override;

        ApplicationState Running() override;

        ApplicationState Finalize() override;

        void Tick(TickCount now, TickCount delta) override;

        void Run(const std::string &file) override;

    protected:
        template <typename RETURN = void, typename ... ARGUMENTS>
        RETURN ProtectedLuaCall(const std::string &name, ARGUMENTS &&... args);

    private:
        LuaState mLuaState;
        TickID mTickID{ InvalidTickID };
        int32 mWidth{ 0 };
        int32 mHeight{ 0 };
        std::string mTitle;
        std::string mLuaInitialize;
        std::string mLuaFinalize;
        std::string mLuaDraw;
        std::string mLuaTick;
    };

    template <typename RETURN, typename ... ARGUMENTS>
    RETURN LuaLauncher::ProtectedLuaCall(const std::string &name, ARGUMENTS &&... args)
    {
        LuaRef function(mLuaState, name.c_str());
        s_assert(function.isFunction());
        return function.call(std::forward<ARGUMENTS>(args)...);
    }
}