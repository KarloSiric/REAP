#pragma once

#include "rengine/common/foundation.h"

namespace reap::rengine::log {
    
constexpr usize REAP_LOG_LOG_MESSAGE_MAX = 1024u;

enum class log_level_t : u8 {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

enum class channel_t : u8 {
	NONE = 0,
	CORE,
	APP,
	PLATFORM,
	RENDER,
	PHYSICS,
	NET,
	ECS,
	GAME,
	TOOLS,
	AUDIO,
	ASSETS,
	COUNT
};

struct record_t {
	log_level_t log_level{ log_level_t::INFO };
	channel_t channel{ channel_t::CORE };
	const char *file{ "" };
	const char *function{ "" };
	i32 line{ 0 };
	char message[REAP_LOG_LOG_MESSAGE_MAX];
};

struct init_t {
	log_level_t min_level{ log_level_t::INFO };
	u32 channel_mask{ 0xFFFFFFFFu };
	bool use_console_stdout{ true };
	bool include_timestamps{ true };
};

inline const char *log_level_name( const log_level_t log_level ) {
	switch ( log_level ) {
        case log_level_t::TRACE:        return "TRACE";
        case log_level_t::DEBUG:        return "DEBUG";
        case log_level_t::INFO:         return "INFO";
        case log_level_t::WARNING:      return "WARNING";
        case log_level_t::ERROR:        return "ERROR";
        case log_level_t::FATAL:        return "FATAL";
        default:                        return "UNKNOWN";
	}
}

inline const char *channel_name( const channel_t channel ) {
    switch ( channel ) {
        case channel_t::CORE:      return "CORE";
        case channel_t::APP:       return "APP";
        case channel_t::PLATFORM:  return "PLATFORM";
        case channel_t::RENDER:    return "RENDER";
        case channel_t::PHYSICS:   return "PHYSICS";
        case channel_t::NET:       return "NET";
        case channel_t::ECS:       return "ECS";
        case channel_t::GAME:      return "GAME";
        case channel_t::TOOLS:     return "TOOLS";
        case channel_t::AUDIO:     return "AUDIO";
        case channel_t::ASSETS:    return "ASSETS";
        default:                   return "CORE";
    }
}

inline u32 channel_bit( const channel_t channel ) {
    return 1u << static_cast<u32>( channel );
}

}; // namespace reap::rengine::log
