# REAP Changelog

All notable changes to REAP are tracked here.

## [Unreleased]

### Added
- Documentation overhaul aligned to the original Quake-style REAP structure PDF.
- New documentation anchors:
  - `docs/project_structure.md`
  - `docs/development_phases.md`
- Expanded project memory/docs navigation for long-horizon solo development.

### Changed
- README and docs now follow the intended long-term engine/game/tools layout:
  - `src/common`
  - `src/renderer`
  - `src/server`
  - `src/client`
  - `src/network`
  - `src/bsp`
  - `src/physics`
  - `src/audio`
  - `src/ecs`
  - `src/vm`
  - `src/platform`
  - `rvm`
  - `game`
  - `tools`
  - `data`
  - `config`
- Documentation direction shifted from generic engine bootstrap notes to the specific intended REAP architecture.

### Fixed
- Public runtime documentation now better matches the intended subsystem boundaries and build order.

## [0.1.0] - 2026-04-20

### Added
- Initial CMake-based project scaffold and runtime module layout.
- Core runtime scaffolding:
  - foundational types
  - app lifecycle
  - logging
  - early platform helpers
- Baseline documentation and project process files.
