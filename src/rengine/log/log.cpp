/*======================================================================
   File: log.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 22:31:16
   Last Modified by: ksiric
   Last Modified: 2026-04-20 01:24:07
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */
#include <cstdio>
#include <cstring>
#include <ctime>

#include "rengine/log/log.h"

namespace 
{

/**
 * @brief Owns the mutable runtime state of the logging subsystem.
 *
 * The logger is intentionally simple for now and keeps only configuration
 * and initialization state in process-global storage.
 */
struct log_runtime_state_t {
    reap::rengine::log::init_t config{};
    bool initialized{ false };
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
void log_init( const init_t &config ){
    g_log_runtime_state_t.config = config;
    g_log_runtime_state_t.initialized = true;
}

/**
 * @brief Resets the logging subsystem back to its uninitialized state.
 */
void log_shutdown( ) {
    g_log_runtime_state_t = {};
}

/**
 * @brief Returns the active runtime logging configuration.
 *
 * @return Read-only reference to the active logging configuration.
 */
const init_t &log_get_config( ) {
    return g_log_runtime_state_t.config;   
}

/**
 * @brief Replaces the active logging configuration.
 *
 * @param[in] config New logging configuration to install.
 */
void log_set_config( const init_t &config ) {
    g_log_runtime_state_t.config = config;
}

/**
 * @brief Tests whether a log event should be emitted under current policy.
 *
 * @param[in] log_level Severity level to test.
 * @param[in] channel Logging channel to test.
 *
 * @return True if the log event is enabled.
 */
bool log_level_enabled( const log_level_t log_level, const channel_t channel ) {
    if ( !g_log_runtime_state_t.initialized ) {
        return false;
    }   
    
    if ( channel == channel_t::NONE || channel == channel_t::COUNT ) {
        return false;
    }
    
    const auto level_as_int = static_cast<reap::rengine::u32>( log_level );
    const auto min_level_as_int = static_cast<reap::rengine::u32>( g_log_runtime_state_t.config.min_level );
    
    if ( level_as_int < min_level_as_int ) {
        return false;
    }
    
    return log_channel_enabled( g_log_runtime_state_t.config.channel_mask, channel );
}   

/**
 * @brief Tests whether a specific channel is enabled within a mask.
 *
 * @param[in] channel_mask Bit mask containing enabled channels.
 * @param[in] channel Channel to test.
 *
 * @return True if the supplied channel bit is enabled.
 */
bool log_channel_enabled( const u32 channel_mask, const channel_t channel ) {
    if ( channel == channel_t::NONE || channel == channel_t::COUNT ) {
        return false;
    }
    
    const auto channel_as_int = static_cast<reap::rengine::u32>( channel );
    
    if ( channel_as_int >= 32 ) {
        return false;
    }
    
    return ( channel_mask & ( 1u << channel_as_int ) ) != 0u;
}

/**
 * @brief Emits a fully built log record to the current output sink.
 *
 * @param[in] record Fully constructed log record to emit.
 */
void log_emit( const record_t &record ) {
    if ( record.message[0] == '\0' ) {
        return;   
    }
    
    if ( !log_level_enabled( record.log_level, record.channel ) ) {
        return ;
    }
    
    const auto &cfg = log_get_config();
    
    // @TODO: For now we will not be touching this, because this will need to be addressed later only
    if ( !cfg.use_console_stdout ) {
        return ;
    }
    
    if ( cfg.include_timestamps == true ) {
        std::time_t now_time = std::time( nullptr );
        std::tm tm_value{};
        
        // @NOTE: This will also be converted because as soon as we add the 
        //        so called platform independency
#       if defined( _WIN32)
            localtime_s( &tm_value, &now_time );
#       else 
            localtime_r( &now_time, &tm_value );
#       endif
            
        char timestamp[32]{};
        
        std::strftime( timestamp, sizeof( timestamp ), "%H:%M:%S", &tm_value );
        std::printf( "[%s] ", timestamp );
    }
    
    std::printf( 
                "[%s][%s] %s:%d (%s) %s\n",
                 log_level_name( record.log_level ),
                 channel_name( record.channel ),
                 record.file,
                 record.line,
                 record.function,
                 record.message
                  );
    // @NOTE: So first we will be pushing it to the stdout but later this will have to be adopted to whatever we will be either in game or this and that right...
    std::fflush( stdout );
}

/**
 * @brief Formats and emits a log event from variadic arguments.
 *
 * This is the convenience wrapper used by logging macros. The actual
 * formatting work is forwarded into `log_emitfv`.
 *
 * @param[in] log_level Severity level of the log event.
 * @param[in] channel Logging channel associated with the event.
 * @param[in] file Source file where the event originated.
 * @param[in] function Source function where the event originated.
 * @param[in] line Source line where the event originated.
 * @param[in] format Printf-style message format string.
 */
void log_emitf( const log_level_t log_level, const channel_t channel,
                const char *file, const char *function, const i32 line,
                const char *format, ... ) {
    if ( !log_level_enabled( log_level, channel ) ) {
        return ;
    }
    va_list args;
    va_start( args, format );
    log_emitfv( log_level, channel, file, function, line, format, args );
    va_end( args );
}

/**
 * @brief Formats and emits a log event from an existing `va_list`.
 *
 * @param[in] log_level Severity level of the log event.
 * @param[in] channel Logging channel associated with the event.
 * @param[in] file Source file where the event originated.
 * @param[in] function Source function where the event originated.
 * @param[in] line Source line where the event originated.
 * @param[in] format Printf-style message format string.
 * @param[in] args Existing variadic argument list used for formatting.
 */
void log_emitfv( const log_level_t log_level, const channel_t channel,
                 const char *file, const char *function, const i32 line,
                 const char *format, va_list args ) {
    
    if ( !log_level_enabled( log_level, channel ) ) {
        return ;
    }   
    
    record_t record{};
    record.log_level = log_level;
    record.channel = channel;
    record.file = file ? file : "<unknown_file>";
    record.function = function ? function : "<unknown_function>";
    record.line = line;
    
    const char *safe_format = format ? format : "<null format>";
    std::vsnprintf( record.message, sizeof ( record.message ), safe_format, args );
    
    log_emit( record );
}

}       // namespace reap::rengine::log
