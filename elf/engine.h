
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
	engine->shadowMap = gfxCreate2dTexture(1024, 1024, 0.0, GFX_CLAMP, GFX_LINEAR, GFX_DEPTH_COMPONENT, GFX_DEPTH_COMPONENT, GFX_UBYTE, NULL);
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

ELF_API unsigned char ELF_APIENTRY elfInit(int width, int height, const char* title, int multisamples, unsigned char fullscreen, const char* log)
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

	return ELF_TRUE;
}

ELF_API unsigned char ELF_APIENTRY elfInitWithConfig(const char* filePath)
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
			eng->sync = (eng->sync*2.0+((float)elfGetElapsedTime(eng->timeSyncTimer)*eng->speed))/3.0;
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

ELF_API unsigned char ELF_APIENTRY elfRun()
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

ELF_API void ELF_APIENTRY elfDeinit()
{
	elfDeinitScripting();
	elfDeinitEngine();
	elfDeinitAudio();
	gfxDeinit();
	elfDeinitContext();
	elfDeinitGeneral();
}

ELF_API void ELF_APIENTRY elfResizeWindow(int width, int height)
{
	elfSetError(ELF_MISSING_FEATURE, "error: resizing not yet in a usable state\n");

	/*if(width <= 0 || height <= 0 || (width == elfGetWindowWidth() &&
		height == elfGetWindowHeight())) return;

	elfResizeContext(width, height);
	elfInitPostProcessBuffers(eng->postProcess);*/
}

ELF_API const char* ELF_APIENTRY elfGetPlatform()
{
#if defined(ELF_WINDOWS)
	return "windows";
#elif defined(ELF_MACOSX)
	return "macosx";
#else
	return "linux";
#endif
}

ELF_API int ELF_APIENTRY elfGetVersionMajor()
{
	return 0;
}

ELF_API int ELF_APIENTRY elfGetVersionMinor()
{
	return 9;
}

ELF_API const char* ELF_APIENTRY elfGetVersionRelease()
{
	return "Beta 2";
}

ELF_API const char* ELF_APIENTRY elfGetVersion()
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

ELF_API const char* ELF_APIENTRY elfGetCurrentDirectory()
{
	return eng->cwd;
}

ELF_API const char* ELF_APIENTRY elfGetErrorString()
{
	return gen->errStr;
}

ELF_API int ELF_APIENTRY elfGetError()
{
	return gen->errCode;
}

ELF_API void ELF_APIENTRY elfQuit()
{
	eng->quit = ELF_TRUE;
}

ELF_API void ELF_APIENTRY elfSetF10Exit(unsigned char exit)
{
	eng->f10Exit = !(exit == ELF_FALSE);
}

ELF_API unsigned char ELF_APIENTRY elfGetF10Exit()
{
	return eng->f10Exit;
}

ELF_API elfScene* ELF_APIENTRY elfLoadScene(const char* filePath)
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

ELF_API void ELF_APIENTRY elfSetScene(elfScene* scene)
{
	if(eng->scene) elfDecRef((elfObject*)eng->scene);
	eng->scene = scene;
	if(eng->scene) elfIncRef((elfObject*)eng->scene);
}

ELF_API elfScene* ELF_APIENTRY elfGetScene()
{
	return eng->scene;
}

ELF_API void ELF_APIENTRY elfSetGui(elfGui* gui)
{
	if(eng->gui) elfDecRef((elfObject*)eng->gui);
	eng->gui = gui;
	if(eng->gui) elfIncRef((elfObject*)eng->gui);
}

ELF_API elfGui* ELF_APIENTRY elfGetGui()
{
	return eng->gui;
}

ELF_API float ELF_APIENTRY elfGetSync()
{
	return eng->sync;
}

ELF_API int ELF_APIENTRY elfGetFps()
{
	return eng->fps;
}

ELF_API void ELF_APIENTRY elfSetFpsLimit(int fpsLimit)
{
	eng->fpsLimit = fpsLimit;
	if(eng->fpsLimit < 0) eng->fpsLimit = 0;
}

ELF_API int ELF_APIENTRY elfGetFpsLimit()
{
	return eng->fpsLimit;
}

ELF_API void ELF_APIENTRY elfSetTickRate(float tickRate)
{
	eng->tickRate = tickRate;
	if(eng->tickRate < 0.0) eng->tickRate = 0.0;
}

ELF_API float ELF_APIENTRY elfGetTickRate()
{
	return eng->tickRate;
}

