/*======================================================================
   File: log_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 22:31:16
   Last Modified by: ksiric
   Last Modified: 2026-05-03 02:23:35
   ---------------------------------------------------------------------
   Description:

   ---------------------------------------------------------------------
   License:
   Company:
   Version: 0.1.0
 ======================================================================
                                                                       */
#include "rengine/log/log_main.h"
#include "rengine/sys/sys_platform.h"

#include <cstdio>
#include <cstring>
#include <ctime>

namespace reap::rengine::log
{

/**
 * @brief Owns the mutable runtime state of the logging subsystem.
 *
 * The logger is intentionally simple for now and keeps only configuration
 * and initialization state in process-global storage.
 */
struct log_runtime_state_t {
    log_config_t config{};
    bool initialized{ false };
    std::FILE *file_handle{ nullptr };
    bool file_error_reported{ false };
};

log_runtime_state_t g_log_runtime_state_t;

}

namespace reap::rengine::log {

// @TODO: Once the platform header is setup we will add the log_basename and
//        log naming and so forth depending on different architectures

/**
 * @brief Installs the active logging configuration and marks the subsystem ready.
 *
 * @param[in] config Logging configuration to install.
 */
log_error_code_t Log_Init( const log_config_t &config ){
    if ( g_log_runtime_state_t.file_handle != nullptr ) {
        std::fclose( g_log_runtime_state_t.file_handle );
        g_log_runtime_state_t.file_handle = nullptr;
    }

    g_log_runtime_state_t = {};

    g_log_runtime_state_t.config = config;
    g_log_runtime_state_t.file_error_reported = false;

    if ( g_log_runtime_state_t.config.file_enabled ) {
        const char *open_mode = ( g_log_runtime_state_t.config.file_mode == log_file_mode_t::APPEND ? "a" : "w" );
        g_log_runtime_state_t.file_handle = std::fopen( g_log_runtime_state_t.config.file_path, open_mode );

        if ( g_log_runtime_state_t.file_handle == nullptr ) {
            g_log_runtime_state_t.initialized = false;
            return log_error_code_t::ERR_FILE_OPEN_FAILED;
        }
    }

    g_log_runtime_state_t.initialized = true;

    return log_error_code_t::OK;
}

/**
 * @brief Resets the logging subsystem back to its uninitialized state.
 */
void Log_Shutdown( ) {
    if ( g_log_runtime_state_t.file_handle != nullptr ) {
        std::fflush( g_log_runtime_state_t.file_handle );
        std::fclose( g_log_runtime_state_t.file_handle );
    }
    g_log_runtime_state_t.initialized = false;      // @NOTE: not really needed.
    g_log_runtime_state_t = {};
}

/**
 * @brief Returns the active runtime logging configuration.
 *
 * @return Read-only reference to the active logging configuration.
 */
const log_config_t &Log_GetConfig( ) {
    return g_log_runtime_state_t.config;
}

/**
 * @brief Replaces the active logging configuration.
 *
 * @param[in] config New logging configuration to install.
 */
log_error_code_t Log_SetConfig( const log_config_t &config ) {
    if ( !g_log_runtime_state_t.initialized ) {
        return log_error_code_t::ERR_NOT_INIT;
    }

    std::FILE *new_file_handle = g_log_runtime_state_t.file_handle;

    const bool file_sink_changed = ( g_log_runtime_state_t.config.file_enabled != config.file_enabled ) || ( g_log_runtime_state_t.config.file_mode != config.file_mode ) || ( std::strncmp( g_log_runtime_state_t.config.file_path, config.file_path, REAP_LOG_FILE_PATH_MAX ) != 0 );

    if ( file_sink_changed ) {

        new_file_handle = nullptr;

        if ( config.file_enabled ) {
            const char *open_mode = ( config.file_mode == log_file_mode_t::APPEND ) ? "a" : "w";

            new_file_handle = std::fopen( config.file_path, open_mode );

            if ( new_file_handle == nullptr ) {
                return log_error_code_t::ERR_FILE_OPEN_FAILED;
            }
        }
    }

    if ( file_sink_changed && g_log_runtime_state_t.file_handle != nullptr ) {
        std::fflush( g_log_runtime_state_t.file_handle );
        std::fclose( g_log_runtime_state_t.file_handle );
    }

    g_log_runtime_state_t.config = config;
    g_log_runtime_state_t.file_handle = new_file_handle;
    g_log_runtime_state_t.file_error_reported = false;

    return log_error_code_t::OK;
}

/**
 * @brief Tests whether a log event should be emitted under current policy.
 *
 * @param[in] level Severity level to test.
 * @param[in] channel Logging channel to test.
 *
 * @return True if the log event is enabled.
 */
bool Log_LevelEnabled( const log_level_t level, const log_channel_t channel ) {
    if ( !g_log_runtime_state_t.initialized ) {
        return false;
    }

    if ( channel == log_channel_t::NONE || channel == log_channel_t::COUNT ) {
        return false;
    }

    const auto level_as_int = static_cast<rcommon::com_u32>( level );
    const auto min_level_as_int = static_cast<rcommon::com_u32>( g_log_runtime_state_t.config.min_level );

    if ( level_as_int < min_level_as_int ) {
        return false;
    }

    return Log_ChannelEnabled( g_log_runtime_state_t.config.channel_mask, channel );
}

/**
 * @brief Tests whether a specific channel is enabled within a mask.
 *
 * @param[in] channel_mask Bit mask containing enabled channels.
 * @param[in] channel Channel to test.
 *
 * @return True if the supplied channel bit is enabled.
 *
 * 0xFFFFFFFF -> 1111 1111 1111 1111
 *
 * Channel -> HOST
 *
 */
bool Log_ChannelEnabled( const rcommon::com_u32 channel_mask, const log_channel_t channel ) {
    if ( channel == log_channel_t::NONE || channel == log_channel_t::COUNT ) {
        return false;
    }

    const auto channel_as_int = static_cast<rcommon::com_u32>( channel );

    // 5 ->                 0000 0000 0000 0101
    // mask -> 0xFFFFFFF -> 1111 1111 1111 1111
    // 1u                   0000 0000 0010 0000 << 2
    //
    //

    if ( channel_as_int >= 32 ) {
        return false;
    }

    return ( channel_mask & ( 1u << channel_as_int ) ) != 0u;
}

/************
 *
 * Helper function
 *
 * for flushing
 *
 ***********/
bool Log_ShouldFlush( const log_flush_policy_t flush_policy, const log_level_t level ) {

    switch ( flush_policy ) {
        case log_flush_policy_t::NEVER:
            return false;
        case log_flush_policy_t::ERRORS_AND_ABOVE:
            return static_cast<rcommon::u32>( level ) >= static_cast<rcommon::u32>( log_level_t::ERROR );
        case log_flush_policy_t::EVERY_MESSAGE:
            return true;
        default:
            return false;
    }
}

/**
 * @brief Emits a fully built log record to the current output sink.
 *
 * @param[in] record Fully constructed log record to emit.
 */
void Log_Emit( const log_record_t &record ) {
    if ( record.message[0] == '\0' ) {
        return;
    }

    if ( !Log_LevelEnabled( record.level, record.channel ) ) {
        return ;
    }

    const auto &cfg = Log_GetConfig();

    // @TODO: For now we will not be touching this, because this will need to be addressed later only
    if ( !cfg.console_enabled && !( cfg.file_enabled && g_log_runtime_state_t.file_handle != nullptr ) ) {
        return ;
    }

    const char *source_file = record.file ? record.file : "<unknown_file>";

    if ( cfg.source_path_mode == log_source_path_mode_t::BASENAME ) {
        source_file = sys::Sys_PathBasename( source_file );
    }

    char timestamp_buffer[32]{};

    if ( cfg.include_timestamps && record.timestamp != std::time_t{} ) {
        std::tm tm_value{};

        if ( sys::Sys_LocalTime( record.timestamp, tm_value ) ) {
            std::strftime( timestamp_buffer, sizeof( timestamp_buffer ), "%H:%M:%S", &tm_value );
        }
    }

    char line_buffer[REAP_LOG_MESSAGE_MAX + 256]{};

    if ( timestamp_buffer[0] != '\0' ) {
        std::snprintf(
                      line_buffer,
                      sizeof( line_buffer ),
                      "[%s][%s][%s] %s:%d (%s) %s\n",
                      timestamp_buffer,
                      Log_LevelName( record.level ),
                      Log_ChannelName( record.channel ),
                      source_file,
                      record.line,
                      record.function ? record.function : "<unknown_function>",
                      record.message
                      );
    } else {
        std::snprintf(
                    line_buffer,
                    sizeof( line_buffer ),
                    "[%s][%s] %s:%d (%s) %s\n",
                    Log_LevelName( record.level ),
                    Log_ChannelName( record.channel ),
                    source_file,
                    record.line,
                    record.function ? record.function : "<unknown_function>",
                    record.message
                    );
    }

    if ( cfg.console_enabled ) {
        std::fputs( line_buffer, stdout );
    }

    if ( cfg.file_enabled && g_log_runtime_state_t.file_handle != nullptr ) {
        std::fputs( line_buffer, g_log_runtime_state_t.file_handle );
    }

    if ( Log_ShouldFlush( cfg.flush_policy, record.level ) ) {

        if ( cfg.console_enabled ) {
            std::fflush( stdout );
        }

        if ( cfg.file_enabled && g_log_runtime_state_t.file_handle != nullptr ) {
            std::fflush( g_log_runtime_state_t.file_handle );
        }
    }
}

/**
 * @brief Formats and emits a log event from variadic arguments.
 *
 * This is the convenience wrapper used by logging macros. The actual
 * formatting work is forwarded into `Log_Emitfv`.
 *
 * @param[in] level Severity level of the log event.
 * @param[in] channel Logging channel associated with the event.
 * @param[in] file Source file where the event originated.
 * @param[in] function Source function where the event originated.
 * @param[in] line Source line where the event originated.
 * @param[in] format Printf-style message format string.
 */
void Log_Emitf( const log_level_t level, const log_channel_t channel,
                const char *file, const char *function, const rcommon::com_i32 line,
                const char *format, ... ) {
    if ( !Log_LevelEnabled( level, channel ) ) {
        return ;
    }
    va_list args;
    va_start( args, format );
    Log_Emitfv( level, channel, file, function, line, format, args );
    va_end( args );
}

/**
 * @brief Formats and emits a log event from an existing `va_list`.
 *
 * @param[in] level Severity level of the log event.
 * @param[in] channel Logging channel associated with the event.
 * @param[in] file Source file where the event originated.
 * @param[in] function Source function where the event originated.
 * @param[in] line Source line where the event originated.
 * @param[in] format Printf-style message format string.
 * @param[in] args Existing variadic argument list used for formatting.
 */
void Log_Emitfv( const log_level_t level, const log_channel_t channel,
                 const char *file, const char *function, const rcommon::com_i32 line,
                 const char *format, va_list args ) {

    if ( !Log_LevelEnabled( level, channel ) ) {
        return ;
    }

    log_record_t record{};
    record.level = level;
    record.channel = channel;
    record.file = file ? file : "<unknown_file>";
    record.function = function ? function : "<unknown_function>";
    record.line = line;
    record.timestamp = std::time( nullptr );

    const char *safe_format = format ? format : "<null format>";
    std::vsnprintf( record.message, sizeof ( record.message ), safe_format, args );

    Log_Emit( record );
}

}       // namespace reap::rengine::log
