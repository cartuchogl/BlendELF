
elf_engine* elf_create_engine()
{
	elf_engine *engine;
	gfx_vertex_data *vertex_data;
	float *vertex_buffer;

	engine = (elf_engine*)malloc(sizeof(elf_engine));
	memset(engine, 0x0, sizeof(elf_engine));
	engine->obj_type = ELF_ENGINE;
	engine->obj_destr = elf_destroy_engine;

	engine->fps_timer = elf_create_timer();
	engine->fps_limit_timer = elf_create_timer();
	engine->time_sync_timer = elf_create_timer();

	elf_inc_ref((elf_object*)engine->fps_timer);
	elf_inc_ref((elf_object*)engine->fps_limit_timer);
	elf_inc_ref((elf_object*)engine->time_sync_timer);

	engine->free_run = ELF_TRUE;
	engine->fps_limit = 0;
	engine->speed = 1.0;
	engine->f10_exit = ELF_TRUE;

	engine->shadow_map_size = 1024;
	engine->shadow_map = gfx_create_2d_texture(1024, 1024, 0.0, GFX_CLAMP, GFX_LINEAR, GFX_DEPTH_COMPONENT, GFX_DEPTH_COMPONENT, GFX_UBYTE, NULL);
	engine->shadow_target = gfx_create_render_target(1024, 1024);
	gfx_set_render_target_depth_texture(engine->shadow_target, engine->shadow_map);
	engine->texture_anisotropy = 1.0;
	engine->occlusion_culling = ELF_FALSE;

	engine->lines = gfx_create_vertex_data(512, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
	gfx_inc_ref((gfx_object*)engine->lines);

	engine->sprite_vertex_array = gfx_create_vertex_array(GFX_FALSE);
	gfx_inc_ref((gfx_object*)engine->sprite_vertex_array);

	vertex_data = gfx_create_vertex_data(36, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);

	vertex_buffer = (float*)gfx_get_vertex_data_buffer(vertex_data);

	vertex_buffer[0] = -0.5;
	vertex_buffer[1] = 0.5;
	vertex_buffer[2] = 0.0;
	vertex_buffer[3] = -0.5;
	vertex_buffer[4] = -0.5;
	vertex_buffer[5] = 0.0;
	vertex_buffer[6] = 0.5;
	vertex_buffer[7] = -0.5;
	vertex_buffer[8] = 0.0;

	vertex_buffer[9] = -0.5;
	vertex_buffer[10] = 0.5;
	vertex_buffer[11] = 0.0;
	vertex_buffer[12] = 0.5;
	vertex_buffer[13] = -0.5;
	vertex_buffer[14] = 0.0;
	vertex_buffer[15] = 0.5;
	vertex_buffer[16] = 0.5;
	vertex_buffer[17] = 0.0;

	vertex_buffer[18] = 0.5;
	vertex_buffer[19] = 0.5;
	vertex_buffer[20] = 0.0;
	vertex_buffer[21] = 0.5;
	vertex_buffer[22] = -0.5;
	vertex_buffer[23] = 0.0;
	vertex_buffer[24] = -0.5;
	vertex_buffer[25] = -0.5;
	vertex_buffer[26] = 0.0;

	vertex_buffer[27] = 0.5;
	vertex_buffer[28] = 0.5;
	vertex_buffer[29] = 0.0;
	vertex_buffer[30] = -0.5;
	vertex_buffer[31] = -0.5;
	vertex_buffer[32] = 0.0;
	vertex_buffer[33] = -0.5;
	vertex_buffer[34] = 0.5;
	vertex_buffer[35] = 0.0;

	gfx_set_vertex_array_data(engine->sprite_vertex_array, GFX_VERTEX, vertex_data);

	vertex_data = gfx_create_vertex_data(24, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);

	vertex_buffer = (float*)gfx_get_vertex_data_buffer(vertex_data);

	vertex_buffer[0] = 0.0;
	vertex_buffer[1] = 1.0;
	vertex_buffer[2] = 0.0;
	vertex_buffer[3] = 0.0;
	vertex_buffer[4] = 1.0;
	vertex_buffer[5] = 0.0;

	vertex_buffer[6] = 0.0;
	vertex_buffer[7] = 1.0;
	vertex_buffer[8] = 1.0;
	vertex_buffer[9] = 0.0;
	vertex_buffer[10] = 1.0;
	vertex_buffer[11] = 1.0;

	vertex_buffer[12] = 0.0;
	vertex_buffer[13] = 1.0;
	vertex_buffer[14] = 0.0;
	vertex_buffer[15] = 0.0;
	vertex_buffer[16] = 1.0;
	vertex_buffer[17] = 0.0;

	vertex_buffer[18] = 0.0;
	vertex_buffer[19] = 1.0;
	vertex_buffer[20] = 1.0;
	vertex_buffer[21] = 0.0;
	vertex_buffer[22] = 1.0;
	vertex_buffer[23] = 1.0;

	gfx_set_vertex_array_data(engine->sprite_vertex_array, GFX_TEX_COORD, vertex_data);

	vertex_data = gfx_create_vertex_data(36, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);

	vertex_buffer = (float*)gfx_get_vertex_data_buffer(vertex_data);

	vertex_buffer[0] = 0.0;
	vertex_buffer[1] = 0.0;
	vertex_buffer[2] = 1.0;
	vertex_buffer[3] = 0.0;
	vertex_buffer[4] = 0.0;
	vertex_buffer[5] = 1.0;
	vertex_buffer[6] = 0.0;
	vertex_buffer[7] = 0.0;
	vertex_buffer[8] = 1.0;

	vertex_buffer[9] = 0.0;
	vertex_buffer[10] = 0.0;
	vertex_buffer[11] = 1.0;
	vertex_buffer[12] = 0.0;
	vertex_buffer[13] = 0.0;
	vertex_buffer[14] = 1.0;
	vertex_buffer[15] = 0.0;
	vertex_buffer[16] = 0.0;
	vertex_buffer[17] = 1.0;

	vertex_buffer[18] = 0.0;
	vertex_buffer[19] = 0.0;
	vertex_buffer[20] = -1.0;
	vertex_buffer[21] = 0.0;
	vertex_buffer[22] = 0.0;
	vertex_buffer[23] = -1.0;
	vertex_buffer[24] = 0.0;
	vertex_buffer[25] = 0.0;
	vertex_buffer[26] = -1.0;

	vertex_buffer[27] = 0.0;
	vertex_buffer[28] = 0.0;
	vertex_buffer[29] = -1.0;
	vertex_buffer[30] = 0.0;
	vertex_buffer[31] = 0.0;
	vertex_buffer[32] = -1.0;
	vertex_buffer[33] = 0.0;
	vertex_buffer[34] = 0.0;
	vertex_buffer[35] = -1.0;

	gfx_set_vertex_array_data(engine->sprite_vertex_array, GFX_NORMAL, vertex_data);

	elf_inc_obj(ELF_ENGINE);

	return engine;
}

void elf_destroy_engine(void *data)
{
	elf_engine *engine = (elf_engine*)data;

	gfx_dec_ref((gfx_object*)engine->lines);
	gfx_dec_ref((gfx_object*)engine->sprite_vertex_array);

	if(engine->scene) elf_dec_ref((elf_object*)engine->scene);
	if(engine->gui) elf_dec_ref((elf_object*)engine->gui);

	if(engine->post_process) elf_destroy_post_process(engine->post_process);
	gfx_destroy_render_target(engine->shadow_target);
	gfx_destroy_texture(engine->shadow_map);

	elf_dec_ref((elf_object*)engine->fps_timer);
	elf_dec_ref((elf_object*)engine->fps_limit_timer);
	elf_dec_ref((elf_object*)engine->time_sync_timer);

	free(engine);

	elf_dec_obj(ELF_ENGINE);
}

unsigned char elf_init_engine()
{
	if(eng)
	{
		elf_set_error(ELF_CANT_INITIALIZE, "error: can't initialize the engine twice!\n");
		return ELF_FALSE;
	}

	eng = elf_create_engine();
	if(!eng) return ELF_FALSE;
	elf_inc_ref((elf_object*)eng);

#ifdef ELF_WINDOWS
	GetCurrentDirectoryA(255, eng->cwd);
#else
	getcwd(eng->cwd, 255);
#endif

	return ELF_TRUE;
}

void elf_deinit_engine()
{
	if(!eng) return;

	elf_dec_ref((elf_object*)eng);
	eng = NULL;
}

unsigned char elf_init(int width, int height,
	const char *title, int multisamples, unsigned char fullscreen, const char *log)
{
	elf_init_general();
	elf_set_log_file_path(log);

	elf_start_log("BlendELF 0.9 Beta\n");

	if(!elf_init_context(width, height, title, multisamples, fullscreen)) return ELF_FALSE;
	if(!gfx_init())
	{
		elf_deinit_context();
		return ELF_FALSE;
	}
	elf_init_audio();
	elf_init_engine();
	elf_init_scripting();
	elf_init_networking();

	return ELF_TRUE;
}

unsigned char elf_init_with_config(const char *file_path)
{
	elf_config *config;

	elf_init_general();

	if(!(config = elf_read_config("config.txt")))
		config = elf_create_config();

	if(!elf_init(config->window_size[0], config->window_size[1], "BlendELF", config->multisamples, !config->fullscreen == ELF_FALSE, config->log))
	{
		elf_set_error(ELF_CANT_INITIALIZE, "error: could not initialize engine\n");
		elf_destroy_config(config);
		return ELF_FALSE;
	}

	elf_set_texture_compress(config->texture_compress);
	elf_set_texture_anisotropy(config->texture_anisotropy);
	elf_set_shadow_map_size(config->shadow_map_size);

	if(strlen(config->start) > 0) elf_load_scene(config->start);

	elf_destroy_config(config);

	return ELF_TRUE;
}

void elf_limit_engine_fps()
{
	if(eng->fps_limit > 0)
	{
		if(elf_get_elapsed_time(eng->fps_limit_timer) > 0.0)
		{
			while(elf_get_elapsed_time(eng->fps_limit_timer) < 1.0/(float)eng->fps_limit);
			elf_start_timer(eng->fps_limit_timer);
		}
		else
		{
			elf_start_timer(eng->fps_limit_timer);
		}
	}
}

void elf_update_engine()
{
	elf_update_audio();

	if(elf_get_elapsed_time(eng->time_sync_timer) > 0.0)
	{
		if(elf_about_zero(eng->tick_rate))
			eng->sync = (eng->sync*4.0+((float)elf_get_elapsed_time(eng->time_sync_timer)*eng->speed))/5.0;
		else eng->sync = eng->tick_rate;

		elf_start_timer(eng->time_sync_timer);

		if(eng->sync > 0.0)
		{
			if(eng->gui) elf_update_gui(eng->gui, eng->sync);

			if(eng->scene)
			{
				elf_update_scene(eng->scene, eng->sync);
			}
		}
	}
	else
	{
		elf_start_timer(eng->time_sync_timer);
	}

	elf_update_scripting();
}

void elf_count_engine_fps()
{
	eng->frames++;

	if(elf_get_elapsed_time(eng->fps_timer) > 0.0)
	{
		if(elf_get_elapsed_time(eng->fps_timer) >= 1.0)
		{
			eng->fps = eng->frames;
			eng->frames = 0;
			elf_start_timer(eng->fps_timer);
		}
	}
	else
	{
		elf_start_timer(eng->fps_timer);
	}
}

unsigned char elf_run()
{
	if(!eng || !eng->free_run) return ELF_FALSE;

	eng->free_run = ELF_FALSE;

	if((eng->f10_exit && elf_get_key_state(ELF_KEY_F10)) || !elf_is_window_opened() || eng->quit)
	{
		eng->free_run = ELF_TRUE;
		return ELF_FALSE;
	}

	gfx_reset_vertices_drawn();

	if(eng->post_process)
	{
		if(elf_get_multisamples() < 1)
		{
			gfx_set_render_target(eng->post_process->main_rt);
			gfx_set_render_target_color_texture(eng->post_process->main_rt, 0, eng->post_process->main_rt_color[0]);
		}
		gfx_clear_buffers(0.0, 0.0, 0.0, 1.0, 1.0);
	}
	else
	{
		gfx_clear_buffers(0.0, 0.0, 0.0, 1.0, 1.0);
	}

	if(eng->scene)
	{
		elf_scene_pre_draw(eng->scene);
		elf_draw_scene(eng->scene);
		elf_scene_post_draw(eng->scene);
	}

	if(eng->scene && eng->post_process)
	{
		if(elf_get_multisamples() > 0)
		{
			gfx_copy_frame_buffer(eng->post_process->main_rt_color[0], 0, 0, 0, 0, elf_get_window_width(), elf_get_window_height());
			if(eng->post_process->dof || eng->post_process->ssao)
				gfx_copy_frame_buffer(eng->post_process->main_rt_depth, 0, 0, 0, 0, elf_get_window_width(), elf_get_window_height());
		}
		elf_run_post_process(eng->post_process, eng->scene);
	}
	if(eng->scene && eng->debug_draw) elf_draw_scene_debug(eng->scene);
	if(eng->gui) elf_draw_gui(eng->gui);

	elf_swap_buffers();

	elf_limit_engine_fps();
	elf_update_engine();
	elf_count_engine_fps();

	eng->free_run = ELF_TRUE;

	elf_sleep(0.001);

	return ELF_TRUE;
}

void elf_deinit()
{
	elf_deinit_networking();
	elf_deinit_scripting();
	elf_deinit_engine();
	elf_deinit_audio();
	gfx_deinit();
	elf_deinit_context();
	elf_deinit_general();
}

void elf_resize_window(int width, int height)
{
	elf_set_error(ELF_MISSING_FEATURE, "error: resizing not yet in a usable state\n");

	/*if(width <= 0 || height <= 0 || (width == elf_get_window_width() &&
		height == elf_get_window_height())) return;

	elf_resize_context(width, height);
	elf_init_post_process_buffers(eng->post_process);*/
}

const char* elf_get_platform()
{
#if defined(ELF_WINDOWS)
	return "windows";
#elif defined(ELF_MACOSX)
	return "macosx";
#else
	return "linux";
#endif
}

int elf_get_version_major()
{
	return 0;
}

int elf_get_version_minor()
{
	return 9;
}

const char* elf_get_version_release()
{
	return "Beta 2";
}

const char* elf_get_version()
{
	return "BlendELF 0.9 Beta 2";
}

char* elf_get_directory_from_path(const char *file_path)
{
	int idx;

	if(strlen(file_path) < 1) return elf_create_string("");

	idx = elf_rfind_chars_from_string(file_path, "/\\");
	if(idx < 1)
	{
		return elf_create_string("");
	}
	else
	{
		return elf_sub_string((char*)file_path, 0, idx+1);
	}
}

const char* elf_get_current_directory()
{
	return eng->cwd;
}

const char* elf_get_error_string()
{
	return gen->err_str;
}

int elf_get_error()
{
	return gen->err_code;
}

void elf_quit()
{
	eng->quit = ELF_TRUE;
}

void elf_set_f10_exit(unsigned char exit)
{
	eng->f10_exit = !(exit == ELF_FALSE);
}

unsigned char elf_get_f10_exit()
{
	return eng->f10_exit;
}

elf_scene* elf_load_scene(const char *file_path)
{
	elf_scene *scene;

	scene = elf_create_scene_from_file(file_path);
	if(scene)
	{
		if(eng->scene) elf_dec_ref((elf_object*)eng->scene);
		eng->scene = scene;
		elf_inc_ref((elf_object*)eng->scene);
	}

	return scene;
}

void elf_set_scene(elf_scene *scene)
{
	if(eng->scene) elf_dec_ref((elf_object*)eng->scene);
	eng->scene = scene;
	if(eng->scene) elf_inc_ref((elf_object*)eng->scene);
}

elf_scene* elf_get_scene()
{
	return eng->scene;
}

void elf_set_gui(elf_gui *gui)
{
	if(eng->gui) elf_dec_ref((elf_object*)eng->gui);
	eng->gui = gui;
	if(eng->gui) elf_inc_ref((elf_object*)eng->gui);
}

elf_gui* elf_get_gui()
{
	return eng->gui;
}

float elf_get_sync()
{
	return eng->sync;
}

int elf_get_fps()
{
	return eng->fps;
}

void elf_set_fps_limit(int fps_limit)
{
	eng->fps_limit = fps_limit;
	if(eng->fps_limit < 0) eng->fps_limit = 0;
}

int elf_get_fps_limit()
{
	return eng->fps_limit;
}

void elf_set_tick_rate(float tick_rate)
{
	eng->tick_rate = tick_rate;
	if(eng->tick_rate < 0.0) eng->tick_rate = 0.0;
}

float elf_get_tick_rate()
{
	return eng->tick_rate;
}

void elf_set_speed(float speed)
{
	eng->speed = speed;
	if(eng->speed < 0.0001) eng->speed = 0.0001;
}

float elf_get_speed()
{
	return eng->speed;
}

unsigned char elf_save_screen_shot(const char *file_path)
{
	unsigned char *data;

	data = (unsigned char*)malloc(sizeof(unsigned char)*elf_get_window_width()*elf_get_window_height()*4);

	gfx_read_pixels(0, 0, elf_get_window_width(), elf_get_window_height(), GFX_BGRA, GFX_UBYTE, data);

	if(!elf_save_image_data(file_path, elf_get_window_width(), elf_get_window_height(), 32, data))
	{
		free(data);
		return ELF_FALSE;
	}

	free(data);

	return ELF_TRUE;
}

void elf_set_texture_compress(unsigned char compress)
{
	eng->texture_compress = !compress == ELF_FALSE;
}

unsigned char elf_get_texture_compress()
{
	return eng->texture_compress;
}

void elf_set_texture_anisotropy(float anisotropy)
{
	eng->texture_anisotropy = anisotropy;
}

float elf_get_texture_anisotropy()
{
	return eng->texture_anisotropy;
}

void elf_set_shadow_map_size(int size)
{
	// why would someone want a shadow map of 1 pixel?...
	if(size < 1) return;

	gfx_destroy_render_target(eng->shadow_target);
	gfx_destroy_texture(eng->shadow_map);

	eng->shadow_map_size = size;
	eng->shadow_map = gfx_create_2d_texture(size, size, 0.0f, GFX_CLAMP, GFX_LINEAR, GFX_DEPTH_COMPONENT, GFX_DEPTH_COMPONENT, GFX_UBYTE, NULL);
	eng->shadow_target = gfx_create_render_target(size, size);
	gfx_set_render_target_depth_texture(eng->shadow_target, eng->shadow_map);
}

int elf_get_shadow_map_size()
{
	return eng->shadow_map_size;
}

int elf_get_polygons_rendered()
{
	return gfx_get_vertices_drawn(GFX_TRIANGLES)/3+gfx_get_vertices_drawn(GFX_TRIANGLE_STRIP)/3;
}

void elf_set_fog(float start, float end, float r, float g, float b)
{
	eng->fog = ELF_TRUE;
	eng->fog_start = start;
	eng->fog_end = end;
	eng->fog_color.r = r;
	eng->fog_color.g = g;
	eng->fog_color.b = b;
}

void elf_disable_fog()
{
	eng->fog = ELF_FALSE;
}

float elf_get_fog_start()
{
	return eng->fog_start;
}

float elf_get_fog_end()
{
	return eng->fog_end;
}

elf_color elf_get_fog_color()
{
	return eng->fog_color;
}

void elf_set_bloom(float threshold)
{
	if(gfx_get_version() < 200) return;

	if(!eng->post_process) eng->post_process = elf_create_post_process();
	elf_set_post_process_bloom(eng->post_process, threshold);
}

void elf_disable_bloom()
{
	if(eng->post_process)
	{
		elf_disable_post_process_bloom(eng->post_process);
		if(!elf_is_post_process_bloom(eng->post_process) &&
			!elf_is_post_process_ssao(eng->post_process) &&
			!elf_is_post_process_dof(eng->post_process) &&
			!elf_is_post_process_light_shafts(eng->post_process))
		{
			elf_destroy_post_process(eng->post_process);
			eng->post_process = NULL;
		}
	}
}

float elf_get_bloom_threshold()
{
	if(!eng->post_process) return ELF_FALSE;
	return elf_get_post_process_bloom_threshold(eng->post_process);
}

void elf_set_dof(float focal_range, float focal_distance)
{
	if(gfx_get_version() < 200) return;

	if(!eng->post_process) eng->post_process = elf_create_post_process();
	elf_set_post_process_dof(eng->post_process, focal_range, focal_distance);
}

void elf_disable_dof()
{
	if(eng->post_process)
	{
		elf_disable_post_process_dof(eng->post_process);
		if(!elf_is_post_process_bloom(eng->post_process) &&
			!elf_is_post_process_ssao(eng->post_process) &&
			!elf_is_post_process_dof(eng->post_process) &&
			!elf_is_post_process_light_shafts(eng->post_process))
		{
			elf_destroy_post_process(eng->post_process);
			eng->post_process = NULL;
		}
	}
}

float elf_get_dof_focal_range()
{
	if(!eng->post_process) return ELF_FALSE;
	return elf_get_post_process_dof_focal_range(eng->post_process);
}

float elf_get_dof_focal_distance()
{
	if(!eng->post_process) return ELF_FALSE;
	return elf_get_post_process_dof_focal_distance(eng->post_process);
}

void elf_set_ssao(float amount)
{
	if(gfx_get_version() < 200) return;

	if(!eng->post_process) eng->post_process = elf_create_post_process();
	elf_set_post_process_ssao(eng->post_process, amount);
}

void elf_disable_ssao()
{
	if(eng->post_process)
	{
		elf_disable_post_process_ssao(eng->post_process);
		if(!elf_is_post_process_bloom(eng->post_process) &&
			!elf_is_post_process_ssao(eng->post_process) &&
			!elf_is_post_process_dof(eng->post_process) &&
			!elf_is_post_process_light_shafts(eng->post_process))
		{
			elf_destroy_post_process(eng->post_process);
			eng->post_process = NULL;
		}
	}
}

float elf_get_ssao_amount()
{
	if(eng->post_process) return elf_get_post_process_ssao_amount(eng->post_process);
	return 0.0;
}

void elf_set_light_shafts(float intensity)
{
	if(gfx_get_version() < 200) return;

	if(!eng->post_process) eng->post_process = elf_create_post_process();
	elf_set_post_process_light_shafts(eng->post_process, intensity);
}

void elf_disable_light_shafts()
{
	if(eng->post_process)
	{
		elf_disable_post_process_light_shafts(eng->post_process);
		if(!elf_is_post_process_bloom(eng->post_process) &&
			!elf_is_post_process_ssao(eng->post_process) &&
			!elf_is_post_process_dof(eng->post_process) &&
			!elf_is_post_process_light_shafts(eng->post_process))
		{
			elf_destroy_post_process(eng->post_process);
			eng->post_process = NULL;
		}
	}
}

float elf_get_light_shafts_intensity()
{
	if(eng->post_process) return elf_get_post_process_light_shafts_intensity(eng->post_process);
	return 0.0;
}

unsigned char elf_is_fog()
{
	return eng->fog;
}

unsigned char elf_is_bloom()
{
	if(eng->post_process) return elf_is_post_process_bloom(eng->post_process);
	return ELF_FALSE;
}

unsigned char elf_is_ssao()
{
	if(eng->post_process) return elf_is_post_process_ssao(eng->post_process);
	return ELF_FALSE;
}

unsigned char elf_is_dof()
{
	if(eng->post_process) return elf_is_post_process_dof(eng->post_process);
	return ELF_FALSE;
}

unsigned char elf_is_light_shafts()
{
	if(eng->post_process) return elf_is_post_process_light_shafts(eng->post_process);
	return ELF_FALSE;
}

void elf_set_occlusion_culling(unsigned char cull)
{
	eng->occlusion_culling = !cull == ELF_FALSE;
}

unsigned char elf_is_occlusion_culling()
{
	return eng->occlusion_culling;
}

void elf_set_debug_draw(unsigned char debug_draw)
{
	eng->debug_draw = !debug_draw == ELF_FALSE;
}

unsigned char elf_is_debug_draw()
{
	return eng->debug_draw;
}

elf_object* elf_get_actor()
{
	return eng->actor;
}

elf_directory_item* elf_create_directory_item()
{
	elf_directory_item *dir_item;

	dir_item = (elf_directory_item*)malloc(sizeof(elf_directory_item));
	memset(dir_item, 0x0, sizeof(elf_directory_item));
	dir_item->obj_type = ELF_DIRECTORY_ITEM;
	dir_item->obj_destr = elf_destroy_directory_item;

	elf_inc_obj(ELF_DIRECTORY_ITEM);

	return dir_item;
}

void elf_destroy_directory_item(void *data)
{
	elf_directory_item *directory_item = (elf_directory_item*)data;

	if(directory_item->name) elf_destroy_string(directory_item->name);

	free(directory_item);

	elf_dec_obj(ELF_DIRECTORY_ITEM);
}

elf_directory* elf_create_directory()
{
	elf_directory *directory;

	directory = (elf_directory*)malloc(sizeof(elf_directory));
	memset(directory, 0x0, sizeof(elf_directory));
	directory->obj_type = ELF_DIRECTORY;
	directory->obj_destr = elf_destroy_directory;

	directory->items = elf_create_list();

	elf_inc_obj(ELF_DIRECTORY);

	return directory;
}

void elf_destroy_directory(void *data)
{
	elf_directory *directory = (elf_directory*)data;

	if(directory->path) elf_destroy_string(directory->path);
	elf_destroy_list(directory->items);

	free(directory);

	elf_dec_obj(ELF_DIRECTORY);
}

void elf_append_folder_to_directory_item_list(elf_list *items, elf_directory_item *nitem)
{
	elf_directory_item *dir_item;
	int i;

	for(i = 0, dir_item = (elf_directory_item*)elf_begin_list(items); dir_item;
		dir_item = (elf_directory_item*)elf_next_in_list(items), i++)
	{
		if(dir_item->item_type == ELF_FILE)
		{
			elf_insert_to_list(items, i, (elf_object*)nitem);
			return;
		}
		else continue;
	}

	elf_append_to_list(items, (elf_object*)nitem);
}

typedef struct elf_dir_item_emul {
	char *str;
	int type;
} elf_dir_item_emul;

static int alphacmp(const void *a, const void *b)
{
	return strcmp((*((elf_dir_item_emul*)a)).str, (*((elf_dir_item_emul*)b)).str);
}

elf_directory* elf_read_directory(const char *path)
{
	elf_directory *directory;
	elf_directory_item *dir_item;
	DIR *dir;
	struct dirent *dp;
	elf_dir_item_emul *names;
	int item_count;
	int i;

	if(!(dir = opendir(path)))
	{
		elf_set_error(ELF_CANT_OPEN_DIRECTORY, "error: could not open directory \"%s\"\n", path);
		return NULL;
	}
	else
	{
		directory = elf_create_directory();
		directory->path = elf_create_string(path);

		while((dp = readdir(dir)))
		{
			dir_item = elf_create_directory_item();
			dir_item->name = elf_create_string(dp->d_name);

#ifdef ELF_WINDOWS
			if(dp->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) dir_item->item_type = ELF_DIR;
			else dir_item->item_type = ELF_FILE;
#else
			if(dp->d_type == 4) dir_item->item_type = ELF_DIR;
			else dir_item->item_type = ELF_FILE;
#endif

			elf_append_to_list(directory->items, (elf_object*)dir_item);
		}

		item_count = elf_get_list_length(directory->items);

		names = (elf_dir_item_emul*)malloc(sizeof(elf_dir_item_emul)*item_count);
		memset(names, 0x0, sizeof(elf_dir_item_emul)*item_count);

		for(i = 0, dir_item = (elf_directory_item*)elf_begin_list(directory->items); dir_item;
			dir_item = (elf_directory_item*)elf_next_in_list(directory->items), i++)
		{
			names[i].str = (char*)malloc(sizeof(char)*(strlen(dir_item->name)+1));
			memcpy(names[i].str, dir_item->name, sizeof(char)*(strlen(dir_item->name)+1));
			names[i].type = dir_item->item_type;
		}

		qsort(names, item_count, sizeof(elf_dir_item_emul), alphacmp);

		elf_destroy_directory(directory);

		directory = elf_create_directory();
		directory->path = elf_create_string(path);

		for(i = 0; i < item_count; i++)
		{
			dir_item = elf_create_directory_item();
			dir_item->name = elf_create_string(names[i].str);
			dir_item->item_type = names[i].type;

			if(dir_item->item_type == ELF_DIR)
				elf_append_folder_to_directory_item_list(directory->items, dir_item);
			else elf_append_to_list(directory->items, (elf_object*)dir_item);

			free(names[i].str);
		}

		free(names);

		return directory;
	}
}

const char* elf_get_directory_path(elf_directory *directory)
{
	return directory->path;
}

int elf_get_directory_item_count(elf_directory *directory)
{
	return elf_get_list_length(directory->items);
}

elf_directory_item* elf_get_directory_item(elf_directory *directory, int idx)
{
	int i;
	elf_directory_item *dir_item;

	if(idx < 0 || idx > elf_get_list_length(directory->items)-1) return NULL;

	for(i = 0, dir_item = (elf_directory_item*)elf_begin_list(directory->items); dir_item;
		dir_item = (elf_directory_item*)elf_next_in_list(directory->items), i++)
	{
		if(i == idx) return dir_item;
	}

	return NULL;
}

const char* elf_get_directory_item_name(elf_directory_item *dir_item)
{
	return dir_item->name;
}

int elf_get_directory_item_type(elf_directory_item *dir_item)
{
	return dir_item->item_type;
}

elf_vec3f elf_create_vec3f()
{
	elf_vec3f result;
	memset(&result, 0x0, sizeof(elf_vec3f));
	return result;
}

elf_vec3f elf_create_vec3f_from_values(float x, float y, float z)
{
	elf_vec3f result;
	memset(&result, 0x0, sizeof(elf_vec3f));

	result.x = x;
	result.y = y;
	result.z = z;

	return result;
}

elf_vec4f elf_create_qua()
{
	elf_vec4f result;
	memset(&result, 0x0, sizeof(elf_vec4f));
	return result;
}

elf_vec4f elf_create_qua_from_euler(float x, float y, float z)
{
	elf_vec4f result;
	memset(&result, 0x0, sizeof(elf_vec4f));

	gfx_qua_from_euler(x, y, z, &result.x);

	return result;
}

elf_vec4f elf_create_qua_from_angle_axis(float angle, float x, float y, float z)
{
	elf_vec4f qua;
	float axis[3];

	axis[0] = x; axis[1] = y; axis[2] = z;
	gfx_qua_from_angle_axis(angle, axis, &qua.x);

	return qua;
}

elf_vec3f elf_mul_qua_vec3f(elf_vec4f qua, elf_vec3f vec)
{
	elf_vec3f result;

	gfx_mul_qua_vec(&qua.x, &vec.x, &result.x);

	return result;
}

elf_vec4f elf_mul_qua_qua(elf_vec4f qua1, elf_vec4f qua2)
{
	elf_vec4f result;

	gfx_mul_qua_qua(&qua1.x, &qua2.x, &result.x);

	return result;
}

elf_vec4f elf_get_qua_inverted(elf_vec4f qua)
{
	elf_vec4f result;

	gfx_qua_get_inverse(&qua.x, &result.x);

	return result;
}

elf_vec3f elf_rotate_vec3f(elf_vec3f vec, float x, float y, float z)
{
	elf_vec4f qua;
	elf_vec3f result;

	gfx_qua_from_euler(x, y, z, &qua.x);

	gfx_mul_qua_vec(&qua.x, &vec.x, &result.x);

	return result;
}

elf_vec3f elf_sub_vec3f_vec3f(elf_vec3f vec1, elf_vec3f vec2)
{
	elf_vec3f result;
	result.x = vec1.x-vec2.x;
	result.y = vec1.y-vec2.y;
	result.z = vec1.z-vec2.z;
	return result;
}

elf_vec3f elf_add_vec3f_vec3f(elf_vec3f vec1, elf_vec3f vec2)
{
	elf_vec3f result;
	result.x = vec1.x+vec2.x;
	result.y = vec1.y+vec2.y;
	result.z = vec1.z+vec2.z;
	return result;
}

float elf_get_vec3f_length(elf_vec3f vec)
{
	return gfx_vec_length(&vec.x);
}

unsigned char elf_about_zero(float val)
{
	if(val < 0.0001 && val > -0.0001) return ELF_TRUE;
	return ELF_FALSE;
}

float elf_float_abs(float val)
{
	if(val < 0.0) return -val;
	return val;
}

float elf_float_min(float a, float b)
{
	if(a < b) return a;
	return b;
}

float elf_float_max(float a, float b)
{
	if(a > b) return a;
	return b;
}

float elf_random_float()
{
	return (float)rand()/(float)RAND_MAX;
}

float elf_random_float_range(float min, float max)
{
	return min+(max-min)*elf_random_float();
}

int elf_random_int()
{
	return rand();
}

int elf_random_int_range(int min, int max)
{
	return (int)(((float)(min+(max-min)))*elf_random_float());
}

