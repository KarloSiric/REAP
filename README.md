# REAP

REAP is a from-scratch 3D arena survival FPS project.

`Fuse` is the native engine runtime being built inside REAP. The long-term goal is not only to ship the game, but also to build the surrounding runtime, toolchain, formats, and scripting path in a disciplined way.

## Direction

The current technical direction is:

- `SDL3` for the platform/window/input layer
- `OpenGL` for rendering
- `Quake III BSP` as the first serious authored map format
- custom engine-owned tools when runtime pressure justifies them
- later custom asset formats such as `rmdl` and archive packaging such as `rpk`

Quake I, II, and III are reference points for learning and architecture, not code sources to copy blindly.

## Current State

The codebase is still early, but it is real and moving in the right direction.

Today the repository contains roughly `3.2k` lines of source under `src/` with these runtime foundations in place:

- `rcommon`
  - core types
  - packed cross-subsystem error surface
  - formatted print/error helpers
- `log`
  - runtime config
  - level filtering
  - channel masking
  - console/file sink path
- `platform`
  - platform/compiler detection
  - basename helper
  - monotonic time helper
- `host`
  - top-level runtime stage and frame loop ownership
- `render`
  - renderer lifecycle contract with error-coded begin/render/end path
- `cmd`
  - command registry
  - argument parsing
  - callback dispatch
- `cvar`
  - cvar registry
  - typed cached values
  - flags and mutation path
- `cfg`
  - cfg file loading
  - single-line execution
  - `exec`, `set`, `seta`, and command fallback

What does not exist yet:

- virtual filesystem
- SDL3 platform backend
- OpenGL context/bootstrap
- shader/texture asset runtime
- BSP loader/runtime
- client/server split
- tools pipeline

## Near-Term Path

The immediate build order is:

1. `fs` / virtual filesystem
2. `SDL3` platform bootstrap
3. `OpenGL` renderer bootstrap
4. local graybox 3D runtime
5. `Quake III BSP` loading and rendering
6. later tools and custom formats such as `rmdl`, `rpk`, and a small purpose-built editor

## Documentation Map

Start here:

- [docs/index.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/index.md)
- [docs/current_status.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/current_status.md)
- [docs/development_phases.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/development_phases.md)
- [docs/roadmap.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/roadmap.md)
- [docs/architecture.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/architecture.md)
- [docs/subsystems.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/subsystems.md)
- [docs/toolchain_plan.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/toolchain_plan.md)
- [docs/API_REFERENCE.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/API_REFERENCE.md)
- [docs/API_IMPLEMENTATION.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/API_IMPLEMENTATION.md)

Long-lived project memory:

- [CHANGELOG.md](/Users/karlosiric/Documents/MyProjects/REAP/CHANGELOG.md)
- [docs/devlog/2026-04.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/devlog/2026-04.md)
- [docs/adr/0001-coop-first-listen-server-architecture.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/adr/0001-coop-first-listen-server-architecture.md)

## Build

Current build path:

```bash
cmake -S . -B build
cmake --build build
./build/bin/reap
```

Later, a thin convenience wrapper can sit on top of this, but CMake remains the real build source of truth.
