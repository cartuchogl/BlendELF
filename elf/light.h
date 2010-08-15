
elf_light* elf_create_light(const char *name)
{
	elf_light *light;

	light = (elf_light*)malloc(sizeof(elf_light));
	memset(light, 0x0, sizeof(elf_light));
	light->obj_type = ELF_LIGHT;
	light->obj_destr = elf_destroy_light;

	elf_init_actor((elf_actor*)light, ELF_FALSE);

	light->distance = 30.0;
	light->fade_speed = 1.0/30.0;
	light->inner_cone = 45.0;
	light->outer_cone = 0.0;
	light->light_type = ELF_POINT_LIGHT;
	light->visible = ELF_TRUE;
	light->shaft = ELF_FALSE;
	light->shaft_size = 1.0;
	light->shaft_intensity = 1.0;
	light->shaft_fade_off = 0.0;

	elf_set_light_color(light, 1.0, 1.0, 1.0, 1.0);

	light->shadow_camera = elf_create_camera("elf_shadow_camera");
	elf_set_camera_viewport(light->shadow_camera, 0, 0, 512, 512);
	elf_set_camera_perspective(light->shadow_camera, (light->inner_cone+light->outer_cone)*2, 1.0, 1.0, light->distance+(1.0/light->fade_speed));

	gfx_matrix4_set_identity(light->projection_matrix);

	light->dobject = elf_create_physics_object_sphere(0.5, 0.0, 0.0, 0.0, 0.0);
	elf_set_physics_object_actor(light->dobject, (elf_actor*)light);
	elf_inc_ref((elf_object*)light->dobject);

	light->pbb_lengths.x = light->pbb_lengths.y = light->pbb_lengths.z = 1.0;

	if(name) light->name = elf_create_string(name);

	elf_inc_obj(ELF_LIGHT);

	return light;
}

void elf_update_light(elf_light *light)
{
	elf_update_actor((elf_actor*)light);
}

void elf_light_pre_draw(elf_light *light)
{
	elf_actor_pre_draw((elf_actor*)light);

	elf_camera_pre_draw(light->shadow_camera);
}

void elf_light_post_draw(elf_light *light)
{
	elf_actor_post_draw((elf_actor*)light);
}

void elf_destroy_light(void *data)
{
	elf_light *light = (elf_light*)data;

	elf_clean_actor((elf_actor*)light);

	elf_destroy_camera(light->shadow_camera);

	free(light);

	elf_dec_obj(ELF_LIGHT);
}

void elf_set_light_type(elf_light *light, int type)
{
	if(type != ELF_POINT_LIGHT &&
		type != ELF_SPOT_LIGHT &&
		type != ELF_SUN_LIGHT) return;
	light->light_type = type;
}

void elf_set_light_color(elf_light *light, float r, float g, float b, float a)
{
	light->color.r = r;
	light->color.g = g;
	light->color.b = b;
	light->color.a = a;
}

void elf_set_light_distance(elf_light *light, float distance)
{
	light->distance = distance;
	if(light->distance < 0.0) light->distance = 0.0;
	elf_set_camera_perspective(light->shadow_camera, (light->inner_cone+light->outer_cone)*2, 1.0, 1.0, light->distance+(1.0/(light->fade_speed)));
}

void elf_set_light_fade_speed(elf_light *light, float fade_speed)
{
	light->fade_speed = fade_speed;
	if(light->fade_speed < 0.0001) light->fade_speed = 0.0001;
	if(light->fade_speed > 1.0) light->fade_speed = 1.0;
	elf_set_camera_perspective(light->shadow_camera, (light->inner_cone+light->outer_cone)*2, 1.0, 1.0, light->distance+(1.0/(light->fade_speed)));
}

void elf_set_light_shadows(elf_light *light, unsigned char shadows)
{
	if(light->shadows == shadows) return;

	light->shadows = shadows;

	light->moved = ELF_TRUE;
}

int elf_get_light_type(elf_light *light)
{
	return light->light_type;
}

elf_color elf_get_light_color(elf_light *light)
{
	return light->color;
}

float elf_get_light_distance(elf_light *light)
{
	return light->distance;
}

float elf_get_light_fade_speed(elf_light *light)
{
	return light->fade_speed;
}

unsigned char elf_get_light_shadows(elf_light *light)
{
	return light->shadows;
}

unsigned char elf_get_light_visible(elf_light *light)
{
	return light->visible;
}

unsigned char elf_is_light_shaft(elf_light *light)
{
	return light->shaft;
}

float elf_get_light_shaft_size(elf_light *light)
{
	return light->shaft_size;
}

float elf_get_light_shaft_intensity(elf_light *light)
{
	return light->shaft_intensity;
}

float elf_get_light_shaft_fade_off(elf_light *light)
{
	return light->shaft_fade_off;
}

elf_vec2f elf_get_light_cone(elf_light *light)
{
	elf_vec2f cone;

	cone.x = light->inner_cone;
	cone.y = light->outer_cone;

	return cone;
}

void elf_set_light_visible(elf_light *light, unsigned char visible)
{
	light->visible = !(visible == ELF_FALSE);
}

