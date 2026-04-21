#pragma once

#include <ctime>

#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::log {
    
/**
 * @brief Maximum number of characters stored in a single log message.
 *
 * Log records own their formatted message payload in fixed-size storage so
 * they can be emitted without depending on temporary external buffers.
 */
constexpr rcommon::usize REAP_LOG_MESSAGE_MAX = 1024u;

/**
 * @brief Maximum number of characters stored in the configured log file path.
 *
 * The logger owns a copied file path in its active configuration so it does
 * not depend on external string lifetime.
 */
constexpr rcommon::usize REAP_LOG_FILE_PATH_MAX = 512u;

/**
 * @brief Describes the severity level of a log event.
 *
 * Levels progress from highly verbose tracing to fatal runtime failures.
 */
enum class log_level_t : rcommon::u8 {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

/**
 * @brief Controls how the file sink opens its target file.
 *
 * `TRUNCATE` starts a fresh log file for the session, while `APPEND` preserves
 * existing content and writes new log events to the end.
 */
enum class log_file_mode_t : rcommon::u8 {
    TRUNCATE,
    APPEND
};

/**
 * @brief Controls when active sinks are flushed after writing log events.
 *
 * The default policy favors normal performance while still flushing failures
 * eagerly so important diagnostics are less likely to be lost on crashes.
 */
enum class log_flush_policy_t : rcommon::u8 {
    NEVER,
    ERRORS_AND_ABOVE,
    EVERY_MESSAGE
};

/**
 * @brief Controls how source file paths are rendered in output.
 *
 * `BASENAME` keeps logs shorter and more readable, while `FULL_PATH` is more
 * useful when debugging include-layout or build-path issues.
 */
enum class log_source_path_mode_t : rcommon::u8 {
    BASENAME,
    FULL_PATH
};

/**
 * @brief Identifies the subsystem channel associated with a log event.
 *
 * Channels allow runtime filtering and make log output readable as the
 * engine grows into multiple subsystems.
 */
enum class log_channel_t : rcommon::u8 {
	NONE = 0,
	CORE,
	HOST,
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
struct log_record_t {
	log_level_t level{ log_level_t::INFO };
	log_channel_t channel{ log_channel_t::CORE };
	const char *file{ "" };
	const char *function{ "" };
	rcommon::com_i32 line{ 0 };
    std::time_t timestamp{};
	char message[REAP_LOG_MESSAGE_MAX]{};
};

/**
 * @brief Public configuration for the logging subsystem.
 *
 * This describes the active logging policy and sink behavior that the logger
 * should attempt to apply at initialization time or during reconfiguration.
 */
struct log_config_t {
	log_level_t min_level{ log_level_t::INFO };
	rcommon::com_u32 channel_mask{ 0xFFFFFFFFu };
	bool console_enabled{ true };
    bool file_enabled{ false };
	bool include_timestamps{ true };
    log_file_mode_t file_mode{ log_file_mode_t::TRUNCATE };
    log_flush_policy_t flush_policy{ log_flush_policy_t::ERRORS_AND_ABOVE };
    log_source_path_mode_t source_path_mode{ log_source_path_mode_t::BASENAME };
    char file_path[REAP_LOG_FILE_PATH_MAX]{ "reap.log" };
};

/**
 * @brief Converts a log level enum into a readable constant string.
 *
 * @param[in] log_level Log level to convert.
 *
 * @return Constant string representation of the level.
 */
constexpr inline const char *log_level_name( const log_level_t log_level ) {
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
constexpr inline const char *log_channel_name( const log_channel_t channel ) {
    switch ( channel ) {
        case log_channel_t::CORE:      return "CORE";
        case log_channel_t::HOST:      return "HOST";
        case log_channel_t::PLATFORM:  return "PLATFORM";
        case log_channel_t::RENDER:    return "RENDER";
        case log_channel_t::PHYSICS:   return "PHYSICS";
        case log_channel_t::NET:       return "NET";
        case log_channel_t::ECS:       return "ECS";
        case log_channel_t::GAME:      return "GAME";
        case log_channel_t::TOOLS:     return "TOOLS";
        case log_channel_t::AUDIO:     return "AUDIO";
        case log_channel_t::ASSETS:    return "ASSETS";
        default:                       return "CORE";
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
constexpr inline rcommon::com_u32 log_channel_bit( const log_channel_t channel ) {
    return 1u << static_cast<rcommon::com_u32>( channel );
}

}; // namespace reap::rengine::log
