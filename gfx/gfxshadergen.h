
typedef struct gfxLine {
	struct gfxLine* next;
	char* text;
} gfxLine;

typedef struct gfxDocument {
	unsigned int numLines;
	unsigned int numChars;
	gfxLine* lines;
} gfxDocument;

char* gfxCreateString(const char* str)
{
	char* nstr;

	if(!str || !strlen(str)) return NULL;

	nstr = (char*)malloc(strlen(str)+1);
	memset(nstr, 0x0, sizeof(char)*(strlen(str)+1));

	memcpy(nstr, str, sizeof(char)*strlen(str));

	return nstr;
}

void gfxDestroyString(char* str)
{
	free(str);
}

gfxLine* gfxCreateLine()
{
	gfxLine* line;

	line = (gfxLine*)malloc(sizeof(gfxLine));
	memset(line, 0x0, sizeof(gfxLine));

	return line;
}

void gfxDestroyLine(gfxLine* line)
{
	if(line->text) gfxDestroyString(line->text);

	free(line);
}

void gfxDestroyLines(gfxLine* line)
{
	if(line->next) gfxDestroyLines(line->next);

	gfxDestroyLine(line);
}

gfxDocument* gfxCreateDocument()
{
	gfxDocument* document;

	document = (gfxDocument*)malloc(sizeof(gfxDocument));
	memset(document, 0x0, sizeof(gfxDocument));

	return document;
}

void gfxDestroyDocument(gfxDocument* document)
{
	if(document->lines) gfxDestroyLines(document->lines);

	free(document);
}

void gfxClearDocument(gfxDocument* document)
{
	if(document->lines) gfxDestroyLines(document->lines);

	memset(document, 0x0, sizeof(gfxDocument));
}

void gfxAddLineToDocument(gfxDocument* document, const char* str)
{
	gfxLine* line;
	gfxLine* lline;

	if(!str || !strlen(str)) return;

	line = gfxCreateLine();

	line->text = gfxCreateString(str);

	if(!document->lines) document->lines = line;
	else
	{
		lline = document->lines;
		while(lline->next) lline = lline->next;
		lline->next = line;
	}

	document->numLines++;
	document->numChars += strlen(str)+1;
}

unsigned int gfxGetDocumentLines(gfxDocument* document)
{
	return document->numLines;
}

unsigned int gfxGetDocumentChars(gfxDocument* document)
{
	return document->numChars;
}

void gfxDocumentToBuffer(gfxDocument* document, char* buf)
{
	int offset;
	gfxLine* line;

	offset = 0;
	line = document->lines;

	while(line)
	{
		memcpy(&buf[offset], line->text, strlen(line->text));
		offset += strlen(line->text);
		buf[offset] = '\n';
		offset++;
		line = line->next;
	}
}

void gfxGetShaderProgramConfig(gfxShaderParams* shaderParams, gfxShaderConfig* shaderConfig)
{
	int i;

	memset(shaderConfig, 0x0, sizeof(gfxShaderConfig));

	for(i = 0; i < GFX_MAX_TEXTURES; i++)
	{
		if(shaderParams->textureParams[i].texture)
		{
			shaderConfig->textures |= shaderParams->textureParams[i].type;
		}
	}

	shaderConfig->light = shaderParams->lightParams.type;
	shaderConfig->vertexColor = shaderParams->renderParams.vertexColor;
	shaderConfig->specular = GFX_FALSE;
	if((shaderParams->materialParams.specularColor.r > 0.0001 ||
		shaderParams->materialParams.specularColor.g > 0.0001 ||
		shaderParams->materialParams.specularColor.b > 0.0001) &&
		shaderParams->materialParams.shininess > 0.0001)
	{
		shaderConfig->specular = GFX_TRUE;
	}

	shaderConfig->gbuffer = shaderParams->gbufferMode;
	shaderConfig->fog = shaderParams->fogParams.mode;
	shaderConfig->blend = shaderParams->renderParams.blendMode;
}

void gfxAddVertexAttributes(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "attribute vec3 elf_VertexAttr;");
	if(config->light || config->textures & GFX_HEIGHT_MAP || config->textures & GFX_CUBE_MAP) gfxAddLineToDocument(document, "attribute vec3 elf_NormalAttr;");
	if(config->textures) gfxAddLineToDocument(document, "attribute vec2 elf_TexCoordAttr;");
	if((config->light && config->textures & GFX_NORMAL_MAP) || config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "attribute vec3 elf_TangentAttr;");
	if(config->vertexColor) gfxAddLineToDocument(document, "attribute vec4 elf_ColorAttr;");
}

void gfxAddVertexUniforms(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "uniform mat4 elf_ProjectionMatrix;");
	gfxAddLineToDocument(document, "uniform mat4 elf_ModelviewMatrix;");
	if(config->light) gfxAddLineToDocument(document, "uniform vec3 elf_LightPosition;");
	if(config->light == GFX_SPOT_LIGHT || config->light == GFX_SUN_LIGHT) gfxAddLineToDocument(document, "uniform vec3 elf_LightSpotDirection;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfxAddLineToDocument(document, "uniform mat4 elf_ShadowProjectionMatrix;");
	if(config->textures & GFX_CUBE_MAP) gfxAddLineToDocument(document, "uniform vec3 elf_CameraPosition;");
}

