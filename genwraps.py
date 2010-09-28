#!/usr/bin/python

decls = """#if defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
	#ifndef ELF_PLAYER
		#define ELF_APIENTRY __stdcall
		#ifdef ELF_DLL
				#define ELF_API __declspec(dllexport)
		#else
				#define ELF_API __declspec(dllimport)
		#endif
	#else
		#define ELF_API
		#define ELF_APIENTRY
	#endif
#else
	#define ELF_API
	#define ELF_APIENTRY
#endif
typedef struct elf_vec2i				elf_vec2i;
typedef struct elf_vec2f				elf_vec2f;
typedef struct elf_vec3f				elf_vec3f;
typedef struct elf_vec4f				elf_vec4f;
typedef struct elf_color				elf_color;
typedef struct elf_general				elf_general;
typedef struct elf_config				elf_config;
typedef struct elf_object				elf_object;
typedef struct elf_resource				elf_resource;
typedef struct elf_gui_object				elf_gui_object;
typedef struct elf_list					elf_list;
typedef struct elf_key_event				elf_key_event;
typedef struct elf_char_event				elf_char_event;
typedef struct elf_context				elf_context;
typedef struct elf_engine				elf_engine;
typedef struct elf_timer				elf_timer;
typedef struct elf_image				elf_image;
typedef struct elf_texture				elf_texture;
typedef struct elf_material				elf_material;
typedef struct elf_bezier_point				elf_bezier_point;
typedef struct elf_bezier_curve				elf_bezier_curve;
typedef struct elf_ipo					elf_ipo;
typedef struct elf_actor				elf_actor;
typedef struct elf_camera				elf_camera;
typedef struct elf_model				elf_model;
typedef struct elf_entity				elf_entity;
typedef struct elf_light				elf_light;
typedef struct elf_scene				elf_scene;
typedef struct elf_pak_index				elf_pak_index;
typedef struct elf_pak					elf_pak;
typedef struct elf_post_process				elf_post_process;
typedef struct elf_script				elf_script;
typedef struct elf_audio_device				elf_audio_device;
typedef struct elf_audio_source				elf_audio_source;
typedef struct elf_sound				elf_sound;
typedef struct elf_bone					elf_bone;
typedef struct elf_armature				elf_armature;
typedef struct elf_string				elf_string;
typedef struct elf_font					elf_font;
typedef struct elf_area					elf_area;
typedef struct elf_label				elf_label;
typedef struct elf_button				elf_button;
typedef struct elf_picture				elf_picture;
typedef struct elf_text_field				elf_text_field;
typedef struct elf_slider				elf_slider;
typedef struct elf_screen				elf_screen;
typedef struct elf_text_list				elf_text_list;
typedef struct elf_check_box				elf_check_box;
typedef struct elf_gui					elf_gui;
typedef struct elf_directory_item			elf_directory_item;
typedef struct elf_directory				elf_directory;
typedef struct elf_collision				elf_collision;
typedef struct elf_physics_tri_mesh			elf_physics_tri_mesh;
typedef struct elf_physics_object			elf_physics_object;
typedef struct elf_physics_world			elf_physics_world;
typedef struct elf_joint				elf_joint;
typedef struct elf_resources				elf_resources;
typedef struct elf_particle				elf_particle;
typedef struct elf_particles				elf_particles;
typedef struct elf_frame_player				elf_frame_player;
typedef struct elf_property				elf_property;
typedef struct elf_server				elf_server;
typedef struct elf_client				elf_client;
typedef struct elf_scripting				elf_scripting;
typedef struct elf_sprite				elf_sprite;
typedef struct elf_video_mode				elf_video_mode;
typedef struct elf_vertice				elf_vertice;
typedef struct elf_face					elf_face;
typedef struct elf_mesh_data				elf_mesh_data;
struct elf_vec2i {
	int x;
	int y;
};
struct elf_vec2f {
	float x;
	float y;
};
struct elf_vec3f {
	float x;
	float y;
	float z;
};
struct elf_vec4f {
	float x;
	float y;
	float z;
	float w;
};
struct elf_color {
	float r;
	float g;
	float b;
	float a;
};
"""

