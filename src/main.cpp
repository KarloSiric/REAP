/*======================================================================
   File: main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-18 23:12:08
   Last Modified by: ksiric
   Last Modified: 2026-04-19 17:14:13
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/app/app.h"

int main(int argc, char const *argv[])
{   
    ( void )argc;
    ( void )argv;
    
    reap::rengine::app_config_t app_config{};   
    reap::rengine::app_state_t app{};
    
    if ( !reap::rengine::app_init( app, app_config ) ) {
        // @TODO: To add 
        return 1;
    }   
    
    while ( reap::rengine::app_is_running( app ) ) {
        // @TODO: Running the application here and all
        
        constexpr reap::rengine::f32 fixed_delta_seconds = 1.0f / 60.0f;
        
        reap::rengine::app_begin_frame( app, fixed_delta_seconds );
        reap::rengine::app_update( app );
        reap::rengine::app_render( app );
        reap::rengine::app_end_frame( app );
    }
    
    reap::rengine::app_shutdown( app );
    
    return ( 0 );
}
