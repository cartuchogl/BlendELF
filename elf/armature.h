
elf_bone* elf_create_bone(const char *name)
{
	elf_bone *bone;

	bone = (elf_bone*)malloc(sizeof(elf_bone));
	memset(bone, 0x0, sizeof(elf_bone));
	bone->obj_type = ELF_BONE;
	bone->obj_destr = elf_destroy_bone;

	if(name) bone->name = elf_create_string(name);

	bone->children = elf_create_list();
	elf_inc_ref((elf_object*)bone->children);

	elf_inc_obj(ELF_BONE);

	return bone;
}

void elf_destroy_bone(void *data)
{
	elf_bone *bone = (elf_bone*)data;

	if(bone->name) elf_destroy_string(bone->name);
	if(bone->frames) free(bone->frames);
	
	elf_dec_ref((elf_object*)bone->children);

	free(bone);

	elf_dec_obj(ELF_BONE);
}

elf_armature* elf_get_bone_armature(elf_bone *bone)
{
	return bone->armature;
}

elf_bone* elf_get_bone_parent(elf_bone *bone)
{
	return bone->parent;
}

elf_bone* elf_get_bone_child_by_name(elf_bone *bone, const char *name)
{
	elf_bone *cbone;

	for(cbone = (elf_bone*)elf_begin_list(bone->children); cbone;
		cbone = (elf_bone*)elf_next_in_list(bone->children))
	{
		if(!strcmp(cbone->name, name))
		{
			return cbone;
		}
	}

	return NULL;
}

elf_bone* elf_get_bone_child_by_id(elf_bone *bone, int id)
{
	elf_bone *cbone;

	for(cbone = (elf_bone*)elf_begin_list(bone->children); cbone;
		cbone = (elf_bone*)elf_next_in_list(bone->children))
	{
		if(cbone->id == id)
		{
			return cbone;
		}
	}

	return NULL;
}

elf_bone* elf_get_bone_child_by_index(elf_bone *bone, int idx)
{
	return (elf_bone*)elf_get_item_from_list(bone->children, idx);
}

elf_vec3f elf_get_bone_position(elf_bone *bone)
{
	return bone->cur_pos;
}

elf_vec3f elf_get_bone_rotation(elf_bone *bone)
{
	elf_vec3f result;

	gfx_qua_to_euler(&bone->cur_qua.x, &result.x);

	return result;
}

elf_vec4f elf_get_bone_orientation(elf_bone *bone)
{
	return bone->qua;
}

void elf_set_bone_armature(elf_bone *bone, elf_armature *armature)
{
	elf_bone *cbone;

	bone->armature = armature;

	for(cbone = (elf_bone*)elf_begin_list(bone->children); cbone;
		cbone = (elf_bone*)elf_next_in_list(bone->children))
	{
		elf_set_bone_armature(cbone, armature);
	}
}

int elf_get_bone_max_id(elf_bone *bone)
{
	int max_id;
	int cur_max_id;
	elf_bone *cbone;

	max_id = bone->id;

	for(cbone = (elf_bone*)elf_begin_list(bone->children); cbone;
		cbone = (elf_bone*)elf_next_in_list(bone->children))
	{
		cur_max_id = elf_get_bone_max_id(cbone);
		if(cur_max_id > max_id) max_id = cur_max_id;
	}

	return max_id;
}

void elf_populate_bone_array(elf_bone *bone, elf_bone **bones)
{
	elf_bone *cbone;

	bones[bone->id] = bone;

	for(cbone = (elf_bone*)elf_begin_list(bone->children); cbone;
		cbone = (elf_bone*)elf_next_in_list(bone->children))
	{
		elf_populate_bone_array(cbone, bones);
	}
}

void elf_update_armature_bones(elf_armature *armature)
{
	int max_id;
	int cur_max_id;
	elf_bone *cbone;

	max_id = 0;
	for(cbone = (elf_bone*)elf_begin_list(armature->root_bones); cbone;
		cbone = (elf_bone*)elf_next_in_list(armature->root_bones))
	{
		cur_max_id = elf_get_bone_max_id(cbone);
		if(cur_max_id > max_id) max_id = cur_max_id;
	}

	if(armature->bones) free(armature->bones);
	armature->bones = (elf_bone**)malloc(sizeof(elf_bone*)*(max_id+1));
	memset(armature->bones, 0x0, sizeof(elf_bone*)*(max_id+1));

	armature->bone_count = max_id+1;

	for(cbone = (elf_bone*)elf_begin_list(armature->root_bones); cbone;
		cbone = (elf_bone*)elf_next_in_list(armature->root_bones))
	{
		elf_populate_bone_array(cbone, armature->bones);
	}
}

elf_armature* elf_create_armature(const char *name)
{
	elf_armature *armature;

	armature = (elf_armature*)malloc(sizeof(elf_armature));
	memset(armature, 0x0, sizeof(elf_armature));
	armature->obj_type = ELF_ARMATURE;
	armature->obj_destr = elf_destroy_armature;

	armature->root_bones = elf_create_list();
	elf_inc_ref((elf_object*)armature->root_bones);

	if(name) armature->name = elf_create_string(name);

	armature->id = ++gen->armature_id_counter;

	elf_inc_obj(ELF_ARMATURE);

	return armature;
}

