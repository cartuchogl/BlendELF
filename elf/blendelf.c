
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <malloc.h>
#include <sys/types.h>

#include <dirent.h>

#include <GL/glfw.h>
#ifdef ELF_MACOSX
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#ifdef ELF_WINDOWS
	#include <windows.h>
#else
	#include <unistd.h>
#endif

#include <FreeImage.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <assimp/assimp.h>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

#include "gfx.h"
#include "blendelf.h"
#include "types.h"

elfGeneral* gen = NULL;
elfContext* ctx = NULL;
elfEngine* eng = NULL;
elfRenderStation* rnd = NULL;
elfResources* res = NULL;

#include "general.h"
#include "config.h"
#include "log.h"
#include "resource.h"
#include "str.h"
#include "list.h"
#include "context.h"
#include "engine.h"
#include "renderstation.h"
#include "resources.h"
#include "frameplayer.h"
#include "timer.h"
#include "image.h"
#include "texture.h"
#include "material.h"
#include "ipo.h"
#include "camera.h"
#include "meshdata.h"
#include "model.h"
#include "entity.h"
#include "light.h"
#include "scene.h"
#include "pak.h"
#include "postprocess.h"
#include "script.h"
#include "armature.h"
#include "property.h"
#include "actor.h"
#include "font.h"
#include "gui.h"
#include "sst.h"
#include "particles.h"
#include "sprite.h"

#ifdef ELF_PLAYER

int main()
{
	elfConfig* config;
	elfScript* script;

	if(!(config = elfReadConfig("config.txt")))
		config = elfCreateConfig();

	if(!elfInit(config))
	{
		elfSetError(ELF_CANT_INITIALIZE, "error: can't initialize engine\n");
		elfDestroyConfig(config);
		return -1;
	}

	script = elfCreateScriptFromFile("Init", "init.lua");
	if(script)
	{
		elfIncRef((elfObject*)script);
		elfRunScript(script);
		elfDecRef((elfObject*)script);
	}
	else
	{
		while(elfRun());
	}

	elfDeinit();

	return 0;
}

#endif	// ELF_PLAYER

