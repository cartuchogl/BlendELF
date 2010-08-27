
elf_camera* elf_create_camera(const char *name)
{
	elf_camera *camera;

	camera = (elf_camera*)malloc(sizeof(elf_camera));
	memset(camera, 0x0, sizeof(elf_camera));
	camera->obj_type = ELF_CAMERA;
	camera->obj_destr = elf_destroy_camera;

	elf_init_actor((elf_actor*)camera, ELF_TRUE);

	camera->mode = ELF_PERSPECTIVE;
	camera->viewp_x = 0;
	camera->viewp_y = 0;
	camera->viewp_width = -1;
	camera->viewp_height = -1;
	camera->fov = 35.0;
	camera->aspect = -1.0;
	camera->ortho_x = 0;
	camera->ortho_y = 0;
	camera->ortho_width = -1;
	camera->ortho_height = -1;
	camera->clip_near = 1.0;
	camera->clip_far = 100.0;

	gfx_matrix4_set_identity(camera->projection_matrix);
	gfx_matrix4_set_identity(camera->modelview_matrix);

	elf_set_camera_perspective(camera, camera->fov, camera->aspect, camera->clip_near, camera->clip_far);

	camera->dobject = elf_create_physics_object_box(0.35, 0.35, 0.35, 0.0, 0.0, 0.0, 0.0);
	elf_set_physics_object_actor(camera->dobject, (elf_actor*)camera);
	elf_inc_ref((elf_object*)camera->dobject);

	camera->pbb_lengths.x = camera->pbb_lengths.y = camera->pbb_lengths.z = 0.7;

	if(name) camera->name = elf_create_string(name);

	camera->id = ++gen->camera_id_counter;
	
	elf_inc_obj(ELF_CAMERA);

	return camera;
}

void elf_update_camera(elf_camera *camera)
{
	elf_update_actor((elf_actor*)camera);

	if(camera->mode == ELF_PERSPECTIVE)
		elf_set_camera_perspective(camera, camera->fov, camera->aspect, camera->clip_near, camera->clip_far);
}

void elf_camera_pre_draw(elf_camera *camera)
{
	elf_actor_pre_draw((elf_actor*)camera);

	gfx_get_frustum(camera->projection_matrix, elf_get_camera_modelview_matrix(camera), camera->frustum);
	elf_get_actor_position_((elf_actor*)camera, &camera->position.x);
}

void elf_camera_post_draw(elf_camera *camera)
{
	elf_actor_post_draw((elf_actor*)camera);
}

void elf_destroy_camera(void *data)
{
	elf_camera *camera = (elf_camera*)data;

	elf_clean_actor((elf_actor*)camera);

	free(camera);

	elf_dec_obj(ELF_CAMERA);
}

void elf_set_camera_viewport(elf_camera *camera, int x, int y, int width, int height)
{
	camera->viewp_x = x;
	camera->viewp_y = y;
	camera->viewp_width = width;
	camera->viewp_height = height;
}

void elf_set_camera_perspective(elf_camera *camera, float fov, float aspect, float clip_near, float clip_far)
{
	camera->mode = ELF_PERSPECTIVE;

	camera->fov = fov;
	camera->aspect = aspect;
	camera->clip_near = clip_near;
	camera->clip_far = clip_far;

	if(aspect <= 0.0)
	{
		if((float)elf_get_window_width()/(float)elf_get_window_height() >= 1.0)
			aspect = (float)elf_get_window_width()/(float)elf_get_window_height();
		else aspect = (float)elf_get_window_height()/(float)elf_get_window_width();
	}

	camera->far_plane_height = 2 * (float)tan(camera->fov * GFX_PI_DIV_180 / 2) * camera->clip_far;
	camera->far_plane_width = camera->far_plane_height * aspect;

	gfx_get_perspective_projection_matrix(camera->fov, aspect,
		camera->clip_near, camera->clip_far, camera->projection_matrix);
}