void elf_deform_entity_with_armature(elf_armature *armature, elf_entity *entity, float frame)
{
	int i, j;
	int id;
	float temp_vec1[3];
	float temp_vec2[3];
	int cid;
	int nid;
	float t;
	float temp_qua[4];
	float *vertex_buffer;
	float *normal_buffer;
	float *orig_vertex_buffer;
	float *orig_normal_buffer;
	elf_bone *bone;
	elf_model *model;

	model = elf_get_entity_model(entity);

	if(!model || !armature->bone_count || !model->boneids || !model->weights) return;

	cid = ((int)frame)-1;
	if(cid < 0) cid = 0;
	nid = cid+1;
	if(frame > armature->frame_count) cid = nid = armature->frame_count-1;
	t = frame-((int)frame);

	armature->cur_frame = frame;
	if(armature->cur_frame > armature->frame_count) armature->cur_frame = armature->frame_count;

	for(i = 0; i < armature->bone_count; i++)
	{
		bone = armature->bones[i];
		if(!bone) continue;

		bone->cur_offset_pos.x = bone->frames[cid].offset_pos.x+(bone->frames[nid].offset_pos.x-bone->frames[cid].offset_pos.x)*t;
		bone->cur_offset_pos.y = bone->frames[cid].offset_pos.y+(bone->frames[nid].offset_pos.y-bone->frames[cid].offset_pos.y)*t;
		bone->cur_offset_pos.z = bone->frames[cid].offset_pos.z+(bone->frames[nid].offset_pos.z-bone->frames[cid].offset_pos.z)*t;
		bone->cur_pos.x = bone->pos.x+bone->cur_offset_pos.x;
		bone->cur_pos.y = bone->pos.y+bone->cur_offset_pos.y;
		bone->cur_pos.z = bone->pos.z+bone->cur_offset_pos.z;

		gfx_qua_slerp(&bone->frames[cid].offset_qua.x, &bone->frames[nid].offset_qua.x, t, &bone->cur_offset_qua.x);
		gfx_mul_qua_qua(&bone->qua.x, &bone->cur_offset_qua.x, temp_qua);
		memcpy(&bone->cur_qua.x, temp_qua, sizeof(float)*4);
	}

	if(!entity->vertices)
	{
		entity->vertices = gfx_create_vertex_data(3*model->vertice_count, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
		gfx_inc_ref((gfx_object*)entity->vertices);
	}

	if(!entity->normals)
	{
		entity->normals = gfx_create_vertex_data(3*model->vertice_count, GFX_FLOAT, GFX_VERTEX_DATA_DYNAMIC);
		gfx_inc_ref((gfx_object*)entity->normals);
	}

	vertex_buffer = (float*)gfx_get_vertex_data_buffer(entity->vertices);
	normal_buffer = (float*)gfx_get_vertex_data_buffer(entity->normals);
	orig_vertex_buffer = (float*)gfx_get_vertex_data_buffer(model->vertices);
	orig_normal_buffer = (float*)gfx_get_vertex_data_buffer(model->normals);

	for(i = 0; i < model->vertice_count; i++)
	{
		memset(&vertex_buffer[i*3], 0x0, sizeof(float)*3);
		memset(&normal_buffer[i*3], 0x0, sizeof(float)*3);

		for(j = 0; j < 4; j++)
		{
			id = model->boneids[i*4+j];

			if(id < 0 || id > (int)armature->bone_count-1 || !(bone = armature->bones[id])) continue;

			memcpy(temp_vec1, &orig_vertex_buffer[i*3], sizeof(float)*3);
			temp_vec1[0] -= bone->pos.x;
			temp_vec1[1] -= bone->pos.y;
			temp_vec1[2] -= bone->pos.z;
			gfx_mul_qua_vec(&bone->cur_offset_qua.x, temp_vec1, temp_vec2);
			temp_vec2[0] += bone->pos.x;
			temp_vec2[1] += bone->pos.y;
			temp_vec2[2] += bone->pos.z;
			temp_vec2[0] += bone->cur_offset_pos.x;
			temp_vec2[1] += bone->cur_offset_pos.y;
			temp_vec2[2] += bone->cur_offset_pos.z;

			vertex_buffer[i*3] += temp_vec2[0]*model->weights[i*4+j];
			vertex_buffer[i*3+1] += temp_vec2[1]*model->weights[i*4+j];
			vertex_buffer[i*3+2] += temp_vec2[2]*model->weights[i*4+j];

			gfx_mul_qua_vec(&bone->cur_offset_qua.x, &orig_normal_buffer[i*3], temp_vec1);

			normal_buffer[i*3] += temp_vec1[0]*model->weights[i*4+j];
			normal_buffer[i*3+1] += temp_vec1[1]*model->weights[i*4+j];
			normal_buffer[i*3+2] += temp_vec1[2]*model->weights[i*4+j];
		}
	}
	
	gfx_update_vertex_data(entity->vertices);
	gfx_update_vertex_data(entity->normals);
}

void elf_destroy_armature(void *data)
{
	elf_armature *armature = (elf_armature*)data;

	if(armature->name) elf_destroy_string(armature->name);
	if(armature->file_path) elf_destroy_string(armature->file_path);

	elf_dec_ref((elf_object*)armature->root_bones);

	if(armature->bones) free(armature->bones);

	free(armature);

	elf_dec_obj(ELF_ARMATURE);
}

elf_bone* elf_get_bone_from_armature_by_name(const char *name, elf_armature *armature)
{
	int i;

	for(i = 0; i < (int)armature->bones; i++)
	{
		if(armature->bones[i] && !strcmp(armature->bones[i]->name, name))
		{
			return armature->bones[i];
		}
	}

	return NULL;
}

elf_bone* elf_get_bone_from_armature_by_id(int id, elf_armature *armature)
{
	if(id < 0 || id > armature->bone_count-1) return NULL;

	return armature->bones[id];
}

void elf_add_root_bone_to_armature(elf_armature *armature, elf_bone *bone)
{
	if(bone->parent) return;
	elf_append_to_list(armature->root_bones, (elf_object*)bone);
	elf_set_bone_armature(bone, armature);
	elf_update_armature_bones(armature);
}

void elf_draw_bone_hierarchy(elf_bone *bone, gfx_shader_params *shader_params)
{
	elf_bone *cbone;
	float min[3];
	float max[3];
	elf_vec3f pos;
	elf_vec3f axis;
	elf_vec4f orient;
	float *vertex_buffer;

	pos = bone->cur_pos;
	orient = bone->cur_qua;

	vertex_buffer = (float*)gfx_get_vertex_data_buffer(eng->lines);

	vertex_buffer[0] = pos.x;
	vertex_buffer[1] = pos.y;
	vertex_buffer[2] = pos.z;

	axis.x = 0.2; axis.y = 0.0; axis.z = 0.0;
	axis = elf_mul_qua_vec3f(orient, axis);
	vertex_buffer[3] = pos.x+axis.x;
	vertex_buffer[4] = pos.y+axis.y;
	vertex_buffer[5] = pos.z+axis.z;

	shader_params->render_params.blend_mode = GFX_NONE;
	gfx_set_color(&shader_params->material_params.color, 0.0, 0.0, 1.0, 1.0);
	gfx_set_shader_params(shader_params);

	gfx_draw_lines(2, eng->lines);

	axis.x = 0.0; axis.y = 0.2; axis.z = 0.0;
	axis = elf_mul_qua_vec3f(orient, axis);
	vertex_buffer[3] = pos.x+axis.x;
	vertex_buffer[4] = pos.y+axis.y;
	vertex_buffer[5] = pos.z+axis.z;

	gfx_set_color(&shader_params->material_params.color, 0.0, 1.0, 0.0, 1.0);
	gfx_set_shader_params(shader_params);

	gfx_draw_lines(2, eng->lines);

	axis.x = 0.0; axis.y = 0.0; axis.z = 0.2;
	axis = elf_mul_qua_vec3f(orient, axis);
	vertex_buffer[3] = pos.x+axis.x;
	vertex_buffer[4] = pos.y+axis.y;
	vertex_buffer[5] = pos.z+axis.z;

	gfx_set_color(&shader_params->material_params.color, 1.0, 0.0, 0.0, 1.0);
	gfx_set_shader_params(shader_params);

	gfx_draw_lines(2, eng->lines);

	min[0] = pos.x-0.05;
	min[1] = pos.y-0.05;
	min[2] = pos.z-0.05;

	max[0] = pos.x+0.05;
	max[1] = pos.y+0.05;
	max[2] = pos.z+0.05;

	shader_params->render_params.blend_mode = GFX_ADD;
	gfx_set_color(&shader_params->material_params.color, 1.0, 0.4, 0.2, 1.0);
	gfx_set_shader_params(shader_params);

	gfx_draw_bounding_box(min, max);

	for(cbone = (elf_bone*)elf_begin_list(bone->children); cbone;
		cbone = (elf_bone*)elf_next_in_list(bone->children))
	{
		vertex_buffer[3] = cbone->cur_pos.x;
		vertex_buffer[4] = cbone->cur_pos.y;
		vertex_buffer[5] = cbone->cur_pos.z;

		gfx_draw_lines(2, eng->lines);

		elf_draw_bone_hierarchy(cbone, shader_params);
	}
}

void elf_draw_armature_debug(elf_armature *armature, gfx_shader_params *shader_params)
{
	elf_bone *bone;

	for(bone = (elf_bone*)elf_begin_list(armature->root_bones); bone;
		bone = (elf_bone*)elf_next_in_list(armature->root_bones))
	{
		elf_draw_bone_hierarchy(bone, shader_params);
	}
}

