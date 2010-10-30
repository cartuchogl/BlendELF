
elfConfig* elfCreateConfig()
{
	elfConfig* config;

	config = (elfConfig*)malloc(sizeof(elfConfig));
	memset(config, 0x0, sizeof(elfConfig));
	config->objType = ELF_CONFIG;
	config->objDestr = elfDestroyConfig;

	config->windowSize.x = 1024;
	config->windowSize.y = 768;

	config->windowTitle = (char*)malloc(sizeof(char)*9);
	memset(config->windowTitle, 0x0, sizeof(char)*9);
	memcpy(config->windowTitle, "BlendELF", sizeof(char)*8);

	config->multisamples = 0;
	config->fullscreen = ELF_FALSE;
	config->textureCompress = ELF_FALSE;
	config->textureAnisotropy = 1.0f;
	config->shadowMapSize = 1024;
	config->fpsLimit = 0.0f;
	config->tickRate = 0.0f;
	config->speed = 1.0f;
	config->f10Exit = ELF_TRUE;

	config->start = (char*)malloc(sizeof(char));
	config->start[0] = '\0';

	config->logPath = (char*)malloc(sizeof(char)*8);
	memset(config->logPath, 0x0, sizeof(char)*8);
	memcpy(config->logPath, "elf.log", sizeof(char)*7);

	return config;
}

void elfDestroyConfig(void* data)
{
	elfConfig* config = (elfConfig*)data;

	if(config->windowTitle) free(config->windowTitle);
	if(config->start) free(config->start);
	if(config->logPath) free(config->logPath);

	free(config);
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
	while((str = elfReadSstNext(text, &pos, " \t\n\r")))
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
				elfReadSstInts(text, &pos, 2, &config->windowSize.x);
			}
			else if(!strcmp(str, "windowTitle"))
			{
				if(config->windowTitle) free(config->windowTitle);
				config->windowTitle = elfReadSstText(text, &pos);
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
				if(config->start) free(config->start);
				config->start = elfReadSstString(text, &pos);
			}
			else if(!strcmp(str, "logPath"))
			{
				if(config->logPath) free(config->logPath);
				config->logPath = elfReadSstString(text, &pos);
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
					free(str);
					break;
				}
			}
			else
			{
				printf("warning: unknown element \"%s\" in config.txt\n", str);
			}
		}
		free(str);
		str = NULL;
	}

	free(text);

	return config;
}

ELF_API void elfSetConfigWindowSize(elfConfig* config, int width, int height)
{
	config->windowSize.x = width;
	config->windowSize.y = height;

	if(config->windowSize.x < 1) config->windowSize.x = 1;
	if(config->windowSize.y < 1) config->windowSize.y = 1;
}

ELF_API void ELF_APIENTRY elfSetConfigMultisamples(elfConfig* config, int multisamples)
{
	config->multisamples = multisamples;
	if(config->multisamples < 0) config->multisamples = 0;
}

ELF_API void ELF_APIENTRY elfSetConfigFullscreen(elfConfig* config, unsigned char fullscreen)
{
	config->fullscreen = !fullscreen == ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfSetConfigTextureCompress(elfConfig* config, unsigned char textureCompress)
{
	config->textureCompress = !textureCompress == ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfSetConfigTextureAnisotropy(elfConfig* config, float textureAnisotropy)
{
	config->textureAnisotropy = textureAnisotropy;
	if(config->textureAnisotropy < 1.0f) config->textureAnisotropy = 1.0f;
}

ELF_API void ELF_APIENTRY elfSetConfigShadowMapSize(elfConfig* config, int shadowMapSize)
{
	config->shadowMapSize = shadowMapSize;
	if(config->shadowMapSize < 1) config->shadowMapSize = 1;
}

ELF_API void ELF_APIENTRY elfSetConfigStart(elfConfig* config, const char* start)
{
	if(config->start) free(config->start);
	config->start = malloc(sizeof(char)*(strlen(start)+1));
	memset(config->start, 0x0, sizeof(char)*(strlen(start)+1));
	memcpy(config->start, start, sizeof(char)*strlen(start));
}

ELF_API void ELF_APIENTRY elfSetConfigLogPath(elfConfig* config, const char* logPath)
{
	if(config->logPath) free(config->logPath);
	config->logPath = malloc(sizeof(char)*(strlen(logPath)+1));
	memset(config->logPath, 0x0, sizeof(char)*(strlen(logPath)+1));
	memcpy(config->logPath, logPath, sizeof(char)*strlen(logPath));
}

ELF_API elfVec2i ELF_APIENTRY elfGetConfigWindowSize(elfConfig* config)
{
	return config->windowSize;
}

ELF_API int ELF_APIENTRY elfGetConfigMultisamples(elfConfig* config)
{
	return config->multisamples;
}

ELF_API unsigned char ELF_APIENTRY elfGetConfigFullscreen(elfConfig* config)
{
	return config->fullscreen;
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

ELF_API const char* ELF_APIENTRY elfGetConfigLogPath(elfConfig* config)
{
	return config->logPath;
}

