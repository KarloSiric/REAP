#pragma once

#include "rengine/fs/fs_error.h"
#include "rengine/fs/fs_types.h"

namespace reap::rengine::fs
{

fs_error_code_t fs_init();

fs_error_code_t fs_shutdown();

fs_error_code_t fs_mount_directory(
    const char *virtual_root,
    const char *physical_path,
    rcommon::u32 flags,
    rcommon::u32 priority );

fs_error_code_t fs_unmount_directory( const char *virtual_root );

rcommon::u32 fs_mount_count();

fs_error_code_t fs_set_write_path( const char *physical_path );

const char *fs_get_write_path();

fs_error_code_t fs_open(
    const char *virtual_path,
    fs_open_mode_t mode,
    fs_file_t &file );

fs_error_code_t fs_close( fs_file_t &file );

fs_error_code_t fs_read(
    fs_file_t &file,
    void *buffer,
    rcommon::u64 bytes_to_read,
    rcommon::u64 &bytes_read_out );

fs_error_code_t fs_write(
    fs_file_t &file,
    const void *buffer,
    rcommon::u64 bytes_to_write,
    rcommon::u64 &bytes_written_out );

fs_error_code_t fs_seek(
    fs_file_t &file,
    rcommon::i64 offset,
    fs_seek_origin_t origin );

fs_error_code_t fs_tell(
    fs_file_t &file,
    rcommon::u64 &out_position );

fs_error_code_t fs_read_entire_file(
    const char *virtual_path,
    void *buffer,
    rcommon::u64 bytes_to_read,
    rcommon::u64 &bytes_read_out );

fs_error_code_t fs_get_file_info(
    const char *virtual_path,
    fs_file_info_t &out_info );

fs_error_code_t fs_resolve_path(
    const char *virtual_path,
    char *out_resolved_path,
    rcommon::u32 out_resolved_path_size );

bool fs_exists( const char *virtual_path );

bool fs_is_initialized();

}
