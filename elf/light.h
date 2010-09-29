
elfLight* elfCreateLight(const char* name)
{
	elfLight* light;

	light = (elfLight*)malloc(sizeof(elfLight));
	memset(light, 0x0, sizeof(elfLight));
	light->objType = ELF_LIGHT;
	light->objDestr = elfDestroyLight;

	elfInitActor((elfActor*)light, ELF_FALSE);

	light->distance = 30.0;
	light->fadeSpeed = 1.0/30.0;
	light->innerCone = 45.0;
	light->outerCone = 0.0;
	light->lightType = ELF_POINT_LIGHT;
	light->visible = ELF_TRUE;
	light->shaft = ELF_FALSE;
	light->shaftSize = 1.0;
	light->shaftIntensity = 1.0;
	light->shaftFadeOff = 0.0;

	elfSetLightColor(light, 1.0, 1.0, 1.0, 1.0);

	light->shadowCamera = elfCreateCamera("elfShadowCamera");
	elfSetCameraViewport(light->shadowCamera, 0, 0, 512, 512);
	elfSetCameraPerspective(light->shadowCamera, (light->innerCone+light->outerCone)*2, 1.0, 1.0, light->distance+(1.0/light->fadeSpeed));

	gfxMatrix4SetIdentity(light->projectionMatrix);

	light->dobject = elfCreatePhysicsObjectSphere(0.5, 0.0, 0.0, 0.0, 0.0);
	elfSetPhysicsObjectActor(light->dobject, (elfActor*)light);
	elfIncRef((elfObject*)light->dobject);

	light->pbbLengths.x = light->pbbLengths.y = light->pbbLengths.z = 1.0;

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

void elfSetLightType(elfLight* light, int type)
{
	if(type != ELF_POINT_LIGHT &&
		type != ELF_SPOT_LIGHT &&
		type != ELF_SUN_LIGHT) return;
	light->lightType = type;
}

void elfSetLightColor(elfLight* light, float r, float g, float b, float a)
{
	light->color.r = r;
	light->color.g = g;
	light->color.b = b;
	light->color.a = a;
}

void elfSetLightDistance(elfLight* light, float distance)
{
	light->distance = distance;
	if(light->distance < 0.0) light->distance = 0.0;
	elfSetCameraPerspective(light->shadowCamera, (light->innerCone+light->outerCone)*2, 1.0, 1.0, light->distance+(1.0/(light->fadeSpeed)));
}

void elfSetLightFadeSpeed(elfLight* light, float fadeSpeed)
{
	light->fadeSpeed = fadeSpeed;
	if(light->fadeSpeed < 0.0001) light->fadeSpeed = 0.0001;
	if(light->fadeSpeed > 1.0) light->fadeSpeed = 1.0;
	elfSetCameraPerspective(light->shadowCamera, (light->innerCone+light->outerCone)*2, 1.0, 1.0, light->distance+(1.0/(light->fadeSpeed)));
}

void elfSetLightShadows(elfLight* light, unsigned char shadows)
{
	if(light->shadows == shadows) return;

	light->shadows = shadows;

	light->moved = ELF_TRUE;
}

int elfGetLightType(elfLight* light)
{
	return light->lightType;
}

elfColor elfGetLightColor(elfLight* light)
{
	return light->color;
}

float elfGetLightDistance(elfLight* light)
{
	return light->distance;
}

float elfGetLightFadeSpeed(elfLight* light)
{
	return light->fadeSpeed;
}

unsigned char elfGetLightShadows(elfLight* light)
{
	return light->shadows;
}

unsigned char elfGetLightVisible(elfLight* light)
{
	return light->visible;
}

unsigned char elfIsLightShaft(elfLight* light)
{
	return light->shaft;
}

float elfGetLightShaftSize(elfLight* light)
{
	return light->shaftSize;
}

float elfGetLightShaftIntensity(elfLight* light)
{
	return light->shaftIntensity;
}

float elfGetLightShaftFadeOff(elfLight* light)
{
	return light->shaftFadeOff;
}

elfVec2f elfGetLightCone(elfLight* light)
{
	elfVec2f cone;

	cone.x = light->innerCone;
	cone.y = light->outerCone;

	return cone;
}

void elfSetLightVisible(elfLight* light, unsigned char visible)
{
	light->visible = !(visible == ELF_FALSE);
}

void elfSetLightCone(elfLight* light, float innerCone, float outerCone)
{
	light->innerCone = innerCone;
	light->outerCone = outerCone;
	if(light->innerCone < 0.0) light->innerCone = 0.0;
	if(light->outerCone < 0.0) light->outerCone = 0.0;
	elfSetCameraPerspective(light->shadowCamera, (light->innerCone+light->outerCone)*2, 1.0, 1.0, light->distance+(1.0/(light->fadeSpeed)));
}

void elfSetLightShaft(elfLight* light, float size, float intensity, float fadeOff)
{
	light->shaft = ELF_TRUE;
	light->shaftSize = size;
	light->shaftIntensity = intensity;
	if(light->shaftIntensity < 0.0) light->shaftIntensity = 0.0;
	light->shaftFadeOff = fadeOff;
	if(light->shaftFadeOff < 0.0) light->shaftFadeOff = 0.0;
	if(light->shaftFadeOff > 1.0) light->shaftFadeOff = 1.0;
}

void elfDisableLightShaft(elfLight* light)
{
	light->shaft = ELF_FALSE;
}

void elfSetLight(elfLight* light, elfCamera* camera, gfxShaderParams* shaderParams)
{
	float axis[3];
	float finalAxis[3] = {0.0, 0.0, -1.0};
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

	if(!light->selected) gfxSetColor(&shaderParams->materialParams.diffuseColor, 0.5, 0.5, 0.2, 1.0);
	else gfxSetColor(&shaderParams->materialParams.diffuseColor, 1.0, 0.0, 0.0, 1.0);
	gfxSetShaderParams(shaderParams);

	step = (360.0/((float)32))*GFX_PI_DIV_180;

	for(i = 0; i < 32; i++)
	{
		vertexBuffer[i*3] = -((float)sin((float)(step*i)))*0.5;
		vertexBuffer[i*3+1] = ((float)cos((float)(step*i)))*0.5;
		vertexBuffer[i*3+2] = 0.0;
	}

	gfxDrawLineLoop(32, eng->lines);

	for(i = 0; i < 32; i++)
	{
		vertexBuffer[i*3] = 0.0;
		vertexBuffer[i*3+1] = -((float)sin((float)(step*i)))*0.5;
		vertexBuffer[i*3+2] = ((float)cos((float)(step*i)))*0.5;
	}

	gfxDrawLineLoop(32, eng->lines);

	for(i = 0; i < 32; i++)
	{
		vertexBuffer[i*3] = -((float)sin((float)(step*i)))*0.5;
		vertexBuffer[i*3+1] = 0.0;
		vertexBuffer[i*3+2] = ((float)cos((float)(step*i)))*0.5;
	}

	gfxDrawLineLoop(32, eng->lines);

	if(!light->selected) gfxSetColor(&shaderParams->materialParams.diffuseColor, 0.3, 0.3, 0.1, 1.0);
	else gfxSetColor(&shaderParams->materialParams.diffuseColor, 1.0, 0.0, 0.0, 1.0);
	gfxSetShaderParams(shaderParams);

	if(light->lightType == ELF_POINT_LIGHT)
	{
		step = (360.0/((float)128))*GFX_PI_DIV_180;

		for(i = 0; i < 128; i++)
		{
			vertexBuffer[i*3] = -((float)sin((float)(step*i)))*light->distance;
			vertexBuffer[i*3+1] = ((float)cos((float)(step*i)))*light->distance;
			vertexBuffer[i*3+2] = 0.0;
		}

		gfxDrawLines(128, eng->lines);

		for(i = 0; i < 128; i++)
		{
			vertexBuffer[i*3] = 0.0;
			vertexBuffer[i*3+1] = -((float)sin((float)(step*i)))*light->distance;
			vertexBuffer[i*3+2] = ((float)cos((float)(step*i)))*light->distance;
		}

		gfxDrawLines(128, eng->lines);

		for(i = 0; i < 128; i++)
		{
			vertexBuffer[i*3] = -((float)sin((float)(step*i)))*light->distance;
			vertexBuffer[i*3+1] = 0.0;
			vertexBuffer[i*3+2] = ((float)cos((float)(step*i)))*light->distance;
		}

		gfxDrawLines(128, eng->lines);

		vertexBuffer[0] = 0.0;
		vertexBuffer[1] = 0.0;
		vertexBuffer[2] = 0.5;
		vertexBuffer[3] = 0.0;
		vertexBuffer[4] = 0.0;
		vertexBuffer[5] = -0.5;
		vertexBuffer[6] = -0.5;
		vertexBuffer[7] = 0.0;
		vertexBuffer[8] = 0.0;
		vertexBuffer[9] = 0.5;
		vertexBuffer[10] = 0.0;
		vertexBuffer[11] = 0.0;
		vertexBuffer[12] = 0.0;
		vertexBuffer[13] = -0.5;
		vertexBuffer[14] = 0.0;
		vertexBuffer[15] = 0.0;
		vertexBuffer[16] = 0.5;
		vertexBuffer[17] = 0.0;

		gfxDrawLines(6, eng->lines);
	}
	else if(light->lightType == ELF_SPOT_LIGHT)
	{
		step = (360.0/((float)128))*GFX_PI_DIV_180;
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

		vertexBuffer[0] = 0.0;
		vertexBuffer[1] = 0.0;
		vertexBuffer[2] = 0.5;
		vertexBuffer[3] = 0.0;
		vertexBuffer[4] = 0.0;
		vertexBuffer[5] = -0.5;
		vertexBuffer[6] = -0.5;
		vertexBuffer[7] = 0.0;
		vertexBuffer[8] = 0.0;
		vertexBuffer[9] = 0.5;
		vertexBuffer[10] = 0.0;
		vertexBuffer[11] = 0.0;
		vertexBuffer[12] = 0.0;
		vertexBuffer[13] = -0.5;
		vertexBuffer[14] = 0.0;
		vertexBuffer[15] = 0.0;
		vertexBuffer[16] = 0.5;
		vertexBuffer[17] = 0.0;
		vertexBuffer[18] = 0.0;
		vertexBuffer[19] = 0.0;
		vertexBuffer[20] = 0.0;
		vertexBuffer[21] = size;
		vertexBuffer[22] = 0.0;
		vertexBuffer[23] = -light->distance;
		vertexBuffer[24] = 0.0;
		vertexBuffer[25] = 0.0;
		vertexBuffer[26] = 0.0;
		vertexBuffer[27] = -size;
		vertexBuffer[28] = 0.0;
		vertexBuffer[29] = -light->distance;

		gfxDrawLines(13, eng->lines);
	}
	else if(light->lightType == ELF_SUN_LIGHT)
	{
		vertexBuffer[0] = 0.0;
		vertexBuffer[1] = 0.0;
		vertexBuffer[2] = 0.5;
		vertexBuffer[3] = 0.0;
		vertexBuffer[4] = 0.0;
		vertexBuffer[5] = -light->distance;
		vertexBuffer[6] = -0.5;
		vertexBuffer[7] = 0.0;
		vertexBuffer[8] = 0.0;
		vertexBuffer[9] = 0.5;
		vertexBuffer[10] = 0.0;
		vertexBuffer[11] = 0.0;
		vertexBuffer[12] = 0.0;
		vertexBuffer[13] = -0.5;
		vertexBuffer[14] = 0.0;
		vertexBuffer[15] = 0.0;
		vertexBuffer[16] = 0.5;
		vertexBuffer[17] = 0.0;

		gfxDrawLines(6, eng->lines);
	}
}