void gfxAddVertexVaryings(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->light || config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "varying vec3 elf_EyeVector;");
	if(config->light && config->textures & GFX_NORMAL_MAP) gfxAddLineToDocument(document, "varying vec3 elf_LightTSDirection;");
	if(config->light && !(config->textures & GFX_NORMAL_MAP)) gfxAddLineToDocument(document, "varying vec3 elf_Normal;");
	if(config->light) gfxAddLineToDocument(document, "varying vec3 elf_LightDirection;");
	if(config->light && config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "varying float elf_Distance;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfxAddLineToDocument(document, "varying vec4 elf_ShadowCoord;");
	if(config->textures && config->textures != GFX_SHADOW_MAP) gfxAddLineToDocument(document, "varying vec2 elf_TexCoord;");
	if(config->textures & GFX_CUBE_MAP) gfxAddLineToDocument(document, "varying vec3 elf_CubeMapCoord;");
	if(config->vertexColor) gfxAddLineToDocument(document, "varying vec4 elf_VertexColor;");
}

void gfxAddVertexInit(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "void main()");
	gfxAddLineToDocument(document, "{");
	gfxAddLineToDocument(document, "\tvec4 vertex = elf_ModelviewMatrix*vec4(elf_VertexAttr, 1.0);");
}

void gfxAddVertexTextureCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures && config->textures != GFX_SHADOW_MAP) gfxAddLineToDocument(document, "\telf_TexCoord = elf_TexCoordAttr;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfxAddLineToDocument(document, "\telf_ShadowCoord = elf_ShadowProjectionMatrix*vertex;");
}

void gfxAddVertexLightingCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->light || config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "\telf_EyeVector = -vertex.xyz;");
	if(config->light)
	{
		if(config->textures & GFX_NORMAL_MAP || config->textures & GFX_HEIGHT_MAP)
		{
			gfxAddLineToDocument(document, "\tvec3 elf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
			gfxAddLineToDocument(document, "\tvec3 elf_Tangent = vec3(elf_ModelviewMatrix*vec4(elf_TangentAttr, 0.0));");
			gfxAddLineToDocument(document, "\tvec3 elf_BiNormal = cross(elf_Normal, elf_Tangent);");
			gfxAddLineToDocument(document, "\tvec3 tmpvec = -vertex.xyz;");
			gfxAddLineToDocument(document, "\telf_EyeVector.x = dot(tmpvec, elf_Tangent);");
			gfxAddLineToDocument(document, "\telf_EyeVector.y = dot(tmpvec, elf_BiNormal);");
			gfxAddLineToDocument(document, "\telf_EyeVector.z = dot(tmpvec, elf_Normal);");
		}
		if(config->textures & GFX_NORMAL_MAP)
		{
			if(config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "\ttmpvec = elf_LightPosition-vertex.xyz;");
			if(config->light == GFX_SUN_LIGHT) gfxAddLineToDocument(document, "\ttmpvec = -elf_LightSpotDirection;");
			gfxAddLineToDocument(document, "\telf_LightDirection = tmpvec;");
			gfxAddLineToDocument(document, "\telf_LightTSDirection.x = dot(tmpvec, elf_Tangent);");
			gfxAddLineToDocument(document, "\telf_LightTSDirection.y = dot(tmpvec, elf_BiNormal);");
			gfxAddLineToDocument(document, "\telf_LightTSDirection.z = dot(tmpvec, elf_Normal);");
		}
		else
		{
				gfxAddLineToDocument(document, "\telf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
				if(config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "\telf_LightDirection = elf_LightPosition-vertex.xyz;");
				if(config->light == GFX_SUN_LIGHT) gfxAddLineToDocument(document, "\telf_LightDirection = -elf_LightSpotDirection;");
		}
	}
	if(config->textures & GFX_CUBE_MAP)
	{
		if(!config->light && !(config->textures & GFX_HEIGHT_MAP))
		{
			gfxAddLineToDocument(document, "\tvec3 elf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
		}
		gfxAddLineToDocument(document, "\telf_CubeMapCoord = reflect(normalize(elf_CameraPosition-vertex.xyz), elf_Normal);");
	}
	if(config->light && config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "\telf_Distance = length(elf_LightDirection);");
}

void gfxAddVertexEnd(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->vertexColor) gfxAddLineToDocument(document, "\telf_VertexColor = elf_ColorAttr;");
	gfxAddLineToDocument(document, "\tgl_Position = elf_ProjectionMatrix*vertex;");
	gfxAddLineToDocument(document, "}");
}

void gfxAddFragmentTextureUniforms(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_ColorMap;");
	if(config->textures & GFX_NORMAL_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_NormalMap;");
	if(config->textures & GFX_SPECULAR_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_SpecularMap;");
	if(config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_HeightMap;");
	if(config->textures & GFX_COLOR_RAMP_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_ColorRampMap;");
	if(config->textures & GFX_LIGHT_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_LightMap;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfxAddLineToDocument(document, "uniform sampler2DShadow elf_ShadowMap;");
	if(config->textures & GFX_CUBE_MAP) gfxAddLineToDocument(document, "uniform samplerCube elf_CubeMap;");
	if(config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "uniform float elf_ParallaxScale;");
}

void gfxAddFragmentFogUniforms(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->fog)
	{
		gfxAddLineToDocument(document, "uniform float elf_FogStart;");
		gfxAddLineToDocument(document, "uniform float elf_FogEnd;");
		gfxAddLineToDocument(document, "uniform vec3 elf_FogColor;");
	}
}

void gfxAddFragmentMaterialUniforms(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "uniform vec4 elf_DiffuseColor;");
	if(config->light)
	{
		gfxAddLineToDocument(document, "uniform vec3 elf_SpecularColor;");
		gfxAddLineToDocument(document, "uniform float elf_Shininess;");
	}
}

void gfxAddFragmentLightingUniforms(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->light) gfxAddLineToDocument(document, "uniform vec3 elf_LightColor;");
	if(config->light && config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "uniform float elf_LightDistance;");
	if(config->light && config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "uniform float elf_LightFadeSpeed;");
	if(config->light == GFX_SPOT_LIGHT) gfxAddLineToDocument(document, "uniform vec3 elf_LightSpotDirection;");
	if(config->light == GFX_SPOT_LIGHT) gfxAddLineToDocument(document, "uniform float elf_LightInnerConeCos;");
	if(config->light == GFX_SPOT_LIGHT) gfxAddLineToDocument(document, "uniform float elf_LightOuterConeCos;");
}

void gfxAddFragmentVaryings(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures) gfxAddLineToDocument(document, "varying vec2 elf_TexCoord;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfxAddLineToDocument(document, "varying vec4 elf_ShadowCoord;");
	if(config->textures & GFX_CUBE_MAP) gfxAddLineToDocument(document, "varying vec3 elf_CubeMapCoord;");
	if(config->light || config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "varying vec3 elf_EyeVector;");
	if(config->light && config->textures & GFX_NORMAL_MAP) gfxAddLineToDocument(document, "varying vec3 elf_LightTSDirection;");
	if(config->light && !(config->textures & GFX_NORMAL_MAP)) gfxAddLineToDocument(document, "varying vec3 elf_Normal;");
	if(config->light) gfxAddLineToDocument(document, "varying vec3 elf_LightDirection;");
	if(config->light && config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "varying float elf_Distance;");
	if(config->vertexColor) gfxAddLineToDocument(document, "varying vec4 elf_VertexColor;");
}

void gfxAddFragmentInit(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "void main()");
	gfxAddLineToDocument(document, "{");
	gfxAddLineToDocument(document, "\tvec4 finalColor = vec4(1.0, 1.0, 1.0, 1.0);");
	if(config->light)
	{
		gfxAddLineToDocument(document, "\tvec4 diffuse = vec4(0.0, 0.0, 0.0, 1.0);");
		gfxAddLineToDocument(document, "\tvec3 specular = vec3(0.0, 0.0, 0.0);");
	}
}

void gfxAddFragmentShadowCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->light && config->textures & GFX_SHADOW_MAP)
	{
		gfxAddLineToDocument(document, "\tfloat shadow = max(shadow2DProj(elf_ShadowMap, elf_ShadowCoord).r, 0.0);");
		gfxAddLineToDocument(document, "\tif(shadow < 0.001) discard;");
	}
}

void gfxAddFragmentParallaxMappingCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->light || config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "\tvec3 E = normalize(elf_EyeVector);");
	if(config->textures & GFX_HEIGHT_MAP)
	{
		gfxAddLineToDocument(document, "\tfloat depth = texture2D(elf_HeightMap, elf_TexCoord).r;");
		gfxAddLineToDocument(document, "\tvec2 elf_HeightTexCoord = E.xy*depth*elf_ParallaxScale;");
		gfxAddLineToDocument(document, "\tdepth = (depth+texture2D(elf_HeightMap, elf_TexCoord+elf_HeightTexCoord).r)*0.5;");
		gfxAddLineToDocument(document, "\telf_HeightTexCoord = E.xy*depth*elf_ParallaxScale;");
		gfxAddLineToDocument(document, "\tdepth = (depth+texture2D(elf_HeightMap, elf_TexCoord+elf_HeightTexCoord).r)*0.5;");
		gfxAddLineToDocument(document, "\telf_HeightTexCoord = E.xy*depth*elf_ParallaxScale;");
		gfxAddLineToDocument(document, "\telf_HeightTexCoord = elf_TexCoord+elf_HeightTexCoord;");
	}
}

void gfxAddFragmentPreLightingCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->light && config->textures & GFX_NORMAL_MAP && config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "\tvec3 N = normalize(texture2D(elf_NormalMap, elf_HeightTexCoord).rgb*2.0-1.0);");
	if(config->light && config->textures & GFX_NORMAL_MAP && !(config->textures & GFX_HEIGHT_MAP)) gfxAddLineToDocument(document, "\tvec3 N = normalize(texture2D(elf_NormalMap, elf_TexCoord).rgb*2.0-1.0);");
	if(config->light && config->textures & GFX_NORMAL_MAP) gfxAddLineToDocument(document, "\tvec3 L = elf_LightTSDirection*inversesqrt(dot(elf_LightTSDirection, elf_LightTSDirection));");
	if(config->light && !(config->textures & GFX_NORMAL_MAP)) gfxAddLineToDocument(document, "\tvec3 N = normalize(elf_Normal);");
	if(config->light && !(config->textures & GFX_NORMAL_MAP)) gfxAddLineToDocument(document, "\tvec3 L = normalize(elf_LightDirection);");
	if(config->light && config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "\tfloat attenuation = clamp(1.0-max(elf_Distance-elf_LightDistance, 0.0)*elf_LightFadeSpeed, 0.0, 1.0);");
	if(config->light == GFX_SPOT_LIGHT)
	{
		gfxAddLineToDocument(document, "\tvec3 D = normalize(elf_LightSpotDirection);");
		if(config->textures & GFX_NORMAL_MAP) gfxAddLineToDocument(document, "\tfloat cosCurAngle = dot(-normalize(elf_LightDirection), D);");
		else gfxAddLineToDocument(document, "\tfloat cosCurAngle = dot(-L, D);");
		gfxAddLineToDocument(document, "\tfloat cosInnerConeAngle = elf_LightInnerConeCos;");
		gfxAddLineToDocument(document, "\tfloat cosOuterConeAngle = elf_LightOuterConeCos;");
		gfxAddLineToDocument(document, "\tfloat cosInnerMinusOuterConeAngle = cosInnerConeAngle-cosOuterConeAngle;");
		gfxAddLineToDocument(document, "\tfloat spot = 0.0;");
		gfxAddLineToDocument(document, "\tspot = clamp((cosCurAngle-cosOuterConeAngle) / cosInnerMinusOuterConeAngle, 0.0, 1.0);");
	}
}

void gfxAddFragmentLightingCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->light)
	{
		gfxAddLineToDocument(document, "\tfloat lambertTerm = max(dot(N, L), 0.0);");
		gfxAddLineToDocument(document, "\tif(lambertTerm > 0.0)");
		gfxAddLineToDocument(document, "\t{");
		gfxAddLineToDocument(document, "\t\tdiffuse = elf_DiffuseColor*vec4(elf_LightColor*lambertTerm, 1.0);");
		if(config->specular)
		{
			gfxAddLineToDocument(document, "\t\tvec3 R = reflect(-L, N);");
			gfxAddLineToDocument(document, "\t\tfloat specStrength = clamp(pow(max(dot(R, E), 0.0), elf_Shininess), 0.0, 1.0);");
			gfxAddLineToDocument(document, "\t\tspecular = elf_SpecularColor*elf_LightColor*specStrength;");
		}
		gfxAddLineToDocument(document, "\t}");
	}
	if(!config->light) gfxAddLineToDocument(document, "\tfinalColor *= elf_DiffuseColor;");
}

void gfxAddFragmentTextureCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures & GFX_HEIGHT_MAP)
	{
		if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "\tfinalColor *= texture2D(elf_ColorMap, elf_HeightTexCoord);");
		if(config->light && config->textures & GFX_COLOR_RAMP_MAP) gfxAddLineToDocument(document, "\tfinalColor.rgb *= texture2D(elf_ColorRampMap, vec2(clamp(lambertTerm, 0.0, 1.0))).rgb*elf_DiffuseColor*elf_LightColor;");
		if(config->textures & GFX_LIGHT_MAP) gfxAddLineToDocument(document, "\tfinalColor.rgb *= texture2D(elf_LightMap, elf_HeightTexCoord).rgb;");
	}
	else
	{
		if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "\tfinalColor *= texture2D(elf_ColorMap, elf_TexCoord);");
		if(config->light && config->textures & GFX_COLOR_RAMP_MAP) gfxAddLineToDocument(document, "\tfinalColor.rgb *= texture2D(elf_ColorRampMap, vec2(clamp(lambertTerm, 0.0, 1.0))).rgb*elf_DiffuseColor*elf_LightColor;");
		if(config->textures & GFX_LIGHT_MAP) gfxAddLineToDocument(document, "\tfinalColor.rgb *= texture2D(elf_LightMap, elf_TexCoord).rgb;");
	}
	if(config->textures & GFX_CUBE_MAP) gfxAddLineToDocument(document, "\tfinalColor *= textureCube(elf_CubeMap, elf_CubeMapCoord);");
}

void gfxAddFragmentPostLightingCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->light && !(config->textures & GFX_COLOR_RAMP_MAP)) gfxAddLineToDocument(document, "\tfinalColor.rgb *= diffuse.rgb;");
	if(config->light && config->specular && config->textures & GFX_SPECULAR_MAP && !(config->textures & GFX_HEIGHT_MAP)) gfxAddLineToDocument(document, "\tfinalColor.rgb += specular*texture2D(elf_SpecularMap, elf_TexCoord).rgb;");
	if(config->light && config->specular && config->textures & GFX_SPECULAR_MAP && config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "\tfinalColor.rgb += specular*texture2D(elf_SpecularMap, elf_HeightTexCoord).rgb;");
	if(config->light && config->specular && !(config->textures & GFX_SPECULAR_MAP)) gfxAddLineToDocument(document, "\tfinalColor.rgb += specular;"); 
	if(config->light && config->light != GFX_SUN_LIGHT) gfxAddLineToDocument(document, "\tfinalColor.rgb *= attenuation;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfxAddLineToDocument(document, "\tfinalColor.rgb *= shadow;");
	if(config->light == GFX_SPOT_LIGHT) gfxAddLineToDocument(document, "\tfinalColor.rgb *= spot;");
}

void gfxAddFragmentEnd(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->fog)
	{
		if(config->blend == GFX_ADD)
			gfxAddLineToDocument(document, "\tfinalColor.rgb = mix(elf_FogColor*(finalColor.r*0.3+finalColor.g*0.59+finalColor.b*0.11), finalColor.rgb, clamp((elf_FogEnd-gl_FragCoord.z/gl_FragCoord.w)/(elf_FogEnd-elf_FogStart), 0.0, 1.0));");
		else
			gfxAddLineToDocument(document, "\tfinalColor.rgb = mix(elf_FogColor, finalColor.rgb, clamp((elf_FogEnd-gl_FragCoord.z/gl_FragCoord.w)/(elf_FogEnd-elf_FogStart), 0.0, 1.0));");
	}
	if(config->vertexColor) gfxAddLineToDocument(document, "\tfinalColor *= elf_VertexColor;");
	gfxAddLineToDocument(document, "\tgl_FragColor = finalColor;");
	gfxAddLineToDocument(document, "}");
}

