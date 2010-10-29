
char* elfReadNext(const char* text, int* pos)
{
	int start, end;
	char* str;

	start =* pos;

	while(text[start] == ' ' || text[start] == '\t' || text[start] == '\n' || text[start] == '\r')
	{
		(*pos)++;
		start++;
	}

	end = start;

	while(text[end] != ' ' && text[end] != '\t' && text[end] != '\n' && text[end] != '\r' && text[end] != '\0')
	{
		(*pos)++;
		end++;
	}

	if(start == end) return NULL;

	str = (char*)malloc(sizeof(char)*(end-start+1));
	memcpy(str, &text[start], sizeof(char)*(end-start));
	str[end-start] = '\0';

	return str;
}

char* elfReadSstString(const char* text, int* pos)
{
	return elfReadNext(text, pos);
}

float elfReadSstFloat(const char* text, int* pos)
{
	char* str;
	float val;

	str = elfReadNext(text, pos);
	val = (float)atof(str);
	free(str);

	return val;
}

void elfReadSstFloats(const char* text, int* pos, int n, float* params)
{
	int i;
	char* str;

	for(i = 0; i < n && (str = elfReadNext(text, pos)); i++)
	{
		params[i] = (float)atof(str);
		free(str);
	}
}

int elfReadSstInt(const char* text, int* pos)
{
	char* str;
	int val;

	str = elfReadNext(text, pos);
	val = atoi(str);
	free(str);

	return val;
}

void elfReadSstInts(const char* text, int* pos, int n, int* params)
{
	int i;
	char* str;

	for(i = 0; i < n && (str = elfReadNext(text, pos)); i++)
	{
		params[i] = atoi(str);
		free(str);
	}
}

unsigned char elfReadSstBool(const char* text, int* pos)
{
	char* str;
	unsigned char result;

	str = elfReadNext(text, pos);

	if(!strcmp(str, "FALSE")) result = ELF_FALSE;
	else result = ELF_TRUE;

	free(str);

	return result;
}

