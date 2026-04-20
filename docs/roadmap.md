# REAP Roadmap

This roadmap defines the build order for REAP as three connected efforts:

- `rengine` - reusable runtime
- `rgame` - REAP gameplay
- `tools` - offline pipeline and authoring support

The goal is not to build every system immediately.  
The goal is to build them in the order that keeps the project understandable, playable, and expandable.

## Milestone 0 - Foundation

Purpose:
- establish repository shape, build system, coding rules, and runtime conventions

Includes:
- CMake bootstrap
- foundational types
- app lifecycle contract
- logging contract
- docs, ADR, devlog, changelog

Exit criteria:
- repository builds cleanly
- app lifecycle exists in code
- logging is available early in runtime

## Milestone 1 - Runtime Bootstrap

Purpose:
- create the minimum engine spine needed to run a real windowed application

Includes:
- `platform` module
- `render` module interface
- Raylib bootstrap backend
- input sampling
- timing and frame delta integration

Exit criteria:
- window opens
- frame loop runs
- clear screen or graybox draw works
- startup and shutdown are visible in logs

## Milestone 2 - Local Graybox Shooter Slice

Purpose:
- prove movement and basic shooter feel before deeper systems

Includes:
- camera
- player movement
- collision placeholder or simple world collision
- one graybox arena
- debug draw and frame stats

Exit criteria:
- player can move in 3D space comfortably
- frame loop, input, and rendering feel stable enough to build on

## Milestone 3 - Coop Runtime Skeleton

Purpose:
- establish honest multiplayer foundations before deep gameplay expansion

Includes:
- session state model
- host/client runtime separation
- connection flow for local host plus remote client
- replicated match shell

Exit criteria:
- host can run a session
- at least one client can connect
- both sides observe shared high-level session state

## Milestone 4 - First Combat Loop

Purpose:
- get the first real REAP loop running

Includes:
- one enemy type
- one weapon
- damage, death, and respawn rules
- one wave loop
- minimal HUD

Exit criteria:
- enemy spawn, damage, death, and wave advance are visible and repeatable
- the loop works in local and early coop cases

## Milestone 5 - Gameplay Expansion

Purpose:
- turn the prototype loop into a reusable game foundation

Includes:
- more enemies
- pickups
- scoring
- wave scaling
- class system planning and first implementation if justified

Exit criteria:
- the arena shooter loop has enough variation for real playtesting

## Milestone 6 - Map Runtime and BSP Loader

Purpose:
- replace graybox-only world assumptions with a real map runtime

Includes:
- BSP file study and runtime loader
- entity lump parsing
- collision queries against map geometry
- debug visualization tools

Exit criteria:
- a compiled BSP arena loads, renders, and supports gameplay placement/query needs

Important scope rule:
- runtime BSP loading comes before writing our own map compiler
- use existing content tools first if they get us gameplay faster

## Milestone 7 - Asset Runtime and Custom Formats

Purpose:
- move from temporary/raw asset loading toward controlled runtime data

Includes:
- custom model format design
- model runtime loader
- materials and texture references
- archive/package format planning

Exit criteria:
- at least one authored model goes through a defined compile-and-load path

Important scope rule:
- runtime consumption comes before building every tool around it

## Milestone 8 - Toolchain Expansion

Purpose:
- build the offline pipeline only once runtime pressure justifies it

Includes:
- model compiler/decompiler
- package tool
- asset validators
- map inspection/debug tools

Exit criteria:
- content iteration becomes faster and more reliable than raw/manual workflows

## Milestone 9 - Advanced Systems

Purpose:
- add systems that matter once the core loop is proven

Includes:
- ECS integration or custom composition system
- richer AI state
- scripting VM if still justified
- save/config systems
- stronger debug tooling

Exit criteria:
- advanced systems clearly reduce engine/game complexity rather than increase it

## Milestone 10 - Steam-Ready Product Pass

Purpose:
- turn the project from technical milestone into release-quality game

Includes:
- host/join flow
- settings and binds
- content completeness
- performance pass
- disconnect/recovery handling
- usability and onboarding polish

Exit criteria:
- repeated 4-player playtests are stable and product-like

## Scope guardrails

Build now:
- runtime spine
- graybox gameplay
- honest multiplayer shape

Delay until justified:
- dedicated servers
- fully custom compiler stack
- custom renderer backend replacement
- VM scripting
- extensive content tools

## How to use this roadmap

- `roadmap.md` decides milestone order
- `current_status.md` says which milestone is active now
- `devlog` records what happened today
- `CHANGELOG` records what changed at milestone level