gfxShaderProgram* gfxGetShaderProgram(gfxShaderConfig* config)
{
	gfxDocument* document;
	gfxShaderProgram* shaderProgram;
	gfxShaderProgram* lshpr;
	char* vertShdr;
	char* fragShdr;

	shaderProgram = driver->shaderPrograms;
	while(shaderProgram)
	{
		if(!memcmp(&shaderProgram->config, config, sizeof(gfxShaderConfig)))
			return shaderProgram;
		shaderProgram = shaderProgram->next;
	}

	document = gfxCreateDocument();

	// --------------------- VERTEX SHADER --------------------- //

	gfxAddVertexAttributes(document, config);
	gfxAddVertexUniforms(document, config);
	gfxAddVertexVaryings(document, config);
	gfxAddVertexInit(document, config);
	gfxAddVertexTextureCalcs(document, config);
	gfxAddVertexLightingCalcs(document, config);
	gfxAddVertexEnd(document, config);

	vertShdr = (char*)malloc(sizeof(char)*gfxGetDocumentChars(document)+1);
	gfxDocumentToBuffer(document, vertShdr);
	vertShdr[gfxGetDocumentChars(document)] = '\0';
	//elfWriteToLog("------------ VERTEX SHADER ------------\n");
	//elfWriteToLog(vertShdr);

	gfxClearDocument(document);

	// --------------------- FRAGMENT SHADER --------------------- //

	gfxAddFragmentTextureUniforms(document, config);
	gfxAddFragmentFogUniforms(document, config);
	gfxAddFragmentMaterialUniforms(document, config);
	gfxAddFragmentLightingUniforms(document, config);
	gfxAddFragmentVaryings(document, config);
	gfxAddFragmentInit(document, config);
	gfxAddFragmentShadowCalcs(document, config);
	gfxAddFragmentParallaxMappingCalcs(document, config);
	gfxAddFragmentPreLightingCalcs(document, config);
	gfxAddFragmentLightingCalcs(document, config);
	gfxAddFragmentTextureCalcs(document, config);
	gfxAddFragmentPostLightingCalcs(document, config);
	gfxAddFragmentEnd(document, config);

	fragShdr = (char*)malloc(sizeof(char)*(gfxGetDocumentChars(document)+1));
	gfxDocumentToBuffer(document, fragShdr);
	fragShdr[gfxGetDocumentChars(document)] = '\0';
	//elfWriteToLog("----------- FRAGMENT SHADER -----------\n");
	//elfWriteToLog(fragShdr);

	// ----------------------------------------------------------- //

	gfxDestroyDocument(document);

	shaderProgram = gfxCreateShaderProgram(vertShdr, fragShdr);

	free(vertShdr);
	free(fragShdr);

	if(shaderProgram)
	{
		memcpy(&shaderProgram->config, config, sizeof(gfxShaderConfig));

		if(!driver->shaderPrograms) driver->shaderPrograms = shaderProgram;
		else
		{
			lshpr = driver->shaderPrograms;
			while(lshpr->next) lshpr = lshpr->next;
			lshpr->next = shaderProgram;
		}
	}

	return shaderProgram;
}

void gfxAddGbufVertexAttributes(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "attribute vec3 elf_VertexAttr;");
	gfxAddLineToDocument(document, "attribute vec3 elf_NormalAttr;");
	if(config->textures) gfxAddLineToDocument(document, "attribute vec2 elf_TexCoordAttr;");
	if(config->textures & GFX_NORMAL_MAP) gfxAddLineToDocument(document, "attribute vec3 elf_TangentAttr;");
	if(config->vertexColor) gfxAddLineToDocument(document, "attribute vec4 elf_ColorAttr;");
}

void gfxAddGbufVertexUniforms(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "uniform mat4 elf_ProjectionMatrix;");
	gfxAddLineToDocument(document, "uniform mat4 elf_ModelviewMatrix;");
}

void gfxAddGbufVertexVaryings(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "varying vec3 elf_Normal;");
	if(config->textures) gfxAddLineToDocument(document, "varying vec2 elf_TexCoord;");
	if(config->textures & GFX_HEIGHT_MAP)gfxAddLineToDocument(document, "varying vec3 elf_EyeVector;");
	if(config->textures & GFX_NORMAL_MAP || config->textures & GFX_HEIGHT_MAP)
	{
		gfxAddLineToDocument(document, "varying vec3 elf_BiNormal;");
		gfxAddLineToDocument(document, "varying vec3 elf_Tangent;");
	}
	if(config->vertexColor) gfxAddLineToDocument(document, "varying vec4 elf_VertexColor;");
}

void gfxAddGbufVertexInit(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "void main()");
	gfxAddLineToDocument(document, "{");
	gfxAddLineToDocument(document, "\tvec4 vertex = elf_ModelviewMatrix*vec4(elf_VertexAttr, 1.0);");
}

void gfxAddGbufVertexTextureCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures && config->textures != GFX_SHADOW_MAP) gfxAddLineToDocument(document, "\telf_TexCoord = elf_TexCoordAttr;");
}

void gfxAddGbufVertexLightingCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures & GFX_NORMAL_MAP || config->textures & GFX_HEIGHT_MAP)
	{
		gfxAddLineToDocument(document, "\telf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
		gfxAddLineToDocument(document, "\telf_Tangent = vec3(elf_ModelviewMatrix*vec4(elf_TangentAttr, 0.0));");
		gfxAddLineToDocument(document, "\telf_BiNormal = cross(elf_Normal, elf_Tangent);");
		if(config->textures & GFX_HEIGHT_MAP)
		{
			gfxAddLineToDocument(document, "\tvec3 tmpvec = -vertex.xyz;");
			gfxAddLineToDocument(document, "\telf_EyeVector.x = dot(tmpvec, elf_Tangent);");
			gfxAddLineToDocument(document, "\telf_EyeVector.y = dot(tmpvec, elf_BiNormal);");
			gfxAddLineToDocument(document, "\telf_EyeVector.z = dot(tmpvec, elf_Normal);");
		}
	}
	else
	{
		gfxAddLineToDocument(document, "\telf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
	}
}

void gfxAddGbufVertexEnd(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->vertexColor) gfxAddLineToDocument(document, "\telf_VertexColor = elf_ColorAttr;");
	gfxAddLineToDocument(document, "\tgl_Position = elf_ProjectionMatrix*vertex;");
	gfxAddLineToDocument(document, "}");
}

