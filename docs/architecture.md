# REAP Architecture Notes

## Guiding Principle

REAP grows outward from a runnable cooperative survival loop, not from speculative systems.

The architecture is built around the smallest valid v1 that people can play, then expanded when the loop proves the need.

## Delivery Priorities

The current v1 target is:

1. Foundation and frame lifecycle (`app`, `common`, `log`)
2. Platform and input wrapper (`platform`)
3. Host/client application runtime (`app` + `network` shaping)
4. Graybox rendering and movement loop
5. One enemy, one weapon, one wave state, shared HUD baseline
6. Host-authoritative match sync path (listen-server)
7. Menu/settings, session restart, and stability pass
8. Gameplay expansion (enemy variety, pickups, classes, content tuning)

Only after those milestones should the project grow into:

1. ECS integration
2. richer gameplay state
3. asset pipeline tools
4. BSP map loading and map tooling
5. custom formats and scripting

## Initial Runtime Shape

The first shipped target should remain intentionally constrained:

- one executable
- one game loop
- one local player with network scaffolding ready
- one test arena
- host/client role-aware runtime
- no VM or full toolchain dependency in v1
- no dedicated server until v1 stability gates are passed

## Long-Term Runtime Shape

Once the project matures, the codebase can be organized into a few clear layers:

- `rengine`: startup, shutdown, frame loop, platform/runtime services, logging, asset interfaces
- `platform`: file access, timers, input, OS glue
- `render`: drawing and frame presentation
- `network`: host/client transport and session flow
- `ecs`: composition and systems
- `physics`: movement, traces, projectiles
- `rgame`: rules, waves, enemies, weapons, pickups
- `assets`: loading and runtime asset management
- `tools`: offline compilers and packers

## Design Guardrails

- The game loop should stay understandable to a single reader
- Tooling should support the game, not lead it
- Networking shapes simulation ownership from v1 onward
- Serialization and custom formats should arrive late, after stable runtime loop needs

## Runtime Ownership Rule

- `rengine` provides runtime services and stays independent of game rules.
- `rgame` owns all gameplay semantics and depends on `rengine`.
- `tools` may use shared low-level utilities, but never pull gameplay runtime logic.

## Engineering Rule

- If a subsystem does not improve the playable loop, it is deferred.
- If it improves visibility, stability, or debugging for an existing loop, it is implemented now.
