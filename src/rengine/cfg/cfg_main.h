
#pragma once

#include "rengine/cfg/cfg_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::cfg {

constexpr rcommon::u32 CFG_MAX_LINE_LENGTH = 1024u;
constexpr rcommon::u32 CFG_MAX_PATH_LENGTH = 260u;
constexpr rcommon::u64 CFG_MAX_FILE_SIZE = 64u * 1024;

cfg_error_code_t cfg_init();
cfg_error_code_t cfg_shutdown();

cfg_error_code_t cfg_load_file( const char *path, bool required = false );
cfg_error_code_t cfg_load_default();
cfg_error_code_t cfg_load_autoexec();

cfg_error_code_t cfg_execute_line( const char *command_line );

}
