
elf_image* elf_create_image()
{
	elf_image *image;

	image = (elf_image*)malloc(sizeof(elf_image));
	memset(image, 0x0, sizeof(elf_image));
	image->obj_type = ELF_IMAGE;
	image->obj_destr = elf_destroy_image;

	elf_inc_obj(ELF_IMAGE);

	return image;
}

elf_image* elf_create_empty_image(int width, int height, int bpp)
{
	elf_image *image;

	if(width < 0 || height < 0 || (bpp != 8 && bpp != 16 && bpp != 24 && bpp != 32)) return NULL;

	image = elf_create_image();

	image->width = width;
	image->height = height;
	image->bpp = bpp;

	image->data = (unsigned char*)malloc(sizeof(unsigned char)*width*height*(bpp/8));
	memset(image->data, 0x0, sizeof(unsigned char)*width*height*(bpp/8));

	return image;
}

elf_image* elf_create_image_from_file(const char *file_path)
{
	elf_image *image;
	FIBITMAP *in;
	int size_bytes;
	const char *type;

	type = strrchr(file_path, '.');
	if(!type)
	{
		elf_set_error(ELF_CANT_OPEN_FILE, "error: can't open file \"%s\"\n", file_path);
		return NULL;
	}

	if(strcmp(type, ".jpg") == 0)
		in = FreeImage_Load(FIF_JPEG, file_path, JPEG_ACCURATE);
	else if(strcmp(type, ".png") == 0)
		in = FreeImage_Load(FIF_PNG, file_path, 0);
	else if(strcmp(type, ".tga") == 0)
		in = FreeImage_Load(FIF_TARGA, file_path, 0);
	else if(strcmp(type, ".pcx") == 0)
		in = FreeImage_Load(FIF_PCX, file_path, 0);
	else if(strcmp(type, ".bmp") == 0)
		in = FreeImage_Load(FIF_BMP, file_path, 0);
	else if(strcmp(type, ".dds") == 0)
		in = FreeImage_Load(FIF_DDS, file_path, 0);
	else
	{
		elf_set_error(ELF_UNKNOWN_FORMAT, "error: can't load image \"%s\", unknown format\n", file_path);
		return NULL;
	}

	if(!in)
	{
		elf_set_error(ELF_CANT_OPEN_FILE, "error: can't open file \"%s\"\n", file_path);
		return NULL;
	}

	image = elf_create_image();

	image->width = FreeImage_GetWidth(in);
	image->height = FreeImage_GetHeight(in);
	image->bpp = FreeImage_GetBPP(in);

	if(image->width == 0 || image->height == 0)
	{
		elf_set_error(ELF_INVALID_SIZE, "error: \"%s\" has invalid size\n", file_path);
		FreeImage_Unload(in);
		free(image);
		return 0;
	}

	size_bytes = image->width*image->height*(image->bpp/8);

	image->data = (unsigned char*)malloc(size_bytes);

	FreeImage_ConvertToRawBits((BYTE*)image->data, in, image->width*(image->bpp/8), image->bpp,
		FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

	FreeImage_Unload(in);

	return image;
}

void elf_destroy_image(void *data)
{
	elf_image *image = (elf_image*)data;

	if(image->data) free(image->data);

	free(image);

	elf_dec_obj(ELF_IMAGE);
}

void elf_set_image_pixel(elf_image *image, int x, int y, float r, float g, float b, float a)
{
	int offset;

	if(x < 0 || x >= image->width || y < 0 || y >= image->height) return;

	offset = image->width*y+x;

	image->data[offset] = (unsigned char)(r*255);
	if(image->bpp == 16) image->data[offset+1] = (unsigned char)(g*255);
	if(image->bpp == 24) image->data[offset+2] = (unsigned char)(b*255);
	if(image->bpp == 32) image->data[offset+3] = (unsigned char)(a*255);
}

int elf_get_image_width(elf_image *image)
{
	return image->width;
}

int elf_get_image_height(elf_image *image)
{
	return image->height;
}

int elf_get_image_bits_per_pixel(elf_image *image)
{
	return image->bpp;
}

elf_color elf_get_image_pixel(elf_image *image, int x, int y)
{
	int offset;
	elf_color color;

	memset(&color, 0x0, sizeof(elf_color));

	if(x < 0 || x >= image->width || y < 0 || y >= image->height) return color;

	offset = image->width*y+x;

	color.r = (float)image->data[offset]/(float)255;
	if(image->bpp == 16) color.g = (float)image->data[offset+1]/(float)255;
	if(image->bpp == 24) color.b = (float)image->data[offset+2]/(float)255;
	if(image->bpp == 32) color.a = (float)image->data[offset+3]/(float)255;

	return color;
}


void* elf_get_image_data(elf_image *image)
{
	return image->data;
}

unsigned char elf_save_image_data(const char *file_path, int width, int height, unsigned char bpp, void *data)
{
	FIBITMAP *out;
	FIBITMAP *temp;
	const char *type;

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
		elf_set_error(ELF_CANT_OPEN_FILE, "error: can't save image \"%s\"\n", file_path);
		return ELF_FALSE;
	}

	type = strrchr(file_path, '.');
	if(strcmp(type, ".bmp") == 0)
		FreeImage_Save(FIF_BMP, out, file_path, 0);
	else if(strcmp(type, ".tga") == 0)
		FreeImage_Save(FIF_TARGA, out, file_path, 0);
	else if(strcmp(type, ".jpg") == 0)
		FreeImage_Save(FIF_JPEG, out, file_path, JPEG_QUALITYSUPERB);
	else if(strcmp(type, ".pcx") == 0)
		FreeImage_Save(FIF_PCX, out, file_path, 0);
	else if(strcmp(type, ".png") == 0)
		FreeImage_Save(FIF_PNG, out, file_path, 0);
	else if(strcmp(type, ".dds") == 0)
		FreeImage_Save(FIF_DDS, out, file_path, 0);
	else
	{
		FreeImage_Unload(out);
		elf_set_error(ELF_UNKNOWN_FORMAT, "error: can't save image \"%s\", unknown format\n", file_path);
		return ELF_FALSE;
	}

	FreeImage_Unload(out);

	return ELF_TRUE;
}

