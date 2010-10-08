
elfConfig* elfCreateConfig()
{
	elfConfig* config;

	config = (elfConfig*)malloc(sizeof(elfConfig));
	memset(config, 0x0, sizeof(elfConfig));
	config->objType = ELF_CONFIG;
	config->objDestr = elfDestroyConfig;

	config->windowSize[0] = 1024;
	config->windowSize[1] = 768;
	config->multisamples = 0;
	config->fullscreen = ELF_FALSE;
	config->textureCompress = ELF_FALSE;
	config->textureAnisotropy = 1.0f;
	config->shadowMapSize = 1024;
	config->start = elfCreateString("");
	config->log = elfCreateString("elf.log");

	elfIncObj(ELF_CONFIG);

	return config;
}

void elfDestroyConfig(void* data)
{
	elfConfig* config = (elfConfig*)data;

	if(config->start) elfDestroyString(config->start);
	if(config->log) elfDestroyString(config->log);

	free(config);

	elfDecObj(ELF_CONFIG);
}

ELF_API elfConfig* ELF_APIENTRY elfReadConfig(const char* filePath)
{
	elfConfig* config;
	FILE* file;
	int length;
	char* text;
	int pos;
	char* str;
	int scope;

	file = fopen(filePath, "r");
	if(!file) return NULL;

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	if(length > 0)
	{
		text = (char*)malloc(sizeof(char)*length+1);
		memset(text, 0x0, sizeof(char)*length+1);
		fread(text, sizeof(char), length, file);
		fclose(file);
	}
	else
	{
		fclose(file);
		return NULL;
	}

	config = elfCreateConfig();

	pos = 0;
	scope = 0;
	while((str = elfReadNext(text, &pos)))
	{
		if(scope > 0)
		{
			if(!strcmp(str, "{"))
			{
				scope++;
			}
			else if(!strcmp(str, "}"))
			{
				scope--;
			}
		}
		else
		{
			if(!strcmp(str, "windowSize"))
			{
				elfReadSstInts(text, &pos, 2, config->windowSize);
			}
			else if(!strcmp(str, "multisamples"))
			{
				config->multisamples = elfReadSstInt(text, &pos);
			}
			else if(!strcmp(str, "fullscreen"))
			{
				config->fullscreen = elfReadSstBool(text, &pos);
			}
			else if(!strcmp(str, "textureCompress"))
			{
				config->textureCompress = elfReadSstBool(text, &pos);
			}
			else if(!strcmp(str, "textureAnisotropy"))
			{
				config->textureAnisotropy = elfReadSstFloat(text, &pos);
			}
			else if(!strcmp(str, "shadowMapSize"))
			{
				config->shadowMapSize = elfReadSstInt(text, &pos);
			}
			else if(!strcmp(str, "start"))
			{
				if(config->start) elfDestroyString(config->start);
				config->start = elfReadSstString(text, &pos);
			}
			else if(!strcmp(str, "log"))
			{
				if(config->log) elfDestroyString(config->log);
				config->log = elfReadSstString(text, &pos);
			}
			else if(!strcmp(str, "{"))
			{
				scope++;
			}
			else if(!strcmp(str, "}"))
			{
				scope--;
				if(scope < 0)
				{
					elfDestroyString(str);
					break;
				}
			}
			else
			{
				printf("warning: unknown element \"%s\" in config.txt\n", str);
			}
		}
		elfDestroyString(str);
		str = NULL;
	}

	free(text);

	return config;
}

ELF_API int ELF_APIENTRY elfGetConfigWindowWidth(elfConfig* config)
{
	return config->windowSize[0];
}

ELF_API int ELF_APIENTRY elfGetConfigWindowHeight(elfConfig* config)
{
	return config->windowSize[1];
}

ELF_API int ELF_APIENTRY elfGetConfigMultisamples(elfConfig* config)
{
	return config->multisamples;
}

ELF_API unsigned char ELF_APIENTRY elfGetConfigFullscreen(elfConfig* config)
{
	return !config->fullscreen == ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfGetConfigTextureCompress(elfConfig* config)
{
	return config->textureCompress;
}

ELF_API float ELF_APIENTRY elfGetConfigTextureAnisotropy(elfConfig* config)
{
	return config->textureAnisotropy;
}

ELF_API int ELF_APIENTRY elfGetConfigShadowMapSize(elfConfig* config)
{
	return config->shadowMapSize;
}

ELF_API const char* ELF_APIENTRY elfGetConfigStart(elfConfig* config)
{
	return config->start;
}

ELF_API const char* ELF_APIENTRY elfGetConfigLog(elfConfig* config)
{
	return config->start;
}

