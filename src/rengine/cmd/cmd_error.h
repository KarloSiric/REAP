#pragma once

#include "rengine/rcommon/com_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::cmd
{

enum class cmd_error_code_t : rcommon::u8 {
    OK,

    ERR_NOT_INIT,
    ERR_IS_INIT,
    ERR_INVALID_COMMAND,
    ERR_COMMAND_ALREADY_EXISTS,
    ERR_COMMAND_NOT_FOUND,
    ERR_REGISTRY_FULL,
    ERR_PARSE_FAILED,
    ERR_INVALID_CALLBACK
};

constexpr inline rcommon::com_error_t cmd_error_code( cmd_error_code_t error ) {
    return rcommon::com_error_make( rcommon::com_domain_t::COM_DOMAIN_CMD , static_cast<rcommon::com_u16>( error ) );
}

}
