/*======================================================================
   File: com_print.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-21 13:11:03
   Last Modified by: ksiric
   Last Modified: 2026-04-21 14:54:27
   ---------------------------------------------------------------------
   Description:
       
   ---------------------------------------------------------------------
   License: 
   Company: 
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/rcommon/com_print.h"
#include "rengine/rcommon/com_error.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

namespace reap::rengine::rcommon
{
 
void Com_Printf( const char *message, ... ) {
    va_list args;
    va_start( args, message );
    com_vprintf( message, args );
    va_end( args );
}
 
void com_vprintf( const char *message, va_list args ) {
    char msg_buf[COM_MSG_MAX]{};
    std::vsnprintf( msg_buf, sizeof( msg_buf ), message, args );
    
    // @TODO: THis will later be changed as to where this will be flushed
    //        and this is important because we might have later func pointers
    //        and other things and it is better to just leave it as it is.
    
    
    
    
}   

void com_dprintf( const char *message, ... ) {
    // @NOTE: THis function is only called and printed once the Developer Mode is enabled, so it is used for more of a developer mode style of printing, while the game and the engine is being in active development state.
    
    va_list args;
    va_start( args, message );
    com_vprintf( message, args );
    va_end( args );
}
    
}       // namespace reap::rengine::rcommon
