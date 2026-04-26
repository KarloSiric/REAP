/*======================================================================
   File: fs_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-26 15:53:16
   Last Modified by: ksiric
   Last Modified: 2026-04-26 16:26:00
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/fs/fs_main.h"

namespace reap::rengine::fs
{
    
namespace {
    struct fs_runtime_state_t {
        bool initialized{ false };
        fs_mount_t mounts[FS_MAX_MOUNTS]{};
        rcommon::u32 mount_count{ 0u };
        char write_path[FS_MAX_PATH_LENGTH]{};
    };
}       // namespace
    
fs_runtime_state_t g_fs_runtime_state{};
    
fs_error_code_t fs_init() {
    if ( g_fs_runtime_state.initialized ) {
        return fs_error_code_t::ERR_IS_INIT;
    }
    
    g_fs_runtime_state = {};
    g_fs_runtime_state.initialized = true;
    
    return fs_error_code_t::OK;
}




}       // namespace reap::rengine::fs


