/*======================================================================
   File: cmd_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-21 22:26:01
   Last Modified by: ksiric
   Last Modified: 2026-04-22 01:30:06
   ---------------------------------------------------------------------
   Description:

   ---------------------------------------------------------------------
   License:
   Company:
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/cmd/cmd_main.h"
#include "rengine/cmd/cmd_error.h"
#include "rengine/rcommon/com_print.h"
#include <cctype>
#include <cstring>

namespace reap::rengine::cmd
{

cmd_registry_t g_cmd_registery{};

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

const cmd_t *cmd_find( const char *cmd_name ) {
    if ( !g_cmd_registery.initialized ) {
        rcommon::com_printf( "cmd_find: cmd system is not initialized." );
        return nullptr;
    }

    if ( cmd_name == nullptr || cmd_name[0] == '\0' ) {
        rcommon::com_printf( "cmd_find: invalid cmd name passed to find." );
        return nullptr;
    }

    for ( rcommon::u32 i = 0; i < g_cmd_registery.cmd_count; i++ ) {
        if ( strcmp( cmd_name, g_cmd_registery.cmd_commands[i].name ) == 0 ) {
            return &g_cmd_registery.cmd_commands[i];
        }
    }

    return nullptr;
}

cmd_error_code_t cmd_parse( char *command_line, rcommon::u32 &argc, char **argv ) {

    if ( command_line == nullptr || command_line[0] == '\0' ) {
        rcommon::com_printf( "cmd_parse: invalid command line passed for parsing." );
        return cmd::cmd_error_code_t::ERR_INVALID_COMMAND;
    }

    argc = 0;

    char *cursor_ptr = command_line;

    while ( *cursor_ptr != '\0' ) {
        while ( *cursor_ptr != '\0' && std::isspace( static_cast<unsigned char>( *cursor_ptr ) ) ) {
            cursor_ptr++;
        }
        if ( *cursor_ptr == '\0' ) {
            break;
        }
        if ( argc >= CMD_MAX_ARGUMENTS ) {
            return cmd::cmd_error_code_t::ERR_PARSE_FAILED;
        }
        argv[argc++] = cursor_ptr;
        while( *cursor_ptr != '\0' && !std::isspace( static_cast<unsigned char>( *cursor_ptr ) ) ) {
            cursor_ptr++;
        }

        if ( *cursor_ptr == '\0' ) {
            break;
        }

        *cursor_ptr = '\0';
        cursor_ptr++;
    }

    return ( argc > 0u ) ? cmd_error_code_t::OK : cmd_error_code_t::ERR_INVALID_COMMAND;
}

cmd_error_code_t cmd_execute( const char *command_line ) {
    if ( !g_cmd_registery.initialized ) {
        rcommon::com_printf( "cmd_execute: cmd system is not initialized; nothing to execute." );
        return cmd::cmd_error_code_t::ERR_NOT_INIT;
    }

    if ( command_line == nullptr || command_line[0] == '\0' ) {
        rcommon::com_printf( "cmd_execute: invalid command line passed to execute." );
        return cmd::cmd_error_code_t::ERR_INVALID_COMMAND;
    }

    rcommon::u32 cmd_argc{};
    char *cmd_argv[CMD_MAX_ARGUMENTS]{};

    char buffer[1024]{};

    strncpy( buffer, command_line, sizeof( buffer ) - 1 );

    // @TODO: Parsing the command line in the first place.
    cmd_error_code_t err = cmd_parse( buffer, cmd_argc, cmd_argv );

    if ( err != cmd::cmd_error_code_t::OK ) {
        rcommon::com_errorf( cmd_error_code( err ), "cmd_execute: cmd_parse: invalid parsing command line." );
    }

    return cmd_error_code_t::OK;

}
