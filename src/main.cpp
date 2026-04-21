/*======================================================================
   File: main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-18 23:12:08
   Last Modified by: ksiric
   Last Modified: 2026-04-21 19:23:09
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/host/host_main.h"
#include "rengine/log/log_main.h"
#include "rengine/platform/sys_platform.h"
#include "rengine/rcommon/com_print.h"
#include "rengine/render/r_error.h"

namespace rr = reap::rengine;
namespace host = rr::host;
namespace log = rr::log;
namespace rc = rr::rcommon;
namespace render = rr::render;
namespace sys = rr::sys;

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
int main(int argc, char const *argv[])
{   
    ( void )argc;
    ( void )argv;
    
    const auto log_init_result = log::log_init();

    if ( log_init_result != log::log_error_code_t::OK ) {
        rc::com_errorf( log::log_error_code( log_init_result ), "log_init failed." );
        return 1;
    }
    
    // @NOTE: Temporary testing purposes.
    // rc::com_errorf( render::r_error_code( render::r_error_code_t::ERR_INVALID_VIEWPORT ), "Temporary testing of the com_errorf to see how it will print an error." );

    host::host_config_t host_config{};
    host::host_state_t host_state{};
    rc::com_f64 previous_time_seconds = sys::sys_time_now_seconds();
    
    if ( host::host_init( host_state, host_config ) != host::host_error_code_t::OK ) {
        log::log_shutdown();
        return 1;
    }   
    
    while ( host::host_is_running( host_state ) ) {
        const rc::com_f64 current_time_seconds = sys::sys_time_now_seconds();
        const rc::com_f64 delta_time_seconds = static_cast<rc::com_f32>( current_time_seconds - previous_time_seconds );
        
        previous_time_seconds = current_time_seconds;
        
        host::host_begin_frame( host_state, delta_time_seconds );
        host::host_update( host_state );
        host::host_render( host_state );
        host::host_end_frame( host_state );
    }
    
    host::host_shutdown( host_state );
    log::log_shutdown();
    
    return ( 0 );
}
