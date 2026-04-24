/*======================================================================
   File: cfg_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-24 15:56:36
   Last Modified by: ksiric
   Last Modified: 2026-04-25 00:31:37
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/cfg/cfg_main.h"
#include "rengine/rcommon/com_print.h"
#include <cctype>
#include <cstdio>

namespace reap::rengine::cfg
{   

struct cfg_runtime_state_t {
    bool initialized { false };
};

cfg_runtime_state_t g_cfg_runtime_state;

constexpr const char *CFG_DEFAULT_PATH = "config/default.cfg";
constexpr const char *CFG_AUTOEXEC_PATH = "config/autoexec.cfg";
    
cfg_error_code_t cfg_init() {
    if ( g_cfg_runtime_state.initialized ) {
        return  cfg_error_code_t::ERR_IS_INIT;
    }
    
    g_cfg_runtime_state = {};
    g_cfg_runtime_state.initialized = true;
    return cfg_error_code_t::OK;
}

cfg_error_code_t cfg_shutdown() {
    if ( !g_cfg_runtime_state.initialized ) {
        return cfg_error_code_t::ERR_NOT_INIT;
    }
    
    g_cfg_runtime_state = {};
    return cfg_error_code_t::OK;
}

cfg_error_code_t cfg_load_file( const char *path, const bool required ) {
    if ( path == nullptr || path[0] == '\0' ) {
        return cfg_error_code_t::ERR_INVALID_PATH;
    } 
    
    if ( !g_cfg_runtime_state.initialized ) {
        return cfg_error_code_t::ERR_NOT_INIT;
    }
    
    std::FILE *cfg_file = std::fopen( path, "r" );
    if ( cfg_file == nullptr ) {
        return required ? cfg_error_code_t::ERR_FILE_OPEN_FAILED : cfg_error_code_t::OK;
    }
    
    char line[1024]{};
    // @NOTE(karlo): without any helpers, everything happens here in this looping process
    while( std::fgets( line, static_cast<int>( sizeof( line ) ), cfg_file ) != nullptr ) {
        char *cursor = line;
        // @NOTE: we trim the whitespaces -> we do not need them.
        while ( std::isspace( static_cast<unsigned char>( *cursor ) ) ) {
            ++cursor;
        }
        // @NOTE: we skip also empty lines.       
        if ( *cursor == '\0' || *cursor == '\n' || *cursor == '\r' ) {
            continue;
        }
        
        // @NOTE: we skip the comments part as well
        // comments are supported the following -> // or #
        
        bool in_quotes = false;
        for ( char *it = cursor; *it != '\0'; ++it ) {
            if ( *it == '"' ) {
                in_quotes = !in_quotes;
            }
            if ( !in_quotes  )
            
            
        }
        
        
        
    }
    
    
    
    
}




    
    
    
    
    
    
    
    
    
}       // namespace reap:rengine::cfg
