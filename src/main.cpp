/*======================================================================
   File: main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-18 23:12:08
   Last Modified by: ksiric
   Last Modified: 2026-05-01 21:30:06
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/host/host_main.h"

#include <cstdlib>

namespace rr = reap::rengine;
namespace host = rr::host;

int main(int argc, char const *argv[])
{   
    host::host_state_t  host_state{};
    host_state.config.argc = argc;
    host_state.config.argv = argv;
    
    if ( host::host_init( host_state ) != host::host_error_code_t::OK ) {
        return ( EXIT_FAILURE );
    }
    
    while( host::host_is_running( host_state ) ) {
        host::host_begin_frame( host_state );
        host::host_update( host_state );
        host::host_render( host_state );
        host::host_end_frame( host_state );
    }
    
    host::host_shutdown( host_state );
    
    return ( EXIT_SUCCESS );
}
