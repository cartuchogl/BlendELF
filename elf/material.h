
ELF_API elfMaterial* ELF_APIENTRY elfCreateMaterial(const char* name)
{
	elfMaterial* material;

	material = (elfMaterial*)malloc(sizeof(elfMaterial));
	memset(material, 0x0, sizeof(elfMaterial));
	material->objType = ELF_MATERIAL;
	material->objDestr = elfDestroyMaterial;

	material->diffuseColor.r = material->diffuseColor.g = material->diffuseColor.b = material->diffuseColor.a = 1.0f;
	material->ambientColor.r = material->ambientColor.g = material->ambientColor.b = material->ambientColor.a = 1.0f;
	material->specularColor.r = material->specularColor.g = material->specularColor.b = 0.25f; material->specularColor.a = 1.0f;
	material->specPower = 32.0f;
	material->lighting = ELF_TRUE;

	material->alphaTest = ELF_FALSE;
	material->alphaThreshold = 0.99f;
	material->parallaxScale = 0.25f;

	if(name) material->name = elfCreateString(name);

	elfIncObj(ELF_MATERIAL);

	material->id = ++res->materialIdCounter;

	return material;
}

void elfDestroyMaterial(void* data)
{
	elfMaterial* material = (elfMaterial*)data;

	if(material->name) elfDestroyString(material->name);
	if(material->filePath) elfDestroyString(material->filePath);

	if(material->diffuseMap) elfDecRef((elfObject*)material->diffuseMap);
	if(material->normalMap) elfDecRef((elfObject*)material->normalMap);
	if(material->heightMap) elfDecRef((elfObject*)material->heightMap);
	if(material->specularMap) elfDecRef((elfObject*)material->specularMap);
	if(material->lightMap) elfDecRef((elfObject*)material->lightMap);
	if(material->cubeMap) elfDecRef((elfObject*)material->cubeMap);

	free(material);

	elfDecObj(ELF_MATERIAL);
}

ELF_API void ELF_APIENTRY elfSetMaterialDiffuseColor(elfMaterial* material, float r, float g, float b, float a)
{
	material->diffuseColor.r = r;
	material->diffuseColor.g = g;
	material->diffuseColor.b = b;
	material->diffuseColor.a = a;
}

ELF_API void ELF_APIENTRY elfSetMaterialAmbientColor(elfMaterial* material, float r, float g, float b, float a)
{
	material->ambientColor.r = r;
	material->ambientColor.g = g;
	material->ambientColor.b = b;
	material->ambientColor.a = a;
}

ELF_API void ELF_APIENTRY elfSetMaterialSpecularColor(elfMaterial* material, float r, float g, float b, float a)
{
	material->specularColor.r = r;
	material->specularColor.g = g;
	material->specularColor.b = b;
	material->specularColor.a = a;
}

ELF_API void ELF_APIENTRY elfSetMaterialSpecularPower(elfMaterial* material, float power)
{
	material->specPower = power;
}

