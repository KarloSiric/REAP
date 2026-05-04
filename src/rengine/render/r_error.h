#pragma once

#include "rengine/rcommon/com_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::render
{

enum class r_error_code_t : rcommon::u8 {
    OK = 0,

    ERR_IS_INIT,
    ERR_NOT_INIT,

    ERR_INVALID_WINDOW_CFG,
    ERR_INVALID_VIEWPORT,

    ERR_FRAME_ALREADY_ACTIVE,
    ERR_FRAME_NOT_ACTIVE,
};

constexpr inline const char *R_ErrorName( const r_error_code_t error ) {
    switch ( error ) {
    case r_error_code_t::OK:
        return "OK";
    case r_error_code_t::ERR_IS_INIT:
        return "ERR_IS_INIT";
    case r_error_code_t::ERR_NOT_INIT:
        return "ERR_NOT_INIT";
    case r_error_code_t::ERR_INVALID_WINDOW_CFG:
        return "ERR_INVALID_WINDOW_CFG";
    case r_error_code_t::ERR_INVALID_VIEWPORT:
        return "ERR_INVALID_VIEWPORT";
    case r_error_code_t::ERR_FRAME_ALREADY_ACTIVE:
        return "ERR_FRAME_ALREADY_ACTIVE";
    case r_error_code_t::ERR_FRAME_NOT_ACTIVE:
        return "ERR_FRAME_NOT_ACTIVE";
    default:
        return "ERR_UNKNOWN";
    }
}

constexpr inline const char *R_ErrorDesc( const r_error_code_t error ) {
    switch ( error ) {
    case r_error_code_t::OK:
        return "operation completed successfully";
    case r_error_code_t::ERR_IS_INIT:
        return "render subsystem is already initialized";
    case r_error_code_t::ERR_NOT_INIT:
        return "render subsystem is not initialized";
    case r_error_code_t::ERR_INVALID_WINDOW_CFG:
        return "invalid render window configuration";
    case r_error_code_t::ERR_INVALID_VIEWPORT:
        return "invalid render viewport dimensions";
    case r_error_code_t::ERR_FRAME_ALREADY_ACTIVE:
        return "render frame is already active";
    case r_error_code_t::ERR_FRAME_NOT_ACTIVE:
        return "render frame is not active";
    default:
        return "unknown render error";
    }
}

constexpr inline rcommon::com_error_t R_ErrorCode( r_error_code_t code ) {
    return rcommon::Com_ErrorMake( rcommon::com_domain_t::COM_DOMAIN_RENDER , static_cast<rcommon::u16>( code ) );
}

}