void gfxAddGbufFragmentTextureUniforms(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_ColorMap;");
	if(config->textures & GFX_NORMAL_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_NormalMap;");
	if(config->textures & GFX_SPECULAR_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_SpecularMap;");
	if(config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_HeightMap;");
	if(config->textures & GFX_LIGHT_MAP) gfxAddLineToDocument(document, "uniform sampler2D elf_LightMap;");
}

void gfxAddGbufFragmentMaterialUniforms(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "uniform vec4 elf_DiffuseColor;");
	gfxAddLineToDocument(document, "uniform vec3 elf_SpecularColor;");
	gfxAddLineToDocument(document, "uniform float elf_Shininess;");
	if(config->textures & GFX_HEIGHT_MAP) gfxAddLineToDocument(document, "uniform float elf_ParallaxScale;");
}

void gfxAddGbufFragmentVaryings(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "varying vec3 elf_Normal;");
	if(config->textures) gfxAddLineToDocument(document, "varying vec2 elf_TexCoord;");
	if(config->textures & GFX_HEIGHT_MAP)gfxAddLineToDocument(document, "varying vec3 elf_EyeVector;");
	if(config->textures & GFX_NORMAL_MAP || config->textures & GFX_HEIGHT_MAP)
	{
		gfxAddLineToDocument(document, "varying vec3 elf_BiNormal;");
		gfxAddLineToDocument(document, "varying vec3 elf_Tangent;");
	}
	if(config->vertexColor) gfxAddLineToDocument(document, "varying vec4 elf_VertexColor;");
}

void gfxAddGbufFragmentInit(gfxDocument* document, gfxShaderConfig* config)
{
	gfxAddLineToDocument(document, "void main()");
	gfxAddLineToDocument(document, "{");
}

void gfxAddGbufFragmentParallaxMappingCalcs(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures & GFX_HEIGHT_MAP)
	{
		gfxAddLineToDocument(document, "\tvec3 E = normalize(elf_EyeVector);");
		gfxAddLineToDocument(document, "\tfloat depth = texture2D(elf_HeightMap, elf_TexCoord).r;");
		gfxAddLineToDocument(document, "\tvec2 texcoord = E.xy*depth*elf_ParallaxScale;");
		gfxAddLineToDocument(document, "\tdepth = (depth+texture2D(elf_HeightMap, elf_TexCoord+texcoord).r)*0.5;");
		gfxAddLineToDocument(document, "\ttexcoord = E.xy*depth*elf_ParallaxScale;");
		gfxAddLineToDocument(document, "\tdepth = (depth+texture2D(elf_HeightMap, elf_TexCoord+texcoord).r)*0.5;");
		gfxAddLineToDocument(document, "\ttexcoord = E.xy*depth*elf_ParallaxScale;");
		gfxAddLineToDocument(document, "\ttexcoord = elf_TexCoord+texcoord;");
	}
	else if(config->textures)
	{
		gfxAddLineToDocument(document, "\tvec2 texcoord = elf_TexCoord;");
	}
}

void gfxAddGbufFragmentEnd(gfxDocument* document, gfxShaderConfig* config)
{
	if(config->textures & GFX_NORMAL_MAP)
	{
		gfxAddLineToDocument(document, "\tvec3 normal = texture2D(elf_NormalMap, texcoord).rgb;");
		gfxAddLineToDocument(document, "\tnormal -= 0.5;");
		gfxAddLineToDocument(document, "\tnormal = normalize(normal.x*elf_Tangent+normal.y*elf_BiNormal+normal.z*elf_Normal);");
		gfxAddLineToDocument(document, "\tgl_FragData[0].rg = normal.xy;");		
	}
	else
	{
		gfxAddLineToDocument(document, "\tgl_FragData[0].rg = normalize(elf_Normal).rg;");
	}
	gfxAddLineToDocument(document, "\tvec4 color = elf_DiffuseColor;");
	if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "\tcolor *= texture2D(elf_ColorMap, texcoord);");
	if(config->textures & GFX_LIGHT_MAP) gfxAddLineToDocument(document, "\tcolor *= texture2D(elf_LightMap, texcoord);");
	gfxAddLineToDocument(document, "\tgl_FragData[1] = vec4(color.rgb, 1.0);");
	gfxAddLineToDocument(document, "\tgl_FragData[2] = vec4(elf_SpecularColor, elf_Shininess/255.0);");
	gfxAddLineToDocument(document, "}");
}

