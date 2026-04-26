# Fuse Engine - API Reference

Complete reference for the current public headers, types, constants, and functions exposed by the Fuse engine runtime inside the REAP project.

**Version:** 0.1.0  
**Last Updated:** April 2026

---

## Table of Contents

- [1. Introduction](#1-introduction)
- [2. Core Foundation Headers](#2-core-foundation-headers)
  - [com_foundation.h - Engine Foundation Types](#com_foundationh---engine-foundation-types)
  - [com_error.h - Common Error Surface](#com_errorh---common-error-surface)
  - [com_print.h - Common Print and Error Output](#com_printh---common-print-and-error-output)
- [3. Logging System](#3-logging-system)
  - [log_types.h - Log Types and Configuration](#log_typesh---log-types-and-configuration)
  - [log_main.h - Logger Runtime API](#log_mainh---logger-runtime-api)
- [4. Platform System](#4-platform-system)
  - [sys_platform.h - Platform and Timing API](#sys_platformh---platform-and-timing-api)
- [5. Host Runtime](#5-host-runtime)
  - [host_types.h - Runtime State and Configuration](#host_typesh---runtime-state-and-configuration)
  - [host_main.h - Host Lifecycle API](#host_mainh---host-lifecycle-api)
- [6. Renderer Contract](#6-renderer-contract)
  - [r_main.h - Renderer Lifecycle API](#r_mainh---renderer-lifecycle-api)
- [7. Command System](#7-command-system)
  - [cmd_main.h - Command Registry and Dispatch](#cmd_mainh---command-registry-and-dispatch)
- [8. Cvar System](#8-cvar-system)
  - [cvar_main.h - Console Variable Runtime](#cvar_mainh---console-variable-runtime)
- [9. Config System](#9-config-system)
  - [cfg_main.h - Config Loading and Execution](#cfg_mainh---config-loading-and-execution)
- [10. Error Headers](#10-error-headers)
- [11. Next Planned Public API](#11-next-planned-public-api)

---

## 1. Introduction

This document serves as the public API reference for Fuse.

Scope:

- documents public headers first
- describes types, constants, and function contracts
- stays focused on the visible API surface
- leaves deeper internal design and behavior to [FUSE_API_IMPLEMENTATION.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/FUSE_API_IMPLEMENTATION.md)

Naming:

- `REAP` is the overall project/game
- `Fuse` is the engine runtime
- source currently lives under `src/rengine/`

---

## 2. Core Foundation Headers

### com_foundation.h - Engine Foundation Types

**Location:** [src/rengine/rcommon/com_foundation.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_foundation.h)

Shared engine-owned foundational types and constants.

#### Type Aliases

| Alias Group | Examples | Description |
|-------------|----------|-------------|
| Signed integers | `i8`, `i16`, `i32`, `i64` | Fixed-width signed types |
| Unsigned integers | `u8`, `u16`, `u32`, `u64` | Fixed-width unsigned types |
| Floating point | `f32`, `f64` | Engine floating-point aliases |
| Size types | `usize` | Memory and container sizes |
| Runtime IDs | `frame_index_t`, `entity_id_t` | Engine runtime identifiers |

#### Constants

| Constant | Description |
|----------|-------------|
| `COM_INVALID_FRAME_INDEX` | Sentinel invalid frame index |
| `COM_INVALID_ENTITY_ID` | Sentinel invalid entity id |
| `COM_PI_F` | Pi as `f32` |
| `COM_TAU_F` | Tau as `f32` |
| `COM_DEG2RAD_F` | Degrees-to-radians multiplier |
| `COM_RAD2DEG_F` | Radians-to-degrees multiplier |
| `COM_EPSILON_F` | Small floating epsilon |
| `COM_INFINITY_F` | Floating infinity |

---

### com_error.h - Common Error Surface

**Location:** [src/rengine/rcommon/com_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_error.h)

Packed surfaced-error API used when subsystem-local typed errors need to cross subsystem boundaries.

#### Types

| Type | Description |
|------|-------------|
| `com_error_t` | Packed 32-bit surfaced error |
| `com_domain_t` | Subsystem/domain identifier |
| `com_error_code_t` | Canonical common error enum |

#### Important Functions

| Function | Description |
|----------|-------------|
| `com_error_ok( code )` | True when code equals `OK` |
| `com_error_failed( code )` | True when code is not `OK` |
| `com_error_name( code )` | String name of common error code |
| `com_domain_name( domain )` | String name of domain |
| `com_error_make( domain, local_error_code )` | Pack domain and local code |
| `com_error_domain( error )` | Extract packed domain |
| `com_error_code( error )` | Extract packed local code |

---

### com_print.h - Common Print and Error Output

**Location:** [src/rengine/rcommon/com_print.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_print.h)

Formatted output helpers shared by subsystems.

#### Constants

| Constant | Description |
|----------|-------------|
| `COM_MSG_MAX` | Maximum formatted message size |

#### Functions

| Function | Description |
|----------|-------------|
| `com_printf( const char *message, ... )` | General formatted output |
| `com_dprintf( const char *message, ... )` | Debug-oriented formatted output |
| `com_vprintf( const char *message, va_list args )` | `va_list` print variant |
| `com_errorf( com_error_t error, const char *message, ... )` | Formatted surfaced error output |
| `com_verrorf( com_error_t error, const char *message, va_list args )` | `va_list` error variant |

---

## 3. Logging System

### log_types.h - Log Types and Configuration

**Location:** [src/rengine/log/log_types.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/log/log_types.h)

Defines log severities, channels, records, and runtime configuration.

#### Important Types

| Type | Description |
|------|-------------|
| `log_level_t` | Trace-to-fatal severity enum |
| `log_file_mode_t` | File open mode policy |
| `log_flush_policy_t` | Flush behavior policy |
| `log_source_path_mode_t` | Basename vs full source path mode |
| `log_channel_t` | Subsystem channel enum |
| `log_record_t` | Built log event payload |
| `log_config_t` | Runtime logger configuration |

#### Important Helpers

| Function | Description |
|----------|-------------|
| `log_level_name( level )` | String name of log level |
| `log_channel_name( channel )` | String name of log channel |
| `log_channel_bit( channel )` | Bitmask for channel |

---

### log_main.h - Logger Runtime API

**Location:** [src/rengine/log/log_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/log/log_main.h)

Public logger lifecycle, configuration, and emission API.

#### Functions

| Function | Description |
|----------|-------------|
| `log_init( const log_config_t &config = {} )` | Initialize logging subsystem |
| `log_shutdown()` | Shutdown logger |
| `log_get_config()` | Get active config |
| `log_set_config( const log_config_t &config )` | Replace runtime config |
| `log_level_enabled( level, channel )` | Check if event would be accepted |
| `log_channel_enabled( channel_mask, channel )` | Check a channel bit in a mask |
| `log_emit( const log_record_t &record )` | Emit fully-built record |
| `log_emitf( ... )` | Build and emit formatted record |
| `log_emitfv( ... )` | `va_list` formatted emit |

#### Macro Layer

| Macro | Description |
|-------|-------------|
| `REAP_LOG_TRACE` | Trace severity log |
| `REAP_LOG_DEBUG` | Debug severity log |
| `REAP_LOG_INFO` | Info severity log |
| `REAP_LOG_WARNING` | Warning severity log |
| `REAP_LOG_ERROR` | Error severity log |
| `REAP_LOG_FATAL` | Fatal severity log |
| `REAP_LOG_CHECK` | Condition-check logging helper |

---

## 4. Platform System

### sys_platform.h - Platform and Timing API

**Location:** [src/rengine/platform/sys_platform.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/platform/sys_platform.h)

Platform/compiler detection and timing/path utility API.

#### Types

| Type | Description |
|------|-------------|
| `platform_t` | Operating-system family enum |
| `compiler_t` | Compiler family enum |

#### Functions

| Function | Description |
|----------|-------------|
| `sys_platform_type()` | Return build platform |
| `sys_compiler_type()` | Return build compiler |
| `sys_platform_name( type )` | String name of platform |
| `sys_compiler_name( type )` | String name of compiler |
| `sys_path_basename( const char *path )` | Basename view into path |
| `sys_time_now_seconds()` | Monotonic time in seconds |
| `sys_local_time( std::time_t time_value, std::tm &time_out )` | Local-time conversion helper |

---

## 5. Host Runtime

### host_types.h - Runtime State and Configuration

**Location:** [src/rengine/host/host_types.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/host/host_types.h)

Defines top-level runtime state and startup configuration types.

#### Important Types

| Type | Description |
|------|-------------|
| `host_stage_t` | High-level runtime lifecycle stage |
| `build_config_t` | Debug/release/distribution build mode |
| `viewport_t` | Width/height pair |
| `window_config_t` | Window startup configuration |
| `frame_t` | Per-frame timing state |
| `host_config_t` | Top-level host startup config |
| `host_state_t` | Mutable runtime host state |

---

### host_main.h - Host Lifecycle API

**Location:** [src/rengine/host/host_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/host/host_main.h)

Top-level runtime lifecycle API used by the executable entry point.

#### Functions

| Function | Description |
|----------|-------------|
| `host_init( host_state_t &host_state, const host_config_t &host_config )` | Initialize host runtime |
| `host_shutdown( host_state_t &host_state )` | Shutdown host runtime |
| `host_begin_frame( host_state_t &host_state, f32 delta_time_seconds )` | Begin current frame |
| `host_update( host_state_t &host_state )` | Update host simulation |
| `host_render( host_state_t &host_state )` | Render current frame |
| `host_end_frame( host_state_t &host_state )` | Finalize current frame |
| `host_is_running( host_state_t &host_state )` | Main-loop continuation query |

---

## 6. Renderer Contract

### r_main.h - Renderer Lifecycle API

**Location:** [src/rengine/render/r_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/render/r_main.h)

Defines the current renderer lifecycle contract.

#### Functions

| Function | Description |
|----------|-------------|
| `r_init( const host::window_config_t &window_config )` | Initialize renderer |
| `r_shutdown()` | Shutdown renderer |
| `r_begin_frame( f32 delta_time_seconds )` | Begin a render frame |
| `r_render_frame()` | Submit/render current frame |
| `r_render_end()` | End current frame |
| `r_is_initialized()` | Query init state |

---

## 7. Command System

### cmd_main.h - Command Registry and Dispatch

**Location:** [src/rengine/cmd/cmd_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cmd/cmd_main.h)

Fixed-registry command backend for textual command dispatch.

#### Constants

| Constant | Description |
|----------|-------------|
| `CMD_MAX_COMMANDS` | Maximum registered commands |
| `CMD_MAX_ARGUMENTS` | Maximum parsed command arguments |

#### Types

| Type | Description |
|------|-------------|
| `cmd_fn_t` | Command callback signature |
| `cmd_t` | Registered command entry |
| `cmd_registry_t` | Command registry state |

#### Functions

| Function | Description |
|----------|-------------|
| `cmd_init()` | Initialize command system |
| `cmd_shutdown()` | Shutdown command system |
| `cmd_register( const char *cmd_name, cmd_fn_t callback_fn, const char *cmd_description )` | Register command |
| `cmd_find( const char *cmd_name )` | Find command by name |
| `cmd_parse( char *command_line, u32 &argc, char **argv )` | Tokenize command line |
| `cmd_execute( const char *command_line )` | Parse and dispatch command |

---

## 8. Cvar System

### cvar_main.h - Console Variable Runtime

**Location:** [src/rengine/cvar/cvar_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cvar/cvar_main.h)

Fixed-registry console variable system with cached typed views.

#### Constants

| Constant | Description |
|----------|-------------|
| `CVAR_MAX_CVARS` | Maximum registered cvars |
| `CVAR_REGISTER_ALLOWED_FLAGS` | Flags permitted during registration |

#### Types

| Type | Description |
|------|-------------|
| `cvar_flags_t` | Cvar policy/state flags |
| `cvar_t` | Cvar entry |
| `cvar_registry_t` | Cvar registry state |

#### Flags

| Flag | Description |
|------|-------------|
| `CVAR_NONE` | No flags |
| `CVAR_ARCHIVE` | Persist/save candidate |
| `CVAR_READONLY` | Cannot be changed normally |
| `CVAR_CHEAT` | Cheat-protected cvar |
| `CVAR_DEV` | Development-oriented cvar |
| `CVAR_MODIFIED` | Changed during current session |

#### Functions

| Function | Description |
|----------|-------------|
| `cvar_init()` | Initialize cvar system |
| `cvar_register( const char *name, const char *default_value, cvar_flags_t flags )` | Register cvar |
| `cvar_set( const char *name, const char *value )` | Change cvar value |
| `cvar_shutdown()` | Shutdown cvar system |
| `cvar_find( const char *name )` | Find cvar by name |
| `cvar_get_string( const char *name )` | Get string value |
| `cvar_get_int( const char *name )` | Get cached integer value |
| `cvar_get_float( const char *name )` | Get cached float value |
| `cvar_get_bool( const char *name )` | Get cached boolean value |

---

## 9. Config System

### cfg_main.h - Config Loading and Execution

**Location:** [src/rengine/cfg/cfg_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cfg/cfg_main.h)

Config runtime used for loading startup/runtime config files and executing config-style lines.

#### Constants

| Constant | Description |
|----------|-------------|
| `CFG_MAX_LINE_LENGTH` | Maximum cfg line length |
| `CFG_MAX_PATH_LENGTH` | Maximum cfg path length |

#### Functions

| Function | Description |
|----------|-------------|
| `cfg_init()` | Initialize cfg subsystem |
| `cfg_shutdown()` | Shutdown cfg subsystem |
| `cfg_load_file( const char *path, bool required = false )` | Load cfg file from path |
| `cfg_load_default()` | Load default startup cfg |
| `cfg_load_autoexec()` | Load optional autoexec cfg |
| `cfg_execute_line( const char *command_line )` | Execute a single cfg-style command line |

#### Supported Line Forms

| Form | Behavior |
|------|----------|
| `exec <path>` | Load another cfg file |
| `set <name> <value>` | Set cvar value |
| `seta <name> <value>` | Set archive-oriented cvar value |
| `<command ...>` | Fallback to command execution |

---

## 10. Error Headers

Each major subsystem currently exposes a typed local error enum in its own header:

- [src/rengine/log/log_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/log/log_error.h)
- [src/rengine/host/host_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/host/host_error.h)
- [src/rengine/platform/sys_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/platform/sys_error.h)
- [src/rengine/render/r_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/render/r_error.h)
- [src/rengine/cmd/cmd_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cmd/cmd_error.h)
- [src/rengine/cvar/cvar_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cvar/cvar_error.h)
- [src/rengine/cfg/cfg_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cfg/cfg_error.h)

Current design rule:

- use typed local error enums inside a subsystem
- convert to `rcommon::com_error_t` when surfacing failures across subsystem boundaries

---

## 11. Next Planned Public API

The next major public API expected to be added is the filesystem layer.

Planned direction:

- `fs_init()`
- `fs_shutdown()`
- mount/search path registration
- engine-owned file open/read helpers
- later archive integration for `rpk` or another package format
