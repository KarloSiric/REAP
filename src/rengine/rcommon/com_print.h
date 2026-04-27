#pragma once

#include <cstdarg>

#include "rengine/rcommon/com_error.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::rcommon
{

constexpr usize COM_MSG_MAX = 2048u;

void com_printf( const char *message, ... );

void com_dprintf( const char *message, ... );

void com_vprintf( const char *message, va_list args );

void com_errorf( const com_error_t error, const char *message, ... );

void com_verrorf( const com_error_t error, const char *message, va_list args );

}

