#pragma once

#include "rengine/cmd/cmd_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::cmd
{

#define CMD_MAX_COMMANDS        256u
#define CMD_MAX_ARGUMENTS       16u

using cmd_fn_t = void (*)( rcommon::u32 argc, char **argv );

struct cmd_t {
    const char *name;
    cmd_fn_t    callback_fn;
    const char *description;
};

struct cmd_registry_t {
    cmd_t cmd_commands[CMD_MAX_COMMANDS];
    rcommon::u32 cmd_count;
    bool initialized;
};

cmd_error_code_t cmd_init( );

void cmd_shutdown();

cmd_error_code_t cmd_register( const char *cmd_name, cmd_fn_t callback_fn, const char *cmd_description );

const cmd_t *cmd_find( const char *cmd_name );

cmd_error_code_t cmd_parse( char *command_line, rcommon::u32 &argc, char **argv );

cmd_error_code_t cmd_execute( const char *command_line );

}