defs = """#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "gfx.h"
#include "blendelf.h"
#define LUA_ELF_USERDATA_HEADER \\
	unsigned char type
#define LUA_ELF_OBJECT				0x0001
#define LUA_ELF_VEC2I				0x0002
#define LUA_ELF_VEC2F				0x0002
#define LUA_ELF_VEC3F				0x0003
#define LUA_ELF_VEC4F				0x0004
#define LUA_ELF_COLOR				0x0005
typedef struct lua_elf_userdata			lua_elf_userdata;
typedef struct lua_elf_object			lua_elf_object;
typedef struct lua_elf_vec2i			lua_elf_vec2i;
typedef struct lua_elf_vec2f			lua_elf_vec2f;
typedef struct lua_elf_vec3f			lua_elf_vec3f;
typedef struct lua_elf_vec4f			lua_elf_vec4f;
typedef struct lua_elf_color			lua_elf_color;
struct lua_elf_userdata {
	LUA_ELF_USERDATA_HEADER;
};
struct lua_elf_object {
	LUA_ELF_USERDATA_HEADER;
	elf_object* object;
};
struct lua_elf_vec2i {
	LUA_ELF_USERDATA_HEADER;
	elf_vec2i val;
};
struct lua_elf_vec2f {
	LUA_ELF_USERDATA_HEADER;
	elf_vec2f val;
};
struct lua_elf_vec3f {
	LUA_ELF_USERDATA_HEADER;
	elf_vec3f val;
};
struct lua_elf_vec4f {
	LUA_ELF_USERDATA_HEADER;
	elf_vec4f val;
};
struct lua_elf_color {
	LUA_ELF_USERDATA_HEADER;
	elf_color val;
};
static int lua_elf_object__gc(lua_State* L)
{
	lua_elf_object *obj = (lua_elf_object*)lua_touserdata(L, 1);
	elf_dec_ref(obj->object);
	return 0;
}
static int lua_elf_vec2i__index(lua_State* L)
{
	lua_elf_vec2i *ud = (lua_elf_vec2i*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), \"x\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.x);
	}
	else if(!strcmp(lua_tostring(L, 2), \"y\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.y);
	}
	return 1;
}
static int lua_elf_vec2i__newindex(lua_State* L)
{
	lua_elf_vec2i *ud = (lua_elf_vec2i*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  \"x\"))
	{
		if(lua_isnumber(L, 3)) ud->val.x = (int)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec2i.x\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"y\"))
	{
		if(lua_isnumber(L, 3)) ud->val.y = (int)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec2i.y\");
	}
	return 0;
}
static int lua_elf_vec2f__index(lua_State* L)
{
	lua_elf_vec2f *ud = (lua_elf_vec2f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), \"x\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.x);
	}
	else if(!strcmp(lua_tostring(L, 2), \"y\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.y);
	}
	return 1;
}
static int lua_elf_vec2f__newindex(lua_State* L)
{
	lua_elf_vec2f *ud = (lua_elf_vec2f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  \"x\"))
	{
		if(lua_isnumber(L, 3)) ud->val.x = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec2f.x\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"y\"))
	{
		if(lua_isnumber(L, 3)) ud->val.y = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec2f.y\");
	}
	return 0;
}
static int lua_elf_vec3f__index(lua_State* L)
{
	lua_elf_vec3f *ud = (lua_elf_vec3f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), \"x\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.x);
	}
	else if(!strcmp(lua_tostring(L, 2), \"y\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.y);
	}
	else if(!strcmp(lua_tostring(L, 2), \"z\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.z);
	}
	return 1;
}
static int lua_elf_vec3f__newindex(lua_State* L)
{
	lua_elf_vec3f *ud = (lua_elf_vec3f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  \"x\"))
	{
		if(lua_isnumber(L, 3)) ud->val.x = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec3f.x\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"y\"))
	{
		if(lua_isnumber(L, 3)) ud->val.y = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec3f.y\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"z\"))
	{
		if(lua_isnumber(L, 3)) ud->val.z = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec3f.z\");
	}
	return 0;
}
static int lua_elf_vec4f__index(lua_State* L)
{
	lua_elf_vec4f *ud = (lua_elf_vec4f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), \"x\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.x);
	}
	else if(!strcmp(lua_tostring(L, 2), \"y\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.y);
	}
	else if(!strcmp(lua_tostring(L, 2), \"z\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.z);
	}
	else if(!strcmp(lua_tostring(L, 2), \"w\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.w);
	}
	return 1;
}
static int lua_elf_vec4f__newindex(lua_State* L)
{
	lua_elf_vec4f *ud = (lua_elf_vec4f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  \"x\"))
	{
		if(lua_isnumber(L, 3)) ud->val.x = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_color.x\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"y\"))
	{
		if(lua_isnumber(L, 3)) ud->val.y = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_color.y\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"z\"))
	{
		if(lua_isnumber(L, 3)) ud->val.z = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_color.z\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"w\"))
	{
		if(lua_isnumber(L, 3)) ud->val.w = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_color.w\");
	}
	return 0;
}
static int lua_elf_color__index(lua_State* L)
{
	lua_elf_color *ud = (lua_elf_color*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), \"r\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.r);
	}
	else if(!strcmp(lua_tostring(L, 2), \"g\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.g);
	}
	else if(!strcmp(lua_tostring(L, 2), \"b\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.b);
	}
	else if(!strcmp(lua_tostring(L, 2), \"a\"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.a);
	}
	return 1;
}
static int lua_elf_color__newindex(lua_State* L)
{
	lua_elf_color *ud = (lua_elf_color*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  \"r\"))
	{
		if(lua_isnumber(L, 3)) ud->val.r = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec4f.r\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"g\"))
	{
		if(lua_isnumber(L, 3)) ud->val.g = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec4f.g\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"b\"))
	{
		if(lua_isnumber(L, 3)) ud->val.b = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec4f.b\");
	}
	else if(!strcmp(lua_tostring(L, 2), \"a\"))
	{
		if(lua_isnumber(L, 3)) ud->val.a = (float)lua_tonumber(L, 3);
		else return luaL_error(L, \"Attemp to assign a non-number to elf_vec4f.a\");
	}
	return 0;
}
static const struct luaL_reg lua_elf_vec2i_mt[] = {
	{\"__index\", lua_elf_vec2i__index},
	{\"__newindex\", lua_elf_vec2i__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_vec2f_mt[] = {
	{\"__index\", lua_elf_vec2f__index},
	{\"__newindex\", lua_elf_vec2f__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_vec3f_mt[] = {
	{\"__index\", lua_elf_vec3f__index},
	{\"__newindex\", lua_elf_vec3f__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_vec4f_mt[] = {
	{\"__index\", lua_elf_vec4f__index},
	{\"__newindex\", lua_elf_vec4f__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_color_mt[] = {
	{\"__index\", lua_elf_color__index},
	{\"__newindex\", lua_elf_color__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_object_mt[] = {
	{"__gc", lua_elf_object__gc},
	{NULL, NULL}
};
void lua_create_elf_vec2i(lua_State* L, elf_vec2i vec)
{
	lua_elf_vec2i *ud;
	ud = (lua_elf_vec2i*)lua_newuserdata(L, sizeof(lua_elf_vec2i));
	ud->type = LUA_ELF_VEC2I;
	ud->val = vec;
	luaL_getmetatable(L, \"lua_elf_vec2i_mt\");
	lua_setmetatable(L, -2);
}
void lua_create_elf_vec2f(lua_State* L, elf_vec2f vec)
{
	lua_elf_vec2f *ud;
	ud = (lua_elf_vec2f*)lua_newuserdata(L, sizeof(lua_elf_vec2f));
	ud->type = LUA_ELF_VEC2F;
	ud->val = vec;
	luaL_getmetatable(L, \"lua_elf_vec2f_mt\");
	lua_setmetatable(L, -2);
}
void lua_create_elf_vec3f(lua_State* L, elf_vec3f vec)
{
	lua_elf_vec3f *ud;
	ud = (lua_elf_vec3f*)lua_newuserdata(L, sizeof(lua_elf_vec3f));
	ud->type = LUA_ELF_VEC3F;
	ud->val = vec;
	luaL_getmetatable(L, \"lua_elf_vec3f_mt\");
	lua_setmetatable(L, -2);
}
void lua_create_elf_vec4f(lua_State* L, elf_vec4f vec)
{
	lua_elf_vec4f *ud;
	ud = (lua_elf_vec4f*)lua_newuserdata(L, sizeof(lua_elf_vec4f));
	ud->type = LUA_ELF_VEC4F;
	ud->val = vec;
	luaL_getmetatable(L, \"lua_elf_vec4f_mt\");
	lua_setmetatable(L, -2);
}
void lua_create_elf_color(lua_State* L, elf_color col)
{
	lua_elf_color *ud;
	ud = (lua_elf_color*)lua_newuserdata(L, sizeof(lua_elf_color));
	ud->type = LUA_ELF_COLOR;
	ud->val = col;
	luaL_getmetatable(L, \"lua_elf_color_mt\");
	lua_setmetatable(L, -2);
}
void lua_create_elf_object(lua_State* L, elf_object* obj)
{
	lua_elf_object *ud;
	ud = (lua_elf_object*)lua_newuserdata(L, sizeof(lua_elf_object));
	ud->type = LUA_ELF_OBJECT;
	ud->object = obj;
	elf_inc_ref(ud->object);
	luaL_getmetatable(L, \"lua_elf_object_mt\");
	lua_setmetatable(L, -2);
}
int lua_fail_arg_count(lua_State* L, const char* func_name, int a, int b)
{
	return luaL_error(L, "%s: Got %d arguments instead of %d", a, b);
}
int lua_fail_arg(lua_State *L, const char* func_name, int idx, const char* etype)
{
	return luaL_error(L, "%s: Argument %d is not of type %s", func_name, idx, etype);
}
"""

