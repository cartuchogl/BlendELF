
typedef struct gfx_line {
	struct gfx_line *next;
	char *text;
} gfx_line;

typedef struct gfx_document {
	unsigned int num_lines;
	unsigned int num_chars;
	gfx_line *lines;
} gfx_document;

char* gfx_create_string(const char *str)
{
	char *nstr;

	if(!str || !strlen(str)) return NULL;

	nstr = (char*)malloc(strlen(str)+1);
	memset(nstr, 0x0, sizeof(char)*(strlen(str)+1));

	memcpy(nstr, str, sizeof(char)*strlen(str));

	return nstr;
}

void gfx_destroy_string(char *str)
{
	free(str);
}

gfx_line *gfx_create_line()
{
	gfx_line *line;

	line = (gfx_line*)malloc(sizeof(gfx_line));
	memset(line, 0x0, sizeof(gfx_line));

	return line;
}

void gfx_destroy_line(gfx_line *line)
{
	if(line->text) gfx_destroy_string(line->text);

	free(line);
}

void gfx_destroy_lines(gfx_line *line)
{
	if(line->next) gfx_destroy_lines(line->next);

	gfx_destroy_line(line);
}

gfx_document* gfx_create_document()
{
	gfx_document *document;

	document = (gfx_document*)malloc(sizeof(gfx_document));
	memset(document, 0x0, sizeof(gfx_document));

	return document;
}

void gfx_destroy_document(gfx_document *document)
{
	if(document->lines) gfx_destroy_lines(document->lines);

	free(document);
}

void gfx_clear_document(gfx_document *document)
{
	if(document->lines) gfx_destroy_lines(document->lines);

	memset(document, 0x0, sizeof(gfx_document));
}

void gfx_add_line_to_document(gfx_document *document, const char *str)
{
	gfx_line *line;
	gfx_line *lline;

	if(!str || !strlen(str)) return;

	line = gfx_create_line();

	line->text = gfx_create_string(str);

	if(!document->lines) document->lines = line;
	else
	{
		lline = document->lines;
		while(lline->next) lline = lline->next;
		lline->next = line;
	}

	document->num_lines++;
	document->num_chars += strlen(str)+1;
}

unsigned int gfx_get_document_lines(gfx_document *document)
{
	return document->num_lines;
}

unsigned int gfx_get_document_chars(gfx_document *document)
{
	return document->num_chars;
}

void gfx_document_to_buffer(gfx_document *document, char *buf)
{
	int offset;
	gfx_line *line;

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

void gfx_get_shader_program_config(gfx_shader_params *shader_params, gfx_shader_config *shader_config)
{
	int i;

	memset(shader_config, 0x0, sizeof(gfx_shader_config));

	for(i = 0; i < GFX_MAX_TEXTURES; i++)
	{
		if(shader_params->texture_params[i].texture)
		{
			shader_config->textures |= shader_params->texture_params[i].type;
		}
	}

	shader_config->light = shader_params->light_params.type;
	shader_config->vertex_color = shader_params->render_params.vertex_color;
	shader_config->specular = GFX_FALSE;
	if((shader_params->material_params.specular_color.r > 0.0001 ||
		shader_params->material_params.specular_color.g > 0.0001 ||
		shader_params->material_params.specular_color.b > 0.0001) &&
		shader_params->material_params.shininess > 0.0001)
	{
		shader_config->specular = GFX_TRUE;
	}

	shader_config->gbuffer = shader_params->gbuffer_mode;
	shader_config->fog = shader_params->fog_params.mode;
	shader_config->blend = shader_params->render_params.blend_mode;
}

void gfx_add_vertex_attributes(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "attribute vec3 elf_VertexAttr;");
	if(config->light || config->textures & GFX_HEIGHT_MAP || config->textures & GFX_CUBE_MAP) gfx_add_line_to_document(document, "attribute vec3 elf_NormalAttr;");
	if(config->textures) gfx_add_line_to_document(document, "attribute vec2 elf_TexCoordAttr;");
	if((config->light && config->textures & GFX_NORMAL_MAP) || config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "attribute vec3 elf_TangentAttr;");
	if(config->vertex_color) gfx_add_line_to_document(document, "attribute vec4 elf_ColorAttr;");
}

void gfx_add_vertex_uniforms(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "uniform mat4 elf_ProjectionMatrix;");
	gfx_add_line_to_document(document, "uniform mat4 elf_ModelviewMatrix;");
	if(config->light) gfx_add_line_to_document(document, "uniform vec3 elf_LightPosition;");
	if(config->light == GFX_SPOT_LIGHT || config->light == GFX_SUN_LIGHT) gfx_add_line_to_document(document, "uniform vec3 elf_LightSpotDirection;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfx_add_line_to_document(document, "uniform mat4 elf_ShadowProjectionMatrix;");
}

void gfx_add_vertex_varyings(gfx_document *document, gfx_shader_config *config)
{
	if(config->light || config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "varying vec3 elf_EyeVector;");
	if(config->light && config->textures & GFX_NORMAL_MAP) gfx_add_line_to_document(document, "varying vec3 elf_LightTSDirection;");
	if(config->light && !(config->textures & GFX_NORMAL_MAP)) gfx_add_line_to_document(document, "varying vec3 elf_Normal;");
	if(config->light) gfx_add_line_to_document(document, "varying vec3 elf_LightDirection;");
	if(config->light && config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "varying float elf_Distance;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfx_add_line_to_document(document, "varying vec4 elf_ShadowCoord;");
	if(config->textures && config->textures != GFX_SHADOW_MAP) gfx_add_line_to_document(document, "varying vec2 elf_TexCoord;");
	if(config->textures & GFX_CUBE_MAP) gfx_add_line_to_document(document, "varying vec3 elf_CubeMapCoord;");
	if(config->vertex_color) gfx_add_line_to_document(document, "varying vec4 elf_VertexColor;");
}

void gfx_add_vertex_init(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "void main()");
	gfx_add_line_to_document(document, "{");
	gfx_add_line_to_document(document, "\tvec4 vertex = elf_ModelviewMatrix*vec4(elf_VertexAttr, 1.0);");
}

