/*======================================================================
   File: cmd_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-21 22:26:01
   Last Modified by: ksiric
   Last Modified: 2026-04-21 23:13:42
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/cmd/cmd_main.h"
#include "rengine/rcommon/com_print.h"

namespace reap::rengine::cmd
{

cmd_registery_t g_cmd_registery{}; 

cmd_error_code_t cmd_init( ) {
    if ( g_cmd_registery.initialized ) {
        rcommon::com_printf( "cmd_init: command system already initialized." );
        return cmd::cmd_error_code_t::ERR_IS_INIT;
    }
    
    g_cmd_registery = {};
    
    g_cmd_registery.cmd_count = 0;
    g_cmd_registery.initialized = true;
    
    return cmd::cmd_error_code_t::OK;
}

void cmd_shutdown() {
    if ( !g_cmd_registery.initialized ) {
        rcommon::com_printf( "cmd_shutdown: command system is not initialized; nothing to shutdown" );
        return ;
    } 
    
    g_cmd_registery = {};
    // @NOTE: Additional setting, might not be neded but still
    g_cmd_registery.cmd_count = 0;
    g_cmd_registery.initialized = false;
    
    return ;
}

cmd_error_code_t cmd_register( const char *cmd_name, cmd_fn_t callback_fn, const char *cmd_description ) {
    if ( !g_cmd_registery.initialized ) {
        rcommon::com_printf( "cmd_register: command system is not initialized." );    
        return cmd::cmd_error_code_t::ERR_NOT_INIT;
    }
    
    // @NOTE: Safety checks that the function has to go through
    if ( cmd_name == nullptr || cmd_name[0] == '\0' ) {
        rcommon::com_printf( "cmd_register: invalid cmd passed to registery." );
        return cmd::cmd_error_code_t::ERR_INVALID_COMMAND;
    }
    
    const cmd_t *command = cmd_find( cmd_name );
    
    // @NOTE: command not found !
    if ( command != nullptr ) {
        rcommon::com_printf( "cmd_register: cmd '%s' already exists and is registered.", cmd_name );
        return cmd::cmd_error_code_t::ERR_COMMAND_ALREADY_EXISTS;
    }
    
    if ( callback_fn == nullptr ) {
        rcommon::com_printf( "cmd_register: invalid cmd callback passed to registery." );
        return cmd::cmd_error_code_t::ERR_INVALID_CALLBACK;
    }
    
    rcommon::u32 count = g_cmd_registery.cmd_count;
    
    if ( g_cmd_registery.cmd_count >= CMD_MAX_COMMANDS ) {
        rcommon::com_printf( "cmd_register: cannot register new cmd, registery is full." );
        return cmd::cmd_error_code_t::ERR_REGISTRY_FULL;
    }
    
    g_cmd_registery.cmd_commands[count].name = cmd_name;
    g_cmd_registery.cmd_commands[count].callback_fn = callback_fn;
    g_cmd_registery.cmd_commands[count].description = cmd_description;
    count++;
    
    g_cmd_registery.cmd_count = count;
    
    return cmd::cmd_error_code_t::OK;   
}
  
  
  
    
    
    
    
    
    
    
    
    
    
    
}
