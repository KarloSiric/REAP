# REAP Architecture

REAP is a large, layered project made of three connected bodies of work:

- `engine runtime`
- `game logic`
- `tools and offline pipeline`

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
- pak/archive tooling
- asset build scripts

## Boundary rules

- `common` is shared foundation
- `renderer` owns drawing and GPU-facing code
- `server` owns authoritative simulation
- `client` owns local input/prediction/presentation bridge
- `network` owns transport and serialization primitives
- `bsp` owns map loading and collision queries
- `physics` owns movement and shared simulation code
- `audio` owns sound runtime
- `ecs` owns entity/component integration layer
- `vm` is the bridge between engine runtime and `rvm`
- `platform` owns OS-specific behavior

## Current implementation reality

The current repository is earlier than the target structure.

Today:
- code is still concentrated in `src/rengine/`
- the project is still in runtime bootstrap
- many target modules are planned but not yet created

That is acceptable for now, as long as new work follows the documented target structure from this point forward.

## Design philosophy

- engine-owned interfaces at subsystem boundaries
- explicit data flow
- no heavy abstraction without runtime pressure
- original implementations inspired by Quake/DOOM lineage, not copied
- long-term maintainability for a solo developer
