
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef ELF_MACOSX
	#include <OpenAL/alc.h>
	#include <OpenAL/al.h>
#else
	#include <AL/alc.h>
	#include <AL/al.h>
#endif

#include <vorbis/vorbisfile.h>

#include "gfx.h"
#include "blendelf.h"
#include "types.h"

#define ELF_AUDIO_STREAM_CHUNK_SIZE 4096*8

typedef struct elfDataChunk			elfDataChunk;
typedef struct elfDataDump			elfDataDump;

struct elfDataChunk {
	elfDataChunk* next;
	int length;
	void* data;
};

struct elfDataDump {
	elfDataChunk* first;
	int offset;
};

elfDataChunk* elfCreateDataChunk()
{
	elfDataChunk* chunk;

	chunk = (elfDataChunk*)malloc(sizeof(elfDataChunk));
	memset(chunk, 0x0, sizeof(elfDataChunk));

	return chunk;
}

void elfDestroyDataChunk(elfDataChunk* chunk)
{
	if(chunk->next) elfDestroyDataChunk(chunk->next);
	if(chunk->data) free(chunk->data);
	free(chunk);
}

elfDataDump* elfCreateDataDump()
{
	elfDataDump* dump;

	dump = (elfDataDump*)malloc(sizeof(elfDataDump));
	memset(dump, 0x0, sizeof(elfDataDump));

	return dump;
}

void elfDestroyDataDump(elfDataDump* dump)
{
	if(dump->first) elfDestroyDataChunk(dump->first);
	free(dump);
}

int elfGetDataDumpLength(elfDataDump* dump)
{
	elfDataChunk* chk;
	int length;

	length = 0;

	chk = dump->first;
	while(chk)
	{
		length += chk->length;
		chk = chk->next;
	}

	return length;
}

void elfAddChunkToDataDump(elfDataDump* dump, void* data, int length)
{
	elfDataChunk* chunk;
	elfDataChunk* chk;

	chunk = elfCreateDataChunk();
	chunk->length = length;
	chunk->data = malloc(length);
	memcpy(chunk->data, data, length);

	if(!dump->first)
	{
		dump->first = chunk;
	}
	else
	{
		chk = dump->first;
		while(chk->next) chk = chk->next;
		chk->next = chunk;
	}
}

void elfDataDumpToBuffer(elfDataDump* dump, void* buf)
{
	int offset;
	elfDataChunk* chk;

	offset = 0;

	chk = dump->first;
	while(chk)
	{
		memcpy(&((char*)buf)[offset], chk->data, chk->length);
		offset += chk->length;
		chk = chk->next;
	}
}

struct elfAudioDevice {
	ELF_OBJECT_HEADER;
	ALCdevice* device;
	ALCcontext* context;
	float volume;
	float rolloff;
	elfList* sources;
};

struct elfAudioSource {
	ELF_OBJECT_HEADER;
	elfSound* sound;
	ALuint source;
	unsigned char loop;
	unsigned char paused;
};

struct elfSound {
	ELF_OBJECT_HEADER;
	char* filePath;
	unsigned char fileType;
	ALuint buffer[3];
	int freq;
	int format;

	unsigned char streamed;
	unsigned char streaming;
	unsigned char eof;
	OggVorbis_File oggFile;
	FILE* file;
	int length;
	int position;
	unsigned char oldestBuffer;
};

elfAudioDevice* audioDevice = NULL;

elfAudioDevice* elfCreateAudioDevice()
{
	elfAudioDevice* device;

	device = (elfAudioDevice*)malloc(sizeof(elfAudioDevice));
	memset(device, 0x0, sizeof(elfAudioDevice));
	device->objType = ELF_AUDIO_DEVICE;
	device->objDestr = elfDestroyAudioDevice;

	device->volume = 1.0f;
	device->rolloff = 1.0f;

	device->sources = elfCreateList();
	elfIncRef((elfObject*)device->sources);

	elfIncObj(ELF_AUDIO_DEVICE);

	return device;
}

