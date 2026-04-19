#pragma once

#include "rengine/common/foundation.h"

namespace reap::rengine 
{
    
enum class app_stage_t : u8 {
    UNINITIALIZED,
    INITIALIZING,
    RUNNING,
    PAUSED,
    SHUTTINGDOWN,
    SHUTDOWN
};

enum class build_config_t : u8 {
    UNKNOWN,
    DEBUG,
    RELEASE,
    DISTRIBUTION
};

struct viewport_t {
    u32 width{};
    u32 height{};
};
 
struct window_config_t {
    viewport_t viewport{};
    const char *title{ "REAP" };
    bool fullscreen{false};
    bool vsync{true};
    u32 target_fps{60};
};

struct frame_t {
    frame_index_t index{};                  // index of the current frame, incremented every frame
    f32 delta_time_seconds{};               // time between the current frame and the previous frame, used for real-time movement simulation 
    f32 real_time_seconds{};                // time since the application started so total time including pauses
    f32 simulation_time_seconds{};          // time used for simulation, can be paused or slowed down
};

struct app_config_t {
    build_config_t build_config{ build_config_t::UNKNOWN };
    window_config_t window_config{};
};

struct app_state_t {
    app_stage_t stage{ app_stage_t::UNINITIALIZED };
    bool running{ false };
    bool has_focus{ false };
    frame_t frame{};
};
 
}       // namespace reap::rengine
