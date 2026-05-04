#pragma once

#include "rengine/host/host_types.h"
#include "rengine/render/r_error.h"

namespace reap::rengine::render
{
    
struct render_runtime_state_t {
    bool initialized{ false };
    bool in_frame{ false };
    
    const sys::sys_window_t *window{ nullptr };
    
    rcommon::u32 viewport_width{ 0u };    
    rcommon::u32 viewport_height{ 0u };    
    
    void *gl_context{ nullptr };
};

r_error_code_t R_Init( const sys::sys_window_t &window, const host::window_config_t &window_config );

void R_Shutdown();

r_error_code_t R_BeginFrame( const rcommon::f32 delta_time_seconds );

r_error_code_t R_RenderFrame();

r_error_code_t R_EndFrame();

bool R_IsInitialized();

}

