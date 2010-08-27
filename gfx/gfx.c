
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <malloc.h>
#include <sys/types.h>

#include <GL/glew.h>
#ifdef ELF_MACOSX
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include "gfx.h"

gfx_general *gfx_gen = NULL;
gfx_driver *driver = NULL;

extern void elf_write_to_log(const char *fmt, ...);

#include "gfxtypes.h"
#include "gfxgeneral.h"
#include "gfxmath.h"
#include "gfxtransform.h"
#include "gfxvertexarray.h"
#include "gfxtexture.h"
#include "gfxshaderprogram.h"
#include "gfxshadergen.h"
#include "gfxrendertarget.h"
#include "gfxshaderparams.h"
#include "gfxquery.h"
#include "gfxgbuffer.h"
#include "gfxdraw.h"

unsigned char gfx_init()
{
	unsigned int *index_buffer;

	if(driver) return GFX_TRUE;

	gfx_gen = gfx_create_general();

	driver = (gfx_driver*)malloc(sizeof(gfx_driver));
	memset(driver, 0x0, sizeof(gfx_driver));

	driver->format_sizes[GFX_FLOAT] = sizeof(float);
	driver->format_sizes[GFX_INT] = sizeof(int);
	driver->format_sizes[GFX_UINT] = sizeof(unsigned int);
	driver->format_sizes[GFX_SHORT] = sizeof(short int);
	driver->format_sizes[GFX_USHORT] = sizeof(unsigned short int);
	driver->format_sizes[GFX_BYTE] = sizeof(char);
	driver->format_sizes[GFX_UBYTE] = sizeof(unsigned char);

	driver->formats[GFX_FLOAT] = GL_FLOAT;
	driver->formats[GFX_INT] = GL_INT;
	driver->formats[GFX_UINT] = GL_UNSIGNED_INT;
	driver->formats[GFX_SHORT] = GL_SHORT;
	driver->formats[GFX_USHORT] = GL_UNSIGNED_SHORT;
	driver->formats[GFX_BYTE] = GL_BYTE;
	driver->formats[GFX_UBYTE] = GL_UNSIGNED_BYTE;

	driver->draw_modes[GFX_POINTS] = GL_POINTS;
	driver->draw_modes[GFX_LINES] = GL_LINES;
	driver->draw_modes[GFX_LINE_LOOP] = GL_LINE_LOOP;
	driver->draw_modes[GFX_LINE_STRIP] = GL_LINE_STRIP;
	driver->draw_modes[GFX_TRIANGLES] = GL_TRIANGLES;
	driver->draw_modes[GFX_TRIANGLE_STRIP] = GL_TRIANGLE_STRIP;
	driver->draw_modes[GFX_TRIANGLE_FAN] = GL_TRIANGLE_FAN;

	driver->texture_internal_formats[GFX_LUMINANCE] = GL_LUMINANCE;
	driver->texture_internal_formats[GFX_LUMINANCE_ALPHA] = GL_LUMINANCE_ALPHA;
	driver->texture_internal_formats[GFX_RGB] = GL_RGB;
	driver->texture_internal_formats[GFX_RGBA] = GL_RGBA;
	driver->texture_internal_formats[GFX_BGR] = GL_BGR;
	driver->texture_internal_formats[GFX_BGRA] = GL_BGRA;
	driver->texture_internal_formats[GFX_RGB16F] = GL_RGB16F_ARB;
	driver->texture_internal_formats[GFX_RGB32F] = GL_RGB32F_ARB;
	driver->texture_internal_formats[GFX_RGBA16F] = GL_RGBA16F_ARB;
	driver->texture_internal_formats[GFX_RGBA32F] = GL_RGBA32F_ARB;
	driver->texture_internal_formats[GFX_COMPRESSED_RGB] = GL_COMPRESSED_RGB;
	driver->texture_internal_formats[GFX_COMPRESSED_RGBA] = GL_COMPRESSED_RGBA;
	driver->texture_internal_formats[GFX_DEPTH_COMPONENT] = GL_DEPTH_COMPONENT;
	driver->texture_internal_formats[GFX_R] = GL_R;
	driver->texture_internal_formats[GFX_RG] = GL_RG;
	driver->texture_internal_formats[GFX_R16F] = GL_R16F;
	driver->texture_internal_formats[GFX_R32F] = GL_R32F;
	driver->texture_internal_formats[GFX_RG16F] = GL_RG16F;
	driver->texture_internal_formats[GFX_RG32F] = GL_RG32F;

	driver->texture_data_formats[GFX_LUMINANCE] = GL_LUMINANCE;
	driver->texture_data_formats[GFX_LUMINANCE_ALPHA] = GL_LUMINANCE_ALPHA;
	driver->texture_data_formats[GFX_RGB] = GL_RGB;
	driver->texture_data_formats[GFX_RGBA] = GL_RGBA;
	driver->texture_data_formats[GFX_BGR] = GL_BGR;
	driver->texture_data_formats[GFX_BGRA] = GL_BGRA;
	driver->texture_data_formats[GFX_RGB16F] = GL_RGB;
	driver->texture_data_formats[GFX_RGB32F] = GL_RGB;
	driver->texture_data_formats[GFX_RGBA16F] = GL_RGBA;
	driver->texture_data_formats[GFX_RGBA32F] = GL_RGBA;
	driver->texture_data_formats[GFX_COMPRESSED_RGB] = GL_RGB;
	driver->texture_data_formats[GFX_COMPRESSED_RGBA] = GL_RGBA;
	driver->texture_data_formats[GFX_DEPTH_COMPONENT] = GL_DEPTH_COMPONENT;
	driver->texture_data_formats[GFX_R] = GL_R;
	driver->texture_data_formats[GFX_RG] = GL_RG;
	driver->texture_data_formats[GFX_R16F] = GL_R;
	driver->texture_data_formats[GFX_R32F] = GL_R;
	driver->texture_data_formats[GFX_RG16F] = GL_RG;
	driver->texture_data_formats[GFX_RG32F] = GL_RG;

	driver->vertex_data_draw_modes[GFX_VERTEX_DATA_STATIC] = GL_STATIC_DRAW;
	driver->vertex_data_draw_modes[GFX_VERTEX_DATA_DYNAMIC] = GL_DYNAMIC_DRAW;

	// just inputting with values that do not make sense
	driver->shader_config.textures = 255;
	driver->shader_config.light = 255;

	glewInit();

	if(glewIsSupported("GL_VERSION_1_1")) driver->version = 110;
	if(glewIsSupported("GL_VERSION_1_4")) driver->version = 140;
	if(glewIsSupported("GL_VERSION_1_5")) driver->version = 150;
	if(glewIsSupported("GL_VERSION_2_0")) driver->version = 200;
	if(glewIsSupported("GL_VERSION_2_1")) driver->version = 210;
	if(glewIsSupported("GL_VERSION_3_0")) driver->version = 300;
	if(glewIsSupported("GL_VERSION_3_1")) driver->version = 310;
	if(glewIsSupported("GL_VERSION_3_2")) driver->version = 320;
	if(glewIsSupported("GL_VERSION_3_3")) driver->version = 330;
	if(glewIsSupported("GL_VERSION_4_0")) driver->version = 400;

	if(driver->version >= 200)
	{
		driver->gpu_data = GFX_TRUE;
	}

	if(driver->version < 200)
	{
		elf_write_to_log("OpenGL version 2.0 not supported!\n");
		return GFX_FALSE;
	}

	if(!glewIsSupported("GL_EXT_framebuffer_object"))
	{
		elf_write_to_log("GL_EXT_framebuffer_object not supported!\n");
		return GFX_FALSE;
	}

	// checks for deferred rendering

	/*if(!glewIsSupported("GL_ARB_texture_float"))
	{
		elf_write_to_log("GL_ARB_texture_float not supported!\n");
		return GFX_FALSE;
	}


	if(!glewIsSupported("GL_ARB_texture_rg"))
	{
		elf_write_to_log("GL_ARB_texture_rg not supported!\n");
		return GFX_FALSE;
	}*/

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &driver->max_texture_size);
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &driver->max_texture_image_units);
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &driver->max_draw_buffers);
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &driver->max_color_attachments);
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &driver->max_anisotropy);

	elf_write_to_log("OpenGL %s; %s; %s\n", glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);

	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	driver->quad_vertex_data = gfx_create_vertex_data(12, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
	driver->quad_tex_coord_data = gfx_create_vertex_data(12, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
	driver->quad_normal_data = gfx_create_vertex_data(12, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
	driver->quad_vertex_array = gfx_create_vertex_array(GFX_FALSE);

	gfx_inc_ref((gfx_object*)driver->quad_vertex_data);
	gfx_inc_ref((gfx_object*)driver->quad_normal_data);
	gfx_inc_ref((gfx_object*)driver->quad_tex_coord_data);
	gfx_inc_ref((gfx_object*)driver->quad_vertex_array);

	gfx_set_vertex_array_data(driver->quad_vertex_array, GFX_VERTEX, driver->quad_vertex_data);
	gfx_set_vertex_array_data(driver->quad_vertex_array, GFX_NORMAL, driver->quad_normal_data);
	gfx_set_vertex_array_data(driver->quad_vertex_array, GFX_TEX_COORD, driver->quad_tex_coord_data);

	driver->bb_vertex_data = gfx_create_vertex_data(24, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
	driver->bb_index_data = gfx_create_vertex_data(36, GFX_UINT, GFX_VERTEX_DATA_STATIC);
	driver->bb_vertex_array = gfx_create_vertex_array(GFX_FALSE);
	driver->bb_vertex_index = gfx_create_vertex_index(GFX_FALSE, driver->bb_index_data);

	gfx_inc_ref((gfx_object*)driver->bb_vertex_data);
	gfx_inc_ref((gfx_object*)driver->bb_index_data);
	gfx_inc_ref((gfx_object*)driver->bb_vertex_array);
	gfx_inc_ref((gfx_object*)driver->bb_vertex_index);

	index_buffer = (unsigned int*)gfx_get_vertex_data_buffer(driver->bb_index_data);

	index_buffer[0] = 0;
	index_buffer[1] = 1;
	index_buffer[2] = 2;
	index_buffer[3] = 2;
	index_buffer[4] = 1;
	index_buffer[5] = 3;
	index_buffer[6] = 2;
	index_buffer[7] = 3;
	index_buffer[8] = 4;
	index_buffer[9] = 4;
	index_buffer[10] = 3;
	index_buffer[11] = 5;
	index_buffer[12] = 4;
	index_buffer[13] = 5;
	index_buffer[14] = 6;
	index_buffer[15] = 6;
	index_buffer[16] = 5;
	index_buffer[17] = 7;
	index_buffer[18] = 6;
	index_buffer[19] = 7;
	index_buffer[20] = 0;
	index_buffer[21] = 0;
	index_buffer[22] = 7;
	index_buffer[23] = 1;
	index_buffer[24] = 0;
	index_buffer[25] = 2;
	index_buffer[26] = 6;
	index_buffer[27] = 6;
	index_buffer[28] = 2;
	index_buffer[29] = 4;
	index_buffer[30] = 3;
	index_buffer[31] = 1;
	index_buffer[32] = 5;
	index_buffer[33] = 5;
	index_buffer[34] = 1;
	index_buffer[35] = 7;

	gfx_set_vertex_array_data(driver->bb_vertex_array, GFX_VERTEX, driver->bb_vertex_data);

	driver->line_vertex_array = gfx_create_vertex_array(GFX_FALSE);
	gfx_inc_ref((gfx_object*)driver->line_vertex_array);

	driver->circle_vertex_data = gfx_create_vertex_data((GFX_MAX_CIRCLE_VERTICES+2)*3, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
	driver->circle_vertex_array = gfx_create_vertex_array(GFX_FALSE);

	gfx_inc_ref((gfx_object*)driver->circle_vertex_data);
	gfx_inc_ref((gfx_object*)driver->circle_vertex_array);

	gfx_set_vertex_array_data(driver->circle_vertex_array, GFX_VERTEX, driver->circle_vertex_data);

	driver->prev_circle_vertice_count = 0;

	return GFX_TRUE;
}

void gfx_deinit()
{
	if(!driver) return;

	if(driver->shader_programs) gfx_destroy_shader_programs(driver->shader_programs);

	gfx_dec_ref((gfx_object*)driver->quad_vertex_array);
	gfx_dec_ref((gfx_object*)driver->quad_vertex_data);
	gfx_dec_ref((gfx_object*)driver->quad_normal_data);
	gfx_dec_ref((gfx_object*)driver->quad_tex_coord_data);

	gfx_dec_ref((gfx_object*)driver->bb_vertex_data);
	gfx_dec_ref((gfx_object*)driver->bb_index_data);
	gfx_dec_ref((gfx_object*)driver->bb_vertex_array);
	gfx_dec_ref((gfx_object*)driver->bb_vertex_index);

	gfx_dec_ref((gfx_object*)driver->line_vertex_array);

	gfx_dec_ref((gfx_object*)driver->circle_vertex_data);
	gfx_dec_ref((gfx_object*)driver->circle_vertex_array);

	free(driver);
	driver = NULL;

	if(gfx_get_global_ref_count() > 0)
	{
		elf_write_to_log("error: possible memory leak in GFX, [%d] references not dereferenced\n",
			gfx_get_global_ref_count());
		gfx_dump_ref_table();
	}

	if(gfx_get_global_ref_count() < 0)
	{
		elf_write_to_log("error: possible double free in GFX, [%d] negative reference count\n",
			gfx_get_global_ref_count());
		gfx_dump_ref_table();
	}

	if(gfx_get_global_obj_count() > 0)
	{
		elf_write_to_log("error: possible memory leak in GFX, [%d] objects not destroyed\n",
			gfx_get_global_obj_count());
		gfx_dump_obj_table();
	}

	if(gfx_get_global_obj_count() < 0)
	{
		elf_write_to_log("error: possible double free in GFX, [%d] negative object count\n",
			gfx_get_global_obj_count());
		gfx_dump_obj_table();
	}

	gfx_destroy_general(gfx_gen);
}

void gfx_clear_buffers(float r, float g, float b, float a, float d)
{
	glClearColor(r, g, b, a);
	glClearDepth(d);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void gfx_clear_color_buffer(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void gfx_clear_depth_buffer(float d)
{
	glClearDepth(d);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void gfx_read_pixels(int x, int y, int width, int height, int format, int data_format, void *data)
{
	glReadPixels(x, y, width, height, driver->texture_data_formats[format], driver->formats[data_format], data);
}

void gfx_copy_frame_buffer(gfx_texture *texture, int ox, int oy, int x, int y, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, x, y, width, height);
	glBindTexture(GL_TEXTURE_2D, 0);
	driver->shader_params.texture_params[0].texture = NULL;
}

void gfx_reset_vertices_drawn()
{
	memset(driver->vertices_drawn, 0x0, sizeof(unsigned int)*GFX_MAX_DRAW_MODES);
	driver->vertices_drawn[GFX_TRIANGLES] = 0;
	driver->vertices_drawn[GFX_TRIANGLE_STRIP] = 0;
}

int gfx_get_vertices_drawn(unsigned int draw_mode)
{
	return driver->vertices_drawn[draw_mode];
}

void gfx_print_gl_error()
{
	GLenum err;

	err = glGetError();

	printf("%s\n", glewGetErrorString(err));
}

void gfx_set_scissor(int x, int y, int width, int height)
{
	glScissor(x, y, width, height);
	glEnable(GL_SCISSOR_TEST);
}

void gfx_disable_scissor()
{
	glDisable(GL_SCISSOR_TEST);
}

