#pragma once

#include "rengine/common/foundation.h"

namespace reap::rengine::platform
{

enum class platform_type_t : u8 {
    UNKNOWN = 0,
    WINDOWS,
    LINUX,
    MACOSX
};    

enum class compiler_type_t : u8 {
    UNKNOWN = 0,
    CLANG,
    GCC,
    MSVC
};    
    
    
    
    
}       // namespace reap::rengine::platform
