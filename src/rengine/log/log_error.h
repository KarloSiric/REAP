#pragma once

#include "rengine/rcommon/com_error.h"
#include "rengine/rcommon/com_foundation.h"
namespace reap::rengine::log
{

enum class log_error_code_t : rcommon::u8 {
      OK = 0,
      
      LOG_NOT_INIT,
}; 

constexpr inline rcommon::com_error_t log_error_code( log_error_code_t error ) {
    return rcommon::com_error_make( rcommon::com_domain_t::COM_DOMAIN_LOG, static_cast<rcommon::com_u16>( error ) );
}
    
}       // namespace reap::rengine::log
