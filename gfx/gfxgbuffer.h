
gfx_gbuffer* gfx_create_gbuffer(int width, int height)
{
	gfx_gbuffer* gbuffer;

	gbuffer = (gfx_gbuffer*)malloc(sizeof(gfx_gbuffer));
	memset(gbuffer, 0x0, sizeof(gfx_gbuffer));
	gbuffer->obj_type = GFX_GBUFFER;
	gbuffer->obj_destr = gfx_destroy_gbuffer;

	gbuffer->width = width;
	gbuffer->height = height;

	gbuffer->depth_tex = gfx_create_2d_texture(width, height, 0.0, GFX_CLAMP, GFX_NEAREST, GFX_DEPTH_COMPONENT, GFX_DEPTH_COMPONENT, GFX_UBYTE, NULL);
	gbuffer->buf1_tex = gfx_create_2d_texture(width, height, 0.0, GFX_CLAMP, GFX_NEAREST, GFX_RG, GFX_RG16F, GFX_FLOAT, NULL);
	gbuffer->buf2_tex = gfx_create_2d_texture(width, height, 0.0, GFX_CLAMP, GFX_NEAREST, GFX_RGBA, GFX_RGBA, GFX_FLOAT, NULL);
	gbuffer->buf3_tex = gfx_create_2d_texture(width, height, 0.0, GFX_CLAMP, GFX_NEAREST, GFX_RGBA, GFX_RGBA, GFX_FLOAT, NULL);
	gbuffer->diffuse_tex = gfx_create_2d_texture(width, height, 0.0, GFX_CLAMP, GFX_NEAREST, GFX_RGBA, GFX_RGBA16F, GFX_FLOAT, NULL);
	gbuffer->specular_tex = gfx_create_2d_texture(width, height, 0.0, GFX_CLAMP, GFX_NEAREST, GFX_RGBA, GFX_RGBA16F, GFX_FLOAT, NULL);
	gbuffer->main_tex = gfx_create_2d_texture(width, height, 0.0, GFX_CLAMP, GFX_LINEAR, GFX_RGBA, GFX_RGBA, GFX_UBYTE, NULL);

	gbuffer->buf_rt = gfx_create_render_target(width, height);
	gbuffer->light_rt = gfx_create_render_target(width, height);
	gbuffer->main_rt = gfx_create_render_target(width, height);

	gfx_set_render_target_color_texture(gbuffer->buf_rt, 0, gbuffer->buf1_tex);
	gfx_set_render_target_color_texture(gbuffer->buf_rt, 1, gbuffer->buf2_tex);
	gfx_set_render_target_color_texture(gbuffer->buf_rt, 2, gbuffer->buf3_tex);
	gfx_set_render_target_depth_texture(gbuffer->buf_rt, gbuffer->depth_tex);

	gfx_set_render_target_color_texture(gbuffer->light_rt, 0, gbuffer->diffuse_tex);
	gfx_set_render_target_color_texture(gbuffer->light_rt, 1, gbuffer->specular_tex);

	gfx_set_render_target_color_texture(gbuffer->main_rt, 0, gbuffer->main_tex);
	gfx_set_render_target_depth_texture(gbuffer->main_rt, gbuffer->depth_tex);

	gfx_inc_ref((gfx_object*)gbuffer->depth_tex);
	gfx_inc_ref((gfx_object*)gbuffer->buf1_tex);
	gfx_inc_ref((gfx_object*)gbuffer->buf2_tex);
	gfx_inc_ref((gfx_object*)gbuffer->buf3_tex);
	gfx_inc_ref((gfx_object*)gbuffer->diffuse_tex);
	gfx_inc_ref((gfx_object*)gbuffer->specular_tex);
	gfx_inc_ref((gfx_object*)gbuffer->main_tex);

	return gbuffer;
}

void gfx_destroy_gbuffer(void *data)
{
	gfx_gbuffer *gbuffer = (gfx_gbuffer*)data;

	gfx_destroy_render_target(gbuffer->buf_rt);
	gfx_destroy_render_target(gbuffer->light_rt);
	gfx_destroy_render_target(gbuffer->main_rt);

	gfx_dec_ref((gfx_object*)gbuffer->depth_tex);
	gfx_dec_ref((gfx_object*)gbuffer->buf1_tex);
	gfx_dec_ref((gfx_object*)gbuffer->buf2_tex);
	gfx_dec_ref((gfx_object*)gbuffer->buf3_tex);
	gfx_dec_ref((gfx_object*)gbuffer->diffuse_tex);
	gfx_dec_ref((gfx_object*)gbuffer->specular_tex);
	gfx_dec_ref((gfx_object*)gbuffer->main_tex);
}

void gfx_bind_gbuffer(gfx_gbuffer *gbuffer, gfx_shader_params *shader_params)
{
	gfx_set_render_target(gbuffer->buf_rt);
}

void gfx_bind_gbuffer_light(gfx_gbuffer *gbuffer, gfx_shader_params *shader_params)
{
	gfx_set_render_target(gbuffer->light_rt);
}

void gfx_bind_gbuffer_main(gfx_gbuffer *gbuffer, gfx_shader_params *shader_params)
{
	gfx_set_render_target(gbuffer->main_rt);
}

gfx_texture* gfx_get_gbuffer_depth(gfx_gbuffer *gbuffer)
{
	return gbuffer->depth_tex;
}

gfx_texture* gfx_get_gbuffer_diffuse(gfx_gbuffer *gbuffer)
{
	return gbuffer->diffuse_tex;
}

gfx_texture* gfx_get_gbuffer_specular(gfx_gbuffer *gbuffer)
{
	return gbuffer->specular_tex;
}

gfx_texture* gfx_get_gbuffer_main(gfx_gbuffer *gbuffer)
{
	return gbuffer->main_tex;
}

gfx_texture* gfx_get_gbuffer_buf1(gfx_gbuffer *gbuffer)
{
	return gbuffer->buf1_tex;
}

gfx_texture* gfx_get_gbuffer_buf2(gfx_gbuffer *gbuffer)
{
	return gbuffer->buf2_tex;
}

gfx_texture* gfx_get_gbuffer_buf3(gfx_gbuffer *gbuffer)
{
	return gbuffer->buf3_tex;
}

