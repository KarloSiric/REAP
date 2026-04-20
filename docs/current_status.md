# REAP Current Status

## Project state

REAP is in early bootstrap.  
The codebase currently has foundational runtime scaffolding and early documentation, but no gameplay loop, renderer, or platform abstraction yet.

## What exists now

- `rengine/common`
  - foundational engine types in place
- `rengine/app`
  - app lifecycle contract exists
- `rengine/log`
  - logger contract and first implementation pass exist
- docs baseline
  - architecture, style, build, reference policy, ADR, devlog, changelog

## What is considered done-for-now

- foundational type aliases and constants
- initial app lifecycle surface
- initial logging design:
  - config/runtime state
  - level/channel filtering
  - record-driven emit path
- baseline documentation system

These systems are not "finished forever," but they are complete enough to stop polishing and move forward.

## Active milestone

`M1 - Runtime Bootstrap and Platform Spine`

This milestone is complete only when:

- the app boots through a clean init/update/render/end-frame/shutdown path
- a platform module exists for timing and path/file helpers
- a render bootstrap exists behind an engine-owned interface
- a window opens and the frame loop runs visibly
- logging is wired into startup and shutdown

## Immediate next tasks

1. Add `rengine/platform` with:
   - time helpers
   - file/path helpers
   - platform/compiler detection utilities
2. Add `rengine/render` interface, not gameplay-facing Raylib calls directly.
3. Use Raylib as the first bootstrap backend behind engine-owned interfaces.
4. Wire `main.cpp` -> `app` -> platform/render/logger startup path.
5. Get one visible window and one clear frame loop on screen.

## Explicitly deferred right now

- custom model format implementation
- BSP loader implementation
- own map compiler/decompiler
- own model compiler/decompiler
- ECS integration
- advanced AI
- dedicated server
- scripting VM
- packaging/archive formats

These are intentionally deferred so the runtime spine is built first.

## Decision defaults for now

- language: C++20
- style: C-style, data-oriented, explicit ownership
- first renderer bootstrap: Raylib behind engine-owned abstraction
- first multiplayer shape: 4-player listen-server
- first game slice: one arena, one enemy, one weapon, one wave loop

## When to update this file

Update this file when:

- the active milestone changes
- "done-for-now" scope changes
- a deferred system becomes active
- the next five tasks materially change
