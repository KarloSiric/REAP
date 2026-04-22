/*======================================================================
   File: sys_platform.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-20 17:42:16
   Last Modified by: ksiric
   Last Modified: 2026-04-22 01:49:12
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

/**
 * @brief Returns the build-target platform for the current executable.
 *
 * Platform detection is resolved at compile time so the rest of the engine
 * can query an engine-owned enum instead of using preprocessor checks
 * directly.
 *
 * @return Detected platform type for the current build.
 */
platform_t sys_platform_type() {
#   if defined( _WIN32 ) 
        return platform_t::WINDOWS;
#   elif defined( __APPLE__ ) 
        return platform_t::MACOSX;
#   elif defined( __linux__ ) 
        return platform_t::LINUX;
#   else 
        return platform_t::UNKNOWN;
#   endif
}    

/**
 * @brief Returns the compiler used to build the current executable.
 *
 * Compiler detection is resolved at compile time and mainly used for
 * diagnostics and startup visibility.
 *
 * @return Detected compiler type for the current build.
 */
compiler_t sys_compiler_type() {
#   if defined( __clang__ ) 
        return compiler_t::CLANG;
#   elif defined( _MSC_VER )
        return compiler_t::MSVC;
#   elif defined( __GNUC__ )
        return compiler_t::GCC;
#   else
        return compiler_t::UNKNOWN;
#   endif
}

/**
 * @brief Converts a platform enum into a readable string.
 *
 * @param[in] type Platform enum value to convert.
 *
 * @return Constant string representation of the supplied platform.
 */
const char *sys_platform_name( platform_t type ) {
    switch( type ) {
        case platform_t::WINDOWS: return "Windows";
        case platform_t::LINUX: return "Linux";
        case platform_t::MACOSX: return "MacOS";
        default: return "Unknown";
    }
}   

/**
 * @brief Converts a compiler enum into a readable string.
 *
 * @param[in] type Compiler enum value to convert.
 *
 * @return Constant string representation of the supplied compiler.
 */
const char *sys_compiler_name( compiler_t type ) {
    switch( type ) {
        case compiler_t::CLANG: return "Clang";
        case compiler_t::GCC: return "GCC";
        case compiler_t::MSVC: return "MSVC";
        default: return "Unknown";
    }
}
/**
 * @brief Returns the basename portion of a path string.
 *
 * This helper scans the provided path and returns a pointer to the character
 * immediately following the last path separator. Both Unix and Windows path
 * separators are supported.
 *
 * The returned pointer refers to a position inside the original string.
 * No allocation or copy is performed.
 *
 * @param[in] path Path string to inspect.
 *
 * @return Pointer to the basename within the original path string.
 */
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

/**
 * @brief Returns the current monotonic timestamp in seconds.
 *
 * Uses `std::chrono::steady_clock`, which is intended for elapsed-time
 * measurement and is not tied to wall-clock adjustments. The returned value
 * is measured from the clock's unspecified epoch.
 *
 * @return Current monotonic timestamp in seconds.
 */
rcommon::com_f64 sys_time_now_seconds() {
    const auto now = std::chrono::steady_clock::now();
    const auto seconds = std::chrono::duration<rcommon::com_f64>( now.time_since_epoch() );
    return seconds.count();
}

bool sys_local_time( std::time_t time_value, std::tm &time_out ) {

#   if defined( _WIN32 ) 
        return localtime_s( &time_out, &time_value ) == 0;
#   else 
        return localtime_r( &time_value, &time_out ) != nullptr;
#   endif
        
}
    
}       // namespace reap::rengine::sys
