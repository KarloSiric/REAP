# REAP Changelog

All notable changes to REAP are tracked here.

## [0.1.0] - 2026-04-25

### Added
- Packed common error surface in `rcommon` for cross-subsystem error reporting.
- Common formatted print/error helpers:
  - `com_printf`
  - `com_dprintf`
  - `com_errorf`
- Logging runtime with:
  - level filtering
  - channel masking
  - console output
  - optional file sink
- Host/runtime lifecycle scaffolding with explicit frame stages.
- Renderer lifecycle contract with error-coded init, begin-frame, render, and end-frame entry points.
- Command subsystem with:
  - fixed registry
  - command lookup
  - argument parsing
  - callback execution
- Cvar subsystem with:
  - fixed registry
  - typed cached values
  - mutation flags
  - readonly/cheat protection hooks
- Cfg subsystem with:
  - file loading
  - single-line execution
  - `exec`
  - `set`
  - `seta`
  - fallback command dispatch
- New documentation anchors:
  - [docs/API_REFERENCE.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/API_REFERENCE.md)
  - [docs/API_IMPLEMENTATION.md](/Users/karlosiric/Documents/MyProjects/REAP/docs/API_IMPLEMENTATION.md)

### Changed
- Documentation now reflects the current project split more accurately:
  - `REAP` is the project/game
  - `Fuse` is the native engine runtime being built inside it
- Runtime direction is now explicitly documented as:
  - `VFS`
  - `SDL3`
  - `OpenGL`
  - `Quake III BSP`
  - later `rmdl` / `rpk` / small engine-owned editor tooling
- Active roadmap and phase docs no longer describe a `Raylib` bootstrap path.

### Fixed
- Project status docs now match the actual codebase more closely.
- Documentation navigation now includes API-oriented references instead of only architecture/process notes.

## [0.1.0] - 2026-04-20

### Added
- Initial CMake-based project scaffold and runtime module layout.
- Core runtime scaffolding:
  - foundational types
  - app lifecycle
  - logging
  - early platform helpers
- Baseline documentation and project process files.
