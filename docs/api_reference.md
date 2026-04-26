# Fuse API Reference

This document describes the current public API surface of the Fuse engine runtime inside the REAP project.

Scope rules:

- this file documents public contracts
- it follows headers first
- it is allowed to lag implementation detail slightly, but not the declared interface
- deeper internal notes belong in [api_implementation.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/api_implementation.md)

## Naming

- `REAP` is the overall project/game
- `Fuse` is the engine runtime
- source currently lives under `src/rengine/`

## `rcommon`

Source:

- [com_foundation.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_foundation.h)
- [com_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_error.h)
- [com_print.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_print.h)

Purpose:

- fixed-width types
- shared numeric/runtime constants
- packed common error representation
- formatted print/error helpers

Important API:

- integer and floating aliases such as `u32`, `i32`, `f32`, `f64`
- `com_error_t`
  - packed cross-subsystem surfaced error value
- `com_error_make( domain, local_code )`
  - packs a subsystem domain and local code into one surfaced error
- `com_error_domain( error )`
  - extracts the subsystem domain
- `com_error_code( error )`
  - extracts the local subsystem code
- `com_printf( ... )`
  - general formatted output helper
- `com_dprintf( ... )`
  - debug-oriented formatted output helper
- `com_errorf( error, ... )`
  - formatted surfaced-error output helper

## `log`

Source:

- [log_types.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/log/log_types.h)
- [log_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/log/log_main.h)

Purpose:

- severity/channel-aware runtime logging
- console/file output policy

Important types:

- `log_level_t`
- `log_channel_t`
- `log_record_t`
- `log_config_t`

Important API:

- `log_init( const log_config_t &config = {} )`
- `log_shutdown()`
- `log_get_config()`
- `log_set_config( const log_config_t &config )`
- `log_level_enabled( level, channel )`
- `log_channel_enabled( mask, channel )`
- `log_emit( const log_record_t &record )`
- `log_emitf( ... )`
- `log_emitfv( ... )`

Macro layer:

- `REAP_LOG_TRACE`
- `REAP_LOG_DEBUG`
- `REAP_LOG_INFO`
- `REAP_LOG_WARNING`
- `REAP_LOG_ERROR`
- `REAP_LOG_FATAL`

## `platform`

Source:

- [sys_platform.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/platform/sys_platform.h)

Purpose:

- engine-owned platform/compiler queries
- path helpers
- time helpers

Important types:

- `platform_t`
- `compiler_t`

Important API:

- `sys_platform_type()`
- `sys_compiler_type()`
- `sys_platform_name( type )`
- `sys_compiler_name( type )`
- `sys_path_basename( path )`
- `sys_time_now_seconds()`
- `sys_local_time( time_value, time_out )`

## `host`

Source:

- [host_types.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/host/host_types.h)
- [host_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/host/host_main.h)

Purpose:

- top-level runtime ownership
- frame lifecycle sequencing

Important types:

- `host_stage_t`
- `build_config_t`
- `viewport_t`
- `window_config_t`
- `frame_t`
- `host_config_t`
- `host_state_t`

Important API:

- `host_init( host_state_t &, const host_config_t & )`
- `host_shutdown( host_state_t & )`
- `host_begin_frame( host_state_t &, f32 delta_time_seconds )`
- `host_update( host_state_t & )`
- `host_render( host_state_t & )`
- `host_end_frame( host_state_t & )`
- `host_is_running( host_state_t & )`

## `render`

Source:

- [r_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/render/r_main.h)

Purpose:

- renderer lifecycle contract
- explicit init/frame-state validation

Important API:

- `r_init( const host::window_config_t &window_config )`
- `r_shutdown()`
- `r_begin_frame( f32 delta_time_seconds )`
- `r_render_frame()`
- `r_render_end()`
- `r_is_initialized()`

## `cmd`

Source:

- [cmd_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cmd/cmd_main.h)

Purpose:

- fixed command registry
- command lookup
- command-line parsing
- callback execution

Important types and constants:

- `CMD_MAX_COMMANDS`
- `CMD_MAX_ARGUMENTS`
- `cmd_fn_t`
- `cmd_t`
- `cmd_registry_t`

Important API:

- `cmd_init()`
- `cmd_shutdown()`
- `cmd_register( const char *cmd_name, cmd_fn_t callback_fn, const char *cmd_description )`
- `cmd_find( const char *cmd_name )`
- `cmd_parse( char *command_line, u32 &argc, char **argv )`
- `cmd_execute( const char *command_line )`

## `cvar`

Source:

- [cvar_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cvar/cvar_main.h)

Purpose:

- fixed cvar registry
- cached string/int/float/bool values
- flag-based mutation policy

Important types and constants:

- `CVAR_MAX_CVARS`
- `cvar_flags_t`
- `cvar_t`
- `cvar_registry_t`
- `CVAR_REGISTER_ALLOWED_FLAGS`

Important API:

- `cvar_init()`
- `cvar_register( const char *name, const char *default_value, cvar_flags_t flags )`
- `cvar_set( const char *name, const char *value )`
- `cvar_shutdown()`
- `cvar_find( const char *name )`
- `cvar_get_string( const char *name )`
- `cvar_get_int( const char *name )`
- `cvar_get_float( const char *name )`
- `cvar_get_bool( const char *name )`

## `cfg`

Source:

- [cfg_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cfg/cfg_main.h)

Purpose:

- startup/runtime config loading
- single-line cfg execution
- bridge between textual config and `cmd`/`cvar`

Important constants:

- `CFG_MAX_LINE_LENGTH`
- `CFG_MAX_PATH_LENGTH`

Important API:

- `cfg_init()`
- `cfg_shutdown()`
- `cfg_load_file( const char *path, bool required = false )`
- `cfg_load_default()`
- `cfg_load_autoexec()`
- `cfg_execute_line( const char *command_line )`

## Error enums

Each major subsystem currently exposes its own local error enum in a dedicated header:

- `log_error.h`
- `host_error.h`
- `r_error.h`
- `cmd_error.h`
- `cvar_error.h`
- `cfg_error.h`
- `sys_error.h`

The current pattern is:

- use subsystem-local typed enums internally
- surface cross-subsystem failures through `rcommon::com_error_t` when needed

## Next API expected to appear

The next major public API addition should be the filesystem layer, likely in a new `fs` subsystem with contracts for:

- init/shutdown
- mount/search path setup
- file open/read queries
- later archive integration