apiheader = """<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<title>BlendELF, Lua API doc</title>
<link rel="stylesheet" type="text/css" href="style.css" />
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
<meta name="description" content="BlendELF, Compact and powerful 3D Game Engine" />
</head>
<body>

<div class="images">
<img src="images/topbanner.jpg" alt="Top Banner" />
</div>

<div class="links">
<a href="index.html">Home</a> | 
<a href="http://forum.blendelf.com">Forums</a> | 
<a href="http://blendelf.com/index.html#Demos">Demos</a> | 
<a href="http://blendelf.com/index.html#Features">Features</a> | 
<a href="http://blendelf.com/index.html#Devkit">Get Development Kit</a> | 
<a href="http://blendelf.com/index.html#Source">Source</a> | 
<a href="http://blendelf.com/index.html#Documentation">Documentation</a> | 
<a href="http://blendelf.com/index.html#License">License</a> | 
<a href="http://blendelf.com/index.html#IRC">IRC</a> | 
<a href="http://blendelf.com/index.html#Contact">Contact</a>
</div>

<div class="topic">BlendELF Lua API doc</div>
<div class="info">
This document contains all of the available functions for the BlendELF Lua API.
</div>

<div class="apitopic">BlendELF TYPES</div>
<div class="apiinfo">
<span class="apikeytype">float</span> - a floating point value, like 0.25 or 7.24
<br /><span class="apikeytype">double</span> - same as a floating poit value but can store more decimals
<br /><span class="apikeytype">int</span> - a positive or negative integer value, like 40 or -2500
<br /><span class="apikeytype">unsigned int</span> - a positive integer value, like 21 or 60
<br /><span class="apikeytype">bool</span> - a truth value, like true or false
<br /><span class="apikeytype">string</span> - a string of characters, like "cat" or "MyEntity"
<br /><span class="apikeytype">elf_vec2i</span> - contains the integer attributes [x|y] which can be accessed by vec.x and vec.y
<br /><span class="apikeytype">elf_vec2f</span> - contains the floating point attributes [x|y] which can be accessed by vec.x and vec.y
<br /><span class="apikeytype">elf_vec3f</span> - contains the floating point attributes [x|y|z] which can be accessed by vec.x, vec.y and vec.z
<br /><span class="apikeytype">elf_vec4f</span> - contains the floating point attributes [x|y|z|w] which can be accessed by vec.x, vec.y, vec.z and vec.w
<br /><span class="apikeytype">elf_color</span> - contains the floating point attributes [r|g|b|a] which can be accessed by col.r, col.g, col.b and col.a
<br /><span class="apiobjtype">object</span> - any BlendELF object other than the types listed above
</div>

"""

