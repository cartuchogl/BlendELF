#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "gfx.h"
#include "blendelf.h"
#define LUA_ELF_USERDATA_HEADER \
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
	if(!strcmp(lua_tostring(L, 2), "x"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.x);
	}
	else if(!strcmp(lua_tostring(L, 2), "y"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.y);
	}
	return 1;
}
static int lua_elf_vec2i__newindex(lua_State* L)
{
	lua_elf_vec2i *ud = (lua_elf_vec2i*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  "x"))
	{
		if(lua_isnumber(L, 3)) ud->val.x = (int)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec2i.x");
	}
	else if(!strcmp(lua_tostring(L, 2), "y"))
	{
		if(lua_isnumber(L, 3)) ud->val.y = (int)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec2i.y");
	}
	return 0;
}
static int lua_elf_vec2f__index(lua_State* L)
{
	lua_elf_vec2f *ud = (lua_elf_vec2f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), "x"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.x);
	}
	else if(!strcmp(lua_tostring(L, 2), "y"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.y);
	}
	return 1;
}
static int lua_elf_vec2f__newindex(lua_State* L)
{
	lua_elf_vec2f *ud = (lua_elf_vec2f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  "x"))
	{
		if(lua_isnumber(L, 3)) ud->val.x = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec2f.x");
	}
	else if(!strcmp(lua_tostring(L, 2), "y"))
	{
		if(lua_isnumber(L, 3)) ud->val.y = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec2f.y");
	}
	return 0;
}
static int lua_elf_vec3f__index(lua_State* L)
{
	lua_elf_vec3f *ud = (lua_elf_vec3f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), "x"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.x);
	}
	else if(!strcmp(lua_tostring(L, 2), "y"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.y);
	}
	else if(!strcmp(lua_tostring(L, 2), "z"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.z);
	}
	return 1;
}
static int lua_elf_vec3f__newindex(lua_State* L)
{
	lua_elf_vec3f *ud = (lua_elf_vec3f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  "x"))
	{
		if(lua_isnumber(L, 3)) ud->val.x = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec3f.x");
	}
	else if(!strcmp(lua_tostring(L, 2), "y"))
	{
		if(lua_isnumber(L, 3)) ud->val.y = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec3f.y");
	}
	else if(!strcmp(lua_tostring(L, 2), "z"))
	{
		if(lua_isnumber(L, 3)) ud->val.z = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec3f.z");
	}
	return 0;
}
static int lua_elf_vec4f__index(lua_State* L)
{
	lua_elf_vec4f *ud = (lua_elf_vec4f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), "x"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.x);
	}
	else if(!strcmp(lua_tostring(L, 2), "y"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.y);
	}
	else if(!strcmp(lua_tostring(L, 2), "z"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.z);
	}
	else if(!strcmp(lua_tostring(L, 2), "w"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.w);
	}
	return 1;
}
static int lua_elf_vec4f__newindex(lua_State* L)
{
	lua_elf_vec4f *ud = (lua_elf_vec4f*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  "x"))
	{
		if(lua_isnumber(L, 3)) ud->val.x = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_color.x");
	}
	else if(!strcmp(lua_tostring(L, 2), "y"))
	{
		if(lua_isnumber(L, 3)) ud->val.y = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_color.y");
	}
	else if(!strcmp(lua_tostring(L, 2), "z"))
	{
		if(lua_isnumber(L, 3)) ud->val.z = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_color.z");
	}
	else if(!strcmp(lua_tostring(L, 2), "w"))
	{
		if(lua_isnumber(L, 3)) ud->val.w = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_color.w");
	}
	return 0;
}
static int lua_elf_color__index(lua_State* L)
{
	lua_elf_color *ud = (lua_elf_color*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2), "r"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.r);
	}
	else if(!strcmp(lua_tostring(L, 2), "g"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.g);
	}
	else if(!strcmp(lua_tostring(L, 2), "b"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.b);
	}
	else if(!strcmp(lua_tostring(L, 2), "a"))
	{
		lua_pushnumber(L, (lua_Number)ud->val.a);
	}
	return 1;
}
static int lua_elf_color__newindex(lua_State* L)
{
	lua_elf_color *ud = (lua_elf_color*)lua_touserdata(L, 1);
	if(!strcmp(lua_tostring(L, 2),  "r"))
	{
		if(lua_isnumber(L, 3)) ud->val.r = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec4f.r");
	}
	else if(!strcmp(lua_tostring(L, 2), "g"))
	{
		if(lua_isnumber(L, 3)) ud->val.g = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec4f.g");
	}
	else if(!strcmp(lua_tostring(L, 2), "b"))
	{
		if(lua_isnumber(L, 3)) ud->val.b = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec4f.b");
	}
	else if(!strcmp(lua_tostring(L, 2), "a"))
	{
		if(lua_isnumber(L, 3)) ud->val.a = (float)lua_tonumber(L, 3);
		else return luaL_error(L, "Attemp to assign a non-number to elf_vec4f.a");
	}
	return 0;
}
static const struct luaL_reg lua_elf_vec2i_mt[] = {
	{"__index", lua_elf_vec2i__index},
	{"__newindex", lua_elf_vec2i__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_vec2f_mt[] = {
	{"__index", lua_elf_vec2f__index},
	{"__newindex", lua_elf_vec2f__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_vec3f_mt[] = {
	{"__index", lua_elf_vec3f__index},
	{"__newindex", lua_elf_vec3f__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_vec4f_mt[] = {
	{"__index", lua_elf_vec4f__index},
	{"__newindex", lua_elf_vec4f__newindex},
	{NULL, NULL}
};
static const struct luaL_reg lua_elf_color_mt[] = {
	{"__index", lua_elf_color__index},
	{"__newindex", lua_elf_color__newindex},
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
	luaL_getmetatable(L, "lua_elf_vec2i_mt");
	lua_setmetatable(L, -2);
}
void lua_create_elf_vec2f(lua_State* L, elf_vec2f vec)
{
	lua_elf_vec2f *ud;
	ud = (lua_elf_vec2f*)lua_newuserdata(L, sizeof(lua_elf_vec2f));
	ud->type = LUA_ELF_VEC2F;
	ud->val = vec;
	luaL_getmetatable(L, "lua_elf_vec2f_mt");
	lua_setmetatable(L, -2);
}
void lua_create_elf_vec3f(lua_State* L, elf_vec3f vec)
{
	lua_elf_vec3f *ud;
	ud = (lua_elf_vec3f*)lua_newuserdata(L, sizeof(lua_elf_vec3f));
	ud->type = LUA_ELF_VEC3F;
	ud->val = vec;
	luaL_getmetatable(L, "lua_elf_vec3f_mt");
	lua_setmetatable(L, -2);
}
void lua_create_elf_vec4f(lua_State* L, elf_vec4f vec)
{
	lua_elf_vec4f *ud;
	ud = (lua_elf_vec4f*)lua_newuserdata(L, sizeof(lua_elf_vec4f));
	ud->type = LUA_ELF_VEC4F;
	ud->val = vec;
	luaL_getmetatable(L, "lua_elf_vec4f_mt");
	lua_setmetatable(L, -2);
}
void lua_create_elf_color(lua_State* L, elf_color col)
{
	lua_elf_color *ud;
	ud = (lua_elf_color*)lua_newuserdata(L, sizeof(lua_elf_color));
	ud->type = LUA_ELF_COLOR;
	ud->val = col;
	luaL_getmetatable(L, "lua_elf_color_mt");
	lua_setmetatable(L, -2);
}
void lua_create_elf_object(lua_State* L, elf_object* obj)
{
	lua_elf_object *ud;
	ud = (lua_elf_object*)lua_newuserdata(L, sizeof(lua_elf_object));
	ud->type = LUA_ELF_OBJECT;
	ud->object = obj;
	elf_inc_ref(ud->object);
	luaL_getmetatable(L, "lua_elf_object_mt");
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
static int lua_GetObjectType(lua_State *L)
{
	int result;
	elf_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetObjectType", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "GetObjectType", 1, "elf_object");}
	arg0 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_object_type(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetObjectRefCount(lua_State *L)
{
	int result;
	elf_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetObjectRefCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "GetObjectRefCount", 1, "elf_object");}
	arg0 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_object_ref_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetGlobalRefCount(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetGlobalRefCount", lua_gettop(L), 0);}
	result = elf_get_global_ref_count();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetGlobalObjCount(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetGlobalObjCount", lua_gettop(L), 0);}
	result = elf_get_global_obj_count();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_IsActor(lua_State *L)
{
	unsigned char result;
	elf_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsActor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "IsActor", 1, "elf_object");}
	arg0 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_actor(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsGuiObject(lua_State *L)
{
	unsigned char result;
	elf_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsGuiObject", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "IsGuiObject", 1, "elf_object");}
	arg0 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_gui_object(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_CreateList(lua_State *L)
{
	elf_list* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateList", lua_gettop(L), 0);}
	result = elf_create_list();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetListLength(lua_State *L)
{
	int result;
	elf_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetListLength", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "GetListLength", 1, "elf_list");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_list_length(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_InsertToList(lua_State *L)
{
	elf_list* arg0;
	int arg1;
	elf_object* arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "InsertToList", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "InsertToList", 1, "elf_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "InsertToList", 2, "number");}
	if(!lua_isuserdata(L, 3) || ((lua_elf_userdata*)lua_touserdata(L,3))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "InsertToList", 3, "elf_object");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 3))->object;
	elf_insert_to_list(arg0, arg1, arg2);
	return 0;
}
static int lua_AppendToList(lua_State *L)
{
	elf_list* arg0;
	elf_object* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AppendToList", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "AppendToList", 1, "elf_list");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "AppendToList", 2, "elf_object");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_append_to_list(arg0, arg1);
	return 0;
}
static int lua_RemoveFromList(lua_State *L)
{
	unsigned char result;
	elf_list* arg0;
	elf_object* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveFromList", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "RemoveFromList", 1, "elf_list");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "RemoveFromList", 2, "elf_object");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_from_list(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetItemFromList(lua_State *L)
{
	elf_object* result;
	elf_list* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetItemFromList", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "GetItemFromList", 1, "elf_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetItemFromList", 2, "number");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_item_from_list(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_BeginList(lua_State *L)
{
	elf_object* result;
	elf_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "BeginList", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "BeginList", 1, "elf_list");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_begin_list(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_NextInList(lua_State *L)
{
	elf_object* result;
	elf_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "NextInList", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "NextInList", 1, "elf_list");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_next_in_list(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_RbeginList(lua_State *L)
{
	elf_object* result;
	elf_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "RbeginList", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "RbeginList", 1, "elf_list");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_rbegin_list(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_RnextInList(lua_State *L)
{
	elf_object* result;
	elf_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "RnextInList", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "RnextInList", 1, "elf_list");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_rnext_in_list(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SeekList(lua_State *L)
{
	elf_list* arg0;
	elf_object* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SeekList", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "SeekList", 1, "elf_list");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "SeekList", 2, "elf_object");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_seek_list(arg0, arg1);
	return 0;
}
static int lua_RseekList(lua_State *L)
{
	elf_list* arg0;
	elf_object* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RseekList", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIST)
		{return lua_fail_arg(L, "RseekList", 1, "elf_list");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT)
		{return lua_fail_arg(L, "RseekList", 2, "elf_object");}
	arg0 = (elf_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_object*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_rseek_list(arg0, arg1);
	return 0;
}
static int lua_ReadConfig(lua_State *L)
{
	elf_config* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ReadConfig", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "ReadConfig", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_read_config(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetConfigWindowWidth(lua_State *L)
{
	int result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigWindowWidth", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigWindowWidth", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_window_width(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetConfigWindowHeight(lua_State *L)
{
	int result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigWindowHeight", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigWindowHeight", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_window_height(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetConfigMultisamples(lua_State *L)
{
	int result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigMultisamples", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigMultisamples", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_multisamples(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetConfigFullscreen(lua_State *L)
{
	unsigned char result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigFullscreen", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigFullscreen", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_fullscreen(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetConfigTextureCompress(lua_State *L)
{
	unsigned char result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigTextureCompress", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigTextureCompress", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_texture_compress(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetConfigTextureAnisotropy(lua_State *L)
{
	float result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigTextureAnisotropy", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigTextureAnisotropy", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_texture_anisotropy(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetConfigShadowMapSize(lua_State *L)
{
	int result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigShadowMapSize", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigShadowMapSize", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_shadow_map_size(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetConfigStart(lua_State *L)
{
	const char* result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigStart", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigStart", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_start(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetConfigLog(lua_State *L)
{
	const char* result;
	elf_config* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetConfigLog", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CONFIG)
		{return lua_fail_arg(L, "GetConfigLog", 1, "elf_config");}
	arg0 = (elf_config*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_config_log(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_SetTitle(lua_State *L)
{
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetTitle", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "SetTitle", 1, "string");}
	arg0 = lua_tostring(L, 1);
	elf_set_title(arg0);
	return 0;
}
static int lua_GetWindowWidth(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetWindowWidth", lua_gettop(L), 0);}
	result = elf_get_window_width();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetWindowHeight(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetWindowHeight", lua_gettop(L), 0);}
	result = elf_get_window_height();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetVideoModeCount(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetVideoModeCount", lua_gettop(L), 0);}
	result = elf_get_video_mode_count();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetVideoMode(lua_State *L)
{
	elf_vec2i result;
	int arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetVideoMode", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "GetVideoMode", 1, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	result = elf_get_video_mode(arg0);
	lua_create_elf_vec2i(L, result);
	return 1;
}
static int lua_GetMultisamples(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetMultisamples", lua_gettop(L), 0);}
	result = elf_get_multisamples();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_IsFullscreen(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsFullscreen", lua_gettop(L), 0);}
	result = elf_is_fullscreen();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetTitle(lua_State *L)
{
	const char* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetTitle", lua_gettop(L), 0);}
	result = elf_get_title();
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetTime(lua_State *L)
{
	double result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetTime", lua_gettop(L), 0);}
	result = elf_get_time();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_Sleep(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "Sleep", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "Sleep", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_sleep(arg0);
	return 0;
}
static int lua_IsWindowOpened(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsWindowOpened", lua_gettop(L), 0);}
	result = elf_is_window_opened();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetMousePosition(lua_State *L)
{
	elf_vec2i result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetMousePosition", lua_gettop(L), 0);}
	result = elf_get_mouse_position();
	lua_create_elf_vec2i(L, result);
	return 1;
}
static int lua_GetMouseForce(lua_State *L)
{
	elf_vec2i result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetMouseForce", lua_gettop(L), 0);}
	result = elf_get_mouse_force();
	lua_create_elf_vec2i(L, result);
	return 1;
}
static int lua_SetMousePosition(lua_State *L)
{
	int arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMousePosition", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetMousePosition", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetMousePosition", 2, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_mouse_position(arg0, arg1);
	return 0;
}
static int lua_HideMouse(lua_State *L)
{
	unsigned char arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "HideMouse", lua_gettop(L), 1);}
	if(!lua_isboolean(L, 1)) {return lua_fail_arg(L, "HideMouse", 1, "boolean");}
	arg0 = (unsigned char)lua_toboolean(L, 1);
	elf_hide_mouse(arg0);
	return 0;
}
static int lua_IsMouseHidden(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsMouseHidden", lua_gettop(L), 0);}
	result = elf_is_mouse_hidden();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetMouseWheel(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetMouseWheel", lua_gettop(L), 0);}
	result = elf_get_mouse_wheel();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetMouseButtonState(lua_State *L)
{
	int result;
	int arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMouseButtonState", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "GetMouseButtonState", 1, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	result = elf_get_mouse_button_state(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetKeyState(lua_State *L)
{
	int result;
	int arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetKeyState", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "GetKeyState", 1, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	result = elf_get_key_state(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetJoystickPresent(lua_State *L)
{
	unsigned char result;
	int arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetJoystickPresent", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "GetJoystickPresent", 1, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	result = elf_get_joystick_present(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetJoystickAxis(lua_State *L)
{
	elf_vec2f result;
	int arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetJoystickAxis", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "GetJoystickAxis", 1, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	result = elf_get_joystick_axis(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_GetJoystickButtonState(lua_State *L)
{
	int result;
	int arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetJoystickButtonState", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "GetJoystickButtonState", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetJoystickButtonState", 2, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_joystick_button_state(arg0, arg1);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetEventCount(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetEventCount", lua_gettop(L), 0);}
	result = elf_get_event_count();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetEvent(lua_State *L)
{
	elf_object* result;
	int arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEvent", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "GetEvent", 1, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	result = elf_get_event(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_Init(lua_State *L)
{
	unsigned char result;
	int arg0;
	int arg1;
	const char* arg2;
	int arg3;
	unsigned char arg4;
	const char* arg5;
	if(lua_gettop(L) != 6) {return lua_fail_arg_count(L, "Init", lua_gettop(L), 6);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "Init", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "Init", 2, "number");}
	if(!lua_isstring(L, 3)) {return lua_fail_arg(L, "Init", 3, "string");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "Init", 4, "number");}
	if(!lua_isboolean(L, 5)) {return lua_fail_arg(L, "Init", 5, "boolean");}
	if(!lua_isstring(L, 6)) {return lua_fail_arg(L, "Init", 6, "string");}
	arg0 = (int)lua_tonumber(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = lua_tostring(L, 3);
	arg3 = (int)lua_tonumber(L, 4);
	arg4 = (unsigned char)lua_toboolean(L, 5);
	arg5 = lua_tostring(L, 6);
	result = elf_init(arg0, arg1, arg2, arg3, arg4, arg5);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_InitWithConfig(lua_State *L)
{
	unsigned char result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "InitWithConfig", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "InitWithConfig", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_init_with_config(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_Deinit(lua_State *L)
{
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "Deinit", lua_gettop(L), 0);}
	elf_deinit();
	return 0;
}
static int lua_ResizeWindow(lua_State *L)
{
	int arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "ResizeWindow", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "ResizeWindow", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "ResizeWindow", 2, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	elf_resize_window(arg0, arg1);
	return 0;
}
static int lua_GetPlatform(lua_State *L)
{
	const char* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetPlatform", lua_gettop(L), 0);}
	result = elf_get_platform();
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetVersionMajor(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetVersionMajor", lua_gettop(L), 0);}
	result = elf_get_version_major();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetVersionMinor(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetVersionMinor", lua_gettop(L), 0);}
	result = elf_get_version_minor();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetVersionRelease(lua_State *L)
{
	const char* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetVersionRelease", lua_gettop(L), 0);}
	result = elf_get_version_release();
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetVersion(lua_State *L)
{
	const char* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetVersion", lua_gettop(L), 0);}
	result = elf_get_version();
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetCurrentDirectory(lua_State *L)
{
	const char* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetCurrentDirectory", lua_gettop(L), 0);}
	result = elf_get_current_directory();
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetErrorString(lua_State *L)
{
	const char* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetErrorString", lua_gettop(L), 0);}
	result = elf_get_error_string();
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetError(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetError", lua_gettop(L), 0);}
	result = elf_get_error();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_Run(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "Run", lua_gettop(L), 0);}
	result = elf_run();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_Quit(lua_State *L)
{
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "Quit", lua_gettop(L), 0);}
	elf_quit();
	return 0;
}
static int lua_SetF10Exit(lua_State *L)
{
	unsigned char arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetF10Exit", lua_gettop(L), 1);}
	if(!lua_isboolean(L, 1)) {return lua_fail_arg(L, "SetF10Exit", 1, "boolean");}
	arg0 = (unsigned char)lua_toboolean(L, 1);
	elf_set_f10_exit(arg0);
	return 0;
}
static int lua_GetF10Exit(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetF10Exit", lua_gettop(L), 0);}
	result = elf_get_f10_exit();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_LoadScene(lua_State *L)
{
	elf_scene* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "LoadScene", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "LoadScene", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_load_scene(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetScene(lua_State *L)
{
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetScene", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "SetScene", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_set_scene(arg0);
	return 0;
}
static int lua_GetScene(lua_State *L)
{
	elf_scene* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetScene", lua_gettop(L), 0);}
	result = elf_get_scene();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetGui(lua_State *L)
{
	elf_gui* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetGui", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_GUI)
		{return lua_fail_arg(L, "SetGui", 1, "elf_gui");}
	arg0 = (elf_gui*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_set_gui(arg0);
	return 0;
}
static int lua_GetGui(lua_State *L)
{
	elf_gui* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetGui", lua_gettop(L), 0);}
	result = elf_get_gui();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSync(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetSync", lua_gettop(L), 0);}
	result = elf_get_sync();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetFps(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetFps", lua_gettop(L), 0);}
	result = elf_get_fps();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SaveScreenShot(lua_State *L)
{
	unsigned char result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SaveScreenShot", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "SaveScreenShot", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_save_screen_shot(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetFpsLimit(lua_State *L)
{
	int arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetFpsLimit", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetFpsLimit", 1, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	elf_set_fps_limit(arg0);
	return 0;
}
static int lua_GetFpsLimit(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetFpsLimit", lua_gettop(L), 0);}
	result = elf_get_fps_limit();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetTickRate(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetTickRate", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetTickRate", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_set_tick_rate(arg0);
	return 0;
}
static int lua_GetTickRate(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetTickRate", lua_gettop(L), 0);}
	result = elf_get_tick_rate();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetSpeed(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetSpeed", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetSpeed", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_set_speed(arg0);
	return 0;
}
static int lua_GetSpeed(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetSpeed", lua_gettop(L), 0);}
	result = elf_get_speed();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetTextureCompress(lua_State *L)
{
	unsigned char arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetTextureCompress", lua_gettop(L), 1);}
	if(!lua_isboolean(L, 1)) {return lua_fail_arg(L, "SetTextureCompress", 1, "boolean");}
	arg0 = (unsigned char)lua_toboolean(L, 1);
	elf_set_texture_compress(arg0);
	return 0;
}
static int lua_GetTextureCompress(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetTextureCompress", lua_gettop(L), 0);}
	result = elf_get_texture_compress();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetTextureAnisotropy(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetTextureAnisotropy", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetTextureAnisotropy", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_set_texture_anisotropy(arg0);
	return 0;
}
static int lua_GetTextureAnisotropy(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetTextureAnisotropy", lua_gettop(L), 0);}
	result = elf_get_texture_anisotropy();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetShadowMapSize(lua_State *L)
{
	int arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetShadowMapSize", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetShadowMapSize", 1, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	elf_set_shadow_map_size(arg0);
	return 0;
}
static int lua_GetShadowMapSize(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetShadowMapSize", lua_gettop(L), 0);}
	result = elf_get_shadow_map_size();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetPolygonsRendered(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetPolygonsRendered", lua_gettop(L), 0);}
	result = elf_get_polygons_rendered();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetFog(lua_State *L)
{
	float arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetFog", lua_gettop(L), 5);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetFog", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetFog", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetFog", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetFog", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetFog", 5, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_fog(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_DisableFog(lua_State *L)
{
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "DisableFog", lua_gettop(L), 0);}
	elf_disable_fog();
	return 0;
}
static int lua_GetFogStart(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetFogStart", lua_gettop(L), 0);}
	result = elf_get_fog_start();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetFogEnd(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetFogEnd", lua_gettop(L), 0);}
	result = elf_get_fog_end();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetFogColor(lua_State *L)
{
	elf_color result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetFogColor", lua_gettop(L), 0);}
	result = elf_get_fog_color();
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_SetBloom(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetBloom", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetBloom", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_set_bloom(arg0);
	return 0;
}
static int lua_DisableBloom(lua_State *L)
{
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "DisableBloom", lua_gettop(L), 0);}
	elf_disable_bloom();
	return 0;
}
static int lua_GetBloomThreshold(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetBloomThreshold", lua_gettop(L), 0);}
	result = elf_get_bloom_threshold();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetDof(lua_State *L)
{
	float arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetDof", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetDof", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetDof", 2, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_dof(arg0, arg1);
	return 0;
}
static int lua_DisableDof(lua_State *L)
{
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "DisableDof", lua_gettop(L), 0);}
	elf_disable_dof();
	return 0;
}
static int lua_GetDofFocalRange(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetDofFocalRange", lua_gettop(L), 0);}
	result = elf_get_dof_focal_range();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetDofFocalDistance(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetDofFocalDistance", lua_gettop(L), 0);}
	result = elf_get_dof_focal_distance();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetSsao(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetSsao", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetSsao", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_set_ssao(arg0);
	return 0;
}
static int lua_DisableSsao(lua_State *L)
{
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "DisableSsao", lua_gettop(L), 0);}
	elf_disable_ssao();
	return 0;
}
static int lua_GetSsaoAmount(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetSsaoAmount", lua_gettop(L), 0);}
	result = elf_get_ssao_amount();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetLightShafts(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetLightShafts", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetLightShafts", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_set_light_shafts(arg0);
	return 0;
}
static int lua_DisableLightShafts(lua_State *L)
{
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "DisableLightShafts", lua_gettop(L), 0);}
	elf_disable_light_shafts();
	return 0;
}
static int lua_GetLightShaftsIntensity(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetLightShaftsIntensity", lua_gettop(L), 0);}
	result = elf_get_light_shafts_intensity();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_IsFog(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsFog", lua_gettop(L), 0);}
	result = elf_is_fog();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsBloom(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsBloom", lua_gettop(L), 0);}
	result = elf_is_bloom();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsSsao(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsSsao", lua_gettop(L), 0);}
	result = elf_is_ssao();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsDof(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsDof", lua_gettop(L), 0);}
	result = elf_is_dof();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsLightShafts(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsLightShafts", lua_gettop(L), 0);}
	result = elf_is_light_shafts();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetOcclusionCulling(lua_State *L)
{
	unsigned char arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetOcclusionCulling", lua_gettop(L), 1);}
	if(!lua_isboolean(L, 1)) {return lua_fail_arg(L, "SetOcclusionCulling", 1, "boolean");}
	arg0 = (unsigned char)lua_toboolean(L, 1);
	elf_set_occlusion_culling(arg0);
	return 0;
}
static int lua_IsOcclusionCulling(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsOcclusionCulling", lua_gettop(L), 0);}
	result = elf_is_occlusion_culling();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetDebugDraw(lua_State *L)
{
	unsigned char arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetDebugDraw", lua_gettop(L), 1);}
	if(!lua_isboolean(L, 1)) {return lua_fail_arg(L, "SetDebugDraw", 1, "boolean");}
	arg0 = (unsigned char)lua_toboolean(L, 1);
	elf_set_debug_draw(arg0);
	return 0;
}
static int lua_IsDebugDraw(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsDebugDraw", lua_gettop(L), 0);}
	result = elf_is_debug_draw();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetActor(lua_State *L)
{
	elf_object* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetActor", lua_gettop(L), 0);}
	result = elf_get_actor();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_ReadDirectory(lua_State *L)
{
	elf_directory* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ReadDirectory", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "ReadDirectory", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_read_directory(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetDirectoryPath(lua_State *L)
{
	const char* result;
	elf_directory* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetDirectoryPath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_DIRECTORY)
		{return lua_fail_arg(L, "GetDirectoryPath", 1, "elf_directory");}
	arg0 = (elf_directory*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_directory_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetDirectoryItemCount(lua_State *L)
{
	int result;
	elf_directory* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetDirectoryItemCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_DIRECTORY)
		{return lua_fail_arg(L, "GetDirectoryItemCount", 1, "elf_directory");}
	arg0 = (elf_directory*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_directory_item_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetDirectoryItem(lua_State *L)
{
	elf_directory_item* result;
	elf_directory* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetDirectoryItem", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_DIRECTORY)
		{return lua_fail_arg(L, "GetDirectoryItem", 1, "elf_directory");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetDirectoryItem", 2, "number");}
	arg0 = (elf_directory*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_directory_item(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetDirectoryItemName(lua_State *L)
{
	const char* result;
	elf_directory_item* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetDirectoryItemName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_DIRECTORY_ITEM)
		{return lua_fail_arg(L, "GetDirectoryItemName", 1, "elf_directory_item");}
	arg0 = (elf_directory_item*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_directory_item_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetDirectoryItemType(lua_State *L)
{
	int result;
	elf_directory_item* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetDirectoryItemType", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_DIRECTORY_ITEM)
		{return lua_fail_arg(L, "GetDirectoryItemType", 1, "elf_directory_item");}
	arg0 = (elf_directory_item*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_directory_item_type(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_CreateVec3f(lua_State *L)
{
	elf_vec3f result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateVec3f", lua_gettop(L), 0);}
	result = elf_create_vec3f();
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_CreateVec3fFromValues(lua_State *L)
{
	elf_vec3f result;
	float arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "CreateVec3fFromValues", lua_gettop(L), 3);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "CreateVec3fFromValues", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "CreateVec3fFromValues", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "CreateVec3fFromValues", 3, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	result = elf_create_vec3f_from_values(arg0, arg1, arg2);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_CreateQua(lua_State *L)
{
	elf_vec4f result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateQua", lua_gettop(L), 0);}
	result = elf_create_qua();
	lua_create_elf_vec4f(L, result);
	return 1;
}
static int lua_CreateQuaFromEuler(lua_State *L)
{
	elf_vec4f result;
	float arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "CreateQuaFromEuler", lua_gettop(L), 3);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "CreateQuaFromEuler", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "CreateQuaFromEuler", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "CreateQuaFromEuler", 3, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	result = elf_create_qua_from_euler(arg0, arg1, arg2);
	lua_create_elf_vec4f(L, result);
	return 1;
}
static int lua_CreateQuaFromAngleAxis(lua_State *L)
{
	elf_vec4f result;
	float arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "CreateQuaFromAngleAxis", lua_gettop(L), 4);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "CreateQuaFromAngleAxis", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "CreateQuaFromAngleAxis", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "CreateQuaFromAngleAxis", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "CreateQuaFromAngleAxis", 4, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	result = elf_create_qua_from_angle_axis(arg0, arg1, arg2, arg3);
	lua_create_elf_vec4f(L, result);
	return 1;
}
static int lua_MulQuaVec3f(lua_State *L)
{
	elf_vec3f result;
	elf_vec4f arg0;
	elf_vec3f arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "MulQuaVec3f", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1)) {return lua_fail_arg(L, "MulQuaVec3f", 1, "elf_vec4f");}
	if(!lua_isuserdata(L, 2)) {return lua_fail_arg(L, "MulQuaVec3f", 2, "elf_vec3f");}
	arg0 = ((lua_elf_vec4f*)lua_touserdata(L, 1))->val;
	arg1 = ((lua_elf_vec3f*)lua_touserdata(L, 2))->val;
	result = elf_mul_qua_vec3f(arg0, arg1);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_MulQuaQua(lua_State *L)
{
	elf_vec4f result;
	elf_vec4f arg0;
	elf_vec4f arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "MulQuaQua", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1)) {return lua_fail_arg(L, "MulQuaQua", 1, "elf_vec4f");}
	if(!lua_isuserdata(L, 2)) {return lua_fail_arg(L, "MulQuaQua", 2, "elf_vec4f");}
	arg0 = ((lua_elf_vec4f*)lua_touserdata(L, 1))->val;
	arg1 = ((lua_elf_vec4f*)lua_touserdata(L, 2))->val;
	result = elf_mul_qua_qua(arg0, arg1);
	lua_create_elf_vec4f(L, result);
	return 1;
}
static int lua_GetQuaInverted(lua_State *L)
{
	elf_vec4f result;
	elf_vec4f arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetQuaInverted", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1)) {return lua_fail_arg(L, "GetQuaInverted", 1, "elf_vec4f");}
	arg0 = ((lua_elf_vec4f*)lua_touserdata(L, 1))->val;
	result = elf_get_qua_inverted(arg0);
	lua_create_elf_vec4f(L, result);
	return 1;
}
static int lua_RotateVec3f(lua_State *L)
{
	elf_vec3f result;
	elf_vec3f arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "RotateVec3f", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1)) {return lua_fail_arg(L, "RotateVec3f", 1, "elf_vec3f");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RotateVec3f", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "RotateVec3f", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "RotateVec3f", 4, "number");}
	arg0 = ((lua_elf_vec3f*)lua_touserdata(L, 1))->val;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	result = elf_rotate_vec3f(arg0, arg1, arg2, arg3);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_SubVec3fVec3f(lua_State *L)
{
	elf_vec3f result;
	elf_vec3f arg0;
	elf_vec3f arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SubVec3fVec3f", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1)) {return lua_fail_arg(L, "SubVec3fVec3f", 1, "elf_vec3f");}
	if(!lua_isuserdata(L, 2)) {return lua_fail_arg(L, "SubVec3fVec3f", 2, "elf_vec3f");}
	arg0 = ((lua_elf_vec3f*)lua_touserdata(L, 1))->val;
	arg1 = ((lua_elf_vec3f*)lua_touserdata(L, 2))->val;
	result = elf_sub_vec3f_vec3f(arg0, arg1);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_AddVec3fVec3f(lua_State *L)
{
	elf_vec3f result;
	elf_vec3f arg0;
	elf_vec3f arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddVec3fVec3f", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1)) {return lua_fail_arg(L, "AddVec3fVec3f", 1, "elf_vec3f");}
	if(!lua_isuserdata(L, 2)) {return lua_fail_arg(L, "AddVec3fVec3f", 2, "elf_vec3f");}
	arg0 = ((lua_elf_vec3f*)lua_touserdata(L, 1))->val;
	arg1 = ((lua_elf_vec3f*)lua_touserdata(L, 2))->val;
	result = elf_add_vec3f_vec3f(arg0, arg1);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetVec3fLength(lua_State *L)
{
	float result;
	elf_vec3f arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetVec3fLength", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1)) {return lua_fail_arg(L, "GetVec3fLength", 1, "elf_vec3f");}
	arg0 = ((lua_elf_vec3f*)lua_touserdata(L, 1))->val;
	result = elf_get_vec3f_length(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_AboutZero(lua_State *L)
{
	unsigned char result;
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "AboutZero", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "AboutZero", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	result = elf_about_zero(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_FloatAbs(lua_State *L)
{
	float result;
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "FloatAbs", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "FloatAbs", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	result = elf_float_abs(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_FloatMin(lua_State *L)
{
	float result;
	float arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "FloatMin", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "FloatMin", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "FloatMin", 2, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_float_min(arg0, arg1);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_FloatMax(lua_State *L)
{
	float result;
	float arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "FloatMax", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "FloatMax", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "FloatMax", 2, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_float_max(arg0, arg1);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_RandomFloat(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "RandomFloat", lua_gettop(L), 0);}
	result = elf_random_float();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_RandomFloatRange(lua_State *L)
{
	float result;
	float arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RandomFloatRange", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "RandomFloatRange", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RandomFloatRange", 2, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_random_float_range(arg0, arg1);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_RandomInt(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "RandomInt", lua_gettop(L), 0);}
	result = elf_random_int();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_RandomIntRange(lua_State *L)
{
	int result;
	int arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RandomIntRange", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "RandomIntRange", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RandomIntRange", 2, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_random_int_range(arg0, arg1);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_CreateFramePlayer(lua_State *L)
{
	elf_frame_player* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateFramePlayer", lua_gettop(L), 0);}
	result = elf_create_frame_player();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_UpdateFramePlayer(lua_State *L)
{
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "UpdateFramePlayer", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "UpdateFramePlayer", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_update_frame_player(arg0);
	return 0;
}
static int lua_SetFramePlayerFrame(lua_State *L)
{
	elf_frame_player* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetFramePlayerFrame", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "SetFramePlayerFrame", 1, "elf_frame_player");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetFramePlayerFrame", 2, "number");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_frame_player_frame(arg0, arg1);
	return 0;
}
static int lua_PlayFramePlayer(lua_State *L)
{
	elf_frame_player* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "PlayFramePlayer", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "PlayFramePlayer", 1, "elf_frame_player");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "PlayFramePlayer", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "PlayFramePlayer", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "PlayFramePlayer", 4, "number");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_play_frame_player(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_LoopFramePlayer(lua_State *L)
{
	elf_frame_player* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "LoopFramePlayer", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "LoopFramePlayer", 1, "elf_frame_player");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "LoopFramePlayer", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "LoopFramePlayer", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "LoopFramePlayer", 4, "number");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_loop_frame_player(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_StopFramePlayer(lua_State *L)
{
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "StopFramePlayer", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "StopFramePlayer", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_stop_frame_player(arg0);
	return 0;
}
static int lua_PauseFramePlayer(lua_State *L)
{
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "PauseFramePlayer", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "PauseFramePlayer", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_pause_frame_player(arg0);
	return 0;
}
static int lua_ResumeFramePlayer(lua_State *L)
{
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ResumeFramePlayer", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "ResumeFramePlayer", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_resume_frame_player(arg0);
	return 0;
}
static int lua_GetFramePlayerStart(lua_State *L)
{
	float result;
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFramePlayerStart", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "GetFramePlayerStart", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_frame_player_start(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetFramePlayerEnd(lua_State *L)
{
	float result;
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFramePlayerEnd", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "GetFramePlayerEnd", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_frame_player_end(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetFramePlayerSpeed(lua_State *L)
{
	float result;
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFramePlayerSpeed", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "GetFramePlayerSpeed", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_frame_player_speed(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetFramePlayerFrame(lua_State *L)
{
	float result;
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFramePlayerFrame", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "GetFramePlayerFrame", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_frame_player_frame(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_IsFramePlayerPlaying(lua_State *L)
{
	unsigned char result;
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsFramePlayerPlaying", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "IsFramePlayerPlaying", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_frame_player_playing(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsFramePlayerPaused(lua_State *L)
{
	unsigned char result;
	elf_frame_player* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsFramePlayerPaused", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FRAME_PLAYER)
		{return lua_fail_arg(L, "IsFramePlayerPaused", 1, "elf_frame_player");}
	arg0 = (elf_frame_player*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_frame_player_paused(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_CreateTimer(lua_State *L)
{
	elf_timer* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateTimer", lua_gettop(L), 0);}
	result = elf_create_timer();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_StartTimer(lua_State *L)
{
	elf_timer* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "StartTimer", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TIMER)
		{return lua_fail_arg(L, "StartTimer", 1, "elf_timer");}
	arg0 = (elf_timer*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_start_timer(arg0);
	return 0;
}
static int lua_GetElapsedTime(lua_State *L)
{
	double result;
	elf_timer* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetElapsedTime", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TIMER)
		{return lua_fail_arg(L, "GetElapsedTime", 1, "elf_timer");}
	arg0 = (elf_timer*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_elapsed_time(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_CreateEmptyImage(lua_State *L)
{
	elf_image* result;
	int arg0;
	int arg1;
	int arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "CreateEmptyImage", lua_gettop(L), 3);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "CreateEmptyImage", 1, "number");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "CreateEmptyImage", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "CreateEmptyImage", 3, "number");}
	arg0 = (int)lua_tonumber(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (int)lua_tonumber(L, 3);
	result = elf_create_empty_image(arg0, arg1, arg2);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_CreateImageFromFile(lua_State *L)
{
	elf_image* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateImageFromFile", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateImageFromFile", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_image_from_file(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetImagePixel(lua_State *L)
{
	elf_image* arg0;
	int arg1;
	int arg2;
	float arg3;
	float arg4;
	float arg5;
	float arg6;
	if(lua_gettop(L) != 7) {return lua_fail_arg_count(L, "SetImagePixel", lua_gettop(L), 7);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IMAGE)
		{return lua_fail_arg(L, "SetImagePixel", 1, "elf_image");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetImagePixel", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetImagePixel", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetImagePixel", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetImagePixel", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "SetImagePixel", 6, "number");}
	if(!lua_isnumber(L, 7)) {return lua_fail_arg(L, "SetImagePixel", 7, "number");}
	arg0 = (elf_image*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (int)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	arg6 = (float)lua_tonumber(L, 7);
	elf_set_image_pixel(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	return 0;
}
static int lua_GetImageWidth(lua_State *L)
{
	int result;
	elf_image* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetImageWidth", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IMAGE)
		{return lua_fail_arg(L, "GetImageWidth", 1, "elf_image");}
	arg0 = (elf_image*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_image_width(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetImageHeight(lua_State *L)
{
	int result;
	elf_image* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetImageHeight", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IMAGE)
		{return lua_fail_arg(L, "GetImageHeight", 1, "elf_image");}
	arg0 = (elf_image*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_image_height(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetImageBitsPerPixel(lua_State *L)
{
	int result;
	elf_image* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetImageBitsPerPixel", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IMAGE)
		{return lua_fail_arg(L, "GetImageBitsPerPixel", 1, "elf_image");}
	arg0 = (elf_image*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_image_bits_per_pixel(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetImagePixel(lua_State *L)
{
	elf_color result;
	elf_image* arg0;
	int arg1;
	int arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "GetImagePixel", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IMAGE)
		{return lua_fail_arg(L, "GetImagePixel", 1, "elf_image");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetImagePixel", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "GetImagePixel", 3, "number");}
	arg0 = (elf_image*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (int)lua_tonumber(L, 3);
	result = elf_get_image_pixel(arg0, arg1, arg2);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_CreateTextureFromFile(lua_State *L)
{
	elf_texture* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateTextureFromFile", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateTextureFromFile", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_texture_from_file(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_CreateTextureFromImage(lua_State *L)
{
	elf_texture* result;
	elf_image* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateTextureFromImage", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IMAGE)
		{return lua_fail_arg(L, "CreateTextureFromImage", 1, "elf_image");}
	arg0 = (elf_image*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_create_texture_from_image(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_CreateCubeMapFromFiles(lua_State *L)
{
	elf_texture* result;
	const char* arg0;
	const char* arg1;
	const char* arg2;
	const char* arg3;
	const char* arg4;
	const char* arg5;
	if(lua_gettop(L) != 6) {return lua_fail_arg_count(L, "CreateCubeMapFromFiles", lua_gettop(L), 6);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateCubeMapFromFiles", 1, "string");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "CreateCubeMapFromFiles", 2, "string");}
	if(!lua_isstring(L, 3)) {return lua_fail_arg(L, "CreateCubeMapFromFiles", 3, "string");}
	if(!lua_isstring(L, 4)) {return lua_fail_arg(L, "CreateCubeMapFromFiles", 4, "string");}
	if(!lua_isstring(L, 5)) {return lua_fail_arg(L, "CreateCubeMapFromFiles", 5, "string");}
	if(!lua_isstring(L, 6)) {return lua_fail_arg(L, "CreateCubeMapFromFiles", 6, "string");}
	arg0 = lua_tostring(L, 1);
	arg1 = lua_tostring(L, 2);
	arg2 = lua_tostring(L, 3);
	arg3 = lua_tostring(L, 4);
	arg4 = lua_tostring(L, 5);
	arg5 = lua_tostring(L, 6);
	result = elf_create_cube_map_from_files(arg0, arg1, arg2, arg3, arg4, arg5);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetTextureName(lua_State *L)
{
	elf_texture* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetTextureName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetTextureName", 1, "elf_texture");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetTextureName", 2, "string");}
	arg0 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_texture_name(arg0, arg1);
	return 0;
}
static int lua_GetTextureName(lua_State *L)
{
	const char* result;
	elf_texture* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextureName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "GetTextureName", 1, "elf_texture");}
	arg0 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_texture_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetTextureFilePath(lua_State *L)
{
	const char* result;
	elf_texture* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextureFilePath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "GetTextureFilePath", 1, "elf_texture");}
	arg0 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_texture_file_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetTextureWidth(lua_State *L)
{
	int result;
	elf_texture* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextureWidth", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "GetTextureWidth", 1, "elf_texture");}
	arg0 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_texture_width(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetTextureHeight(lua_State *L)
{
	int result;
	elf_texture* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextureHeight", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "GetTextureHeight", 1, "elf_texture");}
	arg0 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_texture_height(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetTextureFormat(lua_State *L)
{
	int result;
	elf_texture* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextureFormat", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "GetTextureFormat", 1, "elf_texture");}
	arg0 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_texture_format(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetTextureDataFormat(lua_State *L)
{
	int result;
	elf_texture* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextureDataFormat", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "GetTextureDataFormat", 1, "elf_texture");}
	arg0 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_texture_data_format(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_CreateMaterial(lua_State *L)
{
	elf_material* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateMaterial", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateMaterial", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_material(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetMaterialDiffuseColor(lua_State *L)
{
	elf_material* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetMaterialDiffuseColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialDiffuseColor", 1, "elf_material");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetMaterialDiffuseColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetMaterialDiffuseColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetMaterialDiffuseColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetMaterialDiffuseColor", 5, "number");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_material_diffuse_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetMaterialSpecularColor(lua_State *L)
{
	elf_material* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetMaterialSpecularColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialSpecularColor", 1, "elf_material");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetMaterialSpecularColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetMaterialSpecularColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetMaterialSpecularColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetMaterialSpecularColor", 5, "number");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_material_specular_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetMaterialAmbientColor(lua_State *L)
{
	elf_material* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetMaterialAmbientColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialAmbientColor", 1, "elf_material");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetMaterialAmbientColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetMaterialAmbientColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetMaterialAmbientColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetMaterialAmbientColor", 5, "number");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_material_ambient_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetMaterialSpecularPower(lua_State *L)
{
	elf_material* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialSpecularPower", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialSpecularPower", 1, "elf_material");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetMaterialSpecularPower", 2, "number");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_material_specular_power(arg0, arg1);
	return 0;
}
static int lua_SetMaterialLighting(lua_State *L)
{
	elf_material* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialLighting", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialLighting", 1, "elf_material");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetMaterialLighting", 2, "boolean");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_material_lighting(arg0, arg1);
	return 0;
}
static int lua_SetMaterialName(lua_State *L)
{
	elf_material* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialName", 1, "elf_material");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetMaterialName", 2, "string");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_material_name(arg0, arg1);
	return 0;
}
static int lua_GetMaterialName(lua_State *L)
{
	const char* result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialName", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetMaterialFilePath(lua_State *L)
{
	const char* result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialFilePath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialFilePath", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_file_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetMaterialDiffuseColor(lua_State *L)
{
	elf_color result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialDiffuseColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialDiffuseColor", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_diffuse_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetMaterialSpecularColor(lua_State *L)
{
	elf_color result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialSpecularColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialSpecularColor", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_specular_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetMaterialAmbientColor(lua_State *L)
{
	elf_color result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialAmbientColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialAmbientColor", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_ambient_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetMaterialSpecularPower(lua_State *L)
{
	float result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialSpecularPower", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialSpecularPower", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_specular_power(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetMaterialLighting(lua_State *L)
{
	unsigned char result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialLighting", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialLighting", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_lighting(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetMaterialDiffuseMap(lua_State *L)
{
	elf_material* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialDiffuseMap", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialDiffuseMap", 1, "elf_material");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetMaterialDiffuseMap", 2, "elf_texture");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_material_diffuse_map(arg0, arg1);
	return 0;
}
static int lua_SetMaterialNormalMap(lua_State *L)
{
	elf_material* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialNormalMap", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialNormalMap", 1, "elf_material");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetMaterialNormalMap", 2, "elf_texture");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_material_normal_map(arg0, arg1);
	return 0;
}
static int lua_SetMaterialHeightMap(lua_State *L)
{
	elf_material* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialHeightMap", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialHeightMap", 1, "elf_material");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetMaterialHeightMap", 2, "elf_texture");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_material_height_map(arg0, arg1);
	return 0;
}
static int lua_SetMaterialSpecularMap(lua_State *L)
{
	elf_material* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialSpecularMap", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialSpecularMap", 1, "elf_material");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetMaterialSpecularMap", 2, "elf_texture");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_material_specular_map(arg0, arg1);
	return 0;
}
static int lua_SetMaterialLightMap(lua_State *L)
{
	elf_material* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialLightMap", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialLightMap", 1, "elf_material");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetMaterialLightMap", 2, "elf_texture");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_material_light_map(arg0, arg1);
	return 0;
}
static int lua_SetMaterialCubeMap(lua_State *L)
{
	elf_material* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialCubeMap", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialCubeMap", 1, "elf_material");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetMaterialCubeMap", 2, "elf_texture");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_material_cube_map(arg0, arg1);
	return 0;
}
static int lua_ClearMaterialDiffuseMap(lua_State *L)
{
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearMaterialDiffuseMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "ClearMaterialDiffuseMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_material_diffuse_map(arg0);
	return 0;
}
static int lua_ClearMaterialNormalMap(lua_State *L)
{
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearMaterialNormalMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "ClearMaterialNormalMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_material_normal_map(arg0);
	return 0;
}
static int lua_ClearMaterialHeightMap(lua_State *L)
{
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearMaterialHeightMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "ClearMaterialHeightMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_material_height_map(arg0);
	return 0;
}
static int lua_ClearMaterialSpecularMap(lua_State *L)
{
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearMaterialSpecularMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "ClearMaterialSpecularMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_material_specular_map(arg0);
	return 0;
}
static int lua_ClearMaterialLightMap(lua_State *L)
{
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearMaterialLightMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "ClearMaterialLightMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_material_light_map(arg0);
	return 0;
}
static int lua_ClearMaterialCubeMap(lua_State *L)
{
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearMaterialCubeMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "ClearMaterialCubeMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_material_cube_map(arg0);
	return 0;
}
static int lua_GetMaterialDiffuseMap(lua_State *L)
{
	elf_texture* result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialDiffuseMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialDiffuseMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_diffuse_map(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetMaterialNormalMap(lua_State *L)
{
	elf_texture* result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialNormalMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialNormalMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_normal_map(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetMaterialHeightMap(lua_State *L)
{
	elf_texture* result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialHeightMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialHeightMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_height_map(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetMaterialSpecularMap(lua_State *L)
{
	elf_texture* result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialSpecularMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialSpecularMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_specular_map(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetMaterialLightMap(lua_State *L)
{
	elf_texture* result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialLightMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialLightMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_light_map(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetMaterialCubeMap(lua_State *L)
{
	elf_texture* result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialCubeMap", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialCubeMap", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_cube_map(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetMaterialParallaxScale(lua_State *L)
{
	elf_material* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialParallaxScale", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialParallaxScale", 1, "elf_material");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetMaterialParallaxScale", 2, "number");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_material_parallax_scale(arg0, arg1);
	return 0;
}
static int lua_SetMaterialAlphaTest(lua_State *L)
{
	elf_material* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialAlphaTest", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialAlphaTest", 1, "elf_material");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetMaterialAlphaTest", 2, "boolean");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_material_alpha_test(arg0, arg1);
	return 0;
}
static int lua_SetMaterialAlphaThreshold(lua_State *L)
{
	elf_material* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetMaterialAlphaThreshold", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetMaterialAlphaThreshold", 1, "elf_material");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetMaterialAlphaThreshold", 2, "number");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_material_alpha_threshold(arg0, arg1);
	return 0;
}
static int lua_GetMaterialParallaxScale(lua_State *L)
{
	float result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialParallaxScale", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialParallaxScale", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_parallax_scale(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetMaterialAlphaTest(lua_State *L)
{
	unsigned char result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialAlphaTest", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialAlphaTest", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_alpha_test(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetMaterialAlphaThreshold(lua_State *L)
{
	float result;
	elf_material* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMaterialAlphaThreshold", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "GetMaterialAlphaThreshold", 1, "elf_material");}
	arg0 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_material_alpha_threshold(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_CreateBezierPoint(lua_State *L)
{
	elf_bezier_point* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateBezierPoint", lua_gettop(L), 0);}
	result = elf_create_bezier_point();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetBezierPointPosition(lua_State *L)
{
	elf_bezier_point* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetBezierPointPosition", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_POINT)
		{return lua_fail_arg(L, "SetBezierPointPosition", 1, "elf_bezier_point");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetBezierPointPosition", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetBezierPointPosition", 3, "number");}
	arg0 = (elf_bezier_point*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_bezier_point_position(arg0, arg1, arg2);
	return 0;
}
static int lua_SetBezierPointControl1(lua_State *L)
{
	elf_bezier_point* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetBezierPointControl1", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_POINT)
		{return lua_fail_arg(L, "SetBezierPointControl1", 1, "elf_bezier_point");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetBezierPointControl1", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetBezierPointControl1", 3, "number");}
	arg0 = (elf_bezier_point*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_bezier_point_control1(arg0, arg1, arg2);
	return 0;
}
static int lua_SetBezierPointControl2(lua_State *L)
{
	elf_bezier_point* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetBezierPointControl2", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_POINT)
		{return lua_fail_arg(L, "SetBezierPointControl2", 1, "elf_bezier_point");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetBezierPointControl2", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetBezierPointControl2", 3, "number");}
	arg0 = (elf_bezier_point*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_bezier_point_control2(arg0, arg1, arg2);
	return 0;
}
static int lua_GetBezierPointPosition(lua_State *L)
{
	elf_vec2f result;
	elf_bezier_point* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBezierPointPosition", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_POINT)
		{return lua_fail_arg(L, "GetBezierPointPosition", 1, "elf_bezier_point");}
	arg0 = (elf_bezier_point*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bezier_point_position(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_GetBezierPointControl1(lua_State *L)
{
	elf_vec2f result;
	elf_bezier_point* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBezierPointControl1", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_POINT)
		{return lua_fail_arg(L, "GetBezierPointControl1", 1, "elf_bezier_point");}
	arg0 = (elf_bezier_point*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bezier_point_control1(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_GetBezierPointControl2(lua_State *L)
{
	elf_vec2f result;
	elf_bezier_point* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBezierPointControl2", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_POINT)
		{return lua_fail_arg(L, "GetBezierPointControl2", 1, "elf_bezier_point");}
	arg0 = (elf_bezier_point*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bezier_point_control2(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_CreateBezierCurve(lua_State *L)
{
	elf_bezier_curve* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateBezierCurve", lua_gettop(L), 0);}
	result = elf_create_bezier_curve();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetBezierCurveType(lua_State *L)
{
	elf_bezier_curve* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetBezierCurveType", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_CURVE)
		{return lua_fail_arg(L, "SetBezierCurveType", 1, "elf_bezier_curve");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetBezierCurveType", 2, "number");}
	arg0 = (elf_bezier_curve*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_bezier_curve_type(arg0, arg1);
	return 0;
}
static int lua_GetBezierCurveType(lua_State *L)
{
	int result;
	elf_bezier_curve* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBezierCurveType", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_CURVE)
		{return lua_fail_arg(L, "GetBezierCurveType", 1, "elf_bezier_curve");}
	arg0 = (elf_bezier_curve*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bezier_curve_type(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_AddPointToBezierCurve(lua_State *L)
{
	elf_bezier_curve* arg0;
	elf_bezier_point* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddPointToBezierCurve", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_CURVE)
		{return lua_fail_arg(L, "AddPointToBezierCurve", 1, "elf_bezier_curve");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_BEZIER_POINT)
		{return lua_fail_arg(L, "AddPointToBezierCurve", 2, "elf_bezier_point");}
	arg0 = (elf_bezier_curve*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_bezier_point*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_point_to_bezier_curve(arg0, arg1);
	return 0;
}
static int lua_GetPointFromBezierCurve(lua_State *L)
{
	elf_bezier_point* result;
	elf_bezier_curve* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetPointFromBezierCurve", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_CURVE)
		{return lua_fail_arg(L, "GetPointFromBezierCurve", 1, "elf_bezier_curve");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetPointFromBezierCurve", 2, "number");}
	arg0 = (elf_bezier_curve*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_point_from_bezier_curve(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetBezierCurveValue(lua_State *L)
{
	float result;
	elf_bezier_curve* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetBezierCurveValue", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BEZIER_CURVE)
		{return lua_fail_arg(L, "GetBezierCurveValue", 1, "elf_bezier_curve");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetBezierCurveValue", 2, "number");}
	arg0 = (elf_bezier_curve*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_get_bezier_curve_value(arg0, arg1);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_CreateIpo(lua_State *L)
{
	elf_ipo* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateIpo", lua_gettop(L), 0);}
	result = elf_create_ipo();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_AddCurveToIpo(lua_State *L)
{
	unsigned char result;
	elf_ipo* arg0;
	elf_bezier_curve* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddCurveToIpo", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IPO)
		{return lua_fail_arg(L, "AddCurveToIpo", 1, "elf_ipo");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_BEZIER_CURVE)
		{return lua_fail_arg(L, "AddCurveToIpo", 2, "elf_bezier_curve");}
	arg0 = (elf_ipo*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_bezier_curve*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_add_curve_to_ipo(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetIpoCurveCount(lua_State *L)
{
	int result;
	elf_ipo* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetIpoCurveCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IPO)
		{return lua_fail_arg(L, "GetIpoCurveCount", 1, "elf_ipo");}
	arg0 = (elf_ipo*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_ipo_curve_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetCurveFromIpo(lua_State *L)
{
	elf_bezier_curve* result;
	elf_ipo* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetCurveFromIpo", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IPO)
		{return lua_fail_arg(L, "GetCurveFromIpo", 1, "elf_ipo");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetCurveFromIpo", 2, "number");}
	arg0 = (elf_ipo*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_curve_from_ipo(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetIpoLoc(lua_State *L)
{
	elf_vec3f result;
	elf_ipo* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetIpoLoc", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IPO)
		{return lua_fail_arg(L, "GetIpoLoc", 1, "elf_ipo");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetIpoLoc", 2, "number");}
	arg0 = (elf_ipo*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_get_ipo_loc(arg0, arg1);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetIpoRot(lua_State *L)
{
	elf_vec3f result;
	elf_ipo* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetIpoRot", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IPO)
		{return lua_fail_arg(L, "GetIpoRot", 1, "elf_ipo");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetIpoRot", 2, "number");}
	arg0 = (elf_ipo*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_get_ipo_rot(arg0, arg1);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetIpoScale(lua_State *L)
{
	elf_vec3f result;
	elf_ipo* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetIpoScale", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IPO)
		{return lua_fail_arg(L, "GetIpoScale", 1, "elf_ipo");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetIpoScale", 2, "number");}
	arg0 = (elf_ipo*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_get_ipo_scale(arg0, arg1);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetIpoQua(lua_State *L)
{
	elf_vec4f result;
	elf_ipo* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetIpoQua", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_IPO)
		{return lua_fail_arg(L, "GetIpoQua", 1, "elf_ipo");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetIpoQua", 2, "number");}
	arg0 = (elf_ipo*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_get_ipo_qua(arg0, arg1);
	lua_create_elf_vec4f(L, result);
	return 1;
}
static int lua_CreateProperty(lua_State *L)
{
	elf_property* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateProperty", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateProperty", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_property(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetPropertyType(lua_State *L)
{
	int result;
	elf_property* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetPropertyType", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "GetPropertyType", 1, "elf_property");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_property_type(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetPropertyInt(lua_State *L)
{
	int result;
	elf_property* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetPropertyInt", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "GetPropertyInt", 1, "elf_property");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_property_int(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetPropertyFloat(lua_State *L)
{
	float result;
	elf_property* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetPropertyFloat", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "GetPropertyFloat", 1, "elf_property");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_property_float(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetPropertyString(lua_State *L)
{
	const char* result;
	elf_property* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetPropertyString", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "GetPropertyString", 1, "elf_property");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_property_string(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetPropertyBool(lua_State *L)
{
	unsigned char result;
	elf_property* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetPropertyBool", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "GetPropertyBool", 1, "elf_property");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_property_bool(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetPropertyInt(lua_State *L)
{
	elf_property* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetPropertyInt", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "SetPropertyInt", 1, "elf_property");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetPropertyInt", 2, "number");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_property_int(arg0, arg1);
	return 0;
}
static int lua_SetPropertyFloat(lua_State *L)
{
	elf_property* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetPropertyFloat", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "SetPropertyFloat", 1, "elf_property");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetPropertyFloat", 2, "number");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_property_float(arg0, arg1);
	return 0;
}
static int lua_SetPropertyString(lua_State *L)
{
	elf_property* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetPropertyString", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "SetPropertyString", 1, "elf_property");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetPropertyString", 2, "string");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_property_string(arg0, arg1);
	return 0;
}
static int lua_SetPropertyBool(lua_State *L)
{
	elf_property* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetPropertyBool", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "SetPropertyBool", 1, "elf_property");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetPropertyBool", 2, "boolean");}
	arg0 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_property_bool(arg0, arg1);
	return 0;
}
static int lua_GetActorName(lua_State *L)
{
	const char* result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorName", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetActorFilePath(lua_State *L)
{
	const char* result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorFilePath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorFilePath", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_file_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetActorScript(lua_State *L)
{
	elf_script* result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorScript", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorScript", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_script(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetActorName(lua_State *L)
{
	elf_actor* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetActorName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorName", 1, "elf_actor");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetActorName", 2, "string");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_actor_name(arg0, arg1);
	return 0;
}
static int lua_SetActorScript(lua_State *L)
{
	elf_actor* arg0;
	elf_script* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetActorScript", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorScript", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_SCRIPT)
		{return lua_fail_arg(L, "SetActorScript", 2, "elf_script");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_script*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_actor_script(arg0, arg1);
	return 0;
}
static int lua_ClearActorScript(lua_State *L)
{
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearActorScript", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "ClearActorScript", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_actor_script(arg0);
	return 0;
}
static int lua_SetActorPosition(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorPosition", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorPosition", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorPosition", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorPosition", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorPosition", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_position(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorRotation(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorRotation", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorRotation", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorRotation", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorRotation", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorRotation", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_rotation(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorOrientation(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetActorOrientation", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorOrientation", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorOrientation", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorOrientation", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorOrientation", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetActorOrientation", 5, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_actor_orientation(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_RotateActor(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "RotateActor", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RotateActor", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RotateActor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "RotateActor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "RotateActor", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_rotate_actor(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_RotateActorLocal(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "RotateActorLocal", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RotateActorLocal", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RotateActorLocal", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "RotateActorLocal", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "RotateActorLocal", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_rotate_actor_local(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_MoveActor(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "MoveActor", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "MoveActor", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "MoveActor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "MoveActor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "MoveActor", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_move_actor(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_MoveActorLocal(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "MoveActorLocal", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "MoveActorLocal", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "MoveActorLocal", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "MoveActorLocal", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "MoveActorLocal", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_move_actor_local(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorPositionRelativeTo(lua_State *L)
{
	elf_actor* arg0;
	elf_actor* arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetActorPositionRelativeTo", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorPositionRelativeTo", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "SetActorPositionRelativeTo", 2, "elf_actor");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorPositionRelativeTo", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorPositionRelativeTo", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetActorPositionRelativeTo", 5, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_actor_position_relative_to(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetActorRotationRelativeTo(lua_State *L)
{
	elf_actor* arg0;
	elf_actor* arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetActorRotationRelativeTo", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorRotationRelativeTo", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "SetActorRotationRelativeTo", 2, "elf_actor");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorRotationRelativeTo", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorRotationRelativeTo", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetActorRotationRelativeTo", 5, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_actor_rotation_relative_to(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetActorOrientationRelativeTo(lua_State *L)
{
	elf_actor* arg0;
	elf_actor* arg1;
	float arg2;
	float arg3;
	float arg4;
	float arg5;
	if(lua_gettop(L) != 6) {return lua_fail_arg_count(L, "SetActorOrientationRelativeTo", lua_gettop(L), 6);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorOrientationRelativeTo", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "SetActorOrientationRelativeTo", 2, "elf_actor");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorOrientationRelativeTo", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorOrientationRelativeTo", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetActorOrientationRelativeTo", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "SetActorOrientationRelativeTo", 6, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	elf_set_actor_orientation_relative_to(arg0, arg1, arg2, arg3, arg4, arg5);
	return 0;
}
static int lua_GetActorPosition(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorPosition", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorPosition", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_position(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetActorRotation(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorRotation", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorRotation", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_rotation(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetActorOrientation(lua_State *L)
{
	elf_vec4f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorOrientation", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorOrientation", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_orientation(arg0);
	lua_create_elf_vec4f(L, result);
	return 1;
}
static int lua_SetActorBoundingLengths(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorBoundingLengths", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorBoundingLengths", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorBoundingLengths", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorBoundingLengths", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorBoundingLengths", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_bounding_lengths(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorBoundingOffset(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorBoundingOffset", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorBoundingOffset", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorBoundingOffset", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorBoundingOffset", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorBoundingOffset", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_bounding_offset(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorPhysics(lua_State *L)
{
	elf_actor* arg0;
	int arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetActorPhysics", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorPhysics", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorPhysics", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorPhysics", 3, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_actor_physics(arg0, arg1, arg2);
	return 0;
}
static int lua_IsActorPhysics(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsActorPhysics", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "IsActorPhysics", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_actor_physics(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_DisableActorPhysics(lua_State *L)
{
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "DisableActorPhysics", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "DisableActorPhysics", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_disable_actor_physics(arg0);
	return 0;
}
static int lua_SetActorDamping(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetActorDamping", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorDamping", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorDamping", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorDamping", 3, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_actor_damping(arg0, arg1, arg2);
	return 0;
}
static int lua_SetActorSleepThresholds(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetActorSleepThresholds", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorSleepThresholds", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorSleepThresholds", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorSleepThresholds", 3, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_actor_sleep_thresholds(arg0, arg1, arg2);
	return 0;
}
static int lua_SetActorRestitution(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetActorRestitution", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorRestitution", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorRestitution", 2, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_actor_restitution(arg0, arg1);
	return 0;
}
static int lua_SetActorAnisotropicFriction(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorAnisotropicFriction", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorAnisotropicFriction", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorAnisotropicFriction", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorAnisotropicFriction", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorAnisotropicFriction", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_anisotropic_friction(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorLinearFactor(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorLinearFactor", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorLinearFactor", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorLinearFactor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorLinearFactor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorLinearFactor", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_linear_factor(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorAngularFactor(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorAngularFactor", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorAngularFactor", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorAngularFactor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorAngularFactor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorAngularFactor", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_angular_factor(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_AddForceToActor(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "AddForceToActor", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "AddForceToActor", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "AddForceToActor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "AddForceToActor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "AddForceToActor", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_add_force_to_actor(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_AddForceToActorLocal(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "AddForceToActorLocal", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "AddForceToActorLocal", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "AddForceToActorLocal", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "AddForceToActorLocal", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "AddForceToActorLocal", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_add_force_to_actor_local(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_AddTorqueToActor(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "AddTorqueToActor", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "AddTorqueToActor", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "AddTorqueToActor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "AddTorqueToActor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "AddTorqueToActor", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_add_torque_to_actor(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorLinearVelocity(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorLinearVelocity", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorLinearVelocity", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorLinearVelocity", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorLinearVelocity", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorLinearVelocity", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_linear_velocity(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorLinearVelocityLocal(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorLinearVelocityLocal", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorLinearVelocityLocal", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorLinearVelocityLocal", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorLinearVelocityLocal", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorLinearVelocityLocal", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_linear_velocity_local(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetActorAngularVelocity(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetActorAngularVelocity", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorAngularVelocity", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorAngularVelocity", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetActorAngularVelocity", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetActorAngularVelocity", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_actor_angular_velocity(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_GetActorBoundingLengths(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorBoundingLengths", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorBoundingLengths", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_bounding_lengths(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetActorBoundingOffset(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorBoundingOffset", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorBoundingOffset", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_bounding_offset(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetActorShape(lua_State *L)
{
	int result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorShape", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorShape", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_shape(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorMass(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorMass", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorMass", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_mass(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorLinearDamping(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorLinearDamping", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorLinearDamping", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_linear_damping(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorAngularDamping(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorAngularDamping", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorAngularDamping", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_angular_damping(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorLinearSleepThreshold(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorLinearSleepThreshold", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorLinearSleepThreshold", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_linear_sleep_threshold(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorAngularSleepThreshold(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorAngularSleepThreshold", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorAngularSleepThreshold", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_angular_sleep_threshold(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorRestitution(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorRestitution", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorRestitution", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_restitution(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorAnisotropicFriction(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorAnisotropicFriction", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorAnisotropicFriction", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_anisotropic_friction(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetActorLinearFactor(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorLinearFactor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorLinearFactor", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_linear_factor(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetActorAngularFactor(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorAngularFactor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorAngularFactor", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_angular_factor(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetActorLinearVelocity(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorLinearVelocity", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorLinearVelocity", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_linear_velocity(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetActorAngularVelocity(lua_State *L)
{
	elf_vec3f result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorAngularVelocity", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorAngularVelocity", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_angular_velocity(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_AddHingeJointToActor(lua_State *L)
{
	elf_joint* result;
	elf_actor* arg0;
	elf_actor* arg1;
	const char* arg2;
	float arg3;
	float arg4;
	float arg5;
	float arg6;
	float arg7;
	float arg8;
	if(lua_gettop(L) != 9) {return lua_fail_arg_count(L, "AddHingeJointToActor", lua_gettop(L), 9);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "AddHingeJointToActor", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "AddHingeJointToActor", 2, "elf_actor");}
	if(!lua_isstring(L, 3)) {return lua_fail_arg(L, "AddHingeJointToActor", 3, "string");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "AddHingeJointToActor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "AddHingeJointToActor", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "AddHingeJointToActor", 6, "number");}
	if(!lua_isnumber(L, 7)) {return lua_fail_arg(L, "AddHingeJointToActor", 7, "number");}
	if(!lua_isnumber(L, 8)) {return lua_fail_arg(L, "AddHingeJointToActor", 8, "number");}
	if(!lua_isnumber(L, 9)) {return lua_fail_arg(L, "AddHingeJointToActor", 9, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	arg2 = lua_tostring(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	arg6 = (float)lua_tonumber(L, 7);
	arg7 = (float)lua_tonumber(L, 8);
	arg8 = (float)lua_tonumber(L, 9);
	result = elf_add_hinge_joint_to_actor(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_AddBallJointToActor(lua_State *L)
{
	elf_joint* result;
	elf_actor* arg0;
	elf_actor* arg1;
	const char* arg2;
	float arg3;
	float arg4;
	float arg5;
	if(lua_gettop(L) != 6) {return lua_fail_arg_count(L, "AddBallJointToActor", lua_gettop(L), 6);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "AddBallJointToActor", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "AddBallJointToActor", 2, "elf_actor");}
	if(!lua_isstring(L, 3)) {return lua_fail_arg(L, "AddBallJointToActor", 3, "string");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "AddBallJointToActor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "AddBallJointToActor", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "AddBallJointToActor", 6, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	arg2 = lua_tostring(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	result = elf_add_ball_joint_to_actor(arg0, arg1, arg2, arg3, arg4, arg5);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_AddConeTwistJointToActor(lua_State *L)
{
	elf_joint* result;
	elf_actor* arg0;
	elf_actor* arg1;
	const char* arg2;
	float arg3;
	float arg4;
	float arg5;
	float arg6;
	float arg7;
	float arg8;
	if(lua_gettop(L) != 9) {return lua_fail_arg_count(L, "AddConeTwistJointToActor", lua_gettop(L), 9);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "AddConeTwistJointToActor", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "AddConeTwistJointToActor", 2, "elf_actor");}
	if(!lua_isstring(L, 3)) {return lua_fail_arg(L, "AddConeTwistJointToActor", 3, "string");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "AddConeTwistJointToActor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "AddConeTwistJointToActor", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "AddConeTwistJointToActor", 6, "number");}
	if(!lua_isnumber(L, 7)) {return lua_fail_arg(L, "AddConeTwistJointToActor", 7, "number");}
	if(!lua_isnumber(L, 8)) {return lua_fail_arg(L, "AddConeTwistJointToActor", 8, "number");}
	if(!lua_isnumber(L, 9)) {return lua_fail_arg(L, "AddConeTwistJointToActor", 9, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	arg2 = lua_tostring(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	arg6 = (float)lua_tonumber(L, 7);
	arg7 = (float)lua_tonumber(L, 8);
	arg8 = (float)lua_tonumber(L, 9);
	result = elf_add_cone_twist_joint_to_actor(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetActorJointByName(lua_State *L)
{
	elf_joint* result;
	elf_actor* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetActorJointByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorJointByName", 1, "elf_actor");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetActorJointByName", 2, "string");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_actor_joint_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetActorJointByIndex(lua_State *L)
{
	elf_joint* result;
	elf_actor* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetActorJointByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorJointByIndex", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetActorJointByIndex", 2, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_actor_joint_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_RemoveActorJointByName(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveActorJointByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveActorJointByName", 1, "elf_actor");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "RemoveActorJointByName", 2, "string");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_remove_actor_joint_by_name(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveActorJointByIndex(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveActorJointByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveActorJointByIndex", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveActorJointByIndex", 2, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_actor_joint_by_index(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveActorJointByObject(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	elf_joint* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveActorJointByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveActorJointByObject", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_JOINT)
		{return lua_fail_arg(L, "RemoveActorJointByObject", 2, "elf_joint");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_joint*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_actor_joint_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetActorIpo(lua_State *L)
{
	elf_actor* arg0;
	elf_ipo* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetActorIpo", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorIpo", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_IPO)
		{return lua_fail_arg(L, "SetActorIpo", 2, "elf_ipo");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_ipo*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_actor_ipo(arg0, arg1);
	return 0;
}
static int lua_GetActorIpo(lua_State *L)
{
	elf_ipo* result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorIpo", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorIpo", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_ipo(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetActorIpoFrame(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetActorIpoFrame", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorIpoFrame", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetActorIpoFrame", 2, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_actor_ipo_frame(arg0, arg1);
	return 0;
}
static int lua_PlayActorIpo(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "PlayActorIpo", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "PlayActorIpo", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "PlayActorIpo", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "PlayActorIpo", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "PlayActorIpo", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_play_actor_ipo(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_LoopActorIpo(lua_State *L)
{
	elf_actor* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "LoopActorIpo", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "LoopActorIpo", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "LoopActorIpo", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "LoopActorIpo", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "LoopActorIpo", 4, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_loop_actor_ipo(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_StopActorIpo(lua_State *L)
{
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "StopActorIpo", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "StopActorIpo", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_stop_actor_ipo(arg0);
	return 0;
}
static int lua_PauseActorIpo(lua_State *L)
{
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "PauseActorIpo", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "PauseActorIpo", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_pause_actor_ipo(arg0);
	return 0;
}
static int lua_ResumeActorIpo(lua_State *L)
{
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ResumeActorIpo", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "ResumeActorIpo", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_resume_actor_ipo(arg0);
	return 0;
}
static int lua_GetActorIpoStart(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorIpoStart", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorIpoStart", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_ipo_start(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorIpoEnd(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorIpoEnd", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorIpoEnd", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_ipo_end(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorIpoSpeed(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorIpoSpeed", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorIpoSpeed", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_ipo_speed(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorIpoFrame(lua_State *L)
{
	float result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorIpoFrame", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorIpoFrame", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_ipo_frame(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_IsActorIpoPlaying(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsActorIpoPlaying", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "IsActorIpoPlaying", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_actor_ipo_playing(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsActorIpoPaused(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsActorIpoPaused", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "IsActorIpoPaused", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_actor_ipo_paused(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetActorCollisionCount(lua_State *L)
{
	int result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorCollisionCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorCollisionCount", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_collision_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetActorCollision(lua_State *L)
{
	elf_collision* result;
	elf_actor* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetActorCollision", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorCollision", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetActorCollision", 2, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_actor_collision(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetActorPropertyCount(lua_State *L)
{
	int result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorPropertyCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorPropertyCount", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_property_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_AddPropertyToActor(lua_State *L)
{
	elf_actor* arg0;
	elf_property* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddPropertyToActor", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "AddPropertyToActor", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "AddPropertyToActor", 2, "elf_property");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_property_to_actor(arg0, arg1);
	return 0;
}
static int lua_GetActorPropertyByName(lua_State *L)
{
	elf_property* result;
	elf_actor* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetActorPropertyByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorPropertyByName", 1, "elf_actor");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetActorPropertyByName", 2, "string");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_actor_property_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetActorPropertyByIndex(lua_State *L)
{
	elf_property* result;
	elf_actor* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetActorPropertyByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorPropertyByIndex", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetActorPropertyByIndex", 2, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_actor_property_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_RemoveActorPropertyByName(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveActorPropertyByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveActorPropertyByName", 1, "elf_actor");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "RemoveActorPropertyByName", 2, "string");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_remove_actor_property_by_name(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveActorPropertyByIndex(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveActorPropertyByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveActorPropertyByIndex", 1, "elf_actor");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveActorPropertyByIndex", 2, "number");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_actor_property_by_index(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveActorPropertyByObject(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	elf_property* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveActorPropertyByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveActorPropertyByObject", 1, "elf_actor");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_PROPERTY)
		{return lua_fail_arg(L, "RemoveActorPropertyByObject", 2, "elf_property");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_property*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_actor_property_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveActorProperties(lua_State *L)
{
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "RemoveActorProperties", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveActorProperties", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_remove_actor_properties(arg0);
	return 0;
}
static int lua_SetActorSelected(lua_State *L)
{
	elf_actor* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetActorSelected", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetActorSelected", 1, "elf_actor");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetActorSelected", 2, "boolean");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_actor_selected(arg0, arg1);
	return 0;
}
static int lua_GetActorSelected(lua_State *L)
{
	unsigned char result;
	elf_actor* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetActorSelected", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetActorSelected", 1, "elf_actor");}
	arg0 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_actor_selected(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_CreateCamera(lua_State *L)
{
	elf_camera* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateCamera", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateCamera", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_camera(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetCameraViewport(lua_State *L)
{
	elf_camera* arg0;
	int arg1;
	int arg2;
	int arg3;
	int arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetCameraViewport", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "SetCameraViewport", 1, "elf_camera");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetCameraViewport", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetCameraViewport", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetCameraViewport", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetCameraViewport", 5, "number");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (int)lua_tonumber(L, 3);
	arg3 = (int)lua_tonumber(L, 4);
	arg4 = (int)lua_tonumber(L, 5);
	elf_set_camera_viewport(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetCameraPerspective(lua_State *L)
{
	elf_camera* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetCameraPerspective", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "SetCameraPerspective", 1, "elf_camera");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetCameraPerspective", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetCameraPerspective", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetCameraPerspective", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetCameraPerspective", 5, "number");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_camera_perspective(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetCameraOrthographic(lua_State *L)
{
	elf_camera* arg0;
	int arg1;
	int arg2;
	int arg3;
	int arg4;
	float arg5;
	float arg6;
	if(lua_gettop(L) != 7) {return lua_fail_arg_count(L, "SetCameraOrthographic", lua_gettop(L), 7);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "SetCameraOrthographic", 1, "elf_camera");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetCameraOrthographic", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetCameraOrthographic", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetCameraOrthographic", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetCameraOrthographic", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "SetCameraOrthographic", 6, "number");}
	if(!lua_isnumber(L, 7)) {return lua_fail_arg(L, "SetCameraOrthographic", 7, "number");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (int)lua_tonumber(L, 3);
	arg3 = (int)lua_tonumber(L, 4);
	arg4 = (int)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	arg6 = (float)lua_tonumber(L, 7);
	elf_set_camera_orthographic(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	return 0;
}
static int lua_GetCameraViewportSize(lua_State *L)
{
	elf_vec2i result;
	elf_camera* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCameraViewportSize", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "GetCameraViewportSize", 1, "elf_camera");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_camera_viewport_size(arg0);
	lua_create_elf_vec2i(L, result);
	return 1;
}
static int lua_GetCameraViewportOffset(lua_State *L)
{
	elf_vec2i result;
	elf_camera* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCameraViewportOffset", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "GetCameraViewportOffset", 1, "elf_camera");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_camera_viewport_offset(arg0);
	lua_create_elf_vec2i(L, result);
	return 1;
}
static int lua_GetCameraFov(lua_State *L)
{
	float result;
	elf_camera* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCameraFov", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "GetCameraFov", 1, "elf_camera");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_camera_fov(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetCameraAspect(lua_State *L)
{
	float result;
	elf_camera* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCameraAspect", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "GetCameraAspect", 1, "elf_camera");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_camera_aspect(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetCameraClip(lua_State *L)
{
	elf_vec2f result;
	elf_camera* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCameraClip", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "GetCameraClip", 1, "elf_camera");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_camera_clip(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_GetCameraFarPlaneSize(lua_State *L)
{
	elf_vec2f result;
	elf_camera* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCameraFarPlaneSize", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "GetCameraFarPlaneSize", 1, "elf_camera");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_camera_far_plane_size(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_ProjectCameraPoint(lua_State *L)
{
	elf_vec3f result;
	elf_camera* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "ProjectCameraPoint", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "ProjectCameraPoint", 1, "elf_camera");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "ProjectCameraPoint", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "ProjectCameraPoint", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "ProjectCameraPoint", 4, "number");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	result = elf_project_camera_point(arg0, arg1, arg2, arg3);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_UnProjectCameraPoint(lua_State *L)
{
	elf_vec3f result;
	elf_camera* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "UnProjectCameraPoint", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "UnProjectCameraPoint", 1, "elf_camera");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "UnProjectCameraPoint", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "UnProjectCameraPoint", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "UnProjectCameraPoint", 4, "number");}
	arg0 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	result = elf_un_project_camera_point(arg0, arg1, arg2, arg3);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_CreateVertice(lua_State *L)
{
	elf_vertice* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateVertice", lua_gettop(L), 0);}
	result = elf_create_vertice();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetVerticePosition(lua_State *L)
{
	elf_vertice* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetVerticePosition", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_VERTICE)
		{return lua_fail_arg(L, "SetVerticePosition", 1, "elf_vertice");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetVerticePosition", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetVerticePosition", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetVerticePosition", 4, "number");}
	arg0 = (elf_vertice*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_vertice_position(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetVerticeNormal(lua_State *L)
{
	elf_vertice* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetVerticeNormal", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_VERTICE)
		{return lua_fail_arg(L, "SetVerticeNormal", 1, "elf_vertice");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetVerticeNormal", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetVerticeNormal", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetVerticeNormal", 4, "number");}
	arg0 = (elf_vertice*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_vertice_normal(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetVerticeTexCoord(lua_State *L)
{
	elf_vertice* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetVerticeTexCoord", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_VERTICE)
		{return lua_fail_arg(L, "SetVerticeTexCoord", 1, "elf_vertice");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetVerticeTexCoord", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetVerticeTexCoord", 3, "number");}
	arg0 = (elf_vertice*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_vertice_tex_coord(arg0, arg1, arg2);
	return 0;
}
static int lua_GetVerticePosition(lua_State *L)
{
	elf_vec3f result;
	elf_vertice* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetVerticePosition", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_VERTICE)
		{return lua_fail_arg(L, "GetVerticePosition", 1, "elf_vertice");}
	arg0 = (elf_vertice*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_vertice_position(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetVerticeNormal(lua_State *L)
{
	elf_vec3f result;
	elf_vertice* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetVerticeNormal", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_VERTICE)
		{return lua_fail_arg(L, "GetVerticeNormal", 1, "elf_vertice");}
	arg0 = (elf_vertice*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_vertice_normal(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetVerticeTexCoord(lua_State *L)
{
	elf_vec2f result;
	elf_vertice* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetVerticeTexCoord", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_VERTICE)
		{return lua_fail_arg(L, "GetVerticeTexCoord", 1, "elf_vertice");}
	arg0 = (elf_vertice*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_vertice_tex_coord(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_GetFaceV1(lua_State *L)
{
	int result;
	elf_face* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFaceV1", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FACE)
		{return lua_fail_arg(L, "GetFaceV1", 1, "elf_face");}
	arg0 = (elf_face*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_face_v1(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetFaceV2(lua_State *L)
{
	int result;
	elf_face* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFaceV2", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FACE)
		{return lua_fail_arg(L, "GetFaceV2", 1, "elf_face");}
	arg0 = (elf_face*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_face_v2(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetFaceV3(lua_State *L)
{
	int result;
	elf_face* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFaceV3", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FACE)
		{return lua_fail_arg(L, "GetFaceV3", 1, "elf_face");}
	arg0 = (elf_face*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_face_v3(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_CreateMeshData(lua_State *L)
{
	elf_mesh_data* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateMeshData", lua_gettop(L), 0);}
	result = elf_create_mesh_data();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetMeshDataVerticeCount(lua_State *L)
{
	int result;
	elf_mesh_data* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMeshDataVerticeCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MESH_DATA)
		{return lua_fail_arg(L, "GetMeshDataVerticeCount", 1, "elf_mesh_data");}
	arg0 = (elf_mesh_data*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_mesh_data_vertice_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetMeshDataFaceCount(lua_State *L)
{
	int result;
	elf_mesh_data* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetMeshDataFaceCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MESH_DATA)
		{return lua_fail_arg(L, "GetMeshDataFaceCount", 1, "elf_mesh_data");}
	arg0 = (elf_mesh_data*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_mesh_data_face_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_AddVerticeToMeshData(lua_State *L)
{
	elf_mesh_data* arg0;
	elf_vertice* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddVerticeToMeshData", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MESH_DATA)
		{return lua_fail_arg(L, "AddVerticeToMeshData", 1, "elf_mesh_data");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_VERTICE)
		{return lua_fail_arg(L, "AddVerticeToMeshData", 2, "elf_vertice");}
	arg0 = (elf_mesh_data*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_vertice*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_vertice_to_mesh_data(arg0, arg1);
	return 0;
}
static int lua_AddFaceToMeshData(lua_State *L)
{
	elf_mesh_data* arg0;
	int arg1;
	int arg2;
	int arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "AddFaceToMeshData", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MESH_DATA)
		{return lua_fail_arg(L, "AddFaceToMeshData", 1, "elf_mesh_data");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "AddFaceToMeshData", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "AddFaceToMeshData", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "AddFaceToMeshData", 4, "number");}
	arg0 = (elf_mesh_data*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (int)lua_tonumber(L, 3);
	arg3 = (int)lua_tonumber(L, 4);
	elf_add_face_to_mesh_data(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_GetVerticeFromMeshData(lua_State *L)
{
	elf_vertice* result;
	elf_mesh_data* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetVerticeFromMeshData", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MESH_DATA)
		{return lua_fail_arg(L, "GetVerticeFromMeshData", 1, "elf_mesh_data");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetVerticeFromMeshData", 2, "number");}
	arg0 = (elf_mesh_data*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_vertice_from_mesh_data(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetFaceFromMeshData(lua_State *L)
{
	elf_face* result;
	elf_mesh_data* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetFaceFromMeshData", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MESH_DATA)
		{return lua_fail_arg(L, "GetFaceFromMeshData", 1, "elf_mesh_data");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetFaceFromMeshData", 2, "number");}
	arg0 = (elf_mesh_data*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_face_from_mesh_data(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_CreateModelFromMeshData(lua_State *L)
{
	elf_model* result;
	elf_mesh_data* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateModelFromMeshData", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MESH_DATA)
		{return lua_fail_arg(L, "CreateModelFromMeshData", 1, "elf_mesh_data");}
	arg0 = (elf_mesh_data*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_create_model_from_mesh_data(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetModelName(lua_State *L)
{
	elf_model* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetModelName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "SetModelName", 1, "elf_model");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetModelName", 2, "string");}
	arg0 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_model_name(arg0, arg1);
	return 0;
}
static int lua_GetModelName(lua_State *L)
{
	const char* result;
	elf_model* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetModelName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "GetModelName", 1, "elf_model");}
	arg0 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_model_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetModelFilePath(lua_State *L)
{
	const char* result;
	elf_model* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetModelFilePath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "GetModelFilePath", 1, "elf_model");}
	arg0 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_model_file_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetModelVerticeCount(lua_State *L)
{
	int result;
	elf_model* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetModelVerticeCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "GetModelVerticeCount", 1, "elf_model");}
	arg0 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_model_vertice_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetModelIndiceCount(lua_State *L)
{
	int result;
	elf_model* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetModelIndiceCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "GetModelIndiceCount", 1, "elf_model");}
	arg0 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_model_indice_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetModelBoundingBoxMin(lua_State *L)
{
	elf_vec3f result;
	elf_model* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetModelBoundingBoxMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "GetModelBoundingBoxMin", 1, "elf_model");}
	arg0 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_model_bounding_box_min(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetModelBoundingBoxMax(lua_State *L)
{
	elf_vec3f result;
	elf_model* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetModelBoundingBoxMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "GetModelBoundingBoxMax", 1, "elf_model");}
	arg0 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_model_bounding_box_max(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_CreateEntity(lua_State *L)
{
	elf_entity* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateEntity", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateEntity", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_entity(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GenerateEntityTangents(lua_State *L)
{
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GenerateEntityTangents", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GenerateEntityTangents", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_generate_entity_tangents(arg0);
	return 0;
}
static int lua_SetEntityScale(lua_State *L)
{
	elf_entity* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetEntityScale", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetEntityScale", 1, "elf_entity");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetEntityScale", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetEntityScale", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetEntityScale", 4, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_entity_scale(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_GetEntityScale(lua_State *L)
{
	elf_vec3f result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityScale", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityScale", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_scale(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_SetEntityModel(lua_State *L)
{
	elf_entity* arg0;
	elf_model* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetEntityModel", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetEntityModel", 1, "elf_entity");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "SetEntityModel", 2, "elf_model");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_entity_model(arg0, arg1);
	return 0;
}
static int lua_ClearEntityModel(lua_State *L)
{
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearEntityModel", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "ClearEntityModel", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_entity_model(arg0);
	return 0;
}
static int lua_GetEntityModel(lua_State *L)
{
	elf_model* result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityModel", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityModel", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_model(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetEntityMaterialCount(lua_State *L)
{
	int result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityMaterialCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityMaterialCount", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_material_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_AddEntityMaterial(lua_State *L)
{
	elf_entity* arg0;
	elf_material* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddEntityMaterial", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "AddEntityMaterial", 1, "elf_entity");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "AddEntityMaterial", 2, "elf_material");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_entity_material(arg0, arg1);
	return 0;
}
static int lua_SetEntityMaterial(lua_State *L)
{
	elf_entity* arg0;
	int arg1;
	elf_material* arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetEntityMaterial", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetEntityMaterial", 1, "elf_entity");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetEntityMaterial", 2, "number");}
	if(!lua_isuserdata(L, 3) || ((lua_elf_userdata*)lua_touserdata(L,3))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 3))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetEntityMaterial", 3, "elf_material");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 3))->object;
	elf_set_entity_material(arg0, arg1, arg2);
	return 0;
}
static int lua_RemoveEntityMaterial(lua_State *L)
{
	elf_entity* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveEntityMaterial", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "RemoveEntityMaterial", 1, "elf_entity");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveEntityMaterial", 2, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_remove_entity_material(arg0, arg1);
	return 0;
}
static int lua_GetEntityMaterial(lua_State *L)
{
	elf_material* result;
	elf_entity* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetEntityMaterial", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityMaterial", 1, "elf_entity");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetEntityMaterial", 2, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_entity_material(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetEntityVisible(lua_State *L)
{
	elf_entity* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetEntityVisible", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetEntityVisible", 1, "elf_entity");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetEntityVisible", 2, "boolean");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_entity_visible(arg0, arg1);
	return 0;
}
static int lua_GetEntityVisible(lua_State *L)
{
	unsigned char result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityVisible", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityVisible", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_visible(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetEntityOccluder(lua_State *L)
{
	elf_entity* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetEntityOccluder", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetEntityOccluder", 1, "elf_entity");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetEntityOccluder", 2, "boolean");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_entity_occluder(arg0, arg1);
	return 0;
}
static int lua_GetEntityOccluder(lua_State *L)
{
	unsigned char result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityOccluder", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityOccluder", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_occluder(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetEntityPhysics(lua_State *L)
{
	elf_entity* arg0;
	int arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetEntityPhysics", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetEntityPhysics", 1, "elf_entity");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetEntityPhysics", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetEntityPhysics", 3, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_entity_physics(arg0, arg1, arg2);
	return 0;
}
static int lua_DisableEntityPhysics(lua_State *L)
{
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "DisableEntityPhysics", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "DisableEntityPhysics", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_disable_entity_physics(arg0);
	return 0;
}
static int lua_SetEntityArmature(lua_State *L)
{
	elf_entity* arg0;
	elf_armature* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetEntityArmature", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetEntityArmature", 1, "elf_entity");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_ARMATURE)
		{return lua_fail_arg(L, "SetEntityArmature", 2, "elf_armature");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_armature*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_entity_armature(arg0, arg1);
	return 0;
}
static int lua_SetEntityArmatureFrame(lua_State *L)
{
	elf_entity* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetEntityArmatureFrame", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetEntityArmatureFrame", 1, "elf_entity");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetEntityArmatureFrame", 2, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_entity_armature_frame(arg0, arg1);
	return 0;
}
static int lua_PlayEntityArmature(lua_State *L)
{
	elf_entity* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "PlayEntityArmature", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "PlayEntityArmature", 1, "elf_entity");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "PlayEntityArmature", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "PlayEntityArmature", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "PlayEntityArmature", 4, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_play_entity_armature(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_LoopEntityArmature(lua_State *L)
{
	elf_entity* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "LoopEntityArmature", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "LoopEntityArmature", 1, "elf_entity");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "LoopEntityArmature", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "LoopEntityArmature", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "LoopEntityArmature", 4, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_loop_entity_armature(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_StopEntityArmature(lua_State *L)
{
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "StopEntityArmature", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "StopEntityArmature", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_stop_entity_armature(arg0);
	return 0;
}
static int lua_PauseEntityArmature(lua_State *L)
{
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "PauseEntityArmature", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "PauseEntityArmature", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_pause_entity_armature(arg0);
	return 0;
}
static int lua_ResumeEntityArmature(lua_State *L)
{
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ResumeEntityArmature", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "ResumeEntityArmature", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_resume_entity_armature(arg0);
	return 0;
}
static int lua_GetEntityArmatureStart(lua_State *L)
{
	float result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityArmatureStart", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityArmatureStart", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_armature_start(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetEntityArmatureEnd(lua_State *L)
{
	float result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityArmatureEnd", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityArmatureEnd", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_armature_end(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetEntityArmatureSpeed(lua_State *L)
{
	float result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityArmatureSpeed", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityArmatureSpeed", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_armature_speed(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetEntityArmatureFrame(lua_State *L)
{
	float result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityArmatureFrame", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityArmatureFrame", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_armature_frame(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_IsEntityArmaturePlaying(lua_State *L)
{
	unsigned char result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsEntityArmaturePlaying", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "IsEntityArmaturePlaying", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_entity_armature_playing(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsEntityArmaturePaused(lua_State *L)
{
	unsigned char result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsEntityArmaturePaused", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "IsEntityArmaturePaused", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_entity_armature_paused(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetEntityArmature(lua_State *L)
{
	elf_armature* result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityArmature", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityArmature", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_armature(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetEntityChanged(lua_State *L)
{
	unsigned char result;
	elf_entity* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetEntityChanged", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "GetEntityChanged", 1, "elf_entity");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_entity_changed(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_CreateLight(lua_State *L)
{
	elf_light* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateLight", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateLight", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_light(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetLightType(lua_State *L)
{
	int result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightType", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightType", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_type(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetLightColor(lua_State *L)
{
	elf_color result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightColor", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetLightDistance(lua_State *L)
{
	float result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightDistance", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightDistance", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_distance(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetLightFadeSpeed(lua_State *L)
{
	float result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightFadeSpeed", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightFadeSpeed", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_fade_speed(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetLightShadows(lua_State *L)
{
	unsigned char result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightShadows", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightShadows", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_shadows(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetLightVisible(lua_State *L)
{
	unsigned char result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightVisible", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightVisible", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_visible(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetLightCone(lua_State *L)
{
	elf_vec2f result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightCone", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightCone", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_cone(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_IsLightShaft(lua_State *L)
{
	unsigned char result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsLightShaft", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "IsLightShaft", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_light_shaft(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetLightShaftSize(lua_State *L)
{
	float result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightShaftSize", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightShaftSize", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_shaft_size(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetLightShaftIntensity(lua_State *L)
{
	float result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightShaftIntensity", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightShaftIntensity", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_shaft_intensity(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetLightShaftFadeOff(lua_State *L)
{
	float result;
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLightShaftFadeOff", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "GetLightShaftFadeOff", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_light_shaft_fade_off(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetLightType(lua_State *L)
{
	elf_light* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetLightType", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "SetLightType", 1, "elf_light");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetLightType", 2, "number");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_light_type(arg0, arg1);
	return 0;
}
static int lua_SetLightColor(lua_State *L)
{
	elf_light* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetLightColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "SetLightColor", 1, "elf_light");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetLightColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetLightColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetLightColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetLightColor", 5, "number");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_light_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetLightDistance(lua_State *L)
{
	elf_light* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetLightDistance", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "SetLightDistance", 1, "elf_light");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetLightDistance", 2, "number");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_light_distance(arg0, arg1);
	return 0;
}
static int lua_SetLightFadeSpeed(lua_State *L)
{
	elf_light* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetLightFadeSpeed", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "SetLightFadeSpeed", 1, "elf_light");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetLightFadeSpeed", 2, "number");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_light_fade_speed(arg0, arg1);
	return 0;
}
static int lua_SetLightShadows(lua_State *L)
{
	elf_light* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetLightShadows", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "SetLightShadows", 1, "elf_light");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetLightShadows", 2, "boolean");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_light_shadows(arg0, arg1);
	return 0;
}
static int lua_SetLightVisible(lua_State *L)
{
	elf_light* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetLightVisible", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "SetLightVisible", 1, "elf_light");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetLightVisible", 2, "boolean");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_light_visible(arg0, arg1);
	return 0;
}
static int lua_SetLightCone(lua_State *L)
{
	elf_light* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetLightCone", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "SetLightCone", 1, "elf_light");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetLightCone", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetLightCone", 3, "number");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_light_cone(arg0, arg1, arg2);
	return 0;
}
static int lua_SetLightShaft(lua_State *L)
{
	elf_light* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetLightShaft", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "SetLightShaft", 1, "elf_light");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetLightShaft", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetLightShaft", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetLightShaft", 4, "number");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_light_shaft(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_DisableLightShaft(lua_State *L)
{
	elf_light* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "DisableLightShaft", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "DisableLightShaft", 1, "elf_light");}
	arg0 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_disable_light_shaft(arg0);
	return 0;
}
static int lua_GetBoneArmature(lua_State *L)
{
	elf_armature* result;
	elf_bone* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBoneArmature", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BONE)
		{return lua_fail_arg(L, "GetBoneArmature", 1, "elf_bone");}
	arg0 = (elf_bone*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bone_armature(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetBoneParent(lua_State *L)
{
	elf_bone* result;
	elf_bone* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBoneParent", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BONE)
		{return lua_fail_arg(L, "GetBoneParent", 1, "elf_bone");}
	arg0 = (elf_bone*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bone_parent(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetBoneChildByName(lua_State *L)
{
	elf_bone* result;
	elf_bone* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetBoneChildByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BONE)
		{return lua_fail_arg(L, "GetBoneChildByName", 1, "elf_bone");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetBoneChildByName", 2, "string");}
	arg0 = (elf_bone*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_bone_child_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetBoneChildById(lua_State *L)
{
	elf_bone* result;
	elf_bone* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetBoneChildById", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BONE)
		{return lua_fail_arg(L, "GetBoneChildById", 1, "elf_bone");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetBoneChildById", 2, "number");}
	arg0 = (elf_bone*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_bone_child_by_id(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetBoneChildByIndex(lua_State *L)
{
	elf_bone* result;
	elf_bone* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetBoneChildByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BONE)
		{return lua_fail_arg(L, "GetBoneChildByIndex", 1, "elf_bone");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetBoneChildByIndex", 2, "number");}
	arg0 = (elf_bone*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_bone_child_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetBonePosition(lua_State *L)
{
	elf_vec3f result;
	elf_bone* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBonePosition", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BONE)
		{return lua_fail_arg(L, "GetBonePosition", 1, "elf_bone");}
	arg0 = (elf_bone*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bone_position(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetBoneRotation(lua_State *L)
{
	elf_vec3f result;
	elf_bone* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBoneRotation", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BONE)
		{return lua_fail_arg(L, "GetBoneRotation", 1, "elf_bone");}
	arg0 = (elf_bone*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bone_rotation(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetBoneOrientation(lua_State *L)
{
	elf_vec4f result;
	elf_bone* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetBoneOrientation", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BONE)
		{return lua_fail_arg(L, "GetBoneOrientation", 1, "elf_bone");}
	arg0 = (elf_bone*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_bone_orientation(arg0);
	lua_create_elf_vec4f(L, result);
	return 1;
}
static int lua_CreateArmature(lua_State *L)
{
	elf_armature* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateArmature", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateArmature", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_armature(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetBoneFromArmatureByName(lua_State *L)
{
	elf_bone* result;
	const char* arg0;
	elf_armature* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetBoneFromArmatureByName", lua_gettop(L), 2);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "GetBoneFromArmatureByName", 1, "string");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_ARMATURE)
		{return lua_fail_arg(L, "GetBoneFromArmatureByName", 2, "elf_armature");}
	arg0 = lua_tostring(L, 1);
	arg1 = (elf_armature*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_get_bone_from_armature_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetBoneFromArmatureById(lua_State *L)
{
	elf_bone* result;
	int arg0;
	elf_armature* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetBoneFromArmatureById", lua_gettop(L), 2);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "GetBoneFromArmatureById", 1, "number");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_ARMATURE)
		{return lua_fail_arg(L, "GetBoneFromArmatureById", 2, "elf_armature");}
	arg0 = (int)lua_tonumber(L, 1);
	arg1 = (elf_armature*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_get_bone_from_armature_by_id(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_CreateParticles(lua_State *L)
{
	elf_particles* result;
	const char* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "CreateParticles", lua_gettop(L), 2);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateParticles", 1, "string");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "CreateParticles", 2, "number");}
	arg0 = lua_tostring(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_create_particles(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetParticlesName(lua_State *L)
{
	const char* result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesName", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetParticlesFilePath(lua_State *L)
{
	const char* result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesFilePath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesFilePath", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_file_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_SetParticlesMaxCount(lua_State *L)
{
	elf_particles* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetParticlesMaxCount", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesMaxCount", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesMaxCount", 2, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_particles_max_count(arg0, arg1);
	return 0;
}
static int lua_SetParticlesDrawMode(lua_State *L)
{
	elf_particles* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetParticlesDrawMode", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesDrawMode", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesDrawMode", 2, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_particles_draw_mode(arg0, arg1);
	return 0;
}
static int lua_SetParticlesTexture(lua_State *L)
{
	elf_particles* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetParticlesTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesTexture", 1, "elf_particles");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetParticlesTexture", 2, "elf_texture");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_particles_texture(arg0, arg1);
	return 0;
}
static int lua_ClearParticlesTexture(lua_State *L)
{
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearParticlesTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "ClearParticlesTexture", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_particles_texture(arg0);
	return 0;
}
static int lua_SetParticlesModel(lua_State *L)
{
	elf_particles* arg0;
	elf_model* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetParticlesModel", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesModel", 1, "elf_particles");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_MODEL)
		{return lua_fail_arg(L, "SetParticlesModel", 2, "elf_model");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_model*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_particles_model(arg0, arg1);
	return 0;
}
static int lua_ClearParticlesModel(lua_State *L)
{
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearParticlesModel", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "ClearParticlesModel", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_particles_model(arg0);
	return 0;
}
static int lua_SetParticlesEntity(lua_State *L)
{
	elf_particles* arg0;
	elf_entity* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetParticlesEntity", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesEntity", 1, "elf_particles");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "SetParticlesEntity", 2, "elf_entity");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_particles_entity(arg0, arg1);
	return 0;
}
static int lua_ClearParticlesEntity(lua_State *L)
{
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ClearParticlesEntity", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "ClearParticlesEntity", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_clear_particles_entity(arg0);
	return 0;
}
static int lua_SetParticlesGravity(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetParticlesGravity", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesGravity", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesGravity", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesGravity", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetParticlesGravity", 4, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_particles_gravity(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetParticlesSpawnDelay(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetParticlesSpawnDelay", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesSpawnDelay", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesSpawnDelay", 2, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_particles_spawn_delay(arg0, arg1);
	return 0;
}
static int lua_SetParticlesSpawn(lua_State *L)
{
	elf_particles* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetParticlesSpawn", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesSpawn", 1, "elf_particles");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetParticlesSpawn", 2, "boolean");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_particles_spawn(arg0, arg1);
	return 0;
}
static int lua_SetParticlesSize(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetParticlesSize", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesSize", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesSize", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesSize", 3, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_particles_size(arg0, arg1, arg2);
	return 0;
}
static int lua_SetParticlesSizeGrowth(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetParticlesSizeGrowth", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesSizeGrowth", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesSizeGrowth", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesSizeGrowth", 3, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_particles_size_growth(arg0, arg1, arg2);
	return 0;
}
static int lua_SetParticlesRotation(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetParticlesRotation", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesRotation", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesRotation", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesRotation", 3, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_particles_rotation(arg0, arg1, arg2);
	return 0;
}
static int lua_SetParticlesRotationGrowth(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetParticlesRotationGrowth", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesRotationGrowth", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesRotationGrowth", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesRotationGrowth", 3, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_particles_rotation_growth(arg0, arg1, arg2);
	return 0;
}
static int lua_SetParticlesLifeSpan(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetParticlesLifeSpan", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesLifeSpan", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesLifeSpan", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesLifeSpan", 3, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_particles_life_span(arg0, arg1, arg2);
	return 0;
}
static int lua_SetParticlesFadeSpeed(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetParticlesFadeSpeed", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesFadeSpeed", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesFadeSpeed", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesFadeSpeed", 3, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_particles_fade_speed(arg0, arg1, arg2);
	return 0;
}
static int lua_SetParticlesPositionMin(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetParticlesPositionMin", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesPositionMin", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesPositionMin", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesPositionMin", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetParticlesPositionMin", 4, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_particles_position_min(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetParticlesPositionMax(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetParticlesPositionMax", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesPositionMax", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesPositionMax", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesPositionMax", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetParticlesPositionMax", 4, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_particles_position_max(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetParticlesVelocityMin(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetParticlesVelocityMin", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesVelocityMin", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesVelocityMin", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesVelocityMin", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetParticlesVelocityMin", 4, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_particles_velocity_min(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetParticlesVelocityMax(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetParticlesVelocityMax", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesVelocityMax", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesVelocityMax", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesVelocityMax", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetParticlesVelocityMax", 4, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_particles_velocity_max(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_SetParticlesColorMin(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetParticlesColorMin", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesColorMin", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesColorMin", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesColorMin", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetParticlesColorMin", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetParticlesColorMin", 5, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_particles_color_min(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetParticlesColorMax(lua_State *L)
{
	elf_particles* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetParticlesColorMax", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "SetParticlesColorMax", 1, "elf_particles");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetParticlesColorMax", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetParticlesColorMax", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetParticlesColorMax", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetParticlesColorMax", 5, "number");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_particles_color_max(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_GetParticlesMaxCount(lua_State *L)
{
	int result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesMaxCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesMaxCount", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_max_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesCount(lua_State *L)
{
	int result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesCount", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesDrawMode(lua_State *L)
{
	int result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesDrawMode", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesDrawMode", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_draw_mode(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesTexture(lua_State *L)
{
	elf_texture* result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesTexture", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetParticlesModel(lua_State *L)
{
	elf_model* result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesModel", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesModel", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_model(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetParticlesEntity(lua_State *L)
{
	elf_entity* result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesEntity", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesEntity", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_entity(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetParticlesGravity(lua_State *L)
{
	elf_vec3f result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesGravity", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesGravity", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_gravity(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetParticlesSpawnDelay(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesSpawnDelay", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesSpawnDelay", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_spawn_delay(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesSpawn(lua_State *L)
{
	unsigned char result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesSpawn", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesSpawn", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_spawn(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetParticlesSizeMin(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesSizeMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesSizeMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_size_min(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesSizeMax(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesSizeMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesSizeMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_size_max(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesSizeGrowthMin(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesSizeGrowthMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesSizeGrowthMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_size_growth_min(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesSizeGrowthMax(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesSizeGrowthMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesSizeGrowthMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_size_growth_max(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesRotationMin(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesRotationMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesRotationMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_rotation_min(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesRotationMax(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesRotationMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesRotationMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_rotation_max(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesRotationGrowthMin(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesRotationGrowthMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesRotationGrowthMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_rotation_growth_min(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesRotationGrowthMax(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesRotationGrowthMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesRotationGrowthMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_rotation_growth_max(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesLifeSpanMin(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesLifeSpanMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesLifeSpanMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_life_span_min(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesLifeSpanMax(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesLifeSpanMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesLifeSpanMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_life_span_max(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesFadeSpeedMin(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesFadeSpeedMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesFadeSpeedMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_fade_speed_min(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesFadeSpeedMax(lua_State *L)
{
	float result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesFadeSpeedMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesFadeSpeedMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_fade_speed_max(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetParticlesPositionMin(lua_State *L)
{
	elf_vec3f result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesPositionMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesPositionMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_position_min(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetParticlesPositionMax(lua_State *L)
{
	elf_vec3f result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesPositionMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesPositionMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_position_max(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetParticlesVelocityMin(lua_State *L)
{
	elf_vec3f result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesVelocityMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesVelocityMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_velocity_min(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetParticlesVelocityMax(lua_State *L)
{
	elf_vec3f result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesVelocityMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesVelocityMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_velocity_max(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetParticlesColorMin(lua_State *L)
{
	elf_color result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesColorMin", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesColorMin", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_color_min(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetParticlesColorMax(lua_State *L)
{
	elf_color result;
	elf_particles* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetParticlesColorMax", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "GetParticlesColorMax", 1, "elf_particles");}
	arg0 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_particles_color_max(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_CreateSprite(lua_State *L)
{
	elf_sprite* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateSprite", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateSprite", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_sprite(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetSpriteMaterial(lua_State *L)
{
	elf_sprite* arg0;
	elf_material* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSpriteMaterial", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "SetSpriteMaterial", 1, "elf_sprite");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_MATERIAL)
		{return lua_fail_arg(L, "SetSpriteMaterial", 2, "elf_material");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_material*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_sprite_material(arg0, arg1);
	return 0;
}
static int lua_SetSpriteScale(lua_State *L)
{
	elf_sprite* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetSpriteScale", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "SetSpriteScale", 1, "elf_sprite");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetSpriteScale", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetSpriteScale", 3, "number");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_sprite_scale(arg0, arg1, arg2);
	return 0;
}
static int lua_SetSpriteFaceCamera(lua_State *L)
{
	elf_sprite* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSpriteFaceCamera", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "SetSpriteFaceCamera", 1, "elf_sprite");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetSpriteFaceCamera", 2, "boolean");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_sprite_face_camera(arg0, arg1);
	return 0;
}
static int lua_GetSpriteMaterial(lua_State *L)
{
	elf_material* result;
	elf_sprite* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSpriteMaterial", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "GetSpriteMaterial", 1, "elf_sprite");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_sprite_material(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSpriteScale(lua_State *L)
{
	elf_vec2f result;
	elf_sprite* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSpriteScale", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "GetSpriteScale", 1, "elf_sprite");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_sprite_scale(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_GetSpriteFaceCamera(lua_State *L)
{
	unsigned char result;
	elf_sprite* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSpriteFaceCamera", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "GetSpriteFaceCamera", 1, "elf_sprite");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_sprite_face_camera(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetSpriteVisible(lua_State *L)
{
	elf_sprite* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSpriteVisible", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "SetSpriteVisible", 1, "elf_sprite");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetSpriteVisible", 2, "boolean");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_sprite_visible(arg0, arg1);
	return 0;
}
static int lua_GetSpriteVisible(lua_State *L)
{
	unsigned char result;
	elf_sprite* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSpriteVisible", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "GetSpriteVisible", 1, "elf_sprite");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_sprite_visible(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetSpriteOccluder(lua_State *L)
{
	elf_sprite* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSpriteOccluder", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "SetSpriteOccluder", 1, "elf_sprite");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetSpriteOccluder", 2, "boolean");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_sprite_occluder(arg0, arg1);
	return 0;
}
static int lua_GetSpriteOccluder(lua_State *L)
{
	unsigned char result;
	elf_sprite* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSpriteOccluder", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "GetSpriteOccluder", 1, "elf_sprite");}
	arg0 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_sprite_occluder(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_CreateScene(lua_State *L)
{
	elf_scene* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateScene", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateScene", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_scene(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_CreateSceneFromFile(lua_State *L)
{
	elf_scene* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateSceneFromFile", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateSceneFromFile", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_scene_from_file(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SaveScene(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SaveScene", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "SaveScene", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SaveScene", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_save_scene(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetSceneAmbientColor(lua_State *L)
{
	elf_scene* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetSceneAmbientColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "SetSceneAmbientColor", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetSceneAmbientColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetSceneAmbientColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetSceneAmbientColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetSceneAmbientColor", 5, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_scene_ambient_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_GetSceneAmbientColor(lua_State *L)
{
	elf_color result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneAmbientColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneAmbientColor", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_ambient_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_SetSceneGravity(lua_State *L)
{
	elf_scene* arg0;
	float arg1;
	float arg2;
	float arg3;
	if(lua_gettop(L) != 4) {return lua_fail_arg_count(L, "SetSceneGravity", lua_gettop(L), 4);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "SetSceneGravity", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetSceneGravity", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetSceneGravity", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetSceneGravity", 4, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	elf_set_scene_gravity(arg0, arg1, arg2, arg3);
	return 0;
}
static int lua_GetSceneGravity(lua_State *L)
{
	elf_vec3f result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneGravity", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneGravity", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_gravity(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_SetScenePhysics(lua_State *L)
{
	elf_scene* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetScenePhysics", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "SetScenePhysics", 1, "elf_scene");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetScenePhysics", 2, "boolean");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_scene_physics(arg0, arg1);
	return 0;
}
static int lua_GetScenePhysics(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetScenePhysics", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetScenePhysics", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_physics(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetSceneRunScripts(lua_State *L)
{
	elf_scene* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSceneRunScripts", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "SetSceneRunScripts", 1, "elf_scene");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetSceneRunScripts", 2, "boolean");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_scene_run_scripts(arg0, arg1);
	return 0;
}
static int lua_GetSceneRunScripts(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetSceneRunScripts", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneRunScripts", 1, "elf_scene");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "GetSceneRunScripts", 2, "boolean");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	result = elf_get_scene_run_scripts(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetSceneName(lua_State *L)
{
	const char* result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneName", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetSceneFilePath(lua_State *L)
{
	const char* result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneFilePath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneFilePath", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_file_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetSceneCameraCount(lua_State *L)
{
	int result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneCameraCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneCameraCount", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_camera_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetSceneEntityCount(lua_State *L)
{
	int result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneEntityCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneEntityCount", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_entity_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetSceneLightCount(lua_State *L)
{
	int result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneLightCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneLightCount", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_light_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetSceneArmatureCount(lua_State *L)
{
	int result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneArmatureCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneArmatureCount", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_armature_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetSceneParticlesCount(lua_State *L)
{
	int result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneParticlesCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneParticlesCount", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_particles_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetSceneSpriteCount(lua_State *L)
{
	int result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneSpriteCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneSpriteCount", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_sprite_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_AddCameraToScene(lua_State *L)
{
	elf_scene* arg0;
	elf_camera* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddCameraToScene", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "AddCameraToScene", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "AddCameraToScene", 2, "elf_camera");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_camera_to_scene(arg0, arg1);
	return 0;
}
static int lua_AddEntityToScene(lua_State *L)
{
	elf_scene* arg0;
	elf_entity* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddEntityToScene", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "AddEntityToScene", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "AddEntityToScene", 2, "elf_entity");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_entity_to_scene(arg0, arg1);
	return 0;
}
static int lua_AddLightToScene(lua_State *L)
{
	elf_scene* arg0;
	elf_light* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddLightToScene", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "AddLightToScene", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "AddLightToScene", 2, "elf_light");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_light_to_scene(arg0, arg1);
	return 0;
}
static int lua_AddParticlesToScene(lua_State *L)
{
	elf_scene* arg0;
	elf_particles* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddParticlesToScene", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "AddParticlesToScene", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "AddParticlesToScene", 2, "elf_particles");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_particles_to_scene(arg0, arg1);
	return 0;
}
static int lua_AddSpriteToScene(lua_State *L)
{
	elf_scene* arg0;
	elf_sprite* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddSpriteToScene", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "AddSpriteToScene", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "AddSpriteToScene", 2, "elf_sprite");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_add_sprite_to_scene(arg0, arg1);
	return 0;
}
static int lua_SetSceneActiveCamera(lua_State *L)
{
	elf_scene* arg0;
	elf_camera* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSceneActiveCamera", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "SetSceneActiveCamera", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "SetSceneActiveCamera", 2, "elf_camera");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_scene_active_camera(arg0, arg1);
	return 0;
}
static int lua_GetSceneActiveCamera(lua_State *L)
{
	elf_camera* result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneActiveCamera", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneActiveCamera", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_active_camera(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSceneRayCastResult(lua_State *L)
{
	elf_collision* result;
	elf_scene* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	float arg5;
	float arg6;
	if(lua_gettop(L) != 7) {return lua_fail_arg_count(L, "GetSceneRayCastResult", lua_gettop(L), 7);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneRayCastResult", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetSceneRayCastResult", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "GetSceneRayCastResult", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "GetSceneRayCastResult", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "GetSceneRayCastResult", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "GetSceneRayCastResult", 6, "number");}
	if(!lua_isnumber(L, 7)) {return lua_fail_arg(L, "GetSceneRayCastResult", 7, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	arg6 = (float)lua_tonumber(L, 7);
	result = elf_get_scene_ray_cast_result(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSceneRayCastResults(lua_State *L)
{
	elf_list* result;
	elf_scene* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	float arg5;
	float arg6;
	if(lua_gettop(L) != 7) {return lua_fail_arg_count(L, "GetSceneRayCastResults", lua_gettop(L), 7);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneRayCastResults", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetSceneRayCastResults", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "GetSceneRayCastResults", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "GetSceneRayCastResults", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "GetSceneRayCastResults", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "GetSceneRayCastResults", 6, "number");}
	if(!lua_isnumber(L, 7)) {return lua_fail_arg(L, "GetSceneRayCastResults", 7, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	arg6 = (float)lua_tonumber(L, 7);
	result = elf_get_scene_ray_cast_results(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetDebugSceneRayCastResult(lua_State *L)
{
	elf_collision* result;
	elf_scene* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	float arg5;
	float arg6;
	if(lua_gettop(L) != 7) {return lua_fail_arg_count(L, "GetDebugSceneRayCastResult", lua_gettop(L), 7);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetDebugSceneRayCastResult", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetDebugSceneRayCastResult", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "GetDebugSceneRayCastResult", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "GetDebugSceneRayCastResult", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "GetDebugSceneRayCastResult", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "GetDebugSceneRayCastResult", 6, "number");}
	if(!lua_isnumber(L, 7)) {return lua_fail_arg(L, "GetDebugSceneRayCastResult", 7, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	arg6 = (float)lua_tonumber(L, 7);
	result = elf_get_debug_scene_ray_cast_result(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetDebugSceneRayCastResults(lua_State *L)
{
	elf_list* result;
	elf_scene* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	float arg5;
	float arg6;
	if(lua_gettop(L) != 7) {return lua_fail_arg_count(L, "GetDebugSceneRayCastResults", lua_gettop(L), 7);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetDebugSceneRayCastResults", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetDebugSceneRayCastResults", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "GetDebugSceneRayCastResults", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "GetDebugSceneRayCastResults", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "GetDebugSceneRayCastResults", 5, "number");}
	if(!lua_isnumber(L, 6)) {return lua_fail_arg(L, "GetDebugSceneRayCastResults", 6, "number");}
	if(!lua_isnumber(L, 7)) {return lua_fail_arg(L, "GetDebugSceneRayCastResults", 7, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	arg5 = (float)lua_tonumber(L, 6);
	arg6 = (float)lua_tonumber(L, 7);
	result = elf_get_debug_scene_ray_cast_results(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetCameraByIndex(lua_State *L)
{
	elf_camera* result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetCameraByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetCameraByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetCameraByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_camera_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetEntityByIndex(lua_State *L)
{
	elf_entity* result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetEntityByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetEntityByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetEntityByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_entity_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetLightByIndex(lua_State *L)
{
	elf_light* result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetLightByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetLightByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetLightByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_light_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetArmatureByIndex(lua_State *L)
{
	elf_armature* result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetArmatureByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetArmatureByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetArmatureByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_armature_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetParticlesByIndex(lua_State *L)
{
	elf_particles* result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetParticlesByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetParticlesByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetParticlesByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_particles_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSpriteByIndex(lua_State *L)
{
	elf_sprite* result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetSpriteByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSpriteByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetSpriteByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_sprite_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetTextureByName(lua_State *L)
{
	elf_texture* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetTextureByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetTextureByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetTextureByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_texture_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetMaterialByName(lua_State *L)
{
	elf_material* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetMaterialByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetMaterialByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetMaterialByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_material_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetModelByName(lua_State *L)
{
	elf_model* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetModelByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetModelByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetModelByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_model_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetScriptByName(lua_State *L)
{
	elf_script* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetScriptByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetScriptByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetScriptByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_script_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetCameraByName(lua_State *L)
{
	elf_camera* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetCameraByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetCameraByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetCameraByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_camera_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetEntityByName(lua_State *L)
{
	elf_entity* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetEntityByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetEntityByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetEntityByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_entity_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetLightByName(lua_State *L)
{
	elf_light* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetLightByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetLightByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetLightByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_light_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetArmatureByName(lua_State *L)
{
	elf_armature* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetArmatureByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetArmatureByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetArmatureByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_armature_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetParticlesByName(lua_State *L)
{
	elf_particles* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetParticlesByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetParticlesByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetParticlesByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_particles_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSpriteByName(lua_State *L)
{
	elf_sprite* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetSpriteByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSpriteByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetSpriteByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_sprite_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetActorByName(lua_State *L)
{
	elf_actor* result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetActorByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetActorByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetActorByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_actor_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_RemoveCameraByName(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveCameraByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveCameraByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "RemoveCameraByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_remove_camera_by_name(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveEntityByName(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveEntityByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveEntityByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "RemoveEntityByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_remove_entity_by_name(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveLightByName(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveLightByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveLightByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "RemoveLightByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_remove_light_by_name(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveParticlesByName(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveParticlesByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveParticlesByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "RemoveParticlesByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_remove_particles_by_name(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveSpriteByName(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveSpriteByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveSpriteByName", 1, "elf_scene");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "RemoveSpriteByName", 2, "string");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_remove_sprite_by_name(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveCameraByIndex(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveCameraByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveCameraByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveCameraByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_camera_by_index(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveEntityByIndex(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveEntityByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveEntityByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveEntityByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_entity_by_index(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveLightByIndex(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveLightByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveLightByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveLightByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_light_by_index(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveParticlesByIndex(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveParticlesByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveParticlesByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveParticlesByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_particles_by_index(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveSpriteByIndex(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveSpriteByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveSpriteByIndex", 1, "elf_scene");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveSpriteByIndex", 2, "number");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_sprite_by_index(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveCameraByObject(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	elf_camera* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveCameraByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveCameraByObject", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_CAMERA)
		{return lua_fail_arg(L, "RemoveCameraByObject", 2, "elf_camera");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_camera*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_camera_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveEntityByObject(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	elf_entity* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveEntityByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveEntityByObject", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "RemoveEntityByObject", 2, "elf_entity");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_entity_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveLightByObject(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	elf_light* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveLightByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveLightByObject", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_LIGHT)
		{return lua_fail_arg(L, "RemoveLightByObject", 2, "elf_light");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_light*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_light_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveParticlesByObject(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	elf_particles* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveParticlesByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveParticlesByObject", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_PARTICLES)
		{return lua_fail_arg(L, "RemoveParticlesByObject", 2, "elf_particles");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_particles*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_particles_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveSpriteByObject(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	elf_sprite* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveSpriteByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveSpriteByObject", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_SPRITE)
		{return lua_fail_arg(L, "RemoveSpriteByObject", 2, "elf_sprite");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_sprite*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_sprite_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveActorByObject(lua_State *L)
{
	unsigned char result;
	elf_scene* arg0;
	elf_actor* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveActorByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "RemoveActorByObject", 1, "elf_scene");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_actor(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "RemoveActorByObject", 2, "elf_actor");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_actor*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_actor_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetSceneScripts(lua_State *L)
{
	elf_list* result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneScripts", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneScripts", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_scripts(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSceneTextures(lua_State *L)
{
	elf_list* result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneTextures", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneTextures", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_textures(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSceneMaterials(lua_State *L)
{
	elf_list* result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneMaterials", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneMaterials", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_materials(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSceneModels(lua_State *L)
{
	elf_list* result;
	elf_scene* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSceneModels", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCENE)
		{return lua_fail_arg(L, "GetSceneModels", 1, "elf_scene");}
	arg0 = (elf_scene*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_scene_models(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_CreateScript(lua_State *L)
{
	elf_script* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateScript", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateScript", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_script(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_CreateScriptFromFile(lua_State *L)
{
	elf_script* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateScriptFromFile", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateScriptFromFile", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_script_from_file(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetScriptName(lua_State *L)
{
	elf_script* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetScriptName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCRIPT)
		{return lua_fail_arg(L, "SetScriptName", 1, "elf_script");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetScriptName", 2, "string");}
	arg0 = (elf_script*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_script_name(arg0, arg1);
	return 0;
}
static int lua_GetScriptName(lua_State *L)
{
	const char* result;
	elf_script* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetScriptName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCRIPT)
		{return lua_fail_arg(L, "GetScriptName", 1, "elf_script");}
	arg0 = (elf_script*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_script_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetScriptFilePath(lua_State *L)
{
	const char* result;
	elf_script* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetScriptFilePath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCRIPT)
		{return lua_fail_arg(L, "GetScriptFilePath", 1, "elf_script");}
	arg0 = (elf_script*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_script_file_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_SetScriptText(lua_State *L)
{
	elf_script* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetScriptText", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCRIPT)
		{return lua_fail_arg(L, "SetScriptText", 1, "elf_script");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetScriptText", 2, "string");}
	arg0 = (elf_script*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_script_text(arg0, arg1);
	return 0;
}
static int lua_IsScriptError(lua_State *L)
{
	unsigned char result;
	elf_script* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsScriptError", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCRIPT)
		{return lua_fail_arg(L, "IsScriptError", 1, "elf_script");}
	arg0 = (elf_script*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_script_error(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RunString(lua_State *L)
{
	unsigned char result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "RunString", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "RunString", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_run_string(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RunScript(lua_State *L)
{
	unsigned char result;
	elf_script* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "RunScript", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCRIPT)
		{return lua_fail_arg(L, "RunScript", 1, "elf_script");}
	arg0 = (elf_script*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_run_script(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SetAudioVolume(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetAudioVolume", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetAudioVolume", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_set_audio_volume(arg0);
	return 0;
}
static int lua_GetAudioVolume(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetAudioVolume", lua_gettop(L), 0);}
	result = elf_get_audio_volume();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetAudioRolloff(lua_State *L)
{
	float arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetAudioRolloff", lua_gettop(L), 1);}
	if(!lua_isnumber(L, 1)) {return lua_fail_arg(L, "SetAudioRolloff", 1, "number");}
	arg0 = (float)lua_tonumber(L, 1);
	elf_set_audio_rolloff(arg0);
	return 0;
}
static int lua_GetAudioRolloff(lua_State *L)
{
	float result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetAudioRolloff", lua_gettop(L), 0);}
	result = elf_get_audio_rolloff();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_LoadSound(lua_State *L)
{
	elf_sound* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "LoadSound", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "LoadSound", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_load_sound(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_LoadStreamedSound(lua_State *L)
{
	elf_sound* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "LoadStreamedSound", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "LoadStreamedSound", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_load_streamed_sound(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSoundFileType(lua_State *L)
{
	int result;
	elf_sound* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSoundFileType", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SOUND)
		{return lua_fail_arg(L, "GetSoundFileType", 1, "elf_sound");}
	arg0 = (elf_sound*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_sound_file_type(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_PlaySound(lua_State *L)
{
	elf_audio_source* result;
	elf_sound* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "PlaySound", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SOUND)
		{return lua_fail_arg(L, "PlaySound", 1, "elf_sound");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "PlaySound", 2, "number");}
	arg0 = (elf_sound*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_play_sound(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_PlayEntitySound(lua_State *L)
{
	elf_audio_source* result;
	elf_entity* arg0;
	elf_sound* arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "PlayEntitySound", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "PlayEntitySound", 1, "elf_entity");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_SOUND)
		{return lua_fail_arg(L, "PlayEntitySound", 2, "elf_sound");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "PlayEntitySound", 3, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_sound*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	arg2 = (float)lua_tonumber(L, 3);
	result = elf_play_entity_sound(arg0, arg1, arg2);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_LoopSound(lua_State *L)
{
	elf_audio_source* result;
	elf_sound* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "LoopSound", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SOUND)
		{return lua_fail_arg(L, "LoopSound", 1, "elf_sound");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "LoopSound", 2, "number");}
	arg0 = (elf_sound*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	result = elf_loop_sound(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_LoopEntitySound(lua_State *L)
{
	elf_audio_source* result;
	elf_entity* arg0;
	elf_sound* arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "LoopEntitySound", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_ENTITY)
		{return lua_fail_arg(L, "LoopEntitySound", 1, "elf_entity");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_SOUND)
		{return lua_fail_arg(L, "LoopEntitySound", 2, "elf_sound");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "LoopEntitySound", 3, "number");}
	arg0 = (elf_entity*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_sound*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	arg2 = (float)lua_tonumber(L, 3);
	result = elf_loop_entity_sound(arg0, arg1, arg2);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetSoundVolume(lua_State *L)
{
	elf_audio_source* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSoundVolume", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_AUDIO_SOURCE)
		{return lua_fail_arg(L, "SetSoundVolume", 1, "elf_audio_source");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetSoundVolume", 2, "number");}
	arg0 = (elf_audio_source*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_sound_volume(arg0, arg1);
	return 0;
}
static int lua_GetSoundVolume(lua_State *L)
{
	float result;
	elf_audio_source* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSoundVolume", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_AUDIO_SOURCE)
		{return lua_fail_arg(L, "GetSoundVolume", 1, "elf_audio_source");}
	arg0 = (elf_audio_source*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_sound_volume(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_PauseSound(lua_State *L)
{
	elf_audio_source* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "PauseSound", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_AUDIO_SOURCE)
		{return lua_fail_arg(L, "PauseSound", 1, "elf_audio_source");}
	arg0 = (elf_audio_source*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_pause_sound(arg0);
	return 0;
}
static int lua_ResumeSound(lua_State *L)
{
	elf_audio_source* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ResumeSound", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_AUDIO_SOURCE)
		{return lua_fail_arg(L, "ResumeSound", 1, "elf_audio_source");}
	arg0 = (elf_audio_source*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_resume_sound(arg0);
	return 0;
}
static int lua_StopSound(lua_State *L)
{
	elf_audio_source* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "StopSound", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_AUDIO_SOURCE)
		{return lua_fail_arg(L, "StopSound", 1, "elf_audio_source");}
	arg0 = (elf_audio_source*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_stop_sound(arg0);
	return 0;
}
static int lua_IsSoundPlaying(lua_State *L)
{
	unsigned char result;
	elf_audio_source* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsSoundPlaying", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_AUDIO_SOURCE)
		{return lua_fail_arg(L, "IsSoundPlaying", 1, "elf_audio_source");}
	arg0 = (elf_audio_source*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_sound_playing(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsSoundPaused(lua_State *L)
{
	unsigned char result;
	elf_audio_source* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "IsSoundPaused", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_AUDIO_SOURCE)
		{return lua_fail_arg(L, "IsSoundPaused", 1, "elf_audio_source");}
	arg0 = (elf_audio_source*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_is_sound_paused(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetCollisionActor(lua_State *L)
{
	elf_actor* result;
	elf_collision* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCollisionActor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_COLLISION)
		{return lua_fail_arg(L, "GetCollisionActor", 1, "elf_collision");}
	arg0 = (elf_collision*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_collision_actor(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetCollisionPosition(lua_State *L)
{
	elf_vec3f result;
	elf_collision* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCollisionPosition", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_COLLISION)
		{return lua_fail_arg(L, "GetCollisionPosition", 1, "elf_collision");}
	arg0 = (elf_collision*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_collision_position(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetCollisionNormal(lua_State *L)
{
	elf_vec3f result;
	elf_collision* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCollisionNormal", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_COLLISION)
		{return lua_fail_arg(L, "GetCollisionNormal", 1, "elf_collision");}
	arg0 = (elf_collision*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_collision_normal(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetCollisionDepth(lua_State *L)
{
	float result;
	elf_collision* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCollisionDepth", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_COLLISION)
		{return lua_fail_arg(L, "GetCollisionDepth", 1, "elf_collision");}
	arg0 = (elf_collision*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_collision_depth(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetJointName(lua_State *L)
{
	const char* result;
	elf_joint* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetJointName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_JOINT)
		{return lua_fail_arg(L, "GetJointName", 1, "elf_joint");}
	arg0 = (elf_joint*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_joint_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetJointType(lua_State *L)
{
	int result;
	elf_joint* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetJointType", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_JOINT)
		{return lua_fail_arg(L, "GetJointType", 1, "elf_joint");}
	arg0 = (elf_joint*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_joint_type(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetJointActorA(lua_State *L)
{
	elf_actor* result;
	elf_joint* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetJointActorA", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_JOINT)
		{return lua_fail_arg(L, "GetJointActorA", 1, "elf_joint");}
	arg0 = (elf_joint*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_joint_actor_a(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetJointActorB(lua_State *L)
{
	elf_actor* result;
	elf_joint* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetJointActorB", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_JOINT)
		{return lua_fail_arg(L, "GetJointActorB", 1, "elf_joint");}
	arg0 = (elf_joint*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_joint_actor_b(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetJointPivot(lua_State *L)
{
	elf_vec3f result;
	elf_joint* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetJointPivot", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_JOINT)
		{return lua_fail_arg(L, "GetJointPivot", 1, "elf_joint");}
	arg0 = (elf_joint*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_joint_pivot(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_GetJointAxis(lua_State *L)
{
	elf_vec3f result;
	elf_joint* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetJointAxis", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_JOINT)
		{return lua_fail_arg(L, "GetJointAxis", 1, "elf_joint");}
	arg0 = (elf_joint*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_joint_axis(arg0);
	lua_create_elf_vec3f(L, result);
	return 1;
}
static int lua_CreateFontFromFile(lua_State *L)
{
	elf_font* result;
	const char* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "CreateFontFromFile", lua_gettop(L), 2);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateFontFromFile", 1, "string");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "CreateFontFromFile", 2, "number");}
	arg0 = lua_tostring(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_create_font_from_file(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetFontName(lua_State *L)
{
	const char* result;
	elf_font* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFontName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FONT)
		{return lua_fail_arg(L, "GetFontName", 1, "elf_font");}
	arg0 = (elf_font*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_font_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetFontFilePath(lua_State *L)
{
	const char* result;
	elf_font* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFontFilePath", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FONT)
		{return lua_fail_arg(L, "GetFontFilePath", 1, "elf_font");}
	arg0 = (elf_font*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_font_file_path(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetFontSize(lua_State *L)
{
	int result;
	elf_font* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetFontSize", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FONT)
		{return lua_fail_arg(L, "GetFontSize", 1, "elf_font");}
	arg0 = (elf_font*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_font_size(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetStringWidth(lua_State *L)
{
	int result;
	elf_font* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetStringWidth", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FONT)
		{return lua_fail_arg(L, "GetStringWidth", 1, "elf_font");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetStringWidth", 2, "string");}
	arg0 = (elf_font*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_string_width(arg0, arg1);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetStringHeight(lua_State *L)
{
	int result;
	elf_font* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetStringHeight", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_FONT)
		{return lua_fail_arg(L, "GetStringHeight", 1, "elf_font");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetStringHeight", 2, "string");}
	arg0 = (elf_font*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_string_height(arg0, arg1);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetGuiObjectName(lua_State *L)
{
	const char* result;
	elf_gui_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiObjectName", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectName", 1, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_object_name(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetGuiObjectPosition(lua_State *L)
{
	elf_vec2i result;
	elf_gui_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiObjectPosition", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectPosition", 1, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_object_position(arg0);
	lua_create_elf_vec2i(L, result);
	return 1;
}
static int lua_GetGuiObjectSize(lua_State *L)
{
	elf_vec2i result;
	elf_gui_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiObjectSize", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectSize", 1, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_object_size(arg0);
	lua_create_elf_vec2i(L, result);
	return 1;
}
static int lua_GetGuiObjectColor(lua_State *L)
{
	elf_color result;
	elf_gui_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiObjectColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectColor", 1, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_object_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetGuiObjectVisible(lua_State *L)
{
	unsigned char result;
	elf_gui_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiObjectVisible", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectVisible", 1, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_object_visible(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetGuiObjectScript(lua_State *L)
{
	elf_script* result;
	elf_gui_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiObjectScript", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectScript", 1, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_object_script(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetGuiObjectEvent(lua_State *L)
{
	int result;
	elf_gui_object* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiObjectEvent", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectEvent", 1, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_object_event(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetGuiObjectPosition(lua_State *L)
{
	elf_gui_object* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetGuiObjectPosition", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetGuiObjectPosition", 1, "elf_gui_object");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetGuiObjectPosition", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetGuiObjectPosition", 3, "number");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_gui_object_position(arg0, arg1, arg2);
	return 0;
}
static int lua_SetGuiObjectColor(lua_State *L)
{
	elf_gui_object* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetGuiObjectColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetGuiObjectColor", 1, "elf_gui_object");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetGuiObjectColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetGuiObjectColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetGuiObjectColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetGuiObjectColor", 5, "number");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_gui_object_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetGuiObjectVisible(lua_State *L)
{
	elf_gui_object* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetGuiObjectVisible", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetGuiObjectVisible", 1, "elf_gui_object");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetGuiObjectVisible", 2, "boolean");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_gui_object_visible(arg0, arg1);
	return 0;
}
static int lua_SetGuiObjectScript(lua_State *L)
{
	elf_gui_object* arg0;
	elf_script* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetGuiObjectScript", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "SetGuiObjectScript", 1, "elf_gui_object");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_SCRIPT)
		{return lua_fail_arg(L, "SetGuiObjectScript", 2, "elf_script");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_script*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_gui_object_script(arg0, arg1);
	return 0;
}
static int lua_CreateLabel(lua_State *L)
{
	elf_label* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateLabel", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateLabel", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_label(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetLabelFont(lua_State *L)
{
	elf_font* result;
	elf_label* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLabelFont", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LABEL)
		{return lua_fail_arg(L, "GetLabelFont", 1, "elf_label");}
	arg0 = (elf_label*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_label_font(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetLabelText(lua_State *L)
{
	const char* result;
	elf_label* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetLabelText", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LABEL)
		{return lua_fail_arg(L, "GetLabelText", 1, "elf_label");}
	arg0 = (elf_label*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_label_text(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_SetLabelFont(lua_State *L)
{
	elf_label* arg0;
	elf_font* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetLabelFont", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LABEL)
		{return lua_fail_arg(L, "SetLabelFont", 1, "elf_label");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_FONT)
		{return lua_fail_arg(L, "SetLabelFont", 2, "elf_font");}
	arg0 = (elf_label*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_font*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_label_font(arg0, arg1);
	return 0;
}
static int lua_SetLabelText(lua_State *L)
{
	elf_label* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetLabelText", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_LABEL)
		{return lua_fail_arg(L, "SetLabelText", 1, "elf_label");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetLabelText", 2, "string");}
	arg0 = (elf_label*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_label_text(arg0, arg1);
	return 0;
}
static int lua_CreateButton(lua_State *L)
{
	elf_button* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateButton", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateButton", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_button(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetButtonState(lua_State *L)
{
	unsigned char result;
	elf_button* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetButtonState", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BUTTON)
		{return lua_fail_arg(L, "GetButtonState", 1, "elf_button");}
	arg0 = (elf_button*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_button_state(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetButtonOffTexture(lua_State *L)
{
	elf_texture* result;
	elf_button* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetButtonOffTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BUTTON)
		{return lua_fail_arg(L, "GetButtonOffTexture", 1, "elf_button");}
	arg0 = (elf_button*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_button_off_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetButtonOverTexture(lua_State *L)
{
	elf_texture* result;
	elf_button* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetButtonOverTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BUTTON)
		{return lua_fail_arg(L, "GetButtonOverTexture", 1, "elf_button");}
	arg0 = (elf_button*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_button_over_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetButtonOnTexture(lua_State *L)
{
	elf_texture* result;
	elf_button* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetButtonOnTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BUTTON)
		{return lua_fail_arg(L, "GetButtonOnTexture", 1, "elf_button");}
	arg0 = (elf_button*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_button_on_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetButtonOffTexture(lua_State *L)
{
	elf_button* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetButtonOffTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BUTTON)
		{return lua_fail_arg(L, "SetButtonOffTexture", 1, "elf_button");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetButtonOffTexture", 2, "elf_texture");}
	arg0 = (elf_button*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_button_off_texture(arg0, arg1);
	return 0;
}
static int lua_SetButtonOverTexture(lua_State *L)
{
	elf_button* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetButtonOverTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BUTTON)
		{return lua_fail_arg(L, "SetButtonOverTexture", 1, "elf_button");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetButtonOverTexture", 2, "elf_texture");}
	arg0 = (elf_button*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_button_over_texture(arg0, arg1);
	return 0;
}
static int lua_SetButtonOnTexture(lua_State *L)
{
	elf_button* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetButtonOnTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_BUTTON)
		{return lua_fail_arg(L, "SetButtonOnTexture", 1, "elf_button");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetButtonOnTexture", 2, "elf_texture");}
	arg0 = (elf_button*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_button_on_texture(arg0, arg1);
	return 0;
}
static int lua_CreatePicture(lua_State *L)
{
	elf_picture* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreatePicture", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreatePicture", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_picture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetPictureTexture(lua_State *L)
{
	elf_texture* result;
	elf_picture* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetPictureTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PICTURE)
		{return lua_fail_arg(L, "GetPictureTexture", 1, "elf_picture");}
	arg0 = (elf_picture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_picture_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetPictureScale(lua_State *L)
{
	elf_vec2f result;
	elf_picture* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetPictureScale", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PICTURE)
		{return lua_fail_arg(L, "GetPictureScale", 1, "elf_picture");}
	arg0 = (elf_picture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_picture_scale(arg0);
	lua_create_elf_vec2f(L, result);
	return 1;
}
static int lua_SetPictureTexture(lua_State *L)
{
	elf_picture* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetPictureTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PICTURE)
		{return lua_fail_arg(L, "SetPictureTexture", 1, "elf_picture");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetPictureTexture", 2, "elf_texture");}
	arg0 = (elf_picture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_picture_texture(arg0, arg1);
	return 0;
}
static int lua_SetPictureScale(lua_State *L)
{
	elf_picture* arg0;
	float arg1;
	float arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetPictureScale", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_PICTURE)
		{return lua_fail_arg(L, "SetPictureScale", 1, "elf_picture");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetPictureScale", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetPictureScale", 3, "number");}
	arg0 = (elf_picture*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	elf_set_picture_scale(arg0, arg1, arg2);
	return 0;
}
static int lua_CreateTextField(lua_State *L)
{
	elf_text_field* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateTextField", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateTextField", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_text_field(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetTextFieldTexture(lua_State *L)
{
	elf_texture* result;
	elf_text_field* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextFieldTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "GetTextFieldTexture", 1, "elf_text_field");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_field_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetTextFieldFont(lua_State *L)
{
	elf_font* result;
	elf_text_field* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextFieldFont", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "GetTextFieldFont", 1, "elf_text_field");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_field_font(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetTextFieldTextColor(lua_State *L)
{
	elf_color result;
	elf_text_field* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextFieldTextColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "GetTextFieldTextColor", 1, "elf_text_field");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_field_text_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetTextFieldOffset(lua_State *L)
{
	elf_vec2i result;
	elf_text_field* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextFieldOffset", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "GetTextFieldOffset", 1, "elf_text_field");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_field_offset(arg0);
	lua_create_elf_vec2i(L, result);
	return 1;
}
static int lua_GetTextFieldText(lua_State *L)
{
	const char* result;
	elf_text_field* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextFieldText", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "GetTextFieldText", 1, "elf_text_field");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_field_text(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_SetTextFieldTexture(lua_State *L)
{
	elf_text_field* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetTextFieldTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "SetTextFieldTexture", 1, "elf_text_field");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetTextFieldTexture", 2, "elf_texture");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_text_field_texture(arg0, arg1);
	return 0;
}
static int lua_SetTextFieldFont(lua_State *L)
{
	elf_text_field* arg0;
	elf_font* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetTextFieldFont", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "SetTextFieldFont", 1, "elf_text_field");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_FONT)
		{return lua_fail_arg(L, "SetTextFieldFont", 2, "elf_font");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_font*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_text_field_font(arg0, arg1);
	return 0;
}
static int lua_SetTextFieldTextColor(lua_State *L)
{
	elf_text_field* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetTextFieldTextColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "SetTextFieldTextColor", 1, "elf_text_field");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextFieldTextColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetTextFieldTextColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetTextFieldTextColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetTextFieldTextColor", 5, "number");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_text_field_text_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetTextFieldOffset(lua_State *L)
{
	elf_text_field* arg0;
	int arg1;
	int arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetTextFieldOffset", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "SetTextFieldOffset", 1, "elf_text_field");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextFieldOffset", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetTextFieldOffset", 3, "number");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (int)lua_tonumber(L, 3);
	elf_set_text_field_offset(arg0, arg1, arg2);
	return 0;
}
static int lua_SetTextFieldCursorPosition(lua_State *L)
{
	elf_text_field* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetTextFieldCursorPosition", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "SetTextFieldCursorPosition", 1, "elf_text_field");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextFieldCursorPosition", 2, "number");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_text_field_cursor_position(arg0, arg1);
	return 0;
}
static int lua_SetTextFieldText(lua_State *L)
{
	elf_text_field* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetTextFieldText", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_FIELD)
		{return lua_fail_arg(L, "SetTextFieldText", 1, "elf_text_field");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "SetTextFieldText", 2, "string");}
	arg0 = (elf_text_field*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_set_text_field_text(arg0, arg1);
	return 0;
}
static int lua_CreateSlider(lua_State *L)
{
	elf_slider* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateSlider", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateSlider", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_slider(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSliderBackgroundTexture(lua_State *L)
{
	elf_texture* result;
	elf_slider* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSliderBackgroundTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SLIDER)
		{return lua_fail_arg(L, "GetSliderBackgroundTexture", 1, "elf_slider");}
	arg0 = (elf_slider*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_slider_background_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSliderSliderTexture(lua_State *L)
{
	elf_texture* result;
	elf_slider* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSliderSliderTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SLIDER)
		{return lua_fail_arg(L, "GetSliderSliderTexture", 1, "elf_slider");}
	arg0 = (elf_slider*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_slider_slider_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetSliderValue(lua_State *L)
{
	float result;
	elf_slider* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetSliderValue", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SLIDER)
		{return lua_fail_arg(L, "GetSliderValue", 1, "elf_slider");}
	arg0 = (elf_slider*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_slider_value(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_SetSliderBackgroundTexture(lua_State *L)
{
	elf_slider* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSliderBackgroundTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SLIDER)
		{return lua_fail_arg(L, "SetSliderBackgroundTexture", 1, "elf_slider");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetSliderBackgroundTexture", 2, "elf_texture");}
	arg0 = (elf_slider*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_slider_background_texture(arg0, arg1);
	return 0;
}
static int lua_SetSliderSliderTexture(lua_State *L)
{
	elf_slider* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSliderSliderTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SLIDER)
		{return lua_fail_arg(L, "SetSliderSliderTexture", 1, "elf_slider");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetSliderSliderTexture", 2, "elf_texture");}
	arg0 = (elf_slider*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_slider_slider_texture(arg0, arg1);
	return 0;
}
static int lua_SetSliderValue(lua_State *L)
{
	elf_slider* arg0;
	float arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetSliderValue", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SLIDER)
		{return lua_fail_arg(L, "SetSliderValue", 1, "elf_slider");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetSliderValue", 2, "number");}
	arg0 = (elf_slider*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	elf_set_slider_value(arg0, arg1);
	return 0;
}
static int lua_CreateScreen(lua_State *L)
{
	elf_screen* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateScreen", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateScreen", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_screen(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetScreenTexture(lua_State *L)
{
	elf_texture* result;
	elf_screen* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetScreenTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCREEN)
		{return lua_fail_arg(L, "GetScreenTexture", 1, "elf_screen");}
	arg0 = (elf_screen*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_screen_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetScreenTexture(lua_State *L)
{
	elf_screen* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetScreenTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCREEN)
		{return lua_fail_arg(L, "SetScreenTexture", 1, "elf_screen");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetScreenTexture", 2, "elf_texture");}
	arg0 = (elf_screen*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_screen_texture(arg0, arg1);
	return 0;
}
static int lua_SetScreenToTop(lua_State *L)
{
	elf_screen* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SetScreenToTop", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCREEN)
		{return lua_fail_arg(L, "SetScreenToTop", 1, "elf_screen");}
	arg0 = (elf_screen*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_set_screen_to_top(arg0);
	return 0;
}
static int lua_ForceFocusToScreen(lua_State *L)
{
	elf_screen* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ForceFocusToScreen", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCREEN)
		{return lua_fail_arg(L, "ForceFocusToScreen", 1, "elf_screen");}
	arg0 = (elf_screen*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_force_focus_to_screen(arg0);
	return 0;
}
static int lua_ReleaseFocusFromScreen(lua_State *L)
{
	elf_screen* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "ReleaseFocusFromScreen", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_SCREEN)
		{return lua_fail_arg(L, "ReleaseFocusFromScreen", 1, "elf_screen");}
	arg0 = (elf_screen*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_release_focus_from_screen(arg0);
	return 0;
}
static int lua_CreateTextList(lua_State *L)
{
	elf_text_list* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateTextList", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateTextList", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_text_list(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetTextListFont(lua_State *L)
{
	elf_font* result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListFont", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListFont", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_font(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetTextListSelectionColor(lua_State *L)
{
	elf_color result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListSelectionColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListSelectionColor", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_selection_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetTextListLightColor(lua_State *L)
{
	elf_color result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListLightColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListLightColor", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_light_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetTextListDarkColor(lua_State *L)
{
	elf_color result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListDarkColor", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListDarkColor", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_dark_color(arg0);
	lua_create_elf_color(L, result);
	return 1;
}
static int lua_GetTextListRowCount(lua_State *L)
{
	int result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListRowCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListRowCount", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_row_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetTextListItemCount(lua_State *L)
{
	int result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListItemCount", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListItemCount", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_item_count(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetTextListSelectionIndex(lua_State *L)
{
	int result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListSelectionIndex", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListSelectionIndex", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_selection_index(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetTextListOffset(lua_State *L)
{
	int result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListOffset", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListOffset", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_offset(arg0);
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetTextListItem(lua_State *L)
{
	const char* result;
	elf_text_list* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetTextListItem", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListItem", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetTextListItem", 2, "number");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_text_list_item(arg0, arg1);
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetTextListSelectedItem(lua_State *L)
{
	const char* result;
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetTextListSelectedItem", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "GetTextListSelectedItem", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_text_list_selected_item(arg0);
	lua_pushstring(L, result);
	return 1;
}
static int lua_SetTextListFont(lua_State *L)
{
	elf_text_list* arg0;
	elf_font* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetTextListFont", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "SetTextListFont", 1, "elf_text_list");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_FONT)
		{return lua_fail_arg(L, "SetTextListFont", 2, "elf_font");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_font*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_text_list_font(arg0, arg1);
	return 0;
}
static int lua_SetTextListSelectionColor(lua_State *L)
{
	elf_text_list* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetTextListSelectionColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "SetTextListSelectionColor", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextListSelectionColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetTextListSelectionColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetTextListSelectionColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetTextListSelectionColor", 5, "number");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_text_list_selection_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetTextListLightColor(lua_State *L)
{
	elf_text_list* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetTextListLightColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "SetTextListLightColor", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextListLightColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetTextListLightColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetTextListLightColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetTextListLightColor", 5, "number");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_text_list_light_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetTextListDarkColor(lua_State *L)
{
	elf_text_list* arg0;
	float arg1;
	float arg2;
	float arg3;
	float arg4;
	if(lua_gettop(L) != 5) {return lua_fail_arg_count(L, "SetTextListDarkColor", lua_gettop(L), 5);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "SetTextListDarkColor", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextListDarkColor", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetTextListDarkColor", 3, "number");}
	if(!lua_isnumber(L, 4)) {return lua_fail_arg(L, "SetTextListDarkColor", 4, "number");}
	if(!lua_isnumber(L, 5)) {return lua_fail_arg(L, "SetTextListDarkColor", 5, "number");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (float)lua_tonumber(L, 2);
	arg2 = (float)lua_tonumber(L, 3);
	arg3 = (float)lua_tonumber(L, 4);
	arg4 = (float)lua_tonumber(L, 5);
	elf_set_text_list_dark_color(arg0, arg1, arg2, arg3, arg4);
	return 0;
}
static int lua_SetTextListSize(lua_State *L)
{
	elf_text_list* arg0;
	int arg1;
	int arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetTextListSize", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "SetTextListSize", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextListSize", 2, "number");}
	if(!lua_isnumber(L, 3)) {return lua_fail_arg(L, "SetTextListSize", 3, "number");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = (int)lua_tonumber(L, 3);
	elf_set_text_list_size(arg0, arg1, arg2);
	return 0;
}
static int lua_AddTextListItem(lua_State *L)
{
	elf_text_list* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddTextListItem", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "AddTextListItem", 1, "elf_text_list");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "AddTextListItem", 2, "string");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	elf_add_text_list_item(arg0, arg1);
	return 0;
}
static int lua_SetTextListItem(lua_State *L)
{
	elf_text_list* arg0;
	int arg1;
	const char* arg2;
	if(lua_gettop(L) != 3) {return lua_fail_arg_count(L, "SetTextListItem", lua_gettop(L), 3);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "SetTextListItem", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextListItem", 2, "number");}
	if(!lua_isstring(L, 3)) {return lua_fail_arg(L, "SetTextListItem", 3, "string");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	arg2 = lua_tostring(L, 3);
	elf_set_text_list_item(arg0, arg1, arg2);
	return 0;
}
static int lua_RemoveTextListItem(lua_State *L)
{
	unsigned char result;
	elf_text_list* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveTextListItem", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "RemoveTextListItem", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveTextListItem", 2, "number");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_text_list_item(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveTextListItems(lua_State *L)
{
	elf_text_list* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "RemoveTextListItems", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "RemoveTextListItems", 1, "elf_text_list");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_remove_text_list_items(arg0);
	return 0;
}
static int lua_SetTextListOffset(lua_State *L)
{
	elf_text_list* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetTextListOffset", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "SetTextListOffset", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextListOffset", 2, "number");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_text_list_offset(arg0, arg1);
	return 0;
}
static int lua_SetTextListSelection(lua_State *L)
{
	elf_text_list* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetTextListSelection", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_TEXT_LIST)
		{return lua_fail_arg(L, "SetTextListSelection", 1, "elf_text_list");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "SetTextListSelection", 2, "number");}
	arg0 = (elf_text_list*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	elf_set_text_list_selection(arg0, arg1);
	return 0;
}
static int lua_CreateCheckBox(lua_State *L)
{
	elf_check_box* result;
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "CreateCheckBox", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateCheckBox", 1, "string");}
	arg0 = lua_tostring(L, 1);
	result = elf_create_check_box(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetCheckBoxState(lua_State *L)
{
	unsigned char result;
	elf_check_box* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCheckBoxState", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CHECK_BOX)
		{return lua_fail_arg(L, "GetCheckBoxState", 1, "elf_check_box");}
	arg0 = (elf_check_box*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_check_box_state(arg0);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetCheckBoxOffTexture(lua_State *L)
{
	elf_texture* result;
	elf_check_box* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCheckBoxOffTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CHECK_BOX)
		{return lua_fail_arg(L, "GetCheckBoxOffTexture", 1, "elf_check_box");}
	arg0 = (elf_check_box*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_check_box_off_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetCheckBoxOnTexture(lua_State *L)
{
	elf_texture* result;
	elf_check_box* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetCheckBoxOnTexture", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CHECK_BOX)
		{return lua_fail_arg(L, "GetCheckBoxOnTexture", 1, "elf_check_box");}
	arg0 = (elf_check_box*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_check_box_on_texture(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_SetCheckBoxOffTexture(lua_State *L)
{
	elf_check_box* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetCheckBoxOffTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CHECK_BOX)
		{return lua_fail_arg(L, "SetCheckBoxOffTexture", 1, "elf_check_box");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetCheckBoxOffTexture", 2, "elf_texture");}
	arg0 = (elf_check_box*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_check_box_off_texture(arg0, arg1);
	return 0;
}
static int lua_SetCheckBoxOnTexture(lua_State *L)
{
	elf_check_box* arg0;
	elf_texture* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetCheckBoxOnTexture", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CHECK_BOX)
		{return lua_fail_arg(L, "SetCheckBoxOnTexture", 1, "elf_check_box");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 2))->object) != ELF_TEXTURE)
		{return lua_fail_arg(L, "SetCheckBoxOnTexture", 2, "elf_texture");}
	arg0 = (elf_check_box*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_texture*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	elf_set_check_box_on_texture(arg0, arg1);
	return 0;
}
static int lua_SetCheckBoxState(lua_State *L)
{
	elf_check_box* arg0;
	unsigned char arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "SetCheckBoxState", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_CHECK_BOX)
		{return lua_fail_arg(L, "SetCheckBoxState", 1, "elf_check_box");}
	if(!lua_isboolean(L, 2)) {return lua_fail_arg(L, "SetCheckBoxState", 2, "boolean");}
	arg0 = (elf_check_box*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (unsigned char)lua_toboolean(L, 2);
	elf_set_check_box_state(arg0, arg1);
	return 0;
}
static int lua_CreateGui(lua_State *L)
{
	elf_gui* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "CreateGui", lua_gettop(L), 0);}
	result = elf_create_gui();
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_AddGuiObject(lua_State *L)
{
	unsigned char result;
	elf_gui_object* arg0;
	elf_gui_object* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "AddGuiObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "AddGuiObject", 1, "elf_gui_object");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "AddGuiObject", 2, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_add_gui_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetGuiObjectByName(lua_State *L)
{
	elf_gui_object* result;
	elf_gui_object* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetGuiObjectByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectByName", 1, "elf_gui_object");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "GetGuiObjectByName", 2, "string");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_get_gui_object_by_name(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetGuiObjectByIndex(lua_State *L)
{
	elf_gui_object* result;
	elf_gui_object* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "GetGuiObjectByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "GetGuiObjectByIndex", 1, "elf_gui_object");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "GetGuiObjectByIndex", 2, "number");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_get_gui_object_by_index(arg0, arg1);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_RemoveGuiObjectByName(lua_State *L)
{
	unsigned char result;
	elf_gui_object* arg0;
	const char* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveGuiObjectByName", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveGuiObjectByName", 1, "elf_gui_object");}
	if(!lua_isstring(L, 2)) {return lua_fail_arg(L, "RemoveGuiObjectByName", 2, "string");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = lua_tostring(L, 2);
	result = elf_remove_gui_object_by_name(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveGuiObjectByIndex(lua_State *L)
{
	unsigned char result;
	elf_gui_object* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveGuiObjectByIndex", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveGuiObjectByIndex", 1, "elf_gui_object");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "RemoveGuiObjectByIndex", 2, "number");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_remove_gui_object_by_index(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_RemoveGuiObjectByObject(lua_State *L)
{
	unsigned char result;
	elf_gui_object* arg0;
	elf_gui_object* arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "RemoveGuiObjectByObject", lua_gettop(L), 2);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 1))->object))
		{return lua_fail_arg(L, "RemoveGuiObjectByObject", 1, "elf_gui_object");}
	if(!lua_isuserdata(L, 2) || ((lua_elf_userdata*)lua_touserdata(L,2))->type != LUA_ELF_OBJECT ||
		!elf_is_gui_object(((lua_elf_object*)lua_touserdata(L, 2))->object))
		{return lua_fail_arg(L, "RemoveGuiObjectByObject", 2, "elf_gui_object");}
	arg0 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	arg1 = (elf_gui_object*)((lua_elf_object*)lua_touserdata(L, 2))->object;
	result = elf_remove_gui_object_by_object(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_GetGuiTrace(lua_State *L)
{
	elf_gui_object* result;
	elf_gui* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiTrace", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_GUI)
		{return lua_fail_arg(L, "GetGuiTrace", 1, "elf_gui");}
	arg0 = (elf_gui*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_trace(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetGuiFocus(lua_State *L)
{
	elf_gui_object* result;
	elf_gui* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiFocus", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_GUI)
		{return lua_fail_arg(L, "GetGuiFocus", 1, "elf_gui");}
	arg0 = (elf_gui*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_focus(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_GetGuiActiveTextField(lua_State *L)
{
	elf_gui_object* result;
	elf_gui* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "GetGuiActiveTextField", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_GUI)
		{return lua_fail_arg(L, "GetGuiActiveTextField", 1, "elf_gui");}
	arg0 = (elf_gui*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	result = elf_get_gui_active_text_field(arg0);
	if(result) lua_create_elf_object(L, (elf_object*)result);
	else lua_pushnil(L);
	return 1;
}
static int lua_EmptyGui(lua_State *L)
{
	elf_gui* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "EmptyGui", lua_gettop(L), 1);}
	if(!lua_isuserdata(L, 1) || ((lua_elf_userdata*)lua_touserdata(L,1))->type != LUA_ELF_OBJECT ||
		elf_get_object_type(((lua_elf_object*)lua_touserdata(L, 1))->object) != ELF_GUI)
		{return lua_fail_arg(L, "EmptyGui", 1, "elf_gui");}
	arg0 = (elf_gui*)((lua_elf_object*)lua_touserdata(L, 1))->object;
	elf_empty_gui(arg0);
	return 0;
}
static int lua_CreateSession(lua_State *L)
{
	unsigned char result;
	const char* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "CreateSession", lua_gettop(L), 2);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "CreateSession", 1, "string");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "CreateSession", 2, "number");}
	arg0 = lua_tostring(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_create_session(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_ConnectSession(lua_State *L)
{
	unsigned char result;
	const char* arg0;
	int arg1;
	if(lua_gettop(L) != 2) {return lua_fail_arg_count(L, "ConnectSession", lua_gettop(L), 2);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "ConnectSession", 1, "string");}
	if(!lua_isnumber(L, 2)) {return lua_fail_arg(L, "ConnectSession", 2, "number");}
	arg0 = lua_tostring(L, 1);
	arg1 = (int)lua_tonumber(L, 2);
	result = elf_connect_session(arg0, arg1);
	lua_pushboolean(L, result);
	return 1;
}
static int lua_DisconnectSession(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "DisconnectSession", lua_gettop(L), 0);}
	result = elf_disconnect_session();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_SendStringToClients(lua_State *L)
{
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SendStringToClients", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "SendStringToClients", 1, "string");}
	arg0 = lua_tostring(L, 1);
	elf_send_string_to_clients(arg0);
	return 0;
}
static int lua_SendStringToServer(lua_State *L)
{
	const char* arg0;
	if(lua_gettop(L) != 1) {return lua_fail_arg_count(L, "SendStringToServer", lua_gettop(L), 1);}
	if(!lua_isstring(L, 1)) {return lua_fail_arg(L, "SendStringToServer", 1, "string");}
	arg0 = lua_tostring(L, 1);
	elf_send_string_to_server(arg0);
	return 0;
}
static int lua_GetServerDataAsString(lua_State *L)
{
	const char* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetServerDataAsString", lua_gettop(L), 0);}
	result = elf_get_server_data_as_string();
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetClientDataAsString(lua_State *L)
{
	const char* result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetClientDataAsString", lua_gettop(L), 0);}
	result = elf_get_client_data_as_string();
	lua_pushstring(L, result);
	return 1;
}
static int lua_GetServerEvent(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetServerEvent", lua_gettop(L), 0);}
	result = elf_get_server_event();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetClientEvent(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetClientEvent", lua_gettop(L), 0);}
	result = elf_get_client_event();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_GetCurrentClient(lua_State *L)
{
	int result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "GetCurrentClient", lua_gettop(L), 0);}
	result = elf_get_current_client();
	lua_pushnumber(L, (lua_Number)result);
	return 1;
}
static int lua_IsServer(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsServer", lua_gettop(L), 0);}
	result = elf_is_server();
	lua_pushboolean(L, result);
	return 1;
}
static int lua_IsClient(lua_State *L)
{
	unsigned char result;
	if(lua_gettop(L) != 0) {return lua_fail_arg_count(L, "IsClient", lua_gettop(L), 0);}
	result = elf_is_client();
	lua_pushboolean(L, result);
	return 1;
}
static const struct luaL_reg lua_elf_functions[] = {
	{"GetObjectType", lua_GetObjectType},
	{"GetObjectRefCount", lua_GetObjectRefCount},
	{"GetGlobalRefCount", lua_GetGlobalRefCount},
	{"GetGlobalObjCount", lua_GetGlobalObjCount},
	{"IsActor", lua_IsActor},
	{"IsGuiObject", lua_IsGuiObject},
	{"CreateList", lua_CreateList},
	{"GetListLength", lua_GetListLength},
	{"InsertToList", lua_InsertToList},
	{"AppendToList", lua_AppendToList},
	{"RemoveFromList", lua_RemoveFromList},
	{"GetItemFromList", lua_GetItemFromList},
	{"BeginList", lua_BeginList},
	{"NextInList", lua_NextInList},
	{"RbeginList", lua_RbeginList},
	{"RnextInList", lua_RnextInList},
	{"SeekList", lua_SeekList},
	{"RseekList", lua_RseekList},
	{"ReadConfig", lua_ReadConfig},
	{"GetConfigWindowWidth", lua_GetConfigWindowWidth},
	{"GetConfigWindowHeight", lua_GetConfigWindowHeight},
	{"GetConfigMultisamples", lua_GetConfigMultisamples},
	{"GetConfigFullscreen", lua_GetConfigFullscreen},
	{"GetConfigTextureCompress", lua_GetConfigTextureCompress},
	{"GetConfigTextureAnisotropy", lua_GetConfigTextureAnisotropy},
	{"GetConfigShadowMapSize", lua_GetConfigShadowMapSize},
	{"GetConfigStart", lua_GetConfigStart},
	{"GetConfigLog", lua_GetConfigLog},
	{"SetTitle", lua_SetTitle},
	{"GetWindowWidth", lua_GetWindowWidth},
	{"GetWindowHeight", lua_GetWindowHeight},
	{"GetVideoModeCount", lua_GetVideoModeCount},
	{"GetVideoMode", lua_GetVideoMode},
	{"GetMultisamples", lua_GetMultisamples},
	{"IsFullscreen", lua_IsFullscreen},
	{"GetTitle", lua_GetTitle},
	{"GetTime", lua_GetTime},
	{"Sleep", lua_Sleep},
	{"IsWindowOpened", lua_IsWindowOpened},
	{"GetMousePosition", lua_GetMousePosition},
	{"GetMouseForce", lua_GetMouseForce},
	{"SetMousePosition", lua_SetMousePosition},
	{"HideMouse", lua_HideMouse},
	{"IsMouseHidden", lua_IsMouseHidden},
	{"GetMouseWheel", lua_GetMouseWheel},
	{"GetMouseButtonState", lua_GetMouseButtonState},
	{"GetKeyState", lua_GetKeyState},
	{"GetJoystickPresent", lua_GetJoystickPresent},
	{"GetJoystickAxis", lua_GetJoystickAxis},
	{"GetJoystickButtonState", lua_GetJoystickButtonState},
	{"GetEventCount", lua_GetEventCount},
	{"GetEvent", lua_GetEvent},
	{"Init", lua_Init},
	{"InitWithConfig", lua_InitWithConfig},
	{"Deinit", lua_Deinit},
	{"ResizeWindow", lua_ResizeWindow},
	{"GetPlatform", lua_GetPlatform},
	{"GetVersionMajor", lua_GetVersionMajor},
	{"GetVersionMinor", lua_GetVersionMinor},
	{"GetVersionRelease", lua_GetVersionRelease},
	{"GetVersion", lua_GetVersion},
	{"GetCurrentDirectory", lua_GetCurrentDirectory},
	{"GetErrorString", lua_GetErrorString},
	{"GetError", lua_GetError},
	{"Run", lua_Run},
	{"Quit", lua_Quit},
	{"SetF10Exit", lua_SetF10Exit},
	{"GetF10Exit", lua_GetF10Exit},
	{"LoadScene", lua_LoadScene},
	{"SetScene", lua_SetScene},
	{"GetScene", lua_GetScene},
	{"SetGui", lua_SetGui},
	{"GetGui", lua_GetGui},
	{"GetSync", lua_GetSync},
	{"GetFps", lua_GetFps},
	{"SaveScreenShot", lua_SaveScreenShot},
	{"SetFpsLimit", lua_SetFpsLimit},
	{"GetFpsLimit", lua_GetFpsLimit},
	{"SetTickRate", lua_SetTickRate},
	{"GetTickRate", lua_GetTickRate},
	{"SetSpeed", lua_SetSpeed},
	{"GetSpeed", lua_GetSpeed},
	{"SetTextureCompress", lua_SetTextureCompress},
	{"GetTextureCompress", lua_GetTextureCompress},
	{"SetTextureAnisotropy", lua_SetTextureAnisotropy},
	{"GetTextureAnisotropy", lua_GetTextureAnisotropy},
	{"SetShadowMapSize", lua_SetShadowMapSize},
	{"GetShadowMapSize", lua_GetShadowMapSize},
	{"GetPolygonsRendered", lua_GetPolygonsRendered},
	{"SetFog", lua_SetFog},
	{"DisableFog", lua_DisableFog},
	{"GetFogStart", lua_GetFogStart},
	{"GetFogEnd", lua_GetFogEnd},
	{"GetFogColor", lua_GetFogColor},
	{"SetBloom", lua_SetBloom},
	{"DisableBloom", lua_DisableBloom},
	{"GetBloomThreshold", lua_GetBloomThreshold},
	{"SetDof", lua_SetDof},
	{"DisableDof", lua_DisableDof},
	{"GetDofFocalRange", lua_GetDofFocalRange},
	{"GetDofFocalDistance", lua_GetDofFocalDistance},
	{"SetSsao", lua_SetSsao},
	{"DisableSsao", lua_DisableSsao},
	{"GetSsaoAmount", lua_GetSsaoAmount},
	{"SetLightShafts", lua_SetLightShafts},
	{"DisableLightShafts", lua_DisableLightShafts},
	{"GetLightShaftsIntensity", lua_GetLightShaftsIntensity},
	{"IsFog", lua_IsFog},
	{"IsBloom", lua_IsBloom},
	{"IsSsao", lua_IsSsao},
	{"IsDof", lua_IsDof},
	{"IsLightShafts", lua_IsLightShafts},
	{"SetOcclusionCulling", lua_SetOcclusionCulling},
	{"IsOcclusionCulling", lua_IsOcclusionCulling},
	{"SetDebugDraw", lua_SetDebugDraw},
	{"IsDebugDraw", lua_IsDebugDraw},
	{"GetActor", lua_GetActor},
	{"ReadDirectory", lua_ReadDirectory},
	{"GetDirectoryPath", lua_GetDirectoryPath},
	{"GetDirectoryItemCount", lua_GetDirectoryItemCount},
	{"GetDirectoryItem", lua_GetDirectoryItem},
	{"GetDirectoryItemName", lua_GetDirectoryItemName},
	{"GetDirectoryItemType", lua_GetDirectoryItemType},
	{"CreateVec3f", lua_CreateVec3f},
	{"CreateVec3fFromValues", lua_CreateVec3fFromValues},
	{"CreateQua", lua_CreateQua},
	{"CreateQuaFromEuler", lua_CreateQuaFromEuler},
	{"CreateQuaFromAngleAxis", lua_CreateQuaFromAngleAxis},
	{"MulQuaVec3f", lua_MulQuaVec3f},
	{"MulQuaQua", lua_MulQuaQua},
	{"GetQuaInverted", lua_GetQuaInverted},
	{"RotateVec3f", lua_RotateVec3f},
	{"SubVec3fVec3f", lua_SubVec3fVec3f},
	{"AddVec3fVec3f", lua_AddVec3fVec3f},
	{"GetVec3fLength", lua_GetVec3fLength},
	{"AboutZero", lua_AboutZero},
	{"FloatAbs", lua_FloatAbs},
	{"FloatMin", lua_FloatMin},
	{"FloatMax", lua_FloatMax},
	{"RandomFloat", lua_RandomFloat},
	{"RandomFloatRange", lua_RandomFloatRange},
	{"RandomInt", lua_RandomInt},
	{"RandomIntRange", lua_RandomIntRange},
	{"CreateFramePlayer", lua_CreateFramePlayer},
	{"UpdateFramePlayer", lua_UpdateFramePlayer},
	{"SetFramePlayerFrame", lua_SetFramePlayerFrame},
	{"PlayFramePlayer", lua_PlayFramePlayer},
	{"LoopFramePlayer", lua_LoopFramePlayer},
	{"StopFramePlayer", lua_StopFramePlayer},
	{"PauseFramePlayer", lua_PauseFramePlayer},
	{"ResumeFramePlayer", lua_ResumeFramePlayer},
	{"GetFramePlayerStart", lua_GetFramePlayerStart},
	{"GetFramePlayerEnd", lua_GetFramePlayerEnd},
	{"GetFramePlayerSpeed", lua_GetFramePlayerSpeed},
	{"GetFramePlayerFrame", lua_GetFramePlayerFrame},
	{"IsFramePlayerPlaying", lua_IsFramePlayerPlaying},
	{"IsFramePlayerPaused", lua_IsFramePlayerPaused},
	{"CreateTimer", lua_CreateTimer},
	{"StartTimer", lua_StartTimer},
	{"GetElapsedTime", lua_GetElapsedTime},
	{"CreateEmptyImage", lua_CreateEmptyImage},
	{"CreateImageFromFile", lua_CreateImageFromFile},
	{"SetImagePixel", lua_SetImagePixel},
	{"GetImageWidth", lua_GetImageWidth},
	{"GetImageHeight", lua_GetImageHeight},
	{"GetImageBitsPerPixel", lua_GetImageBitsPerPixel},
	{"GetImagePixel", lua_GetImagePixel},
	{"CreateTextureFromFile", lua_CreateTextureFromFile},
	{"CreateTextureFromImage", lua_CreateTextureFromImage},
	{"CreateCubeMapFromFiles", lua_CreateCubeMapFromFiles},
	{"SetTextureName", lua_SetTextureName},
	{"GetTextureName", lua_GetTextureName},
	{"GetTextureFilePath", lua_GetTextureFilePath},
	{"GetTextureWidth", lua_GetTextureWidth},
	{"GetTextureHeight", lua_GetTextureHeight},
	{"GetTextureFormat", lua_GetTextureFormat},
	{"GetTextureDataFormat", lua_GetTextureDataFormat},
	{"CreateMaterial", lua_CreateMaterial},
	{"SetMaterialDiffuseColor", lua_SetMaterialDiffuseColor},
	{"SetMaterialSpecularColor", lua_SetMaterialSpecularColor},
	{"SetMaterialAmbientColor", lua_SetMaterialAmbientColor},
	{"SetMaterialSpecularPower", lua_SetMaterialSpecularPower},
	{"SetMaterialLighting", lua_SetMaterialLighting},
	{"SetMaterialName", lua_SetMaterialName},
	{"GetMaterialName", lua_GetMaterialName},
	{"GetMaterialFilePath", lua_GetMaterialFilePath},
	{"GetMaterialDiffuseColor", lua_GetMaterialDiffuseColor},
	{"GetMaterialSpecularColor", lua_GetMaterialSpecularColor},
	{"GetMaterialAmbientColor", lua_GetMaterialAmbientColor},
	{"GetMaterialSpecularPower", lua_GetMaterialSpecularPower},
	{"GetMaterialLighting", lua_GetMaterialLighting},
	{"SetMaterialDiffuseMap", lua_SetMaterialDiffuseMap},
	{"SetMaterialNormalMap", lua_SetMaterialNormalMap},
	{"SetMaterialHeightMap", lua_SetMaterialHeightMap},
	{"SetMaterialSpecularMap", lua_SetMaterialSpecularMap},
	{"SetMaterialLightMap", lua_SetMaterialLightMap},
	{"SetMaterialCubeMap", lua_SetMaterialCubeMap},
	{"ClearMaterialDiffuseMap", lua_ClearMaterialDiffuseMap},
	{"ClearMaterialNormalMap", lua_ClearMaterialNormalMap},
	{"ClearMaterialHeightMap", lua_ClearMaterialHeightMap},
	{"ClearMaterialSpecularMap", lua_ClearMaterialSpecularMap},
	{"ClearMaterialLightMap", lua_ClearMaterialLightMap},
	{"ClearMaterialCubeMap", lua_ClearMaterialCubeMap},
	{"GetMaterialDiffuseMap", lua_GetMaterialDiffuseMap},
	{"GetMaterialNormalMap", lua_GetMaterialNormalMap},
	{"GetMaterialHeightMap", lua_GetMaterialHeightMap},
	{"GetMaterialSpecularMap", lua_GetMaterialSpecularMap},
	{"GetMaterialLightMap", lua_GetMaterialLightMap},
	{"GetMaterialCubeMap", lua_GetMaterialCubeMap},
	{"SetMaterialParallaxScale", lua_SetMaterialParallaxScale},
	{"SetMaterialAlphaTest", lua_SetMaterialAlphaTest},
	{"SetMaterialAlphaThreshold", lua_SetMaterialAlphaThreshold},
	{"GetMaterialParallaxScale", lua_GetMaterialParallaxScale},
	{"GetMaterialAlphaTest", lua_GetMaterialAlphaTest},
	{"GetMaterialAlphaThreshold", lua_GetMaterialAlphaThreshold},
	{"CreateBezierPoint", lua_CreateBezierPoint},
	{"SetBezierPointPosition", lua_SetBezierPointPosition},
	{"SetBezierPointControl1", lua_SetBezierPointControl1},
	{"SetBezierPointControl2", lua_SetBezierPointControl2},
	{"GetBezierPointPosition", lua_GetBezierPointPosition},
	{"GetBezierPointControl1", lua_GetBezierPointControl1},
	{"GetBezierPointControl2", lua_GetBezierPointControl2},
	{"CreateBezierCurve", lua_CreateBezierCurve},
	{"SetBezierCurveType", lua_SetBezierCurveType},
	{"GetBezierCurveType", lua_GetBezierCurveType},
	{"AddPointToBezierCurve", lua_AddPointToBezierCurve},
	{"GetPointFromBezierCurve", lua_GetPointFromBezierCurve},
	{"GetBezierCurveValue", lua_GetBezierCurveValue},
	{"CreateIpo", lua_CreateIpo},
	{"AddCurveToIpo", lua_AddCurveToIpo},
	{"GetIpoCurveCount", lua_GetIpoCurveCount},
	{"GetCurveFromIpo", lua_GetCurveFromIpo},
	{"GetIpoLoc", lua_GetIpoLoc},
	{"GetIpoRot", lua_GetIpoRot},
	{"GetIpoScale", lua_GetIpoScale},
	{"GetIpoQua", lua_GetIpoQua},
	{"CreateProperty", lua_CreateProperty},
	{"GetPropertyType", lua_GetPropertyType},
	{"GetPropertyInt", lua_GetPropertyInt},
	{"GetPropertyFloat", lua_GetPropertyFloat},
	{"GetPropertyString", lua_GetPropertyString},
	{"GetPropertyBool", lua_GetPropertyBool},
	{"SetPropertyInt", lua_SetPropertyInt},
	{"SetPropertyFloat", lua_SetPropertyFloat},
	{"SetPropertyString", lua_SetPropertyString},
	{"SetPropertyBool", lua_SetPropertyBool},
	{"GetActorName", lua_GetActorName},
	{"GetActorFilePath", lua_GetActorFilePath},
	{"GetActorScript", lua_GetActorScript},
	{"SetActorName", lua_SetActorName},
	{"SetActorScript", lua_SetActorScript},
	{"ClearActorScript", lua_ClearActorScript},
	{"SetActorPosition", lua_SetActorPosition},
	{"SetActorRotation", lua_SetActorRotation},
	{"SetActorOrientation", lua_SetActorOrientation},
	{"RotateActor", lua_RotateActor},
	{"RotateActorLocal", lua_RotateActorLocal},
	{"MoveActor", lua_MoveActor},
	{"MoveActorLocal", lua_MoveActorLocal},
	{"SetActorPositionRelativeTo", lua_SetActorPositionRelativeTo},
	{"SetActorRotationRelativeTo", lua_SetActorRotationRelativeTo},
	{"SetActorOrientationRelativeTo", lua_SetActorOrientationRelativeTo},
	{"GetActorPosition", lua_GetActorPosition},
	{"GetActorRotation", lua_GetActorRotation},
	{"GetActorOrientation", lua_GetActorOrientation},
	{"SetActorBoundingLengths", lua_SetActorBoundingLengths},
	{"SetActorBoundingOffset", lua_SetActorBoundingOffset},
	{"SetActorPhysics", lua_SetActorPhysics},
	{"IsActorPhysics", lua_IsActorPhysics},
	{"DisableActorPhysics", lua_DisableActorPhysics},
	{"SetActorDamping", lua_SetActorDamping},
	{"SetActorSleepThresholds", lua_SetActorSleepThresholds},
	{"SetActorRestitution", lua_SetActorRestitution},
	{"SetActorAnisotropicFriction", lua_SetActorAnisotropicFriction},
	{"SetActorLinearFactor", lua_SetActorLinearFactor},
	{"SetActorAngularFactor", lua_SetActorAngularFactor},
	{"AddForceToActor", lua_AddForceToActor},
	{"AddForceToActorLocal", lua_AddForceToActorLocal},
	{"AddTorqueToActor", lua_AddTorqueToActor},
	{"SetActorLinearVelocity", lua_SetActorLinearVelocity},
	{"SetActorLinearVelocityLocal", lua_SetActorLinearVelocityLocal},
	{"SetActorAngularVelocity", lua_SetActorAngularVelocity},
	{"GetActorBoundingLengths", lua_GetActorBoundingLengths},
	{"GetActorBoundingOffset", lua_GetActorBoundingOffset},
	{"GetActorShape", lua_GetActorShape},
	{"GetActorMass", lua_GetActorMass},
	{"GetActorLinearDamping", lua_GetActorLinearDamping},
	{"GetActorAngularDamping", lua_GetActorAngularDamping},
	{"GetActorLinearSleepThreshold", lua_GetActorLinearSleepThreshold},
	{"GetActorAngularSleepThreshold", lua_GetActorAngularSleepThreshold},
	{"GetActorRestitution", lua_GetActorRestitution},
	{"GetActorAnisotropicFriction", lua_GetActorAnisotropicFriction},
	{"GetActorLinearFactor", lua_GetActorLinearFactor},
	{"GetActorAngularFactor", lua_GetActorAngularFactor},
	{"GetActorLinearVelocity", lua_GetActorLinearVelocity},
	{"GetActorAngularVelocity", lua_GetActorAngularVelocity},
	{"AddHingeJointToActor", lua_AddHingeJointToActor},
	{"AddBallJointToActor", lua_AddBallJointToActor},
	{"AddConeTwistJointToActor", lua_AddConeTwistJointToActor},
	{"GetActorJointByName", lua_GetActorJointByName},
	{"GetActorJointByIndex", lua_GetActorJointByIndex},
	{"RemoveActorJointByName", lua_RemoveActorJointByName},
	{"RemoveActorJointByIndex", lua_RemoveActorJointByIndex},
	{"RemoveActorJointByObject", lua_RemoveActorJointByObject},
	{"SetActorIpo", lua_SetActorIpo},
	{"GetActorIpo", lua_GetActorIpo},
	{"SetActorIpoFrame", lua_SetActorIpoFrame},
	{"PlayActorIpo", lua_PlayActorIpo},
	{"LoopActorIpo", lua_LoopActorIpo},
	{"StopActorIpo", lua_StopActorIpo},
	{"PauseActorIpo", lua_PauseActorIpo},
	{"ResumeActorIpo", lua_ResumeActorIpo},
	{"GetActorIpoStart", lua_GetActorIpoStart},
	{"GetActorIpoEnd", lua_GetActorIpoEnd},
	{"GetActorIpoSpeed", lua_GetActorIpoSpeed},
	{"GetActorIpoFrame", lua_GetActorIpoFrame},
	{"IsActorIpoPlaying", lua_IsActorIpoPlaying},
	{"IsActorIpoPaused", lua_IsActorIpoPaused},
	{"GetActorCollisionCount", lua_GetActorCollisionCount},
	{"GetActorCollision", lua_GetActorCollision},
	{"GetActorPropertyCount", lua_GetActorPropertyCount},
	{"AddPropertyToActor", lua_AddPropertyToActor},
	{"GetActorPropertyByName", lua_GetActorPropertyByName},
	{"GetActorPropertyByIndex", lua_GetActorPropertyByIndex},
	{"RemoveActorPropertyByName", lua_RemoveActorPropertyByName},
	{"RemoveActorPropertyByIndex", lua_RemoveActorPropertyByIndex},
	{"RemoveActorPropertyByObject", lua_RemoveActorPropertyByObject},
	{"RemoveActorProperties", lua_RemoveActorProperties},
	{"SetActorSelected", lua_SetActorSelected},
	{"GetActorSelected", lua_GetActorSelected},
	{"CreateCamera", lua_CreateCamera},
	{"SetCameraViewport", lua_SetCameraViewport},
	{"SetCameraPerspective", lua_SetCameraPerspective},
	{"SetCameraOrthographic", lua_SetCameraOrthographic},
	{"GetCameraViewportSize", lua_GetCameraViewportSize},
	{"GetCameraViewportOffset", lua_GetCameraViewportOffset},
	{"GetCameraFov", lua_GetCameraFov},
	{"GetCameraAspect", lua_GetCameraAspect},
	{"GetCameraClip", lua_GetCameraClip},
	{"GetCameraFarPlaneSize", lua_GetCameraFarPlaneSize},
	{"ProjectCameraPoint", lua_ProjectCameraPoint},
	{"UnProjectCameraPoint", lua_UnProjectCameraPoint},
	{"CreateVertice", lua_CreateVertice},
	{"SetVerticePosition", lua_SetVerticePosition},
	{"SetVerticeNormal", lua_SetVerticeNormal},
	{"SetVerticeTexCoord", lua_SetVerticeTexCoord},
	{"GetVerticePosition", lua_GetVerticePosition},
	{"GetVerticeNormal", lua_GetVerticeNormal},
	{"GetVerticeTexCoord", lua_GetVerticeTexCoord},
	{"GetFaceV1", lua_GetFaceV1},
	{"GetFaceV2", lua_GetFaceV2},
	{"GetFaceV3", lua_GetFaceV3},
	{"CreateMeshData", lua_CreateMeshData},
	{"GetMeshDataVerticeCount", lua_GetMeshDataVerticeCount},
	{"GetMeshDataFaceCount", lua_GetMeshDataFaceCount},
	{"AddVerticeToMeshData", lua_AddVerticeToMeshData},
	{"AddFaceToMeshData", lua_AddFaceToMeshData},
	{"GetVerticeFromMeshData", lua_GetVerticeFromMeshData},
	{"GetFaceFromMeshData", lua_GetFaceFromMeshData},
	{"CreateModelFromMeshData", lua_CreateModelFromMeshData},
	{"SetModelName", lua_SetModelName},
	{"GetModelName", lua_GetModelName},
	{"GetModelFilePath", lua_GetModelFilePath},
	{"GetModelVerticeCount", lua_GetModelVerticeCount},
	{"GetModelIndiceCount", lua_GetModelIndiceCount},
	{"GetModelBoundingBoxMin", lua_GetModelBoundingBoxMin},
	{"GetModelBoundingBoxMax", lua_GetModelBoundingBoxMax},
	{"CreateEntity", lua_CreateEntity},
	{"GenerateEntityTangents", lua_GenerateEntityTangents},
	{"SetEntityScale", lua_SetEntityScale},
	{"GetEntityScale", lua_GetEntityScale},
	{"SetEntityModel", lua_SetEntityModel},
	{"ClearEntityModel", lua_ClearEntityModel},
	{"GetEntityModel", lua_GetEntityModel},
	{"GetEntityMaterialCount", lua_GetEntityMaterialCount},
	{"AddEntityMaterial", lua_AddEntityMaterial},
	{"SetEntityMaterial", lua_SetEntityMaterial},
	{"RemoveEntityMaterial", lua_RemoveEntityMaterial},
	{"GetEntityMaterial", lua_GetEntityMaterial},
	{"SetEntityVisible", lua_SetEntityVisible},
	{"GetEntityVisible", lua_GetEntityVisible},
	{"SetEntityOccluder", lua_SetEntityOccluder},
	{"GetEntityOccluder", lua_GetEntityOccluder},
	{"SetEntityPhysics", lua_SetEntityPhysics},
	{"DisableEntityPhysics", lua_DisableEntityPhysics},
	{"SetEntityArmature", lua_SetEntityArmature},
	{"SetEntityArmatureFrame", lua_SetEntityArmatureFrame},
	{"PlayEntityArmature", lua_PlayEntityArmature},
	{"LoopEntityArmature", lua_LoopEntityArmature},
	{"StopEntityArmature", lua_StopEntityArmature},
	{"PauseEntityArmature", lua_PauseEntityArmature},
	{"ResumeEntityArmature", lua_ResumeEntityArmature},
	{"GetEntityArmatureStart", lua_GetEntityArmatureStart},
	{"GetEntityArmatureEnd", lua_GetEntityArmatureEnd},
	{"GetEntityArmatureSpeed", lua_GetEntityArmatureSpeed},
	{"GetEntityArmatureFrame", lua_GetEntityArmatureFrame},
	{"IsEntityArmaturePlaying", lua_IsEntityArmaturePlaying},
	{"IsEntityArmaturePaused", lua_IsEntityArmaturePaused},
	{"GetEntityArmature", lua_GetEntityArmature},
	{"GetEntityChanged", lua_GetEntityChanged},
	{"CreateLight", lua_CreateLight},
	{"GetLightType", lua_GetLightType},
	{"GetLightColor", lua_GetLightColor},
	{"GetLightDistance", lua_GetLightDistance},
	{"GetLightFadeSpeed", lua_GetLightFadeSpeed},
	{"GetLightShadows", lua_GetLightShadows},
	{"GetLightVisible", lua_GetLightVisible},
	{"GetLightCone", lua_GetLightCone},
	{"IsLightShaft", lua_IsLightShaft},
	{"GetLightShaftSize", lua_GetLightShaftSize},
	{"GetLightShaftIntensity", lua_GetLightShaftIntensity},
	{"GetLightShaftFadeOff", lua_GetLightShaftFadeOff},
	{"SetLightType", lua_SetLightType},
	{"SetLightColor", lua_SetLightColor},
	{"SetLightDistance", lua_SetLightDistance},
	{"SetLightFadeSpeed", lua_SetLightFadeSpeed},
	{"SetLightShadows", lua_SetLightShadows},
	{"SetLightVisible", lua_SetLightVisible},
	{"SetLightCone", lua_SetLightCone},
	{"SetLightShaft", lua_SetLightShaft},
	{"DisableLightShaft", lua_DisableLightShaft},
	{"GetBoneArmature", lua_GetBoneArmature},
	{"GetBoneParent", lua_GetBoneParent},
	{"GetBoneChildByName", lua_GetBoneChildByName},
	{"GetBoneChildById", lua_GetBoneChildById},
	{"GetBoneChildByIndex", lua_GetBoneChildByIndex},
	{"GetBonePosition", lua_GetBonePosition},
	{"GetBoneRotation", lua_GetBoneRotation},
	{"GetBoneOrientation", lua_GetBoneOrientation},
	{"CreateArmature", lua_CreateArmature},
	{"GetBoneFromArmatureByName", lua_GetBoneFromArmatureByName},
	{"GetBoneFromArmatureById", lua_GetBoneFromArmatureById},
	{"CreateParticles", lua_CreateParticles},
	{"GetParticlesName", lua_GetParticlesName},
	{"GetParticlesFilePath", lua_GetParticlesFilePath},
	{"SetParticlesMaxCount", lua_SetParticlesMaxCount},
	{"SetParticlesDrawMode", lua_SetParticlesDrawMode},
	{"SetParticlesTexture", lua_SetParticlesTexture},
	{"ClearParticlesTexture", lua_ClearParticlesTexture},
	{"SetParticlesModel", lua_SetParticlesModel},
	{"ClearParticlesModel", lua_ClearParticlesModel},
	{"SetParticlesEntity", lua_SetParticlesEntity},
	{"ClearParticlesEntity", lua_ClearParticlesEntity},
	{"SetParticlesGravity", lua_SetParticlesGravity},
	{"SetParticlesSpawnDelay", lua_SetParticlesSpawnDelay},
	{"SetParticlesSpawn", lua_SetParticlesSpawn},
	{"SetParticlesSize", lua_SetParticlesSize},
	{"SetParticlesSizeGrowth", lua_SetParticlesSizeGrowth},
	{"SetParticlesRotation", lua_SetParticlesRotation},
	{"SetParticlesRotationGrowth", lua_SetParticlesRotationGrowth},
	{"SetParticlesLifeSpan", lua_SetParticlesLifeSpan},
	{"SetParticlesFadeSpeed", lua_SetParticlesFadeSpeed},
	{"SetParticlesPositionMin", lua_SetParticlesPositionMin},
	{"SetParticlesPositionMax", lua_SetParticlesPositionMax},
	{"SetParticlesVelocityMin", lua_SetParticlesVelocityMin},
	{"SetParticlesVelocityMax", lua_SetParticlesVelocityMax},
	{"SetParticlesColorMin", lua_SetParticlesColorMin},
	{"SetParticlesColorMax", lua_SetParticlesColorMax},
	{"GetParticlesMaxCount", lua_GetParticlesMaxCount},
	{"GetParticlesCount", lua_GetParticlesCount},
	{"GetParticlesDrawMode", lua_GetParticlesDrawMode},
	{"GetParticlesTexture", lua_GetParticlesTexture},
	{"GetParticlesModel", lua_GetParticlesModel},
	{"GetParticlesEntity", lua_GetParticlesEntity},
	{"GetParticlesGravity", lua_GetParticlesGravity},
	{"GetParticlesSpawnDelay", lua_GetParticlesSpawnDelay},
	{"GetParticlesSpawn", lua_GetParticlesSpawn},
	{"GetParticlesSizeMin", lua_GetParticlesSizeMin},
	{"GetParticlesSizeMax", lua_GetParticlesSizeMax},
	{"GetParticlesSizeGrowthMin", lua_GetParticlesSizeGrowthMin},
	{"GetParticlesSizeGrowthMax", lua_GetParticlesSizeGrowthMax},
	{"GetParticlesRotationMin", lua_GetParticlesRotationMin},
	{"GetParticlesRotationMax", lua_GetParticlesRotationMax},
	{"GetParticlesRotationGrowthMin", lua_GetParticlesRotationGrowthMin},
	{"GetParticlesRotationGrowthMax", lua_GetParticlesRotationGrowthMax},
	{"GetParticlesLifeSpanMin", lua_GetParticlesLifeSpanMin},
	{"GetParticlesLifeSpanMax", lua_GetParticlesLifeSpanMax},
	{"GetParticlesFadeSpeedMin", lua_GetParticlesFadeSpeedMin},
	{"GetParticlesFadeSpeedMax", lua_GetParticlesFadeSpeedMax},
	{"GetParticlesPositionMin", lua_GetParticlesPositionMin},
	{"GetParticlesPositionMax", lua_GetParticlesPositionMax},
	{"GetParticlesVelocityMin", lua_GetParticlesVelocityMin},
	{"GetParticlesVelocityMax", lua_GetParticlesVelocityMax},
	{"GetParticlesColorMin", lua_GetParticlesColorMin},
	{"GetParticlesColorMax", lua_GetParticlesColorMax},
	{"CreateSprite", lua_CreateSprite},
	{"SetSpriteMaterial", lua_SetSpriteMaterial},
	{"SetSpriteScale", lua_SetSpriteScale},
	{"SetSpriteFaceCamera", lua_SetSpriteFaceCamera},
	{"GetSpriteMaterial", lua_GetSpriteMaterial},
	{"GetSpriteScale", lua_GetSpriteScale},
	{"GetSpriteFaceCamera", lua_GetSpriteFaceCamera},
	{"SetSpriteVisible", lua_SetSpriteVisible},
	{"GetSpriteVisible", lua_GetSpriteVisible},
	{"SetSpriteOccluder", lua_SetSpriteOccluder},
	{"GetSpriteOccluder", lua_GetSpriteOccluder},
	{"CreateScene", lua_CreateScene},
	{"CreateSceneFromFile", lua_CreateSceneFromFile},
	{"SaveScene", lua_SaveScene},
	{"SetSceneAmbientColor", lua_SetSceneAmbientColor},
	{"GetSceneAmbientColor", lua_GetSceneAmbientColor},
	{"SetSceneGravity", lua_SetSceneGravity},
	{"GetSceneGravity", lua_GetSceneGravity},
	{"SetScenePhysics", lua_SetScenePhysics},
	{"GetScenePhysics", lua_GetScenePhysics},
	{"SetSceneRunScripts", lua_SetSceneRunScripts},
	{"GetSceneRunScripts", lua_GetSceneRunScripts},
	{"GetSceneName", lua_GetSceneName},
	{"GetSceneFilePath", lua_GetSceneFilePath},
	{"GetSceneCameraCount", lua_GetSceneCameraCount},
	{"GetSceneEntityCount", lua_GetSceneEntityCount},
	{"GetSceneLightCount", lua_GetSceneLightCount},
	{"GetSceneArmatureCount", lua_GetSceneArmatureCount},
	{"GetSceneParticlesCount", lua_GetSceneParticlesCount},
	{"GetSceneSpriteCount", lua_GetSceneSpriteCount},
	{"AddCameraToScene", lua_AddCameraToScene},
	{"AddEntityToScene", lua_AddEntityToScene},
	{"AddLightToScene", lua_AddLightToScene},
	{"AddParticlesToScene", lua_AddParticlesToScene},
	{"AddSpriteToScene", lua_AddSpriteToScene},
	{"SetSceneActiveCamera", lua_SetSceneActiveCamera},
	{"GetSceneActiveCamera", lua_GetSceneActiveCamera},
	{"GetSceneRayCastResult", lua_GetSceneRayCastResult},
	{"GetSceneRayCastResults", lua_GetSceneRayCastResults},
	{"GetDebugSceneRayCastResult", lua_GetDebugSceneRayCastResult},
	{"GetDebugSceneRayCastResults", lua_GetDebugSceneRayCastResults},
	{"GetCameraByIndex", lua_GetCameraByIndex},
	{"GetEntityByIndex", lua_GetEntityByIndex},
	{"GetLightByIndex", lua_GetLightByIndex},
	{"GetArmatureByIndex", lua_GetArmatureByIndex},
	{"GetParticlesByIndex", lua_GetParticlesByIndex},
	{"GetSpriteByIndex", lua_GetSpriteByIndex},
	{"GetTextureByName", lua_GetTextureByName},
	{"GetMaterialByName", lua_GetMaterialByName},
	{"GetModelByName", lua_GetModelByName},
	{"GetScriptByName", lua_GetScriptByName},
	{"GetCameraByName", lua_GetCameraByName},
	{"GetEntityByName", lua_GetEntityByName},
	{"GetLightByName", lua_GetLightByName},
	{"GetArmatureByName", lua_GetArmatureByName},
	{"GetParticlesByName", lua_GetParticlesByName},
	{"GetSpriteByName", lua_GetSpriteByName},
	{"GetActorByName", lua_GetActorByName},
	{"RemoveCameraByName", lua_RemoveCameraByName},
	{"RemoveEntityByName", lua_RemoveEntityByName},
	{"RemoveLightByName", lua_RemoveLightByName},
	{"RemoveParticlesByName", lua_RemoveParticlesByName},
	{"RemoveSpriteByName", lua_RemoveSpriteByName},
	{"RemoveCameraByIndex", lua_RemoveCameraByIndex},
	{"RemoveEntityByIndex", lua_RemoveEntityByIndex},
	{"RemoveLightByIndex", lua_RemoveLightByIndex},
	{"RemoveParticlesByIndex", lua_RemoveParticlesByIndex},
	{"RemoveSpriteByIndex", lua_RemoveSpriteByIndex},
	{"RemoveCameraByObject", lua_RemoveCameraByObject},
	{"RemoveEntityByObject", lua_RemoveEntityByObject},
	{"RemoveLightByObject", lua_RemoveLightByObject},
	{"RemoveParticlesByObject", lua_RemoveParticlesByObject},
	{"RemoveSpriteByObject", lua_RemoveSpriteByObject},
	{"RemoveActorByObject", lua_RemoveActorByObject},
	{"GetSceneScripts", lua_GetSceneScripts},
	{"GetSceneTextures", lua_GetSceneTextures},
	{"GetSceneMaterials", lua_GetSceneMaterials},
	{"GetSceneModels", lua_GetSceneModels},
	{"CreateScript", lua_CreateScript},
	{"CreateScriptFromFile", lua_CreateScriptFromFile},
	{"SetScriptName", lua_SetScriptName},
	{"GetScriptName", lua_GetScriptName},
	{"GetScriptFilePath", lua_GetScriptFilePath},
	{"SetScriptText", lua_SetScriptText},
	{"IsScriptError", lua_IsScriptError},
	{"RunString", lua_RunString},
	{"RunScript", lua_RunScript},
	{"SetAudioVolume", lua_SetAudioVolume},
	{"GetAudioVolume", lua_GetAudioVolume},
	{"SetAudioRolloff", lua_SetAudioRolloff},
	{"GetAudioRolloff", lua_GetAudioRolloff},
	{"LoadSound", lua_LoadSound},
	{"LoadStreamedSound", lua_LoadStreamedSound},
	{"GetSoundFileType", lua_GetSoundFileType},
	{"PlaySound", lua_PlaySound},
	{"PlayEntitySound", lua_PlayEntitySound},
	{"LoopSound", lua_LoopSound},
	{"LoopEntitySound", lua_LoopEntitySound},
	{"SetSoundVolume", lua_SetSoundVolume},
	{"GetSoundVolume", lua_GetSoundVolume},
	{"PauseSound", lua_PauseSound},
	{"ResumeSound", lua_ResumeSound},
	{"StopSound", lua_StopSound},
	{"IsSoundPlaying", lua_IsSoundPlaying},
	{"IsSoundPaused", lua_IsSoundPaused},
	{"GetCollisionActor", lua_GetCollisionActor},
	{"GetCollisionPosition", lua_GetCollisionPosition},
	{"GetCollisionNormal", lua_GetCollisionNormal},
	{"GetCollisionDepth", lua_GetCollisionDepth},
	{"GetJointName", lua_GetJointName},
	{"GetJointType", lua_GetJointType},
	{"GetJointActorA", lua_GetJointActorA},
	{"GetJointActorB", lua_GetJointActorB},
	{"GetJointPivot", lua_GetJointPivot},
	{"GetJointAxis", lua_GetJointAxis},
	{"CreateFontFromFile", lua_CreateFontFromFile},
	{"GetFontName", lua_GetFontName},
	{"GetFontFilePath", lua_GetFontFilePath},
	{"GetFontSize", lua_GetFontSize},
	{"GetStringWidth", lua_GetStringWidth},
	{"GetStringHeight", lua_GetStringHeight},
	{"GetGuiObjectName", lua_GetGuiObjectName},
	{"GetGuiObjectPosition", lua_GetGuiObjectPosition},
	{"GetGuiObjectSize", lua_GetGuiObjectSize},
	{"GetGuiObjectColor", lua_GetGuiObjectColor},
	{"GetGuiObjectVisible", lua_GetGuiObjectVisible},
	{"GetGuiObjectScript", lua_GetGuiObjectScript},
	{"GetGuiObjectEvent", lua_GetGuiObjectEvent},
	{"SetGuiObjectPosition", lua_SetGuiObjectPosition},
	{"SetGuiObjectColor", lua_SetGuiObjectColor},
	{"SetGuiObjectVisible", lua_SetGuiObjectVisible},
	{"SetGuiObjectScript", lua_SetGuiObjectScript},
	{"CreateLabel", lua_CreateLabel},
	{"GetLabelFont", lua_GetLabelFont},
	{"GetLabelText", lua_GetLabelText},
	{"SetLabelFont", lua_SetLabelFont},
	{"SetLabelText", lua_SetLabelText},
	{"CreateButton", lua_CreateButton},
	{"GetButtonState", lua_GetButtonState},
	{"GetButtonOffTexture", lua_GetButtonOffTexture},
	{"GetButtonOverTexture", lua_GetButtonOverTexture},
	{"GetButtonOnTexture", lua_GetButtonOnTexture},
	{"SetButtonOffTexture", lua_SetButtonOffTexture},
	{"SetButtonOverTexture", lua_SetButtonOverTexture},
	{"SetButtonOnTexture", lua_SetButtonOnTexture},
	{"CreatePicture", lua_CreatePicture},
	{"GetPictureTexture", lua_GetPictureTexture},
	{"GetPictureScale", lua_GetPictureScale},
	{"SetPictureTexture", lua_SetPictureTexture},
	{"SetPictureScale", lua_SetPictureScale},
	{"CreateTextField", lua_CreateTextField},
	{"GetTextFieldTexture", lua_GetTextFieldTexture},
	{"GetTextFieldFont", lua_GetTextFieldFont},
	{"GetTextFieldTextColor", lua_GetTextFieldTextColor},
	{"GetTextFieldOffset", lua_GetTextFieldOffset},
	{"GetTextFieldText", lua_GetTextFieldText},
	{"SetTextFieldTexture", lua_SetTextFieldTexture},
	{"SetTextFieldFont", lua_SetTextFieldFont},
	{"SetTextFieldTextColor", lua_SetTextFieldTextColor},
	{"SetTextFieldOffset", lua_SetTextFieldOffset},
	{"SetTextFieldCursorPosition", lua_SetTextFieldCursorPosition},
	{"SetTextFieldText", lua_SetTextFieldText},
	{"CreateSlider", lua_CreateSlider},
	{"GetSliderBackgroundTexture", lua_GetSliderBackgroundTexture},
	{"GetSliderSliderTexture", lua_GetSliderSliderTexture},
	{"GetSliderValue", lua_GetSliderValue},
	{"SetSliderBackgroundTexture", lua_SetSliderBackgroundTexture},
	{"SetSliderSliderTexture", lua_SetSliderSliderTexture},
	{"SetSliderValue", lua_SetSliderValue},
	{"CreateScreen", lua_CreateScreen},
	{"GetScreenTexture", lua_GetScreenTexture},
	{"SetScreenTexture", lua_SetScreenTexture},
	{"SetScreenToTop", lua_SetScreenToTop},
	{"ForceFocusToScreen", lua_ForceFocusToScreen},
	{"ReleaseFocusFromScreen", lua_ReleaseFocusFromScreen},
	{"CreateTextList", lua_CreateTextList},
	{"GetTextListFont", lua_GetTextListFont},
	{"GetTextListSelectionColor", lua_GetTextListSelectionColor},
	{"GetTextListLightColor", lua_GetTextListLightColor},
	{"GetTextListDarkColor", lua_GetTextListDarkColor},
	{"GetTextListRowCount", lua_GetTextListRowCount},
	{"GetTextListItemCount", lua_GetTextListItemCount},
	{"GetTextListSelectionIndex", lua_GetTextListSelectionIndex},
	{"GetTextListOffset", lua_GetTextListOffset},
	{"GetTextListItem", lua_GetTextListItem},
	{"GetTextListSelectedItem", lua_GetTextListSelectedItem},
	{"SetTextListFont", lua_SetTextListFont},
	{"SetTextListSelectionColor", lua_SetTextListSelectionColor},
	{"SetTextListLightColor", lua_SetTextListLightColor},
	{"SetTextListDarkColor", lua_SetTextListDarkColor},
	{"SetTextListSize", lua_SetTextListSize},
	{"AddTextListItem", lua_AddTextListItem},
	{"SetTextListItem", lua_SetTextListItem},
	{"RemoveTextListItem", lua_RemoveTextListItem},
	{"RemoveTextListItems", lua_RemoveTextListItems},
	{"SetTextListOffset", lua_SetTextListOffset},
	{"SetTextListSelection", lua_SetTextListSelection},
	{"CreateCheckBox", lua_CreateCheckBox},
	{"GetCheckBoxState", lua_GetCheckBoxState},
	{"GetCheckBoxOffTexture", lua_GetCheckBoxOffTexture},
	{"GetCheckBoxOnTexture", lua_GetCheckBoxOnTexture},
	{"SetCheckBoxOffTexture", lua_SetCheckBoxOffTexture},
	{"SetCheckBoxOnTexture", lua_SetCheckBoxOnTexture},
	{"SetCheckBoxState", lua_SetCheckBoxState},
	{"CreateGui", lua_CreateGui},
	{"AddGuiObject", lua_AddGuiObject},
	{"GetGuiObjectByName", lua_GetGuiObjectByName},
	{"GetGuiObjectByIndex", lua_GetGuiObjectByIndex},
	{"RemoveGuiObjectByName", lua_RemoveGuiObjectByName},
	{"RemoveGuiObjectByIndex", lua_RemoveGuiObjectByIndex},
	{"RemoveGuiObjectByObject", lua_RemoveGuiObjectByObject},
	{"GetGuiTrace", lua_GetGuiTrace},
	{"GetGuiFocus", lua_GetGuiFocus},
	{"GetGuiActiveTextField", lua_GetGuiActiveTextField},
	{"EmptyGui", lua_EmptyGui},
	{"CreateSession", lua_CreateSession},
	{"ConnectSession", lua_ConnectSession},
	{"DisconnectSession", lua_DisconnectSession},
	{"SendStringToClients", lua_SendStringToClients},
	{"SendStringToServer", lua_SendStringToServer},
	{"GetServerDataAsString", lua_GetServerDataAsString},
	{"GetClientDataAsString", lua_GetClientDataAsString},
	{"GetServerEvent", lua_GetServerEvent},
	{"GetClientEvent", lua_GetClientEvent},
	{"GetCurrentClient", lua_GetCurrentClient},
	{"IsServer", lua_IsServer},
	{"IsClient", lua_IsClient},
	{NULL, NULL}
};
int luaopen_elf(lua_State* L)
{
	lua_pushvalue(L, LUA_GLOBALSINDEX);
	luaL_register(L, NULL, lua_elf_functions);
	lua_pushstring(L, "NONE");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "FALSE");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "TRUE");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_ESC");
	lua_pushnumber(L, 135);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F1");
	lua_pushnumber(L, 136);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F2");
	lua_pushnumber(L, 137);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F3");
	lua_pushnumber(L, 138);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F4");
	lua_pushnumber(L, 139);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F5");
	lua_pushnumber(L, 140);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F6");
	lua_pushnumber(L, 141);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F7");
	lua_pushnumber(L, 142);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F8");
	lua_pushnumber(L, 143);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F9");
	lua_pushnumber(L, 144);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F10");
	lua_pushnumber(L, 145);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F11");
	lua_pushnumber(L, 146);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F12");
	lua_pushnumber(L, 147);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_UP");
	lua_pushnumber(L, 148);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_DOWN");
	lua_pushnumber(L, 149);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_LEFT");
	lua_pushnumber(L, 150);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_RIGHT");
	lua_pushnumber(L, 151);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_LSHIFT");
	lua_pushnumber(L, 152);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_RSHIFT");
	lua_pushnumber(L, 153);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_LCTRL");
	lua_pushnumber(L, 154);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_RCTRL");
	lua_pushnumber(L, 155);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_LALT");
	lua_pushnumber(L, 156);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_RALT");
	lua_pushnumber(L, 157);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_TAB");
	lua_pushnumber(L, 158);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_ENTER");
	lua_pushnumber(L, 159);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_BACKSPACE");
	lua_pushnumber(L, 160);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_INSERT");
	lua_pushnumber(L, 161);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_DEL");
	lua_pushnumber(L, 162);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_PAGEUP");
	lua_pushnumber(L, 163);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_PAGEDOWN");
	lua_pushnumber(L, 164);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_HOME");
	lua_pushnumber(L, 165);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_END");
	lua_pushnumber(L, 166);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_0");
	lua_pushnumber(L, 167);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_1");
	lua_pushnumber(L, 168);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_2");
	lua_pushnumber(L, 169);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_3");
	lua_pushnumber(L, 170);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_4");
	lua_pushnumber(L, 171);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_5");
	lua_pushnumber(L, 172);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_6");
	lua_pushnumber(L, 173);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_7");
	lua_pushnumber(L, 174);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_8");
	lua_pushnumber(L, 175);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_9");
	lua_pushnumber(L, 176);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_DIVIDE");
	lua_pushnumber(L, 177);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_MULTIPLY");
	lua_pushnumber(L, 178);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_SUBTRACT");
	lua_pushnumber(L, 179);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_ADD");
	lua_pushnumber(L, 180);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_DECIMAL");
	lua_pushnumber(L, 181);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_EQUAL");
	lua_pushnumber(L, 182);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_KP_ENTER");
	lua_pushnumber(L, 183);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_SPACE");
	lua_pushnumber(L, 32);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_0");
	lua_pushnumber(L, 48);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_1");
	lua_pushnumber(L, 49);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_2");
	lua_pushnumber(L, 50);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_3");
	lua_pushnumber(L, 51);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_4");
	lua_pushnumber(L, 52);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_5");
	lua_pushnumber(L, 53);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_6");
	lua_pushnumber(L, 54);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_7");
	lua_pushnumber(L, 55);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_8");
	lua_pushnumber(L, 56);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_9");
	lua_pushnumber(L, 57);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_A");
	lua_pushnumber(L, 65);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_B");
	lua_pushnumber(L, 66);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_C");
	lua_pushnumber(L, 67);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_D");
	lua_pushnumber(L, 68);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_E");
	lua_pushnumber(L, 69);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_F");
	lua_pushnumber(L, 70);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_G");
	lua_pushnumber(L, 71);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_H");
	lua_pushnumber(L, 72);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_I");
	lua_pushnumber(L, 73);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_J");
	lua_pushnumber(L, 74);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_K");
	lua_pushnumber(L, 75);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_L");
	lua_pushnumber(L, 76);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_M");
	lua_pushnumber(L, 77);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_N");
	lua_pushnumber(L, 78);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_O");
	lua_pushnumber(L, 79);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_P");
	lua_pushnumber(L, 80);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_Q");
	lua_pushnumber(L, 81);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_R");
	lua_pushnumber(L, 82);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_S");
	lua_pushnumber(L, 83);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_T");
	lua_pushnumber(L, 84);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_U");
	lua_pushnumber(L, 85);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_V");
	lua_pushnumber(L, 86);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_W");
	lua_pushnumber(L, 87);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_X");
	lua_pushnumber(L, 88);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_Y");
	lua_pushnumber(L, 89);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_Z");
	lua_pushnumber(L, 90);
	lua_settable(L, -3);
	lua_pushstring(L, "UP");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "PRESSED");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "DOWN");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "RELEASED");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "OFF");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "ON");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "OVER");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "BUTTON_LEFT");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "BUTTON_MIDDLE");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "BUTTON_RIGHT");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "TEXTURE");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "MATERIAL");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "MODEL");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "CAMERA");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "ENTITY");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "LIGHT");
	lua_pushnumber(L, 0x0005);
	lua_settable(L, -3);
	lua_pushstring(L, "SCENE");
	lua_pushnumber(L, 0x0006);
	lua_settable(L, -3);
	lua_pushstring(L, "LIST");
	lua_pushnumber(L, 0x0007);
	lua_settable(L, -3);
	lua_pushstring(L, "PAK");
	lua_pushnumber(L, 0x0008);
	lua_settable(L, -3);
	lua_pushstring(L, "PAK_INDEX");
	lua_pushnumber(L, 0x0009);
	lua_settable(L, -3);
	lua_pushstring(L, "KEY_EVENT");
	lua_pushnumber(L, 0x000A);
	lua_settable(L, -3);
	lua_pushstring(L, "CHAR_EVENT");
	lua_pushnumber(L, 0x000B);
	lua_settable(L, -3);
	lua_pushstring(L, "CONTEXT");
	lua_pushnumber(L, 0x000C);
	lua_settable(L, -3);
	lua_pushstring(L, "ENGINE");
	lua_pushnumber(L, 0x000D);
	lua_settable(L, -3);
	lua_pushstring(L, "TIMER");
	lua_pushnumber(L, 0x000E);
	lua_settable(L, -3);
	lua_pushstring(L, "IMAGE");
	lua_pushnumber(L, 0x000F);
	lua_settable(L, -3);
	lua_pushstring(L, "POST_PROCESS");
	lua_pushnumber(L, 0x0010);
	lua_settable(L, -3);
	lua_pushstring(L, "SCRIPT");
	lua_pushnumber(L, 0x0011);
	lua_settable(L, -3);
	lua_pushstring(L, "AUDIO_DEVICE");
	lua_pushnumber(L, 0x0012);
	lua_settable(L, -3);
	lua_pushstring(L, "AUDIO_SOURCE");
	lua_pushnumber(L, 0x0013);
	lua_settable(L, -3);
	lua_pushstring(L, "SOUND");
	lua_pushnumber(L, 0x0014);
	lua_settable(L, -3);
	lua_pushstring(L, "BONE");
	lua_pushnumber(L, 0x0015);
	lua_settable(L, -3);
	lua_pushstring(L, "ARMATURE");
	lua_pushnumber(L, 0x0016);
	lua_settable(L, -3);
	lua_pushstring(L, "STRING");
	lua_pushnumber(L, 0x0017);
	lua_settable(L, -3);
	lua_pushstring(L, "FONT");
	lua_pushnumber(L, 0x0018);
	lua_settable(L, -3);
	lua_pushstring(L, "LABEL");
	lua_pushnumber(L, 0x0019);
	lua_settable(L, -3);
	lua_pushstring(L, "BUTTON");
	lua_pushnumber(L, 0x001A);
	lua_settable(L, -3);
	lua_pushstring(L, "PICTURE");
	lua_pushnumber(L, 0x001B);
	lua_settable(L, -3);
	lua_pushstring(L, "TEXT_FIELD");
	lua_pushnumber(L, 0x001C);
	lua_settable(L, -3);
	lua_pushstring(L, "SLIDER");
	lua_pushnumber(L, 0x001D);
	lua_settable(L, -3);
	lua_pushstring(L, "SCREEN");
	lua_pushnumber(L, 0x001E);
	lua_settable(L, -3);
	lua_pushstring(L, "TEXT_LIST");
	lua_pushnumber(L, 0x001F);
	lua_settable(L, -3);
	lua_pushstring(L, "CHECK_BOX");
	lua_pushnumber(L, 0x0020);
	lua_settable(L, -3);
	lua_pushstring(L, "GUI");
	lua_pushnumber(L, 0x0021);
	lua_settable(L, -3);
	lua_pushstring(L, "DIRECTORY_ITEM");
	lua_pushnumber(L, 0x0022);
	lua_settable(L, -3);
	lua_pushstring(L, "DIRECTORY");
	lua_pushnumber(L, 0x0023);
	lua_settable(L, -3);
	lua_pushstring(L, "COLLISION");
	lua_pushnumber(L, 0x0034);
	lua_settable(L, -3);
	lua_pushstring(L, "PHYSICS_OBJECT");
	lua_pushnumber(L, 0x0035);
	lua_settable(L, -3);
	lua_pushstring(L, "PHYSICS_WORLD");
	lua_pushnumber(L, 0x0036);
	lua_settable(L, -3);
	lua_pushstring(L, "JOINT");
	lua_pushnumber(L, 0x0037);
	lua_settable(L, -3);
	lua_pushstring(L, "PARTICLE");
	lua_pushnumber(L, 0x0038);
	lua_settable(L, -3);
	lua_pushstring(L, "PARTICLES");
	lua_pushnumber(L, 0x0039);
	lua_settable(L, -3);
	lua_pushstring(L, "CONFIG");
	lua_pushnumber(L, 0x003A);
	lua_settable(L, -3);
	lua_pushstring(L, "BEZIER_POINT");
	lua_pushnumber(L, 0x003B);
	lua_settable(L, -3);
	lua_pushstring(L, "BEZIER_CURVE");
	lua_pushnumber(L, 0x003C);
	lua_settable(L, -3);
	lua_pushstring(L, "IPO");
	lua_pushnumber(L, 0x003D);
	lua_settable(L, -3);
	lua_pushstring(L, "FRAME_PLAYER");
	lua_pushnumber(L, 0x003E);
	lua_settable(L, -3);
	lua_pushstring(L, "PROPERTY");
	lua_pushnumber(L, 0x003F);
	lua_settable(L, -3);
	lua_pushstring(L, "CLIENT");
	lua_pushnumber(L, 0x0040);
	lua_settable(L, -3);
	lua_pushstring(L, "SCRIPTING");
	lua_pushnumber(L, 0x0041);
	lua_settable(L, -3);
	lua_pushstring(L, "PHYSICS_TRI_MESH");
	lua_pushnumber(L, 0x0042);
	lua_settable(L, -3);
	lua_pushstring(L, "SPRITE");
	lua_pushnumber(L, 0x0043);
	lua_settable(L, -3);
	lua_pushstring(L, "VIDEO_MODE");
	lua_pushnumber(L, 0x0044);
	lua_settable(L, -3);
	lua_pushstring(L, "GENERAL");
	lua_pushnumber(L, 0x0045);
	lua_settable(L, -3);
	lua_pushstring(L, "VERTICE");
	lua_pushnumber(L, 0x0046);
	lua_settable(L, -3);
	lua_pushstring(L, "FACE");
	lua_pushnumber(L, 0x0047);
	lua_settable(L, -3);
	lua_pushstring(L, "MESH_DATA");
	lua_pushnumber(L, 0x0048);
	lua_settable(L, -3);
	lua_pushstring(L, "LIST_PTR");
	lua_pushnumber(L, 0x0049);
	lua_settable(L, -3);
	lua_pushstring(L, "OBJECT_TYPE_COUNT");
	lua_pushnumber(L, 0x004A);
	lua_settable(L, -3);
	lua_pushstring(L, "PERSPECTIVE");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "ORTHOGRAPHIC");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "BOX");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "SPHERE");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "MESH");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "CAPSULE_X");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "CAPSULE_Y");
	lua_pushnumber(L, 0x0005);
	lua_settable(L, -3);
	lua_pushstring(L, "CAPSULE_Z");
	lua_pushnumber(L, 0x0006);
	lua_settable(L, -3);
	lua_pushstring(L, "CONE_X");
	lua_pushnumber(L, 0x0007);
	lua_settable(L, -3);
	lua_pushstring(L, "CONE_Y");
	lua_pushnumber(L, 0x0008);
	lua_settable(L, -3);
	lua_pushstring(L, "CONE_Z");
	lua_pushnumber(L, 0x0009);
	lua_settable(L, -3);
	lua_pushstring(L, "HINGE");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "BALL");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "CONE_TWIST");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "POINT_LIGHT");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "SUN_LIGHT");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "SPOT_LIGHT");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "LUMINANCE");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "LUMINANCE_ALPHA");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "RGB");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "RGBA");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "BGR");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "BGRA");
	lua_pushnumber(L, 0x0005);
	lua_settable(L, -3);
	lua_pushstring(L, "RGB16F");
	lua_pushnumber(L, 0x0006);
	lua_settable(L, -3);
	lua_pushstring(L, "RGB32F");
	lua_pushnumber(L, 0x0007);
	lua_settable(L, -3);
	lua_pushstring(L, "RGBA16F");
	lua_pushnumber(L, 0x0008);
	lua_settable(L, -3);
	lua_pushstring(L, "RGBA32F");
	lua_pushnumber(L, 0x0009);
	lua_settable(L, -3);
	lua_pushstring(L, "ALPHA32F");
	lua_pushnumber(L, 0x000A);
	lua_settable(L, -3);
	lua_pushstring(L, "DEPTH_COMPONENT");
	lua_pushnumber(L, 0x000B);
	lua_settable(L, -3);
	lua_pushstring(L, "COMPRESSED_RGB");
	lua_pushnumber(L, 0x000C);
	lua_settable(L, -3);
	lua_pushstring(L, "COMPRESSED_RGBA");
	lua_pushnumber(L, 0x000D);
	lua_settable(L, -3);
	lua_pushstring(L, "FLOAT");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "INT");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "UINT");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "SHORT");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "USHORT");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "BYTE");
	lua_pushnumber(L, 0x0005);
	lua_settable(L, -3);
	lua_pushstring(L, "UBYTE");
	lua_pushnumber(L, 0x0006);
	lua_settable(L, -3);
	lua_pushstring(L, "PROPERTY_INT");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "PROPERTY_FLOAT");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "PROPERTY_STRING");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "PROPERTY_BOOL");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "COLOR_MAP");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "NORMAL_MAP");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "HEIGHT_MAP");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "SPECULAR_MAP");
	lua_pushnumber(L, 0x0008);
	lua_settable(L, -3);
	lua_pushstring(L, "DETAIL_MAP");
	lua_pushnumber(L, 0x0010);
	lua_settable(L, -3);
	lua_pushstring(L, "SHADOW_MAP");
	lua_pushnumber(L, 0x0020);
	lua_settable(L, -3);
	lua_pushstring(L, "COLOR_RAMP_MAP");
	lua_pushnumber(L, 0x0040);
	lua_settable(L, -3);
	lua_pushstring(L, "LIGHT_MAP");
	lua_pushnumber(L, 0x0080);
	lua_settable(L, -3);
	lua_pushstring(L, "CUBE_MAP");
	lua_pushnumber(L, 0x0100);
	lua_settable(L, -3);
	lua_pushstring(L, "TRANSPARENT");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "ADD");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "DIR");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "FILE");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "CLICKED");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "VALUE_CHANGED");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "GAIN_FOCUS");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "LOSE_FOCUS");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "CHAR_INPUT");
	lua_pushnumber(L, 0x0005);
	lua_settable(L, -3);
	lua_pushstring(L, "SELECTION_CHANGED");
	lua_pushnumber(L, 0x0006);
	lua_settable(L, -3);
	lua_pushstring(L, "STATE_CHANGED");
	lua_pushnumber(L, 0x0007);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_1");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_2");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_3");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_4");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_5");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_6");
	lua_pushnumber(L, 0x0005);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_7");
	lua_pushnumber(L, 0x0006);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_8");
	lua_pushnumber(L, 0x0007);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_9");
	lua_pushnumber(L, 0x0008);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_10");
	lua_pushnumber(L, 0x0009);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_11");
	lua_pushnumber(L, 0x000A);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_12");
	lua_pushnumber(L, 0x000B);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_13");
	lua_pushnumber(L, 0x000C);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_14");
	lua_pushnumber(L, 0x000D);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_15");
	lua_pushnumber(L, 0x000E);
	lua_settable(L, -3);
	lua_pushstring(L, "JOYSTICK_BUTTON_16");
	lua_pushnumber(L, 0x000F);
	lua_settable(L, -3);
	lua_pushstring(L, "LOC_X");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "LOC_Y");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "LOC_Z");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "ROT_X");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "ROT_Y");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "ROT_Z");
	lua_pushnumber(L, 0x0005);
	lua_settable(L, -3);
	lua_pushstring(L, "SCALE_X");
	lua_pushnumber(L, 0x0006);
	lua_settable(L, -3);
	lua_pushstring(L, "SCALE_Y");
	lua_pushnumber(L, 0x0007);
	lua_settable(L, -3);
	lua_pushstring(L, "SCALE_Z");
	lua_pushnumber(L, 0x0008);
	lua_settable(L, -3);
	lua_pushstring(L, "QUA_X");
	lua_pushnumber(L, 0x0009);
	lua_settable(L, -3);
	lua_pushstring(L, "QUA_Y");
	lua_pushnumber(L, 0x000A);
	lua_settable(L, -3);
	lua_pushstring(L, "QUA_Z");
	lua_pushnumber(L, 0x000B);
	lua_settable(L, -3);
	lua_pushstring(L, "QUA_W");
	lua_pushnumber(L, 0x000C);
	lua_settable(L, -3);
	lua_pushstring(L, "NET_NONE");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "NET_CONNECT");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "NET_RECEIVE");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "NET_DISCONNECT");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "OGG");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "WAV");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "NO_ERROR");
	lua_pushnumber(L, 0x0000);
	lua_settable(L, -3);
	lua_pushstring(L, "INVALID_FILE");
	lua_pushnumber(L, 0x0001);
	lua_settable(L, -3);
	lua_pushstring(L, "CANT_OPEN_FILE");
	lua_pushnumber(L, 0x0002);
	lua_settable(L, -3);
	lua_pushstring(L, "CANT_OPEN_DIRECTORY");
	lua_pushnumber(L, 0x0003);
	lua_settable(L, -3);
	lua_pushstring(L, "CANT_INITIALIZE");
	lua_pushnumber(L, 0x0004);
	lua_settable(L, -3);
	lua_pushstring(L, "CANT_RUN_STRING");
	lua_pushnumber(L, 0x0005);
	lua_settable(L, -3);
	lua_pushstring(L, "CANT_RUN_SCRIPT");
	lua_pushnumber(L, 0x0006);
	lua_settable(L, -3);
	lua_pushstring(L, "CANT_CREATE");
	lua_pushnumber(L, 0x0007);
	lua_settable(L, -3);
	lua_pushstring(L, "CANT_RESIZE");
	lua_pushnumber(L, 0x0008);
	lua_settable(L, -3);
	lua_pushstring(L, "INVALID_SIZE");
	lua_pushnumber(L, 0x0009);
	lua_settable(L, -3);
	lua_pushstring(L, "UNKNOWN_FORMAT");
	lua_pushnumber(L, 0x000A);
	lua_settable(L, -3);
	lua_pushstring(L, "UNKNOWN_TYPE");
	lua_pushnumber(L, 0x000B);
	lua_settable(L, -3);
	lua_pushstring(L, "INVALID_HANDLE");
	lua_pushnumber(L, 0x000C);
	lua_settable(L, -3);
	lua_pushstring(L, "MISSING_FEATURE");
	lua_pushnumber(L, 0x000D);
	lua_settable(L, -3);
	lua_pushstring(L, "INVALID_MESH");
	lua_pushnumber(L, 0x000E);
	lua_settable(L, -3);
	lua_pop(L, 1);
	luaL_newmetatable(L, "lua_elf_vec2i_mt");
	luaL_register(L, NULL, lua_elf_vec2i_mt);
	lua_pop(L, 1);
	luaL_newmetatable(L, "lua_elf_vec2f_mt");
	luaL_register(L, NULL, lua_elf_vec2f_mt);
	lua_pop(L, 1);
	luaL_newmetatable(L, "lua_elf_vec3f_mt");
	luaL_register(L, NULL, lua_elf_vec3f_mt);
	lua_pop(L, 1);
	luaL_newmetatable(L, "lua_elf_vec4f_mt");
	luaL_register(L, NULL, lua_elf_vec4f_mt);
	lua_pop(L, 1);
	luaL_newmetatable(L, "lua_elf_color_mt");
	luaL_register(L, NULL, lua_elf_color_mt);
	lua_pop(L, 1);
	luaL_newmetatable(L, "lua_elf_object_mt");
	luaL_register(L, NULL, lua_elf_object_mt);
	lua_pop(L, 1);
	return 0;
}
