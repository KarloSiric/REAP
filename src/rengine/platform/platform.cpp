/*======================================================================
   File: platform.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-20 17:42:16
   Last Modified by: ksiric
   Last Modified: 2026-04-20 18:27:44
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/platform/platform.h"
#include <chrono>

namespace reap::rengine::platform 
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
platform_type_t current_platform() {
#   if defined( _WIN32 ) 
        return platform_type_t::WINDOWS;
#   elif defined( __APPLE__ ) 
        return platform_type_t::MACOSX;
#   elif defined( __linux__ ) 
        return platform_type_t::LINUX;
#   else 
        return platform_type_t::UNKNOWN;
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
compiler_type_t current_compiler() {
#   if defined( __clang__ ) 
        return compiler_type_t::CLANG;
#   elif defined( _MSC_VER )
        return compiler_type_t::MSVC;
#   elif defined( __GNUC__ )
        return compiler_type_t::GCC;
#   else
        return compiler_type_t::UNKNOWN;
#   endif
}

/**
 * @brief Converts a platform enum into a readable string.
 *
 * @param[in] type Platform enum value to convert.
 *
 * @return Constant string representation of the supplied platform.
 */
const char *platform_name( platform_type_t type ) {
    switch( type ) {
        case reap::rengine::platform::platform_type_t::WINDOWS: return "Window";
        case reap::rengine::platform::platform_type_t::LINUX: return "Linux";
        case reap::rengine::platform::platform_type_t::MACOSX: return "MacOS";
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
const char *compiler_name( compiler_type_t type ) {
    switch( type ) {
        case reap::rengine::platform::compiler_type_t::CLANG: return "Clang";
        case reap::rengine::platform::compiler_type_t::GCC: return "GCC";
        case reap::rengine::platform::compiler_type_t::MSVC: return "MSVC";
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
const char *path_basename( const char *path ) {
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
f64 time_now_seconds() {
    const auto now = std::chrono::steady_clock::now();
    const auto seconds = std::chrono::duration<f64>( now.time_since_epoch() );
    return seconds.count();
}
    
}       // namespace reap::rengine::platform