void gfx_add_vertex_texture_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures && config->textures != GFX_SHADOW_MAP) gfx_add_line_to_document(document, "\telf_TexCoord = elf_TexCoordAttr;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfx_add_line_to_document(document, "\telf_ShadowCoord = elf_ShadowProjectionMatrix*vertex;");
}

void gfx_add_vertex_lighting_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->light || config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "\telf_EyeVector = -vertex.xyz;");
	if(config->light)
	{
		if(config->textures & GFX_NORMAL_MAP || config->textures & GFX_HEIGHT_MAP)
		{
			gfx_add_line_to_document(document, "\tvec3 elf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
			gfx_add_line_to_document(document, "\tvec3 elf_Tangent = vec3(elf_ModelviewMatrix*vec4(elf_TangentAttr, 0.0));");
			gfx_add_line_to_document(document, "\tvec3 elf_BiNormal = cross(elf_Normal, elf_Tangent);");
			gfx_add_line_to_document(document, "\tvec3 tmpvec = -vertex.xyz;");
			gfx_add_line_to_document(document, "\telf_EyeVector.x = dot(tmpvec, elf_Tangent);");
			gfx_add_line_to_document(document, "\telf_EyeVector.y = dot(tmpvec, elf_BiNormal);");
			gfx_add_line_to_document(document, "\telf_EyeVector.z = dot(tmpvec, elf_Normal);");
		}
		if(config->textures & GFX_NORMAL_MAP)
		{
			if(config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "\ttmpvec = elf_LightPosition-vertex.xyz;");
			if(config->light == GFX_SUN_LIGHT) gfx_add_line_to_document(document, "\ttmpvec = -elf_LightSpotDirection;");
			gfx_add_line_to_document(document, "\telf_LightDirection = tmpvec;");
			gfx_add_line_to_document(document, "\telf_LightTSDirection.x = dot(tmpvec, elf_Tangent);");
			gfx_add_line_to_document(document, "\telf_LightTSDirection.y = dot(tmpvec, elf_BiNormal);");
			gfx_add_line_to_document(document, "\telf_LightTSDirection.z = dot(tmpvec, elf_Normal);");
		}
		else
		{
				gfx_add_line_to_document(document, "\telf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
				if(config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "\telf_LightDirection = elf_LightPosition-vertex.xyz;");
				if(config->light == GFX_SUN_LIGHT) gfx_add_line_to_document(document, "\telf_LightDirection = -elf_LightSpotDirection;");
		}
	}
	if(config->textures & GFX_CUBE_MAP)
	{
		if(!config->light && !(config->textures & GFX_HEIGHT_MAP))
		{
			gfx_add_line_to_document(document, "\tvec3 elf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
		}
		gfx_add_line_to_document(document, "\telf_CubeMapCoord = reflect(normalize(-vertex.xyz), elf_Normal);");
	}
	if(config->light && config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "\telf_Distance = length(elf_LightDirection);");
}

void gfx_add_vertex_end(gfx_document *document, gfx_shader_config *config)
{
	if(config->vertex_color) gfx_add_line_to_document(document, "\telf_VertexColor = elf_ColorAttr;");
	gfx_add_line_to_document(document, "\tgl_Position = elf_ProjectionMatrix*vertex;");
	gfx_add_line_to_document(document, "}");
}

void gfx_add_fragment_texture_uniforms(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_ColorMap;");
	if(config->textures & GFX_NORMAL_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_NormalMap;");
	if(config->textures & GFX_SPECULAR_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_SpecularMap;");
	if(config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_HeightMap;");
	if(config->textures & GFX_COLOR_RAMP_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_ColorRampMap;");
	if(config->textures & GFX_LIGHT_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_LightMap;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfx_add_line_to_document(document, "uniform sampler2DShadow elf_ShadowMap;");
	if(config->textures & GFX_CUBE_MAP) gfx_add_line_to_document(document, "uniform samplerCube elf_CubeMap;");
	if(config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "uniform float elf_ParallaxScale;");
}

void gfx_add_fragment_fog_uniforms(gfx_document *document, gfx_shader_config *config)
{
	if(config->fog)
	{
		gfx_add_line_to_document(document, "uniform float elf_FogStart;");
		gfx_add_line_to_document(document, "uniform float elf_FogEnd;");
		gfx_add_line_to_document(document, "uniform vec3 elf_FogColor;");
	}
}

void gfx_add_fragment_material_uniforms(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "uniform vec4 elf_DiffuseColor;");
	if(config->light)
	{
		gfx_add_line_to_document(document, "uniform vec3 elf_SpecularColor;");
		gfx_add_line_to_document(document, "uniform float elf_Shininess;");
	}
}

void gfx_add_fragment_lighting_uniforms(gfx_document *document, gfx_shader_config *config)
{
	if(config->light) gfx_add_line_to_document(document, "uniform vec3 elf_LightColor;");
	if(config->light && config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "uniform float elf_LightDistance;");
	if(config->light && config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "uniform float elf_LightFadeSpeed;");
	if(config->light == GFX_SPOT_LIGHT) gfx_add_line_to_document(document, "uniform vec3 elf_LightSpotDirection;");
	if(config->light == GFX_SPOT_LIGHT) gfx_add_line_to_document(document, "uniform float elf_LightInnerConeCos;");
	if(config->light == GFX_SPOT_LIGHT) gfx_add_line_to_document(document, "uniform float elf_LightOuterConeCos;");
}

void gfx_add_fragment_varyings(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures) gfx_add_line_to_document(document, "varying vec2 elf_TexCoord;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfx_add_line_to_document(document, "varying vec4 elf_ShadowCoord;");
	if(config->textures & GFX_CUBE_MAP) gfx_add_line_to_document(document, "varying vec3 elf_CubeMapCoord;");
	if(config->light || config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "varying vec3 elf_EyeVector;");
	if(config->light && config->textures & GFX_NORMAL_MAP) gfx_add_line_to_document(document, "varying vec3 elf_LightTSDirection;");
	if(config->light && !(config->textures & GFX_NORMAL_MAP)) gfx_add_line_to_document(document, "varying vec3 elf_Normal;");
	if(config->light) gfx_add_line_to_document(document, "varying vec3 elf_LightDirection;");
	if(config->light && config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "varying float elf_Distance;");
	if(config->vertex_color) gfx_add_line_to_document(document, "varying vec4 elf_VertexColor;");
}

void gfx_add_fragment_init(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "void main()");
	gfx_add_line_to_document(document, "{");
	gfx_add_line_to_document(document, "\tvec4 final_color = vec4(1.0, 1.0, 1.0, 1.0);");
	if(config->light)
	{
		gfx_add_line_to_document(document, "\tvec4 diffuse = vec4(0.0, 0.0, 0.0, 1.0);");
		gfx_add_line_to_document(document, "\tvec3 specular = vec3(0.0, 0.0, 0.0);");
	}
}

void gfx_add_fragment_shadow_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->light && config->textures & GFX_SHADOW_MAP)
	{
		gfx_add_line_to_document(document, "\tfloat shadow = max(shadow2DProj(elf_ShadowMap, elf_ShadowCoord).r, 0.0);");
		gfx_add_line_to_document(document, "\tif(shadow < 0.001) discard;");
	}
}

void gfx_add_fragment_parallax_mapping_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->light || config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "\tvec3 E = normalize(elf_EyeVector);");
	if(config->textures & GFX_HEIGHT_MAP)
	{
		gfx_add_line_to_document(document, "\tfloat depth = texture2D(elf_HeightMap, elf_TexCoord).r;");
		gfx_add_line_to_document(document, "\tvec2 elf_HeightTexCoord = E.xy*depth*elf_ParallaxScale;");
		gfx_add_line_to_document(document, "\tdepth = (depth+texture2D(elf_HeightMap, elf_TexCoord+elf_HeightTexCoord).r)*0.5;");
		gfx_add_line_to_document(document, "\telf_HeightTexCoord = E.xy*depth*elf_ParallaxScale;");
		gfx_add_line_to_document(document, "\tdepth = (depth+texture2D(elf_HeightMap, elf_TexCoord+elf_HeightTexCoord).r)*0.5;");
		gfx_add_line_to_document(document, "\telf_HeightTexCoord = E.xy*depth*elf_ParallaxScale;");
		gfx_add_line_to_document(document, "\telf_HeightTexCoord = elf_TexCoord+elf_HeightTexCoord;");
	}
}

void gfx_add_fragment_pre_lighting_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->light && config->textures & GFX_NORMAL_MAP && config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "\tvec3 N = normalize(texture2D(elf_NormalMap, elf_HeightTexCoord).rgb*2.0-1.0);");
	if(config->light && config->textures & GFX_NORMAL_MAP && !(config->textures & GFX_HEIGHT_MAP)) gfx_add_line_to_document(document, "\tvec3 N = normalize(texture2D(elf_NormalMap, elf_TexCoord).rgb*2.0-1.0);");
	if(config->light && config->textures & GFX_NORMAL_MAP) gfx_add_line_to_document(document, "\tvec3 L = elf_LightTSDirection*inversesqrt(dot(elf_LightTSDirection, elf_LightTSDirection));");
	if(config->light && !(config->textures & GFX_NORMAL_MAP)) gfx_add_line_to_document(document, "\tvec3 N = normalize(elf_Normal);");
	if(config->light && !(config->textures & GFX_NORMAL_MAP)) gfx_add_line_to_document(document, "\tvec3 L = normalize(elf_LightDirection);");
	if(config->light && config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "\tfloat attenuation = clamp(1.0-max(elf_Distance-elf_LightDistance, 0.0)*elf_LightFadeSpeed, 0.0, 1.0);");
	if(config->light == GFX_SPOT_LIGHT)
	{
		gfx_add_line_to_document(document, "\tvec3 D = normalize(elf_LightSpotDirection);");
		if(config->textures & GFX_NORMAL_MAP) gfx_add_line_to_document(document, "\tfloat cos_cur_angle = dot(-normalize(elf_LightDirection), D);");
		else gfx_add_line_to_document(document, "\tfloat cos_cur_angle = dot(-L, D);");
		gfx_add_line_to_document(document, "\tfloat cos_inner_cone_angle = elf_LightInnerConeCos;");
		gfx_add_line_to_document(document, "\tfloat cos_outer_cone_angle = elf_LightOuterConeCos;");
		gfx_add_line_to_document(document, "\tfloat cos_inner_minus_outer_cone_angle = cos_inner_cone_angle-cos_outer_cone_angle;");
		gfx_add_line_to_document(document, "\tfloat spot = 0.0;");
		gfx_add_line_to_document(document, "\tspot = clamp((cos_cur_angle-cos_outer_cone_angle) / cos_inner_minus_outer_cone_angle, 0.0, 1.0);");
	}
}

