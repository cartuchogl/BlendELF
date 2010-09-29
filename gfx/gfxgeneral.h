
gfxGeneral* gfxCreateGeneral()
{
	gfxGeneral* general;

	general = (gfxGeneral*)malloc(sizeof(gfxGeneral));
	memset(general, 0x0, sizeof(gfxGeneral));

	return general;
}

void gfxDestroyGeneral(gfxGeneral* general)
{
	free(general);	
}

void gfxDumpRefTable()
{
	int i;

	elfWriteToLog("---------- REF COUNT TABLE ----------\n");

	for(i = 0; i < GFX_OBJECT_TYPE_COUNT; i++)
	{
		elfWriteToLog("%d : %d\n", i, gfxGen->refTable[i]);
	}

	elfWriteToLog("-------------------------------------\n");
}

void gfxDumpObjTable()
{
	int i;

	elfWriteToLog("---------- OBJ COUNT TABLE ----------\n");

	for(i = 0; i < GFX_OBJECT_TYPE_COUNT; i++)
	{
		elfWriteToLog("%d : %d\n", i, gfxGen->objTable[i]);
	}

	elfWriteToLog("-------------------------------------\n");
}

void gfxIncRef(gfxObject* obj)
{
	gfxGen->refCount++;
	gfxGen->refTable[obj->objType]++;
	obj->objRefCount++;
}

void gfxDecRef(gfxObject* obj)
{
	gfxGen->refCount--;
	gfxGen->refTable[obj->objType]--;
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

void gfxIncObj(int type)
{
	gfxGen->objCount++;
	gfxGen->objTable[type]++;
}

void gfxDecObj(int type)
{
	gfxGen->objCount--;
	gfxGen->objTable[type]--;
}

int gfxGetObjectType(gfxObject* obj)
{
	return obj->objType;
}

int gfxGetObjectRefCount(gfxObject* obj)
{
	return obj->objRefCount;
}

int gfxGetGlobalRefCount()
{
	return gfxGen->refCount;
}

int gfxGetGlobalObjCount()
{
	return gfxGen->objCount;
}

