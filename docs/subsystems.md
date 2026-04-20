# REAP Subsystem Map

This file defines what each major subsystem is responsible for and where it should live.

## Product layers

### `rengine`
Reusable runtime and engine services.

Owns:
- app lifecycle
- platform/runtime helpers
- logging
- renderer bootstrap and frame submission
- networking runtime
- physics/runtime math
- asset runtime loading
- debug services

Must not own:
- REAP-specific enemy logic
- wave rules
- weapon balance
- class abilities

### `rgame`
REAP-specific game code.

Owns:
- player rules
- weapon behavior
- pickups
- enemies
- waves
- scoring
- match flow
- HUD and gameplay-facing UI state

### `tools`
Offline authoring and build pipeline support.

Owns:
- model compile/decompile tools
- map inspection/debug tools
- package/archive tools
- asset validation and conversion

## Engine runtime subsystems

### `common`
Purpose:
- low-level shared types, constants, and small utilities

Build early:
- yes

Keep small:
- yes

### `app`
Purpose:
- top-level runtime lifecycle
- coordinates init, frame stages, shutdown

Build early:
- yes

### `platform`
Purpose:
- OS-facing utilities that should not leak everywhere

Examples:
- timers
- file/path helpers
- compiler/platform macros
- input/window glue if abstracted at this layer

Build early:
- yes

### `log`
Purpose:
- runtime visibility, diagnostics, and early error tracing

Build early:
- yes

### `render`
Purpose:
- engine-owned rendering interface and backend boundary

Rule:
- gameplay should not talk directly to Raylib

Build early:
- yes, as a bootstrap layer

### `network`
Purpose:
- transport, connection state, snapshots/messages, session flow

Build early:
- yes, because REAP is coop-first

### `physics`
Purpose:
- movement, traces, collision, projectile motion

Build early:
- partially

Start with:
- player movement and simple collision

### `ecs` or custom composition runtime
Purpose:
- manage gameplay entities and systems

Build early:
- no, not before the simple loop proves the need

### `assets`
Purpose:
- load and manage runtime asset data

Build early:
- lightly

Start with:
- the minimum runtime loading needed for graybox and early authored content

## Tool subsystems

### Map toolchain
Includes:
- BSP inspection
- entity lump inspection
- later: map compiler/decompiler only if needed

Recommended order:
1. load BSP in runtime
2. inspect/debug BSP
3. only then consider custom compile/decompile tools

### Model toolchain
Includes:
- raw import strategy
- custom runtime format
- model compiler
- model decompiler/debug inspector

Recommended order:
1. use raw/intermediate content path first
2. design runtime format second
3. compiler/decompiler third

### Packaging toolchain
Includes:
- archive format
- pack/unpack tools
- validation

Recommended order:
- later, after runtime asset loading pressure exists

## Placement rule

Before adding a new file, ask:

- is this runtime-generic or REAP-specific?
- does it belong in `rengine`, `rgame`, or `tools`?
- is it needed now, or is it being invented early?

If the answer is unclear, resolve that before writing code.
