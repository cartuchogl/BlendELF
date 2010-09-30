
ELF_API elfTimer* ELF_APIENTRY elfCreateTimer()
{
	elfTimer* timer;

	timer = (elfTimer*)malloc(sizeof(elfTimer));
	memset(timer, 0x0, sizeof(elfTimer));
	timer->objType = ELF_TIMER;
	timer->objDestr = elfDestroyTimer;

	elfIncObj(ELF_TIMER);

	return timer;
}

void elfDestroyTimer(void* data)
{
	elfTimer* timer = (elfTimer*)data;

	free(timer);

	elfDecObj(ELF_TIMER);
}

ELF_API void ELF_APIENTRY elfStartTimer(elfTimer* timer)
{
	timer->start = elfGetTime();
}

ELF_API double ELF_APIENTRY elfGetElapsedTime(elfTimer* timer)
{
	if(!timer->start) return 0.0;
	return elfGetTime()-timer->start;
}