apifooter = """<div class="copyright">Copyright &copy; 2009-2010 Samuel Anjam</div>

<script type="text/javascript">
var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
</script>
<script type="text/javascript">
try {
var pageTracker = _gat._getTracker("UA-4880379-2");
pageTracker._trackPageview();
} catch(err) {}</script>

</body>
</html>"""

pretypes = ['unsigned',
	'signed',
	'const']

types = ['void',
	'char',
	'int',
	'float',
	'double',
	'unsigned int',
	'const char*',
	'bool']

elftypes = ['elf_vec2i',
	'elf_vec2f',
	'elf_vec3f',
	'elf_vec4f',
	'elf_color']

elfgenobjs = ['elf_object*',
	'elf_actor*',
	'elf_gui_object*']

elfobjs = ['elf_config*',
	'elf_object*',
	'elf_list*',
	'elf_handle*',
	'elf_script*',
	'elf_actor*',
	'elf_camera*',
	'elf_texture*',
	'elf_material*',
	'elf_model*',
	'elf_entity*',
	'elf_light*',
	'elf_bone*',
	'elf_armature*',
	'elf_scene*',
	'elf_collision*',
	'elf_joint*',
	'elf_font*',
	'elf_gui_object*',
	'elf_gui*',
	'elf_label*',
	'elf_button*',
	'elf_picture*',
	'elf_text_field*',
	'elf_slider*',
	'elf_screen*',
	'elf_text_list*',
	'elf_check_box*',
	'elf_timer*',
	'elf_resources*',
	'elf_particle*',
	'elf_particles*',
	'elf_bezier_point*',
	'elf_bezier_curve*',
	'elf_ipo*',
	'elf_frame_player*',
	'elf_sound*',
	'elf_audio_source*',
	'elf_property*',
	'elf_client*',
	'elf_sprite*',
	'elf_directory*',
	'elf_directory_item*',
	'elf_vertice*',
	'elf_face*',
	'elf_mesh_data*',
	'elf_image*']

