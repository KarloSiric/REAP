/*======================================================================
   File: main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-18 23:12:08
   Last Modified by: ksiric
   Last Modified: 2026-04-20 21:58:11
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/app/app_main.h"
#include "rengine/platform/sys_platform.h"

/**
 * @brief OS-level entry point for the REAP executable.
 *
 * The executable owns the top-level application state and drives the main
 * frame loop through the engine application interface.
 *
 * @param[in] argc Number of command-line arguments.
 * @param[in] argv Command-line argument array.
 *
 * @return Process exit code.
 */

reap::rengine::rcommon::com_f64 previous_time_seconds = reap::rengine::sys::sys_time_now_seconds();

int main(int argc, char const *argv[])
{   
    ( void )argc;
    ( void )argv;
    
    reap::rengine::app::app_config_t app_config{};   
    reap::rengine::app::app_state_t app{};
    
    if ( !reap::rengine::app::app_init( app, app_config ) ) {
        // @TODO: To add 
        return 1;
    }   
    
    while ( reap::rengine::app::app_is_running( app ) ) {
        const reap::rengine::rcommon::com_f64 current_time_seconds = reap::rengine::sys::sys_time_now_seconds();
        const reap::rengine::rcommon::com_f64 delta_time_seconds = static_cast<reap::rengine::rcommon::com_f32>( current_time_seconds - previous_time_seconds );
        
        previous_time_seconds = current_time_seconds;
        
        reap::rengine::app::app_begin_frame( app, delta_time_seconds );
        reap::rengine::app::app_update( app );
        reap::rengine::app::app_render( app );
        reap::rengine::app::app_end_frame( app );
    }
    
    reap::rengine::app::app_shutdown( app );
    
    return ( 0 );
}
