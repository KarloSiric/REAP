#pragma once

#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine 
{
    
/**
 * @brief Represents the high-level runtime stage of the application.
 *
 * This enum describes where the app currently is in its lifecycle, from
 * startup through normal execution to shutdown.
 */
enum class app_stage_t : u8 {
    UNINITIALIZED,
    INITIALIZING,
    RUNNING,
    PAUSED,
    SHUTTINGDOWN,
    SHUTDOWN
};

/**
 * @brief Identifies the build configuration the application is running under.
 *
 * This is intended for runtime diagnostics, feature toggles, and startup
 * visibility when distinguishing debug and shipping-oriented builds.
 */
enum class build_config_t : u8 {
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
    com_u32 width{};
    com_u32 height{};
};
 
/**
 * @brief Describes the initial window configuration for the application.
 *
 * This groups the basic startup-facing properties needed to create and
 * configure the primary runtime window.
 */
struct window_config_t {
    viewport_t viewport{};
    const char *title{ "REAP" };
    bool fullscreen{false};
    bool vsync{true};
    com_u32 target_fps{60};
};

/**
 * @brief Stores per-frame runtime timing data for the application.
 *
 * This structure keeps both real elapsed time and simulation time so the
 * engine can distinguish total runtime from simulation-controlled time.
 */
struct frame_t {
    com_frame_index_t index{};               // index of the current frame, incremented every frame
    com_f32 delta_time_seconds{};               // time between the current frame and the previous frame, used for real-time movement simulation 
    com_f32 real_time_seconds{};                // time since the application started so total time including pauses
    com_f32 simulation_time_seconds{};          // time used for simulation, can be paused or slowed down
};

/**
 * @brief Groups the startup configuration for the application runtime.
 *
 * This is the top-level config passed into `app_init` and expanded as the
 * engine gains more startup-configurable systems.
 */
struct app_config_t {
    build_config_t build_config{ build_config_t::UNKNOWN };
    window_config_t window_config{};
};

/**
 * @brief Owns the mutable high-level runtime state of the application.
 *
 * This is the main state object advanced through the app lifecycle and used
 * by the executable entry point to drive the frame loop.
 */
struct app_state_t {
    app_stage_t stage{ app_stage_t::UNINITIALIZED };
    bool running{ false };
    bool has_focus{ false };
    frame_t frame{};
};
 
}       // namespace reap::rengine
