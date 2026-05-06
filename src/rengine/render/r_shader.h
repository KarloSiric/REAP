#pragma once

#include "rengine/rcommon/com_main.h"
#include "rengine/render/r_error.h"


namespace reap::rengine::render
{

constexpr rcommon::u32 R_MAX_SHADER_NAME    = 64u;    
constexpr rcommon::u32 R_MAX_SHADER_PATH    = 256u;    
constexpr rcommon::u32 R_MAX_SHADERS        = 1024u;

struct r_shader_t {
    rcommon::com_u32 shader_id{ 0 };
    char name[R_MAX_SHADER_NAME]{};
    char vertex_path[R_MAX_SHADER_PATH]{};
    char fragment_path[R_MAX_SHADER_PATH]{};
    
    rcommon::u32 gl_program_id{ 0 };
    bool loaded{ false };
};

struct r_shader_registry_t {
    r_shader_t shaders[R_MAX_SHADERS]{};
    rcommon::u32 shader_count{ 0 };
};

void R_ShaderRegistryInit( r_shader_registry_t &registry );

void R_ShaderRegistryShutdown( r_shader_registry_t &registry );

r_error_code_t R_ShaderLoad( const char *name, const char *vertex_path, const char *fragment_path,  )



    
}       // namespace reap::rengine::
