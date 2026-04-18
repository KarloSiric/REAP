#pragma once

#include "rengine/app/app_types.h"

namespace reap::rengine 
{
    
bool app_init( app_t &app, app_config_t &app_config );

void app_shutdown( app_t &app );

void app_begin_frame( app_t &app, f32 delta_time_seconds );

void app_update( app_t &app );

void app_render( app_t &app );

void app_end_frame( app_t &app );

bool app_is_running( app_t &app );

}; // namespace reap::rengine
