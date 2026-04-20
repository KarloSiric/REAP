#pragma once

#include "rengine/app/app_types.h"

namespace reap::rengine::render 
{
    
bool r_init( const app::window_config_t &window_config );

void r_shutdown();

void r_begin_frame( const rcommon::f32 delta_time_seconds );

void r_render_frame();

void r_render_end();

bool r_is_initialized();
    
}       // namespace reap::rengine::render
