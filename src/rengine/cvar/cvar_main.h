#pragma once

#include "rengine/rcommon/com_foundation.h"

#define CVAR_MAX_CVARS              256u

namespace reap::rengine::cvar
{
    
enum cvar_flags_t : rcommon::u32 {
    CVAR_NONE       = 0,
    CVAR_ARCHIVE    = 1 << 0,           // values archived, save to cfg on exit
    CVAR_READONLY   = 1 << 1,           // nobody can change it, it is read only
    CVAR_CHEAT      = 1 << 2,           // only changeable if cheats enabled
    CVAR_DEV        = 1 << 3,           // for development and debug builds
    CVAR_MODIFIED   = 1 << 4            // value was changed this session
};

struct cvar_t {
    const char      *name;
    char            value_string[256];
    char            default_string[256];
    rcommon::u32    value_int;
    rcommon::f32    value_float;
    bool            value_bool;
    cvar_flags_t    flags;
};

struct cvar_registry_t {
    cvar_t          cvars[CVAR_MAX_CVARS];
    rcommon::u32    cvar_count;
    bool            initialized;
};

cvar_error_code_t cvar_init();




    
}       // namespace reap::rengine::cvar
