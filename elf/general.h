
void elfInitGeneral()
{
	if(gen) return;

	gen = (elfGeneral*)malloc(sizeof(elfGeneral));
	memset(gen, 0x0, sizeof(elfGeneral));
	gen->objType = ELF_GENERAL;

	gen->log = (char*)malloc(sizeof(char)*8);
	memcpy(gen->log, "elf.log", sizeof(char)*7);
	gen->log[7] = '\0';

}

void elfDeinitGeneral()
{
	if(!gen) return;

	if(gen->refCount > 0)
	{
		elfLogWrite("error: possible memory leak in ELF, [%d] references not dereferenced\n",
			elfGetGlobalRefCount());
		elfDumpRefTable();
	}

	if(gen->refCount < 0)
	{
		elfLogWrite("error: possible double free in ELF, [%d] negative reference count\n",
			elfGetGlobalRefCount());
		elfDumpRefTable();
	}

	if(gen->objCount > 0)
	{
		elfLogWrite("error: possible memory leak in ELF, [%d] objects not destroyed\n",
			elfGetGlobalObjCount());
		elfDumpObjTable();
	}

	if(gen->objCount < 0)
	{
		elfLogWrite("error: possible double free in ELF, [%d] negative object count\n",
			elfGetGlobalObjCount());
		elfDumpObjTable();
	}

	if(gen->errStr) free(gen->errStr);
	if(gen->log) free(gen->log);

	free(gen);
}

ELF_API void ELF_APIENTRY elfIncRef(elfObject* obj)
{
	gen->refCount++;
	gen->refTable[obj->objType]++;
	obj->objRefCount++;
}

ELF_API void ELF_APIENTRY elfDecRef(elfObject* obj)
{
	gen->refCount--;
	gen->refTable[obj->objType]--;
	obj->objRefCount--;

	if(obj->objRefCount < 1)
	{
		if(obj->objDestr)
		{
			obj->objDestr(obj);
		}
		else
		{
			elfLogWrite("error: no destructor specified for object\n");
		}
	}
}

void elfIncObj(int type)
{
	gen->objCount++;
	gen->objTable[type]++;
}

void elfDecObj(int type)
{
	gen->objCount--;
	gen->objTable[type]--;
}

void elfDumpRefTable()
{
	int i;

	elfLogWrite("---------- REF COUNT TABLE ----------\n");

	for(i = 0; i < ELF_OBJECT_TYPE_COUNT; i++)
	{
		elfLogWrite("%d : %d\n", i, gen->refTable[i]);
	}

	elfLogWrite("-------------------------------------\n");
}

void elfDumpObjTable()
{
	int i;

	elfLogWrite("---------- OBJ COUNT TABLE ----------\n");

	for(i = 0; i < ELF_OBJECT_TYPE_COUNT; i++)
	{
		elfLogWrite("%d : %d\n", i, gen->objTable[i]);
	}

	elfLogWrite("-------------------------------------\n");
}

ELF_API int ELF_APIENTRY elfGetObjectType(elfObject* obj)
{
	return obj->objType;
}

ELF_API int ELF_APIENTRY elfGetObjectRefCount(elfObject* obj)
{
	return obj->objRefCount;
}

ELF_API int ELF_APIENTRY elfGetGlobalRefCount()
{
	return gen->refCount;
}

ELF_API int ELF_APIENTRY elfGetGlobalObjCount()
{
	return gen->objCount;
}

ELF_API unsigned char ELF_APIENTRY elfIsActor(elfObject* obj)
{
	if(obj->objType == ELF_CAMERA || obj->objType == ELF_ENTITY ||
		obj->objType == ELF_LIGHT || obj->objType == ELF_PARTICLES ||
		obj->objType == ELF_SPRITE) return ELF_TRUE;
	return ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfIsGuiObject(elfObject* obj)
{
	if(obj->objType == ELF_GUI || obj->objType == ELF_LABEL || obj->objType == ELF_BUTTON ||
		obj->objType == ELF_PICTURE || obj->objType == ELF_TEXT_FIELD ||
		obj->objType == ELF_SLIDER || obj->objType == ELF_SCREEN ||
		obj->objType == ELF_TEXT_LIST || obj->objType == ELF_CHECK_BOX) return ELF_TRUE;
	return ELF_FALSE;
}

void elfSetLogFilePath(const char* filePath)
{
	FILE* file;

	file = fopen(filePath, "a");
	if(!file)
	{
		file = fopen(filePath, "w");
		if(!file)
		{
			printf("error: can't open log file \"%s\", reverting to default\n", filePath);
			return;
		}
	}

	if(gen->log) free(gen->log);
	gen->log = (char*)malloc(sizeof(char)*(strlen(filePath)+1));
	memcpy(gen->log, filePath, sizeof(char)*strlen(filePath));
	gen->log[strlen(filePath)] = '\0';
}