void elfDestroyAudioDevice(void* data)
{
	elfAudioDevice* device = (elfAudioDevice*)data;

	if(device->sources) elfDecRef((elfObject*)device->sources);

	if(device->device)
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(device->context);
		alcCloseDevice(device->device);
	}

	free(device);

	elfDecObj(ELF_AUDIO_DEVICE);
}

unsigned char elfInitAudio()
{
	if(audioDevice)
	{
		elfLogWrite("warning: cannot initialize audio twice\n");
		return ELF_TRUE;
	}

	audioDevice = elfCreateAudioDevice();
	elfIncRef((elfObject*)audioDevice);

	audioDevice->device = alcOpenDevice(NULL);
	if(!audioDevice->device)
	{
		elfLogWrite("warning: could not create audio device\n");
		elfDeinitAudio();
		return ELF_FALSE;
	}

	audioDevice->context = alcCreateContext(audioDevice->device, NULL);
	if(!audioDevice->context)
	{
		elfLogWrite("warning: could not create audio context\n");
		alcCloseDevice(audioDevice->device);
		audioDevice->device = NULL;
		elfDeinitAudio();
		return ELF_FALSE;
	}

	alcMakeContextCurrent(audioDevice->context);

	alGetError();

	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListener3f(AL_DIRECTION, 0.0f, 0.0f, -1.0f);

	alListenerf(AL_GAIN, 1.0f);

	return ELF_TRUE;
}

void elfDeinitAudio()
{
	if(!audioDevice) return;

	elfDecRef((elfObject*)audioDevice);

	audioDevice = NULL;
}

void elfUpdateAudio()
{
	elfAudioSource* source;

	for(source = (elfAudioSource*)elfBeginList(audioDevice->sources); source;
		source = (elfAudioSource*)elfGetListNext(audioDevice->sources))
	{
		if(source->sound->streamed && !source->paused)
		{
			elfStreamAudioSource(source);
		}

		if(elfGetObjectRefCount((elfObject*)source) < 2 &&
			!elfIsSoundPlaying(source) &&
			!elfIsSoundPaused(source))
		{
			if(source->sound->streamed)
			{
				if(source->sound->eof && !source->loop) elfRemoveListObject(audioDevice->sources, (elfObject*)source);
			}
			else
			{
				elfRemoveListObject(audioDevice->sources, (elfObject*)source);
			}
		}
	}
}

ELF_API void ELF_APIENTRY elfSetAudioVolume(float volume)
{
	if(!audioDevice) return;
	alListenerf(AL_GAIN, volume);
}

ELF_API float ELF_APIENTRY elfGetAudioVolume()
{
	if(!audioDevice) return 0.0f;
	return audioDevice->volume;
}

ELF_API void ELF_APIENTRY elfSetAudioRolloff(float rolloff)
{
	if(!audioDevice) return;
	audioDevice->rolloff = rolloff;
}

ELF_API float ELF_APIENTRY elfGetAudioRolloff()
{
	if(!audioDevice) return 0.0f;
	return audioDevice->rolloff;
}

void elfSetAudioListenerPosition(float x, float y, float z)
{
	if(!audioDevice) return;
	alListener3f(AL_POSITION, x, y, z);
}

void elfSetAudioListenerOrientation(float* params)
{
	if(!audioDevice) return;
	alListenerfv(AL_ORIENTATION, params);
}

elfSound* elfCreateSound()
{
	elfSound* sound;

	sound = (elfSound*)malloc(sizeof(elfSound));
	memset(sound, 0x0, sizeof(elfSound));
	sound->objType = ELF_SOUND;
	sound->objDestr = elfDestroySound;

	elfIncObj(ELF_SOUND);

	return sound;
}