gfxShaderProgram* gfxGetGbufShaderProgram(gfxShaderConfig* config)
{
	gfxDocument* document;
	gfxShaderProgram* shaderProgram;
	gfxShaderProgram* lshpr;
	char* vertShdr;
	char* fragShdr;

	shaderProgram = driver->shaderPrograms;
	while(shaderProgram)
	{
		if(!memcmp(&shaderProgram->config, config, sizeof(gfxShaderConfig)))
			return shaderProgram;
		shaderProgram = shaderProgram->next;
	}

	document = gfxCreateDocument();

	// --------------------- VERTEX SHADER --------------------- //

	if(config->gbuffer == GFX_GBUFFER_DEPTH)
	{
		gfxAddLineToDocument(document, "attribute vec3 elf_VertexAttr;");
		if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "attribute vec2 elf_TexCoordAttr;");
		gfxAddLineToDocument(document, "uniform mat4 elf_ProjectionMatrix;");
		gfxAddLineToDocument(document, "uniform mat4 elf_ModelviewMatrix;");
		if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "varying vec2 elf_TexCoord;");
		gfxAddLineToDocument(document, "void main()");
		gfxAddLineToDocument(document, "{");
		if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "\telf_TexCoord = elf_TexCoordAttr;");
		gfxAddLineToDocument(document, "\tgl_Position = elf_ProjectionMatrix*(elf_ModelviewMatrix*vec4(elf_VertexAttr, 1.0));");
		gfxAddLineToDocument(document, "}");
	}
	else if(config->gbuffer == GFX_GBUFFER_FILL)
	{
		gfxAddGbufVertexAttributes(document, config);
		gfxAddGbufVertexUniforms(document, config);
		gfxAddGbufVertexVaryings(document, config);
		gfxAddGbufVertexInit(document, config);
		gfxAddGbufVertexTextureCalcs(document, config);
		gfxAddGbufVertexLightingCalcs(document, config);
		gfxAddGbufVertexEnd(document, config);
	}
	else if(config->gbuffer == GFX_GBUFFER_LIGHTING)
	{
		gfxAddLineToDocument(document, "attribute vec3 elf_VertexAttr;");
		gfxAddLineToDocument(document, "attribute vec2 elf_TexCoordAttr;");
		gfxAddLineToDocument(document, "uniform mat4 elf_ModelviewMatrix;");
		gfxAddLineToDocument(document, "uniform mat4 elf_ProjectionMatrix;");
		gfxAddLineToDocument(document, "varying vec2 elf_TexCoord;");
		gfxAddLineToDocument(document, "void main()");
		gfxAddLineToDocument(document, "{");
		gfxAddLineToDocument(document, "\telf_TexCoord = elf_TexCoordAttr;");
		gfxAddLineToDocument(document, "\tgl_Position = elf_ProjectionMatrix*(elf_ModelviewMatrix*vec4(elf_VertexAttr, 1.0));");
		gfxAddLineToDocument(document, "}");
	}

	vertShdr = (char*)malloc(sizeof(char)*gfxGetDocumentChars(document)+1);
	gfxDocumentToBuffer(document, vertShdr);
	vertShdr[gfxGetDocumentChars(document)] = '\0';
	//elfWriteToLog("------------ VERTEX SHADER ------------\n");
	//elfWriteToLog(vertShdr);

	gfxClearDocument(document);

	// --------------------- FRAGMENT SHADER --------------------- //

	if(config->gbuffer == GFX_GBUFFER_DEPTH)
	{
		if(config->textures & GFX_COLOR_MAP)
		{
			gfxAddLineToDocument(document, "uniform sampler2D elf_ColorMap;");
			gfxAddLineToDocument(document, "varying vec2 elf_TexCoord;");
		}
		gfxAddLineToDocument(document, "void main()");
		gfxAddLineToDocument(document, "{");
		if(config->textures & GFX_COLOR_MAP) gfxAddLineToDocument(document, "\tgl_FragData[0] = texture2D(elf_ColorMap, elf_TexCoord);");
		gfxAddLineToDocument(document, "}");
	}
	else if(config->gbuffer == GFX_GBUFFER_FILL)
	{
		gfxAddGbufFragmentTextureUniforms(document, config);
		gfxAddGbufFragmentMaterialUniforms(document, config);
		gfxAddGbufFragmentVaryings(document, config);
		gfxAddGbufFragmentInit(document, config);
		gfxAddGbufFragmentParallaxMappingCalcs(document, config);
		gfxAddGbufFragmentEnd(document, config);
	}
	else if(config->gbuffer == GFX_GBUFFER_LIGHTING)
	{
		gfxAddLineToDocument(document, "uniform sampler2D elf_Texture0;");
		gfxAddLineToDocument(document, "uniform sampler2D elf_Texture1;");
		gfxAddLineToDocument(document, "uniform sampler2D elf_Texture2;");
		gfxAddLineToDocument(document, "uniform sampler2D elf_Texture3;");
		gfxAddLineToDocument(document, "uniform vec3 elf_LightPosition;");
		gfxAddLineToDocument(document, "uniform vec3 elf_LightColor;");
		gfxAddLineToDocument(document, "uniform float elf_LightDistance;");
		gfxAddLineToDocument(document, "uniform float elf_LightFadeSpeed;");
		if(config->light == GFX_SPOT_LIGHT)
		{
			gfxAddLineToDocument(document, "uniform vec3 elf_LightSpotDirection;");
			gfxAddLineToDocument(document, "uniform float elf_LightInnerConeCos;");
			gfxAddLineToDocument(document, "uniform float elf_LightOuterConeCos;");
			if(config->textures & GFX_SHADOW_MAP)
			{
				gfxAddLineToDocument(document, "uniform sampler2DShadow elf_ShadowMap;");
				gfxAddLineToDocument(document, "uniform mat4 elf_ShadowProjectionMatrix;");
			}
		}
		else if(config->light == GFX_SUN_LIGHT)
		{
			gfxAddLineToDocument(document, "uniform vec3 elf_LightSpotDirection;");
		}
		gfxAddLineToDocument(document, "uniform mat4 elf_InvProjectionMatrix;");
		gfxAddLineToDocument(document, "varying vec2 elf_TexCoord;");
		gfxAddLineToDocument(document, "void main()");
		gfxAddLineToDocument(document, "{\n");
		gfxAddLineToDocument(document, "\tvec3 diffuse = vec3(0.0, 0.0, 0.0);");
		gfxAddLineToDocument(document, "\tvec3 specular = vec3(0.0, 0.0, 0.0);");
		gfxAddLineToDocument(document, "\tfloat depth = texture2D(elf_Texture0, elf_TexCoord).r*2.0-1.0;");
		gfxAddLineToDocument(document, "\tvec4 vertex = elf_InvProjectionMatrix*vec4(elf_TexCoord.x*2.0-1.0, elf_TexCoord.y*2.0-1.0, depth, 1.0);");
		gfxAddLineToDocument(document, "\tvertex = vec4(vertex.xyz/vertex.w, 1.0);");
		if(config->light == GFX_SPOT_LIGHT && config->textures & GFX_SHADOW_MAP)
		{
			gfxAddLineToDocument(document, "\tvec4 elf_ShadowCoord = elf_ShadowProjectionMatrix*vec4(vertex.xyz, 1.0);");
			gfxAddLineToDocument(document, "\tfloat shadow = shadow2DProj(elf_ShadowMap, elf_ShadowCoord).r;");
			gfxAddLineToDocument(document, "\tif(shadow < 0.001) discard;");
		}
		if(config->light != GFX_SUN_LIGHT)
		{
			gfxAddLineToDocument(document, "\tvec3 elf_LightDirection = elf_LightPosition-vertex.xyz;");
		}
		else
		{
			gfxAddLineToDocument(document, "\tvec3 elf_LightDirection = -elf_LightSpotDirection;");
		}
		gfxAddLineToDocument(document, "\tfloat elf_Distance = length(elf_LightDirection);");
		gfxAddLineToDocument(document, "\tvec3 N = vec3(texture2D(elf_Texture1, elf_TexCoord).rg, 0.0);");
		gfxAddLineToDocument(document, "\tN = normalize(vec3(N.x, N.y, sqrt(1.0-N.x*N.x-N.y*N.y)));");
		gfxAddLineToDocument(document, "\tvec3 L = normalize(elf_LightDirection);");
		if(config->light == GFX_SPOT_LIGHT)
		{
			gfxAddLineToDocument(document, "\tvec3 D = normalize(elf_LightSpotDirection);");
			gfxAddLineToDocument(document, "\tfloat cosCurAngle = dot(-L, D);");
			gfxAddLineToDocument(document, "\tfloat cosInnerConeAngle = elf_LightInnerConeCos;");
			gfxAddLineToDocument(document, "\tfloat cosOuterConeAngle = elf_LightOuterConeCos;");
			gfxAddLineToDocument(document, "\tfloat cosInnerMinusOuterConeAngle = cosInnerConeAngle-cosOuterConeAngle;");
			gfxAddLineToDocument(document, "\tfloat spot = 0.0;");
			gfxAddLineToDocument(document, "\tspot = clamp((cosCurAngle-cosOuterConeAngle) / cosInnerMinusOuterConeAngle, 0.0, 1.0);");
		}
		gfxAddLineToDocument(document, "\tfloat att = clamp(1.0-max(elf_Distance-elf_LightDistance, 0.0)*elf_LightFadeSpeed, 0.0, 1.0);");
		gfxAddLineToDocument(document, "\tfloat lambertTerm = max(dot(N, L), 0.0);");
		gfxAddLineToDocument(document, "\tif(lambertTerm > 0.0)");
		gfxAddLineToDocument(document, "\t{");
		gfxAddLineToDocument(document, "\t\tvec3 E = normalize(-vertex.xyz);");
		gfxAddLineToDocument(document, "\t\tvec3 R = reflect(-L, N);");
		gfxAddLineToDocument(document, "\t\tvec4 spec = texture2D(elf_Texture2, elf_TexCoord);");
		gfxAddLineToDocument(document, "\t\tspec.a = spec.a*255.0;");
		gfxAddLineToDocument(document, "\t\tif(spec.a > 0.0)");
		gfxAddLineToDocument(document, "\t\t{");
		gfxAddLineToDocument(document, "\t\t\tfloat specStrength = clamp(pow(max(dot(R, E), 0.0), spec.a), 0.0, 1.0);");
		gfxAddLineToDocument(document, "\t\t\tspecular = spec.rgb*elf_LightColor*specStrength;");
		gfxAddLineToDocument(document, "\t\t}");
		gfxAddLineToDocument(document, "\t\tdiffuse = elf_LightColor*lambertTerm;");
		gfxAddLineToDocument(document, "\t}");
		if(config->light == GFX_POINT_LIGHT || config->light == GFX_SPOT_LIGHT)
		{
			if(config->light == GFX_POINT_LIGHT) gfxAddLineToDocument(document, "\tfloat str = att;");
			if(config->light == GFX_SPOT_LIGHT) gfxAddLineToDocument(document, "\tfloat str = att*spot;");
			if(config->textures & GFX_SHADOW_MAP) gfxAddLineToDocument(document, "\tstr *= shadow;");
		}
		if(config->light != GFX_SUN_LIGHT)
		{
			gfxAddLineToDocument(document, "\tgl_FragData[0] = vec4(diffuse*str, 1.0);");
			gfxAddLineToDocument(document, "\tgl_FragData[1] = vec4(specular*str, 1.0);");
		}
		else
		{
			gfxAddLineToDocument(document, "\tgl_FragData[0] = vec4(diffuse, 1.0);");
			gfxAddLineToDocument(document, "\tgl_FragData[1] = vec4(specular, 1.0);");
		}
		gfxAddLineToDocument(document, "}");
	}

	fragShdr = (char*)malloc(sizeof(char)*(gfxGetDocumentChars(document)+1));
	gfxDocumentToBuffer(document, fragShdr);
	fragShdr[gfxGetDocumentChars(document)] = '\0';
	//elfWriteToLog("----------- FRAGMENT SHADER -----------\n");
	//elfWriteToLog(fragShdr);

	// ----------------------------------------------------------- //

	gfxDestroyDocument(document);

	shaderProgram = gfxCreateShaderProgram(vertShdr, fragShdr);

	free(vertShdr);
	free(fragShdr);

	if(shaderProgram)
	{
		memcpy(&shaderProgram->config, config, sizeof(gfxShaderConfig));

		if(!driver->shaderPrograms) driver->shaderPrograms = shaderProgram;
		else
		{
			lshpr = driver->shaderPrograms;
			while(lshpr->next) lshpr = lshpr->next;
			lshpr->next = shaderProgram;
		}
	}

	return shaderProgram;
}

