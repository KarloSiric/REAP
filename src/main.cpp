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
#include "rengine/host/host_main.h"
#include "rengine/platform/sys_platform.h"

/**
 * @brief OS-level entry point for the REAP executable.
 *
 * The executable owns the top-level host state and drives the main
 * frame loop through the engine host interface.
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
    
    reap::rengine::host::host_config_t host_config{};
    reap::rengine::host::host_state_t host_state{};
    
    if ( !reap::rengine::host::host_init( host_state, host_config ) ) {
        // @TODO: To add 
        return 1;
    }   
    
    while ( reap::rengine::host::host_is_running( host_state ) ) {
        const reap::rengine::rcommon::com_f64 current_time_seconds = reap::rengine::sys::sys_time_now_seconds();
        const reap::rengine::rcommon::com_f64 delta_time_seconds = static_cast<reap::rengine::rcommon::com_f32>( current_time_seconds - previous_time_seconds );
        
        previous_time_seconds = current_time_seconds;
        
        reap::rengine::host::host_begin_frame( host_state, delta_time_seconds );
        reap::rengine::host::host_update( host_state );
        reap::rengine::host::host_render( host_state );
        reap::rengine::host::host_end_frame( host_state );
    }
    
    reap::rengine::host::host_shutdown( host_state );
    
    return ( 0 );
}
