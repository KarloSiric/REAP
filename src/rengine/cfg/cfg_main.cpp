/*======================================================================
   File: cfg_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-24 15:56:36
   Last Modified by: ksiric
   Last Modified: 2026-04-27 17:36:23
   ---------------------------------------------------------------------
   Description:

   ---------------------------------------------------------------------
   License:
   Company:
   Version: 0.1.0
 ======================================================================
																	   */
#include "rengine/cfg/cfg_main.h"
#include "rengine/cmd/cmd_main.h"
#include "rengine/cvar/cvar_main.h"

#include <cctype>
#include <cstdio>
#include <cstring>

namespace reap::rengine::cfg {

struct cfg_runtime_state_t {
	bool initialized{ false };
};

cfg_runtime_state_t g_cfg_runtime_state;

constexpr const char *CFG_DEFAULT_PATH = "config/default.cfg";
constexpr const char *CFG_AUTOEXEC_PATH = "config/autoexec.cfg";

cfg_error_code_t cfg_init() {
	if ( g_cfg_runtime_state.initialized ) {
		return cfg_error_code_t::ERR_IS_INIT;
	}
	g_cfg_runtime_state = {};
	g_cfg_runtime_state.initialized = true;
	return cfg_error_code_t::OK;
}

cfg_error_code_t cfg_shutdown() {
	if ( !g_cfg_runtime_state.initialized ) {
		return cfg_error_code_t::ERR_NOT_INIT;
	}
	g_cfg_runtime_state = {};
	return cfg_error_code_t::OK;
}

cfg_error_code_t cfg_load_file( const char *path, const bool required ) {
	if ( path == nullptr || path[0] == '\0' ) {
		return cfg_error_code_t::ERR_INVALID_PATH;
	}
	if ( !g_cfg_runtime_state.initialized ) {
		return cfg_error_code_t::ERR_NOT_INIT;
	}
	std::FILE *cfg_file = std::fopen( path, "r" );
	if ( cfg_file == nullptr ) {
		return required ? cfg_error_code_t::ERR_FILE_OPEN_FAILED : cfg_error_code_t::OK;
	}
	cfg_error_code_t result = cfg_error_code_t::OK;
	char line[CFG_MAX_LINE_LENGTH]{};

	while ( std::fgets( line, static_cast<int>( sizeof( line ) ), cfg_file ) != nullptr ) {
		const cfg_error_code_t line_result = cfg_execute_line( line );
		if ( line_result != cfg_error_code_t::OK && result == cfg_error_code_t::OK ) {
			result = line_result;
		}
	}
	if ( std::fclose( cfg_file ) != 0 ) {
		return cfg_error_code_t::ERR_IO_ERROR;
	}
	return result;
}

cfg_error_code_t cfg_load_default() {
	if ( !g_cfg_runtime_state.initialized ) {
		return cfg_error_code_t::ERR_NOT_INIT;
	}
	return cfg_load_file( CFG_DEFAULT_PATH, true );
}

cfg_error_code_t cfg_load_autoexec() {
	if ( !g_cfg_runtime_state.initialized ) {
		return cfg_error_code_t::ERR_NOT_INIT;
	}
	return cfg_load_file( CFG_AUTOEXEC_PATH, false );
}

cfg_error_code_t cfg_execute_line( const char *command_line ) {
	if ( !g_cfg_runtime_state.initialized ) {
		return cfg_error_code_t::ERR_INVALID_LINE;
	}
	char line[CFG_MAX_LINE_LENGTH]{};
	std::strncpy( line, command_line, sizeof( line ) - 1 );

	// @NOTE: now we continue working, so we first trim whitespaces
	//  - exec <file>    -> cfg_load_file
	//  - set / seta     -> cvar::cvar_set
	//  - otherwise      -> cmd::cmd_execute
	// return cfg_error_code_t codes consistently

	char *cursor = line;
	while ( std::isspace( static_cast<unsigned char>( *cursor ) ) ) {
		++cursor;
	}
	if ( *cursor == '\0' || *cursor == '\n' || *cursor == '\r' ) {
		return cfg_error_code_t::OK;
	}
	bool in_quotes = false;
	for ( char *it = cursor; *it != '\0'; ++it ) {
		// @NOTE: we skipping these comments here, usual procedure like in the cfg_load_file func
		if ( *it == '"' ) {
			in_quotes = !in_quotes;
		}
		if ( !in_quotes && it[0] == '/' && it[1] == '/' ) {
			*it = '\0';
			break;
		}
		if ( !in_quotes && *it == '#' ) {
			*it = '\0';
			break;
		}
	}
	char *end = cursor + std::strlen( cursor );
	while ( end > cursor && std::isspace( static_cast<unsigned char>( end[-1] ) ) ) {
		--end;
	}
	*end = '\0';
	if ( *cursor == '\0' ) {
		return cfg_error_code_t::OK;
	}
	char command[32]{};
	rcommon::u32 i = 0;
	while ( *cursor != '\0' && !std::isspace( static_cast<unsigned char>( *cursor ) ) && ( i + 1u ) < sizeof( command ) ) {
		command[i++] = *cursor++;
	}
	command[i] = '\0';
	if ( std::strcmp( command, "exec" ) == 0 ) {
		while ( std::isspace( static_cast<unsigned char>( *cursor ) ) ) {
			++cursor;
		}
		if ( *cursor == '\0' ) {
			return cfg_error_code_t::ERR_PARSE_FAILED;
		}
		char exec_path[CFG_MAX_PATH_LENGTH]{};
		i = 0;
		if ( *cursor == '"' ) {
			++cursor;
			while ( cursor[i] != '\0' && cursor[i] != '"' && ( i + 1u ) < sizeof( exec_path ) ) {
				exec_path[i] = cursor[i];
				++i;
			}
			if ( cursor[i] != '"' ) {
				return cfg_error_code_t::ERR_PARSE_FAILED;
			}
		} else {
			while ( cursor[i] != '\0' && !std::isspace( static_cast<unsigned char>( cursor[i] ) ) && ( i + 1u ) < sizeof( exec_path ) ) {
				exec_path[i] = cursor[i];
				++i;
			}
		}
		exec_path[i] = '\0';
		return cfg_load_file( exec_path, false );
	}
	if ( std::strcmp( command, "set" ) == 0 || std::strcmp( command, "seta" ) == 0 ) {
		while ( std::isspace( static_cast<unsigned char>( *cursor ) ) ) {
			++cursor;
		}
		if ( *cursor == '\0' ) {
			return cfg_error_code_t::ERR_PARSE_FAILED;
		}
		char cvar_name[256]{};
		i = 0;
		while ( *cursor != '\0' && !std::isspace( static_cast<unsigned char>( *cursor ) ) && ( i + 1u ) < sizeof( cvar_name ) ) {
			cvar_name[i++] = *cursor++;
		}
		cvar_name[i] = '\0';

		if ( cvar_name[0] == '\0' ) {
			return cfg_error_code_t::ERR_PARSE_FAILED;
		}
		while ( std::isspace( static_cast<unsigned char>( *cursor ) ) ) {
			++cursor;
		}
		if ( *cursor == '\0' ) {
			return cfg_error_code_t::ERR_PARSE_FAILED;
		}
		char cvar_value[CFG_MAX_LINE_LENGTH]{};
		i = 0;
		if ( *cursor == '"' ) {
			++cursor;
			while ( cursor[i] != '\0' && cursor[i] != '"' && ( i + 1u ) < sizeof( cvar_value ) ) {
				cvar_value[i] = cursor[i];
				++i;
			}
			if ( cursor[i] != '"' ) {
				return cfg_error_code_t::ERR_PARSE_FAILED;
			}
		} else {
			while ( cursor[i] != '\0' && !std::isspace( static_cast<unsigned char>( cursor[i] ) ) && ( i + 1u ) < sizeof( cvar_value ) ) {
				cvar_value[i] = cursor[i];
				++i;
			}
		}
		cvar_value[i] = '\0';
		if ( cvar_value[0] == '\0' ) {
			return cfg_error_code_t::ERR_PARSE_FAILED;
		}
		if ( cvar::cvar_set( cvar_name, cvar_value ) != cvar::cvar_error_code_t::OK ) {
			return cfg_error_code_t::ERR_PARSE_FAILED;
		}
		return cfg_error_code_t::OK;
	}
	if ( cmd::cmd_execute( line ) != cmd::cmd_error_code_t::OK ) {
		return cfg_error_code_t::ERR_COMMAND_FAILED;
	}
	return cfg_error_code_t::OK;
}

} // namespace reap::rengine::cfg
