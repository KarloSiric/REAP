/*======================================================================
   File: sys_platform.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-20 17:42:16
   Last Modified by: ksiric
   Last Modified: 2026-05-01 11:45:14
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/sys/sys_platform.h"
#include "rengine/sys/sys_platform_internal.h"

#include <cstring>
#include <chrono>

namespace reap::rengine::sys
{

sys_runtime_state_t g_sys_runtime_state;

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

sys_error_code_t sys_init( const sys_init_info_t &info_init ) {
    if ( g_sys_runtime_state.initialized ) {
        return sys_error_code_t::ERR_IS_INIT;
    }
    if ( info_init.app_name == nullptr || info_init.app_name[0] == '\0' ) {
        return sys_error_code_t::ERR_INVALID_ARGUMENT;
    }
    if ( info_init.organization_name == nullptr || info_init.organization_name[0] == '\0' ) {
        return sys_error_code_t::ERR_INVALID_ARGUMENT;
    }
    g_sys_runtime_state = {};
    
    std::strncpy(
                 g_sys_runtime_state.app_name,
                 info_init.app_name,
                 sizeof( g_sys_runtime_state.app_name ) - 1u 
    );
    
    std::strncpy(
                 g_sys_runtime_state.organization_name,
                 info_init.organization_name,
                 sizeof( g_sys_runtime_state.organization_name ) - 1u 
    );
    
    g_sys_runtime_state.argc = info_init.argc;
    g_sys_runtime_state.argv = info_init.argv;
    
    sys_error_code_t paths_result = sys_platform_build_paths( info_init, g_sys_runtime_state.sys_paths );
    
    if ( paths_result != sys_error_code_t::OK ) {
        g_sys_runtime_state = {};
        return paths_result;
    }
    
    g_sys_runtime_state.initialized = true;
    
    return sys_error_code_t::OK;
}

sys_error_code_t sys_shutdown() {
    if ( !g_sys_runtime_state.initialized ) {
        return sys_error_code_t::ERR_NOT_INIT;
    }
    
    g_sys_runtime_state = {};
    
    g_sys_runtime_state.initialized = false;
    
    return sys_error_code_t::OK;
}

bool sys_is_initialized() {
    return g_sys_runtime_state.initialized;
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

#   if      REAP_PLATFORM_WINDOWS 
                return localtime_s( &time_out, &time_value ) == 0;
#   else 
                return localtime_r( &time_value, &time_out ) != nullptr;
#   endif 
                
}

const sys_paths_t &sys_paths() {
    return g_sys_runtime_state.sys_paths;
}

sys_error_code_t sys_get_paths( sys_paths_t &out_paths ) {
    if ( !g_sys_runtime_state.initialized ) {
        return sys_error_code_t::ERR_NOT_INIT;
    }   
    
    out_paths = g_sys_runtime_state.sys_paths;
    
    return sys_error_code_t::OK;
}
 
void sys_sleep_milliseconds( rcommon::u64 milliseconds ) {
    sys_platform_sleep_milliseconds( milliseconds );
    return ;
}   

}       // namespace reap::rengine::sys
