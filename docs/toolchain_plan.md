# REAP Toolchain Plan

REAP’s toolchain should follow the runtime, not lead it.

That means:
- build runtime consumption first
- then build the offline pipeline that supports it

## Maps and BSP

Target:
- authored arenas
- entity metadata
- collision-ready world representation
- visibility-ready world representation

Recommended order:
1. learn and load BSP at runtime
2. parse the entity lump
3. use BSP for collision and visibility queries
4. build debug inspection tools
5. only then consider compiler/decompiler work if it is truly needed

Important rule:
- runtime BSP support comes before custom map compiler ambitions

## Models

Target:
- runtime model loading
- later custom `.rmdl` format
- later compiler/decompiler tooling

Recommended order:
1. get visible content on screen using the simplest viable path
2. define the runtime model requirements
3. design `.rmdl`
4. build runtime `.rmdl` loader
5. build model compiler
6. build decompiler/inspector if useful

## Textures and materials

Target:
- predictable runtime texture loading
- material definition files
- later atlas/packing tools

Recommended order:
1. simple direct texture loading
2. material file conventions
3. texture conversion/mip work
4. atlas tools only when they reduce pain

## Scripts

Target:
- `game.bin` bytecode generated from the REAP script path

Recommended order:
1. `rvm` runtime
2. assembler
3. game script bytecode
4. later language compiler
5. debug symbol support

## Archives / packaging

Target:
- packaged shipping asset archives

Recommended order:
1. direct loose-file runtime loading
2. define archive format only once asset pressure exists
3. build create/list/extract tool

## Tooling rule

Do not build a full toolchain because it sounds impressive.

Build the specific tool when:
- the runtime path exists
- the manual workflow is painful
- the tool will clearly save future development time
