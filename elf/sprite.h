
ELF_API elfSprite* ELF_APIENTRY elfCreateSprite(const char* name)
{
	elfSprite* sprite;

	sprite = (elfSprite*)malloc(sizeof(elfSprite));
	memset(sprite, 0x0, sizeof(elfSprite));
	sprite->objType = ELF_SPRITE;
	sprite->objDestr = elfDestroySprite;

	elfInitActor((elfActor*)sprite, ELF_FALSE);

	sprite->scale.x = sprite->scale.y = 1.0f;
	sprite->texSize.x = sprite->texSize.y = 0.6f;
	sprite->realScale.x = sprite->realScale.y = 0.6f; sprite->realScale.z = 1.0f;
	sprite->query = gfxCreateQuery();
	sprite->visible = ELF_TRUE;
	sprite->culled = ELF_TRUE;

	sprite->dobject = elfCreatePhysicsObjectBox(0.3f, 0.3f, 0.01f, 0.0f, 0.0f, 0.0f, 0.0f);
	elfSetPhysicsObjectActor(sprite->dobject, (elfActor*)sprite);
	elfIncRef((elfObject*)sprite->dobject);

	sprite->pbbLengths.x = sprite->pbbLengths.y = 0.6f; sprite->pbbLengths.z = 0.01f;

	sprite->framePlayer = elfCreateFramePlayer();
	elfIncRef((elfObject*)sprite->framePlayer);

	if(name) sprite->name = elfCreateString(name);

	sprite->id = ++res->spriteIdCounter;

	elfIncObj(ELF_SPRITE);

	return sprite;
}

void elfUpdateSprite(elfSprite* sprite)
{
	elfUpdateActor((elfActor*)sprite);
}

void elfSpritePreDraw(elfSprite* sprite, elfCamera* camera)
{
	elfVec4f orient;

	elfActorPreDraw((elfActor*)sprite);

	elfGetActorPosition_((elfActor*)sprite, &sprite->position.x);

	if(sprite->faceCamera && camera)
	{
		elfGetActorOrientation_((elfActor*)camera, &orient.x);
		elfSetActorOrientation((elfActor*)sprite, orient.x, orient.y, orient.z, orient.w);
	}
}

void elfSpritePostDraw(elfSprite* sprite)
{
	elfActorPostDraw((elfActor*)sprite);
}

void elfDestroySprite(void* data)
{
	elfSprite* sprite = (elfSprite*)data;

	elfCleanActor((elfActor*)sprite);

	if(sprite->query) gfxDestroyQuery(sprite->query);

	if(sprite->material) elfDecRef((elfObject*)sprite->material);
	elfDecRef((elfObject*)sprite->framePlayer);

	free(sprite);

	elfDecObj(ELF_SPRITE);
}

void elfCalcSpriteBounds(elfSprite* sprite)
{
	if(sprite->material)
	{
		if(sprite->material->diffuseMap && sprite->material->diffuseMap->texture)
		{
			sprite->texSize.x = (float)gfxGetTextureWidth(sprite->material->diffuseMap->texture)/100.0f;
			sprite->texSize.y = (float)gfxGetTextureHeight(sprite->material->diffuseMap->texture)/100.0f;
		}
	}
	else
	{
		sprite->scale.x = sprite->scale.y = 1.0f;
		sprite->texSize.x = sprite->texSize.y = 0.6f;
		sprite->realScale.x = sprite->realScale.y = 0.6f; sprite->realScale.z = 1.0f;
		sprite->pbbLengths.x = sprite->pbbLengths.y = 0.6f; sprite->pbbLengths.z = 0.01f;
	}

	sprite->pbbLengths.x = sprite->texSize.x;
	sprite->pbbLengths.y = sprite->texSize.y;
	sprite->pbbLengths.z = 0.01f;
	sprite->realScale.x = sprite->scale.x*sprite->texSize.x;
	sprite->realScale.y = sprite->scale.y*sprite->texSize.y;
	sprite->realScale.z = 0.0f;

	sprite->cullRadius = elfGetVec3fLength(sprite->realScale)/2.0f;

	sprite->realScale.z = 1.0f;
}

