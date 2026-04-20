#pragma once

#include "rengine/common/foundation.h"

namespace reap::rengine::platform
{

enum class platform_type_t : u8 {
    UNKNOWN = 0,
    WINDOWS,
    LINUX,
    MACOSX
};    

enum class compiler_type_t : u8 {
    UNKNOWN = 0,
    CLANG,
    GCC,
    MSVC
};    

/**
 * @brief Returns the platform the engine was built for.
 *
 * This query exposes the operating-system family through the engine-owned
 * platform subsystem, which keeps the rest of the runtime insulated from
 * direct platform checks.
 *
 * @return The detected platform type for the current build.
 */
platform_type_t current_platform();

/**
 * @brief Returns the compiler used to build the engine.
 *
 * This is primarily useful for logging, diagnostics, and build/runtime
 * sanity checks when bringing the engine up across different environments.
 *
 * @return The detected compiler type for the current build.
 */
compiler_type_t current_compiler();

/**
 * @brief Converts a platform enum value into a readable string.
 *
 * This helper is intended for startup logs, diagnostics, and debug output.
 *
 * @param[in] type Platform value to convert.
 *
 * @return Constant string representation of the platform value.
 */
const char *platform_name( platform_type_t type );

/**
 * @brief Converts a compiler enum value into a readable string.
 *
 * This helper is intended for startup logs, diagnostics, and debug output.
 *
 * @param[in] type Compiler value to convert.
 *
 * @return Constant string representation of the compiler value.
 */
const char *compiler_name( compiler_type_t type );

/**
 * @brief Returns the basename portion of a path string.
 *
 * This helper is part of the platform API because path separator handling is
 * platform-facing behavior. It is primarily useful for subsystems such as
 * logging that only need the filename portion of a full path.
 *
 * The returned pointer refers to a position inside the original string.
 * No allocation or copy is performed.
 *
 * @param[in] path Path string to inspect.
 *
 * @return Pointer to the basename within the original path string.
 */
const char *path_basename( const char *path );

/**
 * @brief Returns the current monotonic time in seconds.
 *
 * The value comes from a monotonic clock and is intended for elapsed-time
 * calculations such as frame timing and runtime measurements. It is not
 * wall-clock time and should not be used for calendar or real-world time.
 *
 * @return Current monotonic timestamp in seconds.
 */
f64 time_now_seconds();
    
}       // namespace reap::rengine::platform
