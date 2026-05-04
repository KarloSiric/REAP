/*======================================================================
   File: r_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-20 21:01:21
   Last Modified by: ksiric
   Last Modified: 2026-04-26 03:19:57
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/render/r_main.h"
#include "rengine/log/log_main.h"

namespace {

struct render_runtime_state_t {
    bool initialized{ false };
    bool in_frame{ false };
};

render_runtime_state_t g_render_runtime_state{};

}

namespace reap::rengine::render 
{
    
r_error_code_t R_Init( const host::window_config_t &window_config ) {
    if ( R_IsInitialized() ) {
        REAP_LOG_WARNING( log::log_channel_t::RENDER, "renderer already initialized." );
        return r_error_code_t::ERR_IS_INIT;
    }
    
    if ( window_config.viewport.width == 0u || window_config.viewport.height == 0u ) {
        REAP_LOG_ERROR(
            log::log_channel_t::RENDER,
            "invalid viewport %ux%u (both dimensions must be > 0).",
            window_config.viewport.width,
            window_config.viewport.height
        );
        return r_error_code_t::ERR_INVALID_VIEWPORT;
    }
    
    g_render_runtime_state.initialized = true;
    g_render_runtime_state.in_frame = false;
    
    REAP_LOG_INFO(
        log::log_channel_t::RENDER,
        "renderer initialized with viewport %ux%u.",
        window_config.viewport.width,
        window_config.viewport.height
    );

    return r_error_code_t::OK;
}

void R_Shutdown() {
    if ( !R_IsInitialized() ) {
        REAP_LOG_INFO( log::log_channel_t::RENDER, "renderer was not initialized; nothing to shutdown." );
        return ;
    }
    
    g_render_runtime_state.initialized = false;
    g_render_runtime_state.in_frame = false;
    
    REAP_LOG_INFO( log::log_channel_t::RENDER, "renderer shutdown complete." );
}

r_error_code_t R_BeginFrame( const rcommon::com_f32 delta_time_seconds ) {
    if ( !R_IsInitialized() ) {
        return r_error_code_t::ERR_NOT_INIT;
    }
    
    if ( g_render_runtime_state.in_frame ) {
        return r_error_code_t::ERR_FRAME_ALREADY_ACTIVE;
    }
    
    ( void )delta_time_seconds;
    g_render_runtime_state.in_frame = true;
    
    return r_error_code_t::OK;
}

r_error_code_t R_RenderFrame() {
    if ( !R_IsInitialized() ) {
        return r_error_code_t::ERR_NOT_INIT;
    }
    
    if ( !g_render_runtime_state.in_frame ) {
        return r_error_code_t::ERR_FRAME_NOT_ACTIVE;
    }
    
    return r_error_code_t::OK;
}

r_error_code_t R_EndFrame() {
    if ( !R_IsInitialized() ) {
        return r_error_code_t::ERR_NOT_INIT;
    }
    
    if ( !g_render_runtime_state.in_frame ) {
        return r_error_code_t::ERR_FRAME_NOT_ACTIVE;
    }
    
    g_render_runtime_state.in_frame = false;
    
    return r_error_code_t::OK;
}

bool R_IsInitialized() {
    return g_render_runtime_state.initialized;
}

}       // namespace reap::rengine::render
