#pragma once

#include "rengine/app/app_types.h"

namespace reap::rengine 
{
    
bool app_init( app_state_t &app_state, app_config_t &app_config );

void app_shutdown( app_state_t &app_state );

void app_begin_frame( app_state_t &app_state, f32 delta_time_seconds );

void app_update( app_state_t &app_state );

void app_render( const app_state_t &app_state );

void app_end_frame( app_state_t &app_state );

bool app_is_running( app_state_t &app_state );

}; // namespace reap::rengine