void elfDestroySound(void* data)
{
	elfSound* sound = (elfSound*)data;

	if(sound->filePath) elfDestroyString(sound->filePath);
	if(!sound->streamed)
	{
		if(sound->buffer[0]) alDeleteBuffers(1, &sound->buffer[0]);
	}
	else
	{
		alDeleteBuffers(3, sound->buffer);
		if(sound->fileType == ELF_OGG) ov_clear(&sound->oggFile);
		if(sound->fileType == ELF_WAV) fclose(sound->file);
	}
	free(sound);

	elfDecObj(ELF_SOUND);
}

unsigned char elfInitSoundWithOgg(elfSound* snd, const char* filePath)
{
	vorbis_info* info = NULL;

	if(snd->streamed && snd->fileType == ELF_OGG)
	{
		ov_clear(&snd->oggFile);
		snd->file = NULL;
	}
	if(snd->streamed && snd->fileType == ELF_WAV)
	{
		fclose(snd->file);
		snd->file = NULL;
	}

	snd->fileType = ELF_NONE;
	snd->length = 0;
	snd->position = 0;
	snd->eof = ELF_FALSE;

	snd->file = fopen(filePath, "rb");
	if(!snd->file)
	{
		elfSetError(ELF_CANT_OPEN_FILE, "error: can't open file \"%s\"\n", filePath);
		return ELF_FALSE;
	}

	snd->fileType = ELF_OGG;

	ov_open(snd->file, &snd->oggFile, NULL, 0);
	info = ov_info(&snd->oggFile, -1);

	if(info->channels == 1) snd->format = AL_FORMAT_MONO16;
	else if(info->channels == 2) snd->format = AL_FORMAT_STEREO16;
	else
	{
		elfSetError(ELF_CANT_OPEN_FILE, "error: invalid number of channels in \"%s\"\n", filePath);
		ov_clear(&snd->oggFile);
		return ELF_FALSE;
	}

	snd->freq = info->rate;

	return ELF_TRUE;
}

unsigned char elfInitSoundWithWav(elfSound* snd, const char* filePath)
{
	char buf[ELF_AUDIO_STREAM_CHUNK_SIZE];

	char magic[5] = "\0\0\0\0";
	unsigned int chunkLength = 0;
	int junkData = 0;
	unsigned short int audioFormat = 0;
	unsigned short int channels = 0;
	unsigned int freq = 0;
	unsigned char fmtFound = ELF_FALSE;
	unsigned char dataFound = ELF_FALSE;

	if(snd->streamed && snd->fileType == ELF_OGG)
	{
		ov_clear(&snd->oggFile);
		snd->file = NULL;
	}
	if(snd->streamed && snd->fileType == ELF_WAV)
	{
		fclose(snd->file);
		snd->file = NULL;
	}

	snd->fileType = ELF_NONE;
	snd->length = 0;
	snd->position = 0;
	snd->eof = ELF_FALSE;

	snd->file = fopen(filePath, "rb");
	if(!snd->file)
	{
		elfSetError(ELF_CANT_OPEN_FILE, "error: can't open file \"%s\"\n", filePath);
		return ELF_FALSE;
	}

	snd->fileType = ELF_WAV;

	fread(&magic, sizeof(int), 1, snd->file);
	if(strcmp((char*)&magic, "RIFF"))
	{
		elfSetError(ELF_INVALID_FILE, "error: \"%s\" invalid wav file, RIFF not found\n", filePath);
		return ELF_FALSE;
	}

	fread(&chunkLength, sizeof(unsigned int), 1, snd->file);
	fread(&magic, sizeof(int), 1, snd->file);
	if(strcmp((char*)&magic, "WAVE"))
	{
		elfSetError(ELF_INVALID_FILE, "error: \"%s\" invalid wav file, WAVE not found\n", filePath);
		return ELF_FALSE;
	}

	while(1)
	{
		if(fmtFound && dataFound) break;

		if(feof(snd->file))
		{
			if(!fmtFound || !dataFound)
			{
				elfSetError(ELF_INVALID_FILE, "error: \"%s\" invalid wav file\n", filePath);
				return ELF_FALSE;
			}
			break;
		}

		fread(&magic, sizeof(int), 1, snd->file);
		fread(&chunkLength, sizeof(unsigned int), 1, snd->file);
		if(strcmp((char*)&magic, "fmt ") == 0)
		{
			fread(&audioFormat, sizeof(unsigned short int), 1, snd->file);
			fread(&channels, sizeof(unsigned short int), 1, snd->file);
			fread(&freq, sizeof(unsigned int), 1, snd->file);
			fread(&junkData, sizeof(unsigned int), 1, snd->file);
			fread(&junkData, sizeof(unsigned short int), 1, snd->file);
			fread(&junkData, sizeof(unsigned short int), 1, snd->file);

			if(chunkLength-16 > 0) fread(buf, 1, chunkLength-16, snd->file);

			if(audioFormat != 1)
			{
				elfSetError(ELF_INVALID_FILE, "error: \"%s\" invalid wav file, invalid audio format\n", filePath);
				return ELF_FALSE;
			}

			snd->freq = freq;

			if(channels == 1) snd->format = AL_FORMAT_MONO16;
			else if(channels == 2) snd->format = AL_FORMAT_STEREO16;
			else
			{
				elfSetError(ELF_INVALID_FILE, "error: \"%s\" invalid wav file, invalid number of channels\n", filePath);
				return ELF_FALSE;
			}

			fmtFound = ELF_TRUE;
		}
		else if(strcmp((char*)&magic, "data") == 0)
		{
			snd->length = chunkLength;
			dataFound = ELF_TRUE;
		}
	}

	return ELF_TRUE;
}