defines = []
functions = []

class Define:
	def __init__(self):
		self.name = ''
		self.value = ''
		self.doc = ''
		self.mdoc = ''
		self.mdocc = ''

class Parameter:
	def __init__(self):
		self.type = ''
		self.orig_type = ''
		self.name = ''

class Function:
	def __init__(self):
		self.type = ''
		self.orig_type = ''
		self.name = ''
		self.orig_name = ''
		self.params = []
		self.doc = ''
		self.mdoc = ''
		self.mdocc = ''
	def dump(self):
		dstr = self.type+'['+self.orig_type+'] '+self.name+'['+self.orig_name+']('
		for param in self.params:
			dstr += param.type+'['+param.orig_type+'] '+param.name+', '
		dstr += ')'
		print dstr

def get_parts(line):
	tstr = ''
	parts = []
	for c in line:
		if c in ' \t\n#();,':
			if len(tstr) > 0: parts.append(tstr)
			tstr = ''
			continue
		tstr += c
	return parts

def get_name_in_caps(name):
	nname = ''
	start = True
	for c in name:
		if start == True:
			nname += c.upper()
			start = False
		else:
			if c == '_':
				start = True
				continue
			else:
				nname += c
	return nname

def get_doc(obj, parts):
	next = 0
	readdoc = False
	readmdoc = False
	readmdocc = False

	while next < len(parts):
		if parts[next] == '<doc>': readdoc = True; readmdoc = False; readmdocc = False
		elif parts[next] == '<mdoc>': readmdoc = True; readdoc = False; readmdocc = False
		elif parts[next] == '<mdocc>': readmdocc = True; readdoc = False; readmdoc = False
		else:
			if readdoc:
				if len(obj.doc) > 0: obj.doc += ' '+parts[next]
				else: obj.doc = parts[next]
			elif readmdoc:
				if len(obj.mdoc) > 0: obj.mdoc += ' '+parts[next]
				else: obj.mdoc = parts[next]
			elif readmdocc:
				if len(obj.mdocc) > 0: obj.mdocc += ' '+parts[next]
				else: obj.mdocc = parts[next]
		next += 1

def get_define(parts):
	define = Define()
	define.name = parts[1][4:]
	define.value = parts[2]

	get_doc(define, parts)

	return define

