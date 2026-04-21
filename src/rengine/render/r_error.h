#pragma once

#include "rengine/rcommon/com_foundation.h"

namespace reap::rengine::render
{

enum class r_error_code_t : rcommon::u8 {
    OK = 0,
    
    ERR_IS_INIT,                      // already initialized.
    ERR_NOT_INIT,                     // not initialized.
    
    ERR_INVALID_WINDOW_CFG,           // invalid window cfg.
    ERR_INVALID_VIEWPORT,             // invalid viewport.
    
    ERR_FRAME_ALREADY_ACTIVE,         // frame already active.
    ERR_FRAME_NOT_ACTIVE,             // frame not active.
};

}       // namespace reap::rengine::render
    
