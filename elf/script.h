
elf_script* elf_create_script(const char* name)
{
	elf_script* script;

	script = (elf_script*)malloc(sizeof(elf_script));
	memset(script, 0x0, sizeof(elf_script));
	script->obj_type = ELF_SCRIPT;
	script->obj_destr = elf_destroy_script;

	script->id = ++gen->script_id_counter;

	if(name) script->name = elf_create_string(name);

	elf_inc_obj(ELF_SCRIPT);

	return script;
}

elf_script* elf_create_script_from_file(const char* file_path)
{
	elf_script* script = NULL;
	FILE* file;
	int length;
	char* text;

	file = fopen(file_path, "r");
	if(!file)
	{
		elf_set_error(ELF_CANT_OPEN_FILE, "error: can't open file \"%s\"\n", file_path);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	if(length > 0)
	{
		text = (char*)malloc(sizeof(char)*length+1);
		memset(text, 0x0, sizeof(char)*length+1);
		fread(text, sizeof(char), length, file);

		script = elf_create_script(NULL);

		script->name = elf_create_string(file_path);
		script->file_path = elf_create_string(file_path);

		elf_set_script_text(script, text);

		free(text);
	}

	fclose(file);

	return script;
}

void elf_destroy_script(void* data)
{
	elf_script* script = (elf_script*)data;

	if(script->name) elf_destroy_string(script->name);
	if(script->file_path) elf_destroy_string(script->file_path);
	if(script->text) elf_destroy_string(script->text);

	elf_dec_obj(ELF_SCRIPT);

	free(script);
}

void elf_set_script_name(elf_script* script, const char* name)
{
	if(script->name) elf_destroy_string(script->name);
	script->name = elf_create_string(name);
}

const char* elf_get_script_name(elf_script* script)
{
	return script->name;
}

const char* elf_get_script_file_path(elf_script* script)
{
	return script->file_path;
}

void elf_set_script_text(elf_script* script, const char* text)
{
	if(script->text) elf_destroy_string(script->text);
	script->text = NULL;
	if(text) script->text = elf_create_string(text);
	script->error = ELF_FALSE;
}

unsigned char elf_is_script_error(elf_script* script)
{
	return script->error;
}

