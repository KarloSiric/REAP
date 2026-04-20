/*======================================================================
   File: r_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-20 20:45:00
   Last Modified by: ksiric
   Last Modified: 2026-04-20 20:45:00
   ---------------------------------------------------------------------
   Description:
       First renderer bootstrap for the REAP project.
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/renderer/r_main.h"

namespace
{
/**
 * @brief Internal renderer runtime state.
 */
struct r_render_runtime_state_t {
    bool initialized{ false };
    reap::rengine::com_u32 frame_index{ 0 };
    reap::rengine::com_f64 run_time_seconds{ 0.0 };
    reap::rengine::com_f32 last_delta_time_seconds{ 0.0f };
    reap::rengine::viewport_t viewport{};
};

r_render_runtime_state_t g_r_render_runtime_state_t{};
}

namespace reap::rengine
{

/**
 * @brief Initializes the renderer runtime state.
 *
 * @param[in] window_config Startup window configuration.
 *
 * @return True when initialization succeeded.
 */
bool r_init( const window_config_t &window_config ) {
    if ( g_r_render_runtime_state_t.initialized ) {
        return true;
    }

    if ( window_config.viewport.width == 0 || window_config.viewport.height == 0 ) {
        return false;
    }

    g_r_render_runtime_state_t.initialized = true;
    g_r_render_runtime_state_t.viewport = window_config.viewport;
    g_r_render_runtime_state_t.frame_index = 0u;

    return true;
}

/**
 * @brief Shuts down renderer runtime state.
 */
void r_shutdown() {
    g_r_render_runtime_state_t = {};
}

/**
 * @brief Begins a render frame.
 *
 * @param[in] delta_time_seconds Time elapsed from previous frame.
 */
void r_begin_frame( const com_f32 delta_time_seconds ) {
    if ( !g_r_render_runtime_state_t.initialized ) {
        return;
    }

    if ( delta_time_seconds < 0.0f ) {
        return;
    }
    
    g_r_render_runtime_state_t.last_delta_time_seconds = delta_time_seconds;
    ++g_r_render_runtime_state_t.frame_index;
    g_r_render_runtime_state_t.run_time_seconds += static_cast<reap::rengine::com_f64>( delta_time_seconds );
}

/**
 * @brief Submits the placeholder render pass.
 */
void r_render_frame() {
    if ( !g_r_render_runtime_state_t.initialized ) {
        return;
    }

    // @TODO: Replace with actual render backend calls.
}

/**
 * @brief Ends a render frame.
 */
void r_end_frame() {
    if ( !g_r_render_runtime_state_t.initialized ) {
        return;
    }

    // @TODO: Replace with swap/present and deferred submission flush.
}

/**
 * @brief Returns the active viewport for the renderer.
 *
 * @return Current viewport dimensions.
 */
viewport_t r_viewport() {
    return g_r_render_runtime_state_t.viewport;
}

/**
 * @brief Fills caller-provided stats with current renderer runtime counters.
 *
 * @param[out] out_stats Output destination for current stats.
 */
void r_get_stats( r_frame_stats_t &out_stats ) {
    out_stats.frame_index = g_r_render_runtime_state_t.frame_index;
    out_stats.delta_time_seconds = g_r_render_runtime_state_t.last_delta_time_seconds;
    out_stats.run_time_seconds = g_r_render_runtime_state_t.run_time_seconds;
}

/**
 * @brief Updates renderer viewport while running.
 *
 * @param[in] viewport New viewport.
 *
 * @return True when update succeeded.
 */
bool r_set_viewport( const viewport_t &viewport ) {
    if ( viewport.width == 0 || viewport.height == 0 ) {
        return false;
    }

    g_r_render_runtime_state_t.viewport = viewport;
    return true;
}

/**
 * @brief Returns whether the renderer runtime is initialized.
 *
 * @return True if renderer is active.
 */
bool r_is_initialized() {
    return g_r_render_runtime_state_t.initialized;
}

}       // namespace reap::rengine
