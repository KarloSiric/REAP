#pragma once

#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::host
{
    
/**
 * @brief Represents the high-level runtime stage of the host layer.
 *
 * This enum describes where the host currently is in its lifecycle, from
 * startup through normal execution to shutdown.
 */
enum class host_stage_t : rcommon::u8 {
    UNINITIALIZED,
    INITIALIZING,
    RUNNING,
    PAUSED,
    SHUTTINGDOWN,
    SHUTDOWN
};

/**
 * @brief Identifies the build configuration the host is running under.
 *
 * This is intended for runtime diagnostics, feature toggles, and startup
 * visibility when distinguishing debug and shipping-oriented builds.
 */
enum class build_config_t : rcommon::u8 {
    UNKNOWN,
    DEBUG,
    RELEASE,
    DISTRIBUTION
};

/**
 * @brief Describes the dimensions of a renderable viewport.
 *
 * This type is used by window and rendering configuration to represent the
 * target width and height of the application view.
 */
struct viewport_t {
    rcommon::com_u32 width{};
    rcommon::com_u32 height{};
};
 
/**
 * @brief Describes the initial window configuration for the host.
 *
 * This groups the basic startup-facing properties needed to create and
 * configure the primary runtime window.
 */
struct window_config_t {
    viewport_t viewport{};
    const char *title{ "REAP" };
    bool fullscreen{false};
    bool vsync{true};
    rcommon::com_u32 target_fps{60};
};

/**
 * @brief Stores per-frame runtime timing data for the host.
 *
 * This structure keeps both real elapsed time and simulation time so the
 * engine can distinguish total runtime from simulation-controlled time.
 */
struct frame_t {
    rcommon::com_frame_index_t index{};               // index of the current frame, incremented every frame
    rcommon::com_f32 delta_time_seconds{};               // time between the current frame and the previous frame, used for real-time movement simulation 
    rcommon::com_f32 real_time_seconds{};                // time since the application started so total time including pauses
    rcommon::com_f32 simulation_time_seconds{};          // time used for simulation, can be paused or slowed down
};

/**
 * @brief Groups the startup configuration for the host runtime.
 *
 * This is the top-level config passed into `host_init` and expanded as the
 * engine gains more startup-configurable systems.
 */
struct host_config_t {
    build_config_t build_config{ build_config_t::UNKNOWN };
    window_config_t window_config{};
};

/**
 * @brief Owns the mutable high-level runtime state of the host layer.
 *
 * This is the main state object advanced through the host lifecycle and used
 * by the executable entry point to drive the frame loop.
 */
struct host_state_t {
    host_stage_t stage{ host_stage_t::UNINITIALIZED };
    bool running{ false };
    bool has_focus{ false };
    frame_t frame{};
};
 
}       // namespace reap::rengine::host