ELF_API void ELF_APIENTRY elfSetSpeed(float speed)
{
	eng->speed = speed;
	if(eng->speed < 0.0001) eng->speed = 0.0001;
}

ELF_API float ELF_APIENTRY elfGetSpeed()
{
	return eng->speed;
}

ELF_API unsigned char ELF_APIENTRY elfSaveScreenShot(const char* filePath)
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

ELF_API void ELF_APIENTRY elfSetTextureCompress(unsigned char compress)
{
	eng->textureCompress = !compress == ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfGetTextureCompress()
{
	return eng->textureCompress;
}

ELF_API void ELF_APIENTRY elfSetTextureAnisotropy(float anisotropy)
{
	eng->textureAnisotropy = anisotropy;
}

ELF_API float ELF_APIENTRY elfGetTextureAnisotropy()
{
	return eng->textureAnisotropy;
}

ELF_API void ELF_APIENTRY elfSetShadowMapSize(int size)
{
	// why would someone want a shadow map of 1 pixel?...
	if(size < 1) return;

	gfxDestroyRenderTarget(eng->shadowTarget);
	gfxDestroyTexture(eng->shadowMap);

	eng->shadowMapSize = size;
	eng->shadowMap = gfxCreate2dTexture(size, size, 0.0f, GFX_CLAMP, GFX_LINEAR, GFX_DEPTH_COMPONENT, GFX_DEPTH_COMPONENT, GFX_UBYTE, NULL);
	eng->shadowTarget = gfxCreateRenderTarget(size, size);
	gfxSetRenderTargetDepthTexture(eng->shadowTarget, eng->shadowMap);
}

ELF_API int ELF_APIENTRY elfGetShadowMapSize()
{
	return eng->shadowMapSize;
}

ELF_API int ELF_APIENTRY elfGetPolygonsRendered()
{
	return gfxGetVerticesDrawn(GFX_TRIANGLES)/3+gfxGetVerticesDrawn(GFX_TRIANGLE_STRIP)/3;
}

ELF_API void ELF_APIENTRY elfSetFog(float start, float end, float r, float g, float b)
{
	eng->fog = ELF_TRUE;
	eng->fogStart = start;
	eng->fogEnd = end;
	eng->fogColor.r = r;
	eng->fogColor.g = g;
	eng->fogColor.b = b;
}

ELF_API void ELF_APIENTRY elfDisableFog()
{
	eng->fog = ELF_FALSE;
}

ELF_API float ELF_APIENTRY elfGetFogStart()
{
	return eng->fogStart;
}

ELF_API float ELF_APIENTRY elfGetFogEnd()
{
	return eng->fogEnd;
}

ELF_API elfColor ELF_APIENTRY elfGetFogColor()
{
	return eng->fogColor;
}

ELF_API void ELF_APIENTRY elfSetBloom(float threshold)
{
	if(gfxGetVersion() < 200) return;

	if(!eng->postProcess) eng->postProcess = elfCreatePostProcess();
	elfSetPostProcessBloom(eng->postProcess, threshold);
}

ELF_API void ELF_APIENTRY elfDisableBloom()
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

ELF_API float ELF_APIENTRY elfGetBloomThreshold()
{
	if(!eng->postProcess) return ELF_FALSE;
	return elfGetPostProcessBloomThreshold(eng->postProcess);
}

ELF_API void ELF_APIENTRY elfSetDof(float focalRange, float focalDistance)
{
	if(gfxGetVersion() < 200) return;

	if(!eng->postProcess) eng->postProcess = elfCreatePostProcess();
	elfSetPostProcessDof(eng->postProcess, focalRange, focalDistance);
}

ELF_API void ELF_APIENTRY elfDisableDof()
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

ELF_API float ELF_APIENTRY elfGetDofFocalRange()
{
	if(!eng->postProcess) return ELF_FALSE;
	return elfGetPostProcessDofFocalRange(eng->postProcess);
}

ELF_API float ELF_APIENTRY elfGetDofFocalDistance()
{
	if(!eng->postProcess) return ELF_FALSE;
	return elfGetPostProcessDofFocalDistance(eng->postProcess);
}

ELF_API void ELF_APIENTRY elfSetSsao(float amount)
{
	if(gfxGetVersion() < 200) return;

	if(!eng->postProcess) eng->postProcess = elfCreatePostProcess();
	elfSetPostProcessSsao(eng->postProcess, amount);
}

ELF_API void ELF_APIENTRY elfDisableSsao()
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

ELF_API float ELF_APIENTRY elfGetSsaoAmount()
{
	if(eng->postProcess) return elfGetPostProcessSsaoAmount(eng->postProcess);
	return 0.0;
}

ELF_API void ELF_APIENTRY elfSetLightShafts(float intensity)
{
	if(gfxGetVersion() < 200) return;

	if(!eng->postProcess) eng->postProcess = elfCreatePostProcess();
	elfSetPostProcessLightShafts(eng->postProcess, intensity);
}

ELF_API void ELF_APIENTRY elfDisableLightShafts()
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

ELF_API float ELF_APIENTRY elfGetLightShaftsIntensity()
{
	if(eng->postProcess) return elfGetPostProcessLightShaftsIntensity(eng->postProcess);
	return 0.0;
}

ELF_API unsigned char ELF_APIENTRY elfIsFog()
{
	return eng->fog;
}

ELF_API unsigned char ELF_APIENTRY elfIsBloom()
{
	if(eng->postProcess) return elfIsPostProcessBloom(eng->postProcess);
	return ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfIsSsao()
{
	if(eng->postProcess) return elfIsPostProcessSsao(eng->postProcess);
	return ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfIsDof()
{
	if(eng->postProcess) return elfIsPostProcessDof(eng->postProcess);
	return ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfIsLightShafts()
{
	if(eng->postProcess) return elfIsPostProcessLightShafts(eng->postProcess);
	return ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfSetOcclusionCulling(unsigned char cull)
{
	eng->occlusionCulling = !cull == ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfIsOcclusionCulling()
{
	return eng->occlusionCulling;
}

ELF_API void ELF_APIENTRY elfSetDebugDraw(unsigned char debugDraw)
{
	eng->debugDraw = !debugDraw == ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfIsDebugDraw()
{
	return eng->debugDraw;
}

ELF_API elfObject* ELF_APIENTRY elfGetActor()
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

void elfAppendDirectoryItemListFolder(elfList* items, elfDirectoryItem* nitem)
{
	elfDirectoryItem* dirItem;
	int i;

	for(i = 0, dirItem = (elfDirectoryItem*)elfBeginList(items); dirItem;
		dirItem = (elfDirectoryItem*)elfGetListNext(items), i++)
	{
		if(dirItem->itemType == ELF_FILE)
		{
			elfInsertListObject(items, i, (elfObject*)nitem);
			return;
		}
		else continue;
	}

	elfAppendListObject(items, (elfObject*)nitem);
}

typedef struct elfDirItemEmul {
	char* str;
	int type;
} elfDirItemEmul;

static int alphacmp(const void* a, const void* b)
{
	return strcmp((*((elfDirItemEmul*)a)).str, (*((elfDirItemEmul*)b)).str);
}

ELF_API elfDirectory* ELF_APIENTRY elfReadDirectory(const char* path)
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

			elfAppendListObject(directory->items, (elfObject*)dirItem);
		}

		itemCount = elfGetListLength(directory->items);

		names = (elfDirItemEmul*)malloc(sizeof(elfDirItemEmul)*itemCount);
		memset(names, 0x0, sizeof(elfDirItemEmul)*itemCount);

		for(i = 0, dirItem = (elfDirectoryItem*)elfBeginList(directory->items); dirItem;
			dirItem = (elfDirectoryItem*)elfGetListNext(directory->items), i++)
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
				elfAppendDirectoryItemListFolder(directory->items, dirItem);
			else elfAppendListObject(directory->items, (elfObject*)dirItem);

			free(names[i].str);
		}

		free(names);

		return directory;
	}
}

ELF_API const char* ELF_APIENTRY elfGetDirectoryPath(elfDirectory* directory)
{
	return directory->path;
}

ELF_API int ELF_APIENTRY elfGetDirectoryItemCount(elfDirectory* directory)
{
	return elfGetListLength(directory->items);
}

ELF_API elfDirectoryItem* ELF_APIENTRY elfGetDirectoryItem(elfDirectory* directory, int idx)
{
	int i;
	elfDirectoryItem* dirItem;

	if(idx < 0 || idx > elfGetListLength(directory->items)-1) return NULL;

	for(i = 0, dirItem = (elfDirectoryItem*)elfBeginList(directory->items); dirItem;
		dirItem = (elfDirectoryItem*)elfGetListNext(directory->items), i++)
	{
		if(i == idx) return dirItem;
	}

	return NULL;
}

ELF_API const char* ELF_APIENTRY elfGetDirectoryItemName(elfDirectoryItem* dirItem)
{
	return dirItem->name;
}

ELF_API int ELF_APIENTRY elfGetDirectoryItemType(elfDirectoryItem* dirItem)
{
	return dirItem->itemType;
}

ELF_API elfVec3f ELF_APIENTRY elfCreateVec3f(float x, float y, float z)
{
	elfVec3f result;

	result.x = x;
	result.y = y;
	result.z = z;

	return result;
}

ELF_API elfVec4f ELF_APIENTRY elfCreateQua(float x, float y, float z, float w)
{
	elfVec4f result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;

	return result;
}

ELF_API elfVec4f ELF_APIENTRY elfCreateQuaFromEuler(float x, float y, float z)
{
	elfVec4f result;
	memset(&result, 0x0, sizeof(elfVec4f));

	gfxQuaFromEuler(x, y, z, &result.x);

	return result;
}

ELF_API elfVec4f ELF_APIENTRY elfCreateQuaFromAngleAxis(float angle, float x, float y, float z)
{
	elfVec4f qua;
	float axis[3];

	axis[0] = x; axis[1] = y; axis[2] = z;
	gfxQuaFromAngleAxis(angle, axis, &qua.x);

	return qua;
}

ELF_API elfVec3f ELF_APIENTRY elfMulQuaVec3f(elfVec4f qua, elfVec3f vec)
{
	elfVec3f result;

	gfxMulQuaVec(&qua.x, &vec.x, &result.x);

	return result;
}

ELF_API elfVec4f ELF_APIENTRY elfMulQuaQua(elfVec4f qua1, elfVec4f qua2)
{
	elfVec4f result;

	gfxMulQuaQua(&qua1.x, &qua2.x, &result.x);

	return result;
}

ELF_API elfVec4f ELF_APIENTRY elfGetQuaInverted(elfVec4f qua)
{
	elfVec4f result;

	gfxQuaGetInverse(&qua.x, &result.x);

	return result;
}

ELF_API elfVec3f ELF_APIENTRY elfRotateVec3f(elfVec3f vec, float x, float y, float z)
{
	elfVec4f qua;
	elfVec3f result;

	gfxQuaFromEuler(x, y, z, &qua.x);

	gfxMulQuaVec(&qua.x, &vec.x, &result.x);

	return result;
}

ELF_API elfVec3f ELF_APIENTRY elfSubVec3fVec3f(elfVec3f vec1, elfVec3f vec2)
{
	elfVec3f result;
	result.x = vec1.x-vec2.x;
	result.y = vec1.y-vec2.y;
	result.z = vec1.z-vec2.z;
	return result;
}

ELF_API elfVec3f ELF_APIENTRY elfAddVec3fVec3f(elfVec3f vec1, elfVec3f vec2)
{
	elfVec3f result;
	result.x = vec1.x+vec2.x;
	result.y = vec1.y+vec2.y;
	result.z = vec1.z+vec2.z;
	return result;
}

ELF_API float ELF_APIENTRY elfGetVec3fLength(elfVec3f vec)
{
	return gfxVecLength(&vec.x);
}

ELF_API unsigned char ELF_APIENTRY elfAboutZero(float val)
{
	if(val < 0.0001 && val > -0.0001) return ELF_TRUE;
	return ELF_FALSE;
}

ELF_API float ELF_APIENTRY elfFloatAbs(float val)
{
	if(val < 0.0) return -val;
	return val;
}

ELF_API float ELF_APIENTRY elfFloatMin(float a, float b)
{
	if(a < b) return a;
	return b;
}

ELF_API float ELF_APIENTRY elfFloatMax(float a, float b)
{
	if(a > b) return a;
	return b;
}

ELF_API float ELF_APIENTRY elfRandomFloat()
{
	return (float)rand()/(float)RAND_MAX;
}

ELF_API float ELF_APIENTRY elfRandomFloatRange(float min, float max)
{
	return min+(max-min)*elfRandomFloat();
}

ELF_API int ELF_APIENTRY elfRandomInt()
{
	return rand();
}

ELF_API int ELF_APIENTRY elfRandomIntRange(int min, int max)
{
	return (int)(((float)(min+(max-min)))*elfRandomFloat());
}