void gfx_add_fragment_lighting_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->light)
	{
		gfx_add_line_to_document(document, "\tfloat lambertTerm = max(dot(N, L), 0.0);");
		gfx_add_line_to_document(document, "\tif(lambertTerm > 0.0)");
		gfx_add_line_to_document(document, "\t{");
		gfx_add_line_to_document(document, "\t\tdiffuse = elf_DiffuseColor*vec4(elf_LightColor*lambertTerm, 1.0);");
		if(config->specular)
		{
			gfx_add_line_to_document(document, "\t\tvec3 R = reflect(-L, N);");
			gfx_add_line_to_document(document, "\t\tfloat specStrength = clamp(pow(max(dot(R, E), 0.0), elf_Shininess), 0.0, 1.0);");
			gfx_add_line_to_document(document, "\t\tspecular = elf_SpecularColor*elf_LightColor*specStrength;");
		}
		gfx_add_line_to_document(document, "\t}");
	}
	if(!config->light) gfx_add_line_to_document(document, "\tfinal_color *= elf_DiffuseColor;");
}

void gfx_add_fragment_texture_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures & GFX_HEIGHT_MAP)
	{
		if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "\tfinal_color *= texture2D(elf_ColorMap, elf_HeightTexCoord);");
		if(config->light && config->textures & GFX_COLOR_RAMP_MAP) gfx_add_line_to_document(document, "\tfinal_color.rgb *= texture2D(elf_ColorRampMap, vec2(clamp(lambertTerm, 0.0, 1.0))).rgb*elf_DiffuseColor*elf_LightColor;");
		if(config->textures & GFX_LIGHT_MAP) gfx_add_line_to_document(document, "\tfinal_color.rgb *= texture2D(elf_LightMap, elf_HeightTexCoord).rgb;");
	}
	else
	{
		if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "\tfinal_color *= texture2D(elf_ColorMap, elf_TexCoord);");
		if(config->light && config->textures & GFX_COLOR_RAMP_MAP) gfx_add_line_to_document(document, "\tfinal_color.rgb *= texture2D(elf_ColorRampMap, vec2(clamp(lambertTerm, 0.0, 1.0))).rgb*elf_DiffuseColor*elf_LightColor;");
		if(config->textures & GFX_LIGHT_MAP) gfx_add_line_to_document(document, "\tfinal_color.rgb *= texture2D(elf_LightMap, elf_TexCoord).rgb;");
	}
	if(config->textures & GFX_CUBE_MAP) gfx_add_line_to_document(document, "\tfinal_color *= textureCube(elf_CubeMap, elf_CubeMapCoord);");
}

