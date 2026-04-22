/*======================================================================
   File: cvar_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-22 21:04:15
   Last Modified by: ksiric
   Last Modified: 2026-04-23 00:54:32
   ---------------------------------------------------------------------
   Description:

   ---------------------------------------------------------------------
   License:
   Company:
   Version: 0.1.0
 ======================================================================
																	   */
#include "rengine/cvar/cvar_main.h"
#include "rengine/cvar/cvar_error.h"
#include "rengine/rcommon/com_print.h"
#include <cctype>
#include <cstdlib>
#include <cstring>

namespace reap::rengine::cvar {

cvar_registry_t g_cvar_registry;

cvar_error_code_t cvar_init() {
	if ( g_cvar_registry.initialized ) {
		rcommon::com_printf( "cvar_init: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_IS_INIT), cvar_error_desc( cvar_error_code_t::ERR_IS_INIT ) );
		return cvar_error_code_t::ERR_IS_INIT;
	}

	g_cvar_registry = {};
	g_cvar_registry.initialized = true;
	return cvar_error_code_t::OK;
}

// @NOTE(karlo): helper func for parsing the proper bool value
bool cvar_parse_bool( const char *value ) {
    // @NOTE(karlo) -> for design wise choice I went for nullptr, 0, false, "", "false", "off", "no" to be a bool false value.
    if ( value == nullptr || value[0] == '\0' ) {
        return false;
    }
    
    char lower[32]{};
    
    for ( int i = 0; i < 31 && lower[i] != '\0'; i++ ) {
        lower[i] = static_cast<char>( tolower( static_cast<unsigned char>( value[i] ) ) );
    }
    
    if ( std::strcmp( value, "0"     )     == 0 || 
         std::strcmp( value, "false" )     == 0 ||
         std::strcmp( value, "off"   )     == 0 ||
         std::strcmp( value, "no"    )     == 0    ) {
        return false;
    }
    
    if ( std::strcmp( value, "1" ) == 0 ||
         std::strcmp( value, "true" ) == 0 ||
         std::strcmp( value, "on" ) == 0 ||
         std::strcmp( value, "yes" ) == 0 ) {
        return true;
    }
    
    return ( std::atoi( value ) != 0 );
}

cvar_error_code_t cvar_register( const char *name, const char *default_value, cvar_flags_t flags ) {
	if ( !g_cvar_registry.initialized ) {
		rcommon::com_printf( "cvar_register: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_NOT_INIT ), cvar_error_desc( cvar_error_code_t::ERR_NOT_INIT ) );
		return cvar_error_code_t::ERR_NOT_INIT;
	}

	if ( name == nullptr || name[0] == '\0' ) {
		rcommon::com_printf( "cvar_register: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_INVALID_CVAR ), cvar_error_desc( cvar_error_code_t::ERR_INVALID_CVAR ) );
		return cvar_error_code_t::ERR_INVALID_CVAR;
	}
    
    if ( default_value == nullptr || default_value[0] == '\0' ) {
        rcommon::com_printf( "cvar_register: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_INVALID_DEFAULT_VALUE ), cvar_error_desc( cvar_error_code_t::ERR_INVALID_DEFAULT_VALUE ) );
        return cvar_error_code_t::ERR_INVALID_DEFAULT_VALUE;
    }
    
    /*
     * @NOTE(Karlo): importnat here to make a flags bits mask and check like that.
     * 
     * More professional structure then, and we ensure that we do not miss any masks.
     * 
     */
    rcommon::u32 flags_bits = static_cast<rcommon::u32>( flags );
    
    if ( ( flags_bits & CVAR_MODIFIED ) != 0u ) {
        rcommon::com_printf( "cvar_register: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_INVALID_FLAG ), cvar_error_desc( cvar_error_code_t::ERR_INVALID_FLAG ) );
        return cvar_error_code_t::ERR_INVALID_FLAG;
    }
    
    // @NOTE(karlo): Additional safety checking for the masking part.
    if ( ( flags & ~CVAR_REGISTER_ALLOWED_FLAGS ) != 0 ) {
        rcommon::com_printf( "cvar_register: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_INVALID_FLAG ), cvar_error_desc( cvar_error_code_t::ERR_INVALID_FLAG ) );
        return cvar_error_code_t::ERR_INVALID_FLAG;
    } 
        
    // @NOTE(karlo): checking if we have that cvar already
    const cvar_t *cvar = cvar_find( name );
    
    // @NOTE(karlo): checking not by strcmp but by checking pointer dangling
    if ( cvar != nullptr ) {
        rcommon::com_printf( "cvar_register: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_CVAR_ALREADY_EXISTS ), cvar_error_desc( cvar_error_code_t::ERR_CVAR_ALREADY_EXISTS ) );
        return cvar_error_code_t::ERR_CVAR_ALREADY_EXISTS;
    }
    
    if ( g_cvar_registry.cvar_count >= CVAR_MAX_CVARS ) {
        rcommon::com_printf( "cvar_register: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_REGISTRY_FULL ), cvar_error_desc( cvar_error_code_t::ERR_REGISTRY_FULL ) );
        return cvar_error_code_t::ERR_REGISTRY_FULL;
    }
    
    g_cvar_registry.cvars[g_cvar_registry.cvar_count].name = name;
    strncpy( g_cvar_registry.cvars[g_cvar_registry.cvar_count].value_string, default_value, 256 );
    strncpy( g_cvar_registry.cvars[g_cvar_registry.cvar_count].default_string, default_value, 256 );
    g_cvar_registry.cvars[g_cvar_registry.cvar_count].value_int = std::atoi( default_value );
    g_cvar_registry.cvars[g_cvar_registry.cvar_count].value_float = std::atof( default_value );
    g_cvar_registry.cvars[g_cvar_registry.cvar_count].value_bool = ( std::atoi( default_value ) != 0 );
    g_cvar_registry.cvars[g_cvar_registry.cvar_count].flags = flags;
    g_cvar_registry.cvar_count++;
    
    return cvar_error_code_t::OK;   
}



} // namespace reap::rengine::cvar
