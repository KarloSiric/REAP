# REAP Architecture Notes

## Guiding Principle

REAP should grow outward from a playable shooter, not inward from a speculative engine.

That means the architecture starts with the smallest runnable slice and only expands when the game loop proves a need.

## Early System Layers

The first implementation layers should be:

1. Application bootstrap
2. Platform and input wrapper
3. Camera and player movement
4. Graybox rendering
5. Minimal gameplay loop

Only after that should the project grow into:

6. ECS integration
7. richer gameplay state
8. asset pipeline tools
9. BSP map loading
10. custom formats and scripting

## Initial Runtime Shape

The first app should remain simple:

- one executable
- one game loop
- one local player
- one test arena
- no networking
- no VM
- no asset compiler dependency

## Long-Term Runtime Shape

Once the project matures, the codebase can be organized into a few clear layers:

- `app`: startup, shutdown, frame loop
- `platform`: file access, timers, input, OS glue
- `render`: drawing and frame presentation
- `game`: rules, waves, enemies, weapons, pickups
- `ecs`: composition and systems
- `physics`: movement, traces, projectiles
- `assets`: loading and runtime asset management
- `tools`: offline compilers and packers

## Design Guardrails

- The game loop should stay understandable to a single reader
- Serialization and custom formats should arrive late, not first
- Tooling should support the game, not lead it
- Networking remains a post-vertical-slice concern

