
#pragma once

#include "rengine/cfg/cfg_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::cfg {

constexpr rcommon::u32 CFG_MAX_LINE_LENGTH = 1024u;
constexpr rcommon::u32 CFG_MAX_PATH_LENGTH = 260u;
constexpr rcommon::u64 CFG_MAX_FILE_SIZE = 64u * 1024;

cfg_error_code_t Cfg_Init();
cfg_error_code_t Cfg_Shutdown();

cfg_error_code_t Cfg_LoadFile( const char *path, bool required = false );
cfg_error_code_t Cfg_LoadDefault();
cfg_error_code_t Cfg_LoadAutoexec();

cfg_error_code_t Cfg_ExecuteLine( const char *command_line );

}