void elf_set_light_cone(elf_light *light, float inner_cone, float outer_cone)
{
	light->inner_cone = inner_cone;
	light->outer_cone = outer_cone;
	if(light->inner_cone < 0.0) light->inner_cone = 0.0;
	if(light->outer_cone < 0.0) light->outer_cone = 0.0;
	elf_set_camera_perspective(light->shadow_camera, (light->inner_cone+light->outer_cone)*2, 1.0, 1.0, light->distance+(1.0/(light->fade_speed)));
}

void elf_set_light_shaft(elf_light *light, float size, float intensity, float fade_off)
{
	light->shaft = ELF_TRUE;
	light->shaft_size = size;
	light->shaft_intensity = intensity;
	if(light->shaft_intensity < 0.0) light->shaft_intensity = 0.0;
	light->shaft_fade_off = fade_off;
	if(light->shaft_fade_off < 0.0) light->shaft_fade_off = 0.0;
	if(light->shaft_fade_off > 1.0) light->shaft_fade_off = 1.0;
}

void elf_disable_light_shaft(elf_light *light)
{
	light->shaft = ELF_FALSE;
}

void elf_set_light(elf_light *light, elf_camera *camera, gfx_shader_params *shader_params)
{
	float axis[3];
	float final_axis[3] = {0.0, 0.0, -1.0};
	float matrix[16];
	float matrix2[16];
	float orient[4];
	float final_pos[4];

	gfx_mul_matrix4_matrix4(gfx_get_transform_matrix(light->transform), elf_get_camera_modelview_matrix(camera), matrix);
	final_pos[0] = matrix[12];
	final_pos[1] = matrix[13];
	final_pos[2] = matrix[14];

	gfx_get_transform_orientation(light->transform, orient);
	gfx_mul_qua_vec(orient, final_axis, axis);
	gfx_matrix4_get_inverse(elf_get_camera_modelview_matrix(camera), matrix2);
	gfx_mul_matrix4_vec3(matrix2, axis, final_axis);

	shader_params->light_params.type = light->light_type;
	memcpy(&shader_params->light_params.position.x, final_pos, sizeof(float)*3);
	memcpy(&shader_params->light_params.direction.x, final_axis, sizeof(float)*3);
	memcpy(&shader_params->light_params.color.r, &light->color.r, sizeof(float)*4);
	shader_params->light_params.distance = light->distance;
	shader_params->light_params.fade_speed = light->fade_speed;
	shader_params->light_params.inner_cone = light->inner_cone;
	shader_params->light_params.outer_cone = light->outer_cone;
}

unsigned char elf_get_light_changed(elf_light *light)
{
	return light->moved;
}

