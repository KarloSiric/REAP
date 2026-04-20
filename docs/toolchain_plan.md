# REAP Toolchain Plan

This file describes the intended content and offline pipeline strategy for REAP.

The rule is simple:

- runtime needs come first
- offline tools follow real pressure from runtime/content workflows

## Maps

### Goal

Use authored 3D arenas with gameplay metadata, collision support, and enough visibility into the format to debug runtime issues confidently.

### Recommended order

1. Use an existing editor workflow first.
2. Load BSP maps at runtime.
3. Parse entity data for spawns, pickups, wave triggers, and metadata.
4. Add runtime debug visualization.
5. Add map inspection/decompile utilities if they help iteration.
6. Only build a custom compiler if external tooling becomes a real blocker.

### Why

Writing a correct map compiler is substantial work.  
A loader and inspection path teach the runtime side sooner and get gameplay on screen faster.

## Models

### Goal

Move from temporary/raw content loading to a predictable runtime-ready model format with explicit control over mesh data, materials, and later animation.

### Recommended order

1. Start with the simplest import path that gets visible content on screen.
2. Define runtime requirements for a custom model format.
3. Design the format on paper.
4. Write runtime loader.
5. Write model compiler.
6. Add decompiler or inspector tool if it improves debugging and pipeline trust.

### Why

The format should be designed around actual runtime needs, not invented too early.

## Materials and textures

Start simple:
- texture references
- material names
- minimal render properties

Delay:
- advanced material graphs
- heavy editor UX

## Packaging

Archive/package formats should arrive after:
- runtime asset loading exists
- enough assets exist to justify packaging
- iteration pain is real

## Validation tooling

Validation tools are worth writing when:
- bad assets waste runtime debugging time
- multiple formats start interacting
- content production becomes repeatable

## Scope guardrails

Build now:
- runtime-friendly loading path
- visibility/debuggability

Delay:
- full custom authoring stack
- compiler/decompiler for every format
- packaging polish before content pressure exists
