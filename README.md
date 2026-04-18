# REAP

REAP is a from-scratch 3D arena survival FPS with fast movement, wave combat, and a strong Quake-era action feel.

The project is being built in modern C++20 with a C-style, data-oriented architecture. The goal is not to assemble a game out of engine features first. The goal is to learn by building the game, the engine layers it truly needs, and the supporting tools in the right order.

## Current Status

REAP is in pre-production bootstrap.

The repository currently contains project foundations only:

- licensing and source reference policy
- repository hygiene and workflow docs
- coding style and architecture notes
- no engine or gameplay code yet

## Project Goals

- Build a playable arena shooter vertical slice from scratch
- Learn engine architecture by implementing only what the game actually needs
- Keep the codebase explicit, understandable, and performant
- Favor iteration speed and clarity over premature feature sprawl
- Ship a graybox-first playable loop before building advanced tools

## Design Pillars

- Fast, aggressive first-person movement
- Minimal HUD and high combat readability
- Arena layouts that reward circulation, verticality, and pickup control
- Wave-based combat with room for solo play first and coop later
- Brutal, readable game feel before polish systems

## Technical Direction

- Language: C++20
- Style: C-style, data-oriented, low-magic C++
- Build system: CMake
- Planned libraries:
  - Raylib for windowing, input, rendering bootstrap, and basic audio
  - Flecs for ECS
  - GLM for math

These libraries are planned, not yet vendored into the repository.

## Engineering Principles

- No classical OOP architecture
- No inheritance trees as the core design tool
- No virtual-by-default abstractions
- Explicit ownership and lifetime
- Small modules with clear prefixes and boundaries
- Build the playable loop first, the tools second

## Quake III Reference Boundary

REAP may study Quake III Arena and related open-source descendants for architectural ideas, gameplay patterns, and historical reference.

REAP does not assume that the Quake III source can be copied wholesale into this codebase.

Project policy:

- Study systems and reimplement what we understand
- Keep REAP code original by default
- If any code is ever imported or adapted from Quake-derived sources, preserve notices, record provenance, and review license implications first
- Do not blend copied engine code into original modules casually

See [docs/reference_policy.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/reference_policy.md) for the working rules.

## Development Strategy

The project will be built in layers, with each phase producing something runnable:

1. Repo and tooling foundation
2. Window, input, camera, and graybox arena
3. Basic movement and feel iteration
4. One enemy, one weapon, one wave loop
5. HUD, pickups, game over, win condition
6. Broader engine systems only after the core loop is fun

## Planned Repository Shape

This is the intended structure once implementation begins:

```text
REAP/
├── CMakeLists.txt
├── README.md
├── CLAUDE.md
├── CODEX.md
├── docs/
├── src/
├── thirdparty/
├── tools/
├── data/
└── config/
```

## Workflow Rules

- Discuss substantial implementation before broad code changes
- Prefer file-by-file progress for learning-heavy work
- Keep snippets small and explain why each file exists
- Avoid overbuilding engine subsystems before the vertical slice proves the need

## Near-Term Next Step

The next milestone after this docs setup is to create the actual repo scaffolding for:

- `CMakeLists.txt`
- `src/`
- `thirdparty/`
- the first tiny application entry point

That first application should do only one thing well:

- open a window
- run a frame loop
- capture mouse input
- render a simple graybox arena

