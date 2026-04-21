#pragma once

#include "rengine/host/host_error.h"
#include "rengine/host/host_types.h"

namespace reap::rengine::host
{
    
/**
 * @brief Initializes the top-level host runtime state.
 *
 * This is the main runtime entry contract for rEngine. It prepares the host
 * state for the frame lifecycle and is the place where subsystem startup
 * will be coordinated as the engine grows.
 *
 * @param[in,out] host_state Runtime state owned by the host layer.
 * @param[in] host_config Startup configuration for the host.
 *
 * @return True if initialization succeeded, otherwise false.
 */
host_error_code_t host_init( host_state_t &host_state, const host_config_t &host_config );

/**
 * @brief Shuts down the top-level host runtime.
 *
 * This transitions the host out of its running state and is responsible for
 * coordinating subsystem teardown as the engine matures.
 *
 * @param[in,out] host_state Runtime state owned by the host layer.
 */
void host_shutdown( host_state_t &host_state );

/**
 * @brief Begins a new frame for the host.
 *
 * This stage advances frame counters and updates frame-timing values before
 * simulation and rendering work happen.
 *
 * @param[in,out] host_state Runtime state owned by the host layer.
 * @param[in] delta_time_seconds Time elapsed since the previous frame.
 */
void host_begin_frame( host_state_t &host_state, rcommon::com_f32 delta_time_seconds );

/**
 * @brief Updates the host simulation for the current frame.
 *
 * This stage is where engine and gameplay simulation work will be driven once
 * additional subsystems are wired into the frame loop.
 *
 * @param[in,out] host_state Runtime state owned by the host layer.
 */
void host_update( host_state_t &host_state );

/**
 * @brief Renders the current host frame.
 *
 * This stage is responsible for presentation-facing work and will later
 * coordinate render submission for engine and gameplay systems.
 *
 * @param[in] host_state Read-only host state for the current frame.
 */
void host_render( const host_state_t &host_state );

/**
 * @brief Finalizes the current host frame.
 *
 * This stage handles end-of-frame transitions and cleanup needed before the
 * next frame begins.
 *
 * @param[in,out] host_state Runtime state owned by the host layer.
 */
void host_end_frame( host_state_t &host_state );

/**
 * @brief Reports whether the host should continue running.
 *
 * This is the main loop query used by the executable entry point.
 *
 * @param[in] host_state Runtime state owned by the host layer.
 *
 * @return True while the host should continue running.
 */
bool host_is_running( host_state_t &host_state );

} // namespace reap::rengine::host
