# REAP Project Structure

This is the intended long-term REAP repository structure.

`REAP` is the project/game. `Fuse` is the engine runtime inside it.

## Target layout

```text
reap/
├── README.md
├── Makefile or build wrapper
├── src/
│   ├── common/
│   ├── renderer/
│   ├── server/
│   ├── client/
│   ├── network/
│   ├── bsp/
│   ├── physics/
│   ├── audio/
│   ├── ecs/
│   ├── vm/
│   └── platform/
├── rvm/
├── game/
├── tools/
├── data/
├── config/
├── thirdparty/
└── docs/
```

## Meaning of each top-level directory

- `src`
  - native Fuse engine runtime
- `rvm`
  - standalone REAP Virtual Machine project
- `game`
  - gameplay scripts intended to run on the VM
- `tools`
  - standalone asset and pipeline tools
- `data`
  - runtime assets
- `config`
  - default cfg files
- `thirdparty`
  - vendored external libraries
- `docs`
  - architecture and process documentation

## Important note about the current repo

The current source still lives under `src/rengine/` because the project is still in early foundation stage.

From this point forward, the docs and long-term structure should assume the target shape above, and future migrations should move code toward it instead of inventing a different architecture each time.

## Key architectural message

This project is not just one executable.

It is a family of connected systems:
- native engine runtime
- scripting VM
- gameplay layer
- tools pipeline
- asset/data tree

That is why the structure must be explicit.
