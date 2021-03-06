
elfImage* elfCreateImage()
{
	elfImage* image;

	image = (elfImage*)malloc(sizeof(elfImage));
	memset(image, 0x0, sizeof(elfImage));
	image->objType = ELF_IMAGE;
	image->objDestr = elfDestroyImage;

	elfIncObj(ELF_IMAGE);

	return image;
}

ELF_API elfImage* ELF_APIENTRY elfCreateEmptyImage(int width, int height, int bpp)
{
	elfImage* image;

	if(width < 0 || height < 0 || (bpp != 8 && bpp != 16 && bpp != 24 && bpp != 32)) return NULL;

	image = elfCreateImage();

	image->width = width;
	image->height = height;
	image->bpp = bpp;

	image->data = (unsigned char*)malloc(sizeof(unsigned char)*width*height*(bpp/8));
	memset(image->data, 0x0, sizeof(unsigned char)*width*height*(bpp/8));

	return image;
}

ELF_API elfImage* ELF_APIENTRY elfCreateImageFromFile(const char* filePath)
{
	elfImage* image;
	FIBITMAP* in;
	int sizeBytes;
	const char* type;

	type = strrchr(filePath, '.');
	if(!type)
	{
		elfSetError(ELF_CANT_OPEN_FILE, "error: can't open file \"%s\"\n", filePath);
		return NULL;
	}

	if(strcmp(type, ".jpg") == 0)
		in = FreeImage_Load(FIF_JPEG, filePath, JPEG_ACCURATE);
	else if(strcmp(type, ".png") == 0)
		in = FreeImage_Load(FIF_PNG, filePath, 0);
	else if(strcmp(type, ".tga") == 0)
		in = FreeImage_Load(FIF_TARGA, filePath, 0);
	else if(strcmp(type, ".pcx") == 0)
		in = FreeImage_Load(FIF_PCX, filePath, 0);
	else if(strcmp(type, ".bmp") == 0)
		in = FreeImage_Load(FIF_BMP, filePath, 0);
	else if(strcmp(type, ".dds") == 0)
		in = FreeImage_Load(FIF_DDS, filePath, 0);
	else
	{
		elfSetError(ELF_UNKNOWN_FORMAT, "error: can't load image \"%s\", unknown format\n", filePath);
		return NULL;
	}

	if(!in)
	{
		elfSetError(ELF_CANT_OPEN_FILE, "error: can't open file \"%s\"\n", filePath);
		return NULL;
	}

	image = elfCreateImage();

	image->width = FreeImage_GetWidth(in);
	image->height = FreeImage_GetHeight(in);
	image->bpp = FreeImage_GetBPP(in);

	if(image->width == 0 || image->height == 0)
	{
		elfSetError(ELF_INVALID_SIZE, "error: \"%s\" has invalid size\n", filePath);
		FreeImage_Unload(in);
		elfDestroyImage(image);
		return 0;
	}

	sizeBytes = image->width*image->height*(image->bpp/8);

	image->data = (unsigned char*)malloc(sizeBytes);

	FreeImage_ConvertToRawBits((BYTE*)image->data, in, image->width*(image->bpp/8), image->bpp,
		FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

	FreeImage_Unload(in);

	return image;
}

void elfDestroyImage(void* data)
{
	elfImage* image = (elfImage*)data;

	if(image->data) free(image->data);

	free(image);

	elfDecObj(ELF_IMAGE);
}

ELF_API void ELF_APIENTRY elfSetImagePixel(elfImage* image, int x, int y, float r, float g, float b, float a)
{
	int offset;

	if(x < 0 || x >= image->width || y < 0 || y >= image->height) return;

	offset = image->width*y+x;

	image->data[offset] = (unsigned char)(r*255);
	if(image->bpp == 16) image->data[offset+1] = (unsigned char)(g*255);
	if(image->bpp == 24) image->data[offset+2] = (unsigned char)(b*255);
	if(image->bpp == 32) image->data[offset+3] = (unsigned char)(a*255);
}

ELF_API int ELF_APIENTRY elfGetImageWidth(elfImage* image)
{
	return image->width;
}

ELF_API int ELF_APIENTRY elfGetImageHeight(elfImage* image)
{
	return image->height;
}

ELF_API int ELF_APIENTRY elfGetImageBitsPerPixel(elfImage* image)
{
	return image->bpp;
}

ELF_API elfColor ELF_APIENTRY elfGetImagePixel(elfImage* image, int x, int y)
{
	int offset;
	elfColor color;

	memset(&color, 0x0, sizeof(elfColor));

	if(x < 0 || x >= image->width || y < 0 || y >= image->height) return color;

	offset = image->width*y+x;

	color.r = (float)image->data[offset]/(float)255;
	if(image->bpp == 16) color.g = (float)image->data[offset+1]/(float)255;
	if(image->bpp == 24) color.b = (float)image->data[offset+2]/(float)255;
	if(image->bpp == 32) color.a = (float)image->data[offset+3]/(float)255;

	return color;
}


void* elfGetImageData(elfImage* image)
{
	return image->data;
}

unsigned char elfSaveImageData(const char* filePath, int width, int height, unsigned char bpp, void* data)
{
	FIBITMAP* out;
	FIBITMAP* temp;
	const char* type;

	if(width < 1 || height < 1 || bpp%8 != 0 || bpp > 32 || !data) return ELF_FALSE;

	out = FreeImage_ConvertFromRawBits((BYTE*)data, width, height, width*(bpp/8), bpp, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

	// the jpg freeimage plugin can't save a 32 bit map, and who knows what other
	// plugins can't, so for now, this should fix it...
	if(bpp != 24)
	{
		temp = FreeImage_ConvertTo24Bits(out);
		FreeImage_Unload(out);
		out = temp;
	}

	if(!out)
	{
		elfSetError(ELF_CANT_OPEN_FILE, "error: can't save image \"%s\"\n", filePath);
		return ELF_FALSE;
	}

	type = strrchr(filePath, '.');
	if(strcmp(type, ".bmp") == 0)
		FreeImage_Save(FIF_BMP, out, filePath, 0);
	else if(strcmp(type, ".tga") == 0)
		FreeImage_Save(FIF_TARGA, out, filePath, 0);
	else if(strcmp(type, ".jpg") == 0)
		FreeImage_Save(FIF_JPEG, out, filePath, JPEG_QUALITYSUPERB);
	else if(strcmp(type, ".pcx") == 0)
		FreeImage_Save(FIF_PCX, out, filePath, 0);
	else if(strcmp(type, ".png") == 0)
		FreeImage_Save(FIF_PNG, out, filePath, 0);
	else if(strcmp(type, ".dds") == 0)
		FreeImage_Save(FIF_DDS, out, filePath, 0);
	else
	{
		FreeImage_Unload(out);
		elfSetError(ELF_UNKNOWN_FORMAT, "error: can't save image \"%s\", unknown format\n", filePath);
		return ELF_FALSE;
	}

	FreeImage_Unload(out);

	return ELF_TRUE;
}