void gfx_add_fragment_post_lighting_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->light && !(config->textures & GFX_COLOR_RAMP_MAP)) gfx_add_line_to_document(document, "\tfinal_color.rgb *= diffuse.rgb;");
	if(config->light && config->specular && config->textures & GFX_SPECULAR_MAP && !(config->textures & GFX_HEIGHT_MAP)) gfx_add_line_to_document(document, "\tfinal_color.rgb += specular*texture2D(elf_SpecularMap, elf_TexCoord).rgb;");
	if(config->light && config->specular && config->textures & GFX_SPECULAR_MAP && config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "\tfinal_color.rgb += specular*texture2D(elf_SpecularMap, elf_HeightTexCoord).rgb;");
	if(config->light && config->specular && !(config->textures & GFX_SPECULAR_MAP)) gfx_add_line_to_document(document, "\tfinal_color.rgb += specular;"); 
	if(config->light && config->light != GFX_SUN_LIGHT) gfx_add_line_to_document(document, "\tfinal_color.rgb *= attenuation;");
	if(config->light && config->textures & GFX_SHADOW_MAP) gfx_add_line_to_document(document, "\tfinal_color.rgb *= shadow;");
	if(config->light == GFX_SPOT_LIGHT) gfx_add_line_to_document(document, "\tfinal_color.rgb *= spot;");
}

void gfx_add_fragment_end(gfx_document *document, gfx_shader_config *config)
{
	if(config->fog)
	{
		if(config->blend == GFX_ADD)
			gfx_add_line_to_document(document, "\tfinal_color.rgb = mix(elf_FogColor*(final_color.r*0.3+final_color.g*0.59+final_color.b*0.11), final_color.rgb, clamp((elf_FogEnd-gl_FragCoord.z/gl_FragCoord.w)/(elf_FogEnd-elf_FogStart), 0.0, 1.0));");
		else
			gfx_add_line_to_document(document, "\tfinal_color.rgb = mix(elf_FogColor, final_color.rgb, clamp((elf_FogEnd-gl_FragCoord.z/gl_FragCoord.w)/(elf_FogEnd-elf_FogStart), 0.0, 1.0));");
	}
	if(config->vertex_color) gfx_add_line_to_document(document, "\tfinal_color *= elf_VertexColor;");
	gfx_add_line_to_document(document, "\tgl_FragColor = final_color;");
	gfx_add_line_to_document(document, "}");
}

