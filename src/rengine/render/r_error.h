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

constexpr inline rcommon::com_error_t r_error_code( r_error_code_t code ) {
    return rcommon::com_error_make( rcommon::com_domain_t::COM_DOMAIN_RENDER , static_cast<rcommon::u16>( code ) );
}

}

