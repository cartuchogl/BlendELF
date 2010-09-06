
void gfx_set_color(gfx_color *color, float r, float g, float b, float a)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
}

void gfx_set_shader_params_default(gfx_shader_params *shader_params)
{
	int i;

	memset(shader_params, 0x0, sizeof(gfx_shader_params));

	shader_params->render_params.depth_test = GFX_TRUE;
	shader_params->render_params.depth_write = GFX_TRUE;
	shader_params->render_params.depth_func = GFX_LESS;
	shader_params->render_params.color_write = GFX_TRUE;
	shader_params->render_params.alpha_write = GFX_TRUE;
	shader_params->render_params.alpha_threshold = 0.99;
	shader_params->render_params.cull_face = GFX_TRUE;
	shader_params->render_params.line_width = 1.0;
	shader_params->render_params.cull_face_mode = GFX_BACK;
	shader_params->render_params.front_face = GFX_COUNTER_CLOCK_WISE;

	gfx_set_color(&shader_params->material_params.diffuse_color, 1.0, 1.0, 1.0, 1.0);
	gfx_set_color(&shader_params->material_params.specular_color, 1.0, 1.0, 1.0, 1.0);

	for(i = 0; i < GFX_MAX_TEXTURES; i++)
	{
		shader_params->texture_params[i].type = GFX_COLOR_MAP;
		shader_params->texture_params[i].texture = NULL;
		shader_params->texture_params[i].projection_mode = GFX_NONE;
		gfx_matrix4_set_identity(shader_params->texture_params[i].matrix);
	}

	gfx_matrix4_set_identity(shader_params->projection_matrix);
	gfx_matrix4_set_identity(shader_params->inv_projection_matrix);
	gfx_matrix4_set_identity(shader_params->modelview_matrix);

	shader_params->shader_program = NULL;
}

void gfx_set_material_params_default(gfx_shader_params *shader_params)
{
	gfx_set_color(&shader_params->material_params.diffuse_color, 1.0, 1.0, 1.0, 1.0);
	gfx_set_color(&shader_params->material_params.specular_color, 1.0, 1.0, 1.0, 1.0);
	shader_params->material_params.shininess = 0.0;
}

void gfx_set_texture_params_default(gfx_shader_params *shader_params)
{
	int i;

	for(i = 0; i < GFX_MAX_TEXTURES; i++)
	{
		shader_params->texture_params[i].type = GFX_COLOR_MAP;
		shader_params->texture_params[i].texture = NULL;
		shader_params->texture_params[i].projection_mode = GFX_NONE;
		shader_params->texture_params[i].parallax_scale = 0.25;
		gfx_matrix4_set_identity(shader_params->texture_params[i].matrix);
	}
}

