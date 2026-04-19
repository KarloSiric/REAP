/*======================================================================
   File: log.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 22:31:16
   Last Modified by: ksiric
   Last Modified: 2026-04-19 23:01:08
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

struct log_runtime_state_t {
    reap::rengine::log::init_t config{};
    bool initialized{ false };
};

log_runtime_state_t g_log_runtime_state_t;

}

namespace reap::rengine::log {

// @TODO: Once the platform header is setup we will add the log_basename and
//        log naming and so forth depending on different architectures

void log_init( const init_t &config ){
    g_log_runtime_state_t.config = config;
    g_log_runtime_state_t.initialized = true;
}

void log_shutdown( ) {
    g_log_runtime_state_t = {};
}

const init_t &log_get_config( ) {
    return g_log_runtime_state_t.config;   
}

void log_set_config( const init_t &config ) {
    g_log_runtime_state_t.config = config;
}

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








}       // namespace reap::rengine::log








        


