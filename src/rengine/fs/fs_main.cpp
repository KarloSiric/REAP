/*======================================================================
   File: fs_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-26 15:53:16
   Last Modified by: ksiric
   Last Modified: 2026-04-26 18:47:27
   ---------------------------------------------------------------------
   Description:

   ---------------------------------------------------------------------
   License:
   Company:
   Version: 0.1.0
 ======================================================================
																	   */

#include "rengine/fs/fs_main.h"
#include <cstdio>
#include <cstring>

namespace reap::rengine::fs {

namespace {
struct fs_runtime_state_t {
	bool initialized{ false };
	fs_mount_t mounts[FS_MAX_MOUNTS]{};
	rcommon::u32 mount_count{ 0u };
	char write_path[FS_MAX_PATH_LENGTH]{};
};
} // namespace

fs_runtime_state_t g_fs_runtime_state{};

fs_error_code_t fs_init() {
	if ( g_fs_runtime_state.initialized ) {
		return fs_error_code_t::ERR_IS_INIT;
	}

	g_fs_runtime_state = {};
	g_fs_runtime_state.initialized = true;

	return fs_error_code_t::OK;
}

fs_error_code_t fs_shutdown() {
	if ( !g_fs_runtime_state.initialized ) {
		return fs_error_code_t::ERR_NOT_INIT;
	}
	g_fs_runtime_state = {};
	g_fs_runtime_state.initialized = false;
	return fs_error_code_t::OK;
}

fs_error_code_t fs_mount_directory( const char *virtual_root, const char *physical_path, rcommon::u32 flags, rcommon::u32 priority ) {
	if ( !g_fs_runtime_state.initialized ) {
		return fs_error_code_t::ERR_NOT_INIT;
	}
	if ( virtual_root == nullptr ) {
		return fs_error_code_t::ERR_INVALID_PATH;
	}
	if ( physical_path == nullptr || physical_path[0] == '\0' ) {
		return fs_error_code_t::ERR_INVALID_PATH;
	}
	const rcommon::u32 allowed_flags = FS_MOUNT_READ_ONLY | FS_MOUNT_WRITABLE;
	if ( ( flags & ~allowed_flags ) != 0u ) {
		return fs_error_code_t::ERR_INVALID_ARGUMENT;
	}
	if ( ( flags & allowed_flags ) == 0u ) {
		return fs_error_code_t::ERR_INVALID_ARGUMENT;
	}

	if ( g_fs_runtime_state.mount_count >= FS_MAX_MOUNTS ) {
		return fs_error_code_t::ERR_TOO_MANY_MOUNTS;
	}

	fs_mount_t &mount = g_fs_runtime_state.mounts[g_fs_runtime_state.mount_count];

	mount.type = fs_mount_type_t::FS_DIRECTORY;

	std::strncpy( mount.virtual_root, virtual_root, sizeof( mount.virtual_root ) - 1u );
	mount.virtual_root[sizeof( mount.virtual_root ) - 1u] = '\0';

	std::strncpy( mount.physical_root, physical_path, sizeof( mount.physical_root ) - 1u );
	mount.physical_root[sizeof( mount.physical_root ) - 1u] = '\0';
	mount.flags = flags;
	mount.priority = priority;
	++g_fs_runtime_state.mount_count;
	return fs_error_code_t::OK;
}

fs_error_code_t fs_unmount_directory( const char *virtual_root ) {
	if ( !g_fs_runtime_state.initialized ) {
		return fs_error_code_t::ERR_NOT_INIT;
	}
	if ( virtual_root == nullptr ) {
		return fs_error_code_t::ERR_INVALID_PATH;
	}
	for ( rcommon::u32 i = 0u; i < g_fs_runtime_state.mount_count; ++i ) {
		if ( std::strcmp( g_fs_runtime_state.mounts[i].virtual_root, virtual_root ) == 0 ) {
			for ( rcommon::u32 j = i; j + 1u < g_fs_runtime_state.mount_count; ++j ) {
				g_fs_runtime_state.mounts[j] = g_fs_runtime_state.mounts[j + 1u];
			}
			--g_fs_runtime_state.mount_count;
			g_fs_runtime_state.mounts[g_fs_runtime_state.mount_count] = {};

			return fs_error_code_t::OK;
		}
	}
	return fs_error_code_t::ERR_MOUNT_NOT_FOUND;
}

fs_error_code_t fs_set_write_path( const char *physical_path ) {
	if ( !g_fs_runtime_state.initialized ) {
		return fs_error_code_t::ERR_NOT_INIT;
	}
	if ( physical_path == nullptr || physical_path[0] == '\0' ) {
		return fs_error_code_t::ERR_INVALID_PATH;
	}
	std::strncpy(
		g_fs_runtime_state.write_path,
		physical_path,
		sizeof( g_fs_runtime_state.write_path ) - 1u );
	g_fs_runtime_state.write_path[sizeof( g_fs_runtime_state.write_path ) - 1u] = '\0';
	return fs_error_code_t::OK;
}

const char *fs_get_write_path() {
	if ( !g_fs_runtime_state.initialized ) {
		return nullptr;
	}
	if ( g_fs_runtime_state.write_path[0] == '\0' ) {
		return nullptr;
	}
	return g_fs_runtime_state.write_path;
}

fs_error_code_t fs_resolve_path( const char *virtual_path, char *out_resolved_path, rcommon::u32 out_resolved_path_size ) {
    if ( !g_fs_runtime_state.initialized ) {
        return fs_error_code_t::ERR_NOT_INIT;
    }
    if ( virtual_path == nullptr || virtual_path[0] == '\0' ) {
        return fs_error_code_t::ERR_INVALID_PATH;
    }
    if ( out_resolved_path == nullptr || out_resolved_path_size == 0u ) {
        return fs_error_code_t::ERR_INVALID_ARGUMENT;
    }
    out_resolved_path[0] = '\0';
    for ( rcommon::u32 i = 0u; i < g_fs_runtime_state.mount_count; ++i ) {
        const fs_mount_t &mount = g_fs_runtime_state.mounts[i];
        // @NOTE: Adding later for the so called packaging system.
        if ( mount.type != fs_mount_type_t::FS_DIRECTORY ) {
            continue;
        }
        const bool mounted_at_root = ( mount.virtual_root[0] == '\0' );
        // @NOTE: Only if it is mounted at the root.
        if ( mounted_at_root ) {
            const int written = std::snprintf( out_resolved_path, out_resolved_path_size, "%s/%s", mount.physical_root, virtual_path );
            
            if ( written < 0 || static_cast<rcommon::u32>( written ) >= out_resolved_path_size ) {
                out_resolved_path[0] = '\0';
                return fs_error_code_t::ERR_BUFFER_TOO_SMALL;
            }
            return fs_error_code_t::OK;
        }
        
        // @NOTE: For when it is not mounted at the root.
        const rcommon::u32 virtual_root_len = static_cast<rcommon::u32>( std::strlen( mount.virtual_root ) );
        if ( std::strncmp( virtual_path, mount.virtual_root, virtual_root_len ) != 0 ){
            continue;
        }
        const char next_char = virtual_path[virtual_root_len];
        if ( next_char != '\0' && next_char != '/' ) {
            continue;
        }
        const char *relative_path = virtual_path + virtual_root_len;
        if ( relative_path[0] == '/' ) {
            ++relative_path;
        }
        
        const int written = std::snprintf( out_resolved_path, out_resolved_path_size, "%s/%s", mount.virtual_root, relative_path );
        
        if ( written < 0 || static_cast<rcommon::u32>( written ) >= out_resolved_path_size ) {
            out_resolved_path[0] = '\0';
            return fs_error_code_t::ERR_BUFFER_TOO_SMALL;
        }
    }
    return fs_error_code_t::OK;
}



} // namespace reap::rengine::fs