ELF_API void ELF_APIENTRY elfSetMaterialLighting(elfMaterial* material, unsigned char lighting)
{
	material->lighting = !lighting == ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfSetMaterialName(elfMaterial* material, const char* name)
{
	if(material->name) elfDestroyString(material->name);
	material->name = elfCreateString(name);
}

ELF_API const char* ELF_APIENTRY elfGetMaterialName(elfMaterial* material)
{
	return material->name;
}

ELF_API const char* ELF_APIENTRY elfGetMaterialFilePath(elfMaterial* material)
{
	return material->filePath;
}

ELF_API elfColor ELF_APIENTRY elfGetMaterialDiffuseColor(elfMaterial* material)
{
	return material->diffuseColor;
}

ELF_API elfColor ELF_APIENTRY elfGetMaterialAmbientColor(elfMaterial* material)
{
	return material->ambientColor;
}

ELF_API elfColor ELF_APIENTRY elfGetMaterialSpecularColor(elfMaterial* material)
{
	return material->specularColor;
}

ELF_API float ELF_APIENTRY elfGetMaterialSpecularPower(elfMaterial* material)
{
	return material->specPower;
}

ELF_API unsigned char ELF_APIENTRY elfGetMaterialLighting(elfMaterial* material)
{
	return material->lighting;
}

ELF_API void ELF_APIENTRY elfSetMaterialDiffuseMap(elfMaterial* material, elfTexture* texture)
{
	int format;

	if(material->diffuseMap) elfDecRef((elfObject*)material->diffuseMap);
	material->diffuseMap = texture;
	if(material->diffuseMap)
	{
		elfIncRef((elfObject*)material->diffuseMap);

		format = elfGetTextureFormat(material->diffuseMap);
		if(format == GFX_RGBA || format == GFX_COMPRESSED_RGBA ||
			format == GFX_BGRA || format == GFX_LUMINANCE_ALPHA)
			material->alphaTest = ELF_TRUE;
	}
}

ELF_API void ELF_APIENTRY elfSetMaterialNormalMap(elfMaterial* material, elfTexture* texture)
{
	if(material->normalMap) elfDecRef((elfObject*)material->normalMap);
	material->normalMap = texture;
	if(material->normalMap) elfIncRef((elfObject*)material->normalMap);
}

ELF_API void ELF_APIENTRY elfSetMaterialHeightMap(elfMaterial* material, elfTexture* texture)
{
	if(material->heightMap) elfDecRef((elfObject*)material->heightMap);
	material->heightMap = texture;
	if(material->heightMap) elfIncRef((elfObject*)material->heightMap);
}

ELF_API void ELF_APIENTRY elfSetMaterialSpecularMap(elfMaterial* material, elfTexture* texture)
{
	if(material->specularMap) elfDecRef((elfObject*)material->specularMap);
	material->specularMap = texture;
	if(material->specularMap) elfIncRef((elfObject*)material->specularMap);
}

ELF_API void ELF_APIENTRY elfSetMaterialLightMap(elfMaterial* material, elfTexture* texture)
{
	if(material->lightMap) elfDecRef((elfObject*)material->lightMap);
	material->lightMap = texture;
	if(material->lightMap) elfIncRef((elfObject*)material->lightMap);
}

ELF_API void ELF_APIENTRY elfSetMaterialCubeMap(elfMaterial* material, elfTexture* texture)
{
	if(gfxGetTextureType(texture->texture) != GFX_CUBE_MAP_TEXTURE) return;
	if(material->cubeMap) elfDecRef((elfObject*)material->cubeMap);
	material->cubeMap = texture;
	if(material->cubeMap) elfIncRef((elfObject*)material->cubeMap);
}

ELF_API void ELF_APIENTRY elfClearMaterialDiffuseMap(elfMaterial* material)
{
	if(material->diffuseMap) elfDecRef((elfObject*)material->diffuseMap);
	material->diffuseMap = NULL;
}

ELF_API void ELF_APIENTRY elfClearMaterialNormalMap(elfMaterial* material)
{
	if(material->normalMap) elfDecRef((elfObject*)material->normalMap);
	material->normalMap = NULL;
}

ELF_API void ELF_APIENTRY elfClearMaterialHeightMap(elfMaterial* material)
{
	if(material->heightMap) elfDecRef((elfObject*)material->heightMap);
	material->heightMap = NULL;
}

ELF_API void ELF_APIENTRY elfClearMaterialSpecularMap(elfMaterial* material)
{
	if(material->specularMap) elfDecRef((elfObject*)material->specularMap);
	material->specularMap = NULL;
}

ELF_API void ELF_APIENTRY elfClearMaterialLightMap(elfMaterial* material)
{
	if(material->lightMap) elfDecRef((elfObject*)material->lightMap);
	material->lightMap = NULL;
}

ELF_API void ELF_APIENTRY elfClearMaterialCubeMap(elfMaterial* material)
{
	if(material->cubeMap) elfDecRef((elfObject*)material->cubeMap);
	material->cubeMap = NULL;
}

ELF_API elfTexture* ELF_APIENTRY elfGetMaterialDiffuseMap(elfMaterial* material)
{
	return material->diffuseMap;
}

ELF_API elfTexture* ELF_APIENTRY elfGetMaterialNormalMap(elfMaterial* material)
{
	return material->normalMap;
}

ELF_API elfTexture* ELF_APIENTRY elfGetMaterialHeightMap(elfMaterial* material)
{
	return material->heightMap;
}

ELF_API elfTexture* ELF_APIENTRY elfGetMaterialSpecularMap(elfMaterial* material)
{
	return material->specularMap;
}

ELF_API elfTexture* ELF_APIENTRY elfGetMaterialLightMap(elfMaterial* material)
{
	return material->lightMap;
}

ELF_API elfTexture* ELF_APIENTRY elfGetMaterialCubeMap(elfMaterial* material)
{
	return material->cubeMap;
}

ELF_API void ELF_APIENTRY elfSetMaterialParallaxScale(elfMaterial* material, float scale)
{
	material->parallaxScale = scale;
	if(material->parallaxScale < 0.0f) material->parallaxScale = 0.0f;
}

ELF_API void ELF_APIENTRY elfSetMaterialAlphaTest(elfMaterial* material, unsigned char alphaTest)
{
	material->alphaTest = !alphaTest == ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfSetMaterialAlphaThreshold(elfMaterial* material, float threshold)
{
	material->alphaThreshold = threshold;
	if(material->alphaThreshold < 0.0f) material->alphaThreshold = 0.0f;
	if(material->alphaThreshold > 1.0f) material->alphaThreshold = 1.0f;
}

ELF_API float ELF_APIENTRY elfGetMaterialParallaxScale(elfMaterial* material)
{
	return material->parallaxScale;
}

ELF_API unsigned char ELF_APIENTRY elfGetMaterialAlphaTest(elfMaterial* material)
{
	return material->alphaTest;
}

ELF_API float ELF_APIENTRY elfGetMaterialAlphaThreshold(elfMaterial* material)
{
	return material->alphaThreshold;
}

void elfSetTextureParamsDefault(gfxTextureParams* params)
{
	params->type = ELF_COLOR_MAP;
	params->texture = NULL;
	params->projectionMode = GFX_NONE;
	params->parallaxScale = 0.0f;
}

void elfSetMaterial(elfMaterial* material, int mode, gfxShaderParams* shaderParams)
{
	int i;

	for(i = 0; i < 6; i++) elfSetTextureParamsDefault(&shaderParams->textureParams[i]);

	if(mode == ELF_DRAW_DEPTH)
	{
		if(material->diffuseMap && material->alphaTest)
		{
			shaderParams->renderParams.alphaTest = ELF_TRUE;
			shaderParams->renderParams.alphaThreshold = material->alphaThreshold;
			shaderParams->textureParams[0].type = ELF_COLOR_MAP;
			shaderParams->textureParams[0].texture = material->diffuseMap->texture;
			shaderParams->textureParams[0].projectionMode = GFX_NONE;
		}
	}
	else if(mode == ELF_DRAW_AMBIENT)
	{
		shaderParams->materialParams.diffuseColor.r = material->ambientColor.r*eng->scene->ambientColor.r;
		shaderParams->materialParams.diffuseColor.g = material->ambientColor.g*eng->scene->ambientColor.g;
		shaderParams->materialParams.diffuseColor.b = material->ambientColor.b*eng->scene->ambientColor.b;
		shaderParams->materialParams.diffuseColor.a = 1.0f;

		if(material->diffuseMap)
		{
			shaderParams->textureParams[0].type = ELF_COLOR_MAP;
			shaderParams->textureParams[0].texture = material->diffuseMap->texture;
			shaderParams->textureParams[0].projectionMode = GFX_NONE;
		}

		if(material->heightMap)
		{
			shaderParams->textureParams[2].type = ELF_HEIGHT_MAP;
			shaderParams->textureParams[2].texture = material->heightMap->texture;
			shaderParams->textureParams[2].projectionMode = GFX_NONE;
			shaderParams->textureParams[2].parallaxScale = material->parallaxScale*0.05f;
		}

		if(material->lightMap)
		{
			shaderParams->textureParams[4].type = ELF_LIGHT_MAP;
			shaderParams->textureParams[4].texture = material->lightMap->texture;
			shaderParams->textureParams[4].projectionMode = GFX_NONE;
		}

		if(material->cubeMap)
		{
			shaderParams->textureParams[5].type = ELF_CUBE_MAP;
			shaderParams->textureParams[5].texture = material->cubeMap->texture;
			shaderParams->textureParams[5].projectionMode = GFX_NONE;
		}
	}
	else if(mode == ELF_DRAW_WITHOUT_LIGHTING)
	{
		memcpy(&shaderParams->materialParams.diffuseColor.r, &material->diffuseColor.r, sizeof(float)*4);

		if(material->diffuseMap)
		{
			shaderParams->textureParams[0].type = ELF_COLOR_MAP;
			shaderParams->textureParams[0].texture = material->diffuseMap->texture;
			shaderParams->textureParams[0].projectionMode = GFX_NONE;
		}

		if(material->heightMap)
		{
			shaderParams->textureParams[2].type = ELF_HEIGHT_MAP;
			shaderParams->textureParams[2].texture = material->heightMap->texture;
			shaderParams->textureParams[2].projectionMode = GFX_NONE;
			shaderParams->textureParams[2].parallaxScale = material->parallaxScale*0.05f;
		}

		if(material->lightMap)
		{
			shaderParams->textureParams[4].type = ELF_LIGHT_MAP;
			shaderParams->textureParams[4].texture = material->lightMap->texture;
			shaderParams->textureParams[4].projectionMode = GFX_NONE;
		}

		if(material->cubeMap)
		{
			shaderParams->textureParams[5].type = ELF_CUBE_MAP;
			shaderParams->textureParams[5].texture = material->cubeMap->texture;
			shaderParams->textureParams[5].projectionMode = GFX_NONE;
		}
	}
	else if(mode == ELF_DRAW_WITH_LIGHTING)
	{
		memcpy(&shaderParams->materialParams.diffuseColor.r, &material->diffuseColor.r, sizeof(float)*4);
		memcpy(&shaderParams->materialParams.specularColor.r, &material->specularColor.r, sizeof(float)*4);
		shaderParams->materialParams.shininess = material->specPower;

		if(material->diffuseMap)
		{
			shaderParams->textureParams[0].type = ELF_COLOR_MAP;
			shaderParams->textureParams[0].texture = material->diffuseMap->texture;
			shaderParams->textureParams[0].projectionMode = GFX_NONE;
		}

		if(material->normalMap)
		{
			shaderParams->textureParams[1].type = ELF_NORMAL_MAP;
			shaderParams->textureParams[1].texture = material->normalMap->texture;
			shaderParams->textureParams[1].projectionMode = GFX_NONE;
		}

		if(material->heightMap)
		{
			shaderParams->textureParams[2].type = ELF_HEIGHT_MAP;
			shaderParams->textureParams[2].texture = material->heightMap->texture;
			shaderParams->textureParams[2].projectionMode = GFX_NONE;
			shaderParams->textureParams[2].parallaxScale = material->parallaxScale*0.05f;
		}

		if(material->specularMap)
		{
			shaderParams->textureParams[3].type = ELF_SPECULAR_MAP;
			shaderParams->textureParams[3].texture = material->specularMap->texture;
			shaderParams->textureParams[3].projectionMode = GFX_NONE;
		}

		if(material->lightMap)
		{
			shaderParams->textureParams[4].type = ELF_LIGHT_MAP;
			shaderParams->textureParams[4].texture = material->lightMap->texture;
			shaderParams->textureParams[4].projectionMode = GFX_NONE;
		}

		if(material->cubeMap)
		{
			shaderParams->textureParams[5].type = ELF_CUBE_MAP;
			shaderParams->textureParams[5].texture = material->cubeMap->texture;
			shaderParams->textureParams[5].projectionMode = GFX_NONE;
		}
	}
}

