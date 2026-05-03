#pragma once

#include "rengine/rcommon/com_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::host
{

enum class host_error_code_t : rcommon::u8 {
    OK = 0,

    ERR_NOT_INIT,
    ERR_IS_INIT,
    ERR_INITIALIZING,
};

constexpr inline const char *host_error_name( const host_error_code_t error ) {
    switch ( error ) {
    case host_error_code_t::OK:
        return "OK";
    case host_error_code_t::ERR_NOT_INIT:
        return "ERR_NOT_INIT";
    case host_error_code_t::ERR_IS_INIT:
        return "ERR_IS_INIT";
    case host_error_code_t::ERR_INITIALIZING:
        return "ERR_INITIALIZING";
    default:
        return "ERR_UNKNOWN";
    }
}

constexpr inline const char *host_error_desc( const host_error_code_t error ) {
    switch ( error ) {
    case host_error_code_t::OK:
        return "operation completed successfully";
    case host_error_code_t::ERR_NOT_INIT:
        return "host subsystem is not initialized";
    case host_error_code_t::ERR_IS_INIT:
        return "host subsystem is already initialized";
    case host_error_code_t::ERR_INITIALIZING:
        return "host subsystem failed while initializing";
    default:
        return "unknown host error";
    }
}

constexpr inline rcommon::com_error_t host_error_code( host_error_code_t error ) {
    return rcommon::com_error_make( rcommon::com_domain_t::COM_DOMAIN_HOST, static_cast<rcommon::com_u16>( error ) );
}

}
