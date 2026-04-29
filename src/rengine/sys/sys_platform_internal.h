#pragma once

#include "rengine/sys/sys_platform.h"
#include "rengine/sys/sys_error.h"

namespace reap::rengine::sys {

sys_error_code_t sys_platform_build_paths( const sys_init_info_t &info_init, sys_paths_t &out_paths );

void sys_platform_sleep_milliseconds(const rcommon::u64 milliseconds );

} // namespace reap::rengine::sys