ELF_API elfSound* ELF_APIENTRY elfLoadSound(const char* filePath)
{
	elfSound* snd = NULL;

	elfDataDump* dump;
	char buf[ELF_AUDIO_STREAM_CHUNK_SIZE];
	int bytesRead = 0;
	char* data;

	int endian = 0;
	int bitStream = 0;

	char* type = NULL;

	if(!audioDevice) return NULL;

	snd = elfCreateSound();
	snd->filePath = elfCreateString(filePath);

	type = strrchr((char*)filePath, '.');

	if(strcmp(type, ".ogg") == 0)
	{
		if(!elfInitSoundWithOgg(snd, snd->filePath))
		{
			elfDestroySound(snd);
			return NULL;
		}

		dump = elfCreateDataDump();
		do
		{
			bytesRead = ov_read(&snd->oggFile, buf, ELF_AUDIO_STREAM_CHUNK_SIZE, endian, 2, 1, &bitStream);
			elfAddChunkToDataDump(dump, buf, bytesRead);
			snd->length += bytesRead;
		}
		while (bytesRead > 0);

		snd->length = elfGetDataDumpLength(dump);
		data = (char*)malloc(snd->length);
		elfDataDumpToBuffer(dump, data);

		elfDestroyDataDump(dump);
		ov_clear(&snd->oggFile);
	}
	else if(strcmp(type, ".wav") == 0)
	{
		if(!elfInitSoundWithWav(snd, snd->filePath))
		{
			elfDestroySound(snd);
			return NULL;
		}

		data = (char*)malloc(snd->length);
		fread(data, sizeof(char), snd->length, snd->file);

		fclose(snd->file);
		snd->file = NULL;
	}
	else
	{
		elfSetError(ELF_UNKNOWN_FORMAT, "error: can't load \"%s\", unknown format\n", filePath);
		elfDestroySound(snd);
		return NULL;
	}

	alGenBuffers(1, &snd->buffer[0]);
	alBufferData(snd->buffer[0], snd->format, data, snd->length, snd->freq);

	free(data);

	return snd;
}

