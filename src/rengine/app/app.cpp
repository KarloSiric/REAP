/*======================================================================
   File: app.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 01:23:58
   Last Modified by: ksiric
   Last Modified: 2026-04-19 21:18:21
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/app/app.h"

namespace reap::rengine
{

bool app_init( app_state_t &app_state, const app_config_t &app_config ) {
    
    ( void )app_config;
    
    app_state.stage = app_stage_t::INITIALIZING;
    app_state.running = true;
    app_state.has_focus = true;
    app_state.frame = {};
    
    app_state.stage = app_stage_t::RUNNING;
    
    return true;   
}

void app_shutdown( app_state_t &app_state) {
    
    app_state.running = false;
    app_state.stage = app_stage_t::SHUTDOWN;
    
}

void app_begin_frame( app_state_t &app_state, f32 delta_time_seconds ) {
    
    if ( app_state.stage == app_stage_t::SHUTDOWN ) {
        return ;
    }
    
    app_state.frame.index++;
    app_state.frame.delta_time_seconds = delta_time_seconds;
    app_state.frame.real_time_seconds += delta_time_seconds;
    if ( app_state.stage == app_stage_t::RUNNING ) {
        app_state.frame.simulation_time_seconds += delta_time_seconds;
    }
}

void app_update( app_state_t &app_state ) {
    
    if ( app_state.stage != app_stage_t::RUNNING ) {
        return ;
    }
    
    if ( !app_state.running ) {
        return ;
    }
    
    // @TODO: Update the application stage, and handle input, AI, gameplay etc.
    /*
    
    
    
    
    
    

    */   
    
    return ;
}

void app_render( const app_state_t &app_state ) {
    
    // @TODO: Render the application stage, and handle rendering of the scene, UI, etc.
    
    ( void )app_state;
    
    return ;
}

void app_end_frame( app_state_t &app_state ) {
    
    if ( app_state.stage == app_stage_t::SHUTTINGDOWN ) {
        app_state.running = false;
        app_state.stage = app_stage_t::SHUTDOWN;
    }
    
    return ;
}

bool app_is_running( app_state_t &app_state ) {
    return app_state.running && ( app_state.stage != app_stage_t::SHUTTINGDOWN && app_state.stage != app_stage_t::SHUTDOWN );
}

}
