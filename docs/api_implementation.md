# Fuse API Implementation Notes

This document explains how the current Fuse API is implemented today, where the ownership lives, and where the largest known gaps still are.

This is not a line-by-line code dump.

It is the implementation-oriented companion to [api_reference.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/api_reference.md).

## Source layout today

Current engine code lives under `src/rengine/` even though the long-term target layout is broader.

Current implemented modules:

- `rcommon`
- `log`
- `platform`
- `host`
- `render`
- `cmd`
- `cvar`
- `cfg`

## Runtime ownership model

### `main.cpp`

Source:

- [src/main.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/main.cpp)

Current role:

- initializes logging
- creates top-level host config/state
- drives the host frame loop
- shuts down host and logging

Current limitation:

- config/cmd/cvar are not fully wired into startup here yet
- visible platform/render bootstrap is not present yet

### `host`

Source:

- [host_main.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/host/host_main.cpp)

Current role:

- owns top-level runtime state transitions
- sequences `render` begin/update/render/end integration

Current limitation:

- no SDL event pumping
- no input ownership yet
- no broader subsystem orchestration yet

## Subsystem implementation notes

### `rcommon`

Source:

- [com_foundation.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_foundation.h)
- [com_error.h](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_error.h)
- [com_print.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/rcommon/com_print.cpp)

Implementation notes:

- acts as the shared foundation layer for all current systems
- packed surfaced errors are domain plus local-code pairs
- common print/error functions are intentionally lightweight

Current limitation:

- no deeper shared string/container/memory utility layer yet

### `log`

Source:

- [log_main.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/log/log_main.cpp)

Implementation notes:

- logger owns a runtime config struct and optional file handle
- filtering happens by severity and channel bitmask before formatting work
- file path and message storage use fixed-size buffers

Strength:

- this is already a solid foundation-style subsystem for the stage of the project

Current limitation:

- macro layer can still be cleaned further
- startup integration can become richer once more subsystems exist

### `platform`

Source:

- [sys_platform.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/platform/sys_platform.cpp)

Implementation notes:

- currently provides platform/compiler queries and timing/path helpers only
- this is still a pre-SDL platform layer

Current limitation:

- no windowing/input/event backend yet
- no OS abstraction around files, sockets, or process-level details yet

### `render`

Source:

- [r_main.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/render/r_main.cpp)

Implementation notes:

- current renderer owns a tiny runtime state:
  - initialized flag
  - in-frame flag
- functions currently validate lifecycle order and return typed errors

Strength:

- the contract exists before the backend exists, which is good

Current limitation:

- no SDL/OpenGL backend
- no actual draw submission
- no resource ownership

### `cmd`

Source:

- [cmd_main.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cmd/cmd_main.cpp)

Implementation notes:

- fixed-size registry
- linear lookup
- in-place token parsing into `argv`
- callback dispatch through `cmd_fn_t`

Strength:

- simple and easy to reason about

Current limitation:

- no quoted-argument aware parsing yet
- no command removal, aliases, or completion layer yet
- no console UI feeding into it yet

### `cvar`

Source:

- [cvar_main.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cvar/cvar_main.cpp)

Implementation notes:

- fixed-size registry
- each cvar caches string/int/float/bool views
- flags hold mutation policy and modified-state information

Strength:

- good base for early engine work

Current limitation:

- no persistence/save path yet
- no callbacks/change notifications yet
- no VFS-backed archive/write integration yet

### `cfg`

Source:

- [cfg_main.cpp](/Users/karlosiric/Documents/MyProjects/REAP/src/rengine/cfg/cfg_main.cpp)

Implementation notes:

- supports line-by-line file loading
- supports single-line execution via `cfg_execute_line`
- strips comments with quote awareness
- recognizes:
  - `exec`
  - `set`
  - `seta`
  - fallback command execution

Current limitation:

- still uses direct `std::fopen`
- parsing logic is duplicated between file execution and single-line execution
- should eventually centralize line execution and let file loading be only I/O

## Status assessment

The current codebase is small, but it is not toy-code anymore.

What is good:

- subsystem boundaries are visible early
- error returns are explicit
- logging/common/platform/host shape is sensible
- command/cvar/cfg foundation exists before heavier runtime systems

What is not done:

- no filesystem seam
- no visible runtime backend
- no asset/resource runtime
- no BSP path
- no client/server split

## What should happen next

The next implementation move should be:

1. add `fs`
2. route `cfg` through `fs`
3. add `SDL3` bootstrap in `platform`
4. add `OpenGL` bootstrap in `render`

That keeps the engine growing from the bottom upward instead of skipping layers.
