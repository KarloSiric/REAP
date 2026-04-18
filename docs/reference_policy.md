# Quake Reference Policy

## Purpose

REAP may learn from Quake III Arena and related open-source descendants, but that does not mean the codebase should absorb those sources wholesale.

This document defines the working boundary for safe and disciplined use of Quake-derived material.

## Allowed

- Study gameplay systems and architecture
- Study movement logic and simulation ideas
- Study command buffer, console, snapshot, and BSP concepts
- Write fresh notes from that study
- Reimplement ideas in original REAP code

## Not Allowed By Default

- Copy entire modules into REAP just because they already exist
- Bulk-port headers and source files with rename-only edits
- Blend imported code into original REAP files without provenance
- Assume license compatibility is solved by intent alone

## If Direct Reuse Ever Happens

Before any direct code adaptation or import:

1. Identify the exact source project and file
2. Record the original license and notices
3. Decide whether adaptation is actually necessary
4. Keep imported material isolated and documented
5. Mark changed files clearly

## Preferred Default

The preferred default for REAP is:

- understand the system
- write it ourselves
- document the inspiration
- keep the codebase clean

