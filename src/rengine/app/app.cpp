/*======================================================================
   File: app.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 01:23:58
   Last Modified by: ksiric
   Last Modified: 2026-04-19 02:10:10
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

bool app_init( app_t &app, const app_config_t &app_config ) {
    
    (void)app_config;
    
    app.state = app_state_t::Initializing;
    app.running = true;
    app.has_focus = true;
    app.frame = {};
    
    app.state = app_state_t::Running;
    
    return true;   
}

void app_shutdown( app_t &app) {
    
    app.running = false;
    app.state = app_state_t::Shutdown;
    
}

void app_begin_frame( app_t &app, f32 delta_time_seconds ) {
    
    app.frame.index++;
    app.frame.delta_time_seconds = delta_time_seconds;
    app.frame.real_time_seconds += delta_time_seconds;
    app.frame.simulation_time_seconds += delta_time_seconds;
    
}

void app_update( app_t &app ) {
    
    if ( app.state != app_state_t::Running ) {
        return ;
    }
    
    if ( !app.running ) {
        return ;
    }
    
    // @TODO: Update the application state, and handle input, AI, gameplay etc.
    /*
    
    
    
    
    
    
    
    */   
    
    return ;
}

void app_render( const app_t &app ) {
    
    // @TODO: Render the application state, and handle rendering of the scene, UI, etc.
    
    ( void )app;
    
    return ;
}

void app_end_frame( app_t &app ) {
    
    if ( app.state == app_state_t::ShuttingDown ) {
        app.running = false;
        app.state = app_state_t::Shutdown;
    }
    
    return ;
}

bool app_is_running( app_t &app ) {
    return app.running && ( app.state != app_state_t::ShuttingDown && app.state != app_state_t::Shutdown );
}

}
