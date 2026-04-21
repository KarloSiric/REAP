#pragma once

#include "rengine/rcommon/com_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::sys
{

enum class sys_error_code_t : rcommon::u8 {
    OK = 0,
    
    ERR_UNSUPPORTED_PLATFORM,
    ERR_UNSUPPORTED_COMPILER,
    ERR_INVALID_PATH,
    ERR_TIME_UNAVAILABLE,
    ERR_LOCALTIME_FAILED
};

constexpr inline rcommon::com_error_t sys_error_code( sys_error_code_t error ) {
    return rcommon::com_error_make( rcommon::com_domain_t::COM_DOMAIN_SYS,  static_cast<rcommon::com_u16>( error ) );
}
    
}       // namespace reap::rengine::sys
