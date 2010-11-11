
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

	file = fopen(gen->log, "a");
	if(file)
	{
		va_start(args, fmt);
		vfprintf(file, fmt, args);
		va_end(args);

		fclose(file);
	}

	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

void elfSetError(int code, const char* fmt, ...)
{
	va_list args;
	FILE* file;
	int len = -1;

	file = fopen(gen->log, "a");
	if(file)
	{

		va_start(args, fmt);
		len = vfprintf(file, fmt, args);
		va_end(args);

		fclose(file);
	}

	if(len > 0)
	{
		if(gen->errStr) free(gen->errStr);
		gen->errStr = malloc(sizeof(char)*(len+1));

		va_start(args, fmt);
		vsprintf(gen->errStr, fmt, args);
		va_end(args);

		gen->errStr[len] = '\0';
	}

	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	gen->errCode = code;
}

ELF_API void ELF_APIENTRY elfWriteLogLine(const char* str)
{
	FILE* file;

	file = fopen(gen->log, "a");
	if(file)
	{
		fprintf(file, "%s\n", (char*)str);
		fclose(file);
	}
}

