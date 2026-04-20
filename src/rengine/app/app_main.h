#pragma once

#include "rengine/app/app_types.h"

namespace reap::rengine 
{
    
/**
 * @brief Initializes the top-level application runtime state.
 *
 * This is the main runtime entry contract for rEngine. It prepares the app
 * state for the frame lifecycle and is the place where subsystem startup
 * will be coordinated as the engine grows.
 *
 * @param[in,out] app_state Runtime state owned by the application layer.
 * @param[in] app_config Startup configuration for the application.
 *
 * @return True if initialization succeeded, otherwise false.
 */
bool app_init( app_state_t &app_state, const app_config_t &app_config );

/**
 * @brief Shuts down the top-level application runtime.
 *
 * This transitions the app out of its running state and is responsible for
 * coordinating subsystem teardown as the engine matures.
 *
 * @param[in,out] app_state Runtime state owned by the application layer.
 */
void app_shutdown( app_state_t &app_state );

/**
 * @brief Begins a new frame for the application.
 *
 * This stage advances frame counters and updates frame-timing values before
 * simulation and rendering work happen.
 *
 * @param[in,out] app_state Runtime state owned by the application layer.
 * @param[in] delta_time_seconds Time elapsed since the previous frame.
 */
void app_begin_frame( app_state_t &app_state, com_f32 delta_time_seconds );

/**
 * @brief Updates the application simulation for the current frame.
 *
 * This stage is where engine and gameplay simulation work will be driven once
 * additional subsystems are wired into the frame loop.
 *
 * @param[in,out] app_state Runtime state owned by the application layer.
 */
void app_update( app_state_t &app_state );

/**
 * @brief Renders the current application frame.
 *
 * This stage is responsible for presentation-facing work and will later
 * coordinate render submission for engine and gameplay systems.
 *
 * @param[in] app_state Read-only application state for the current frame.
 */
void app_render( const app_state_t &app_state );

/**
 * @brief Finalizes the current application frame.
 *
 * This stage handles end-of-frame transitions and cleanup needed before the
 * next frame begins.
 *
 * @param[in,out] app_state Runtime state owned by the application layer.
 */
void app_end_frame( app_state_t &app_state );

/**
 * @brief Reports whether the application should continue running.
 *
 * This is the main loop query used by the executable entry point.
 *
 * @param[in] app_state Runtime state owned by the application layer.
 *
 * @return True while the application should continue running.
 */
bool app_is_running( app_state_t &app_state );

}; // namespace reap::rengine
