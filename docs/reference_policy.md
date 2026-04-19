# Quake Reference Policy

## Purpose
We may study historical references (especially Quake-era design), but REAP code must stay original and legally clean.

## Allowed
- Study mechanics, architecture, and architecture-level tradeoffs.
- Reimplement ideas from scratch.
- Create notes that capture what was studied and what was adapted.

## Not Allowed by default
- Copy-paste imports into REAP modules.
- Rename-only ports.
- Unattributed or unlicensed integration.

## If direct reuse ever happens
Before adapting external source code:
1. Record exact source project/file.
2. Record license and compatibility details.
3. Justify the adaptation.
4. Keep adapted code isolated.
5. Add explicit provenance comments to changed modules.

## Implementation Discipline
- Understand first.
- Re-derive second.
- Document decisions in `docs/adr/`.
