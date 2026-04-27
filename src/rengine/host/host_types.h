#pragma once

#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::host
{

enum class host_stage_t : rcommon::u8 {
    UNINITIALIZED,
    INITIALIZING,
    RUNNING,
    PAUSED,
    SHUTTINGDOWN,
    SHUTDOWN
};

enum class build_config_t : rcommon::u8 {
    UNKNOWN,
    DEBUG,
    RELEASE,
    DISTRIBUTION
};

struct viewport_t {
    rcommon::com_u32 width{};
    rcommon::com_u32 height{};
};

struct window_config_t {
    viewport_t viewport{};
    const char *title{ "REAP" };
    bool fullscreen{false};
    bool vsync{true};
    rcommon::com_u32 target_fps{60};
};

struct frame_t {
    rcommon::com_frame_index_t index{};
    rcommon::com_f32 delta_time_seconds{};
    rcommon::com_f32 real_time_seconds{};
    rcommon::com_f32 simulation_time_seconds{};
};

struct host_config_t {
    build_config_t build_config{ build_config_t::UNKNOWN };
    window_config_t window_config{};
};

struct host_state_t {
    host_stage_t stage{ host_stage_t::UNINITIALIZED };
    bool running{ false };
    bool has_focus{ false };
    frame_t frame{};
};

}
