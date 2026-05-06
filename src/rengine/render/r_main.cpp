/*======================================================================
   File: r_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-20 21:01:21
   Last Modified by: ksiric
   Last Modified: 2026-05-06 14:45:21
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
#include "rengine/render/r_gl.h"

#include <SDL3/SDL.h>

namespace reap::rengine::render 
{
    
render_runtime_state_t g_render_runtime_state{};

r_error_code_t R_Init( const sys::sys_window_t &window, const host::window_config_t &window_config ) {
    if ( R_IsInitialized() ) {
        REAP_LOG_WARNING( log::log_channel_t::RENDER, "renderer already initialized." );
        return r_error_code_t::ERR_IS_INIT;
    } 
    
    if ( !window.valid || window.native_window == nullptr ) {
        REAP_LOG_ERROR( log::log_channel_t::RENDER, "invalid sys window." );
        return r_error_code_t::ERR_INVALID_WINDOW_CFG;
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
    
    g_render_runtime_state.window = &window;
    g_render_runtime_state.viewport_width = window_config.viewport.width;
    g_render_runtime_state.viewport_height = window_config.viewport.height;
    g_render_runtime_state.gl_state = {};
    g_render_runtime_state.initialized = true;
    g_render_runtime_state.in_frame = false;
    
    REAP_LOG_INFO(
        log::log_channel_t::RENDER,
        "renderer initialized with viewport %ux%u.",
        g_render_runtime_state.viewport_width,
        g_render_runtime_state.viewport_height
    );
    
    // @TODO: Need to setup the SDL openGL context because we are using SDL as the main layer and we need to give it the context for the renderer.
    
    // @NOTE: Calling "R_GLinit" setting up the OpengGL pipeline getting things ready!
    const auto gl_result = R_GLInit( window, window_config.vsync, g_render_runtime_state.gl_state );
    
    if ( gl_result != r_error_code_t::OK ) {
        return gl_result;
    }
    
    return r_error_code_t::OK;
}

void R_Shutdown() {
    if ( !R_IsInitialized() ) {
        REAP_LOG_INFO( log::log_channel_t::RENDER, "renderer was not initialized; nothing to shutdown." );
        return ;
    }
    
    R_GLShutdown( g_render_runtime_state.gl_state );
    
    g_render_runtime_state = {};
    
    REAP_LOG_INFO( log::log_channel_t::RENDER, "renderer shutdown complete." );
}

r_error_code_t R_BeginFrame( const rcommon::com_f32 delta_time_seconds ) {
    if ( !R_IsInitialized() ) {
        return r_error_code_t::ERR_NOT_INIT;
    }
    
    if ( g_render_runtime_state.in_frame ) {
        return r_error_code_t::ERR_FRAME_ALREADY_ACTIVE;
    }
        
    const auto gl_result = R_GLBeginFrame( *g_render_runtime_state.window ); 
    if ( gl_result != r_error_code_t::OK ) {
        return r_error_code_t::ERR_BEGIN_DRAW;
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
    
    const auto gl_result = R_GLEndFrame( *g_render_runtime_state.window );
    if ( gl_result != r_error_code_t::OK ) {
        return r_error_code_t::ERR_END_DRAW;
    }
    
    g_render_runtime_state.in_frame = false;
    
    return r_error_code_t::OK;
}

bool R_IsInitialized() {
    return g_render_runtime_state.initialized;
}

}       // namespace reap::rengine::render
