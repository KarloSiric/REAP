# REAP Documentation Hub

This document is the starting point for navigating REAP as a long-horizon engine, game, and tools project.

## What each document is for

- [current_status.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/current_status.md)
  - The single source of truth for where development currently is.
  - Read this first when resuming work after a break.
- [roadmap.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/roadmap.md)
  - The full development sequence from bootstrap to Steam-ready release.
  - Defines what should happen now, later, and much later.
- [subsystems.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/subsystems.md)
  - Explains the purpose and boundaries of each major runtime and tool subsystem.
  - Use this when deciding where code should live.
- [toolchain_plan.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/toolchain_plan.md)
  - Explains asset pipeline direction for maps, models, materials, archives, and offline tools.
  - Use this before building content formats or compilers.
- [architecture.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/architecture.md)
  - High-level runtime architecture and dependency boundaries.
- [coding_style.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/coding_style.md)
  - Coding rules, naming, and engine style constraints.
- [build_guide.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/build_guide.md)
  - How to configure and build the repository.
- [reference_policy.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/reference_policy.md)
  - Rules for studying and re-deriving ideas from Quake-era sources.

## Long-lived project memory

- [../CHANGELOG.md](/Users/karlosiric/Documents/MyProjects/REAP/CHANGELOG.md)
  - Milestone and release-facing change log.
- [devlog/2026-04.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/devlog/2026-04.md)
  - Daily engineering notes, risks, and exact next steps.
- [adr/0001-coop-first-listen-server-architecture.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/adr/0001-coop-first-listen-server-architecture.md)
  - The first locked architecture decision record.

## Resume workflow

When resuming work after time away:

1. Read [current_status.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/current_status.md).
2. Check the latest entry in [devlog/2026-04.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/devlog/2026-04.md).
3. Confirm the active milestone in [roadmap.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/roadmap.md).
4. Open [subsystems.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/subsystems.md) before creating a new module.
5. Update `current_status`, `devlog`, and `CHANGELOG` whenever milestone state changes materially.
