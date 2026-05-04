#pragma once

#include "rengine/host/host_types.h"
#include "rengine/rcommon/com_foundation.h"
#include "rengine/sys/sys_error.h"

namespace reap::rengine::sys 
{

struct sys_window_desc_t {
    const char *title{ rcommon::COM_GAME_INFO.name };
    rcommon::u32 width{ host::HOST_DEFAULT_VIEWPORT_WIDTH };
    rcommon::u32 height{ host::HOST_DEFAULT_VIEWPORT_HEIGHT };
    bool fullscreen{ false };
    bool vsync{ true };
};

struct sys_window_t {
    void *native_window{ nullptr };
    
    rcommon::u32 width{ 0u };
    rcommon::u32 height{ 0u };
    
    bool fullscreen{ false};
    bool vsync{ true };
    bool should_close{ false };
    bool valid{ false };
};

sys_error_code_t Sys_CreateWindow( const sys_window_desc_t &window_description, sys_window_t &out_window );

void Sys_DestroyWindow( sys_window_t &window );

void Sys_PollWindowEvents( sys_window_t &window );

bool Sys_WindowShouldClose( const sys_window_t &window ); 
    
}       // namespace reap::rengine::sys