void elfResetSpriteDebugPhysicsObject(elfSprite* sprite)
{
	float position[3];
	float orient[4];
	float scale[3];

	if(sprite->dobject)
	{
		elfSetPhysicsObjectActor(sprite->dobject, NULL);
		elfSetPhysicsObjectWorld(sprite->dobject, NULL);
		elfDecRef((elfObject*)sprite->dobject);
	}

	sprite->dobject = elfCreatePhysicsObjectBox(sprite->texSize.x/2.0f,
		sprite->texSize.y/2.0f, 0.01f/2.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	elfSetPhysicsObjectActor(sprite->dobject, (elfActor*)sprite);
	elfIncRef((elfObject*)sprite->dobject);

	gfxGetTransformPosition(sprite->transform, position);
	gfxGetTransformOrientation(sprite->transform, orient);
	gfxGetTransformScale(sprite->transform, scale);

	elfSetPhysicsObjectPosition(sprite->dobject, position[0], position[1], position[2]);
	elfSetPhysicsObjectOrientation(sprite->dobject, orient[0], orient[1], orient[2], orient[3]);
	elfSetPhysicsObjectScale(sprite->dobject, scale[0], scale[1], scale[2]);

	if(sprite->scene) elfSetPhysicsObjectWorld(sprite->dobject, sprite->scene->dworld);
}

ELF_API void ELF_APIENTRY elfSetSpriteMaterial(elfSprite* sprite, elfMaterial* material)
{
	if(sprite->material) elfDecRef((elfObject*)sprite->material);
	sprite->material = material;
	if(sprite->material) elfIncRef((elfObject*)sprite->material);

	elfCalcSpriteBounds(sprite);

	gfxSetTransformScale(sprite->transform, sprite->realScale.x, sprite->realScale.y, sprite->realScale.z);

	if(sprite->object) elfSetActorPhysics((elfActor*)sprite, ELF_TRUE);

	elfResetSpriteDebugPhysicsObject(sprite);
}

ELF_API void ELF_APIENTRY elfSetSpriteScale(elfSprite* sprite, float x, float y)
{
	sprite->scale.x = x; sprite->scale.y = y;

	elfCalcSpriteBounds(sprite);

	gfxSetTransformScale(sprite->transform, sprite->realScale.x, sprite->realScale.y, sprite->realScale.z);

	if(sprite->object) elfSetPhysicsObjectScale(sprite->object, sprite->scale.x, sprite->scale.y, 1.0f);
	if(sprite->dobject) elfSetPhysicsObjectScale(sprite->dobject, sprite->scale.x, sprite->scale.y, 1.0f);
}

ELF_API void ELF_APIENTRY elfSetSpriteFaceCamera(elfSprite* sprite, unsigned char faceCamera)
{
	sprite->faceCamera = !faceCamera == ELF_FALSE;
}

ELF_API elfMaterial* ELF_APIENTRY elfGetSpriteMaterial(elfSprite* sprite)
{
	return sprite->material;
}

ELF_API elfVec2f ELF_APIENTRY elfGetSpriteScale(elfSprite* sprite)
{
	return sprite->scale;
}

ELF_API unsigned char ELF_APIENTRY elfGetSpriteFaceCamera(elfSprite* sprite)
{
	return sprite->faceCamera;
}

ELF_API void ELF_APIENTRY elfSetSpriteVisible(elfSprite* sprite, unsigned char visible)
{
	if(sprite->visible == visible) return;

	sprite->visible = !visible == ELF_FALSE;

	sprite->moved = ELF_TRUE;
}

ELF_API unsigned char ELF_APIENTRY elfGetSpriteVisible(elfSprite* sprite)
{
	return sprite->visible;
}

ELF_API void ELF_APIENTRY elfSetSpriteOccluder(elfSprite* sprite, unsigned char occluder)
{
	sprite->occluder = !occluder == ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfGetSpriteOccluder(elfSprite* sprite)
{
	return sprite->occluder;
}

unsigned char elfCullSprite(elfSprite* sprite, elfCamera* camera)
{
	if(!sprite->material || !sprite->visible) return ELF_TRUE;

	return !elfSphereInsideFrustum(camera, &sprite->position.x, sprite->cullRadius);
}

void elfDrawSprite(elfSprite* sprite, int mode, gfxShaderParams* shaderParams)
{
	if(!sprite->material || !sprite->visible ||
		(mode == ELF_DRAW_WITHOUT_LIGHTING && sprite->material->lighting)) return;

	gfxMulMatrix4Matrix4(gfxGetTransformMatrix(sprite->transform),
			shaderParams->cameraMatrix, shaderParams->modelviewMatrix);
	gfxMulMatrix3Matrix4(gfxGetTransformNormalMatrix(sprite->transform),
			shaderParams->cameraMatrix, shaderParams->normalMatrix);

	elfSetMaterial(sprite->material, mode, shaderParams);
	gfxSetShaderParams(shaderParams);

	gfxDrawVertexArray(rnd->spriteVertexArray, 12, GFX_TRIANGLES);
}

void elfDrawSpriteDebug(elfSprite* sprite, gfxShaderParams* shaderParams)
{
	float* vertexBuffer;

	gfxMulMatrix4Matrix4(gfxGetTransformMatrix(sprite->transform),
		shaderParams->cameraMatrix, shaderParams->modelviewMatrix);

	vertexBuffer = (float*)gfxGetVertexDataBuffer(rnd->lines);

	vertexBuffer[0] = -0.5f;
	vertexBuffer[1] = 0.5f;
	vertexBuffer[2] = 0.0f;

	vertexBuffer[3] = -0.5f;
	vertexBuffer[4] = -0.5f;
	vertexBuffer[5] = 0.0f;

	vertexBuffer[6] = -0.5f;
	vertexBuffer[7] = -0.5f;
	vertexBuffer[8] = 0.0f;

	vertexBuffer[9] = 0.5f;
	vertexBuffer[10] = -0.5f;
	vertexBuffer[11] = 0.0f;

	vertexBuffer[12] = 0.5f;
	vertexBuffer[13] = -0.5f;
	vertexBuffer[14] = 0.0f;

	vertexBuffer[15] = 0.5f;
	vertexBuffer[16] = 0.5f;
	vertexBuffer[17] = 0.0f;

	vertexBuffer[18] = 0.5f;
	vertexBuffer[19] = 0.5f;
	vertexBuffer[20] = 0.0f;

	vertexBuffer[21] = -0.5f;
	vertexBuffer[22] = 0.5f;
	vertexBuffer[23] = 0.0f;

	if(!sprite->selected) gfxSetColor(&shaderParams->materialParams.diffuseColor, 0.6f, 0.2f, 0.6f, 1.0f);
	else gfxSetColor(&shaderParams->materialParams.diffuseColor, 1.0f, 0.0f, 0.0f, 1.0f);
	gfxSetShaderParams(shaderParams);
	elfDrawLines(8, rnd->lines);

	elfDrawActorDebug((elfActor*)sprite, shaderParams);
}

