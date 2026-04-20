# Quake / id Reference Policy

REAP is structurally inspired by Quake 3 / id Software style architecture.

That inspiration is allowed and intentional.

## What is allowed

- studying subsystem boundaries
- studying gameplay/runtime architecture
- studying patterns like:
  - command buffer
  - cvars
  - snapshots
  - BSP handling
  - VM boundaries
  - client/server split
- re-deriving systems in original REAP code

## What is not allowed by default

- copying source files wholesale
- rename-only ports
- blending copied code into original modules without provenance
- assuming license concerns disappear because the architecture is similar

## Working rule

We can be heavily inspired by the shape and discipline of Quake-style engines.

We still write REAP’s implementation ourselves unless a later deliberate decision is documented and license-reviewed.
