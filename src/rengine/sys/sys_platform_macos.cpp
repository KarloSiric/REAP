/*======================================================================
   File: sys_platform_macos.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-27 17:32:33
   Last Modified by: ksiric
   Last Modified: 2026-04-28 19:03:56
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/sys/sys_platform_internal.h"

#if REAP_PLATFORM_MACOS

#include <mach-o/dyld.h>

#include <cstring>
#include <cerrno>
#include <cstdint>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <system_error>

namespace reap::rengine::sys
{

namespace {
    
bool sys_copy_path( char *out_path, const rcommon::u32 out_path_size, const std::filesystem::path &path ) {
    if ( out_path == nullptr || out_path_size == 0u ) {
        return false;
    }
    
    std::string path_string = path.lexically_normal().string();
    
    if ( path_string.size() >= out_path_size ) {
        out_path[0] = '\0';
        return false;
    }
    
    std::strncpy( out_path, path_string.c_str(), out_path_size - 1u ); 
    out_path[out_path_size - 1u] = '\0';
    
    return true;
}

const char *sys_find_argv_value( const sys_init_info_t &info, const char *arg_name ) {
    if ( info.argv == nullptr || arg_name == nullptr ) {
        return nullptr;
    }
    
    for ( int i = 1; i + 1 < info.argc; ++i ) {
        if ( std::strcmp( info.argv[i], arg_name ) == 0 ) {
            return info.argv[i+1];
        }
    }
    return nullptr;
}

}

sys_error_code_t sys_platform_build_paths( const sys_init_info_t &info_init, sys_paths_t &out_paths ) {
    
    out_paths = {};
    
    std::error_code ec{};
    
    const std::filesystem::path working_dir = std::filesystem::current_path( ec );
    if ( ec ) {
        return sys_error_code_t::ERR_PATH_QUERY_FAILED;
    }
    
    char executable_buffer[SYS_MAX_PATH_LENGTH]{};
    std::uint32_t executable_buffer_size = static_cast<std::uint32_t>( sizeof( executable_buffer ) );
    
    if ( _NSGetExecutablePath( executable_buffer, &executable_buffer_size ) != 0 ) {
        return sys_error_code_t::ERR_PATH_TOO_LONG;
    }    
    
    std::filesystem::path executable_path = std::filesystem::weakly_canonical( executable_buffer, ec );
       
    if ( ec ) {
        ec.clear();
        executable_path = executable_buffer;
    }
    
    const std::filesystem::path executable_dir = executable_path.parent_path();
    
    const char *base_path_override = sys_find_argv_value( info_init, "-basedir" );
    
    const std::filesystem::path base_path = ( base_path_override != nullptr && base_path_override[0] != '\0' ) ? std::filesystem::path( base_path_override ) : working_dir;
    
    const char *user_path_override = sys_find_argv_value( info_init, "-userpath" );
    
    std::filesystem::path user_path{};
    
    if ( user_path_override != nullptr && user_path_override[0] != '\0' ) {
        user_path = user_path_override;
    } else {
        const char *home = std::getenv( "HOME" );
        
        if ( home == nullptr || home[0] == '\0' ) {
            return sys_error_code_t::ERR_PATH_QUERY_FAILED;
        }
        
        user_path = std::filesystem::path( home ) / 
                    "Library" / 
                    "Application Support" / 
                    info_init.app_name;
    }
    
    std::filesystem::create_directories( user_path, ec );
    if ( ec ) {
        return sys_error_code_t::ERR_DIRECTORY_CREATE_FAILED;
    }
    if ( !sys_copy_path( out_paths.executable_path, sizeof( out_paths.executable_path ), executable_path ) ) {
        return sys_error_code_t::ERR_PATH_TOO_LONG;
    }    
    if ( !sys_copy_path( out_paths.executable_dir, sizeof( out_paths.executable_dir ), executable_dir ) ) {
        return sys_error_code_t::ERR_PATH_TOO_LONG;
    }
    if ( !sys_copy_path( out_paths.working_dir, sizeof( out_paths.working_dir ), working_dir ) ) {
        return sys_error_code_t::ERR_PATH_TOO_LONG;
    }
    if ( !sys_copy_path( out_paths.base_path, sizeof( out_paths.base_path ), base_path ) ) {
        return sys_error_code_t::ERR_PATH_TOO_LONG;
    }
    if ( !sys_copy_path( out_paths.user_path, sizeof( out_paths.user_path), user_path ) ) {
        return sys_error_code_t::ERR_PATH_TOO_LONG;
    }
    
    return sys_error_code_t::OK;   
}

void sys_platform_sleep_milliseconds( const rcommon::u64 milliseconds ) {
    timespec request{};
    request.tv_sec = static_cast<time_t>( milliseconds / 1000u );
    request.tv_nsec = static_cast<long>( ( milliseconds % 1000u ) * 1000000u );
    while ( nanosleep( &request, &request ) == -1 && errno == EINTR ) {
               
    }      
}

}       // namespace reap::rengine::sys
    
#endif
