# REAP - CLAUDE.md

## What this project is

REAP is a from-scratch 3D arena survival FPS with fast movement, wave combat, and minimal UI.

The codebase is being built in C++20, but in a C-style and data-oriented way.

## Language and architecture rules

- Use C++20
- Prefer structs and free functions over class-heavy designs
- Avoid inheritance-driven architecture
- Avoid virtual dispatch unless a concrete need is proven
- Keep ownership explicit
- Favor simple data flow over clever abstractions
- Use module prefixes instead of deep object hierarchies

## Project priorities

- Build the playable loop first
- Graybox before polish
- Movement feel before content scale
- One good arena and one good combat loop before big systems
- Engine features must justify themselves through gameplay needs

## Quake III reference rules

- Quake III is a reference, not a code dump
- Study ideas, architecture, and patterns first
- Do not import source wholesale
- If any code is adapted from Quake-derived projects, preserve provenance and review licensing before merge

## Collaboration rules for this repository

- Do not silently implement broad features without discussion
- Keep changes small and explain file purpose clearly
- When coding, prefer snippets and file-by-file progress
- If there are multiple valid directions, surface the tradeoffs before locking one in

## Planned stack

- C++20
- CMake
- Raylib
- Flecs
- GLM

## Current phase

Pre-production bootstrap.

The repository currently contains documentation, licensing, and workflow setup only.

