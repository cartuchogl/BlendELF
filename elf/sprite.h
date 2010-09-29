
elfSprite* elfCreateSprite(const char* name)
{
	elfSprite* sprite;

	sprite = (elfSprite*)malloc(sizeof(elfSprite));
	memset(sprite, 0x0, sizeof(elfSprite));
	sprite->objType = ELF_SPRITE;
	sprite->objDestr = elfDestroySprite;

	elfInitActor((elfActor*)sprite, ELF_FALSE);

	sprite->scale.x = sprite->scale.y = 1.0;
	sprite->texSize.x = sprite->texSize.y = 0.6;
	sprite->realScale.x = sprite->realScale.y = 0.6; sprite->realScale.z = 1.0;
	sprite->query = gfxCreateQuery();
	sprite->visible = ELF_TRUE;
	sprite->culled = ELF_TRUE;

	sprite->dobject = elfCreatePhysicsObjectBox(0.3, 0.3, 0.01, 0.0, 0.0, 0.0, 0.0);
	elfSetPhysicsObjectActor(sprite->dobject, (elfActor*)sprite);
	elfIncRef((elfObject*)sprite->dobject);

	sprite->pbbLengths.x = sprite->pbbLengths.y = 0.6; sprite->pbbLengths.z = 0.01;

	sprite->framePlayer = elfCreateFramePlayer();
	elfIncRef((elfObject*)sprite->framePlayer);

	if(name) sprite->name = elfCreateString(name);

	sprite->id = ++gen->spriteIdCounter;

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
			sprite->texSize.x = (float)gfxGetTextureWidth(sprite->material->diffuseMap->texture)/100.0;
			sprite->texSize.y = (float)gfxGetTextureHeight(sprite->material->diffuseMap->texture)/100.0;
		}
	}
	else
	{
		sprite->scale.x = sprite->scale.y = 1.0;
		sprite->texSize.x = sprite->texSize.y = 0.6;
		sprite->realScale.x = sprite->realScale.y = 0.6; sprite->realScale.z = 1.0;
		sprite->pbbLengths.x = sprite->pbbLengths.y = 0.6; sprite->pbbLengths.z = 0.01;
	}

	sprite->pbbLengths.x = sprite->texSize.x;
	sprite->pbbLengths.y = sprite->texSize.y;
	sprite->pbbLengths.z = 0.01;
	sprite->realScale.x = sprite->scale.x*sprite->texSize.x;
	sprite->realScale.y = sprite->scale.y*sprite->texSize.y;
	sprite->realScale.z = 0.0;

	sprite->cullRadius = elfGetVec3fLength(sprite->realScale)/2.0;

	sprite->realScale.z = 1.0;
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

	sprite->dobject = elfCreatePhysicsObjectBox(sprite->texSize.x/2.0,
		sprite->texSize.y/2.0, 0.01/2.0, 0.0, 0.0, 0.0, 0.0);

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

void elfSetSpriteMaterial(elfSprite* sprite, elfMaterial* material)
{
	if(sprite->material) elfDecRef((elfObject*)sprite->material);
	sprite->material = material;
	if(sprite->material) elfIncRef((elfObject*)sprite->material);

	elfCalcSpriteBounds(sprite);

	gfxSetTransformScale(sprite->transform, sprite->realScale.x, sprite->realScale.y, sprite->realScale.z);

	if(sprite->object)
	{
		elfSetActorPhysics((elfActor*)sprite, elfGetActorShape((elfActor*)sprite),
			elfGetActorMass((elfActor*)sprite));
	}

	elfResetSpriteDebugPhysicsObject(sprite);
}

void elfSetSpriteScale(elfSprite* sprite, float x, float y)
{
	sprite->scale.x = x; sprite->scale.y = y;

	elfCalcSpriteBounds(sprite);

	gfxSetTransformScale(sprite->transform, sprite->realScale.x, sprite->realScale.y, sprite->realScale.z);

	if(sprite->object) elfSetPhysicsObjectScale(sprite->object, sprite->scale.x, sprite->scale.y, 1.0);
	if(sprite->dobject) elfSetPhysicsObjectScale(sprite->dobject, sprite->scale.x, sprite->scale.y, 1.0);
}

void elfSetSpriteFaceCamera(elfSprite* sprite, unsigned char faceCamera)
{
	sprite->faceCamera = !faceCamera == ELF_FALSE;
}

elfMaterial* elfGetSpriteMaterial(elfSprite* sprite)
{
	return sprite->material;
}

elfVec2f elfGetSpriteScale(elfSprite* sprite)
{
	return sprite->scale;
}

unsigned char elfGetSpriteFaceCamera(elfSprite* sprite)
{
	return sprite->faceCamera;
}

void elfSetSpriteVisible(elfSprite* sprite, unsigned char visible)
{
	if(sprite->visible == visible) return;

	sprite->visible = !visible == ELF_FALSE;

	sprite->moved = ELF_TRUE;
}

unsigned char elfGetSpriteVisible(elfSprite* sprite)
{
	return sprite->visible;
}

void elfSetSpriteOccluder(elfSprite* sprite, unsigned char occluder)
{
	sprite->occluder = !occluder == ELF_FALSE;
}

unsigned char elfGetSpriteOccluder(elfSprite* sprite)
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

	elfSetMaterial(sprite->material, mode, shaderParams);
	gfxSetShaderParams(shaderParams);

	gfxDrawVertexArray(eng->spriteVertexArray, 12, GFX_TRIANGLES);
}

void elfDrawSpriteDebug(elfSprite* sprite, gfxShaderParams* shaderParams)
{
	float* vertexBuffer;

	gfxMulMatrix4Matrix4(gfxGetTransformMatrix(sprite->transform),
		shaderParams->cameraMatrix, shaderParams->modelviewMatrix);

	vertexBuffer = (float*)gfxGetVertexDataBuffer(eng->lines);

	vertexBuffer[0] = -0.5;
	vertexBuffer[1] = 0.5;
	vertexBuffer[2] = 0.0;

	vertexBuffer[3] = -0.5;
	vertexBuffer[4] = -0.5;
	vertexBuffer[5] = 0.0;

	vertexBuffer[6] = -0.5;
	vertexBuffer[7] = -0.5;
	vertexBuffer[8] = 0.0;

	vertexBuffer[9] = 0.5;
	vertexBuffer[10] = -0.5;
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

	vertexBuffer[21] = -0.5;
	vertexBuffer[22] = 0.5;
	vertexBuffer[23] = 0.0;

	if(!sprite->selected) gfxSetColor(&shaderParams->materialParams.diffuseColor, 0.6, 0.2, 0.6, 1.0);
	else gfxSetColor(&shaderParams->materialParams.diffuseColor, 1.0, 0.0, 0.0, 1.0);
	gfxSetShaderParams(shaderParams);
	gfxDrawLines(8, eng->lines);
}