gfx_shader_program* gfx_get_shader_program(gfx_shader_config *config)
{
	gfx_document *document;
	gfx_shader_program *shader_program;
	gfx_shader_program *lshpr;
	char *vert_shdr;
	char *frag_shdr;

	shader_program = driver->shader_programs;
	while(shader_program)
	{
		if(!memcmp(&shader_program->config, config, sizeof(gfx_shader_config)))
			return shader_program;
		shader_program = shader_program->next;
	}

	document = gfx_create_document();

	// --------------------- VERTEX SHADER --------------------- //

	gfx_add_vertex_attributes(document, config);
	gfx_add_vertex_uniforms(document, config);
	gfx_add_vertex_varyings(document, config);
	gfx_add_vertex_init(document, config);
	gfx_add_vertex_texture_calcs(document, config);
	gfx_add_vertex_lighting_calcs(document, config);
	gfx_add_vertex_end(document, config);

	vert_shdr = (char*)malloc(sizeof(char)*gfx_get_document_chars(document)+1);
	gfx_document_to_buffer(document, vert_shdr);
	vert_shdr[gfx_get_document_chars(document)] = '\0';
	elf_write_to_log("------------ VERTEX SHADER ------------\n");
	elf_write_to_log(vert_shdr);

	gfx_clear_document(document);

	// --------------------- FRAGMENT SHADER --------------------- //

	gfx_add_fragment_texture_uniforms(document, config);
	gfx_add_fragment_fog_uniforms(document, config);
	gfx_add_fragment_material_uniforms(document, config);
	gfx_add_fragment_lighting_uniforms(document, config);
	gfx_add_fragment_varyings(document, config);
	gfx_add_fragment_init(document, config);
	gfx_add_fragment_shadow_calcs(document, config);
	gfx_add_fragment_parallax_mapping_calcs(document, config);
	gfx_add_fragment_pre_lighting_calcs(document, config);
	gfx_add_fragment_lighting_calcs(document, config);
	gfx_add_fragment_texture_calcs(document, config);
	gfx_add_fragment_post_lighting_calcs(document, config);
	gfx_add_fragment_end(document, config);

	frag_shdr = (char*)malloc(sizeof(char)*(gfx_get_document_chars(document)+1));
	gfx_document_to_buffer(document, frag_shdr);
	frag_shdr[gfx_get_document_chars(document)] = '\0';
	elf_write_to_log("----------- FRAGMENT SHADER -----------\n");
	elf_write_to_log(frag_shdr);

	// ----------------------------------------------------------- //

	gfx_destroy_document(document);

	shader_program = gfx_create_shader_program(vert_shdr, frag_shdr);

	free(vert_shdr);
	free(frag_shdr);

	if(shader_program)
	{
		memcpy(&shader_program->config, config, sizeof(gfx_shader_config));

		if(!driver->shader_programs) driver->shader_programs = shader_program;
		else
		{
			lshpr = driver->shader_programs;
			while(lshpr->next) lshpr = lshpr->next;
			lshpr->next = shader_program;
		}
	}

	return shader_program;
}

void gfx_add_gbuf_vertex_attributes(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "attribute vec3 elf_VertexAttr;");
	gfx_add_line_to_document(document, "attribute vec3 elf_NormalAttr;");
	if(config->textures) gfx_add_line_to_document(document, "attribute vec2 elf_TexCoordAttr;");
	if(config->textures & GFX_NORMAL_MAP) gfx_add_line_to_document(document, "attribute vec3 elf_TangentAttr;");
	if(config->vertex_color) gfx_add_line_to_document(document, "attribute vec4 elf_ColorAttr;");
}

void gfx_add_gbuf_vertex_uniforms(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "uniform mat4 elf_ProjectionMatrix;");
	gfx_add_line_to_document(document, "uniform mat4 elf_ModelviewMatrix;");
}

void gfx_add_gbuf_vertex_varyings(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "varying vec3 elf_Normal;");
	if(config->textures) gfx_add_line_to_document(document, "varying vec2 elf_TexCoord;");
	if(config->textures & GFX_HEIGHT_MAP)gfx_add_line_to_document(document, "varying vec3 elf_EyeVector;");
	if(config->textures & GFX_NORMAL_MAP || config->textures & GFX_HEIGHT_MAP)
	{
		gfx_add_line_to_document(document, "varying vec3 elf_BiNormal;");
		gfx_add_line_to_document(document, "varying vec3 elf_Tangent;");
	}
	if(config->vertex_color) gfx_add_line_to_document(document, "varying vec4 elf_VertexColor;");
}

void gfx_add_gbuf_vertex_init(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "void main()");
	gfx_add_line_to_document(document, "{");
	gfx_add_line_to_document(document, "\tvec4 vertex = elf_ModelviewMatrix*vec4(elf_VertexAttr, 1.0);");
}

void gfx_add_gbuf_vertex_texture_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures && config->textures != GFX_SHADOW_MAP) gfx_add_line_to_document(document, "\telf_TexCoord = elf_TexCoordAttr;");
}

void gfx_add_gbuf_vertex_lighting_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures & GFX_NORMAL_MAP || config->textures & GFX_HEIGHT_MAP)
	{
		gfx_add_line_to_document(document, "\telf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
		gfx_add_line_to_document(document, "\telf_Tangent = vec3(elf_ModelviewMatrix*vec4(elf_TangentAttr, 0.0));");
		gfx_add_line_to_document(document, "\telf_BiNormal = cross(elf_Normal, elf_Tangent);");
		if(config->textures & GFX_HEIGHT_MAP)
		{
			gfx_add_line_to_document(document, "\tvec3 tmpvec = -vertex.xyz;");
			gfx_add_line_to_document(document, "\telf_EyeVector.x = dot(tmpvec, elf_Tangent);");
			gfx_add_line_to_document(document, "\telf_EyeVector.y = dot(tmpvec, elf_BiNormal);");
			gfx_add_line_to_document(document, "\telf_EyeVector.z = dot(tmpvec, elf_Normal);");
		}
	}
	else
	{
		gfx_add_line_to_document(document, "\telf_Normal = vec3(elf_ModelviewMatrix*vec4(elf_NormalAttr, 0.0));");
	}
}

void gfx_add_gbuf_vertex_end(gfx_document *document, gfx_shader_config *config)
{
	if(config->vertex_color) gfx_add_line_to_document(document, "\telf_VertexColor = elf_ColorAttr;");
	gfx_add_line_to_document(document, "\tgl_Position = elf_ProjectionMatrix*vertex;");
	gfx_add_line_to_document(document, "}");
}

