#pragma once

#include "rengine/rcommon/com_error.h"

namespace reap::rengine::rcommon 
{

void com_printf( const char *message, ... );

void com_dprintf( const char *message, ... );

void com_vprintf( const char *message, va_list args );

void com_errorf();
    
}       // namespace reap::rengine::rcommon


