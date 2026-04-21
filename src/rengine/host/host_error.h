#pragma once

#include "rengine/rcommon/com_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::host
{
    
enum class host_error_code_t : rcommon::u8 { 
    OK = 0,
    
    ERR_NOT_INIT,                          // host not initialized.
    ERR_IS_INIT,                           // host already initialized.
    ERR_INITIALIZING,                      // host was initializing another system.
};    

constexpr inline rcommon::com_error_t host_error_code( host_error_code_t error ) {
    return rcommon::com_error_make( rcommon::com_domain_t::COM_DOMAIN_HOST, static_cast<rcommon::com_u16>( error ) );
}
    
}       // namespace reap::rengine::host