void gfx_add_gbuf_fragment_texture_uniforms(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_ColorMap;");
	if(config->textures & GFX_NORMAL_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_NormalMap;");
	if(config->textures & GFX_SPECULAR_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_SpecularMap;");
	if(config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_HeightMap;");
	if(config->textures & GFX_LIGHT_MAP) gfx_add_line_to_document(document, "uniform sampler2D elf_LightMap;");
}

void gfx_add_gbuf_fragment_material_uniforms(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "uniform vec4 elf_DiffuseColor;");
	gfx_add_line_to_document(document, "uniform vec3 elf_SpecularColor;");
	gfx_add_line_to_document(document, "uniform float elf_Shininess;");
	if(config->textures & GFX_HEIGHT_MAP) gfx_add_line_to_document(document, "uniform float elf_ParallaxScale;");
}

void gfx_add_gbuf_fragment_varyings(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "varying vec3 elf_Normal;");
	if(config->textures) gfx_add_line_to_document(document, "varying vec2 elf_TexCoord;");
	if(config->textures & GFX_HEIGHT_MAP)gfx_add_line_to_document(document, "varying vec3 elf_EyeVector;");
	if(config->textures & GFX_NORMAL_MAP || config->textures & GFX_HEIGHT_MAP)
	{
		gfx_add_line_to_document(document, "varying vec3 elf_BiNormal;");
		gfx_add_line_to_document(document, "varying vec3 elf_Tangent;");
	}
	if(config->vertex_color) gfx_add_line_to_document(document, "varying vec4 elf_VertexColor;");
}

void gfx_add_gbuf_fragment_init(gfx_document *document, gfx_shader_config *config)
{
	gfx_add_line_to_document(document, "void main()");
	gfx_add_line_to_document(document, "{");
}

void gfx_add_gbuf_fragment_parallax_mapping_calcs(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures & GFX_HEIGHT_MAP)
	{
		gfx_add_line_to_document(document, "\tvec3 E = normalize(elf_EyeVector);");
		gfx_add_line_to_document(document, "\tfloat depth = texture2D(elf_HeightMap, elf_TexCoord).r;");
		gfx_add_line_to_document(document, "\tvec2 texcoord = E.xy*depth*elf_ParallaxScale;");
		gfx_add_line_to_document(document, "\tdepth = (depth+texture2D(elf_HeightMap, elf_TexCoord+texcoord).r)*0.5;");
		gfx_add_line_to_document(document, "\ttexcoord = E.xy*depth*elf_ParallaxScale;");
		gfx_add_line_to_document(document, "\tdepth = (depth+texture2D(elf_HeightMap, elf_TexCoord+texcoord).r)*0.5;");
		gfx_add_line_to_document(document, "\ttexcoord = E.xy*depth*elf_ParallaxScale;");
		gfx_add_line_to_document(document, "\ttexcoord = elf_TexCoord+texcoord;");
	}
	else if(config->textures)
	{
		gfx_add_line_to_document(document, "\tvec2 texcoord = elf_TexCoord;");
	}
}

void gfx_add_gbuf_fragment_end(gfx_document *document, gfx_shader_config *config)
{
	if(config->textures & GFX_NORMAL_MAP)
	{
		gfx_add_line_to_document(document, "\tvec3 normal = texture2D(elf_NormalMap, texcoord).rgb;");
		gfx_add_line_to_document(document, "\tnormal -= 0.5;");
		gfx_add_line_to_document(document, "\tnormal = normalize(normal.x*elf_Tangent+normal.y*elf_BiNormal+normal.z*elf_Normal);");
		gfx_add_line_to_document(document, "\tgl_FragData[0].rg = normal.xy;");		
	}
	else
	{
		gfx_add_line_to_document(document, "\tgl_FragData[0].rg = normalize(elf_Normal).rg;");
	}
	gfx_add_line_to_document(document, "\tvec4 color = elf_DiffuseColor;");
	if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "\tcolor *= texture2D(elf_ColorMap, texcoord);");
	if(config->textures & GFX_LIGHT_MAP) gfx_add_line_to_document(document, "\tcolor *= texture2D(elf_LightMap, texcoord);");
	gfx_add_line_to_document(document, "\tgl_FragData[1] = vec4(color.rgb, 1.0);");
	gfx_add_line_to_document(document, "\tgl_FragData[2] = vec4(elf_SpecularColor, elf_Shininess/255.0);");
	gfx_add_line_to_document(document, "}");
}

