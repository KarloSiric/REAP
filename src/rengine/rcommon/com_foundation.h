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

namespace reap::rengine::rcommon
{

/**
 * @brief Fixed-width signed integer aliases used throughout the engine.
 */
using com_i8  = std::int8_t;
using com_i16 = std::int16_t;
using com_i32 = std::int32_t;
using com_i64 = std::int64_t;

using i8  = com_i8;
using i16 = com_i16;
using i32 = com_i32;
using i64 = com_i64;

/**
 * @brief Fixed-width unsigned integer aliases used throughout the engine.
 */
using com_u8  = std::uint8_t;
using com_u16 = std::uint16_t;
using com_u32 = std::uint32_t;
using com_u64 = std::uint64_t;

using u8  = com_u8;
using u16 = com_u16;
using u32 = com_u32;
using u64 = com_u64;

/**
 * @brief Floating-point aliases used throughout the engine.
 */
using com_f32 = float;
using com_f64 = double;

using f32 = com_f32;
using f64 = com_f64;

/**
 * @brief Unsigned size type alias used for memory and container sizes.
 */
using com_usize = std::size_t;

using usize = com_usize;

/**
 * @brief Common identifier aliases used by runtime systems.
 */
using com_frame_index_t = com_u64;
using com_entity_id_t = com_u32;

using frame_index_t = com_frame_index_t;
using entity_id_t = com_entity_id_t;

/**
 * @brief Sentinel values used for invalid runtime identifiers.
 */
constexpr com_frame_index_t COM_INVALID_FRAME_INDEX = std::numeric_limits<com_frame_index_t>::max();
constexpr com_entity_id_t COM_INVALID_ENTITY_ID = std::numeric_limits<com_entity_id_t>::max();

constexpr frame_index_t INVALID_FRAME_INDEX = COM_INVALID_FRAME_INDEX;
constexpr entity_id_t INVALID_ENTITY_ID = COM_INVALID_ENTITY_ID;

/**
 * @brief Common numeric constants shared by runtime systems.
 */
constexpr com_f32 COM_PI_F = 3.14159265358979323846f;
constexpr com_f32 COM_TAU_F = 6.28318530717958647692f;
constexpr com_f32 COM_DEG2RAD_F = COM_PI_F / 180.0f;
constexpr com_f32 COM_RAD2DEG_F = 180.0f / COM_PI_F;
constexpr com_f32 COM_EPSILON_F = 1.0e-6f;
constexpr com_f32 COM_INFINITY_F = std::numeric_limits<com_f32>::infinity();

constexpr f32 PI_F = COM_PI_F;
constexpr f32 TAU_F = COM_TAU_F;
constexpr f32 DEG2RAD_F = COM_DEG2RAD_F;
constexpr f32 RAD2DEG_F = COM_RAD2DEG_F;
constexpr f32 EPSILON_F = COM_EPSILON_F;
constexpr f32 INFINITY_F = COM_INFINITY_F;

static_assert( sizeof( com_i8 ) == 1, "com_i8 must be 1 byte" );
static_assert( sizeof( com_i16 ) == 2, "com_i16 must be 2 bytes" );
static_assert( sizeof( com_i32 ) == 4, "com_i32 must be 4 bytes" );
static_assert( sizeof( com_i64 ) == 8, "com_i64 must be 8 bytes" );

static_assert( sizeof( com_u8 ) == 1, "com_u8 must be 1 byte" );
static_assert( sizeof( com_u16 ) == 2, "com_u16 must be 2 bytes" );
static_assert( sizeof( com_u32 ) == 4, "com_u32 must be 4 bytes" );
static_assert( sizeof( com_u64 ) == 8, "com_u64 must be 8 bytes" );

} // namespace reap::rengine
