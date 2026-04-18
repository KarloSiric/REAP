# Coding Style

## Core Style

REAP uses C++20, but the coding style should remain close to clear, explicit C-style engine code.

## Rules

- Prefer `struct` plus free functions
- Avoid class hierarchies as the main design pattern
- Avoid inheritance unless there is a compelling, concrete need
- Avoid virtual dispatch by default
- Prefer explicit data flow over hidden behavior
- Prefer simple modules over framework-like subsystems

## Naming

- Types: `snake_case_t` where that style fits the engine layer
- Functions: `module_verb_noun`
- Constants and macros: `SCREAMING_SNAKE_CASE`
- Files: lowercase with module prefixes where useful

## C++ Features To Prefer

- `std::array`
- `std::vector`
- `std::span`
- `std::string_view`
- RAII for narrow ownership cases such as small wrappers

## C++ Features To Use Sparingly

- templates beyond small utility cases
- exceptions
- RTTI
- operator-heavy APIs
- metaprogramming
- smart abstraction layers that hide cost

## Engine Mindset

- make data layout visible
- make ownership visible
- make frame-to-frame behavior easy to trace
- optimize for comprehension and iteration speed first

