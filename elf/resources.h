
elfResources* elfCreateResources()
{
	elfResources* resources;

	resources = (elfResources*)malloc(sizeof(elfResources));
	memset(resources, 0x0, sizeof(elfResources));
	resources->objType = ELF_RESOURCES;
	resources->objDestr = elfDestroyResources;

	resources->textures = elfCreateList();
	elfIncRef((elfObject*)resources->textures);

	return resources;
}

void elfDestroyResources(void *data)
{
	elfResources* resources = (elfResources*)data;

	elfDecRef((elfObject*)resources->textures);

	free(resources);
}

unsigned char elfInitResources()
{
	if(res)
	{
		elfSetError(ELF_CANT_INITIALIZE, "error: can't initialize resources twice!\n");
		return ELF_FALSE;
	}

	res = elfCreateResources();
	elfIncRef((elfObject*)res);

	return ELF_TRUE;
}

void elfDeinitResources()
{
	if(res)
	{
		elfDecRef((elfObject*)res);
		res = NULL;
	}
}

ELF_API elfTexture* elfGetResourcesTexture(const char* filePath, const char* name)
{
	elfTexture* tex;

	if(!name || strlen(name) < 1)
	{
		for(tex = (elfTexture*)elfBeginList(res->textures); tex;
			tex = (elfTexture*)elfGetListNext(res->textures))
		{
			if(!strcmp(tex->filePath, filePath)) return tex;
		}
	}
	else
	{
		for(tex = (elfTexture*)elfBeginList(res->textures); tex;
			tex = (elfTexture*)elfGetListNext(res->textures))
		{
			if(!strcmp(tex->filePath, filePath) && !strcmp(tex->name, name)) return tex;
		}
	}

	return NULL;
}

ELF_API elfTexture* elfGetOrLoadResourcesTexture(const char* filePath, const char* name)
{
	elfTexture* texture;

	texture = elfGetResourcesTexture(filePath, name);
	if(!texture)
	{
		texture = elfCreateTextureFromFile(name, filePath);
		if(texture) elfAppendListObject(res->textures, (elfObject*)texture);
	}

	return texture;
}

