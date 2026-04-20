#pragma once

#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::log {
    
/**
 * @brief Maximum number of characters stored in a single log message.
 *
 * Log records own their formatted message payload in fixed-size storage so
 * they can be emitted without depending on temporary external buffers.
 */
constexpr usize REAP_LOG_MESSAGE_MAX = 1024u;

/**
 * @brief Describes the severity level of a log event.
 *
 * Levels progress from highly verbose tracing to fatal runtime failures.
 */
enum class log_level_t : u8 {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

/**
 * @brief Identifies the subsystem channel associated with a log event.
 *
 * Channels allow runtime filtering and make log output readable as the
 * engine grows into multiple subsystems.
 */
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

/**
 * @brief Represents a fully built log event.
 *
 * A log record contains both metadata and the final formatted message text.
 * The logging sink path operates on this complete event structure.
 */
struct record_t {
	log_level_t log_level{ log_level_t::INFO };
	channel_t channel{ channel_t::CORE };
	const char *file{ "" };
	const char *function{ "" };
	com_i32 line{ 0 };
	char message[REAP_LOG_MESSAGE_MAX];
};

/**
 * @brief Runtime configuration for the logging subsystem.
 *
 * This controls filtering behavior and output formatting policy for all log
 * events emitted while the configuration is active.
 */
struct init_t {
	log_level_t min_level{ log_level_t::INFO };
	com_u32 channel_mask{ 0xFFFFFFFFu };
	bool use_console_stdout{ true };
	bool include_timestamps{ true };
};

/**
 * @brief Converts a log level enum into a readable constant string.
 *
 * @param[in] log_level Log level to convert.
 *
 * @return Constant string representation of the level.
 */
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

/**
 * @brief Converts a channel enum into a readable constant string.
 *
 * @param[in] channel Channel to convert.
 *
 * @return Constant string representation of the channel.
 */
inline const char *log_channel_name( const channel_t channel ) {
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

/**
 * @brief Returns the bit mask associated with a single log channel.
 *
 * This helper is used when constructing or testing logging channel masks.
 *
 * @param[in] channel Channel to convert into a mask bit.
 *
 * @return Bit mask value for the supplied channel.
 */
inline com_u32 log_channel_bit( const channel_t channel ) {
    return 1u << static_cast<com_u32>( channel );
}

}; // namespace reap::rengine::log
