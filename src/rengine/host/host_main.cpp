/*======================================================================
   File: host_main.cpp
   Project: REAP
   Author: ksiric <email@example.com>
   Created: 2026-04-19 01:23:58
   Last Modified by: ksiric
   Last Modified: 2026-05-04 01:06:08
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

namespace {

void host_cmd_echo( rc::u32 argc, char **argv ) {
    for ( rc::u32 i = 1u; i < argc; ++i ) {
        rc::com_printf( "%s%s", argv[i], ( i + 1u < argc ) ? " " : "\n" );
    }
    if ( argc <= 1u ) {
        rc::com_printf( "\n" );
    }
}

void host_cmd_version( rc::u32 argc, char **argv ) {
    ( void )argc;
    ( void )argv;

    const rc::com_version_t &engine_version = rc::COM_ENGINE_INFO.version;
    const rc::com_version_t &game_version = rc::COM_GAME_INFO.version;

    rc::com_printf(
        "%s %u.%u.%u.%u | %s %u.%u.%u.%u\n",
        rc::COM_ENGINE_INFO.name,
        engine_version.major,
        engine_version.minor,
        engine_version.patch,
        engine_version.build,
        rc::COM_GAME_INFO.name,
        game_version.major,
        game_version.minor,
        game_version.patch,
        game_version.build );
}

} // namespace

namespace reap::rengine::host {
 
void host_prepare_state_for_init( host_state_t &host_state ) {
    host_state.stage = host_stage_t::INITIALIZING;
    host_state.running = false;
    host_state.has_focus = true;
    host_state.frame = {};
}    

host_error_code_t host_init_core_engine_systems( host_state_t &host_state ) {
    sys::sys_init_info_t sys_info {
        .argc = host_state.config.argc,
        .argv = host_state.config.argv,
        .app_name = rcommon::COM_GAME_INFO.internal_name,
        .organization_name = rcommon::COM_GAME_INFO.organization_name
    };
    
    // @NOTE: we will first be initializing the sys subsystems
    const auto sys_result = sys::sys_init( sys_info );
    if ( sys_result != sys::sys_error_code_t::OK ) {
        rcommon::com_errorf( sys_error_code( sys_result ) , "host_init: sys_init failed: %s", sys::sys_error_desc( sys_result ) );
        
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
    }
    
    const auto log_result = log::log_init();
    if ( log_result != log::log_error_code_t::OK ) {
        rcommon::com_errorf( log::log_error_code( log_result ), "host_init: log_init failed: %s", log::log_error_desc( log_result ) );
        
        // @NOTE: Shutting things down here before we return and exit.
        sys::sys_shutdown();
        
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
    }
    
    const auto fs_result = fs::fs_init();
    if( fs_result != fs::fs_error_code_t::OK ) {
        rcommon::com_errorf( fs_error_code( fs_result ), "host_init: fs_init failed: %s", fs::fs_error_desc( fs_result ) );
        log::log_shutdown();       
        sys::sys_shutdown();
        
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
    }
    // @NOTE: CMD SYSTEM INIT
    const auto cmd_result = cmd::cmd_init();
    
    if ( cmd_result != cmd::cmd_error_code_t::OK ) 
    {
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
    
    if ( cvar_result != cvar::cvar_error_code_t::OK ) 
    {
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
    if ( cfg_result != cfg::cfg_error_code_t::OK ) 
    {
        rcommon::com_errorf( cfg_error_code( cfg_result ), "host_init: cfg_init failed: %s", cfg::cfg_error_desc( cfg_result ) );
        
        cvar::cvar_shutdown();
        cmd::cmd_shutdown();       
        fs::fs_shutdown();
        log::log_shutdown();
        sys::sys_shutdown();
        
        host_state.running = false;
        host_state.stage = host_stage_t::SHUTDOWN;
        return host_error_code_t::ERR_INITIALIZING;
    }
         
    return host_error_code_t::OK;      
}

host_error_code_t host_mount_file_system( void ) {
    const sys::sys_paths_t &paths = sys::sys_paths();

    const auto base_mount_result = fs::fs_mount_directory(
        "",
        paths.base_path,
        fs::FS_MOUNT_READ_ONLY,
        0u );

    if ( base_mount_result != fs::fs_error_code_t::OK ) {
        rc::com_errorf(
            fs::fs_error_code( base_mount_result ),
            "host_init: filesystem base mount failed: %s",
            fs::fs_error_desc( base_mount_result ) );
        return host_error_code_t::ERR_INITIALIZING;
    }

    const auto write_path_result = fs::fs_set_write_path( paths.user_path );
    if ( write_path_result != fs::fs_error_code_t::OK ) {
        rc::com_errorf(
            fs::fs_error_code( write_path_result ),
            "host_init: filesystem write path failed: %s",
            fs::fs_error_desc( write_path_result ) );
        return host_error_code_t::ERR_INITIALIZING;
    }

    return host_error_code_t::OK;
}

host_error_code_t host_register_builtin_cvars( void ) {
    struct builtin_cvar_t {
        const char *name;
        const char *default_value;
        cvar::cvar_flags_t flags;
    };

    const builtin_cvar_t builtin_cvars[] = {
        { "r_width", "1280", cvar::CVAR_ARCHIVE },
        { "r_height", "720", cvar::CVAR_ARCHIVE },
        { "r_fullscreen", "0", cvar::CVAR_ARCHIVE },
        { "r_vsync", "1", cvar::CVAR_ARCHIVE },
        { "r_fov", "90", cvar::CVAR_ARCHIVE },
        { "r_near", "0.1", cvar::CVAR_ARCHIVE },
        { "r_far", "1000", cvar::CVAR_ARCHIVE },
        
        { "host_target_fps", "60", cvar::CVAR_ARCHIVE },
        { "host_timescale", "0.25", cvar::CVAR_ARCHIVE },
        { "host_max_delta_time", "0.25", cvar::CVAR_ARCHIVE },
        
        { "developer", "1", cvar::CVAR_ARCHIVE },
        { "con_show", "0", cvar::CVAR_ARCHIVE },
        
        { "sys_app_name", rc::COM_GAME_INFO.internal_name, cvar::CVAR_READONLY },
    };

    for ( const builtin_cvar_t &builtin_cvar : builtin_cvars ) {
        const auto result = cvar::cvar_register(
            builtin_cvar.name,
            builtin_cvar.default_value,
            builtin_cvar.flags );

        if ( result != cvar::cvar_error_code_t::OK ) {
            rc::com_errorf(
                cvar::cvar_error_code( result ),
                "host_init: failed to register cvar '%s': %s",
                builtin_cvar.name,
                cvar::cvar_error_desc( result ) );
            return host_error_code_t::ERR_INITIALIZING;
        }
    }

    return host_error_code_t::OK;
}

host_error_code_t host_register_builtin_commands( void ) {
    struct builtin_command_t {
        const char *name;
        cmd::cmd_fn_t callback;
        const char *description;
    };

    const builtin_command_t builtin_commands[] = {
        { "echo", host_cmd_echo, "prints text to the engine console" },
        { "version", host_cmd_version, "prints engine and game version information" }
    };

    for ( const builtin_command_t &builtin_command : builtin_commands ) {
        const auto result = cmd::cmd_register(
            builtin_command.name,
            builtin_command.callback,
            builtin_command.description );

        if ( result != cmd::cmd_error_code_t::OK ) {
            rc::com_errorf(
                cmd::cmd_error_code( result ),
                "host_init: failed to register command '%s': %s",
                builtin_command.name,
                cmd::cmd_error_desc( result ) );
            return host_error_code_t::ERR_INITIALIZING;
        }
    }

    return host_error_code_t::OK;
}

host_error_code_t host_load_startup_config( void ) {
    const auto default_result = cfg::cfg_load_file( "config/default.cfg", false );
    if ( default_result != cfg::cfg_error_code_t::OK ) {
        rc::com_errorf(
            cfg::cfg_error_code( default_result ),
            "host_init: default config load failed: %s",
            cfg::cfg_error_desc( default_result ) );
        return host_error_code_t::ERR_INITIALIZING;
    }

    const auto autoexec_result = cfg::cfg_load_autoexec();
    if ( autoexec_result != cfg::cfg_error_code_t::OK ) {
        rc::com_errorf(
            cfg::cfg_error_code( autoexec_result ),
            "host_init: autoexec config load failed: %s",
            cfg::cfg_error_desc( autoexec_result ) );
        return host_error_code_t::ERR_INITIALIZING;
    }

    return host_error_code_t::OK;
}

host_error_code_t host_apply_cvars_to_config( host_state_t &host_state ) {
    host::window_config_t &window_config = host_state.config.window_config;

    const rcommon::u32 width = cvar::cvar_get_int( "r_width" );
    const rcommon::u32 height = cvar::cvar_get_int( "r_height" );
    const rcommon::u32 target_fps = cvar::cvar_get_int( "host_target_fps" );

    if ( width != 0u ) {
        window_config.viewport.width = width;
    }

    if ( height != 0u ) {
        window_config.viewport.height = height;
    }

    if ( target_fps != 0u ) {
        window_config.target_fps = target_fps;
    }

    window_config.fullscreen = cvar::cvar_get_bool( "r_fullscreen" );
    window_config.vsync = cvar::cvar_get_bool( "r_vsync" );

    return host_error_code_t::OK;
}

host_error_code_t host_init_renderer( host_state_t &host_state ) {
    const auto render_result = render::r_init( host_state.config.window_config );
    if ( render_result != render::r_error_code_t::OK ) {
        rc::com_errorf(
            render::r_error_code( render_result ),
            "host_init: renderer initialization failed." );
        return host_error_code_t::ERR_INITIALIZING;
    }

    return host_error_code_t::OK;
}

host_error_code_t host_finish_init( host_state_t &host_state ) {
    host_state.running = true;
    host_state.stage = host_stage_t::RUNNING;

    const rcommon::com_f64 now = sys::sys_time_now_seconds();

    host_state.frame.current_time_seconds = now;
    host_state.frame.previous_time_seconds = now;

    return host_error_code_t::OK;
}

void host_requet_shutdown( host_state_t &host_state )
{
    if ( host_state.stage == host_stage_t::SHUTDOWN ) {
        return ;
    }
    
    host_state.running = false;
    host_state.stage = host_stage_t::SHUTTINGDOWN;       
    
    return ;
}

host_error_code_t host_init( host_state_t &host_state ) {
    // @NOTE: We are preparing things for making the engine wire up  properly.
    host_error_code_t result{};
    
    host_prepare_state_for_init( host_state );
    
    result = host_init_core_engine_systems( host_state );
    if ( result != host_error_code_t::OK ) {
        return result;
    }
    
    result = host_mount_file_system(); 
    if ( result != host_error_code_t::OK ) {
        host_shutdown( host_state );
        return result;          
    }
    
    result = host_register_builtin_cvars();
    if ( result != host_error_code_t::OK ) {
        host_shutdown( host_state );
        return result;
    }
    
    result = host_register_builtin_commands();
    if ( result != host_error_code_t::OK ) {
        host_shutdown( host_state );
        return result;
    }

    result = host_load_startup_config();
    if ( result != host_error_code_t::OK ) {
        host_shutdown( host_state );
        return result;
    }

    result = host_apply_cvars_to_config( host_state );
    if ( result != host_error_code_t::OK ) {
        host_shutdown( host_state );
        return result;
    }

    result = host_init_renderer( host_state );
    if ( result != host_error_code_t::OK ) {
        host_shutdown( host_state );
        return result;
    }

    result = host_finish_init( host_state );
    if ( result != host_error_code_t::OK ) {
        host_shutdown( host_state );
        return result;
    }  
    
    return result;
}

void host_shutdown( host_state_t &host_state ) {
	host_state.running = false;
	host_state.stage = host_stage_t::SHUTDOWN;
    
    // @NOTE(karlo): Added shutdown of the entire host system
    
    render::r_shutdown();
    cfg::cfg_shutdown();
    cvar::cvar_shutdown();
    cmd::cmd_shutdown();
    fs::fs_shutdown();
    log::log_shutdown();
    sys::sys_shutdown();
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