void elf_draw_light_debug(elf_light *light, gfx_shader_params *shader_params)
{
	float *vertex_buffer;
	float step;
	float size;
	int i;

	gfx_mul_matrix4_matrix4(gfx_get_transform_matrix(light->transform),
		shader_params->camera_matrix, shader_params->modelview_matrix);

	vertex_buffer = (float*)gfx_get_vertex_data_buffer(eng->lines);

	if(!light->selected) gfx_set_color(&shader_params->material_params.color, 0.5, 0.5, 0.2, 1.0);
	else gfx_set_color(&shader_params->material_params.color, 1.0, 0.0, 0.0, 1.0);
	gfx_set_shader_params(shader_params);

	step = (360.0/((float)32))*GFX_PI_DIV_180;

	for(i = 0; i < 32; i++)
	{
		vertex_buffer[i*3] = -((float)sin((float)(step*i)))*0.5;
		vertex_buffer[i*3+1] = ((float)cos((float)(step*i)))*0.5;
		vertex_buffer[i*3+2] = 0.0;
	}

	gfx_draw_line_loop(32, eng->lines);

	for(i = 0; i < 32; i++)
	{
		vertex_buffer[i*3] = 0.0;
		vertex_buffer[i*3+1] = -((float)sin((float)(step*i)))*0.5;
		vertex_buffer[i*3+2] = ((float)cos((float)(step*i)))*0.5;
	}

	gfx_draw_line_loop(32, eng->lines);

	for(i = 0; i < 32; i++)
	{
		vertex_buffer[i*3] = -((float)sin((float)(step*i)))*0.5;
		vertex_buffer[i*3+1] = 0.0;
		vertex_buffer[i*3+2] = ((float)cos((float)(step*i)))*0.5;
	}

	gfx_draw_line_loop(32, eng->lines);

	if(!light->selected) gfx_set_color(&shader_params->material_params.color, 0.3, 0.3, 0.1, 1.0);
	else gfx_set_color(&shader_params->material_params.color, 1.0, 0.0, 0.0, 1.0);
	gfx_set_shader_params(shader_params);

	if(light->light_type == ELF_POINT_LIGHT)
	{
		step = (360.0/((float)128))*GFX_PI_DIV_180;

		for(i = 0; i < 128; i++)
		{
			vertex_buffer[i*3] = -((float)sin((float)(step*i)))*light->distance;
			vertex_buffer[i*3+1] = ((float)cos((float)(step*i)))*light->distance;
			vertex_buffer[i*3+2] = 0.0;
		}

		gfx_draw_lines(128, eng->lines);

		for(i = 0; i < 128; i++)
		{
			vertex_buffer[i*3] = 0.0;
			vertex_buffer[i*3+1] = -((float)sin((float)(step*i)))*light->distance;
			vertex_buffer[i*3+2] = ((float)cos((float)(step*i)))*light->distance;
		}

		gfx_draw_lines(128, eng->lines);

		for(i = 0; i < 128; i++)
		{
			vertex_buffer[i*3] = -((float)sin((float)(step*i)))*light->distance;
			vertex_buffer[i*3+1] = 0.0;
			vertex_buffer[i*3+2] = ((float)cos((float)(step*i)))*light->distance;
		}

		gfx_draw_lines(128, eng->lines);

		vertex_buffer[0] = 0.0;
		vertex_buffer[1] = 0.0;
		vertex_buffer[2] = 0.5;
		vertex_buffer[3] = 0.0;
		vertex_buffer[4] = 0.0;
		vertex_buffer[5] = -0.5;
		vertex_buffer[6] = -0.5;
		vertex_buffer[7] = 0.0;
		vertex_buffer[8] = 0.0;
		vertex_buffer[9] = 0.5;
		vertex_buffer[10] = 0.0;
		vertex_buffer[11] = 0.0;
		vertex_buffer[12] = 0.0;
		vertex_buffer[13] = -0.5;
		vertex_buffer[14] = 0.0;
		vertex_buffer[15] = 0.0;
		vertex_buffer[16] = 0.5;
		vertex_buffer[17] = 0.0;

		gfx_draw_lines(6, eng->lines);
	}
	else if(light->light_type == ELF_SPOT_LIGHT)
	{
		step = (360.0/((float)128))*GFX_PI_DIV_180;
		size = sin((float)GFX_PI_DIV_180*light->inner_cone)*light->distance;

		for(i = 0; i < 128; i++)
		{
			vertex_buffer[i*3] = -(float)sin(step*i)*size;
			vertex_buffer[i*3+1] = (float)cos(step*i)*size;
			vertex_buffer[i*3+2] = -light->distance;
		}

		gfx_draw_lines(128, eng->lines);

		size = sin((float)GFX_PI_DIV_180*(light->inner_cone+light->outer_cone))*light->distance;

		for(i = 0; i < 128; i++)
		{
			vertex_buffer[i*3] = -(float)sin(step*i)*size;
			vertex_buffer[i*3+1] = (float)cos(step*i)*size;
			vertex_buffer[i*3+2] = -light->distance;
		}

		gfx_draw_lines(128, eng->lines);

		vertex_buffer[0] = 0.0;
		vertex_buffer[1] = 0.0;
		vertex_buffer[2] = 0.5;
		vertex_buffer[3] = 0.0;
		vertex_buffer[4] = 0.0;
		vertex_buffer[5] = -0.5;
		vertex_buffer[6] = -0.5;
		vertex_buffer[7] = 0.0;
		vertex_buffer[8] = 0.0;
		vertex_buffer[9] = 0.5;
		vertex_buffer[10] = 0.0;
		vertex_buffer[11] = 0.0;
		vertex_buffer[12] = 0.0;
		vertex_buffer[13] = -0.5;
		vertex_buffer[14] = 0.0;
		vertex_buffer[15] = 0.0;
		vertex_buffer[16] = 0.5;
		vertex_buffer[17] = 0.0;
		vertex_buffer[18] = 0.0;
		vertex_buffer[19] = 0.0;
		vertex_buffer[20] = 0.0;
		vertex_buffer[21] = size;
		vertex_buffer[22] = 0.0;
		vertex_buffer[23] = -light->distance;
		vertex_buffer[24] = 0.0;
		vertex_buffer[25] = 0.0;
		vertex_buffer[26] = 0.0;
		vertex_buffer[27] = -size;
		vertex_buffer[28] = 0.0;
		vertex_buffer[29] = -light->distance;

		gfx_draw_lines(13, eng->lines);
	}
	else if(light->light_type == ELF_SUN_LIGHT)
	{
		vertex_buffer[0] = 0.0;
		vertex_buffer[1] = 0.0;
		vertex_buffer[2] = 0.5;
		vertex_buffer[3] = 0.0;
		vertex_buffer[4] = 0.0;
		vertex_buffer[5] = -light->distance;
		vertex_buffer[6] = -0.5;
		vertex_buffer[7] = 0.0;
		vertex_buffer[8] = 0.0;
		vertex_buffer[9] = 0.5;
		vertex_buffer[10] = 0.0;
		vertex_buffer[11] = 0.0;
		vertex_buffer[12] = 0.0;
		vertex_buffer[13] = -0.5;
		vertex_buffer[14] = 0.0;
		vertex_buffer[15] = 0.0;
		vertex_buffer[16] = 0.5;
		vertex_buffer[17] = 0.0;

		gfx_draw_lines(6, eng->lines);
	}
}