gfx_shader_program* gfx_get_gbuf_shader_program(gfx_shader_config *config)
{
	gfx_document *document;
	gfx_shader_program *shader_program;
	gfx_shader_program *lshpr;
	char *vert_shdr;
	char *frag_shdr;

	shader_program = driver->shader_programs;
	while(shader_program)
	{
		if(!memcmp(&shader_program->config, config, sizeof(gfx_shader_config)))
			return shader_program;
		shader_program = shader_program->next;
	}

	document = gfx_create_document();

	// --------------------- VERTEX SHADER --------------------- //

	if(config->gbuffer == GFX_GBUFFER_DEPTH)
	{
		gfx_add_line_to_document(document, "attribute vec3 elf_VertexAttr;");
		if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "attribute vec2 elf_TexCoordAttr;");
		gfx_add_line_to_document(document, "uniform mat4 elf_ProjectionMatrix;");
		gfx_add_line_to_document(document, "uniform mat4 elf_ModelviewMatrix;");
		if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "varying vec2 elf_TexCoord;");
		gfx_add_line_to_document(document, "void main()");
		gfx_add_line_to_document(document, "{");
		if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "\telf_TexCoord = elf_TexCoordAttr;");
		gfx_add_line_to_document(document, "\tgl_Position = elf_ProjectionMatrix*(elf_ModelviewMatrix*vec4(elf_VertexAttr, 1.0));");
		gfx_add_line_to_document(document, "}");
	}
	else if(config->gbuffer == GFX_GBUFFER_FILL)
	{
		gfx_add_gbuf_vertex_attributes(document, config);
		gfx_add_gbuf_vertex_uniforms(document, config);
		gfx_add_gbuf_vertex_varyings(document, config);
		gfx_add_gbuf_vertex_init(document, config);
		gfx_add_gbuf_vertex_texture_calcs(document, config);
		gfx_add_gbuf_vertex_lighting_calcs(document, config);
		gfx_add_gbuf_vertex_end(document, config);
	}
	else if(config->gbuffer == GFX_GBUFFER_LIGHTING)
	{
		gfx_add_line_to_document(document, "attribute vec3 elf_VertexAttr;");
		gfx_add_line_to_document(document, "attribute vec2 elf_TexCoordAttr;");
		gfx_add_line_to_document(document, "uniform mat4 elf_ModelviewMatrix;");
		gfx_add_line_to_document(document, "uniform mat4 elf_ProjectionMatrix;");
		gfx_add_line_to_document(document, "varying vec2 elf_TexCoord;");
		gfx_add_line_to_document(document, "void main()");
		gfx_add_line_to_document(document, "{");
		gfx_add_line_to_document(document, "\telf_TexCoord = elf_TexCoordAttr;");
		gfx_add_line_to_document(document, "\tgl_Position = elf_ProjectionMatrix*(elf_ModelviewMatrix*vec4(elf_VertexAttr, 1.0));");
		gfx_add_line_to_document(document, "}");
	}

	vert_shdr = (char*)malloc(sizeof(char)*gfx_get_document_chars(document)+1);
	gfx_document_to_buffer(document, vert_shdr);
	vert_shdr[gfx_get_document_chars(document)] = '\0';
	//elf_write_to_log("------------ VERTEX SHADER ------------\n");
	//elf_write_to_log(vert_shdr);

	gfx_clear_document(document);

	// --------------------- FRAGMENT SHADER --------------------- //

	if(config->gbuffer == GFX_GBUFFER_DEPTH)
	{
		if(config->textures & GFX_COLOR_MAP)
		{
			gfx_add_line_to_document(document, "uniform sampler2D elf_ColorMap;");
			//gfx_add_line_to_document(document, "uniform float elf_AlphaThreshold;");
			gfx_add_line_to_document(document, "varying vec2 elf_TexCoord;");
		}
		gfx_add_line_to_document(document, "void main()");
		gfx_add_line_to_document(document, "{");
		if(config->textures & GFX_COLOR_MAP) gfx_add_line_to_document(document, "\tgl_FragData[0] = texture2D(elf_ColorMap, elf_TexCoord);");
		gfx_add_line_to_document(document, "}");
	}
	else if(config->gbuffer == GFX_GBUFFER_FILL)
	{
		gfx_add_gbuf_fragment_texture_uniforms(document, config);
		gfx_add_gbuf_fragment_material_uniforms(document, config);
		gfx_add_gbuf_fragment_varyings(document, config);
		gfx_add_gbuf_fragment_init(document, config);
		gfx_add_gbuf_fragment_parallax_mapping_calcs(document, config);
		gfx_add_gbuf_fragment_end(document, config);
	}
	else if(config->gbuffer == GFX_GBUFFER_LIGHTING)
	{
		gfx_add_line_to_document(document, "uniform sampler2D elf_Texture0;");
		gfx_add_line_to_document(document, "uniform sampler2D elf_Texture1;");
		gfx_add_line_to_document(document, "uniform sampler2D elf_Texture2;");
		gfx_add_line_to_document(document, "uniform sampler2D elf_Texture3;");
		gfx_add_line_to_document(document, "uniform vec3 elf_LightPosition;");
		gfx_add_line_to_document(document, "uniform vec3 elf_LightColor;");
		gfx_add_line_to_document(document, "uniform float elf_LightDistance;");
		gfx_add_line_to_document(document, "uniform float elf_LightFadeSpeed;");
		if(config->light == GFX_SPOT_LIGHT)
		{
			gfx_add_line_to_document(document, "uniform vec3 elf_LightSpotDirection;");
			gfx_add_line_to_document(document, "uniform float elf_LightInnerConeCos;");
			gfx_add_line_to_document(document, "uniform float elf_LightOuterConeCos;");
			if(config->textures & GFX_SHADOW_MAP)
			{
				gfx_add_line_to_document(document, "uniform sampler2DShadow elf_ShadowMap;");
				gfx_add_line_to_document(document, "uniform mat4 elf_ShadowProjectionMatrix;");
			}
		}
		else if(config->light == GFX_SUN_LIGHT)
		{
			gfx_add_line_to_document(document, "uniform vec3 elf_LightSpotDirection;");
		}
		gfx_add_line_to_document(document, "uniform mat4 elf_InvProjectionMatrix;");
		gfx_add_line_to_document(document, "varying vec2 elf_TexCoord;");
		gfx_add_line_to_document(document, "void main()");
		gfx_add_line_to_document(document, "{\n");
		gfx_add_line_to_document(document, "\tvec3 diffuse = vec3(0.0, 0.0, 0.0);");
		gfx_add_line_to_document(document, "\tvec3 specular = vec3(0.0, 0.0, 0.0);");
		gfx_add_line_to_document(document, "\tfloat depth = texture2D(elf_Texture0, elf_TexCoord).r*2.0-1.0;");
		gfx_add_line_to_document(document, "\tvec4 vertex = elf_InvProjectionMatrix*vec4(elf_TexCoord.x*2.0-1.0, elf_TexCoord.y*2.0-1.0, depth, 1.0);");
		gfx_add_line_to_document(document, "\tvertex = vec4(vertex.xyz/vertex.w, 1.0);");
		if(config->light == GFX_SPOT_LIGHT && config->textures & GFX_SHADOW_MAP)
		{
			gfx_add_line_to_document(document, "\tvec4 elf_ShadowCoord = elf_ShadowProjectionMatrix*vec4(vertex.xyz, 1.0);");
			gfx_add_line_to_document(document, "\tfloat shadow = shadow2DProj(elf_ShadowMap, elf_ShadowCoord).r;");
			gfx_add_line_to_document(document, "\tif(shadow < 0.001) discard;");
		}
		if(config->light != GFX_SUN_LIGHT)
		{
			gfx_add_line_to_document(document, "\tvec3 elf_LightDirection = elf_LightPosition-vertex.xyz;");
		}
		else
		{
			gfx_add_line_to_document(document, "\tvec3 elf_LightDirection = -elf_LightSpotDirection;");
		}
		gfx_add_line_to_document(document, "\tfloat elf_Distance = length(elf_LightDirection);");
		gfx_add_line_to_document(document, "\tvec3 N = vec3(texture2D(elf_Texture1, elf_TexCoord).rg, 0.0);");
		gfx_add_line_to_document(document, "\tN = normalize(vec3(N.x, N.y, sqrt(1.0-N.x*N.x-N.y*N.y)));");
		gfx_add_line_to_document(document, "\tvec3 L = normalize(elf_LightDirection);");
		if(config->light == GFX_SPOT_LIGHT)
		{
			gfx_add_line_to_document(document, "\tvec3 D = normalize(elf_LightSpotDirection);");
			gfx_add_line_to_document(document, "\tfloat cos_cur_angle = dot(-L, D);");
			gfx_add_line_to_document(document, "\tfloat cos_inner_cone_angle = elf_LightInnerConeCos;");
			gfx_add_line_to_document(document, "\tfloat cos_outer_cone_angle = elf_LightOuterConeCos;");
			gfx_add_line_to_document(document, "\tfloat cos_inner_minus_outer_cone_angle = cos_inner_cone_angle-cos_outer_cone_angle;");
			gfx_add_line_to_document(document, "\tfloat spot = 0.0;");
			gfx_add_line_to_document(document, "\tspot = clamp((cos_cur_angle-cos_outer_cone_angle) / cos_inner_minus_outer_cone_angle, 0.0, 1.0);");
		}
		gfx_add_line_to_document(document, "\tfloat att = clamp(1.0-max(elf_Distance-elf_LightDistance, 0.0)*elf_LightFadeSpeed, 0.0, 1.0);");
		gfx_add_line_to_document(document, "\tfloat lambert_term = max(dot(N, L), 0.0);");
		gfx_add_line_to_document(document, "\tif(lambert_term > 0.0)");
		gfx_add_line_to_document(document, "\t{");
		gfx_add_line_to_document(document, "\t\tvec3 E = normalize(-vertex.xyz);");
		gfx_add_line_to_document(document, "\t\tvec3 R = reflect(-L, N);");
		gfx_add_line_to_document(document, "\t\tvec4 spec = texture2D(elf_Texture2, elf_TexCoord);");
		gfx_add_line_to_document(document, "\t\tspec.a = spec.a*255.0;");
		gfx_add_line_to_document(document, "\t\tif(spec.a > 0.0)");
		gfx_add_line_to_document(document, "\t\t{");
		gfx_add_line_to_document(document, "\t\t\tfloat spec_strength = clamp(pow(max(dot(R, E), 0.0), spec.a), 0.0, 1.0);");
		gfx_add_line_to_document(document, "\t\t\tspecular = spec.rgb*elf_LightColor*spec_strength;");
		gfx_add_line_to_document(document, "\t\t}");
		gfx_add_line_to_document(document, "\t\tdiffuse = elf_LightColor*lambert_term;");
		gfx_add_line_to_document(document, "\t}");
		if(config->light == GFX_POINT_LIGHT || config->light == GFX_SPOT_LIGHT)
		{
			if(config->light == GFX_POINT_LIGHT) gfx_add_line_to_document(document, "\tfloat str = att;");
			if(config->light == GFX_SPOT_LIGHT) gfx_add_line_to_document(document, "\tfloat str = att*spot;");
			if(config->textures & GFX_SHADOW_MAP) gfx_add_line_to_document(document, "\tstr *= shadow;");
		}
		if(config->light != GFX_SUN_LIGHT)
		{
			gfx_add_line_to_document(document, "\tgl_FragData[0] = vec4(diffuse*str, 1.0);");
			gfx_add_line_to_document(document, "\tgl_FragData[1] = vec4(specular*str, 1.0);");
		}
		else
		{
			gfx_add_line_to_document(document, "\tgl_FragData[0] = vec4(diffuse, 1.0);");
			gfx_add_line_to_document(document, "\tgl_FragData[1] = vec4(specular, 1.0);");
		}
		gfx_add_line_to_document(document, "}");
	}

	frag_shdr = (char*)malloc(sizeof(char)*(gfx_get_document_chars(document)+1));
	gfx_document_to_buffer(document, frag_shdr);
	frag_shdr[gfx_get_document_chars(document)] = '\0';
	//elf_write_to_log("----------- FRAGMENT SHADER -----------\n");
	//elf_write_to_log(frag_shdr);

	// ----------------------------------------------------------- //

	gfx_destroy_document(document);

	shader_program = gfx_create_shader_program(vert_shdr, frag_shdr);

	free(vert_shdr);
	free(frag_shdr);

	if(shader_program)
	{
		memcpy(&shader_program->config, config, sizeof(gfx_shader_config));

		if(!driver->shader_programs) driver->shader_programs = shader_program;
		else
		{
			lshpr = driver->shader_programs;
			while(lshpr->next) lshpr = lshpr->next;
			lshpr->next = shader_program;
		}
	}

	return shader_program;
}

