#pragma once

#include "rengine/rcommon/com_foundation.h"
#include "rengine/rcommon/com_error.h"

namespace reap::rengine::cvar
{
    
enum class cvar_error_code_t : rcommon::u8 {
    OK = 0,
    
    ERR_NOT_INIT,
    ERR_IS_INIT,
    ERR_INVALID_CVAR,
    ERR_CVAR_ALREADY_EXISTS,
    ERR_CVAR_NOT_FOUND,
    ERR_REGISTRY_FULL,
    ERR_READONLY,
    ERR_CHEAT_PROTECTED
};    

constexpr inline rcommon::com_error_t cvar_error_make( cvar_error_code_t error ) {
    return rcommon::com_error_make( rcommon::com_domain_t::COM_DOMAIN_CVAR, static_cast<rcommon::com_u16>( error ) );
}
    
}       // namespace reap::rengine::cvar