void elf_set_camera_orthographic(elf_camera *camera, int x, int y, int width, int height, float clip_near, float clip_far)
{
	camera->mode = ELF_ORTHOGRAPHIC;

	camera->ortho_x = x;
	camera->ortho_y = y;
	camera->ortho_width = width;
	camera->ortho_height = height;
	camera->clip_near = clip_near;
	camera->clip_far = clip_far;

	camera->far_plane_height = height;
	camera->far_plane_width = width;

	if(width <= 0) width = elf_get_window_width();
	if(height <= 0) height = elf_get_window_height();

	gfx_get_orthographic_projection_matrix(
		(float)camera->ortho_x, (float)(camera->ortho_x+width),
		(float)camera->ortho_y, (float)(camera->ortho_y+height),
		(float)camera->clip_near, camera->clip_far, camera->projection_matrix);
}

float elf_get_camera_fov(elf_camera *camera)
{
	return camera->fov;
}

float elf_get_camera_aspect(elf_camera *camera)
{
	float aspect = camera->aspect;

	if(aspect <= 0.0)
	{
		if((float)elf_get_window_width()/(float)elf_get_window_height() >= 1.0)
			aspect = (float)elf_get_window_width()/(float)elf_get_window_height();
		else aspect = (float)elf_get_window_height()/(float)elf_get_window_width();
	}

	return aspect;
}

elf_vec2i elf_get_camera_viewport_size(elf_camera *camera)
{
	elf_vec2i size;

	size.x = camera->viewp_width;
	size.y = camera->viewp_height;
	if(size.x <= 0.0) size.x = elf_get_window_width();
	if(size.y <= 0.0) size.x = elf_get_window_height();

	return size;
}

elf_vec2i elf_get_camera_viewport_offset(elf_camera *camera)
{
	elf_vec2i offset;

	offset.x = camera->viewp_x;
	offset.y = camera->viewp_y;

	return offset;
}

elf_vec2f elf_get_camera_clip(elf_camera *camera)
{
	elf_vec2f clip;

	clip.x = camera->clip_near;
	clip.y = camera->clip_far;

	return clip;
}

elf_vec2f elf_get_camera_far_plane_size(elf_camera *camera)
{
	elf_vec2f size;

	size.x = camera->far_plane_width;
	size.y = camera->far_plane_height;
	if(size.x <= 0.0) size.x = elf_get_window_width();
	if(size.y <= 0.0) size.x = elf_get_window_height();

	return size;
}

float* elf_get_camera_projection_matrix(elf_camera *camera)
{
	return camera->projection_matrix;
}

float* elf_get_camera_modelview_matrix(elf_camera *camera)
{
	memcpy(camera->modelview_matrix, gfx_get_transform_matrix(camera->transform), sizeof(float)*16);
	return camera->modelview_matrix;
}

void elf_set_camera(elf_camera *camera, gfx_shader_params *shader_params)
{
	int viewp_width, viewp_height;

	viewp_width = camera->viewp_width;
	viewp_height = camera->viewp_height;
	if(camera->viewp_width <= 0) viewp_width = elf_get_window_width();
	if(camera->viewp_height <= 0) viewp_height = elf_get_window_height();

	gfx_set_viewport(camera->viewp_x, camera->viewp_y, viewp_width, viewp_height);

	memcpy(shader_params->projection_matrix, camera->projection_matrix, sizeof(float)*16);
	memcpy(camera->modelview_matrix, gfx_get_transform_matrix(camera->transform), sizeof(float)*16);
	memcpy(shader_params->modelview_matrix, camera->modelview_matrix, sizeof(float)*16);
	memcpy(shader_params->camera_matrix, camera->modelview_matrix, sizeof(float)*16);

	shader_params->clip_start = camera->clip_near;
	shader_params->clip_end = camera->clip_far;
	shader_params->viewport_width = viewp_width;
	shader_params->viewport_height = viewp_height;
}

unsigned char elf_aabb_inside_frustum(elf_camera *camera, float *min, float *max)
{
	return gfx_aabb_inside_frustum(camera->frustum, min, max);
}

unsigned char elf_sphere_inside_frustum(elf_camera *camera, float *pos, float radius)
{
	return gfx_sphere_inside_frustum(camera->frustum, pos, radius);
}

unsigned char elf_camera_inside_aabb(elf_camera *camera, float *min, float *max)
{
	return camera->position.x > min[0]-camera->clip_near && camera->position.y > min[1]-camera->clip_near && camera->position.z > min[2]-camera->clip_near &&
		camera->position.x < max[0]+camera->clip_near && camera->position.y < max[1]+camera->clip_near && camera->position.z < max[2]+camera->clip_near;
}