void gfx_set_shader_params(gfx_shader_params *shader_params)
{
	int i;
	gfx_shader_config shader_config;
	gfx_shader_program *shader_program;

	if(memcmp(&driver->shader_params.render_params, &shader_params->render_params, sizeof(gfx_render_params)))
	{
		if(shader_params->render_params.depth_test) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);

		if(shader_params->render_params.depth_write) glDepthMask(1);
		else glDepthMask(0);

		switch(shader_params->render_params.depth_func)
		{
			case GFX_NEVER: glDepthFunc(GL_NEVER); break;
			case GFX_LESS: glDepthFunc(GL_LESS); break;
			case GFX_EQUAL: glDepthFunc(GL_EQUAL); break;
			case GFX_LEQUAL: glDepthFunc(GL_LEQUAL); break;
			case GFX_GREATER: glDepthFunc(GL_GREATER); break;
			case GFX_NOTEQUAL: glDepthFunc(GL_NOTEQUAL); break;
			case GFX_GEQUAL: glDepthFunc(GL_GEQUAL); break;
			case GFX_ALWAYS: glDepthFunc(GL_ALWAYS); break;
		}

		glColorMask(shader_params->render_params.color_write,
			shader_params->render_params.color_write,
			shader_params->render_params.color_write,
			shader_params->render_params.alpha_write);

		if(shader_params->render_params.cull_face) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

		if(shader_params->render_params.alpha_test)
		{
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, shader_params->render_params.alpha_threshold);
		}
		else glDisable(GL_ALPHA_TEST);

		switch(shader_params->render_params.blend_mode)
		{
			case GFX_NONE:
				glDisable(GL_BLEND);
				break;
			case GFX_TRANSPARENT:
				glEnable(GL_BLEND);
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
			case GFX_ADD:
				glEnable(GL_BLEND);
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_ONE, GL_ONE);
				break;
			case GFX_MULTIPLY:
				glEnable(GL_BLEND);
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_DST_COLOR, GL_ZERO);
				break;
			case GFX_SUBTRACT:
				glEnable(GL_BLEND);
				glBlendEquation(GL_FUNC_SUBTRACT);
				glBlendFunc(GL_ONE, GL_ONE);
				break;
		}

		if(!shader_params->render_params.offset_scale ||
			!shader_params->render_params.offset_bias)
			glDisable(GL_POLYGON_OFFSET_FILL);
		else
		{
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(shader_params->render_params.offset_scale,
				shader_params->render_params.offset_bias);
		}

		glLineWidth(shader_params->render_params.line_width);
		if(shader_params->render_params.line_smooth)
			glEnable(GL_LINE_SMOOTH);
		else glDisable(GL_LINE_SMOOTH);

		if(shader_params->render_params.cull_face_mode == GFX_BACK)
			glCullFace(GL_BACK);
		else glCullFace(GL_FRONT);

		if(shader_params->render_params.front_face == GFX_COUNTER_CLOCK_WISE)
			glFrontFace(GL_CCW);
		else glFrontFace(GL_CW);

		if(shader_params->render_params.wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if(driver->version < 200)
	{
		if(memcmp(&driver->shader_params.texture_params, &shader_params->texture_params, sizeof(gfx_texture_params)*GFX_MAX_TEXTURES))
		{
			for(i = 0; i < GFX_MAX_TEXTURES; i++)
			{
				glActiveTexture(GL_TEXTURE0_ARB+i);
				glClientActiveTexture(GL_TEXTURE0_ARB+i);

				if(shader_params->texture_params[i].texture &&
					(shader_params->texture_params[i].type == GFX_COLOR_MAP ||
					shader_params->texture_params[i].type == GFX_LIGHT_MAP ||
					shader_params->texture_params[i].type == GFX_SHADOW_MAP))
				{
					if(!glIsEnabled(GL_TEXTURE_2D)) glEnable(GL_TEXTURE_2D);

					glBindTexture(GL_TEXTURE_2D, shader_params->texture_params[i].texture->id);

					if(shader_params->texture_params[i].type == GFX_SHADOW_MAP)
					{
						glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
						glTexGenfv(GL_S, GL_EYE_PLANE, &shader_params->texture_params[i].matrix[0]);
						glEnable(GL_TEXTURE_GEN_S);

						glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
						glTexGenfv(GL_T, GL_EYE_PLANE, &shader_params->texture_params[i].matrix[4]);
						glEnable(GL_TEXTURE_GEN_T);

						glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
						glTexGenfv(GL_R, GL_EYE_PLANE, &shader_params->texture_params[i].matrix[8]);
						glEnable(GL_TEXTURE_GEN_R);

						glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
						glTexGenfv(GL_Q, GL_EYE_PLANE, &shader_params->texture_params[i].matrix[12]);
						glEnable(GL_TEXTURE_GEN_Q);
					}
					else
					{
						glDisable(GL_TEXTURE_GEN_S);
						glDisable(GL_TEXTURE_GEN_T);
						glDisable(GL_TEXTURE_GEN_R);
						glDisable(GL_TEXTURE_GEN_Q);
					}

					if(shader_params->texture_params[i].projection_mode == GFX_SHADOW_PROJECTION)
					{
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
					}
					else
					{
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
					}
				}
				else
				{
					glDisable(GL_TEXTURE_2D);
				}
			}
		}

		if(memcmp(&driver->shader_params.fog_params, &shader_params->fog_params, sizeof(gfx_fog_params)))
		{
			if(shader_params->fog_params.mode)
			{
				glEnable(GL_FOG);
				glFogi(GL_FOG_MODE, GL_LINEAR);
				glFogf(GL_FOG_START, shader_params->fog_params.start);
				glFogf(GL_FOG_END, shader_params->fog_params.start);
				glFogfv(GL_FOG_COLOR, &shader_params->fog_params.color.r);
			}
			else
			{
				glDisable(GL_FOG);
			}
		}

		if(memcmp(&driver->shader_params.light_params, &shader_params->light_params, sizeof(gfx_light_params)))
		{
			if(shader_params->light_params.type)
			{
				float position[4];

				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);

				glLightfv(GL_LIGHT0, GL_DIFFUSE, &shader_params->light_params.color.r);
				glLightfv(GL_LIGHT0, GL_SPECULAR, &shader_params->light_params.color.r);
				glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0/(shader_params->light_params.distance+1.0/shader_params->light_params.fade_speed));

				if(shader_params->light_params.type != GFX_SPOT_LIGHT)
				{
					glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
					glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
				}
				else
				{
					glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, shader_params->light_params.outer_cone);
					glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, shader_params->light_params.inner_cone);
					glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, &shader_params->light_params.direction.x);
				}

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				if(shader_params->light_params.type == GFX_SUN_LIGHT)
				{
					memcpy(position, &shader_params->light_params.direction.x, sizeof(float)*3);
					position[3] = 1.0;
				}
				else
				{
					memcpy(position, &shader_params->light_params.position.x, sizeof(float)*3);
					position[3] = 0.0;
				}

				glLightfv(GL_LIGHT0, GL_POSITION, position);
			}
			else
			{
				glDisable(GL_LIGHTING);
			}
		}

		if(memcmp(&driver->shader_params.material_params, &shader_params->material_params, sizeof(gfx_material_params)))
		{
			glColor4f(shader_params->material_params.diffuse_color.r,
				shader_params->material_params.diffuse_color.g,
				shader_params->material_params.diffuse_color.b,
				shader_params->material_params.diffuse_color.a);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, &shader_params->material_params.diffuse_color.r);
			glMaterialfv(GL_FRONT, GL_SPECULAR, &shader_params->material_params.specular_color.r);
			glMaterialf(GL_FRONT, GL_DIFFUSE, shader_params->material_params.shininess);
		}

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(shader_params->projection_matrix);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(shader_params->modelview_matrix);
	}
	else
	{
		if(memcmp(&driver->shader_params.texture_params, &shader_params->texture_params, sizeof(gfx_texture_params)*GFX_MAX_TEXTURES))
		{
			for(i = 0; i < GFX_MAX_TEXTURES; i++)
			{
				glActiveTexture(GL_TEXTURE0+i);
				glClientActiveTexture(GL_TEXTURE0+i);

				if(shader_params->texture_params[i].texture)
				{
					glBindTexture(GL_TEXTURE_2D, shader_params->texture_params[i].texture->id);

					switch(shader_params->texture_params[i].projection_mode)
					{
						case GFX_NONE:
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
							break;
						case GFX_SHADOW_PROJECTION:
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
							break;
					}
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}
			}
		}

		shader_program = shader_params->shader_program;

		if(shader_program)
		{
			if(shader_program != driver->shader_params.shader_program)
				glUseProgram(shader_program->id);

			// just inputting with values that do not make sense
			driver->shader_config.textures = 255;
			driver->shader_config.light = 255;
		}
		else
		{
			gfx_get_shader_program_config(shader_params, &shader_config);
			if(memcmp(&driver->shader_config, &shader_config, sizeof(gfx_shader_config)))
			{
				memcpy(&driver->shader_config, &shader_config, sizeof(gfx_shader_config));
				if(shader_params->gbuffer_mode > 0) shader_program = gfx_get_gbuf_shader_program(&shader_config);
				else shader_program = gfx_get_shader_program(&shader_config);
				if(shader_program) glUseProgram(shader_program->id);
				else return;
			}
			else
			{
				shader_program = driver->shader_params.shader_program;
			}
		}

		if(shader_program->projection_matrix_loc != -1)
			glUniformMatrix4fv(shader_program->projection_matrix_loc,
				1, GL_FALSE, shader_params->projection_matrix);
		if(shader_program->inv_projection_matrix_loc != -1)
			glUniformMatrix4fv(shader_program->inv_projection_matrix_loc,
				1, GL_FALSE, shader_params->inv_projection_matrix);
		if(shader_program->modelview_matrix_loc != -1)
			glUniformMatrix4fv(shader_program->modelview_matrix_loc,
				1, GL_FALSE, shader_params->modelview_matrix);

		if(shader_program->fog_start_loc != -1)
			glUniform1f(shader_program->fog_start_loc, shader_params->fog_params.start);
		if(shader_program->fog_end_loc != -1)
			glUniform1f(shader_program->fog_end_loc, shader_params->fog_params.end);
		if(shader_program->fog_color_loc != -1)
			glUniform3fv(shader_program->fog_color_loc, 1, &shader_params->fog_params.color.r);

		if(shader_program->ambient_color_loc != -1)
			glUniform4fv(shader_program->ambient_color_loc, 1, &shader_params->material_params.ambient_color.r);
		if(shader_program->diffuse_color_loc != -1)
			glUniform4fv(shader_program->diffuse_color_loc, 1, &shader_params->material_params.diffuse_color.r);
		if(shader_program->specular_color_loc != -1)
			glUniform3fv(shader_program->specular_color_loc, 1, &shader_params->material_params.specular_color.r);
		if(shader_program->shininess_loc != -1)
			glUniform1f(shader_program->shininess_loc, shader_params->material_params.shininess);

		if(shader_program->texture0_loc != -1)
			glUniform1i(shader_program->texture0_loc, 0);
		if(shader_program->texture1_loc != -1)
			glUniform1i(shader_program->texture1_loc, 1);
		if(shader_program->texture2_loc != -1)
			glUniform1i(shader_program->texture2_loc, 2);
		if(shader_program->texture3_loc != -1)
			glUniform1i(shader_program->texture3_loc, 3);
		if(shader_program->alpha_threshold_loc != -1)
			glUniform1f(shader_program->alpha_threshold_loc, shader_params->render_params.alpha_threshold);

		for(i = 0; i < GFX_MAX_TEXTURES; i++)
		{
			if(shader_params->texture_params[i].texture)
			{
				switch(shader_params->texture_params[i].type)
				{
					case GFX_COLOR_MAP:
						if(shader_program->color_map_loc != -1)
							glUniform1i(shader_program->color_map_loc, i);
						break;
					case GFX_NORMAL_MAP:
						if(shader_program->normal_map_loc != -1)
							glUniform1i(shader_program->normal_map_loc, i);
						break;
					case GFX_HEIGHT_MAP:
						if(shader_program->parallax_scale_loc != -1)
							glUniform1f(shader_program->parallax_scale_loc, shader_params->texture_params[i].parallax_scale);
						if(shader_program->height_map_loc != -1)
							glUniform1i(shader_program->height_map_loc, i);
						break;
					case GFX_SPECULAR_MAP:
						if(shader_program->specular_map_loc != -1)
							glUniform1i(shader_program->specular_map_loc, i);
						break;
					case GFX_COLOR_RAMP_MAP:
						if(shader_program->color_ramp_map_loc != -1)
							glUniform1i(shader_program->color_ramp_map_loc, i);
						break;
					case GFX_LIGHT_MAP:
						if(shader_program->light_map_loc != -1)
							glUniform1i(shader_program->light_map_loc, i);
						break;
					case GFX_SHADOW_MAP:
						if(shader_program->shadow_map_loc != -1)
							glUniform1i(shader_program->shadow_map_loc, i);
						if(shader_program->shadow_projection_matrix_loc != -1)
							glUniformMatrix4fv(shader_program->shadow_projection_matrix_loc,
								1, GL_FALSE, shader_params->texture_params[i].matrix);
						break;
				}
			}
		}

		if(shader_params->light_params.type)
		{
			if(shader_program->light_position_loc != -1)
				glUniform3fv(shader_program->light_position_loc, 1, &shader_params->light_params.position.x);
			if(shader_program->light_color_loc != -1)
				glUniform3fv(shader_program->light_color_loc, 1, &shader_params->light_params.color.r);
			if(shader_program->light_distance_loc != -1)
				glUniform1f(shader_program->light_distance_loc, shader_params->light_params.distance);
			if(shader_program->light_fade_speed_loc != -1)
				glUniform1f(shader_program->light_fade_speed_loc, shader_params->light_params.fade_speed);
			if(shader_program->light_spot_direction_loc != -1)
				glUniform3fv(shader_program->light_spot_direction_loc, 1, &shader_params->light_params.direction.x);
			if(shader_program->light_inner_cone_cos_loc != -1)
				glUniform1f(shader_program->light_inner_cone_cos_loc, (float)cos(shader_params->light_params.inner_cone*GFX_PI_DIV_180));
			if(shader_program->light_outer_cone_cos_loc != -1)
				glUniform1f(shader_program->light_outer_cone_cos_loc, (float)cos((shader_params->light_params.inner_cone+shader_params->light_params.outer_cone)*GFX_PI_DIV_180));
		}
	
		if(shader_program->clip_start_loc != -1)
			glUniform1f(shader_program->clip_start_loc, shader_params->clip_start);
		if(shader_program->clip_end_loc != -1)
			glUniform1f(shader_program->clip_end_loc, shader_params->clip_end);
		if(shader_program->viewport_width_loc != -1)
			glUniform1i(shader_program->viewport_width_loc, shader_params->viewport_width);
		if(shader_program->viewport_height_loc != -1)
			glUniform1i(shader_program->viewport_height_loc, shader_params->viewport_height);
	}

	memcpy(&driver->shader_params, shader_params, sizeof(gfx_shader_params));
	driver->shader_params.shader_program = shader_program;
}

