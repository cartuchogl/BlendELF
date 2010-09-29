
void gfxDraw_2dQuad(float x, float y, float width, float height)
{
	float* vertexBuffer;

	vertexBuffer = (float*)gfxGetVertexDataBuffer(driver->quadVertexData);

	vertexBuffer[0] = x;
	vertexBuffer[1] = y+height;
	vertexBuffer[2] = 0.0;
	vertexBuffer[3] = x;
	vertexBuffer[4] = y;
	vertexBuffer[5] = 0.0;
	vertexBuffer[6] = x+width;
	vertexBuffer[7] = y+height;
	vertexBuffer[8] = 0.0;
	vertexBuffer[9] = x+width;
	vertexBuffer[10] = y;
	vertexBuffer[11] = 0.0;

	gfxUpdateVertexData(driver->quadVertexData);
	gfxDrawVertexArray(driver->quadVertexArray, 4, GFX_TRIANGLE_STRIP);
}

void gfxDrawTextured_2dQuad(float x, float y, float width, float height)
{
	float* vertexBuffer;
	float* texCoordBuffer;

	vertexBuffer = (float*)gfxGetVertexDataBuffer(driver->quadVertexData);
	texCoordBuffer = (float*)gfxGetVertexDataBuffer(driver->quadTexCoordData);

	vertexBuffer[0] = x;
	vertexBuffer[1] = y+height;
	vertexBuffer[2] = 0.0;
	vertexBuffer[3] = x;
	vertexBuffer[4] = y;
	vertexBuffer[5] = 0.0;
	vertexBuffer[6] = x+width;
	vertexBuffer[7] = y+height;
	vertexBuffer[8] = 0.0;
	vertexBuffer[9] = x+width;
	vertexBuffer[10] = y;
	vertexBuffer[11] = 0.0;
	texCoordBuffer[0] = 0.0;
	texCoordBuffer[1] = 1.0;
	texCoordBuffer[2] = 0.0;
	texCoordBuffer[3] = 0.0;
	texCoordBuffer[4] = 1.0;
	texCoordBuffer[5] = 1.0;
	texCoordBuffer[6] = 1.0;
	texCoordBuffer[7] = 0.0;

	gfxUpdateVertexData(driver->quadVertexData);
	gfxUpdateVertexData(driver->quadTexCoordData);
	gfxDrawVertexArray(driver->quadVertexArray, 4, GFX_TRIANGLE_STRIP);
}

void gfxDrawTextured_2dQuadRegion(float x, float y, float width, float height, float tx, float ty, float twidth, float theight)
{
	float* vertexBuffer;
	float* texCoordBuffer;

	vertexBuffer = (float*)gfxGetVertexDataBuffer(driver->quadVertexData);
	texCoordBuffer = (float*)gfxGetVertexDataBuffer(driver->quadTexCoordData);

	vertexBuffer[0] = x;
	vertexBuffer[1] = y+height;
	vertexBuffer[2] = 0.0;
	vertexBuffer[3] = x;
	vertexBuffer[4] = y;
	vertexBuffer[5] = 0.0;
	vertexBuffer[6] = x+width;
	vertexBuffer[7] = y+height;
	vertexBuffer[8] = 0.0;
	vertexBuffer[9] = x+width;
	vertexBuffer[10] = y;
	vertexBuffer[11] = 0.0;
	texCoordBuffer[0] = tx;
	texCoordBuffer[1] = ty+theight;
	texCoordBuffer[2] = tx;
	texCoordBuffer[3] = ty;
	texCoordBuffer[4] = tx+twidth;
	texCoordBuffer[5] = ty+theight;
	texCoordBuffer[6] = tx+twidth;
	texCoordBuffer[7] = ty;

	gfxUpdateVertexData(driver->quadVertexData);
	gfxUpdateVertexData(driver->quadTexCoordData);
	gfxDrawVertexArray(driver->quadVertexArray, 4, GFX_TRIANGLE_STRIP);
}

