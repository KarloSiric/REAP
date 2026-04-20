#pragma once

/**
 * @brief Common engine result/error codes.
 *
 * This lives in rcommon so all subsystems can use the same baseline
 * contract for success/failure without inventing separate ad-hoc enums.
 */
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::rcommon {

/**
 * @brief Canonical result code used across the engine.
 *
 * The enum is intentionally compact and stable.  Individual systems can layer
 * their own richer error types on top of this baseline when needed.
 */
enum class error_code_t : com_u8 {
    OK = 0,
    FAILED,
    INVALID_ARGUMENT,
    INVALID_STATE,
    INVALID_OPERATION,
    NOT_INITIALIZED,
    ALREADY_INITIALIZED,
    OUT_OF_MEMORY,
    NOT_FOUND,
    UNSUPPORTED,
    IO_ERROR,
    INTERNAL_ERROR
};

/**
 * @brief Returns true when the code represents a success path.
 *
 * @param[in] code Error/result code to test.
 * @return True if code equals error_code_t::OK.
 */
constexpr bool com_error_ok( const error_code_t code ) {
    return code == error_code_t::OK;
}

/**
 * @brief Returns true when the code represents an error path.
 *
 * @param[in] code Error/result code to test.
 * @return True when code is not error_code_t::OK.
 */
constexpr bool com_error_failed( const error_code_t code ) {
    return code != error_code_t::OK;
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
inline const char *com_error_name( const error_code_t code ) {
    switch ( code ) {
        case error_code_t::OK:                   return "OK";
        case error_code_t::FAILED:               return "FAILED";
        case error_code_t::INVALID_ARGUMENT:     return "INVALID_ARGUMENT";
        case error_code_t::INVALID_STATE:        return "INVALID_STATE";
        case error_code_t::INVALID_OPERATION:    return "INVALID_OPERATION";
        case error_code_t::NOT_INITIALIZED:      return "NOT_INITIALIZED";
        case error_code_t::ALREADY_INITIALIZED:  return "ALREADY_INITIALIZED";
        case error_code_t::OUT_OF_MEMORY:        return "OUT_OF_MEMORY";
        case error_code_t::NOT_FOUND:            return "NOT_FOUND";
        case error_code_t::UNSUPPORTED:          return "UNSUPPORTED";
        case error_code_t::IO_ERROR:             return "IO_ERROR";
        case error_code_t::INTERNAL_ERROR:       return "INTERNAL_ERROR";
        default:                                 return "UNKNOWN_ERROR";
    }
}

} // namespace reap::rengine::rcommon
