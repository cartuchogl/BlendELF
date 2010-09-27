
void elf_init_general()
{
	if(gen) return;

	gen = (elf_general*)malloc(sizeof(elf_general));
	memset(gen, 0x0, sizeof(elf_general));
	gen->obj_type = ELF_GENERAL;

	gen->log = elf_create_string("elf.log");

}

void elf_deinit_general()
{
	if(!gen) return;

	if(gen->err_str) elf_destroy_string(gen->err_str);

	if(gen->ref_count > 0)
	{
		elf_write_to_log("error: possible memory leak in ELF, [%d] references not dereferenced\n",
			elf_get_global_ref_count());
		elf_dump_ref_table();
	}

	if(gen->ref_count < 0)
	{
		elf_write_to_log("error: possible double free in ELF, [%d] negative reference count\n",
			elf_get_global_ref_count());
		elf_dump_ref_table();
	}

	if(gen->obj_count > 1)
	{
		elf_write_to_log("error: possible memory leak in ELF, [%d] objects not destroyed\n",
			elf_get_global_obj_count()-1);
		elf_dump_obj_table();
	}

	if(gen->obj_count < 1)
	{
		elf_write_to_log("error: possible double free in ELF, [%d] negative object count\n",
			elf_get_global_obj_count()-1);
		elf_dump_obj_table();
	}

	if(gen->log) elf_destroy_string(gen->log);

	free(gen);
}

void elf_inc_ref(elf_object* obj)
{
	gen->ref_count++;
	gen->ref_table[obj->obj_type]++;
	obj->obj_ref_count++;
}

void elf_dec_ref(elf_object* obj)
{
	gen->ref_count--;
	gen->ref_table[obj->obj_type]--;
	obj->obj_ref_count--;

	if(obj->obj_ref_count < 1)
	{
		if(obj->obj_destr)
		{
			obj->obj_destr(obj);
		}
		else
		{
			elf_write_to_log("error: no destructor specified for object\n");
		}
	}
}

void elf_inc_obj(int type)
{
	gen->obj_count++;
	gen->obj_table[type]++;
}

void elf_dec_obj(int type)
{
	gen->obj_count--;
	gen->obj_table[type]--;
}

void elf_dump_ref_table()
{
	int i;

	elf_write_to_log("---------- REF COUNT TABLE ----------\n");

	for(i = 0; i < ELF_OBJECT_TYPE_COUNT; i++)
	{
		elf_write_to_log("%d : %d\n", i, gen->ref_table[i]);
	}

	elf_write_to_log("-------------------------------------\n");
}

void elf_dump_obj_table()
{
	int i;

	elf_write_to_log("---------- OBJ COUNT TABLE ----------\n");

	for(i = 0; i < ELF_OBJECT_TYPE_COUNT; i++)
	{
		elf_write_to_log("%d : %d\n", i, gen->obj_table[i]);
	}

	elf_write_to_log("-------------------------------------\n");
}

int elf_get_object_type(elf_object* obj)
{
	return obj->obj_type;
}

int elf_get_object_ref_count(elf_object* obj)
{
	return obj->obj_ref_count;
}

int elf_get_global_ref_count()
{
	return gen->ref_count;
}

int elf_get_global_obj_count()
{
	return gen->obj_count;
}

unsigned char elf_is_actor(elf_object* obj)
{
	if(obj->obj_type == ELF_CAMERA || obj->obj_type == ELF_ENTITY ||
		obj->obj_type == ELF_LIGHT || obj->obj_type == ELF_PARTICLES ||
		obj->obj_type == ELF_SPRITE) return ELF_TRUE;
	return ELF_FALSE;
}

unsigned char elf_is_gui_object(elf_object* obj)
{
	if(obj->obj_type == ELF_GUI || obj->obj_type == ELF_LABEL || obj->obj_type == ELF_BUTTON ||
		obj->obj_type == ELF_PICTURE || obj->obj_type == ELF_TEXT_FIELD ||
		obj->obj_type == ELF_SLIDER || obj->obj_type == ELF_SCREEN ||
		obj->obj_type == ELF_TEXT_LIST || obj->obj_type == ELF_CHECK_BOX) return ELF_TRUE;
	return ELF_FALSE;
}

void elf_set_log_file_path(const char* file_path)
{
	FILE* file;

	file = fopen(file_path, "a");
	if(!file)
	{
		file = fopen(file_path, "w");
		if(!file)
		{
			printf("error: can't open log file \"%s\", reverting to default\n", file_path);
			return;
		}
	}

	if(gen->log) elf_destroy_string(gen->log);
	gen->log = elf_create_string(file_path);
}

