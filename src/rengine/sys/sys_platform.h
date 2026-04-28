#pragma once

#include "rengine/sys/sys_error.h"
#include "rengine/rcommon/com_foundation.h"

#include <ctime>

namespace reap::rengine::sys
{

constexpr rcommon::u32 SYS_MAX_PATH_LENGTH = 1024u;
constexpr rcommon::u32 SYS_MAX_NAME_LENGTH = 256;

enum class platform_t : rcommon::com_u8 {
    UNKNOWN = 0,
    WINDOWS,
    LINUX,
    MACOSX
};

enum class compiler_t : rcommon::com_u8 {
    UNKNOWN = 0,
    CLANG,
    GCC,
    MSVC
};

struct sys_init_info_t {
    int argc{ 0 };
    const char *const *argv{ nullptr };

    const char *app_name{ nullptr };
    const char *organization_name{ nullptr };
};


struct sys_paths_t {
    char executable_path[SYS_MAX_PATH_LENGTH]{};
    char executable_dir[SYS_MAX_PATH_LENGTH]{};
    char working_dir[SYS_MAX_PATH_LENGTH]{};

    char base_path[SYS_MAX_PATH_LENGTH]{};
    char user_path[SYS_MAX_PATH_LENGTH]{};
};

struct sys_runtime_state_t {
    bool initialized{ false };
    
    char app_name[SYS_MAX_NAME_LENGTH]{};
    char organization_name[SYS_MAX_NAME_LENGTH]{};
    
    int argc{ 0u };
    const char *const *argv{ nullptr };
    sys_paths_t sys_paths{};
    
};

extern sys_runtime_state_t g_sys_runtime_state;

sys_error_code_t sys_platform_build_paths( const sys_init_info_t &info_init, sys_paths_t &out_paths );

sys_error_code_t sys_init( const sys_init_info_t &init_info );
void sys_shutdown();

bool sys_is_initialized();

platform_t sys_platform_type();
compiler_t sys_compiler_type();

const char *sys_platform_name( platform_t type );
const char *sys_compiler_name( compiler_t type );

const sys_paths_t &sys_paths();
sys_error_code_t sys_get_paths( sys_paths_t &out_paths );

const char *sys_path_basename( const char *path );

rcommon::com_f64 sys_time_now_seconds();
void sys_sleep_milliseconds( rcommon::u32 milliseconds );

bool sys_local_time( std::time_t time_value, std::tm &time_out );

/* CROSS PLATFORM AND COMPILER DETECTION */

#   if  defined( _WIN32 ) 
#       define REAP_PLATFORM_WINDOWS    1
#   else
#       define REAP_PLATFORM_WINDOWS    0
#   endif

#   if  defined( __APPLE__ ) && defined( __MACH__ )
#       define REAP_PLATFORM_MACOS      1
#   else
#       define REAP_PLATFORM_MACOS      0
#   endif

#   if  defined( __linux__ ) 
#       define REAP_PLATFORM_LINUX      1
#   else
#       define REAP_PLATFORM_LINUX      0
#   endif

#   if  defined( _MSC_VER ) 
#       define REAP_COMPILER_MSVC       1
#   else
#       define REAP_COMPILER_MSVC       0
#   endif

#   if  defined( __clang__ ) 
#       define REAP_COMPILER_CLANG      1
#   else
#       define REAP_COMPILER_CLANG      0
#   endif

#   if  defined( __GNUC__ ) && !defined( __clang__ ) 
#       define REAP_COMPILER_GCC        1
#   else
#       define REAP_COMPILER_GCC        0
#   endif

}
