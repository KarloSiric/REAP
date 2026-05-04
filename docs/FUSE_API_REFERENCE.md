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
| `Com_ErrorOk( code )` | True when code equals `OK` |
| `Com_ErrorFailed( code )` | True when code is not `OK` |
| `Com_ErrorName( code )` | String name of common error code |
| `Com_DomainName( domain )` | String name of domain |
| `Com_ErrorMake( domain, local_error_code )` | Pack domain and local code |
| `Com_ErrorDomain( error )` | Extract packed domain |
| `Com_ErrorCode( error )` | Extract packed local code |

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
| `Com_Printf( const char *message, ... )` | General formatted output |
| `Com_DPrintf( const char *message, ... )` | Debug-oriented formatted output |
| `Com_VPrintf( const char *message, va_list args )` | `va_list` print variant |
| `Com_Errorf( com_error_t error, const char *message, ... )` | Formatted surfaced error output |
| `Com_VErrorf( com_error_t error, const char *message, va_list args )` | `va_list` error variant |

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
| `Log_LevelName( level )` | String name of log level |
| `Log_ChannelName( channel )` | String name of log channel |
| `Log_ChannelBit( channel )` | Bitmask for channel |

---

### log_main.h - Logger Runtime API

**Location:** [src/rengine/log/log_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/log/log_main.h)

Public logger lifecycle, configuration, and emission API.

#### Functions

| Function | Description |
|----------|-------------|
| `Log_Init( const log_config_t &config = {} )` | Initialize logging subsystem |
| `Log_Shutdown()` | Shutdown logger |
| `Log_GetConfig()` | Get active config |
| `Log_SetConfig( const log_config_t &config )` | Replace runtime config |
| `Log_LevelEnabled( level, channel )` | Check if event would be accepted |
| `Log_ChannelEnabled( channel_mask, channel )` | Check a channel bit in a mask |
| `Log_Emit( const log_record_t &record )` | Emit fully-built record |
| `Log_Emitf( ... )` | Build and emit formatted record |
| `Log_Emitfv( ... )` | `va_list` formatted emit |

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
| `Sys_PlatformType()` | Return build platform |
| `Sys_CompilerType()` | Return build compiler |
| `Sys_PlatformName( type )` | String name of platform |
| `Sys_CompilerName( type )` | String name of compiler |
| `Sys_PathBasename( const char *path )` | Basename view into path |
| `Sys_TimeNowSeconds()` | Monotonic time in seconds |
| `Sys_LocalTime( std::time_t time_value, std::tm &time_out )` | Local-time conversion helper |

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
| `Host_Init( host_state_t &host_state, const host_config_t &host_config )` | Initialize host runtime |
| `Host_Shutdown( host_state_t &host_state )` | Shutdown host runtime |
| `Host_BeginFrame( host_state_t &host_state, f32 delta_time_seconds )` | Begin current frame |
| `Host_Update( host_state_t &host_state )` | Update host simulation |
| `Host_Render( host_state_t &host_state )` | Render current frame |
| `Host_EndFrame( host_state_t &host_state )` | Finalize current frame |
| `Host_IsRunning( host_state_t &host_state )` | Main-loop continuation query |

---

## 6. Renderer Contract

### r_main.h - Renderer Lifecycle API

**Location:** [src/rengine/render/r_main.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/render/r_main.h)

Defines the current renderer lifecycle contract.

#### Functions

| Function | Description |
|----------|-------------|
| `R_Init( const host::window_config_t &window_config )` | Initialize renderer |
| `R_Shutdown()` | Shutdown renderer |
| `R_BeginFrame( f32 delta_time_seconds )` | Begin a render frame |
| `R_RenderFrame()` | Submit/render current frame |
| `R_EndFrame()` | End current frame |
| `R_IsInitialized()` | Query init state |

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
| `Cmd_Init()` | Initialize command system |
| `Cmd_Shutdown()` | Shutdown command system |
| `Cmd_Register( const char *cmd_name, cmd_fn_t callback_fn, const char *cmd_description )` | Register command |
| `Cmd_Find( const char *cmd_name )` | Find command by name |
| `Cmd_Parse( char *command_line, u32 &argc, char **argv )` | Tokenize command line |
| `Cmd_Execute( const char *command_line )` | Parse and dispatch command |

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
| `Cvar_Init()` | Initialize cvar system |
| `Cvar_Register( const char *name, const char *default_value, cvar_flags_t flags )` | Register cvar |
| `Cvar_Set( const char *name, const char *value )` | Change cvar value |
| `Cvar_Shutdown()` | Shutdown cvar system |
| `Cvar_Find( const char *name )` | Find cvar by name |
| `Cvar_GetString( const char *name )` | Get string value |
| `Cvar_GetInt( const char *name )` | Get cached integer value |
| `Cvar_GetFloat( const char *name )` | Get cached float value |
| `Cvar_GetBool( const char *name )` | Get cached boolean value |

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
| `Cfg_Init()` | Initialize cfg subsystem |
| `Cfg_Shutdown()` | Shutdown cfg subsystem |
| `Cfg_LoadFile( const char *path, bool required = false )` | Load cfg file from path |
| `Cfg_LoadDefault()` | Load default startup cfg |
| `Cfg_LoadAutoexec()` | Load optional autoexec cfg |
| `Cfg_ExecuteLine( const char *command_line )` | Execute a single cfg-style command line |

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

- `FS_Init()`
- `FS_Shutdown()`
- mount/search path registration
- engine-owned file open/read helpers
- later archive integration for `rpk` or another package format