void gfxDrawBoundingBox(float min[3], float max[3])
{
	float* vertexBuffer;

	vertexBuffer = (float*)gfxGetVertexDataBuffer(driver->bbVertexData);

	vertexBuffer[0] = min[0];
	vertexBuffer[1] = max[1];
	vertexBuffer[2] = max[2];
	vertexBuffer[3] = min[0];
	vertexBuffer[4] = max[1];
	vertexBuffer[5] = min[2];
	vertexBuffer[6] = min[0];
	vertexBuffer[7] = min[1];
	vertexBuffer[8] = max[2];
	vertexBuffer[9] = min[0];
	vertexBuffer[10] = min[1];
	vertexBuffer[11] = min[2];
	vertexBuffer[12] = max[0];
	vertexBuffer[13] = min[1];
	vertexBuffer[14] = max[2];
	vertexBuffer[15] = max[0];
	vertexBuffer[16] = min[1];
	vertexBuffer[17] = min[2];
	vertexBuffer[18] = max[0];
	vertexBuffer[19] = max[1];
	vertexBuffer[20] = max[2];
	vertexBuffer[21] = max[0];
	vertexBuffer[22] = max[1];
	vertexBuffer[23] = min[2];

	gfxUpdateVertexData(driver->bbVertexData);
	gfxSetVertexArray(driver->bbVertexArray);
	gfxDrawVertexIndex(driver->bbVertexIndex, GFX_TRIANGLES);
}

void gfxDrawLines(int count, gfxVertexData* vertices)
{
	if(count < 2) return;
	if(count > gfxGetVertexDataCount(vertices)/3) count -= count-(gfxGetVertexDataCount(vertices)/3);

	gfxSetVertexArrayData(driver->lineVertexArray, GFX_VERTEX, vertices);
	gfxDrawVertexArray(driver->lineVertexArray, count, GFX_LINES);
}

void gfxDrawLineLoop(int count, gfxVertexData* vertices)
{
	if(count < 2) return;
	if(count > gfxGetVertexDataCount(vertices)/3) count -= count-(gfxGetVertexDataCount(vertices)/3);

	gfxSetVertexArrayData(driver->lineVertexArray, GFX_VERTEX, vertices);
	gfxDrawVertexArray(driver->lineVertexArray, count, GFX_LINE_LOOP);
}

float gfxGetAbsoluteValue(float val)
{
	if(val < 0.0) return -val;
	return val;
}

unsigned char gfxIsAboutSame(float v1, float v2)
{
	if(gfxGetAbsoluteValue(v1-v2) < 0.0001) return GFX_TRUE;
	return GFX_FALSE;
}

void gfxDrawCircle(int vertices, float size)
{
	float step;
	int i;
	float* vertexBuffer;

	if(vertices < 3) return;
	if(vertices > GFX_MAX_CIRCLE_VERTICES) vertices = GFX_MAX_CIRCLE_VERTICES;

	if(vertices != driver->prevCircleVerticeCount || !gfxIsAboutSame(size, driver->prevCircleSize))
	{
		step = (360.0/((float)vertices))*GFX_PI_DIV_180;

		vertexBuffer = (float*)gfxGetVertexDataBuffer(driver->circleVertexData);

		vertexBuffer[0] = 0.0;
		vertexBuffer[1] = 0.0;
		vertexBuffer[2] = 0.0;

		for(i = 1; i < vertices+2; i++)
		{
			vertexBuffer[i*3] = -((float)sin((float)(step*(i-1))))*size;
			vertexBuffer[i*3+1] = ((float)cos((float)(step*(i-1))))*size;
			vertexBuffer[i*3+2] = 0.0;
		}
	}

	gfxUpdateVertexData(driver->circleVertexData);
	gfxDrawVertexArray(driver->circleVertexArray, vertices+2, GFX_TRIANGLE_FAN);

	driver->prevCircleVerticeCount = vertices;
}

