# REAP Current Status

## Project state

REAP is still in early foundation stage, but the runtime stack is now more real than the old docs implied.

`Fuse` is the engine runtime inside the REAP project.

Current code snapshot:

- roughly `3.2k` lines of source under `src/`
- early runtime modules live under `src/rengine/`
- build succeeds through CMake
- the executable runs through the host/frame loop scaffold

## What exists now

- foundational types and shared error surface
- common formatted print/error helpers
- logging runtime
- early platform runtime helpers
- host lifecycle scaffold
- renderer lifecycle contract
- command system backend
- cvar system backend
- cfg loading/execution backend
- documentation/process system

## What is done-for-now

- `rcommon`
  - type aliases
  - numeric constants
  - sentinel values
  - packed subsystem error representation
  - formatted print/error helpers
- `log`
  - runtime state
  - level/channel filtering
  - console/file output path
- `platform`
  - platform/compiler detection
  - basename helper
  - monotonic time helper
  - local-time helper
- `host`
  - startup/shutdown ownership
  - frame begin/update/render/end sequencing
- `render`
  - init/shutdown state
  - in-frame state validation
  - error-coded lifecycle contract
- `cmd`
  - command registry
  - duplicate prevention
  - fixed argument parsing
  - callback execution
- `cvar`
  - fixed registry
  - typed cached values
  - flags
  - set/find/get path
- `cfg`
  - file loading
  - line execution
  - `exec`
  - `set`
  - `seta`
  - fallback command dispatch

## Active milestone

`M2 - Filesystem and SDL3/OpenGL Runtime Bootstrap`

This milestone is complete only when:

- the engine has a real virtual filesystem layer
- cfg loading can go through that filesystem layer
- the platform layer boots through `SDL3`
- an `OpenGL` context can be created cleanly
- the renderer lifecycle is backed by a visible runtime instead of only state checks

## Immediate next tasks

1. add `fs` / virtual filesystem as the next foundational subsystem
2. route cfg file loading through the filesystem API
3. migrate the runtime bootstrap direction to `SDL3`
4. bring up an `OpenGL` context behind the renderer/platform seam
5. keep docs and API references aligned as the runtime grows

## Explicitly not active yet

- real BSP runtime implementation
- client/server networking
- gameplay loop
- `rmdl` runtime/tooling
- `rpk` packaging
- custom editor tooling
- VM/game-script runtime

These are all intended, but they are not the current coding target.

## Resume rule

If work pauses, resume from this file first.

Do not restart architecture design from scratch unless this file and the surrounding docs are intentionally updated with a new direction.
