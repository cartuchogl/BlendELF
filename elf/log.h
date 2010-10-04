
void elfStartLog(const char* text)
{
	FILE* file;

	file = fopen(gen->log, "w");
	if(!file) return;

	fwrite(text, sizeof(char), strlen(text), file);
	fclose(file);
}

void elfLogWrite(const char* fmt, ...)
{
	va_list list;
	const char* p,* s;
	int d;
	double f;
	FILE* file;

	va_start(list, fmt);

	file = fopen(gen->log, "a");
	if(!file) fopen(gen->log, "w");

	for(p = fmt;* p; ++p)
	{
		if(*p != '%')
		{
			putc(*p, stdout);
			if(file) putc(*p, file);
		}
		else
		{
			switch(*++p)
			{
				case 's':
					s = va_arg(list, char*);
					if(s == NULL) continue;
					printf("%s", s);
					if(file) fprintf(file, "%s", s);
					continue;
				case 'd':
					d = va_arg(list, int);
					printf("%d", d);
					if(file) fprintf(file, "%d", d);
					continue;
				case 'f':
					f = va_arg(list, double);
					printf("%f", f);
					if(file) fprintf(file, "%f", f);
					continue;
			}
		}
	}

	if(file) fclose(file);
}

void elfSetError(int code, const char* fmt, ...)
{
	va_list list;
	const char* p,* s;
	int d;
	double f;
	char* errStr;
	char* tmpStr;
	char num[32];
	FILE* file;

	va_start(list, fmt);

	file = fopen(gen->log, "a");
	if(!file) fopen(gen->log, "w");

	errStr = elfCreateString("");

	for(p = fmt;* p; ++p)
	{
		if(*p != '%')
		{
			putc(*p, stdout);
			if(file) putc(*p, file);
			tmpStr = elfAppendCharToString(errStr,* p);
			elfDestroyString(errStr);
			errStr = tmpStr;
		}
		else
		{
			switch(*++p)
			{
				case 's':
					s = va_arg(list, char*);
					if(s == NULL) continue;
					printf("%s", s);
					if(file) fprintf(file, "%s", s);

					tmpStr = elfMergeStrings(errStr, s);
					elfDestroyString(errStr);
					errStr = tmpStr;
					continue;
				case 'd':
					d = va_arg(list, int);
					printf("%d", d);
					if(file) fprintf(file, "%d", d);

					memset(num, 0x0, sizeof(char)*32);
					sprintf(num, "%d", d);

					tmpStr = elfMergeStrings(errStr, num);
					elfDestroyString(errStr);
					errStr = tmpStr;
					continue;
				case 'f':
					f = va_arg(list, double);
					printf("%f", f);
					if(file) fprintf(file, "%f", f);

					memset(num, 0x0, sizeof(char)*32);
					sprintf(num, "%f", f);

					tmpStr = elfMergeStrings(errStr, num);
					elfDestroyString(errStr);
					errStr = tmpStr;
					continue;
			}
		}
	}

	gen->errCode = code;

	if(gen->errStr) elfDestroyString(gen->errStr);
	gen->errStr = elfCreateString(errStr);
	elfDestroyString(errStr);

	if(file) fclose(file);
}

void elfSetErrorNoSave(int code, const char* fmt, ...)
{
	va_list list;
	const char* p,* s;
	int d;
	double f;
	char* errStr;
	char* tmpStr;
	char num[32];

	va_start(list, fmt);

	errStr = elfCreateString("");

	for(p = fmt;* p; ++p)
	{
		if(*p != '%')
		{
			putc(*p, stdout);

			tmpStr = elfAppendCharToString(errStr,* p);
			elfDestroyString(errStr);
			errStr = tmpStr;
		}
		else
		{
			switch(*++p)
			{
				case 's':
					s = va_arg(list, char*);
					if(s == NULL) continue;
					printf("%s", s);

					tmpStr = elfMergeStrings(errStr, s);
					elfDestroyString(errStr);
					errStr = tmpStr;
					continue;
				case 'd':
					d = va_arg(list, int);
					printf("%d", d);

					memset(num, 0x0, sizeof(char)*32);
					sprintf(num, "%d", d);

					tmpStr = elfMergeStrings(errStr, num);
					elfDestroyString(errStr);
					errStr = tmpStr;
					continue;
				case 'f':
					f = va_arg(list, double);
					printf("%f", f);

					memset(num, 0x0, sizeof(char)*32);
					sprintf(num, "%f", f);

					tmpStr = elfMergeStrings(errStr, num);
					elfDestroyString(errStr);
					errStr = tmpStr;
					continue;
			}
		}
	}

	gen->errCode = code;

	if(gen->errStr) elfDestroyString(gen->errStr);
	gen->errStr = elfCreateString(errStr);
	elfDestroyString(errStr);
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