unsigned char elf_camera_inside_sphere(elf_camera *camera, float *pos, float radius)
{
	return camera->position.x > pos[0]-radius && camera->position.y > pos[1]-radius && camera->position.z > pos[2]-radius &&
		camera->position.x < pos[0]+radius && camera->position.y < pos[1]+radius && camera->position.z < pos[2]+radius;
}

void elf_draw_camera_debug(elf_camera *camera, gfx_shader_params *shader_params)
{
	float min[3];
	float max[3];
	float position[3];
	float rotation[3];
	gfx_transform *transform;
	float *vertex_buffer;

	transform = gfx_create_object_transform();

	gfx_get_transform_position(camera->transform, position);
	gfx_get_transform_rotation(camera->transform, rotation);
	gfx_set_transform_position(transform, position[0], position[1], position[2]);
	gfx_set_transform_rotation(transform, rotation[0], rotation[1], rotation[2]);

	gfx_mul_matrix4_matrix4(gfx_get_transform_matrix(transform),
		shader_params->camera_matrix, shader_params->modelview_matrix);

	gfx_destroy_transform(transform);

	min[0] = min[1] = min[2] = -0.35;
	max[0] = max[1] = max[2] = 0.35;

	gfx_set_color(&shader_params->material_params.color, 0.2, 0.6, 0.2, 1.0);
	shader_params->render_params.blend_mode = ELF_ADD;
	gfx_set_shader_params(shader_params);
	gfx_draw_bounding_box(min, max);

	vertex_buffer = (float*)gfx_get_vertex_data_buffer(eng->lines);

	vertex_buffer[0] = -1.5;
	vertex_buffer[1] = 0.0;
	vertex_buffer[2] = 0.0;
	vertex_buffer[3] = 1.5;
	vertex_buffer[4] = 0.0;
	vertex_buffer[5] = 0.0;
	vertex_buffer[6] = 0.0;
	vertex_buffer[7] = -1.5;
	vertex_buffer[8] = 0.0;
	vertex_buffer[9] = 0.0;
	vertex_buffer[10] = 1.5;
	vertex_buffer[11] = 0.0;
	vertex_buffer[12] = 0.0;
	vertex_buffer[13] = 0.0;
	vertex_buffer[14] = 0.5;
	vertex_buffer[15] = 0.0;
	vertex_buffer[16] = 0.0;
	vertex_buffer[17] = -3.0;

	if(!camera->selected) gfx_set_color(&shader_params->material_params.color, 0.2, 0.6, 0.2, 1.0);
	else gfx_set_color(&shader_params->material_params.color, 1.0, 0.0, 0.0, 1.0);
	gfx_set_shader_params(shader_params);
	gfx_draw_lines(6, eng->lines);
}

elf_vec3f elf_project_camera_point(elf_camera *camera, float x, float y, float z)
{
	elf_vec3f result;
	int viewp[4];

	viewp[0] = camera->viewp_x;
	viewp[1] = camera->viewp_y;
	viewp[2] = camera->viewp_width;
	viewp[3] = camera->viewp_height;

	if(viewp[2] <= 0) viewp[2] = elf_get_window_width();
	if(viewp[3] <= 0) viewp[3] = elf_get_window_height();

	gfx_project(x, y, z, elf_get_camera_modelview_matrix(camera),
		elf_get_camera_projection_matrix(camera), viewp, &result.x);

	return result;
}

elf_vec3f elf_un_project_camera_point(elf_camera *camera, float x, float y, float z)
{
	elf_vec3f result;
	int viewp[4];

	viewp[0] = camera->viewp_x;
	viewp[1] = camera->viewp_y;
	viewp[2] = camera->viewp_width;
	viewp[3] = camera->viewp_height;

	if(viewp[2] <= 0) viewp[2] = elf_get_window_width();
	if(viewp[3] <= 0) viewp[3] = elf_get_window_height();

	gfx_un_project(x, camera->viewp_height-y, z, elf_get_camera_modelview_matrix(camera),
		elf_get_camera_projection_matrix(camera), viewp, &result.x);

	return result;
}

