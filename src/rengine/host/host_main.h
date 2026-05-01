#pragma once

#include "rengine/host/host_error.h"
#include "rengine/host/host_types.h"

namespace reap::rengine::host
{

host_error_code_t host_init( host_state_t &host_state );

void host_shutdown( host_state_t &host_state );

void host_begin_frame( host_state_t &host_state );

void host_update( host_state_t &host_state );

void host_render( host_state_t &host_state );

void host_end_frame( host_state_t &host_state );

bool host_is_running( host_state_t &host_state );

}
