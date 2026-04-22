/*======================================================================
   File: cvar_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-22 21:04:15
   Last Modified by: ksiric
   Last Modified: 2026-04-22 23:08:46
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/cvar/cvar_main.h"
#include "rengine/cvar/cvar_error.h"
#include "rengine/rcommon/com_print.h"

namespace reap::rengine::cvar
{
 
cvar_registry_t g_cvar_registry;

cvar_error_code_t cvar_init() {
    if ( g_cvar_registry.initialized ) {
        rcommon::com_printf( "cvar_init: cvar system already initialized." );
        return cvar_error_code_t::ERR_IS_INIT;
    }
    
    
    
    
    
    
    
    
    return cvar_error_code_t::OK;
}
        
    
    
    
    
    
}       // namespace reap::rengine::cvar
