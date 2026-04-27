/*======================================================================
   File: sys_platform.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-20 17:42:16
   Last Modified by: ksiric
   Last Modified: 2026-04-27 16:00:57
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/platform/sys_platform.h"
#include <chrono>

namespace reap::rengine::sys
{
    
sys_init_desc_t g_sys_init_desc = {};
sys_paths_t g_sys_paths = {};

platform_t sys_platform_type() {
#   if      REAP_PLATFORM_WINDOWS
                return platform_t::WINDOWS;
#   elif    REAP_PLATFORM_MACOS
                return platform_t::MACOSX;
#   elif     REAP_PLATFORM_LINUX
                return platform_t::LINUX;
#   else
                return platform_t::UNKNOWN;
#   endif
}    

compiler_t sys_compiler_type() {
#   if      REAP_COMPILER_MSVC
                return compiler_t::MSVC;
#   elif    REAP_COMPILER_CLANG
                return compiler_t::CLANG;
#   elif    REAP_COMPILER_GCC
                return compiler_t::GCC;
#   else
                return compiler_t::UNKNOWN;
#   endif
}

const char *sys_platform_name( platform_t type ) {
    switch( type ) {
        case platform_t::WINDOWS: return "Windows";
        case platform_t::LINUX: return "Linux";
        case platform_t::MACOSX: return "MacOS";
        default: return "Unknown";
    }
}   

const char *sys_compiler_name( compiler_t type ) {
    switch( type ) {
        case compiler_t::CLANG: return "Clang";
        case compiler_t::GCC: return "GCC";
        case compiler_t::MSVC: return "MSVC";
        default: return "Unknown";
    }
}

const char *sys_path_basename( const char *path ) {
    if ( path == nullptr || path[0] == '\0' ) {
        return "";
    }
    
    const char *basename = path;
    
    for ( const char *it = path; *it != '\0'; ++it ) {
        if ( *it == '/' || *it == '\\' ) {
            basename = it + 1;
        }
    }   
    
    return basename;
}

rcommon::com_f64 sys_time_now_seconds() {
    const auto now = std::chrono::steady_clock::now();
    const auto seconds = std::chrono::duration<rcommon::com_f64>( now.time_since_epoch() );
    return seconds.count();
}

bool sys_local_time( std::time_t time_value, std::tm &time_out ) {

#   if  REAP_PLATFORM_WINDOWS 
            return localtime_s( &time_out, &time_value ) == 0;
#   else 
            return localtime_r( &time_value, &time_out ) != nullptr;
#   endif
        
}
    
}       // namespace reap::rengine::sys
