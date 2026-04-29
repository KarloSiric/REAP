/*======================================================================
   File: sys_platform_win32.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-27 17:32:49
   Last Modified by: ksiric
   Last Modified: 2026-04-28 23:38:04
   ---------------------------------------------------------------------
   Description:

   ---------------------------------------------------------------------
   License:
   Company:
   Version: 0.1.0
 ======================================================================
																	   */
#include "rengine/sys/sys_platform_internal.h"

#include <system_error>
#include <filesystem>

#if REAP_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace reap::rengine::sys {

sys_error_code_t sys_platform_build_paths( const sys_init_info_t &info_init, sys_paths_t &out_paths ) {
	out_paths = {};

	std::error_code ec{};

	const std::filesystem::path working_dir = std::filesystem::current_path( ec );
	if ( ec ) {
		return sys_error_code_t::ERR_PATH_QUERY_FAILED;
	}
}

void sys_platform_sleep_milliseconds( const rcommon::u64 milliseconds ) {
	Sleep( milliseconds );
}

} // namespace reap::rengine::sys

#endif
