/*======================================================================
   File: host_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 01:23:58
   Last Modified by: ksiric
   Last Modified: 2026-04-21 21:40:58
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/host/host_main.h"
#include "rengine/rcommon/com_print.h"
#include "rengine/render/r_main.h"

namespace rc = reap::rengine::rcommon;

namespace reap::rengine::host
{

/**
 * @brief Initializes the host runtime state for the first frame.
 *
 * The initial implementation is intentionally small and only prepares the
 * lifecycle state needed for the frame loop to begin.
 *
 * @param[in,out] host_state Mutable host runtime state.
 * @param[in] host_config Startup configuration for the host.
 *
 * @return Host initialization result code.
 */
host_error_code_t host_init( host_state_t &host_state, const host_config_t &host_config ) {
    host_state.stage = host_stage_t::INITIALIZING;
    host_state.running = true;
    host_state.has_focus = true;
    host_state.frame = {};

    const auto render_result = render::r_init( host_config.window_config );

    if ( render_result != render::r_error_code_t::OK ) {
        rc::com_errorf(
            render::r_error_code( render_result ),
            "host_init: renderer initialization failed."
        );

        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
    }

    host_state.stage = host_stage_t::RUNNING;

    return host_error_code_t::OK;
}

/**
 * @brief Shuts down the host runtime state.
 *
 * @param[in,out] host_state Mutable host runtime state.
 */
void host_shutdown( host_state_t &host_state ) {
    host_state.running = false;
    host_state.stage = host_stage_t::SHUTDOWN;

    // @TODO: Also has to shutdown all the other subsystems in the engine,
    //        the host has to be able to orchestrate things and
    //        deal with the proper shutdown and cleaning of everything
    //        else.

    render::r_shutdown();
}

/**
 * @brief Advances per-frame timing and counters at the start of a frame.
 *
 * @param[in,out] host_state Mutable host runtime state.
 * @param[in] delta_time_seconds Time elapsed since the previous frame.
 */
void host_begin_frame( host_state_t &host_state, rcommon::com_f32 delta_time_seconds ) {
    if ( host_state.stage == host_stage_t::SHUTDOWN ) {
        return;
    }

    const auto render_result = render::r_begin_frame( delta_time_seconds );

    if ( render_result != render::r_error_code_t::OK ) {
        rc::com_errorf(
            render::r_error_code( render_result ),
            "host_begin_frame: renderer begin-frame failed."
        );

        host_state.running = false;
        host_state.stage = host_stage_t::SHUTTINGDOWN;
        return;
    }

    host_state.frame.index++;
    host_state.frame.delta_time_seconds = delta_time_seconds;
    host_state.frame.real_time_seconds += delta_time_seconds;

    if ( host_state.stage == host_stage_t::RUNNING ) {
        host_state.frame.simulation_time_seconds += delta_time_seconds;
    }
}

/**
 * @brief Runs the host update stage for the current frame.
 *
 * This function is currently a lifecycle placeholder and will later become
 * the place where engine and gameplay simulation work is coordinated.
 *
 * @param[in,out] host_state Mutable host runtime state.
 */
void host_update( host_state_t &host_state ) {
    if ( host_state.stage != host_stage_t::RUNNING ) {
        return;
    }

    if ( !host_state.running ) {
        return;
    }

    // @TODO: Update the host stage, and handle input, AI, gameplay etc.
}

/**
 * @brief Runs the render stage for the current host frame.
 *
 * This function is currently a placeholder until the render subsystem is
 * wired into the host frame loop.
 *
 * @param[in,out] host_state Runtime state owned by the host layer.
 */
void host_render( host_state_t &host_state ) {
    if ( host_state.stage != host_stage_t::RUNNING || !host_state.running ) {
        return;
    }

    // @TODO: Render the host stage, and handle rendering of the scene, UI, etc.
    const auto render_result = render::r_render_frame();

    if ( render_result != render::r_error_code_t::OK ) {
        rc::com_errorf(
            render::r_error_code( render_result ),
            "host_render: renderer frame submission failed."
        );

        host_state.running = false;
        host_state.stage = host_stage_t::SHUTTINGDOWN;
    }
}

/**
 * @brief Finalizes the current frame and handles lifecycle transitions.
 *
 * @param[in,out] host_state Mutable host runtime state.
 */
void host_end_frame( host_state_t &host_state ) {
    if ( host_state.stage == host_stage_t::SHUTDOWN ) {
        return;
    }

    const auto render_result = render::r_render_end();

    if ( render_result != render::r_error_code_t::OK ) {
        rc::com_errorf(
            render::r_error_code( render_result ),
            "host_end_frame: renderer end-frame failed."
        );

        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return;
    }

    if ( host_state.stage == host_stage_t::SHUTTINGDOWN ) {
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
    }
}

/**
 * @brief Reports whether the host should continue running.
 *
 * @param[in] host_state Current host runtime state.
 *
 * @return True while the main loop should continue executing.
 */
bool host_is_running( host_state_t &host_state ) {
    return host_state.running &&
           ( host_state.stage != host_stage_t::SHUTTINGDOWN &&
             host_state.stage != host_stage_t::SHUTDOWN );
}

}
