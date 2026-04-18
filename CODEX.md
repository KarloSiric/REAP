# REAP - CODEX.md

## Project identity

REAP is a 3D arena survival FPS built from scratch with modern C++20 in a low-magic, C-style architecture.

The intention is to learn by building the game and only the engine layers that the game genuinely needs.

## Working style

- Explain substantial work before doing it
- Prefer small, reviewable changes
- Use snippets and file-by-file guidance when implementation starts
- Keep the user involved in architectural decisions
- Do not sprint ahead into large unseen engine builds

## Technical constraints

- C++20
- Data-oriented design
- No classical OOP as the main architecture
- No inheritance trees as the default composition tool
- No framework-driven engine design
- Explicit memory, ownership, and module boundaries

## Module philosophy

- Small modules
- Clear prefixes
- Narrow headers
- Minimal hidden behavior
- Favor directness over abstraction layers

## External dependencies

Planned dependencies:

- Raylib
- Flecs
- GLM

Do not assume these are present until they are actually added under `thirdparty/` or wired through the build.

## Quake-derived source policy

- Treat Quake III and related projects as references first
- Reimplement ideas rather than copying source by default
- Any direct reuse or adaptation must be intentional, documented, and license-aware
- Avoid mixing imported code into original REAP modules without clear provenance notes

## Immediate goal

Establish a professional repository foundation, then begin the smallest possible runnable application:

- build setup
- window
- loop
- input
- camera
- graybox arena

