#pragma once

#include "rengine/app/app_types.h"
#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine
{

/**
 * @brief Initializes the renderer runtime.
 *
 * This call currently only stores startup config and validates that a viewport
 * size is usable for the first frame sequence.
 *
 * @param[in] window_config Window configuration used by the first render pass.
 *
 * @return True when renderer runtime enters initialized state.
 */
bool r_init( const window_config_t &window_config );

/**
 * @brief Shuts down renderer runtime.
 *
 * Marks renderer runtime as uninitialized and drops owned transient state.
 */
void r_shutdown();

/**
 * @brief Begins a new render frame.
 *
 * This is where clear color/buffer setup will live once a backend exists.
 *
 * @param[in] delta_time_seconds Time elapsed since previous frame.
 */
void r_begin_frame( const com_f32 delta_time_seconds );

/**
 * @brief Records the main render pass entry.
 *
 * First implementation is intentionally placeholder-only; no GPU calls yet.
 */
void r_render_frame();

/**
 * @brief Ends the current render frame.
 *
 * First implementation is placeholder-only and safe to call repeatedly.
 */
void r_end_frame();

/**
 * @brief Runtime frame statistics produced by the renderer.
 */
struct r_frame_stats_t {
    com_u32 frame_index{};         ///< Internal render frame counter.
    com_f32 delta_time_seconds{};   ///< Last frame delta time in seconds.
    com_f64 run_time_seconds{};    ///< Total time spent in initialized renderer mode.
};

/**
 * @brief Returns read-only runtime viewport configuration.
 *
 * This gives engine and debug systems the current drawable viewport.
 *
 * @return Current renderer viewport.
 */
viewport_t r_viewport();

/**
 * @brief Returns current render frame stats.
 *
 * @param[out] out_stats Output copy of the current frame stats.
 */
void r_get_stats( r_frame_stats_t &out_stats );

/**
 * @brief Reconfigures viewport geometry while renderer runtime is live.
 *
 * Useful for future resize events and debug tools.
 *
 * @param[in] viewport New viewport bounds.
 *
 * @return True when resize request is accepted.
 */
bool r_set_viewport( const viewport_t &viewport );

/**
 * @brief Returns whether renderer runtime is initialized.
 *
 * @return True if renderer is initialized and active.
 */
bool r_is_initialized();

}       // namespace reap::rengine
