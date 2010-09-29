
elfEngine* elfCreateEngine()
{
	elfEngine* engine;
	gfxVertexData* vertexData;
	float* vertexBuffer;

	engine = (elfEngine*)malloc(sizeof(elfEngine));
	memset(engine, 0x0, sizeof(elfEngine));
	engine->objType = ELF_ENGINE;
	engine->objDestr = elfDestroyEngine;

	engine->fpsTimer = elfCreateTimer();
	engine->fpsLimitTimer = elfCreateTimer();
	engine->timeSyncTimer = elfCreateTimer();

	elfIncRef((elfObject*)engine->fpsTimer);
	elfIncRef((elfObject*)engine->fpsLimitTimer);
	elfIncRef((elfObject*)engine->timeSyncTimer);

	engine->freeRun = ELF_TRUE;
	engine->fpsLimit = 0;
	engine->speed = 1.0;
	engine->f10Exit = ELF_TRUE;

	engine->shadowMapSize = 1024;
	engine->shadowMap = gfxCreate_2dTexture(1024, 1024, 0.0, GFX_CLAMP, GFX_LINEAR, GFX_DEPTH_COMPONENT, GFX_DEPTH_COMPONENT, GFX_UBYTE, NULL);
	engine->shadowTarget = gfxCreateRenderTarget(1024, 1024);
	gfxSetRenderTargetDepthTexture(engine->shadowTarget, engine->shadowMap);
	engine->textureAnisotropy = 1.0;
	engine->occlusionCulling = ELF_FALSE;

	engine->lines = gfxCreateVertexData(512, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
	gfxIncRef((gfxObject*)engine->lines);

	engine->spriteVertexArray = gfxCreateVertexArray(GFX_FALSE);
	gfxIncRef((gfxObject*)engine->spriteVertexArray);

	vertexData = gfxCreateVertexData(36, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);

	vertexBuffer = (float*)gfxGetVertexDataBuffer(vertexData);

	vertexBuffer[0] = -0.5;
	vertexBuffer[1] = 0.5;
	vertexBuffer[2] = 0.0;
	vertexBuffer[3] = -0.5;
	vertexBuffer[4] = -0.5;
	vertexBuffer[5] = 0.0;
	vertexBuffer[6] = 0.5;
	vertexBuffer[7] = -0.5;
	vertexBuffer[8] = 0.0;

	vertexBuffer[9] = -0.5;
	vertexBuffer[10] = 0.5;
	vertexBuffer[11] = 0.0;
	vertexBuffer[12] = 0.5;
	vertexBuffer[13] = -0.5;
	vertexBuffer[14] = 0.0;
	vertexBuffer[15] = 0.5;
	vertexBuffer[16] = 0.5;
	vertexBuffer[17] = 0.0;

	vertexBuffer[18] = 0.5;
	vertexBuffer[19] = 0.5;
	vertexBuffer[20] = 0.0;
	vertexBuffer[21] = 0.5;
	vertexBuffer[22] = -0.5;
	vertexBuffer[23] = 0.0;
	vertexBuffer[24] = -0.5;
	vertexBuffer[25] = -0.5;
	vertexBuffer[26] = 0.0;

	vertexBuffer[27] = 0.5;
	vertexBuffer[28] = 0.5;
	vertexBuffer[29] = 0.0;
	vertexBuffer[30] = -0.5;
	vertexBuffer[31] = -0.5;
	vertexBuffer[32] = 0.0;
	vertexBuffer[33] = -0.5;
	vertexBuffer[34] = 0.5;
	vertexBuffer[35] = 0.0;

	gfxSetVertexArrayData(engine->spriteVertexArray, GFX_VERTEX, vertexData);

	vertexData = gfxCreateVertexData(24, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);

	vertexBuffer = (float*)gfxGetVertexDataBuffer(vertexData);

	vertexBuffer[0] = 0.0;
	vertexBuffer[1] = 1.0;
	vertexBuffer[2] = 0.0;
	vertexBuffer[3] = 0.0;
	vertexBuffer[4] = 1.0;
	vertexBuffer[5] = 0.0;

	vertexBuffer[6] = 0.0;
	vertexBuffer[7] = 1.0;
	vertexBuffer[8] = 1.0;
	vertexBuffer[9] = 0.0;
	vertexBuffer[10] = 1.0;
	vertexBuffer[11] = 1.0;

	vertexBuffer[12] = 0.0;
	vertexBuffer[13] = 1.0;
	vertexBuffer[14] = 0.0;
	vertexBuffer[15] = 0.0;
	vertexBuffer[16] = 1.0;
	vertexBuffer[17] = 0.0;

	vertexBuffer[18] = 0.0;
	vertexBuffer[19] = 1.0;
	vertexBuffer[20] = 1.0;
	vertexBuffer[21] = 0.0;
	vertexBuffer[22] = 1.0;
	vertexBuffer[23] = 1.0;

	gfxSetVertexArrayData(engine->spriteVertexArray, GFX_TEX_COORD, vertexData);

	vertexData = gfxCreateVertexData(36, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);

	vertexBuffer = (float*)gfxGetVertexDataBuffer(vertexData);

	vertexBuffer[0] = 0.0;
	vertexBuffer[1] = 0.0;
	vertexBuffer[2] = 1.0;
	vertexBuffer[3] = 0.0;
	vertexBuffer[4] = 0.0;
	vertexBuffer[5] = 1.0;
	vertexBuffer[6] = 0.0;
	vertexBuffer[7] = 0.0;
	vertexBuffer[8] = 1.0;

	vertexBuffer[9] = 0.0;
	vertexBuffer[10] = 0.0;
	vertexBuffer[11] = 1.0;
	vertexBuffer[12] = 0.0;
	vertexBuffer[13] = 0.0;
	vertexBuffer[14] = 1.0;
	vertexBuffer[15] = 0.0;
	vertexBuffer[16] = 0.0;
	vertexBuffer[17] = 1.0;

	vertexBuffer[18] = 0.0;
	vertexBuffer[19] = 0.0;
	vertexBuffer[20] = -1.0;
	vertexBuffer[21] = 0.0;
	vertexBuffer[22] = 0.0;
	vertexBuffer[23] = -1.0;
	vertexBuffer[24] = 0.0;
	vertexBuffer[25] = 0.0;
	vertexBuffer[26] = -1.0;

	vertexBuffer[27] = 0.0;
	vertexBuffer[28] = 0.0;
	vertexBuffer[29] = -1.0;
	vertexBuffer[30] = 0.0;
	vertexBuffer[31] = 0.0;
	vertexBuffer[32] = -1.0;
	vertexBuffer[33] = 0.0;
	vertexBuffer[34] = 0.0;
	vertexBuffer[35] = -1.0;

	gfxSetVertexArrayData(engine->spriteVertexArray, GFX_NORMAL, vertexData);

	elfIncObj(ELF_ENGINE);

	return engine;
}

void elfDestroyEngine(void* data)
{
	elfEngine* engine = (elfEngine*)data;

	gfxDecRef((gfxObject*)engine->lines);
	gfxDecRef((gfxObject*)engine->spriteVertexArray);

	if(engine->scene) elfDecRef((elfObject*)engine->scene);
	if(engine->gui) elfDecRef((elfObject*)engine->gui);

	if(engine->postProcess) elfDestroyPostProcess(engine->postProcess);
	gfxDestroyRenderTarget(engine->shadowTarget);
	gfxDestroyTexture(engine->shadowMap);

	elfDecRef((elfObject*)engine->fpsTimer);
	elfDecRef((elfObject*)engine->fpsLimitTimer);
	elfDecRef((elfObject*)engine->timeSyncTimer);

	free(engine);

	elfDecObj(ELF_ENGINE);
}

unsigned char elfInitEngine()
{
	if(eng)
	{
		elfSetError(ELF_CANT_INITIALIZE, "error: can't initialize the engine twice!\n");
		return ELF_FALSE;
	}

	eng = elfCreateEngine();
	if(!eng) return ELF_FALSE;
	elfIncRef((elfObject*)eng);

#ifdef ELF_WINDOWS
	GetCurrentDirectoryA(255, eng->cwd);
#else
	getcwd(eng->cwd, 255);
#endif

	return ELF_TRUE;
}

void elfDeinitEngine()
{
	if(!eng) return;

	elfDecRef((elfObject*)eng);
	eng = NULL;
}

unsigned char elfInit(int width, int height,
	const char* title, int multisamples, unsigned char fullscreen, const char* log)
{
	elfInitGeneral();
	elfSetLogFilePath(log);

	elfStartLog("BlendELF 0.9 Beta\n");

	if(!elfInitContext(width, height, title, multisamples, fullscreen)) return ELF_FALSE;
	if(!gfxInit())
	{
		elfDeinitContext();
		return ELF_FALSE;
	}
	elfInitAudio();
	elfInitEngine();
	elfInitScripting();
	elfInitNetworking();

	return ELF_TRUE;
}

unsigned char elfInitWithConfig(const char* filePath)
{
	elfConfig* config;

	elfInitGeneral();

	if(!(config = elfReadConfig("config.txt")))
		config = elfCreateConfig();

	if(!elfInit(config->windowSize[0], config->windowSize[1], "BlendELF", config->multisamples, !config->fullscreen == ELF_FALSE, config->log))
	{
		elfSetError(ELF_CANT_INITIALIZE, "error: could not initialize engine\n");
		elfDestroyConfig(config);
		return ELF_FALSE;
	}

	elfSetTextureCompress(config->textureCompress);
	elfSetTextureAnisotropy(config->textureAnisotropy);
	elfSetShadowMapSize(config->shadowMapSize);

	if(strlen(config->start) > 0) elfLoadScene(config->start);

	elfDestroyConfig(config);

	return ELF_TRUE;
}

void elfLimitEngineFps()
{
	if(eng->fpsLimit > 0)
	{
		if(elfGetElapsedTime(eng->fpsLimitTimer) > 0.0)
		{
			while(elfGetElapsedTime(eng->fpsLimitTimer) < 1.0/(float)eng->fpsLimit);
			elfStartTimer(eng->fpsLimitTimer);
		}
		else
		{
			elfStartTimer(eng->fpsLimitTimer);
		}
	}
}

void elfUpdateEngine()
{
	elfUpdateAudio();

	if(elfGetElapsedTime(eng->timeSyncTimer) > 0.0)
	{
		if(elfAboutZero(eng->tickRate))
			eng->sync = (eng->sync*4.0+((float)elfGetElapsedTime(eng->timeSyncTimer)*eng->speed))/5.0;
		else eng->sync = eng->tickRate;

		elfStartTimer(eng->timeSyncTimer);

		if(eng->sync > 0.0)
		{
			if(eng->gui) elfUpdateGui(eng->gui, eng->sync);

			if(eng->scene)
			{
				elfUpdateScene(eng->scene, eng->sync);
			}
		}
	}
	else
	{
		elfStartTimer(eng->timeSyncTimer);
	}

	elfUpdateScripting();
}

void elfCountEngineFps()
{
	eng->frames++;

	if(elfGetElapsedTime(eng->fpsTimer) > 0.0)
	{
		if(elfGetElapsedTime(eng->fpsTimer) >= 1.0)
		{
			eng->fps = eng->frames;
			eng->frames = 0;
			elfStartTimer(eng->fpsTimer);
		}
	}
	else
	{
		elfStartTimer(eng->fpsTimer);
	}
}

unsigned char elfRun()
{
	if(!eng || !eng->freeRun) return ELF_FALSE;

	eng->freeRun = ELF_FALSE;

	if((eng->f10Exit && elfGetKeyState(ELF_KEY_F10)) || !elfIsWindowOpened() || eng->quit)
	{
		eng->freeRun = ELF_TRUE;
		return ELF_FALSE;
	}

	gfxResetVerticesDrawn();

	if(eng->postProcess)
	{
		if(elfGetMultisamples() < 1)
		{
			gfxSetRenderTarget(eng->postProcess->mainRt);
			gfxSetRenderTargetColorTexture(eng->postProcess->mainRt, 0, eng->postProcess->mainRtColor[0]);
		}
		gfxClearBuffers(0.0, 0.0, 0.0, 1.0, 1.0);
	}
	else
	{
		gfxClearBuffers(0.0, 0.0, 0.0, 1.0, 1.0);
	}

	if(eng->scene)
	{
		elfScenePreDraw(eng->scene);
		elfDrawScene(eng->scene);
		elfScenePostDraw(eng->scene);
	}

	if(eng->scene && eng->postProcess)
	{
		if(elfGetMultisamples() > 0)
		{
			gfxCopyFrameBuffer(eng->postProcess->mainRtColor[0], 0, 0, 0, 0, elfGetWindowWidth(), elfGetWindowHeight());
			if(eng->postProcess->dof || eng->postProcess->ssao)
				gfxCopyFrameBuffer(eng->postProcess->mainRtDepth, 0, 0, 0, 0, elfGetWindowWidth(), elfGetWindowHeight());
		}
		elfRunPostProcess(eng->postProcess, eng->scene);
	}
	if(eng->scene && eng->debugDraw) elfDrawSceneDebug(eng->scene);
	if(eng->gui) elfDrawGui(eng->gui);

	elfSwapBuffers();

	elfLimitEngineFps();
	elfUpdateEngine();
	elfCountEngineFps();

	eng->freeRun = ELF_TRUE;

	elfSleep(0.001);

	return ELF_TRUE;
}

void elfDeinit()
{
	elfDeinitNetworking();
	elfDeinitScripting();
	elfDeinitEngine();
	elfDeinitAudio();
	gfxDeinit();
	elfDeinitContext();
	elfDeinitGeneral();
}

void elfResizeWindow(int width, int height)
{
	elfSetError(ELF_MISSING_FEATURE, "error: resizing not yet in a usable state\n");

	/*if(width <= 0 || height <= 0 || (width == elfGetWindowWidth() &&
		height == elfGetWindowHeight())) return;

	elfResizeContext(width, height);
	elfInitPostProcessBuffers(eng->postProcess);*/
}

const char* elfGetPlatform()
{
#if defined(ELF_WINDOWS)
	return "windows";
#elif defined(ELF_MACOSX)
	return "macosx";
#else
	return "linux";
#endif
}

int elfGetVersionMajor()
{
	return 0;
}

int elfGetVersionMinor()
{
	return 9;
}

const char* elfGetVersionRelease()
{
	return "Beta 2";
}

const char* elfGetVersion()
{
	return "BlendELF 0.9 Beta 2";
}

char* elfGetDirectoryFromPath(const char* filePath)
{
	int idx;

	if(strlen(filePath) < 1) return elfCreateString("");

	idx = elfRfindCharsFromString(filePath, "/\\");
	if(idx < 1)
	{
		return elfCreateString("");
	}
	else
	{
		return elfSubString((char*)filePath, 0, idx+1);
	}
}

const char* elfGetCurrentDirectory()
{
	return eng->cwd;
}

const char* elfGetErrorString()
{
	return gen->errStr;
}

int elfGetError()
{
	return gen->errCode;
}

void elfQuit()
{
	eng->quit = ELF_TRUE;
}

void elfSetF10Exit(unsigned char exit)
{
	eng->f10Exit = !(exit == ELF_FALSE);
}

unsigned char elfGetF10Exit()
{
	return eng->f10Exit;
}

elfScene* elfLoadScene(const char* filePath)
{
	elfScene* scene;

	scene = elfCreateSceneFromFile(filePath);
	if(scene)
	{
		if(eng->scene) elfDecRef((elfObject*)eng->scene);
		eng->scene = scene;
		elfIncRef((elfObject*)eng->scene);
	}

	return scene;
}

void elfSetScene(elfScene* scene)
{
	if(eng->scene) elfDecRef((elfObject*)eng->scene);
	eng->scene = scene;
	if(eng->scene) elfIncRef((elfObject*)eng->scene);
}

elfScene* elfGetScene()
{
	return eng->scene;
}

void elfSetGui(elfGui* gui)
{
	if(eng->gui) elfDecRef((elfObject*)eng->gui);
	eng->gui = gui;
	if(eng->gui) elfIncRef((elfObject*)eng->gui);
}

elfGui* elfGetGui()
{
	return eng->gui;
}

float elfGetSync()
{
	return eng->sync;
}

int elfGetFps()
{
	return eng->fps;
}

void elfSetFpsLimit(int fpsLimit)
{
	eng->fpsLimit = fpsLimit;
	if(eng->fpsLimit < 0) eng->fpsLimit = 0;
}

int elfGetFpsLimit()
{
	return eng->fpsLimit;
}

void elfSetTickRate(float tickRate)
{
	eng->tickRate = tickRate;
	if(eng->tickRate < 0.0) eng->tickRate = 0.0;
}

float elfGetTickRate()
{
	return eng->tickRate;
}

void elfSetSpeed(float speed)
{
	eng->speed = speed;
	if(eng->speed < 0.0001) eng->speed = 0.0001;
}

float elfGetSpeed()
{
	return eng->speed;
}

unsigned char elfSaveScreenShot(const char* filePath)
{
	unsigned char* data;

	data = (unsigned char*)malloc(sizeof(unsigned char)*elfGetWindowWidth()*elfGetWindowHeight()*4);

	gfxReadPixels(0, 0, elfGetWindowWidth(), elfGetWindowHeight(), GFX_BGRA, GFX_UBYTE, data);

	if(!elfSaveImageData(filePath, elfGetWindowWidth(), elfGetWindowHeight(), 32, data))
	{
		free(data);
		return ELF_FALSE;
	}

	free(data);

	return ELF_TRUE;
}

void elfSetTextureCompress(unsigned char compress)
{
	eng->textureCompress = !compress == ELF_FALSE;
}

unsigned char elfGetTextureCompress()
{
	return eng->textureCompress;
}

void elfSetTextureAnisotropy(float anisotropy)
{
	eng->textureAnisotropy = anisotropy;
}

float elfGetTextureAnisotropy()
{
	return eng->textureAnisotropy;
}

void elfSetShadowMapSize(int size)
{
	// why would someone want a shadow map of 1 pixel?...
	if(size < 1) return;

	gfxDestroyRenderTarget(eng->shadowTarget);
	gfxDestroyTexture(eng->shadowMap);

	eng->shadowMapSize = size;
	eng->shadowMap = gfxCreate_2dTexture(size, size, 0.0f, GFX_CLAMP, GFX_LINEAR, GFX_DEPTH_COMPONENT, GFX_DEPTH_COMPONENT, GFX_UBYTE, NULL);
	eng->shadowTarget = gfxCreateRenderTarget(size, size);
	gfxSetRenderTargetDepthTexture(eng->shadowTarget, eng->shadowMap);
}

int elfGetShadowMapSize()
{
	return eng->shadowMapSize;
}

int elfGetPolygonsRendered()
{
	return gfxGetVerticesDrawn(GFX_TRIANGLES)/3+gfxGetVerticesDrawn(GFX_TRIANGLE_STRIP)/3;
}

void elfSetFog(float start, float end, float r, float g, float b)
{
	eng->fog = ELF_TRUE;
	eng->fogStart = start;
	eng->fogEnd = end;
	eng->fogColor.r = r;
	eng->fogColor.g = g;
	eng->fogColor.b = b;
}

void elfDisableFog()
{
	eng->fog = ELF_FALSE;
}

float elfGetFogStart()
{
	return eng->fogStart;
}

float elfGetFogEnd()
{
	return eng->fogEnd;
}

elfColor elfGetFogColor()
{
	return eng->fogColor;
}

void elfSetBloom(float threshold)
{
	if(gfxGetVersion() < 200) return;

	if(!eng->postProcess) eng->postProcess = elfCreatePostProcess();
	elfSetPostProcessBloom(eng->postProcess, threshold);
}

void elfDisableBloom()
{
	if(eng->postProcess)
	{
		elfDisablePostProcessBloom(eng->postProcess);
		if(!elfIsPostProcessBloom(eng->postProcess) &&
			!elfIsPostProcessSsao(eng->postProcess) &&
			!elfIsPostProcessDof(eng->postProcess) &&
			!elfIsPostProcessLightShafts(eng->postProcess))
		{
			elfDestroyPostProcess(eng->postProcess);
			eng->postProcess = NULL;
		}
	}
}

float elfGetBloomThreshold()
{
	if(!eng->postProcess) return ELF_FALSE;
	return elfGetPostProcessBloomThreshold(eng->postProcess);
}

void elfSetDof(float focalRange, float focalDistance)
{
	if(gfxGetVersion() < 200) return;

	if(!eng->postProcess) eng->postProcess = elfCreatePostProcess();
	elfSetPostProcessDof(eng->postProcess, focalRange, focalDistance);
}

void elfDisableDof()
{
	if(eng->postProcess)
	{
		elfDisablePostProcessDof(eng->postProcess);
		if(!elfIsPostProcessBloom(eng->postProcess) &&
			!elfIsPostProcessSsao(eng->postProcess) &&
			!elfIsPostProcessDof(eng->postProcess) &&
			!elfIsPostProcessLightShafts(eng->postProcess))
		{
			elfDestroyPostProcess(eng->postProcess);
			eng->postProcess = NULL;
		}
	}
}

float elfGetDofFocalRange()
{
	if(!eng->postProcess) return ELF_FALSE;
	return elfGetPostProcessDofFocalRange(eng->postProcess);
}

float elfGetDofFocalDistance()
{
	if(!eng->postProcess) return ELF_FALSE;
	return elfGetPostProcessDofFocalDistance(eng->postProcess);
}

void elfSetSsao(float amount)
{
	if(gfxGetVersion() < 200) return;

	if(!eng->postProcess) eng->postProcess = elfCreatePostProcess();
	elfSetPostProcessSsao(eng->postProcess, amount);
}

void elfDisableSsao()
{
	if(eng->postProcess)
	{
		elfDisablePostProcessSsao(eng->postProcess);
		if(!elfIsPostProcessBloom(eng->postProcess) &&
			!elfIsPostProcessSsao(eng->postProcess) &&
			!elfIsPostProcessDof(eng->postProcess) &&
			!elfIsPostProcessLightShafts(eng->postProcess))
		{
			elfDestroyPostProcess(eng->postProcess);
			eng->postProcess = NULL;
		}
	}
}

float elfGetSsaoAmount()
{
	if(eng->postProcess) return elfGetPostProcessSsaoAmount(eng->postProcess);
	return 0.0;
}

void elfSetLightShafts(float intensity)
{
	if(gfxGetVersion() < 200) return;

	if(!eng->postProcess) eng->postProcess = elfCreatePostProcess();
	elfSetPostProcessLightShafts(eng->postProcess, intensity);
}

void elfDisableLightShafts()
{
	if(eng->postProcess)
	{
		elfDisablePostProcessLightShafts(eng->postProcess);
		if(!elfIsPostProcessBloom(eng->postProcess) &&
			!elfIsPostProcessSsao(eng->postProcess) &&
			!elfIsPostProcessDof(eng->postProcess) &&
			!elfIsPostProcessLightShafts(eng->postProcess))
		{
			elfDestroyPostProcess(eng->postProcess);
			eng->postProcess = NULL;
		}
	}
}

float elfGetLightShaftsIntensity()
{
	if(eng->postProcess) return elfGetPostProcessLightShaftsIntensity(eng->postProcess);
	return 0.0;
}

unsigned char elfIsFog()
{
	return eng->fog;
}

unsigned char elfIsBloom()
{
	if(eng->postProcess) return elfIsPostProcessBloom(eng->postProcess);
	return ELF_FALSE;
}

unsigned char elfIsSsao()
{
	if(eng->postProcess) return elfIsPostProcessSsao(eng->postProcess);
	return ELF_FALSE;
}

unsigned char elfIsDof()
{
	if(eng->postProcess) return elfIsPostProcessDof(eng->postProcess);
	return ELF_FALSE;
}

unsigned char elfIsLightShafts()
{
	if(eng->postProcess) return elfIsPostProcessLightShafts(eng->postProcess);
	return ELF_FALSE;
}

void elfSetOcclusionCulling(unsigned char cull)
{
	eng->occlusionCulling = !cull == ELF_FALSE;
}

unsigned char elfIsOcclusionCulling()
{
	return eng->occlusionCulling;
}

void elfSetDebugDraw(unsigned char debugDraw)
{
	eng->debugDraw = !debugDraw == ELF_FALSE;
}

unsigned char elfIsDebugDraw()
{
	return eng->debugDraw;
}

elfObject* elfGetActor()
{
	return eng->actor;
}

elfDirectoryItem* elfCreateDirectoryItem()
{
	elfDirectoryItem* dirItem;

	dirItem = (elfDirectoryItem*)malloc(sizeof(elfDirectoryItem));
	memset(dirItem, 0x0, sizeof(elfDirectoryItem));
	dirItem->objType = ELF_DIRECTORY_ITEM;
	dirItem->objDestr = elfDestroyDirectoryItem;

	elfIncObj(ELF_DIRECTORY_ITEM);

	return dirItem;
}

void elfDestroyDirectoryItem(void* data)
{
	elfDirectoryItem* directoryItem = (elfDirectoryItem*)data;

	if(directoryItem->name) elfDestroyString(directoryItem->name);

	free(directoryItem);

	elfDecObj(ELF_DIRECTORY_ITEM);
}

elfDirectory* elfCreateDirectory()
{
	elfDirectory* directory;

	directory = (elfDirectory*)malloc(sizeof(elfDirectory));
	memset(directory, 0x0, sizeof(elfDirectory));
	directory->objType = ELF_DIRECTORY;
	directory->objDestr = elfDestroyDirectory;

	directory->items = elfCreateList();

	elfIncObj(ELF_DIRECTORY);

	return directory;
}

void elfDestroyDirectory(void* data)
{
	elfDirectory* directory = (elfDirectory*)data;

	if(directory->path) elfDestroyString(directory->path);
	elfDestroyList(directory->items);

	free(directory);

	elfDecObj(ELF_DIRECTORY);
}

void elfAppendFolderToDirectoryItemList(elfList* items, elfDirectoryItem* nitem)
{
	elfDirectoryItem* dirItem;
	int i;

	for(i = 0, dirItem = (elfDirectoryItem*)elfBeginList(items); dirItem;
		dirItem = (elfDirectoryItem*)elfNextInList(items), i++)
	{
		if(dirItem->itemType == ELF_FILE)
		{
			elfInsertToList(items, i, (elfObject*)nitem);
			return;
		}
		else continue;
	}

	elfAppendToList(items, (elfObject*)nitem);
}

typedef struct elfDirItemEmul {
	char* str;
	int type;
} elfDirItemEmul;

static int alphacmp(const void* a, const void* b)
{
	return strcmp((*((elfDirItemEmul*)a)).str, (*((elfDirItemEmul*)b)).str);
}

elfDirectory* elfReadDirectory(const char* path)
{
	elfDirectory* directory;
	elfDirectoryItem* dirItem;
	DIR* dir;
	struct dirent* dp;
	elfDirItemEmul* names;
	int itemCount;
	int i;

	if(!(dir = opendir(path)))
	{
		elfSetError(ELF_CANT_OPEN_DIRECTORY, "error: could not open directory \"%s\"\n", path);
		return NULL;
	}
	else
	{
		directory = elfCreateDirectory();
		directory->path = elfCreateString(path);

		while((dp = readdir(dir)))
		{
			dirItem = elfCreateDirectoryItem();
			dirItem->name = elfCreateString(dp->d_name);

#ifdef ELF_WINDOWS
			if(dp->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) dirItem->itemType = ELF_DIR;
			else dirItem->itemType = ELF_FILE;
#else
			if(dp->d_type == 4) dirItem->itemType = ELF_DIR;
			else dirItem->itemType = ELF_FILE;
#endif

			elfAppendToList(directory->items, (elfObject*)dirItem);
		}

		itemCount = elfGetListLength(directory->items);

		names = (elfDirItemEmul*)malloc(sizeof(elfDirItemEmul)*itemCount);
		memset(names, 0x0, sizeof(elfDirItemEmul)*itemCount);

		for(i = 0, dirItem = (elfDirectoryItem*)elfBeginList(directory->items); dirItem;
			dirItem = (elfDirectoryItem*)elfNextInList(directory->items), i++)
		{
			names[i].str = (char*)malloc(sizeof(char)*(strlen(dirItem->name)+1));
			memcpy(names[i].str, dirItem->name, sizeof(char)*(strlen(dirItem->name)+1));
			names[i].type = dirItem->itemType;
		}

		qsort(names, itemCount, sizeof(elfDirItemEmul), alphacmp);

		elfDestroyDirectory(directory);

		directory = elfCreateDirectory();
		directory->path = elfCreateString(path);

		for(i = 0; i < itemCount; i++)
		{
			dirItem = elfCreateDirectoryItem();
			dirItem->name = elfCreateString(names[i].str);
			dirItem->itemType = names[i].type;

			if(dirItem->itemType == ELF_DIR)
				elfAppendFolderToDirectoryItemList(directory->items, dirItem);
			else elfAppendToList(directory->items, (elfObject*)dirItem);

			free(names[i].str);
		}

		free(names);

		return directory;
	}
}

const char* elfGetDirectoryPath(elfDirectory* directory)
{
	return directory->path;
}

int elfGetDirectoryItemCount(elfDirectory* directory)
{
	return elfGetListLength(directory->items);
}

elfDirectoryItem* elfGetDirectoryItem(elfDirectory* directory, int idx)
{
	int i;
	elfDirectoryItem* dirItem;

	if(idx < 0 || idx > elfGetListLength(directory->items)-1) return NULL;

	for(i = 0, dirItem = (elfDirectoryItem*)elfBeginList(directory->items); dirItem;
		dirItem = (elfDirectoryItem*)elfNextInList(directory->items), i++)
	{
		if(i == idx) return dirItem;
	}

	return NULL;
}

const char* elfGetDirectoryItemName(elfDirectoryItem* dirItem)
{
	return dirItem->name;
}

int elfGetDirectoryItemType(elfDirectoryItem* dirItem)
{
	return dirItem->itemType;
}

elfVec3f elfCreateVec3f()
{
	elfVec3f result;
	memset(&result, 0x0, sizeof(elfVec3f));
	return result;
}

elfVec3f elfCreateVec3fFromValues(float x, float y, float z)
{
	elfVec3f result;
	memset(&result, 0x0, sizeof(elfVec3f));

	result.x = x;
	result.y = y;
	result.z = z;

	return result;
}

elfVec4f elfCreateQua()
{
	elfVec4f result;
	memset(&result, 0x0, sizeof(elfVec4f));
	return result;
}

elfVec4f elfCreateQuaFromEuler(float x, float y, float z)
{
	elfVec4f result;
	memset(&result, 0x0, sizeof(elfVec4f));

	gfxQuaFromEuler(x, y, z, &result.x);

	return result;
}

elfVec4f elfCreateQuaFromAngleAxis(float angle, float x, float y, float z)
{
	elfVec4f qua;
	float axis[3];

	axis[0] = x; axis[1] = y; axis[2] = z;
	gfxQuaFromAngleAxis(angle, axis, &qua.x);

	return qua;
}

elfVec3f elfMulQuaVec3f(elfVec4f qua, elfVec3f vec)
{
	elfVec3f result;

	gfxMulQuaVec(&qua.x, &vec.x, &result.x);

	return result;
}

elfVec4f elfMulQuaQua(elfVec4f qua1, elfVec4f qua2)
{
	elfVec4f result;

	gfxMulQuaQua(&qua1.x, &qua2.x, &result.x);

	return result;
}

elfVec4f elfGetQuaInverted(elfVec4f qua)
{
	elfVec4f result;

	gfxQuaGetInverse(&qua.x, &result.x);

	return result;
}

elfVec3f elfRotateVec3f(elfVec3f vec, float x, float y, float z)
{
	elfVec4f qua;
	elfVec3f result;

	gfxQuaFromEuler(x, y, z, &qua.x);

	gfxMulQuaVec(&qua.x, &vec.x, &result.x);

	return result;
}

elfVec3f elfSubVec3fVec3f(elfVec3f vec1, elfVec3f vec2)
{
	elfVec3f result;
	result.x = vec1.x-vec2.x;
	result.y = vec1.y-vec2.y;
	result.z = vec1.z-vec2.z;
	return result;
}

elfVec3f elfAddVec3fVec3f(elfVec3f vec1, elfVec3f vec2)
{
	elfVec3f result;
	result.x = vec1.x+vec2.x;
	result.y = vec1.y+vec2.y;
	result.z = vec1.z+vec2.z;
	return result;
}

float elfGetVec3fLength(elfVec3f vec)
{
	return gfxVecLength(&vec.x);
}

unsigned char elfAboutZero(float val)
{
	if(val < 0.0001 && val > -0.0001) return ELF_TRUE;
	return ELF_FALSE;
}

float elfFloatAbs(float val)
{
	if(val < 0.0) return -val;
	return val;
}

float elfFloatMin(float a, float b)
{
	if(a < b) return a;
	return b;
}

float elfFloatMax(float a, float b)
{
	if(a > b) return a;
	return b;
}

float elfRandomFloat()
{
	return (float)rand()/(float)RAND_MAX;
}

float elfRandomFloatRange(float min, float max)
{
	return min+(max-min)*elfRandomFloat();
}

int elfRandomInt()
{
	return rand();
}

int elfRandomIntRange(int min, int max)
{
	return (int)(((float)(min+(max-min)))*elfRandomFloat());
}

