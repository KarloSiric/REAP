# REAP Subsystems

This file defines what the major REAP modules are supposed to do.

## `common`

Shared engine foundation used by both client and server style code.

Expected contents:
- engine bootstrap
- memory helpers
- command system
- cvar system
- console backend
- filesystem
- pak/archive reading
- logging
- string helpers
- math
- common types

This is the layer everything else stands on.

## `renderer`

Owns:
- frame begin/end
- world rendering
- BSP rendering
- model rendering
- materials
- shaders
- particles
- lightmaps
- sky
- debug draw

Rule:
- the rest of the engine should not call Raylib directly

## `server`

Owns:
- authoritative simulation
- client connection management
- snapshot generation
- receiving input
- sending world state
- game VM bridge on the authoritative side

## `client`

Owns:
- local input
- prediction
- interpolation
- view/camera
- client-side effects
- HUD
- scoreboard
- console UI
- menus

## `network`

Owns:
- socket-level communication
- packet framing
- reliable/unreliable channel logic
- serialization

Both client and server depend on this layer.

## `bsp`

Owns:
- BSP loading
- BSP format definitions
- traceline / tracebox
- PVS lookup
- entity lump parsing
- collision against brush geometry

## `physics`

Owns:
- player movement
- slide movement
- step movement
- air movement
- shared movement code used by both prediction and authoritative simulation

## `audio`

Owns:
- audio runtime startup/shutdown
- loading sounds
- mixing
- spatial sound
- music playback

## `ecs`

Owns:
- entity/component definitions
- system registration
- prefab setup
- query helpers

This is the replacement for a monolithic entity array.

## `vm`

Owns:
- loading the gameplay VM in the engine runtime
- trap bridge between VM and native engine code
- engine-side debugging of VM state

## `platform`

Owns:
- OS entry point details
- timing
- file/path wrappers where needed
- OS socket differences where needed
- crash/error/platform-specific behavior

This is the engine/OS seam.

## `rvm`

Standalone virtual machine project.

Owns:
- VM runtime
- memory model
- stack
- opcodes
- loader
- debugger
- assembler
- disassembler
- later language compiler

## `game`

Owns gameplay logic intended to run on the VM:
- players
- weapons
- projectiles
- combat
- enemies
- AI
- waves
- spawn logic
- items
- triggers
- rules

## `tools`

Owns offline content pipeline:
- model compiler/decompiler
- texture processing
- pak/archive creation and extraction
- asset build orchestration
