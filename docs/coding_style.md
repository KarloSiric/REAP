# REAP Coding Style

## Core Style
REAP uses C++20, with an explicit C-style, data-oriented engine style.

## Rules
- Use `struct` plus free functions.
- Keep ownership and lifetime explicit at module boundaries.
- Avoid class hierarchies as the primary architecture style.
- Avoid inheritance and virtual dispatch by default.
- Prefer explicit data flow over hidden behavior.
- Prefer simple modules over framework-like monoliths.

## Naming
- Types: `snake_case_t`.
- Functions: `module_verb_noun`.
- Constants and macros: `SCREAMING_SNAKE_CASE`.
- Files: lowercase module names where useful.

## C++ Features To Prefer
- `std::array`, `std::span`, and `std::string_view`.
- `std::vector` when dynamic ownership is explicit.
- Scoped ownership objects (`std::unique_ptr`, `std::shared_ptr`) only where object ownership semantics are obvious.
- RAII for narrow resource ownership boundaries.

## C++ Features To Use Sparingly
- Templates beyond small utility cases.
- Exceptions.
- RTTI.
- Operator-heavy APIs.
- Heavy metaprogramming.
- Indirection layers that hide cost or intent.

## Engine Mindset
- Make data layout visible.
- Make ownership visible.
- Make frame-to-frame behavior easy to trace.
- Optimize for comprehension and iteration speed first.

## Logging and Erroring Contracts
- Keep logs channeled and leveled.
- Keep public logging API minimal and explicit.
- Treat `record_t` as the canonical event payload, and keep output functions as sinks.
