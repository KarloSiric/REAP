/*======================================================================
   File: r_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-20 21:01:21
   Last Modified by: ksiric
   Last Modified: 2026-04-21 15:54:13
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

bool r_init( const host::window_config_t &window_config ) {
    if ( r_is_initialized() ) {
        REAP_LOG_INFO( reap::rengine::log::log_channel_t::RENDER, "r_init: called but renderer already initialized. Reusing existing renderer state." );
        return true;
    }
    
    if ( window_config.viewport.width == 0u || window_config.viewport.height == 0u ) {
        REAP_LOG_ERROR(
            reap::rengine::log::log_channel_t::RENDER,
            "r_init: error: invalid viewport %ux%u (both dimensions must be > 0).",
            window_config.viewport.width,
            window_config.viewport.height
        );
        return false;
    }
    
    g_render_runtime_state.initialized = true;
    g_render_runtime_state.in_frame = false;
    
    REAP_LOG_INFO(
        reap::rengine::log::log_channel_t::RENDER,
        "r_init: renderer initialized with viewport %ux%u.",
        window_config.viewport.width,
        window_config.viewport.height
    );

    return true;
}

void r_shutdown() {
    if ( !r_is_initialized() ) {
        REAP_LOG_INFO( reap::rengine::log::log_channel_t::RENDER, "r_shutdown: renderer was not initialized; no action taken." );
        return ;
    }
    
    g_render_runtime_state.initialized = false;
    g_render_runtime_state.in_frame = false;
    
    REAP_LOG_INFO( reap::rengine::log::log_channel_t::RENDER, "r_shutdown: renderer shutdown complete." );
}

void r_begin_frame( const rcommon::com_f32 delta_time_seconds ) {
    if ( !r_is_initialized() ) {
        return ;
    }
    
    ( void )delta_time_seconds;
    g_render_runtime_state.in_frame = true;
}

void r_render_frame() {
    if ( !r_is_initialized() || !g_render_runtime_state.in_frame ) {
        return ;
    }
}

void r_render_end() {
    if ( !r_is_initialized() || !g_render_runtime_state.in_frame ) {
        return ;
    }
    
    g_render_runtime_state.in_frame = false;
}

bool r_is_initialized() {
    return g_render_runtime_state.initialized;
}

}       // namespace reap::rengine::render
