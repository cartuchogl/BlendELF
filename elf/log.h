
void elfStartLog()
{
	FILE* file;

	file = fopen(gen->log, "w");
	if(file) fclose(file);
}

void elfLogWrite(const char* fmt, ...)
{
	va_list args;
	FILE* file;

	va_start(args, fmt);

	file = fopen(gen->log, "a");
	if(file)
	{
		vfprintf(file, fmt, args);
		fclose(file);
	}

	vprintf(fmt, args);

	va_end(args);
}

void elfSetError(int code, const char* fmt, ...)
{
	va_list args;
	FILE* file;
	int len = -1;

	va_start(args, fmt);

	file = fopen(gen->log, "a");
	if(file)
	{
		len = vfprintf(file, fmt, args);
		fclose(file);
	}

	if(len > 0)
	{
		if(gen->errStr) elfDestroyString(gen->errStr);
		gen->errStr = malloc(sizeof(char)*(len+1));
		vsprintf(gen->errStr, fmt, args);
		gen->errStr[len] = '\0';
	}

	vprintf(fmt, args);

	gen->errCode = code;

	va_end(args);
}

ELF_API void ELF_APIENTRY elfWriteLogLine(const char* str)
{
	FILE* file;

	file = fopen(gen->log, "a");
	if(!file) fopen(gen->log, "w");

	if(file)
	{
		fprintf(file, "%s\n", (char*)str);
		fclose(file);
	}
}

