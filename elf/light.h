
ELF_API elfLight* ELF_APIENTRY elfCreateLight(const char* name)
{
	elfLight* light;

	light = (elfLight*)malloc(sizeof(elfLight));
	memset(light, 0x0, sizeof(elfLight));
	light->objType = ELF_LIGHT;
	light->objDestr = elfDestroyLight;

	elfInitActor((elfActor*)light, ELF_FALSE);

	light->distance = 30.0f;
	light->fadeSpeed = 1.0f/30.0f;
	light->innerCone = 45.0f;
	light->outerCone = 0.0f;
	light->lightType = ELF_POINT_LIGHT;
	light->visible = ELF_TRUE;
	light->shaft = ELF_FALSE;
	light->shaftSize = 1.0f;
	light->shaftIntensity = 1.0f;
	light->shaftFadeOff = 0.0f;

	elfSetLightColor(light, 1.0f, 1.0f, 1.0f, 1.0f);

	light->shadowCamera = elfCreateCamera("elfShadowCamera");
	elfSetCameraViewport(light->shadowCamera, 0, 0, 512, 512);
	elfSetCameraPerspective(light->shadowCamera, (light->innerCone+light->outerCone)*2, 1.0f, 1.0f, light->distance+(1.0f/light->fadeSpeed));

	gfxMatrix4SetIdentity(light->projectionMatrix);

	light->dobject = elfCreatePhysicsObjectSphere(0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	elfSetPhysicsObjectActor(light->dobject, (elfActor*)light);
	elfIncRef((elfObject*)light->dobject);

	light->pbbLengths.x = light->pbbLengths.y = light->pbbLengths.z = 1.0f;

	if(name) light->name = elfCreateString(name);

	elfIncObj(ELF_LIGHT);

	return light;
}

void elfUpdateLight(elfLight* light)
{
	elfUpdateActor((elfActor*)light);
}

void elfLightPreDraw(elfLight* light)
{
	elfActorPreDraw((elfActor*)light);

	elfCameraPreDraw(light->shadowCamera);
}

void elfLightPostDraw(elfLight* light)
{
	elfActorPostDraw((elfActor*)light);
}

void elfDestroyLight(void* data)
{
	elfLight* light = (elfLight*)data;

	elfCleanActor((elfActor*)light);

	elfDestroyCamera(light->shadowCamera);

	free(light);

	elfDecObj(ELF_LIGHT);
}

ELF_API void ELF_APIENTRY elfSetLightType(elfLight* light, int type)
{
	if(type != ELF_POINT_LIGHT &&
		type != ELF_SPOT_LIGHT &&
		type != ELF_SUN_LIGHT) return;
	light->lightType = type;
}

ELF_API void ELF_APIENTRY elfSetLightColor(elfLight* light, float r, float g, float b, float a)
{
	light->color.r = r;
	light->color.g = g;
	light->color.b = b;
	light->color.a = a;
}

ELF_API void ELF_APIENTRY elfSetLightDistance(elfLight* light, float distance)
{
	light->distance = distance;
	if(light->distance < 0.0f) light->distance = 0.0f;
	elfSetCameraPerspective(light->shadowCamera, (light->innerCone+light->outerCone)*2, 1.0f, 1.0f, light->distance+(1.0f/(light->fadeSpeed)));
}

ELF_API void ELF_APIENTRY elfSetLightFadeSpeed(elfLight* light, float fadeSpeed)
{
	light->fadeSpeed = fadeSpeed;
	if(light->fadeSpeed < 0.0001f) light->fadeSpeed = 0.0001f;
	if(light->fadeSpeed > 1.0f) light->fadeSpeed = 1.0f;
	elfSetCameraPerspective(light->shadowCamera, (light->innerCone+light->outerCone)*2, 1.0f, 1.0f, light->distance+(1.0f/(light->fadeSpeed)));
}

ELF_API void ELF_APIENTRY elfSetLightShadows(elfLight* light, unsigned char shadows)
{
	if(light->shadows == shadows) return;

	light->shadows = shadows;

	light->moved = ELF_TRUE;
}

ELF_API int ELF_APIENTRY elfGetLightType(elfLight* light)
{
	return light->lightType;
}

ELF_API elfColor ELF_APIENTRY elfGetLightColor(elfLight* light)
{
	return light->color;
}

ELF_API float ELF_APIENTRY elfGetLightDistance(elfLight* light)
{
	return light->distance;
}

ELF_API float ELF_APIENTRY elfGetLightFadeSpeed(elfLight* light)
{
	return light->fadeSpeed;
}

ELF_API unsigned char ELF_APIENTRY elfGetLightShadows(elfLight* light)
{
	return light->shadows;
}

ELF_API unsigned char ELF_APIENTRY elfGetLightVisible(elfLight* light)
{
	return light->visible;
}

ELF_API unsigned char ELF_APIENTRY elfIsLightShaft(elfLight* light)
{
	return light->shaft;
}

ELF_API float ELF_APIENTRY elfGetLightShaftSize(elfLight* light)
{
	return light->shaftSize;
}

ELF_API float ELF_APIENTRY elfGetLightShaftIntensity(elfLight* light)
{
	return light->shaftIntensity;
}

ELF_API float ELF_APIENTRY elfGetLightShaftFadeOff(elfLight* light)
{
	return light->shaftFadeOff;
}

ELF_API elfVec2f ELF_APIENTRY elfGetLightCone(elfLight* light)
{
	elfVec2f cone;

	cone.x = light->innerCone;
	cone.y = light->outerCone;

	return cone;
}

ELF_API void ELF_APIENTRY elfSetLightVisible(elfLight* light, unsigned char visible)
{
	light->visible = !(visible == ELF_FALSE);
}

ELF_API void ELF_APIENTRY elfSetLightCone(elfLight* light, float innerCone, float outerCone)
{
	light->innerCone = innerCone;
	light->outerCone = outerCone;
	if(light->innerCone < 0.0f) light->innerCone = 0.0f;
	if(light->outerCone < 0.0f) light->outerCone = 0.0f;
	elfSetCameraPerspective(light->shadowCamera, (light->innerCone+light->outerCone)*2, 1.0f, 1.0f, light->distance+(1.0f/(light->fadeSpeed)));
}

ELF_API void ELF_APIENTRY elfSetLightShaft(elfLight* light, float size, float intensity, float fadeOff)
{
	light->shaft = ELF_TRUE;
	light->shaftSize = size;
	light->shaftIntensity = intensity;
	if(light->shaftIntensity < 0.0f) light->shaftIntensity = 0.0f;
	light->shaftFadeOff = fadeOff;
	if(light->shaftFadeOff < 0.0f) light->shaftFadeOff = 0.0f;
	if(light->shaftFadeOff > 1.0f) light->shaftFadeOff = 1.0f;
}

ELF_API void ELF_APIENTRY elfDisableLightShaft(elfLight* light)
{
	light->shaft = ELF_FALSE;
}

void elfSetLight(elfLight* light, elfCamera* camera, gfxShaderParams* shaderParams)
{
	float axis[3];
	float finalAxis[3] = {0.0f, 0.0f, -1.0f};
	float matrix[16];
	float matrix2[16];
	float orient[4];
	float finalPos[4];

	shaderParams->lightParams.type = light->lightType;

	if(gfxGetVersion() < 200)
	{
		gfxGetTransformPosition(light->transform, finalPos);
		gfxGetTransformOrientation(light->transform, orient);
		gfxMulQuaVec(orient, finalAxis, axis);

		memcpy(&shaderParams->lightParams.position.x, finalPos, sizeof(float)*3);
		memcpy(&shaderParams->lightParams.direction.x, axis, sizeof(float)*3);
	}
	else
	{
		gfxMulMatrix4Matrix4(gfxGetTransformMatrix(light->transform), elfGetCameraModelviewMatrix(camera), matrix);
		finalPos[0] = matrix[12];
		finalPos[1] = matrix[13];
		finalPos[2] = matrix[14];

		gfxGetTransformOrientation(light->transform, orient);
		gfxMulQuaVec(orient, finalAxis, axis);
		gfxMatrix4GetInverse(elfGetCameraModelviewMatrix(camera), matrix2);
		gfxMulMatrix4Vec3(matrix2, axis, finalAxis);

		memcpy(&shaderParams->lightParams.position.x, finalPos, sizeof(float)*3);
		memcpy(&shaderParams->lightParams.direction.x, finalAxis, sizeof(float)*3);
	}

	memcpy(&shaderParams->lightParams.color.r, &light->color.r, sizeof(float)*4);
	shaderParams->lightParams.distance = light->distance;
	shaderParams->lightParams.fadeSpeed = light->fadeSpeed;
	shaderParams->lightParams.innerCone = light->innerCone;
	shaderParams->lightParams.outerCone = light->outerCone;
}

unsigned char elfGetLightChanged(elfLight* light)
{
	return light->moved;
}

void elfDrawLightDebug(elfLight* light, gfxShaderParams* shaderParams)
{
	float* vertexBuffer;
	float step;
	float size;
	int i;

	gfxMulMatrix4Matrix4(gfxGetTransformMatrix(light->transform),
		shaderParams->cameraMatrix, shaderParams->modelviewMatrix);

	vertexBuffer = (float*)gfxGetVertexDataBuffer(eng->lines);

	if(!light->selected) gfxSetColor(&shaderParams->materialParams.diffuseColor, 0.5f, 0.5f, 0.2f, 1.0f);
	else gfxSetColor(&shaderParams->materialParams.diffuseColor, 1.0f, 0.0f, 0.0f, 1.0f);
	gfxSetShaderParams(shaderParams);

	step = (360.0f/32.0)*GFX_PI_DIV_180;

	for(i = 0; i < 32; i++)
	{
		vertexBuffer[i*3] = -((float)sin((float)(step*i)))*0.5f;
		vertexBuffer[i*3+1] = ((float)cos((float)(step*i)))*0.5f;
		vertexBuffer[i*3+2] = 0.0f;
	}

	gfxDrawLineLoop(32, eng->lines);

	for(i = 0; i < 32; i++)
	{
		vertexBuffer[i*3] = 0.0f;
		vertexBuffer[i*3+1] = -((float)sin(step*i))*0.5f;
		vertexBuffer[i*3+2] = ((float)cos(step*i))*0.5f;
	}

	gfxDrawLineLoop(32, eng->lines);

	for(i = 0; i < 32; i++)
	{
		vertexBuffer[i*3] = -((float)sin(step*i))*0.5f;
		vertexBuffer[i*3+1] = 0.0f;
		vertexBuffer[i*3+2] = ((float)cos(step*i))*0.5f;
	}

	gfxDrawLineLoop(32, eng->lines);

	if(!light->selected) gfxSetColor(&shaderParams->materialParams.diffuseColor, 0.3f, 0.3f, 0.1f, 1.0f);
	else gfxSetColor(&shaderParams->materialParams.diffuseColor, 1.0f, 0.0f, 0.0f, 1.0f);
	gfxSetShaderParams(shaderParams);

	if(light->lightType == ELF_POINT_LIGHT)
	{
		step = (360.0f/128.0f)*GFX_PI_DIV_180;

		for(i = 0; i < 128; i++)
		{
			vertexBuffer[i*3] = -((float)sin(step*i))*light->distance;
			vertexBuffer[i*3+1] = ((float)cos(step*i))*light->distance;
			vertexBuffer[i*3+2] = 0.0f;
		}

		gfxDrawLines(128, eng->lines);

		for(i = 0; i < 128; i++)
		{
			vertexBuffer[i*3] = 0.0f;
			vertexBuffer[i*3+1] = -((float)sin(step*i))*light->distance;
			vertexBuffer[i*3+2] = ((float)cos(step*i))*light->distance;
		}

		gfxDrawLines(128, eng->lines);

		for(i = 0; i < 128; i++)
		{
			vertexBuffer[i*3] = -((float)sin(step*i))*light->distance;
			vertexBuffer[i*3+1] = 0.0f;
			vertexBuffer[i*3+2] = ((float)cos(step*i))*light->distance;
		}

		gfxDrawLines(128, eng->lines);

		vertexBuffer[0] = 0.0f;
		vertexBuffer[1] = 0.0f;
		vertexBuffer[2] = 0.5f;
		vertexBuffer[3] = 0.0f;
		vertexBuffer[4] = 0.0f;
		vertexBuffer[5] = -0.5f;
		vertexBuffer[6] = -0.5f;
		vertexBuffer[7] = 0.0f;
		vertexBuffer[8] = 0.0f;
		vertexBuffer[9] = 0.5f;
		vertexBuffer[10] = 0.0f;
		vertexBuffer[11] = 0.0f;
		vertexBuffer[12] = 0.0f;
		vertexBuffer[13] = -0.5f;
		vertexBuffer[14] = 0.0f;
		vertexBuffer[15] = 0.0f;
		vertexBuffer[16] = 0.5f;
		vertexBuffer[17] = 0.0f;

		gfxDrawLines(6, eng->lines);
	}
	else if(light->lightType == ELF_SPOT_LIGHT)
	{
		step = (360.0f/128.0)*GFX_PI_DIV_180;
		size = sin((float)GFX_PI_DIV_180*light->innerCone)*light->distance;

		for(i = 0; i < 128; i++)
		{
			vertexBuffer[i*3] = -(float)sin(step*i)*size;
			vertexBuffer[i*3+1] = (float)cos(step*i)*size;
			vertexBuffer[i*3+2] = -light->distance;
		}

		gfxDrawLines(128, eng->lines);

		size = sin((float)GFX_PI_DIV_180*(light->innerCone+light->outerCone))*light->distance;

		for(i = 0; i < 128; i++)
		{
			vertexBuffer[i*3] = -(float)sin(step*i)*size;
			vertexBuffer[i*3+1] = (float)cos(step*i)*size;
			vertexBuffer[i*3+2] = -light->distance;
		}

		gfxDrawLines(128, eng->lines);

		vertexBuffer[0] = 0.0f;
		vertexBuffer[1] = 0.0f;
		vertexBuffer[2] = 0.5f;
		vertexBuffer[3] = 0.0f;
		vertexBuffer[4] = 0.0f;
		vertexBuffer[5] = -0.5f;
		vertexBuffer[6] = -0.5f;
		vertexBuffer[7] = 0.0f;
		vertexBuffer[8] = 0.0f;
		vertexBuffer[9] = 0.5f;
		vertexBuffer[10] = 0.0f;
		vertexBuffer[11] = 0.0f;
		vertexBuffer[12] = 0.0f;
		vertexBuffer[13] = -0.5f;
		vertexBuffer[14] = 0.0f;
		vertexBuffer[15] = 0.0f;
		vertexBuffer[16] = 0.5f;
		vertexBuffer[17] = 0.0f;
		vertexBuffer[18] = 0.0f;
		vertexBuffer[19] = 0.0f;
		vertexBuffer[20] = 0.0f;
		vertexBuffer[21] = size;
		vertexBuffer[22] = 0.0f;
		vertexBuffer[23] = -light->distance;
		vertexBuffer[24] = 0.0f;
		vertexBuffer[25] = 0.0f;
		vertexBuffer[26] = 0.0f;
		vertexBuffer[27] = -size;
		vertexBuffer[28] = 0.0f;
		vertexBuffer[29] = -light->distance;

		gfxDrawLines(13, eng->lines);
	}
	else if(light->lightType == ELF_SUN_LIGHT)
	{
		vertexBuffer[0] = 0.0f;
		vertexBuffer[1] = 0.0f;
		vertexBuffer[2] = 0.5f;
		vertexBuffer[3] = 0.0f;
		vertexBuffer[4] = 0.0f;
		vertexBuffer[5] = -light->distance;
		vertexBuffer[6] = -0.5f;
		vertexBuffer[7] = 0.0f;
		vertexBuffer[8] = 0.0f;
		vertexBuffer[9] = 0.5f;
		vertexBuffer[10] = 0.0f;
		vertexBuffer[11] = 0.0f;
		vertexBuffer[12] = 0.0f;
		vertexBuffer[13] = -0.5f;
		vertexBuffer[14] = 0.0f;
		vertexBuffer[15] = 0.0f;
		vertexBuffer[16] = 0.5f;
		vertexBuffer[17] = 0.0f;

		gfxDrawLines(6, eng->lines);
	}

	elfDrawActorDebug((elfActor*)light, shaderParams);
}

