
#include "default.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "gfx.h"
#include "blendelf.h"
#include "types.h"

int luaopen_elf(lua_State* L);

struct elf_scripting {
	ELF_OBJECT_HEADER;
	struct lua_State *L;
	elf_list *cur_scripts;
};

elf_scripting *scr = NULL;

elf_scripting* elf_create_scripting()
{
	elf_scripting *scripting;

	scripting = (elf_scripting*)malloc(sizeof(elf_scripting));
	memset(scripting, 0x0, sizeof(elf_scripting));
	scripting->type = ELF_SCRIPTING;

	scripting->L = lua_open();
	if(!scripting->L)
	{
		elf_set_error(ELF_CANT_INITIALIZE, "error: failed to initialize lua\n");
		elf_destroy_scripting(scripting);
		return NULL;
	}
	luaL_openlibs(scripting->L);
	luaopen_elf(scripting->L);

	scripting->cur_scripts = elf_create_list();
	elf_inc_ref((elf_object*)scripting->cur_scripts);

	return scripting;
}

void elf_destroy_scripting(elf_scripting *scripting)
{
	if(scripting->L) lua_close(scripting->L);

	elf_dec_ref((elf_object*)scripting->cur_scripts);

	free(scripting);
}

unsigned char elf_init_scripting()
{
	if(scr)
	{
		elf_write_to_log("warning: cannot initialize scripting twice\n");
		return ELF_TRUE;
	}

	scr = elf_create_scripting();
	if(!scr) return ELF_FALSE;

	elf_inc_ref((elf_object*)scr);

	return ELF_TRUE;
}

void elf_update_scripting()
{
	if(scr) lua_gc(scr->L, LUA_GCCOLLECT, 0);
}

void elf_deinit_scripting()
{
	if(!scr) return;

	elf_dec_ref((elf_object*)scr);
	scr = NULL;
}

elf_script* elf_get_current_script()
{
	if(!scr) return NULL;
	return (elf_script*)elf_rbegin_list(scr->cur_scripts);
}

void elf_set_script_error(int err, const char *msg)
{
	lua_Debug ar;
	elf_script *script;

	if(!scr) return;

	lua_getstack(scr->L, 0 + 1, &ar);
	lua_getinfo(scr->L, "Sl", &ar);
	//luaL_where(scr->L, 0);

	script = elf_get_current_script();
	if(ar.source[0] == '@')
	{
		elf_set_error_no_save(err, "[%s]:%d: %s\n", ar.short_src, ar.currentline, msg);
	}
	else
	{
		elf_set_error_no_save(err, "[%s \"%s\"]:%d: %s\n", script->file_path, script->name, ar.currentline, msg);
	}
}

unsigned char elf_run_string(const char *str)
{
	int err;

	if(!scr || !str) return ELF_FALSE;

	err = 0;
	err = luaL_dostring(scr->L, str);
	if(err)
	{
		elf_set_error(ELF_CANT_RUN_STRING, "error: can't run string \"%s\"\n%s\n", str, lua_tostring(scr->L, -1));
		return ELF_FALSE;
	}

	return ELF_TRUE;
}

unsigned char elf_run_script(elf_script *script)
{
	int err;
	
	if(!scr || !script->text || script->error) return ELF_FALSE;

	elf_append_to_list(scr->cur_scripts, (elf_object*)script);

	err = 0;
	err = luaL_dostring(scr->L, script->text);
	if(err)
	{
		elf_set_error(ELF_CANT_RUN_SCRIPT, "error: can't run script \"%s\"\n%s\n", script->name, lua_tostring(scr->L, -1));

		script->error = ELF_TRUE;
		elf_rbegin_list(scr->cur_scripts);
		elf_remove_from_list(scr->cur_scripts, (elf_object*)script);
		return ELF_FALSE;
	}

	elf_rbegin_list(scr->cur_scripts);
	elf_remove_from_list(scr->cur_scripts, (elf_object*)script);
	return ELF_TRUE;
}

