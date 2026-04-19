#pragma once

#include <cstdarg>

#include "rengine/log/log_types.h"

namespace reap::rengine::log {

void log_init( const init_t &config = {} );
void log_shutdown();

const init_t &log_get_config();
void log_set_config( const init_t &config );

bool log_level_enabled( const log_level_t log_level, const channel_t channel );
bool log_channel_enabled( const u32 channel_mask, const channel_t channel );

void log_emit( const record_t &record );

void log_emitf( const log_level_t log_level, const channel_t channel,
                const char *file, const char *function, const i32 line,
                const char *format, ... );

void log_emitfv( const log_level_t log_level, const channel_t channel,
                 const char *file, const char *function, const i32 line,
                 const char *format, va_list args );

} // namespace reap::rengine::log

#define REAP_LOG_IF_ENABLED( LOG_LEVEL, LOG_CHANNEL )                                                           \
	if ( reap::rengine::log : log_level_enabled( ( LOG_LEVEL ), ( LOG_CHANNEL ) ) )

#define REAP_LOG( LOG_LEVEL, LOG_CHANNEL, LOG_MESSAGE )                                                         \
	do {                                                                                                        \
		if ( reap::rengine::log::log_level_enabled( ( LOG_LEVEL ), ( LOG_CHANNEL ) ) ) {                        \
    		const reap::rengine::log::record_t record = {                                                       \
    			( LOG_LEVEL ), ( LOG_CHANNEL ), __FILE__, __func__, __LINE__, ( LOG_MESSAGE )                   \
            };                                                                                                  \
            reap::rengine::log::log_emit( record, ( LOG_MESSAGE ) );                                            \
        }                                                                                                       \
    } while( false )
    
    
#define REAP_LOGF( LOG_LEVEL, LOG_CHANNEL, LOG_FORMAT, ... )                                                    \
    do {                                                                                                        \
        if ( reap::rengine::log:log_level_enabled( ( LOG_LEVEL), ( LOG_CHANNEL ) ) ) {                          \
            reap::rengine::log::log_emitf(                                                                      \
                ( LOG_LEVEL ), ( LOG_CHANNEL ), __FILE__, __func__, __LINE__, ( LOG_FORMAT ), __VA_ARGS__ );    \
        }                                                                                                       \
    } while ( false )
    
#define REAP_LOGF_IF( LOG_CONDITION, LOG_LEVEL, LOG_CHANNEL, LOG_FORMAT, ... )                                  \
    do {                                                                                                        \
        if ( ( CONDITION ) && reap::rengine::log::log_level_enabled( ( LOG_LEVEL ), (LOG_CHANNEL ) ) ) {        \
            reap::rengine::log::log_emtif(                                                                      \
                ( LOG_LEVEL ), ( LOG_CHANNEL ), __FILE__, __func__, __LINE__, ( LOG_FORMAT ), __VA_ARGS__ );    \
        }                                                                                                       \
    } while ( false )

#define REAP_LOG_TRACE( LOG_CHANNEL, LOG_FORMAT, ... )          REAP_LOGF( reap::rengine::log::log_level_t::TRACE, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ ) 

#define REAP_LOG_DEBUG( LOG_CHANNEL, LOG_FORMAT, ... )          REAP_LOGF( reap::rengine::log::log_level_t::DEBUG, ( LOG_CHANNEL ), ( LOG_FORMAT), __VA_ARGS__ )

#define REAP_LOG_INFO( LOG_CHANNEL, LOG_FORMAT, ... )           REAP_LOGF( reap::rengine::log::log_level_t::INFO, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_WARNING( LOG_CHANNEL, LOG_FORAMT, ... )        REAP_LOGF( reap::rengine::log::log_level_t::WARNING, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_ERROR( LOG_CHANNEL, LOG_FORMAT, ... )          REAP_LOGF( reap::rengine::log::log_level_t::ERROR, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_FATAL( LOG_CHANNEL, LOG_FORMAT, ... )          REAP_LOGF( reap::rengine::log::log_level_t::FATAL, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_INFO_MESSAGE( LOG_CHANNEL, LOG_MESSAGE )       REAP_LOG( reap::rengine::log::log_level_t::INFO, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )

#define REAP_LOG_WARNING_MESSAGE( LOG_CHANNEL, LOG_MESSAGE )    REAP_LOG( reap::rengine::log::log_level_t::WARNING, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
#define REAP_LOG_ERROR_MESSAGE( LOG_CHANNEL, LOG_MESSAGE )      REAP_LOG( reap::rengine::log::log_level_t::ERROR, ( LOG_CHANNEL ), ( LOG_FORMAT ), __VA_ARGS__ )
    
    
#define REAP_LOG_CHECK( CONDITION, LOG_CHANNEL, LOG_FORMAT, ... )                                                                   \
    do {                                                                                                                            \
        if ( !CONDITION ) {                                                                                                         \
            REAP_LOGF( reap::rengine::log::log_level_t::ERROR, ( LOG_CHANNEL ), "CHECK failed: ", ( LOG_FORMAT ), __VA_ARGS__ );    \
        }                                                                                                                           \
    } while ( false )
