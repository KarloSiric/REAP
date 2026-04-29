/*======================================================================
   File: sys_platform_linux.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-27 17:32:41
   Last Modified by: ksiric
   Last Modified: 2026-04-30 00:06:26
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/sys/sys_platform_internal.h"

#if REAP_PLATFORM_LINUX

#include <chrono>
#include <cstdlib>
#include <cerrno>
#include <ctime>
#include <cstring>
#include <filesystem>
#include <string>
#include <system_error>
#include <unistd.h>

namespace reap::rengine::sys
{

sys_error_code_t sys_platform_build_paths(const sys_init_info_t &info_init, sys_paths_t &out_paths ) {
    std::error_code ec{};
    out_paths = {};
    
    const std::filesystem::path working_dir = std::filesystem::curentcurrent_path( ec );
    if ( ec ) {
        return sys_error_code_t::ERR_PATH_QUERY_FAILED;
    }
       
    
    
       
    return sys_error_code_t::OK;
}
    
}       // namespace reap::rengine::sys

#endif
