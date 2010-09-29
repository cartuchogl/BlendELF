
void elfInitGeneral()
{
	if(gen) return;

	gen = (elfGeneral*)malloc(sizeof(elfGeneral));
	memset(gen, 0x0, sizeof(elfGeneral));
	gen->objType = ELF_GENERAL;

	gen->log = elfCreateString("elf.log");

}

void elfDeinitGeneral()
{
	if(!gen) return;

	if(gen->errStr) elfDestroyString(gen->errStr);

	if(gen->refCount > 0)
	{
		elfWriteToLog("error: possible memory leak in ELF, [%d] references not dereferenced\n",
			elfGetGlobalRefCount());
		elfDumpRefTable();
	}

	if(gen->refCount < 0)
	{
		elfWriteToLog("error: possible double free in ELF, [%d] negative reference count\n",
			elfGetGlobalRefCount());
		elfDumpRefTable();
	}

	if(gen->objCount > 1)
	{
		elfWriteToLog("error: possible memory leak in ELF, [%d] objects not destroyed\n",
			elfGetGlobalObjCount()-1);
		elfDumpObjTable();
	}

	if(gen->objCount < 1)
	{
		elfWriteToLog("error: possible double free in ELF, [%d] negative object count\n",
			elfGetGlobalObjCount()-1);
		elfDumpObjTable();
	}

	if(gen->log) elfDestroyString(gen->log);

	free(gen);
}

void elfIncRef(elfObject* obj)
{
	gen->refCount++;
	gen->refTable[obj->objType]++;
	obj->objRefCount++;
}

void elfDecRef(elfObject* obj)
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
			elfWriteToLog("error: no destructor specified for object\n");
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

	elfWriteToLog("---------- REF COUNT TABLE ----------\n");

	for(i = 0; i < ELF_OBJECT_TYPE_COUNT; i++)
	{
		elfWriteToLog("%d : %d\n", i, gen->refTable[i]);
	}

	elfWriteToLog("-------------------------------------\n");
}

void elfDumpObjTable()
{
	int i;

	elfWriteToLog("---------- OBJ COUNT TABLE ----------\n");

	for(i = 0; i < ELF_OBJECT_TYPE_COUNT; i++)
	{
		elfWriteToLog("%d : %d\n", i, gen->objTable[i]);
	}

	elfWriteToLog("-------------------------------------\n");
}

int elfGetObjectType(elfObject* obj)
{
	return obj->objType;
}

int elfGetObjectRefCount(elfObject* obj)
{
	return obj->objRefCount;
}

int elfGetGlobalRefCount()
{
	return gen->refCount;
}

int elfGetGlobalObjCount()
{
	return gen->objCount;
}

unsigned char elfIsActor(elfObject* obj)
{
	if(obj->objType == ELF_CAMERA || obj->objType == ELF_ENTITY ||
		obj->objType == ELF_LIGHT || obj->objType == ELF_PARTICLES ||
		obj->objType == ELF_SPRITE) return ELF_TRUE;
	return ELF_FALSE;
}

unsigned char elfIsGuiObject(elfObject* obj)
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

	if(gen->log) elfDestroyString(gen->log);
	gen->log = elfCreateString(filePath);
}

