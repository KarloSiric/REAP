#pragma once

#include <cstdarg>

#include "rengine/log/log_types.h"

namespace reap::rengine::log 
{

/**
 * @brief Initializes the logging subsystem.
 *
 * The provided configuration becomes the active runtime policy for filtering,
 * channel masking, and output behavior.
 *
 * @param[in] config Logging configuration to install.
 */
void log_init( const init_t &config = {} );

/**
 * @brief Shuts down the logging subsystem.
 *
 * This clears the runtime logging state and returns the subsystem to its
 * uninitialized state.
 */
void log_shutdown();

/**
 * @brief Returns the current logging configuration.
 *
 * This exposes the active runtime policy used by the logging subsystem.
 *
 * @return Read-only reference to the active logging configuration.
 */
const init_t &log_get_config();

/**
 * @brief Replaces the active logging configuration at runtime.
 *
 * This allows logging behavior such as channel masks and minimum level to be
 * changed without restarting the application.
 *
 * @param[in] config New logging configuration to install.
 */
void log_set_config( const init_t &config );

/**
 * @brief Tests whether a log event is enabled for the given level and channel.
 *
 * This is the main filter query used by logging macros and formatted emit
 * helpers before constructing or submitting a log event.
 *
 * @param[in] log_level Severity level to test.
 * @param[in] channel Logging channel to test.
 *
 * @return True if the event is enabled by the current logging policy.
 */
bool log_level_enabled( const log_level_t log_level, const channel_t channel );

/**
 * @brief Tests whether a specific logging channel is enabled in a mask.
 *
 * This helper performs the channel-bit test used by the logging subsystem's
 * channel filtering logic.
 *
 * @param[in] channel_mask Bit mask containing enabled channels.
 * @param[in] channel Channel to test.
 *
 * @return True if the channel bit is enabled in the mask.
 */
bool log_channel_enabled( const rcommon::com_u32 channel_mask, const channel_t channel );

/**
 * @brief Emits a fully built log record to the active output sink.
 *
 * The supplied record is expected to already contain the complete event
 * payload, including metadata and final message text.
 *
 * @param[in] record Fully built log record to emit.
 */
void log_emit( const record_t &record );

/**
 * @brief Builds and emits a formatted log record.
 *
 * This helper captures source metadata and formats the final message before
 * forwarding the completed record to the logging sink path.
 *
 * @param[in] log_level Severity level of the log event.
 * @param[in] channel Logging channel associated with the event.
 * @param[in] file Source file where the event originated.
 * @param[in] function Source function where the event originated.
 * @param[in] line Source line where the event originated.
 * @param[in] format Printf-style message format string.
 */
void log_emitf( const log_level_t log_level, const channel_t channel,
                const char *file, const char *function, const rcommon::com_i32 line,
                const char *format, ... );

/**
 * @brief Builds and emits a formatted log record from an existing `va_list`.
 *
 * This variant exists so the formatting path can be implemented once and
 * shared by wrapper functions that receive variadic arguments.
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
                 const char *file, const char *function, const rcommon::com_i32 line,
                 const char *format, va_list args );


} // namespace reap::rengine::log

#define REAP_LOG_IF_ENABLED( LOG_LEVEL, LOG_CHANNEL )                                                           \
	if ( reap::rengine::log::log_level_enabled( ( LOG_LEVEL ), ( LOG_CHANNEL ) ) )

#define REAP_LOG( LOG_LEVEL, LOG_CHANNEL, LOG_MESSAGE )                                                         \
	do {                                                                                                        \
		if ( reap::rengine::log::log_level_enabled( ( LOG_LEVEL ), ( LOG_CHANNEL ) ) ) {                        \
    		const reap::rengine::log::record_t record = {                                                       \
    			( LOG_LEVEL ), ( LOG_CHANNEL ), __FILE__, __func__, __LINE__, ( LOG_MESSAGE )                   \
            };                                                                                                  \
            reap::rengine::log::log_emit( record );                                                             \
        }                                                                                                       \
    } while( false );
    
    
#define REAP_LOGF( LOG_LEVEL, LOG_CHANNEL, LOG_FORMAT, ... )                                                    \
    do {                                                                                                        \
        if ( reap::rengine::log::log_level_enabled( ( LOG_LEVEL), ( LOG_CHANNEL ) ) ) {                          \
            reap::rengine::log::log_emitf(                                                                      \
                ( LOG_LEVEL ), ( LOG_CHANNEL ), __FILE__, __func__, __LINE__, ( LOG_FORMAT )                     \
				__VA_OPT__( , ) __VA_ARGS__ );                                                             \
        }                                                                                                       \
    } while ( false );
    
#define REAP_LOGF_IF( LOG_CONDITION, LOG_LEVEL, LOG_CHANNEL, LOG_FORMAT, ... )                                  \
    do {                                                                                                        \
        if ( ( LOG_CONDITION ) && reap::rengine::log::log_level_enabled( ( LOG_LEVEL ), (LOG_CHANNEL ) ) ) {    \
            reap::rengine::log::log_emitfv(                                                                     \
                ( LOG_LEVEL ), ( LOG_CHANNEL ), __FILE__, __func__, __LINE__, ( LOG_FORMAT )                    \
				__VA_OPT__( , ) __VA_ARGS__ );                                                             \
        }                                                                                                       \
    } while ( false );

#define REAP_LOG_TRACE( LOG_CHANNEL, LOG_FORMAT, ... )          REAP_LOGF( reap::rengine::log::log_level_t::TRACE, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ ) 

#define REAP_LOG_DEBUG( LOG_CHANNEL, LOG_FORMAT, ... )          REAP_LOGF( reap::rengine::log::log_level_t::DEBUG, ( LOG_CHANNEL ), ( LOG_FORMAT), __VA_ARGS__ )

#define REAP_LOG_INFO( LOG_CHANNEL, LOG_FORMAT, ... )           REAP_LOGF( reap::rengine::log::log_level_t::INFO, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_WARNING( LOG_CHANNEL, LOG_FORMAT, ... )        REAP_LOGF( reap::rengine::log::log_level_t::WARNING, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_ERROR( LOG_CHANNEL, LOG_FORMAT, ... )          REAP_LOGF( reap::rengine::log::log_level_t::ERROR, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_FATAL( LOG_CHANNEL, LOG_FORMAT, ... )          REAP_LOGF( reap::rengine::log::log_level_t::FATAL, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_INFO_MESSAGE( LOG_CHANNEL, LOG_MESSAGE )       REAP_LOG( reap::rengine::log::log_level_t::INFO, ( LOG_CHANNEL ), ( LOG_MESSAGE ) )

#define REAP_LOG_WARNING_MESSAGE( LOG_CHANNEL, LOG_MESSAGE )    REAP_LOG( reap::rengine::log::log_level_t::WARNING, ( LOG_CHANNEL ), ( LOG_MESSAGE ) )
    
#define REAP_LOG_ERROR_MESSAGE( LOG_CHANNEL, LOG_MESSAGE )      REAP_LOG( reap::rengine::log::log_level_t::ERROR, ( LOG_CHANNEL ), ( LOG_MESSAGE ) )
    
    
#define REAP_LOG_CHECK( CONDITION, LOG_CHANNEL, LOG_FORMAT, ... )                                                                   \
    do {                                                                                                                            \
        if ( !CONDITION ) {                                                                                                         \
            REAP_LOGF( reap::rengine::log::log_level_t::ERROR, ( LOG_CHANNEL ), "CHECK failed: ", ( LOG_FORMAT ), __VA_ARGS__ );    \
        }                                                                                                                           \
    } while ( false );
