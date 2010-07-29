
elf_vertice* elf_create_vertice()
{
	elf_vertice *vertice;

	vertice = (elf_vertice*)malloc(sizeof(elf_vertice));
	memset(vertice, 0x0, sizeof(elf_vertice));
	vertice->obj_type = ELF_VERTICE;
	vertice->obj_destr = elf_destroy_vertice;

	elf_inc_obj(ELF_VERTICE);

	return vertice;
}

void elf_destroy_vertice(void *data)
{
	elf_vertice *vertice = (elf_vertice*)data;

	free(vertice);

	elf_dec_obj(ELF_VERTICE);
}

void elf_set_vertice_position(elf_vertice *vertice, float x, float y, float z)
{
	vertice->position.x = x;
	vertice->position.y = y;
	vertice->position.z = z;
}

void elf_set_vertice_normal(elf_vertice *vertice, float x, float y, float z)
{
	vertice->normal.x = x;
	vertice->normal.y = y;
	vertice->normal.z = z;
}

void elf_set_vertice_tex_coord(elf_vertice *vertice, float u, float v)
{
	vertice->tex_coord.x = u;
	vertice->tex_coord.y = v;
}

elf_vec3f elf_get_vertice_position(elf_vertice *vertice)
{
	return vertice->position;
}

elf_vec3f elf_get_vertice_normal(elf_vertice *vertice)
{
	return vertice->normal;
}

elf_vec2f elf_get_vertice_tex_coord(elf_vertice *vertice)
{
	return vertice->tex_coord;
}

elf_face* elf_create_face()
{
	elf_face *face;

	face = (elf_face*)malloc(sizeof(elf_face));
	memset(face, 0x0, sizeof(elf_face));
	face->obj_type = ELF_FACE;
	face->obj_destr = elf_destroy_face;

	elf_inc_obj(ELF_FACE);

	return face;
}

void elf_destroy_face(void *data)
{
	elf_face *face = (elf_face*)data;

	free(face);

	elf_dec_obj(ELF_FACE);
}

int elf_get_face_v1(elf_face *face)
{
	return face->v1;
}

int elf_get_face_v2(elf_face *face)
{
	return face->v2;
}

int elf_get_face_v3(elf_face *face)
{
	return face->v3;
}

elf_mesh_data* elf_create_mesh_data()
{
	elf_mesh_data *mesh_data;

	mesh_data = (elf_mesh_data*)malloc(sizeof(elf_mesh_data));
	memset(mesh_data, 0x0, sizeof(elf_mesh_data));
	mesh_data->obj_type = ELF_MESH_DATA;
	mesh_data->obj_destr = elf_destroy_mesh_data;

	mesh_data->vertices = elf_create_list();
	mesh_data->faces = elf_create_list();

	elf_inc_ref((elf_object*)mesh_data->vertices);
	elf_inc_ref((elf_object*)mesh_data->faces);

	elf_inc_obj(ELF_MESH_DATA);

	return mesh_data;
}

void elf_destroy_mesh_data(void *data)
{
	elf_mesh_data *mesh_data = (elf_mesh_data*)data;

	elf_dec_ref((elf_object*)mesh_data->vertices);
	elf_dec_ref((elf_object*)mesh_data->faces);

	free(mesh_data);

	elf_dec_obj(ELF_MESH_DATA);
}

int elf_get_mesh_data_vertice_count(elf_mesh_data *mesh_data)
{
	return elf_get_list_length(mesh_data->vertices);
}

int elf_get_mesh_data_face_count(elf_mesh_data *mesh_data)
{
	return elf_get_list_length(mesh_data->faces);
}

void elf_add_vertice_to_mesh_data(elf_mesh_data *mesh_data, elf_vertice *vertice)
{
	elf_append_to_list(mesh_data->vertices, (elf_object*)vertice);
}

void elf_add_face_to_mesh_data(elf_mesh_data *mesh_data, int v1, int v2, int v3)
{
	elf_face *face;

	if(v1 < 0 || v2 < 0 || v3 < 0) return;
	if(v1 > elf_get_list_length(mesh_data->vertices) ||
		v2 > elf_get_list_length(mesh_data->vertices) ||
		v3 > elf_get_list_length(mesh_data->vertices)) return;

	face = elf_create_face();

	face->v1 = v1;
	face->v2 = v2;
	face->v3 = v3;

	elf_append_to_list(mesh_data->faces, (elf_object*)face);
}

elf_vertice* elf_get_vertice_from_mesh_data(elf_mesh_data *mesh_data, int idx)
{
	return (elf_vertice*)elf_get_item_from_list(mesh_data->vertices, idx);
}

elf_face* elf_get_face_from_mesh_data(elf_mesh_data *mesh_data, int idx)
{
	return (elf_face*)elf_get_item_from_list(mesh_data->faces, idx);
}