def get_function(parts):
	func = Function()

	next = 0;
	if parts[0] in pretypes:
		func.type = parts[0] + ' ' + parts[1]
		func.orig_type = func.type
		next = 2
	elif parts[0] in types or parts[0] in elftypes:
		func.type = parts[0]
		func.orig_type = func.type
		next = 1
	elif parts[0] in elfobjs:
		func.type = parts[0]
		func.orig_type = func.type
		next = 1
	else: return None

	func.name = get_name_in_caps(parts[next])[3:]
	func.orig_name = parts[next]
	next += 1

	while next < len(parts):
		param = Parameter()
		if parts[next] in pretypes:
			param.type = parts[next] + ' ' + parts[next+1]
			param.orig_type = param.type
			next += 2
		elif parts[next] in types or parts[next] in elftypes:
			param.type = parts[next]
			param.orig_type = param.type
			next += 1
		elif parts[next] in elfobjs:
			param.type = parts[next]
			param.orig_type = param.type
			next += 1
		elif parts[next] == '//': break;
		else: return None

		param.name = parts[next]
		next += 1

		func.params.append(param)

	get_doc(func, parts)

	return func

src = open('elf/blendelf.h')

skip = False
for line in src:
	parts = get_parts(line)
	if '<!>' in parts: continue
	if '<!!' in parts: skip = True
	if '!!>' in parts: skip = False
	if skip == True: continue
	if len(parts) > 0:
		if parts[0] == 'define':
			define = get_define(parts)
			defines.append(define)
		if parts[0] in pretypes or parts[0] in types or parts[0] in elftypes or parts[0] in elfobjs:
			func = get_function(parts)
			if func != None: functions.append(func)

src.close()

bindsh = open('gfx/blendelf.h', 'w')
bindsh.write('#ifndef ELF_BINDS_H\n#define ELF_BINDS_H\n')

for define in defines:
	bindsh.write('#define ELF_'+define.name+' '+define.value+'\n')

bindsh.write(decls)

for func in functions:
	bindsh.write('ELF_API '+func.type+' ELF_APIENTRY elf'+func.name+'(')
	for i in range(len(func.params)):
		bindsh.write(func.params[i].type+' '+func.params[i].name)
		if(i < len(func.params)-1): bindsh.write(', ')
	bindsh.write(');\n')

bindsh.write('#endif\n')
bindsh.close()

bindsc = open('elf/binds.c', 'w')

bindsc.write(defs)

