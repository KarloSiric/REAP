#pragma once

#include "rengine/host/host_types.h"
#include "rengine/render/r_error.h"

namespace reap::rengine::render 
{
    
r_error_code_t r_init( const host::window_config_t &window_config );

void r_shutdown();

r_error_code_t r_begin_frame( const rcommon::f32 delta_time_seconds );

r_error_code_t r_render_frame();

r_error_code_t r_render_end();

bool r_is_initialized();
    
}       // namespace reap::rengine::render