ELF_API elfSound* ELF_APIENTRY elfLoadStreamedSound(const char* filePath)
{
	elfSound* snd = NULL;

	char* type = NULL;

	if(!audioDevice) return NULL;

	snd = elfCreateSound();

	snd->filePath = elfCreateString(filePath);
	snd->streamed = ELF_TRUE;

	type = strrchr((char*)filePath, '.');

	if(strcmp(type, ".ogg") == 0)
	{
		if(!elfInitSoundWithOgg(snd, snd->filePath))
		{
			elfDestroySound(snd);
			return NULL;
		}
	}
	else if(strcmp(type, ".wav") == 0)
	{
		if(!elfInitSoundWithWav(snd, snd->filePath))
		{
			elfDestroySound(snd);
			return NULL;
		}
	}
	else
	{
		elfSetError(ELF_UNKNOWN_FORMAT, "error: can't load \"%s\", unknown format\n", filePath);
		elfDestroySound(snd);
		return NULL;
	}

	alGenBuffers(3, snd->buffer);

	return snd;
}

ELF_API int ELF_APIENTRY elfGetSoundFileType(elfSound* sound)
{
	return sound->fileType;
}

ELF_API elfAudioSource* ELF_APIENTRY elfPlaySound(elfSound* sound, float volume)
{
	elfAudioSource* source;

	if(!audioDevice || sound->streaming) return NULL;

	source = elfCreateAudioSource();

	// clear errors
	alGetError();

	source->sound = sound;
	elfIncRef((elfObject*)sound);

	alGenSources(1, &source->source);

	// check if everything went well
	if(alGetError() != AL_NO_ERROR)
	{
		elfDestroyAudioSource(source);
		return NULL;
	}

	if(!source->sound->streamed) alSourcei(source->source, AL_BUFFER, sound->buffer[0]);

	alSourcef(source->source, AL_GAIN, volume);
	alSourcef(source->source, AL_ROLLOFF_FACTOR, audioDevice->rolloff);

	if(source->sound->streamed)
	{
		elfStreamAudioSource(source);
		source->sound->streaming = ELF_TRUE;
	}
	alSourcePlay(source->source);

	elfAppendListObject(audioDevice->sources, (elfObject*)source);

	return source;
}

ELF_API elfAudioSource* ELF_APIENTRY elfPlayEntitySound(elfEntity* entity, elfSound* sound, float volume)
{
	elfAudioSource* source;
	float position[3];

	if(!audioDevice || sound->streaming) return NULL;

	source = elfCreateAudioSource();

	// clear errors
	alGetError();

	source->sound = sound;
	elfIncRef((elfObject*)sound);

	alGenSources(1, &source->source);

	// check if everything went well
	if(alGetError() != AL_NO_ERROR)
	{
		elfDestroyAudioSource(source);
		return NULL;
	}

	if(!source->sound->streamed) alSourcei(source->source, AL_BUFFER, sound->buffer[0]);

	alSourcef(source->source, AL_GAIN, volume);
	alSourcef(source->source, AL_ROLLOFF_FACTOR, audioDevice->rolloff);

	elfGetActorPosition_((elfActor*)entity, position);
	alSource3f(source->source, AL_POSITION, position[0], position[1], position[2]);

	if(source->sound->streamed)
	{
		elfStreamAudioSource(source);
		source->sound->streaming = ELF_TRUE;
	}
	alSourcePlay(source->source);

	elfAppendListObject(audioDevice->sources, (elfObject*)source);
	elfAppendListObject(entity->sources, (elfObject*)source);

	return source;
}

ELF_API elfAudioSource* ELF_APIENTRY elfLoopSound(elfSound* sound, float volume)
{
	elfAudioSource* source;

	if(!audioDevice || sound->streaming) return NULL;

	source = elfCreateAudioSource();

	// clear errors
	alGetError();

	source->loop = ELF_TRUE;
	source->sound = sound;
	elfIncRef((elfObject*)sound);

	alGenSources(1, &source->source);

	// check if everything went well
	if(alGetError() != AL_NO_ERROR)
	{
		elfDestroyAudioSource(source);
		return NULL;
	}

	if(!source->sound->streamed)
	{
		alSourcei(source->source, AL_BUFFER, sound->buffer[0]);
		alSourcei(source->source, AL_LOOPING, AL_TRUE);
	}

	alSourcef(source->source, AL_GAIN, volume);
	alSourcef(source->source, AL_ROLLOFF_FACTOR, audioDevice->rolloff);

	if(source->sound->streamed)
	{
		elfStreamAudioSource(source);
		source->sound->streaming = ELF_TRUE;
	}
	alSourcePlay(source->source);

	elfAppendListObject(audioDevice->sources, (elfObject*)source);

	return source;
}

