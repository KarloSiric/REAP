/*======================================================================
   File: cvar_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-22 21:04:15
   Last Modified by: ksiric
   Last Modified: 2026-04-27 17:37:39
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
		rcommon::com_printf( "cvar_init: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_IS_INIT ), cvar_error_desc( cvar_error_code_t::ERR_IS_INIT ) );
		return cvar_error_code_t::ERR_IS_INIT;
	}

	g_cvar_registry = {};
	g_cvar_registry.initialized = true;
	return cvar_error_code_t::OK;
}

// @NOTE(karlo): helper func for parsing the proper bool lower
bool cvar_parse_bool( const char *value ) {
	// @NOTE(karlo) -> for design wise choice I went for nullptr, 0, false, "", "false", "off", "no" to be a bool false value.
	if ( value == nullptr || value[0] == '\0' ) {
		return false;
	}

	char lower[32]{};
	rcommon::u32 i;

	for ( i = 0; i < 31 && value[i] != '\0'; i++ ) {
    lower[i] = static_cast<char>( std::tolower( static_cast<unsigned char>( value[i] ) ) );
	}
	lower[i] = '\0';

	if ( std::strcmp( lower, "0" ) == 0 || std::strcmp( lower, "false" ) == 0 || std::strcmp( lower, "off" ) == 0 || std::strcmp( lower, "no" ) == 0 ) {
		return false;
	}

	if ( std::strcmp( lower, "1" ) == 0 || std::strcmp( lower, "true" ) == 0 || std::strcmp( lower, "on" ) == 0 || std::strcmp( lower, "yes" ) == 0 ) {
		return true;
	}

	return ( std::atoi( lower ) != 0 );
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
	if ( ( flags_bits & ~CVAR_REGISTER_ALLOWED_FLAGS ) != 0 ) {
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

	cvar_t &entry = g_cvar_registry.cvars[g_cvar_registry.cvar_count];

	entry.name = name;
	std::strncpy( entry.value_string, default_value, sizeof( entry.value_string ) - 1 );
	std::strncpy( entry.default_string, default_value, sizeof( entry.default_string ) - 1 );
	entry.value_string[sizeof( entry.value_string ) - 1] = '\0';
	entry.default_string[sizeof( entry.default_string ) - 1] = '\0';
	entry.value_int = std::atoi( default_value );
	entry.value_float = std::atof( default_value );
	entry.flags = flags;
	entry.value_bool = cvar_parse_bool( entry.value_string );
	g_cvar_registry.cvar_count++;

	return cvar_error_code_t::OK;
}

// @TODO(karlo): adding other functions tommorow

cvar_error_code_t cvar_set( const char *name, const char *value ) {
	if ( !g_cvar_registry.initialized ) {
		rcommon::com_printf( "cvar_set: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_NOT_INIT ), cvar_error_desc( cvar_error_code_t::ERR_NOT_INIT ) );
		return cvar_error_code_t::ERR_NOT_INIT;
	}

	if ( name == nullptr || name[0] == '\0' ) {
        rcommon::com_printf( "cvar_set: %s: %s\n",
                             cvar_error_name( cvar_error_code_t::ERR_INVALID_CVAR ),
                             cvar_error_desc( cvar_error_code_t::ERR_INVALID_CVAR ) );
        return cvar_error_code_t::ERR_INVALID_CVAR;
	}
    
    if ( value == nullptr ) {
        rcommon::com_printf( "cvar_set: %s: %s\n",
                             cvar_error_name( cvar_error_code_t::ERR_INVALID_CVAR ),
                             cvar_error_desc( cvar_error_code_t::ERR_INVALID_CVAR ) );
        return cvar_error_code_t::ERR_INVALID_CVAR;
        
    }
    
    cvar_t *target = nullptr;
    // @NOTE: O(n) because we do not know, we need to check everything basically.
    for ( rcommon::u32 i = 0; i < g_cvar_registry.cvar_count; ++i ) {
        if ( std::strcmp( g_cvar_registry.cvars[i].name, name ) == 0 ) {
            target = &g_cvar_registry.cvars[i];
            break;
        }
    }
    if ( target == nullptr ) {
        rcommon::com_printf( "cvar_set: %s: %s\n",
                             cvar_error_name( cvar_error_code_t::ERR_CVAR_NOT_FOUND ),
                             cvar_error_desc( cvar_error_code_t::ERR_CVAR_NOT_FOUND ) );
        return cvar_error_code_t::ERR_CVAR_NOT_FOUND;
    } 
    if ( ( static_cast<rcommon::u32>( target->flags ) & CVAR_READONLY ) != 0 ) {
        rcommon::com_printf( "cvar_set: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_READONLY ), cvar_error_desc( cvar_error_code_t::ERR_READONLY ) );
        return cvar_error_code_t::ERR_READONLY;
    }
    
    // @TODO(karlo): later this will need to be replaced with real cheats if we enable these and stuff 
    const bool cheats_enabled = false;
    if ( ( static_cast<rcommon::u32>( target->flags ) & CVAR_CHEAT ) != 0 && !cheats_enabled ) {
        rcommon::com_printf( "cvar_set: %s: %s\n",
                             cvar_error_name( cvar_error_code_t::ERR_CHEAT_PROTECTED ),
                             cvar_error_desc( cvar_error_code_t::ERR_CHEAT_PROTECTED ) );
        return cvar_error_code_t::ERR_CHEAT_PROTECTED;
    }
    
    std::strncpy( target->value_string, value, sizeof( target->value_string ) - 1 );
    target->value_string[sizeof( target->value_string ) - 1u] = '\0';
    
    target->value_int = static_cast<rcommon::u32>( std::atoi( target->value_string ) );
    target->value_float = static_cast<rcommon::f32>( std::atof( target->value_string ) );
    target->value_bool = cvar_parse_bool( target->value_string );
    
    target->flags = static_cast<cvar_flags_t>( static_cast<rcommon::u32>( target->flags ) | CVAR_MODIFIED );
    
    return cvar_error_code_t::OK;
}

cvar_error_code_t cvar_shutdown() {
    if ( !g_cvar_registry.initialized ) {
        rcommon::com_printf( "cvar_shutdown: %s: %s\n", cvar_error_name( cvar_error_code_t::ERR_NOT_INIT ), cvar_error_desc( cvar_error_code_t::ERR_NOT_INIT ) );
        return cvar_error_code_t::ERR_NOT_INIT;
    }
    g_cvar_registry = {};
    
    return cvar_error_code_t::OK;
}

const cvar_t *cvar_find( const char *name ) {
    if ( !g_cvar_registry.initialized ) {
        return nullptr;
    }
    
    if ( name == nullptr || name[0] == '\0' ) {
        return nullptr;
    }
    
    const cvar_t *cvar = nullptr;
    
    for ( rcommon::u32 i = 0; i < g_cvar_registry.cvar_count; ++i ) {
        if ( std::strcmp( g_cvar_registry.cvars[i].name, name ) == 0 ) {
            cvar = &g_cvar_registry.cvars[i];
            return cvar;
        } 
    }
    
    return cvar;
}

const char *cvar_get_string( const char *name ) {
    if ( !g_cvar_registry.initialized ) {
        return nullptr;
    }
    
    if ( name == nullptr || name[0] == '\0' ) {
        return nullptr;
    }
    
    const cvar_t *cvar = cvar_find( name );
    
    if ( cvar == nullptr ) {
        // @TODO: we just return an empty string
        return "";
    } 
    
    return cvar->value_string;
}

rcommon::u32 cvar_get_int( const char *name ) {
    if ( !g_cvar_registry.initialized ) {
        return (rcommon::u32)0u;
    }
    
    if ( name == nullptr || name[0] == '\0' ) {
        return (rcommon::u32)0u;
    }
    
    const cvar_t *cvar = cvar_find( name );
    
    if ( cvar == nullptr ) {
        return (rcommon::u32)0u;
    }
    
    return cvar->value_int;
}

rcommon::f32 cvar_get_float( const char *name ) {
    if ( !g_cvar_registry.initialized ) {
        return (rcommon::f32)0.0f;
    }
    
    if ( name == nullptr || name[0] == '\0' ) {
        return (rcommon::f32)0.0f;
    }
    
    const cvar_t *cvar = cvar_find( name );
    
    if ( cvar == nullptr ) {
        return (rcommon::f32)0.0f;
    }
    
    return cvar->value_float;
}

bool cvar_get_bool( const char *name ) {
    if ( !g_cvar_registry.initialized ) {
        return false;
    }
    
    if ( name == nullptr || name[0] == '\0' ) {
        return false;
    }
    
    const cvar_t *cvar = cvar_find( name );
    
    if ( cvar == nullptr ) {
        return false;
    }
    
    return cvar->value_bool;
}

} // namespace reap::rengine::cvar
