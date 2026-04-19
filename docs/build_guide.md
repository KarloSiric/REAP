# Build Guide

## Objective
Keep project startup reproducible across machines and preserve a clear path from source to playable build.

## Tooling
- CMake 3.20+
- C++20 toolchain (Apple Clang, Clang, GCC, or MSVC)
- Git

## Quick build
```bash
cmake -S . -B build
cmake --build build
```

Run:
```bash
./build/bin/reap
```
(Path may vary by platform and generator.)

## Current Minimum Goal
The first runnable executable should:
- Initialize app lifecycle.
- Run frame update loop.
- Render a graybox scene.
- Exit cleanly.
- Keep logging and config paths visible from runtime.

## Dependency Strategy (v1)
- Raylib and Flecs remain planned.
- GLM remains planned for math where needed.
- Third-party code can be vendored under `thirdparty/`.
- Build scripts should degrade gracefully if optional dependencies are absent.

## Build Hygiene
- Build outputs in `build/` only.
- Do not commit binaries or generated artifacts.
- Keep documentation and source independent from platform-specific machine state.
