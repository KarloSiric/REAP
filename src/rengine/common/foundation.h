#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

/**
 * @brief Converts a preprocessor token into a string literal.
 */
#define REAP_STRINGIFY( x ) #x

/**
 * @brief Expands a preprocessor token before stringifying it.
 */
#define REAP_TOSTRING( x ) REAP_STRINGIFY( x )

/**
 * @brief Expands to the current source file and line as a string literal.
 */
#define REAP_FILE_LINE __FILE__ ":" REAP_TOSTRING( __LINE__ )

namespace reap::rengine 
{

/**
 * @brief Fixed-width signed integer aliases used throughout the engine.
 */
using i8            = std::int8_t;
using i16           = std::int16_t;
using i32           = std::int32_t;
using i64           = std::int64_t;

/**
 * @brief Fixed-width unsigned integer aliases used throughout the engine.
 */
using u8            = std::uint8_t;
using u16           = std::uint16_t;
using u32           = std::uint32_t;
using u64           = std::uint64_t;

/**
 * @brief Floating-point aliases used throughout the engine.
 */
using f32           = float;
using f64           = double;

/**
 * @brief Unsigned size type alias used for memory and container sizes.
 */
using usize         = std::size_t;

/**
 * @brief Common identifier aliases used by runtime systems.
 */
using frame_index_t = u64;
using entity_id_t   = u32;

/**
 * @brief Sentinel values used for invalid runtime identifiers.
 */
constexpr frame_index_t INVALID_FRAME_INDEX = std::numeric_limits<frame_index_t>::max();
constexpr entity_id_t INVALID_ENTITY_ID     = std::numeric_limits<entity_id_t>::max();

/**
 * @brief Common numeric constants shared by runtime systems.
 */
constexpr f32 PI_F       = 3.14159265358979323846f;
constexpr f32 TAU_F      = 6.28318530717958647692f;
constexpr f32 DEG2RAD_F  = PI_F / 180.0f;
constexpr f32 RAD2DEG_F  = 180.0f / PI_F;
constexpr f32 EPSILON_F  = 1.0e-6f;
constexpr f32 INFINITY_F = std::numeric_limits<f32>::infinity();

static_assert( sizeof( i8 )  == 1, "i8 must be 1 byte" );
static_assert( sizeof( i16 ) == 2, "i16 must be 2 bytes" );
static_assert( sizeof( i32 ) == 4, "i32 must be 4 bytes" );
static_assert( sizeof( i64 ) == 8, "i64 must be 8 bytes" );

static_assert( sizeof( u8 )  == 1, "u8 must be 1 byte" );
static_assert( sizeof( u16 ) == 2, "u16 must be 2 bytes" );
static_assert( sizeof( u32 ) == 4, "u32 must be 4 bytes" );
static_assert( sizeof( u64 ) == 8, "u64 must be 8 bytes" );

} // namespace reap::engine
