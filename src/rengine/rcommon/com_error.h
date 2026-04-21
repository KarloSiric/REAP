#pragma once

/**
 * @brief Common engine result/error codes.
 *
 * This lives in rcommon so all subsystems can use the same baseline
 * contract for success/failure without inventing separate ad-hoc enums.
 */
#include "rengine/rcommon/com_foundation.h"

#define COM_MSG_MAX                 2048u
#define COM_ERROR_MSG_MAX           2048u

namespace reap::rengine::rcommon {
    
// @NOTE: One common error_code that is tightly packed for it to be 
//        used by each and every other subsystem, or better say they
//        all convert their local enum subsystem error type to this one
//        so that the common Errorf printing function can use this.

using com_error_t = com_u32;


// @TODO: Simple domain name which can be extended to each and every single 
//        subsystem as we keep expanding the engine and adding new things.
enum class com_domain_t : u16 {
    COM_DOMAIN_COMMON = 0,
    COM_DOMAIN_RENDER,
    COM_DOMAIN_LOG,
    COM_DOMAIN_HOST,
    COM_DOMAIN_SYS,
    COM_DOMAIN_AUDIO,
    COM_DOMAIN_FS,
    COM_DOMAIN_NET,
    COM_DOMAIN_GAME
};


/**
 * @brief Canonical result code used across the engine.
 *
 * The enum is intentionally compact and stable.  Individual systems can layer
 * their own richer error types on top of this baseline when needed.
 */
enum class com_error_code_t : com_u8 {
    OK = 0,
    ERR_FAILED,
    ERR_INVALID_ARGUMENT,
    ERR_INVALID_STATE,
    ERR_INVALID_OPERATION,
    ERR_NOT_INIT,
    ERR_IS_INIT,
    ERR_OUT_OF_MEMORY,
    ERR_NOT_FOUND,
    ERR_UNSUPPORTED,
    ERR_IO_ERROR,
    ERR_INTERNAL_ERROR
};


/**
 * @brief Returns true when the code represents a success path.
 *
 * @param[in] code Error/result code to test.
 * @return True if code equals com_error_code_t::OK.
 */
constexpr bool com_error_ok( const com_error_code_t code ) {
    return code == com_error_code_t::OK;
}

/**
 * @brief Returns true when the code represents an error path.
 *
 * @param[in] code Error/result code to test.
 * @return True when code is not com_error_code_t::OK.
 */
constexpr bool com_error_failed( const com_error_code_t code ) {
    return code != com_error_code_t::OK;
}

/**
 * @brief Human readable error-name helper for debug and log output.
 *
 * The returned pointer is valid for static storage duration.
 *
 * @param[in] code Code to convert.
 *
 * @return Constant error name string.
 */
inline const char *com_error_name( const com_error_code_t code ) {
    switch ( code ) {
        case com_error_code_t::OK:                       return "OK";
        case com_error_code_t::ERR_FAILED:               return "COM_FAILED";
        case com_error_code_t::ERR_INVALID_ARGUMENT:     return "COM_INVALID_ARGUMENT";
        case com_error_code_t::ERR_INVALID_STATE:        return "COM_INVALID_STATE";
        case com_error_code_t::ERR_INVALID_OPERATION:    return "COM_INVALID_OPERATION";
        case com_error_code_t::ERR_NOT_INIT:             return "COM_NOT_INITIALIZED";
        case com_error_code_t::ERR_IS_INIT:              return "COM_ALREADY_INITIALIZED";
        case com_error_code_t::ERR_OUT_OF_MEMORY:        return "COM_OUT_OF_MEMORY";
        case com_error_code_t::ERR_NOT_FOUND:            return "NOT_FOUND";
        case com_error_code_t::ERR_UNSUPPORTED:          return "COM_UNSUPPORTED";
        case com_error_code_t::ERR_IO_ERROR:             return "IO_ERROR";
        case com_error_code_t::ERR_INTERNAL_ERROR:       return "COM_INTERNAL_ERROR";
        default:                                         return "COM_UNKNOWN_ERROR";
    }
}

constexpr inline com_error_t com_error_make( const com_domain_t domain, const com_u16 local_enum_error_code ) {
    return ( static_cast<com_error_t>( domain) << 16u | static_cast<com_error_t>( local_enum_error_code ) );
}

constexpr inline com_domain_t com_error_domain( const com_error_t error ) {
    return static_cast<com_domain_t>( ( error >> 16u ) & 0xFFFF );
}

constexpr inline com_u16 com_error_code( const com_error_t error ) {
    return static_cast<com_u16>( error & 0xFFFF );
}

} // namespace reap::rengine::rcommon
