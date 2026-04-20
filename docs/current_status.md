# REAP Current Status

## Project state

REAP is in early foundation stage.

The intended long-term structure is now locked to the Quake-style REAP layout documented in [project_structure.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/project_structure.md), even though the current repo still only contains the first runtime scaffolding under `src/rengine/`.

## What exists now

- foundational types
- application lifecycle scaffold
- logging scaffold
- early platform scaffold
- documentation/process system

## What is done-for-now

- `foundation`
  - type aliases
  - numeric constants
  - sentinel values
- `app`
  - init/begin-frame/update/render/end-frame/shutdown skeleton
- `log`
  - runtime state
  - level/channel filtering
  - record-based emit path
- `platform`
  - platform/compiler detection
  - basename helper
  - monotonic time helper

## Active milestone

`M1 - Finish Foundation, Begin Runtime Bootstrap`

This milestone is complete only when:

- platform is fully integrated into runtime code
- logger macro layer is cleaned up
- build convenience script exists
- first render/bootstrap interface exists
- a windowed frame loop is possible to build next without reworking the foundation

## Immediate next tasks

1. finish `platform` integration and small cleanup
2. clean logger macros and header consistency
3. add `build.sh` as a thin wrapper around the real build flow
4. define the first renderer interface
5. bootstrap Raylib behind that interface

## Explicitly not active yet

- BSP runtime
- VM runtime
- command/cvar/console family
- client/server split
- ECS runtime
- tool executables
- custom formats

These are all planned, but they are not the current task.

## Resume rule

If work pauses, resume from this file first.  
Do not restart architecture design from scratch unless this file and the corresponding docs are intentionally changed.
