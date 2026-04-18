# Build Guide

## Current State

The repository is not buildable yet.

This document exists to define the intended build direction before source files are added.

## Planned Toolchain

- CMake
- A C++20-capable compiler
  - Apple Clang
  - Clang
  - GCC
  - MSVC

## Planned External Dependencies

- Raylib
- Flecs
- GLM

These are expected to be added intentionally under `thirdparty/` or wired in through a clearly documented dependency strategy.

## Build Philosophy

- A fresh clone should be able to configure the project with minimal manual steps
- Dependencies should not be hidden behind undocumented machine-local setup
- Build outputs should stay out of source control
- Debug builds should be the default during early development

## First Build Milestone

The first successful build should produce a tiny desktop executable that:

- opens a window
- processes input
- runs a frame loop
- draws a graybox test arena

