
ELF_API elfFramePlayer* ELF_APIENTRY elfCreateFramePlayer()
{
	elfFramePlayer* player;

	player = (elfFramePlayer*)malloc(sizeof(elfFramePlayer));
	memset(player, 0x0, sizeof(elfFramePlayer));
	player->objType = ELF_FRAME_PLAYER;
	player->objDestr = elfDestroyFramePlayer;

	player->curFrame = 1.0f;

	elfIncObj(ELF_FRAME_PLAYER);
	
	return player;
}

void elfDestroyFramePlayer(void* data)
{
	elfFramePlayer* player = (elfFramePlayer*)data;

	free(player);

	elfDecObj(ELF_FRAME_PLAYER);
}

ELF_API void ELF_APIENTRY elfUpdateFramePlayer(elfFramePlayer* player)
{
	if(player->end > 1.0f && !player->pause)
	{
		player->curFrame += player->speed*elfGetSync();
		if(player->loop)
		{
			if(player->curFrame > player->end+1) elfSetFramePlayerFrame(player, player->start);
			else elfSetFramePlayerFrame(player, player->curFrame);
		}
		else
		{
			if(player->curFrame > player->end)
			{
				elfSetFramePlayerFrame(player, player->curFrame);
				elfStopFramePlayer(player);
			}
			else elfSetFramePlayerFrame(player, player->curFrame);
		}
	}
}

ELF_API void ELF_APIENTRY elfSetFramePlayerFrame(elfFramePlayer* player, float frame)
{
	player->curFrame = frame;
	if(player->curFrame < 1.0f) player->curFrame = 1.0f;

	if(elfIsFramePlayerPlaying(player) || elfIsFramePlayerPaused(player))
	{
		if(player->curFrame < player->start) player->curFrame = player->start;
		if(player->loop)
		{
			if(player->curFrame > player->end+1) player->curFrame = player->start;
		}
		else
		{
			if(player->curFrame > player->end) player->curFrame = player->end;
		}
	}

	if(player->callback) player->callback(player);
}

ELF_API void ELF_APIENTRY elfPlayFramePlayer(elfFramePlayer* player, float start, float end, float speed)
{
	player->start = start;
	player->end = end;
	if(player->start < 1.0f) player->start = 1.0f;
	if(player->end < player->start) player->end = player->start;
	player->curFrame = player->start;
	player->speed = speed;
	player->loop = ELF_FALSE;
	player->pause = ELF_FALSE;

	elfSetFramePlayerFrame(player, player->curFrame);
}

ELF_API void ELF_APIENTRY elfLoopFramePlayer(elfFramePlayer* player, float start, float end, float speed)
{
	player->start = start;
	player->end = end;
	player->curFrame = start;
	player->speed = speed;
	player->pause = ELF_FALSE;
	player->loop = ELF_TRUE;

	elfSetFramePlayerFrame(player, player->curFrame);
}

ELF_API void ELF_APIENTRY elfStopFramePlayer(elfFramePlayer* player)
{
	player->start = 0.0f;
	player->end = 0.0f;
	player->speed = 0.0f;
	player->pause = ELF_FALSE;
	player->loop = ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfPauseFramePlayer(elfFramePlayer* player)
{
	if(player->end > 0.99999f) player->pause = ELF_TRUE;
}

ELF_API void ELF_APIENTRY elfResumeFramePlayer(elfFramePlayer* player)
{
	if(player->end > 0.99999f) player->pause = ELF_FALSE;
}

ELF_API float ELF_APIENTRY elfGetFramePlayerStart(elfFramePlayer* player)
{
	return player->start;
}

ELF_API float ELF_APIENTRY elfGetFramePlayerEnd(elfFramePlayer* player)
{
	return player->end;
}

ELF_API float ELF_APIENTRY elfGetFramePlayerSpeed(elfFramePlayer* player)
{
	return player->speed;
}

ELF_API float ELF_APIENTRY elfGetFramePlayerFrame(elfFramePlayer* player)
{
	return player->curFrame;
}

ELF_API unsigned char ELF_APIENTRY elfIsFramePlayerPlaying(elfFramePlayer* player)
{
	if(player->end > 0.99999f && !player->pause) return ELF_TRUE;
	return ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfIsFramePlayerPaused(elfFramePlayer* player)
{
	if(player->pause) return ELF_TRUE;
	return ELF_FALSE;
}

void elfSetFramePlayerUserData(elfFramePlayer* player, void* userData)
{
	player->userData = userData;
}

void* elfGetFramePlayerUserData(elfFramePlayer* player)
{
	return player->userData;
}

void elfSetFramePlayerCallback(elfFramePlayer* player, void (*callback)(elfFramePlayer*))
{
	player->callback = callback;
}

