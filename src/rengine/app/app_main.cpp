/*======================================================================
   File: app_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 01:23:58
   Last Modified by: ksiric
   Last Modified: 2026-04-20 20:34:20
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/app/app_main.h"

namespace reap::rengine
{

/**
 * @brief Initializes the application runtime state for the first frame.
 *
 * The initial implementation is intentionally small and only prepares the
 * lifecycle state needed for the frame loop to begin.
 *
 * @param[in,out] app_state Mutable application runtime state.
 * @param[in] app_config Startup configuration for the application.
 *
 * @return True if initialization completed successfully.
 */
bool app_init( app_state_t &app_state, const app_config_t &app_config ) {
    ( void )app_config;
    
    app_state.stage = app_stage_t::INITIALIZING;
    app_state.running = true;
    app_state.has_focus = true;
    app_state.frame = {};
    
    app_state.stage = app_stage_t::RUNNING;
    
    return true;   
}

/**
 * @brief Shuts down the application runtime state.
 *
 * @param[in,out] app_state Mutable application runtime state.
 */
void app_shutdown( app_state_t &app_state) {
    app_state.running = false;
    app_state.stage = app_stage_t::SHUTDOWN;
}

/**
 * @brief Advances per-frame timing and counters at the start of a frame.
 *
 * @param[in,out] app_state Mutable application runtime state.
 * @param[in] delta_time_seconds Time elapsed since the previous frame.
 */
void app_begin_frame( app_state_t &app_state, com_f32 delta_time_seconds ) {
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

/**
 * @brief Runs the application update stage for the current frame.
 *
 * This function is currently a lifecycle placeholder and will later become
 * the place where engine and gameplay simulation work is coordinated.
 *
 * @param[in,out] app_state Mutable application runtime state.
 */
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

/**
 * @brief Runs the render stage for the current frame.
 *
 * This function is currently a placeholder until the render subsystem is
 * wired into the application frame loop.
 *
 * @param[in] app_state Read-only application state for the current frame.
 */
void app_render( const app_state_t &app_state ) {
    // @TODO: Render the application stage, and handle rendering of the scene, UI, etc.
    
    ( void )app_state;
    
    return ;
}

/**
 * @brief Finalizes the current frame and handles lifecycle transitions.
 *
 * @param[in,out] app_state Mutable application runtime state.
 */
void app_end_frame( app_state_t &app_state ) {
    if ( app_state.stage == app_stage_t::SHUTTINGDOWN ) {
        app_state.running = false;
        app_state.stage = app_stage_t::SHUTDOWN;
    }
    
    return ;
}

/**
 * @brief Reports whether the application should continue running.
 *
 * @param[in] app_state Current application runtime state.
 *
 * @return True while the main loop should continue executing.
 */
bool app_is_running( app_state_t &app_state ) {
    return app_state.running && ( app_state.stage != app_stage_t::SHUTTINGDOWN && app_state.stage != app_stage_t::SHUTDOWN );
}

}