ELF_API elfAudioSource* ELF_APIENTRY elfLoopEntitySound(elfEntity* entity, elfSound* sound, float volume)
{
	elfAudioSource* source;
	float position[3];

	if(!audioDevice || sound->streaming) return NULL;

	source = elfCreateAudioSource();

	// clear errors
	alGetError();

	source->loop = ELF_TRUE;
	source->sound = sound;
	elfIncRef((elfObject*)sound);

	alGenSources(1, &source->source);

	// check if everything went well
	if(alGetError() != AL_NO_ERROR)
	{
		elfDestroyAudioSource(source);
		return NULL;
	}

	if(!source->sound->streamed)
	{
		alSourcei(source->source, AL_BUFFER, sound->buffer[0]);
		alSourcei(source->source, AL_LOOPING, AL_TRUE);
	}

	alSourcef(source->source, AL_GAIN, volume);
	alSourcef(source->source, AL_ROLLOFF_FACTOR, audioDevice->rolloff);

	elfGetActorPosition_((elfActor*)entity, position);
	alSource3f(source->source, AL_POSITION, position[0], position[1], position[2]);

	if(source->sound->streamed)
	{
		elfStreamAudioSource(source);
		source->sound->streaming = ELF_TRUE;
	}
	alSourcePlay(source->source);

	elfAppendListObject(audioDevice->sources, (elfObject*)source);
	elfAppendListObject(entity->sources, (elfObject*)source);

	return source;
}

elfAudioSource* elfCreateAudioSource()
{
	elfAudioSource* source;

	source = (elfAudioSource*)malloc(sizeof(elfAudioSource));
	memset(source, 0x0, sizeof(elfAudioSource));
	source->objType = ELF_AUDIO_SOURCE;
	source->objDestr = elfDestroyAudioSource;

	elfIncObj(ELF_AUDIO_SOURCE);

	return source;
}

void elfStreamAudioSource(elfAudioSource* source)
{
	int queued;
	int processed;
	unsigned int buffer;

	char buf[ELF_AUDIO_STREAM_CHUNK_SIZE];
	int read;
	int bytesRead;
	int bytesToRead;

	int endian = 0;
	int bitStream = 0;

	if(!source->sound->eof)
	{
		if(!elfIsSoundPlaying(source) && !elfIsSoundPaused(source))
		{
			elfResumeSound(source);
		}
	}
	else
	{
		if(!source->loop)
		{
			return;
		}
	}

	alGetSourcei(source->source, AL_BUFFERS_QUEUED, &queued);
	alGetSourcei(source->source, AL_BUFFERS_PROCESSED, &processed);

	while(processed--) alSourceUnqueueBuffers(source->source, 1, &buffer);

	if(queued < 3)
	{
		bytesRead = 0;
		if(source->sound->fileType == ELF_OGG)
		{
			bytesToRead = ELF_AUDIO_STREAM_CHUNK_SIZE;

			do
			{
				read = ov_read(&source->sound->oggFile, &buf[bytesRead], ELF_AUDIO_STREAM_CHUNK_SIZE-bytesRead, endian, 2, 1, &bitStream);
				if(read < 1)
				{
					if(source->loop) elfInitSoundWithOgg(source->sound, source->sound->filePath);
					else source->sound->eof = ELF_TRUE;
					break;
				}
				bytesRead += read;
				bytesToRead -= read;
			}
			while (bytesToRead > 0);

			source->sound->position += bytesRead;
		}
		else if(source->sound->fileType == ELF_WAV)
		{
			if(source->sound->length-source->sound->position > ELF_AUDIO_STREAM_CHUNK_SIZE)
				bytesToRead = ELF_AUDIO_STREAM_CHUNK_SIZE;
			else bytesToRead = source->sound->length-source->sound->position;

			if(bytesToRead > 0) fread(buf, sizeof(char), bytesToRead, source->sound->file);
			else
			{
				if(source->loop) elfInitSoundWithWav(source->sound, source->sound->filePath);
				else source->sound->eof = ELF_TRUE;
			}

			bytesRead = bytesToRead;
			source->sound->position += bytesRead;
		}

		if(bytesRead > 0)
		{
			alBufferData(source->sound->buffer[source->sound->oldestBuffer], source->sound->format, buf, bytesRead, source->sound->freq);
			alSourceQueueBuffers(source->source, 1, &source->sound->buffer[source->sound->oldestBuffer]);
			source->sound->oldestBuffer++;
			if(source->sound->oldestBuffer > 2) source->sound->oldestBuffer = 0;
		}
	}
}

