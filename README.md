# REAP

REAP is a from-scratch 3D arena survival FPS built with a Quake-era mindset:

- explicit systems
- clear module boundaries
- fast iteration
- gameplay-first engine growth
- tools built when runtime pressure justifies them

The long-term goal is not only to ship the game, but to build the surrounding runtime, toolchain, formats, and scripting path in a disciplined way.

## Project Direction

REAP follows a Quake 3 / id Software style structure adapted to this project:

- `src/common` for shared engine foundation
- `src/renderer` for all rendering
- `src/server` for authoritative simulation
- `src/client` for local player runtime and presentation bridge
- `src/network` for low-level networking
- `src/bsp` for map loading and collision
- `src/physics` for shared movement and simulation
- `src/audio` for sound runtime
- `src/ecs` for entity/component integration
- `src/vm` for engine-side VM bridge
- `src/platform` for OS-specific code
- `rvm/` as a standalone virtual machine project
- `game/` for gameplay scripts
- `tools/` for asset pipeline executables
- `data/` for runtime assets
- `config/` for default configuration

This is the intended destination structure.  
The current codebase is still early and has not been fully migrated into that layout yet.

## Core Principles

- Build one real subsystem at a time.
- Keep engine-owned interfaces between subsystems.
- Avoid speculative overengineering.
- Re-derive ideas from Quake/DOOM lineage instead of copying code.
- Make the project resumable after long breaks through strong documentation.

## Current State

The project is still in foundation/bootstrap stage.

Currently in place:
- foundational types
- app lifecycle scaffold
- logger scaffold
- early platform scaffold
- documentation system and architecture direction

Currently missing:
- render bootstrap
- windowed runtime
- command/cvar backend
- real gameplay loop
- BSP runtime
- VM runtime
- asset pipeline

Read the current active status in [docs/current_status.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/current_status.md).

## Documentation Map

Start here:

- [docs/index.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/index.md)
- [docs/project_structure.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/project_structure.md)
- [docs/development_phases.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/development_phases.md)
- [docs/current_status.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/current_status.md)
- [docs/architecture.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/architecture.md)
- [docs/subsystems.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/subsystems.md)
- [docs/toolchain_plan.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/toolchain_plan.md)
- [docs/build_guide.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/build_guide.md)
- [docs/coding_style.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/coding_style.md)
- [docs/reference_policy.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/reference_policy.md)

Long-lived project memory:

- [CHANGELOG.md](/Users/karlosiric/Documents/MyProjects/REAP/CHANGELOG.md)
- [docs/devlog/2026-04.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/devlog/2026-04.md)
- [docs/adr/0001-coop-first-listen-server-architecture.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/adr/0001-coop-first-listen-server-architecture.md)

## Build

Current build path:

```bash
cmake -S . -B build
cmake --build build
```

Long-term, a thin `build.sh` wrapper will sit on top of the real build system for convenience.
