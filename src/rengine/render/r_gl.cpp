/*======================================================================
   File: r_gl.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-05-05 22:02:15
   Last Modified by: ksiric
   Last Modified: 2026-05-06 00:28:38
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/render/r_gl.h"
#include "rengine/log/log_main.h"

#include <SDL3/SDL.h>

namespace reap::rengine::render
{
    
r_error_code_t R_GLInit( const sys::sys_window_t &window, bool vsync, r_gl_state_t &gl_state ) 
{
    SDL_Window *sdl_window{ nullptr};
    
    if ( window.native_window == nullptr || !window.valid ) {
        return r_error_code_t::ERR_INVALID_WINDOW_CFG;
    }
    
    sdl_window = static_cast<SDL_Window *>( window.native_window );
    
    if ( 
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 )  != 0    ||
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 )  != 0    ||
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE )                       != 0    ||
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 )           != 0    ||
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 )            != 0    ||
        SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 )           != 0     )  
    {
        REAP_LOG_ERROR( log::log_channel_t::RENDER, "SDL_GL_SetAttribute failed: %s", SDL_GetError() );

        return r_error_code_t::ERR_OPENGL_INIT;       
    }
    
    SDL_GLContext gl_context{ nullptr };
    gl_context = SDL_GL_CreateContext( sdl_window );
    
    if ( gl_context == nullptr ) {
        REAP_LOG_ERROR( log::log_channel_t::RENDER, "SDL_GL_CreateContext failed: %s", SDL_GetError() );
        return r_error_code_t::ERR_OPENGL_INIT;
    }
    
    if ( SDL_GL_MakeCurrent( sdl_window, gl_context ) != 0 ) {
        SDL_GL_DestroyContext( gl_context );
        REAP_LOG_ERROR( log::log_channel_t::RENDER, "SDL_GL_MakeCurrent failed: %s", SDL_GetError() );
        return r_error_code_t::ERR_OPENGL_INIT;
    }
    
    gl_state.context = gl_context;   

    return r_error_code_t::OK;
}

void R_GLShutdown( r_gl_state_t &gl_state )
{
    if ( gl_state.context == nullptr ) {
        return ;
    }
    
    SDL_GL_DestroyContext( static_cast<SDL_GLContext>( gl_state.context ) );
    gl_state.context = nullptr;
    
    REAP_LOG_INFO( log::log_channel_t::RENDER, "OpenGL Context shutdown completed." );
    
    return ;
}
    
}       // namespace reap::rengine::render

