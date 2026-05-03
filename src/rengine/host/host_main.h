#pragma once

#include "rengine/host/host_error.h"
#include "rengine/host/host_types.h"

namespace reap::rengine::host
{ 
    
void host_prepare_state_for_init( host_state_t &host_state );    

host_error_code_t host_init_core_engine_systems( host_state_t &host_state );

host_error_code_t host_mount_file_system( void );

host_error_code_t host_register_builtin_cvars( void );

host_error_code_t host_register_builtin_commands( void );

host_error_code_t host_load_startup_config( void );

host_error_code_t host_apply_cvars_to_config( host_state_t &host_state );

host_error_code_t host_init_renderer( host_state_t &host_state );

host_error_code_t host_finish_init( host_state_t &host_state );

host_error_code_t host_init( host_state_t &host_state );

void host_shutdown( host_state_t &host_state );

void host_begin_frame( host_state_t &host_state );

void host_update( host_state_t &host_state );

void host_render( host_state_t &host_state );

void host_end_frame( host_state_t &host_state );

bool host_is_running( host_state_t &host_state );

}
