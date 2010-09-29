
elfVertice* elfCreateVertice()
{
	elfVertice* vertice;

	vertice = (elfVertice*)malloc(sizeof(elfVertice));
	memset(vertice, 0x0, sizeof(elfVertice));
	vertice->objType = ELF_VERTICE;
	vertice->objDestr = elfDestroyVertice;

	elfIncObj(ELF_VERTICE);

	return vertice;
}

void elfDestroyVertice(void* data)
{
	elfVertice* vertice = (elfVertice*)data;

	free(vertice);

	elfDecObj(ELF_VERTICE);
}

void elfSetVerticePosition(elfVertice* vertice, float x, float y, float z)
{
	vertice->position.x = x;
	vertice->position.y = y;
	vertice->position.z = z;
}

void elfSetVerticeNormal(elfVertice* vertice, float x, float y, float z)
{
	vertice->normal.x = x;
	vertice->normal.y = y;
	vertice->normal.z = z;
}

void elfSetVerticeTexCoord(elfVertice* vertice, float u, float v)
{
	vertice->texCoord.x = u;
	vertice->texCoord.y = v;
}

elfVec3f elfGetVerticePosition(elfVertice* vertice)
{
	return vertice->position;
}

elfVec3f elfGetVerticeNormal(elfVertice* vertice)
{
	return vertice->normal;
}

elfVec2f elfGetVerticeTexCoord(elfVertice* vertice)
{
	return vertice->texCoord;
}

elfFace* elfCreateFace()
{
	elfFace* face;

	face = (elfFace*)malloc(sizeof(elfFace));
	memset(face, 0x0, sizeof(elfFace));
	face->objType = ELF_FACE;
	face->objDestr = elfDestroyFace;

	elfIncObj(ELF_FACE);

	return face;
}

void elfDestroyFace(void* data)
{
	elfFace* face = (elfFace*)data;

	free(face);

	elfDecObj(ELF_FACE);
}

int elfGetFaceV1(elfFace* face)
{
	return face->v1;
}

int elfGetFaceV2(elfFace* face)
{
	return face->v2;
}

int elfGetFaceV3(elfFace* face)
{
	return face->v3;
}

elfMeshData* elfCreateMeshData()
{
	elfMeshData* meshData;

	meshData = (elfMeshData*)malloc(sizeof(elfMeshData));
	memset(meshData, 0x0, sizeof(elfMeshData));
	meshData->objType = ELF_MESH_DATA;
	meshData->objDestr = elfDestroyMeshData;

	meshData->vertices = elfCreateList();
	meshData->faces = elfCreateList();

	elfIncRef((elfObject*)meshData->vertices);
	elfIncRef((elfObject*)meshData->faces);

	elfIncObj(ELF_MESH_DATA);

	return meshData;
}

void elfDestroyMeshData(void* data)
{
	elfMeshData* meshData = (elfMeshData*)data;

	elfDecRef((elfObject*)meshData->vertices);
	elfDecRef((elfObject*)meshData->faces);

	free(meshData);

	elfDecObj(ELF_MESH_DATA);
}

int elfGetMeshDataVerticeCount(elfMeshData* meshData)
{
	return elfGetListLength(meshData->vertices);
}

int elfGetMeshDataFaceCount(elfMeshData* meshData)
{
	return elfGetListLength(meshData->faces);
}

void elfAddVerticeToMeshData(elfMeshData* meshData, elfVertice* vertice)
{
	elfAppendToList(meshData->vertices, (elfObject*)vertice);
}

void elfAddFaceToMeshData(elfMeshData* meshData, int v1, int v2, int v3)
{
	elfFace* face;

	if(v1 < 0 || v2 < 0 || v3 < 0) return;
	if(v1 > elfGetListLength(meshData->vertices) ||
		v2 > elfGetListLength(meshData->vertices) ||
		v3 > elfGetListLength(meshData->vertices)) return;

	face = elfCreateFace();

	face->v1 = v1;
	face->v2 = v2;
	face->v3 = v3;

	elfAppendToList(meshData->faces, (elfObject*)face);
}

elfVertice* elfGetVerticeFromMeshData(elfMeshData* meshData, int idx)
{
	return (elfVertice*)elfGetItemFromList(meshData->vertices, idx);
}

elfFace* elfGetFaceFromMeshData(elfMeshData* meshData, int idx)
{
	return (elfFace*)elfGetItemFromList(meshData->faces, idx);
}