void elfDestroyAudioSource(void* data)
{
	elfAudioSource* source = (elfAudioSource*)data;

	if(source->sound)
	{
		source->sound->streaming = ELF_FALSE;
		elfDecRef((elfObject*)source->sound);
	}
	if(source->source) alDeleteSources(1, &source->source);

	free(source);

	elfDecObj(ELF_AUDIO_SOURCE);
}

ELF_API void ELF_APIENTRY elfSetSoundVolume(elfAudioSource* source, float volume)
{
	alSourcef(source->source, AL_GAIN, volume);
}

ELF_API float ELF_APIENTRY elfGetSoundVolume(elfAudioSource* source)
{
	float volume = 0.0f;
	alGetSourcef(source->source, AL_GAIN, &volume);
	return volume;
}

ELF_API void ELF_APIENTRY elfPauseSound(elfAudioSource* source)
{
	alSourcePause(source->source);
	source->paused = ELF_TRUE;
}

ELF_API void ELF_APIENTRY elfResumeSound(elfAudioSource* source)
{
	if(elfIsSoundPlaying(source)) return;

	if(source->sound->streamed)
	{
		if(source->sound->eof)
		{
			if(source->sound->fileType == ELF_OGG) elfInitSoundWithOgg(source->sound, source->sound->filePath);
			else if(source->sound->fileType == ELF_WAV) elfInitSoundWithWav(source->sound, source->sound->filePath);
		}
		else
		{
			alSourcePlay(source->source);
		}
	}
	else
	{
		alSourcePlay(source->source);
	}
	source->paused = ELF_FALSE;
}

ELF_API void ELF_APIENTRY elfStopSound(elfAudioSource* source)
{
	int queued;
	unsigned int buffer;

	if(source->sound->streamed)
	{
		alSourceStop(source->source);
		alGetSourcei(source->source, AL_BUFFERS_QUEUED, &queued);
		while(queued--) alSourceUnqueueBuffers(source->source, 1, &buffer);
		source->sound->eof = ELF_TRUE;
	}
	else
	{
		alSourceStop(source->source);
		source->paused = ELF_FALSE;
	}
}

ELF_API unsigned char ELF_APIENTRY elfIsSoundPlaying(elfAudioSource* source)
{
	int state = 0;
	alGetSourcei(source->source, AL_SOURCE_STATE, &state);
	if(state == AL_PLAYING) return ELF_TRUE;
	return ELF_FALSE;
}

ELF_API unsigned char ELF_APIENTRY elfIsSoundPaused(elfAudioSource* source)
{
	return source->paused;
}

void elfSetSoundPosition(elfAudioSource* source, float x, float y, float z)
{
	alSource3f(source->source, AL_POSITION, x, y, z);
}

