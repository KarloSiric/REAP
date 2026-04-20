# REAP Development Phases

This is the detailed build order for REAP.

The rule is simple:
- each phase must leave the project in a more runnable state
- do not build deep later-phase systems before earlier runtime pressure exists

## Phase 0 - Foundation

Build:
- basic types
- app lifecycle skeleton
- logging
- platform scaffold
- docs/process system

Exit when:
- the project builds
- the foundation is documented

## Phase 1 - Runtime Bootstrap

Build:
- finish platform integration
- build convenience script
- first renderer interface
- Raylib bootstrap backend
- visible window and frame loop

Exit when:
- the project runs visibly

## Phase 2 - Command and Config Backbone

Build:
- command system backend
- cvar system backend
- cfg execution/loading
- prepare for later console UI

Exit when:
- runtime commands can be registered and executed
- cfg files can drive startup/runtime configuration

## Phase 3 - Local 3D Graybox

Build:
- camera
- input integration
- player movement
- one graybox arena
- debug visuals

Exit when:
- the player can move around a 3D space comfortably

## Phase 4 - Honest Runtime Split

Build:
- clearer client/server/runtime ownership
- low-level network groundwork
- session model

Exit when:
- the multiplayer architecture is no longer only theoretical

## Phase 5 - First Combat Loop

Build:
- one enemy
- one weapon
- basic damage/death
- one wave loop
- minimal HUD

Exit when:
- REAP starts to feel like a game, not just a runtime

## Phase 6 - BSP Runtime

Build:
- BSP loading
- entity lump parsing
- collision queries
- runtime debug support

Exit when:
- authored arenas can replace pure graybox assumptions

## Phase 7 - VM and Game Script Path

Build:
- `rvm` runtime
- assembler
- engine-side VM bridge
- gameplay scripts running through the VM path

Exit when:
- gameplay starts moving into the intended script/runtime split

## Phase 8 - Asset Formats and Tools

Build:
- runtime model format path
- model compiler/decompiler
- texture pipeline
- pak/archive tools

Exit when:
- authored content has a defined production pipeline

## Phase 9 - Product Growth

Build:
- more enemies
- more maps
- better menus/config
- performance work
- stability work

Exit when:
- the game is stable and content-complete enough to feel real

## Solo-developer rule

At any moment:
- one active phase
- one active subsystem
- one or two active files

That is how a project this large stays sane.
