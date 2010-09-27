
gfx_general* gfx_create_general()
{
	gfx_general* general;

	general = (gfx_general*)malloc(sizeof(gfx_general));
	memset(general, 0x0, sizeof(gfx_general));

	return general;
}

void gfx_destroy_general(gfx_general* general)
{
	free(general);	
}

void gfx_dump_ref_table()
{
	int i;

	elf_write_to_log("---------- REF COUNT TABLE ----------\n");

	for(i = 0; i < GFX_OBJECT_TYPE_COUNT; i++)
	{
		elf_write_to_log("%d : %d\n", i, gfx_gen->ref_table[i]);
	}

	elf_write_to_log("-------------------------------------\n");
}

void gfx_dump_obj_table()
{
	int i;

	elf_write_to_log("---------- OBJ COUNT TABLE ----------\n");

	for(i = 0; i < GFX_OBJECT_TYPE_COUNT; i++)
	{
		elf_write_to_log("%d : %d\n", i, gfx_gen->obj_table[i]);
	}

	elf_write_to_log("-------------------------------------\n");
}

void gfx_inc_ref(gfx_object* obj)
{
	gfx_gen->ref_count++;
	gfx_gen->ref_table[obj->obj_type]++;
	obj->obj_ref_count++;
}

void gfx_dec_ref(gfx_object* obj)
{
	gfx_gen->ref_count--;
	gfx_gen->ref_table[obj->obj_type]--;
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

void gfx_inc_obj(int type)
{
	gfx_gen->obj_count++;
	gfx_gen->obj_table[type]++;
}

void gfx_dec_obj(int type)
{
	gfx_gen->obj_count--;
	gfx_gen->obj_table[type]--;
}

int gfx_get_object_type(gfx_object* obj)
{
	return obj->obj_type;
}

int gfx_get_object_ref_count(gfx_object* obj)
{
	return obj->obj_ref_count;
}

int gfx_get_global_ref_count()
{
	return gfx_gen->ref_count;
}

int gfx_get_global_obj_count()
{
	return gfx_gen->obj_count;
}

