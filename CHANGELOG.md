# REAP Changelog

All notable changes to REAP are tracked here.

## [Unreleased]

### Added
- Baseline engineering docs for v1 direction (release notes, devlog, ADR, architecture, style, build guide, reference policy).
- Engine/game split formalization (rengine + rgame boundary) aligned to coop-first execution.
- Logging subsystem now has a record-driven emission path (`record_t`, filtering, formatted emit pipeline).
- Project navigation docs for long-horizon development:
  - docs hub
  - current status tracker
  - milestone roadmap
  - subsystem map
  - toolchain plan

### Changed
- Documentation and execution framing updated from prototype-first toward 4-player cooperative vertical slice.
- README now points to the documentation hub and current active milestone.

### Fixed
- None in this release window.

## [0.1.0] - 2026-04-20

### Added
- Initial CMake-based project scaffold and runtime module layout (`rengine/app`, `rengine/log`, `rengine/common`).
- Core logging interfaces and initial implementation:
  - `log_init`, `log_shutdown`, config and runtime state.
  - `log_level_enabled`, `log_channel_enabled`.
  - `log_emit`, `log_emitf`, `log_emitfv` path.
- Baseline documentation set (`docs/architecture.md`, `docs/coding_style.md`, `docs/build_guide.md`, `docs/reference_policy.md`).

### Changed
- Standardized direction on explicit C-style, data-oriented C++ engine implementation.

### Fixed
- Logging output model updated to avoid pointer-based temporary message lifetime issues by centralizing payload in record data.