for func in functions:
	bindsc.write('static int lua_'+func.name+'(lua_State *L)\n')
	bindsc.write('{\n')
	if func.type != 'void':
		bindsc.write('\t'+func.type+' result;\n')
	for i in range(len(func.params)):
		bindsc.write('\t'+func.params[i].type+' arg'+str(i)+';\n')
	bindsc.write('\tif(lua_gettop(L) != '+str(len(func.params))+') {return lua_fail_arg_count(L, \"'+func.name+'\", lua_gettop(L), '+str(len(func.params))+');}\n')
	for i in range(len(func.params)):
		if func.params[i].type == 'int':
			bindsc.write('\tif(!lua_isnumber(L, '+str(i+1)+')) {return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"number\");}\n')
		if func.params[i].type == 'float':
			bindsc.write('\tif(!lua_isnumber(L, '+str(i+1)+')) {return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"number\");}\n')
		if func.params[i].type == 'double':
			bindsc.write('\tif(!lua_isnumber(L, '+str(i+1)+')) {return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"number\");}\n')
		if func.params[i].type == 'unsigned char':
			bindsc.write('\tif(!lua_isboolean(L, '+str(i+1)+')) {return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"boolean\");}\n')
		if func.params[i].type == 'const char*':
			bindsc.write('\tif(!lua_isstring(L, '+str(i+1)+')) {return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"string\");}\n')
		if func.params[i].type in elfobjs:
			if func.params[i].type == 'elf_actor*':
				bindsc.write('\tif(!lua_isuserdata(L, '+str(i+1)+') || ((lua_elf_userdata*)lua_touserdata(L,'+str(i+1)+'))->type != LUA_ELF_OBJECT ||\n\t\t!elf_is_actor(((lua_elf_object*)lua_touserdata(L, '+str(i+1)+'))->object))\n\t\t{return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"'+func.params[i].type[:-1]+'\");}\n')
			elif func.params[i].type == 'elf_gui_object*':
				bindsc.write('\tif(!lua_isuserdata(L, '+str(i+1)+') || ((lua_elf_userdata*)lua_touserdata(L,'+str(i+1)+'))->type != LUA_ELF_OBJECT ||\n\t\t!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, '+str(i+1)+'))->object))\n\t\t{return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"'+func.params[i].type[:-1]+'\");}\n')
			elif func.params[i].type == 'elf_object*':
				bindsc.write('\tif(!lua_isuserdata(L, '+str(i+1)+') || ((lua_elf_userdata*)lua_touserdata(L,'+str(i+1)+'))->type != LUA_ELF_OBJECT)\n\t\t{return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"'+func.params[i].type[:-1]+'\");}\n')
			else:
				bindsc.write('\tif(!lua_isuserdata(L, '+str(i+1)+') || ((lua_elf_userdata*)lua_touserdata(L,'+str(i+1)+'))->type != LUA_ELF_OBJECT ||\n\t\telf_get_object_type(((lua_elf_object*)lua_touserdata(L, '+str(i+1)+'))->object) != '+func.params[i].type[:-1].upper()+')\n\t\t{return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"'+func.params[i].type[:-1]+'\");}\n')
		if func.params[i].type in elftypes:
			bindsc.write('\tif(!lua_isuserdata(L, '+str(i+1)+')) {return lua_fail_arg(L, \"'+func.name+'\", '+str(i+1)+', \"'+func.params[i].type+'\");}\n')
	for i in range(len(func.params)):
		if func.params[i].type == 'int':
			bindsc.write('\targ'+str(i)+' = (int)lua_tonumber(L, '+str(i+1)+');\n')
		elif func.params[i].type == 'float':
			bindsc.write('\targ'+str(i)+' = (float)lua_tonumber(L, '+str(i+1)+');\n')
		elif func.params[i].type == 'double':
			bindsc.write('\targ'+str(i)+' = lua_tonumber(L, '+str(i+1)+');\n')
		elif func.params[i].type == 'unsigned char':
			bindsc.write('\targ'+str(i)+' = (unsigned char)lua_toboolean(L, '+str(i+1)+');\n')
		elif func.params[i].type == 'const char*':
			bindsc.write('\targ'+str(i)+' = lua_tostring(L, '+str(i+1)+');\n')
		elif func.params[i].type in elfobjs:
			bindsc.write('\targ'+str(i)+' = ('+func.params[i].type+')((lua_elf_object*)lua_touserdata(L, '+str(i+1)+'))->object;\n')
		elif func.params[i].type in elftypes:
			bindsc.write('\targ'+str(i)+' = ((lua_'+func.params[i].type+'*)lua_touserdata(L, '+str(i+1)+'))->val;\n')
	if func.type != 'void':
		bindsc.write('\tresult = '+func.orig_name+'(')
	else: bindsc.write('\t'+func.orig_name+'(')
	for i in range(len(func.params)):
		if i != len(func.params)-1:
			bindsc.write('arg'+str(i)+', ')
		else: bindsc.write('arg'+str(i))
	bindsc.write(');\n')
	if func.type == 'int':
		bindsc.write('\tlua_pushnumber(L, (lua_Number)result);\n')
	elif func.type == 'float':
		bindsc.write('\tlua_pushnumber(L, (lua_Number)result);\n')
	elif func.type == 'double':
		bindsc.write('\tlua_pushnumber(L, (lua_Number)result);\n')
	elif func.type == 'unsigned char':
		bindsc.write('\tlua_pushboolean(L, result);\n')
	elif func.type == 'const char*':
		bindsc.write('\tlua_pushstring(L, result);\n')
	elif func.type in elfobjs:
		bindsc.write('\tif(result) lua_create_elf_object(L, (elf_object*)result);\n')
		bindsc.write('\telse lua_pushnil(L);\n')
	elif func.type in elftypes:
		bindsc.write('\tlua_create_'+func.type+'(L, result);\n')
	if func.type != 'void':
		bindsc.write('\treturn 1;\n')
	else: bindsc.write('\treturn 0;\n')
	bindsc.write('}\n')

