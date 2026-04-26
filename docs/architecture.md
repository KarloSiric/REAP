# REAP Architecture

REAP is a layered project made of three connected bodies of work:

- `Fuse` engine runtime
- game logic
- tools and offline pipeline

The long-term structure follows Quake-style separation, adapted to REAP and modern C++.

## Top-level architecture

### `src/`

The native engine runtime.

Target modules:

- `common`
- `renderer`
- `server`
- `client`
- `network`
- `bsp`
- `physics`
- `audio`
- `ecs`
- `vm`
- `platform`

### `rvm/`

Standalone REAP Virtual Machine project.

Owns:

- VM runtime
- assembler
- disassembler
- later the REAP Script compiler

### `game/`

Gameplay scripts intended to run on the VM.

This is where high-level REAP gameplay should live once the VM path is real:

- players
- waves
- enemies
- combat
- items
- rules

### `tools/`

Offline pipeline executables.

Owns:

- model compiler/decompiler
- texture pipeline
- archive tooling
- small engine-owned editor tools when justified

## Boundary rules

- `common` is shared foundation
- `renderer` owns GPU-facing code
- `server` owns authoritative simulation
- `client` owns local input/prediction/presentation bridge
- `network` owns transport and serialization primitives
- `bsp` owns map loading and collision/visibility queries
- `physics` owns movement and shared simulation code
- `audio` owns sound runtime
- `ecs` owns entity/component integration layer
- `vm` is the bridge between engine runtime and `rvm`
- `platform` owns OS-facing behavior and the SDL seam

## Current implementation reality

The current repository is much earlier than the target structure.

Today:

- code is still concentrated in `src/rengine/`
- the project is still in bootstrap/foundation phase
- command/cvar/cfg subsystems already exist before the visible runtime backend does
- the next major missing seam is the filesystem layer

That is acceptable for now, as long as new work follows the documented target structure from this point forward.

## Design philosophy

- engine-owned interfaces at subsystem boundaries
- explicit data flow
- no heavy abstraction without runtime pressure
- learn from Quake/DOOM lineage without copying blindly
- long-term maintainability for a solo developer
