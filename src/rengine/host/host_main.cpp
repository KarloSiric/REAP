/*======================================================================
   File: host_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 01:23:58
   Last Modified by: ksiric
   Last Modified: 2026-05-02 20:54:46
   ---------------------------------------------------------------------
   Description:

   ---------------------------------------------------------------------
   License:
   Company:
   Version: 0.1.0
 ======================================================================
																	   */
#include "rengine/cmd/cmd_main.h"
#include "rengine/cvar/cvar_main.h"
#include "rengine/rcommon/com_print.h"
#include "rengine/host/host_main.h"
#include "rengine/cfg/cfg_main.h"
#include "rengine/fs/fs_main.h"
#include "rengine/log/log_main.h"
#include "rengine/render/r_main.h"
#include "rengine/sys/sys_platform.h"

namespace rc = reap::rengine::rcommon;

namespace reap::rengine::host {

host_error_code_t host_init( host_state_t &host_state ) {
	host_state.stage = host_stage_t::INITIALIZING;
	host_state.running = false;
	host_state.has_focus = true;
	host_state.frame = {};

	const rcommon::com_f64 now = sys::sys_time_now_seconds();

	host_state.frame.current_time_seconds = now;
	host_state.frame.previous_time_seconds = now;

	sys::sys_init_info_t sys_info{
		.argc = host_state.config.argc,
		.argv = host_state.config.argv,
		.app_name = rcommon::COM_GAME_INFO.internal_name,
		.organization_name = rcommon::COM_GAME_INFO.organization_name
	};

	// @NOTE: SYS SYSTEM INIT
	const auto sys_result = sys::sys_init( sys_info );

	if ( sys_result != sys::sys_error_code_t::OK ) {
		rc::com_errorf( sys::sys_error_code( sys_result ), "host_init: sys_init failed: %s", sys::sys_error_desc( sys_result ) );

		host_state.running = false;
		host_state.stage = host_stage_t::SHUTDOWN;
		return host_error_code_t::ERR_INITIALIZING;
	}

	// @NOTE: LOG SYSTEM INIT
	const auto log_result = log::log_init();

	if ( log_result != log::log_error_code_t::OK ) {
		rcommon::com_errorf( log::log_error_code( log_result ), "host_init: log_init failed: %s", log::log_error_desc( log_result ) );

		sys::sys_shutdown();

		host_state.running = false;
		host_state.stage = host_stage_t::SHUTDOWN;
		return host_error_code_t::ERR_INITIALIZING;
	}

	// @NOTE: FS SYSTEM INIT
	const auto fs_result = fs::fs_init();

	if ( fs_result != fs::fs_error_code_t::OK ) {
		rcommon::com_errorf( fs::fs_error_code( fs_result ), "host_init: fs_init failed: %s", fs::fs_error_desc( fs_result ) );

		log::log_shutdown();
		sys::sys_shutdown();

        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
	}

	// @NOTE: Wiring up all of the paths for the FS
	const sys::sys_paths_t &paths = sys::sys_paths();

	const auto base_mount_result = fs::fs_mount_directory(
		"",
		paths.base_path,
		fs::FS_MOUNT_READ_ONLY,
		0u );

	if ( base_mount_result != fs::fs_error_code_t::OK ) {
        rc::com_errorf(
            fs::fs_error_code( base_mount_result ), "host_init: filesystem base mount failed: %s",fs::fs_error_desc( base_mount_result ) );
        
        fs::fs_shutdown();
        log::log_shutdown();
        sys::sys_shutdown();
        
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
	}
    
    // @NOTE: Wiring up the write paths for the FS
    const auto write_path_result = fs::fs_set_write_path( paths.user_path );
    
    if ( write_path_result != fs::fs_error_code_t::OK ) {
        rc::com_errorf(
            fs::fs_error_code( write_path_result ), "host_init: filesystem write path failed: %s",fs::fs_error_desc( write_path_result ) );
        
        fs::fs_shutdown();
        log::log_shutdown();
        sys::sys_shutdown();
        
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
    }
    
    // @NOTE: CMD SYSTEM INIT
    const auto cmd_result = cmd::cmd_init();
    
    if ( cmd_result != cmd::cmd_error_code_t::OK ) {
        rcommon::com_errorf( cmd_error_code( cmd_result ), "host_init: cmd_init failed: %s", cmd_error_desc( cmd_result ) );
        
        fs::fs_shutdown();
        log::log_shutdown();
        sys::sys_shutdown();
        
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
    }
    
    // @NOTE: CVAR SYSTEM INIT
    const auto cvar_result = cvar::cvar_init();
    
    if ( cvar_result != cvar::cvar_error_code_t::OK ) {
        rcommon::com_errorf( cvar_error_code( cvar_result ), "host_init: cvar_init failed: %s", cvar::cvar_error_desc( cvar_result ) );
    
        cmd::cmd_shutdown();       
        fs::fs_shutdown();
        log::log_shutdown();
        sys::sys_shutdown();
        
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
    }
    
    // @NOTE: CFG SYSTEM INIT
    const auto cfg_result = cfg::cfg_init();
    // @TODO(karlo - 2.5.2026):Tommorow continue working on this system.      
    if ( cfg_result != cfg::cfg_error_code_t::OK ) {
        rcommon::com_errorf( cfg_error_code(  ), const char *message, ...)
    }   
       
       
       
       
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

	// @NOTE: RENDER SYSTEM INIT
	const auto render_result = render::r_init( host_state.config.window_config );

	if ( render_result != render::r_error_code_t::OK ) {
		rc::com_errorf(
			render::r_error_code( render_result ),
			"host_init: renderer initialization failed." );

		host_state.running = false;
		host_state.stage = host_stage_t::SHUTDOWN;
		return host_error_code_t::ERR_INITIALIZING;
	}

	host_state.running = true;
	host_state.stage = host_stage_t::RUNNING;

	return host_error_code_t::OK;
}

void host_shutdown( host_state_t &host_state ) {
	host_state.running = false;
	host_state.stage = host_stage_t::SHUTDOWN;

	// @TODO: Also has to shutdown all the other subsystems in the engine,
	//        the host has to be able to orchestrate things and
	//        deal with the proper shutdown and cleaning of everything
	//        else.

	render::r_shutdown();
}

void host_begin_frame( host_state_t &host_state ) {
	if ( host_state.stage == host_stage_t::SHUTDOWN ) {
		return;
	}

	frame_t &frame = host_state.frame;

	frame.previous_time_seconds = frame.current_time_seconds;
	frame.current_time_seconds = sys::sys_time_now_seconds();

	frame.delta_time_seconds = static_cast<rcommon::f32>( frame.current_time_seconds - frame.previous_time_seconds );

	frame.real_time_seconds += frame.delta_time_seconds;

	if ( host_state.stage == host_stage_t::RUNNING ) {
		frame.simulation_time_seconds += frame.delta_time_seconds;
	}

	frame.index++;

	const auto render_result = render::r_begin_frame( frame.delta_time_seconds );

	if ( render_result != render::r_error_code_t::OK ) {
		rc::com_errorf(
			render::r_error_code( render_result ),
			"host_begin_frame: renderer begin-frame failed." );

		host_state.running = false;
		host_state.stage = host_stage_t::SHUTTINGDOWN;
		return;
	}
}

void host_update( host_state_t &host_state ) {
	if ( host_state.stage != host_stage_t::RUNNING ) {
		return;
	}

	if ( !host_state.running ) {
		return;
	}

	// @TODO: Update the host stage, and handle input, AI, gameplay etc.
}

void host_render( host_state_t &host_state ) {
	if ( host_state.stage != host_stage_t::RUNNING || !host_state.running ) {
		return;
	}

	// @TODO: Render the host stage, and handle rendering of the scene, UI, etc.
	const auto render_result = render::r_render_frame();

	if ( render_result != render::r_error_code_t::OK ) {
		rc::com_errorf(
			render::r_error_code( render_result ),
			"host_render: renderer frame submission failed." );

		host_state.running = false;
		host_state.stage = host_stage_t::SHUTTINGDOWN;
	}
}

void host_end_frame( host_state_t &host_state ) {
	if ( host_state.stage == host_stage_t::SHUTDOWN ) {
		return;
	}

	const auto render_result = render::r_render_end();

	if ( render_result != render::r_error_code_t::OK ) {
		rc::com_errorf(
			render::r_error_code( render_result ),
			"host_end_frame: renderer end-frame failed." );

		host_state.running = false;
		host_state.stage = host_stage_t::SHUTDOWN;
		return;
	}

	if ( host_state.stage == host_stage_t::SHUTTINGDOWN ) {
		host_state.running = false;
		host_state.stage = host_stage_t::SHUTDOWN;
	}
}

bool host_is_running( host_state_t &host_state ) {
	return host_state.running && ( host_state.stage != host_stage_t::SHUTTINGDOWN && host_state.stage != host_stage_t::SHUTDOWN );
}

} // namespace reap::rengine::host
