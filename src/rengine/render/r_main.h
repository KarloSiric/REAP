#pragma once

#include "rengine/host/host_types.h"
#include "rengine/render/r_error.h"

namespace reap::rengine::render
{

r_error_code_t R_Init( const host::window_config_t &window_config );

void R_Shutdown();

r_error_code_t R_BeginFrame( const rcommon::f32 delta_time_seconds );

r_error_code_t R_RenderFrame();

r_error_code_t R_EndFrame();

bool R_IsInitialized();

}
