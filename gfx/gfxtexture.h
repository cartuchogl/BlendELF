
int gfx_get_max_texture_size()
{
	return driver->max_texture_size;
}

gfx_texture* gfx_create_texture()
{
	gfx_texture *texture;

	texture = (gfx_texture*)malloc(sizeof(gfx_texture));
	memset(texture, 0x0, sizeof(gfx_texture));
	texture->obj_type = GFX_TEXTURE;
	texture->obj_destr = gfx_destroy_texture;

	gfx_inc_obj(GFX_TEXTURE);

	return texture;
}

gfx_texture* gfx_create_2d_texture(unsigned int width, unsigned int height, float anisotropy, int mode, int filter, int format, int internal_format, int data_format, void *data)
{
	gfx_texture *texture;

	if(driver->version < 130) return NULL;

	if(width == 0 || height == 0 || (int)width > gfx_get_max_texture_size() || (int)height > gfx_get_max_texture_size())
	{
		printf("error: invalid dimensions when creating texture\n");
		return NULL;
	}

	if(!(format >= GFX_LUMINANCE && format < GFX_MAX_TEXTURE_FORMATS))
	{
		printf("error: invalid format when creating texture\n");
		return NULL;
	}

	if(!(data_format >= GFX_FLOAT && data_format < GFX_MAX_FORMATS))
	{
		printf("error: invalid data format when creating texture\n");
		return NULL;
	}

	texture = gfx_create_texture();

	texture->type = GFX_2D_MAP_TEXTURE;
	texture->width = width;
	texture->height = height;
	texture->format = format;
	texture->data_format = data_format;

	glActiveTexture(GL_TEXTURE0);
	glClientActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &texture->id);

	glBindTexture(GL_TEXTURE_2D, texture->id);

	if(data && filter != GFX_NEAREST)
	{
		if(driver->version >= 140)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if(filter != GFX_NEAREST)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	if(mode == GFX_REPEAT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	if(anisotropy > 1.0 && driver->version >= 200)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, driver->texture_internal_formats[internal_format], width, height, 0,
		driver->texture_data_formats[format], driver->formats[data_format], data);

	glBindTexture(GL_TEXTURE_2D, 0);
	driver->shader_params.texture_params[0].texture = NULL;

	return texture;
}

gfx_texture* gfx_create_cube_map(unsigned int width, unsigned int height, float anisotropy, int mode, int filter, int format, int internal_format, int data_format, void *xpos, void *xneg, void *ypos, void *yneg, void *zpos, void *zneg)
{
	gfx_texture *texture;

	if(width == 0 || height == 0 || (int)width > gfx_get_max_texture_size() || (int)height > gfx_get_max_texture_size())
	{
		printf("error: invalid dimensions when creating texture\n");
		return NULL;
	}

	if(!(format >= GFX_LUMINANCE && format < GFX_MAX_TEXTURE_FORMATS))
	{
		printf("error: invalid format when creating texture\n");
		return NULL;
	}

	if(!(data_format >= GFX_FLOAT && data_format < GFX_MAX_FORMATS))
	{
		printf("error: invalid data format when creating texture\n");
		return NULL;
	}

	texture = gfx_create_texture();

	texture->type = GFX_CUBE_MAP_TEXTURE;
	texture->width = width;
	texture->height = height;
	texture->format = format;
	texture->data_format = data_format;

	glActiveTexture(GL_TEXTURE0);
	glClientActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &texture->id);

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, driver->texture_internal_formats[internal_format], width, height, 0,
		driver->texture_data_formats[format], driver->formats[data_format], xpos);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, driver->texture_internal_formats[internal_format], width, height, 0,
		driver->texture_data_formats[format], driver->formats[data_format], xneg);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, driver->texture_internal_formats[internal_format], width, height, 0,
		driver->texture_data_formats[format], driver->formats[data_format], ypos);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, driver->texture_internal_formats[internal_format], width, height, 0,
		driver->texture_data_formats[format], driver->formats[data_format], yneg);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, driver->texture_internal_formats[internal_format], width, height, 0,
		driver->texture_data_formats[format], driver->formats[data_format], zpos);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, driver->texture_internal_formats[internal_format], width, height, 0,
		driver->texture_data_formats[format], driver->formats[data_format], zneg);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	driver->shader_params.texture_params[0].texture = NULL;

	return texture;
}

void gfx_destroy_texture(void *data)
{
	gfx_texture *texture = (gfx_texture*)data;

	if(texture->id) glDeleteTextures(1, &texture->id);

	free(texture);

	gfx_dec_obj(GFX_TEXTURE);

}

int gfx_get_texture_type(gfx_texture *texture)
{
	return texture->type;
}

int gfx_get_texture_width(gfx_texture *texture)
{
	return texture->width;
}

int gfx_get_texture_height(gfx_texture *texture)
{
	return texture->height;
}

int gfx_get_texture_format(gfx_texture *texture)
{
	return texture->format;
}

int gfx_get_texture_data_format(gfx_texture *texture)
{
	return texture->data_format;
}

void gfx_copy_framebuffer_to_texture(gfx_texture *texture)
{
	glActiveTexture(GL_TEXTURE0);
	glClientActiveTexture(GL_TEXTURE0);
	if(!glIsEnabled(GL_TEXTURE_2D)) glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, texture->width, texture->height);
}

