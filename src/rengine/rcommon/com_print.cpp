/*======================================================================
   File: com_print.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-21 13:11:03
   Last Modified by: ksiric
   Last Modified: 2026-04-21 20:51:07
   ---------------------------------------------------------------------
   Description:

   ---------------------------------------------------------------------
   License:
   Company:
   Version: 0.1.0
 ======================================================================
                                                                       */

#include "rengine/rcommon/com_print.h"

#include <cstdarg>
#include <cstdio>

namespace reap::rengine::rcommon
{

void Com_Printf( const char *message, ... ) {
    va_list args;
    va_start( args, message );
    Com_VPrintf( message, args );
    va_end( args );
}

void Com_VPrintf( const char *message, va_list args ) {
    char msg_buf[COM_MSG_MAX]{};
    const char *safe_message = message ? message : "<null message>";
    std::vsnprintf( msg_buf, sizeof( msg_buf ), safe_message, args );

    // @TODO: Route this through registered print sinks once com_print owns
    //        callback-based output targets.
    std::fputs( msg_buf, stdout );
    std::fflush( stdout );
}

void Com_DPrintf( const char *message, ... ) {
    // @NOTE: THis function is only called and printed once the Developer Mode is enabled, so it is used for more of a developer mode style of printing, while the game and the engine is being in active development state.

    va_list args;
    va_start( args, message );
    Com_VPrintf( message, args );
    va_end( args );
}

void Com_Errorf( const com_error_t error, const char *message, ... ) {
    va_list args;
    va_start( args, message );
    Com_VErrorf( error, message, args );
    va_end( args );
}

void Com_VErrorf( const com_error_t error, const char *message, va_list args ) {
    char msg_buf[COM_MSG_MAX]{};
    char msg_final[COM_MSG_MAX + 256]{};
    const char *safe_format = message ? message : "<null error message>";
    std::vsnprintf( msg_buf, sizeof( msg_buf ), safe_format, args );
    const com_domain_t domain = Com_ErrorDomain( error );

    std::snprintf(msg_final,
                  sizeof( msg_final ),
                  "[ERROR][%s][0x%08X] %s\n",
                  Com_DomainName( domain ),
                  static_cast<unsigned int>( error ),
                  msg_buf
                  );

    std::fputs( msg_final, stderr );
    std::fflush( stderr );
}

}       // namespace reap::rengine::rcommon