bindsc.write('static const struct luaL_reg lua_elf_functions[] = {\n')
for func in functions:
	bindsc.write('\t{\"'+func.name+'\", lua_'+func.name+'},\n')
bindsc.write('\t{NULL, NULL}\n};\n')
bindsc.write('int luaopen_elf(lua_State* L)\n')
bindsc.write('{\n')
bindsc.write('\tlua_pushvalue(L, LUA_GLOBALSINDEX);\n')
bindsc.write('\tluaL_register(L, NULL, lua_elf_functions);\n')
for define in defines:
	bindsc.write('\tlua_pushstring(L, \"'+define.name+'\");\n')
	bindsc.write('\tlua_pushnumber(L, '+define.value+');\n')
	bindsc.write('\tlua_settable(L, -3);\n')
bindsc.write('\tlua_pop(L, 1);\n')
bindsc.write('\tluaL_newmetatable(L, \"lua_elf_vec2i_mt\");\n')
bindsc.write('\tluaL_register(L, NULL, lua_elf_vec2i_mt);\n')
bindsc.write('\tlua_pop(L, 1);\n')
bindsc.write('\tluaL_newmetatable(L, \"lua_elf_vec2f_mt\");\n')
bindsc.write('\tluaL_register(L, NULL, lua_elf_vec2f_mt);\n')
bindsc.write('\tlua_pop(L, 1);\n')
bindsc.write('\tluaL_newmetatable(L, \"lua_elf_vec3f_mt\");\n')
bindsc.write('\tluaL_register(L, NULL, lua_elf_vec3f_mt);\n')
bindsc.write('\tlua_pop(L, 1);\n')
bindsc.write('\tluaL_newmetatable(L, \"lua_elf_vec4f_mt\");\n')
bindsc.write('\tluaL_register(L, NULL, lua_elf_vec4f_mt);\n')
bindsc.write('\tlua_pop(L, 1);\n')
bindsc.write('\tluaL_newmetatable(L, \"lua_elf_color_mt\");\n')
bindsc.write('\tluaL_register(L, NULL, lua_elf_color_mt);\n')
bindsc.write('\tlua_pop(L, 1);\n')
bindsc.write('\tluaL_newmetatable(L, \"lua_elf_object_mt\");\n')
bindsc.write('\tluaL_register(L, NULL, lua_elf_object_mt);\n')
bindsc.write('\tlua_pop(L, 1);\n')
bindsc.write('\treturn 0;\n')
bindsc.write('}\n')
bindsc.close()

docs = open('docs/api_doc.html', 'w')

docs.write(apiheader)

for define in defines:
	if len(define.mdoc) > 0:
		docs.write('<div class=\"apitopic\">'+define.mdoc+'</div>\n')
	if len(define.mdocc) > 0:
		docs.write('<div class=\"apiinfo\">'+define.mdocc+'</div>\n')
	docs.write('<div class=\"apidefine\">elf.'+define.name+'</div>\n')

for func in functions:
	if len(func.mdoc) > 0:
		docs.write('<div class=\"apitopic\">'+func.mdoc+'</div>\n')
	if len(func.mdocc) > 0:
		docs.write('<div class=\"apiinfo\">'+func.mdocc+'</div>\n')
	docs.write('<div class=\"apifunc\">')
	if func.type == 'elf_handle':
		docs.write('<span class=\"apiobjtype\">object</span> ')
	elif func.type == 'const char*':
		docs.write('<span class=\"apikeytype\">string</span> ')
	elif func.type == 'void':
		pass
	else: docs.write('<span class=\"apikeytype\">'+func.type+'</span> ')
	docs.write('elf.'+func.name+'( ')
	for i in range(len(func.params)):
		if func.params[i].type == 'elf_handle':
			docs.write('<span class=\"apiobjtype\">object</span> '+func.params[i].name)
		elif func.params[i].type == 'const char*':
			docs.write('<span class=\"apikeytype\">string</span> '+func.params[i].name)
		else: docs.write('<span class="apikeytype">'+func.params[i].type+'</span> '+func.params[i].name)
		if(i < len(func.params)-1): docs.write(', ')
	docs.write(' )</div>\n')

docs.write(apifooter)

docs.close()

