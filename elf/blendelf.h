
// <!!
#ifndef BLENDELF_H
#define BLENDELF_H

#if defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
	#ifndef ELF_PLAYER
		#define ELF_APIENTRY __stdcall
		#ifdef ELF_DLL
			#define ELF_API __declspec(dllexport)
		#else
			#define ELF_API __declspec(dllimport)
		#endif
	#else
		#define ELF_API
		#define ELF_APIENTRY
	#endif
#else
	#define ELF_API
	#define ELF_APIENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif
// !!>

#define ELF_NONE					0x0000	// <mdoc> NONE VALUE

#define ELF_FALSE					0x0000	// <mdoc> TRUTH VALUES <mdocc> The thruth value flags. Usually you can just use normal Lua true and false but there are some special cases.
#define ELF_TRUE					0x0001

#define ELF_KEY_ESC					135	// <mdoc> KEY CODES <mdocc> The key codes used by elf.GetKeyState
#define ELF_KEY_F1					136
#define ELF_KEY_F2					137
#define ELF_KEY_F3					138
#define ELF_KEY_F4					139
#define ELF_KEY_F5					140
#define ELF_KEY_F6					141
#define ELF_KEY_F7					142
#define ELF_KEY_F8					143
#define ELF_KEY_F9					144
#define ELF_KEY_F10					145
#define ELF_KEY_F11					146
#define ELF_KEY_F12					147
#define ELF_KEY_UP					148
#define ELF_KEY_DOWN					149
#define ELF_KEY_LEFT					150
#define ELF_KEY_RIGHT					151
#define ELF_KEY_LSHIFT					152
#define ELF_KEY_RSHIFT					153
#define ELF_KEY_LCTRL					154
#define ELF_KEY_RCTRL					155
#define ELF_KEY_LALT					156
#define ELF_KEY_RALT					157
#define ELF_KEY_TAB					158
#define ELF_KEY_ENTER					159
#define ELF_KEY_BACKSPACE				160
#define ELF_KEY_INSERT					161
#define ELF_KEY_DEL					162
#define ELF_KEY_PAGEUP					163
#define ELF_KEY_PAGEDOWN				164
#define ELF_KEY_HOME					165
#define ELF_KEY_END					166
#define ELF_KEY_KP_0					167
#define ELF_KEY_KP_1					168
#define ELF_KEY_KP_2					169
#define ELF_KEY_KP_3					170
#define ELF_KEY_KP_4					171
#define ELF_KEY_KP_5					172
#define ELF_KEY_KP_6					173
#define ELF_KEY_KP_7					174
#define ELF_KEY_KP_8					175
#define ELF_KEY_KP_9					176
#define ELF_KEY_KP_DIVIDE				177
#define ELF_KEY_KP_MULTIPLY				178
#define ELF_KEY_KP_SUBTRACT				179
#define ELF_KEY_KP_ADD					180
#define ELF_KEY_KP_DECIMAL				181
#define ELF_KEY_KP_EQUAL				182
#define ELF_KEY_KP_ENTER				183
#define ELF_KEY_SPACE					32
#define ELF_KEY_0					48
#define ELF_KEY_1					49
#define ELF_KEY_2					50
#define ELF_KEY_3					51
#define ELF_KEY_4					52
#define ELF_KEY_5					53
#define ELF_KEY_6					54
#define ELF_KEY_7					55
#define ELF_KEY_8					56
#define ELF_KEY_9					57
#define ELF_KEY_A					65
#define ELF_KEY_B					66
#define ELF_KEY_C					67
#define ELF_KEY_D					68
#define ELF_KEY_E					69
#define ELF_KEY_F					70
#define ELF_KEY_G					71
#define ELF_KEY_H					72
#define ELF_KEY_I					73
#define ELF_KEY_J					74
#define ELF_KEY_K					75
#define ELF_KEY_L					76
#define ELF_KEY_M					77
#define ELF_KEY_N					78
#define ELF_KEY_O					79
#define ELF_KEY_P					80
#define ELF_KEY_Q					81
#define ELF_KEY_R					82
#define ELF_KEY_S					83
#define ELF_KEY_T					84
#define ELF_KEY_U					85
#define ELF_KEY_V					86
#define ELF_KEY_W					87
#define ELF_KEY_X					88
#define ELF_KEY_Y					89
#define ELF_KEY_Z					90

#define ELF_UP						0x0000	// <mdoc> KEY AND MOUSE STATES <mdocc> The state codes returned by elf.GetKeyState and elf.GetMouseButtonState
#define ELF_PRESSED					0x0001
#define ELF_DOWN					0x0002
#define ELF_RELEASED					0x0003

#define ELF_OFF						0x0000	// <mdoc> GUI BUTTON STATE <mdocc> The gui button states returned by elf.GetButtonState
#define ELF_ON						0x0001
#define ELF_OVER					0x0002

#define ELF_BUTTON_LEFT					0x0000	// <mdoc> MOUSE BUTTON CODES <mdocc> The mouse button codes used by elf.GetMouseButtonState
#define ELF_BUTTON_MIDDLE				0x0001
#define ELF_BUTTON_RIGHT				0x0002

#define ELF_TEXTURE					0x0000	// <mdoc> ELF OBJECT TYPES <mdocc> The  object types returned by elf.GetObjectType
#define ELF_MATERIAL					0x0001
#define ELF_MODEL					0x0002
#define ELF_CAMERA					0x0003
#define ELF_ENTITY					0x0004
#define ELF_LIGHT					0x0005
#define ELF_SCENE					0x0006
#define ELF_LIST					0x0007
#define ELF_PAK						0x0008
#define ELF_PAK_INDEX					0x0009
#define ELF_KEY_EVENT					0x000A
#define ELF_CHAR_EVENT					0x000B
#define ELF_CONTEXT					0x000C
#define ELF_ENGINE					0x000D
#define ELF_TIMER					0x000E
#define ELF_IMAGE					0x000F
#define ELF_POST_PROCESS				0x0010
#define ELF_SCRIPT					0x0011
#define ELF_AUDIO_DEVICE				0x0012
#define ELF_AUDIO_SOURCE				0x0013
#define ELF_SOUND					0x0014
#define ELF_BONE					0x0015
#define ELF_ARMATURE					0x0016
#define ELF_STRING					0x0017
#define ELF_FONT					0x0018
#define ELF_LABEL					0x0019
#define ELF_BUTTON					0x001A
#define ELF_PICTURE					0x001B
#define ELF_TEXT_FIELD					0x001C
#define ELF_SLIDER					0x001D
#define ELF_SCREEN					0x001E
#define ELF_TEXT_LIST					0x001F
#define ELF_CHECK_BOX					0x0020
#define ELF_GUI						0x0021
#define ELF_DIRECTORY_ITEM				0x0022
#define ELF_DIRECTORY					0x0023
#define ELF_COLLISION					0x0034
#define ELF_PHYSICS_OBJECT				0x0035
#define ELF_PHYSICS_WORLD				0x0036
#define ELF_JOINT					0x0037
#define ELF_PARTICLE					0x0038
#define ELF_PARTICLES					0x0039
#define ELF_CONFIG					0x003A
#define ELF_BEZIER_POINT				0x003B
#define ELF_BEZIER_CURVE				0x003C
#define ELF_IPO						0x003D
#define ELF_FRAME_PLAYER				0x003E
#define ELF_PROPERTY					0x003F
#define ELF_SCRIPTING					0x0040
#define ELF_PHYSICS_TRI_MESH				0x0041
#define ELF_SPRITE					0x0042
#define ELF_VIDEO_MODE					0x0043
#define ELF_GENERAL					0x0044
#define ELF_VERTEX					0x0045
#define ELF_FACE					0x0046
#define ELF_MESH_DATA					0x0047
#define ELF_LIST_PTR					0x0048
#define ELF_RESOURCES					0x0049
#define ELF_RENDER_STATION				0x004A
#define ELF_OBJECT_TYPE_COUNT				0x004B	// <mdoc> NUMBER OF OBJECT TYPES

#define ELF_PERSPECTIVE					0x0000	// <mdoc> CAMERA MODE <mdocc> The camera modes used by camera internal functions
#define ELF_ORTHOGRAPHIC				0x0001

#define ELF_BOX						0x0000	// <mdoc> PHYSICS SHAPES <mdocc> The physics shapes used by elf.SetEntityPhysics
#define ELF_SPHERE					0x0001
#define ELF_MESH					0x0002
#define ELF_CAPSULE_X					0x0003
#define ELF_CAPSULE_Y					0x0004
#define ELF_CAPSULE_Z					0x0005
#define ELF_CONE_X					0x0006
#define ELF_CONE_Y					0x0007
#define ELF_CONE_Z					0x0008

#define ELF_HINGE					0x0001	// <mdoc> JOINT TYPES <mdocc> The joint types returned by elf.GetJointType
#define ELF_BALL					0x0002
#define ELF_CONE_TWIST					0x0003

#define ELF_POINT_LIGHT					0x0001	// <mdoc> LIGHT TYPES <mdocc> The light types used by elf.SetLightType
#define ELF_SUN_LIGHT					0x0002
#define ELF_SPOT_LIGHT					0x0003

#define ELF_LUMINANCE					0x0000	// <mdoc> TEXTURE FORMATS <mdocc> The texture formats returned by elf.GetTextureFormat
#define ELF_LUMINANCE_ALPHA				0x0001
#define ELF_RGB						0x0002
#define ELF_RGBA					0x0003
#define ELF_BGR						0x0004
#define ELF_BGRA					0x0005
#define ELF_RGB16F					0x0006
#define ELF_RGB32F					0x0007
#define ELF_RGBA16F					0x0008
#define ELF_RGBA32F					0x0009
#define ELF_ALPHA32F					0x000A
#define ELF_DEPTH_COMPONENT				0x000B
#define ELF_COMPRESSED_RGB				0x000C
#define ELF_COMPRESSED_RGBA				0x000D

#define ELF_FLOAT					0x0000	// <mdoc> TEXTURE DATA FORMATS <mdocc> The texture formats returned by elf.GetTextureDataFormat
#define ELF_INT						0x0001
#define ELF_UINT					0x0002
#define ELF_SHORT					0x0003
#define ELF_USHORT					0x0004
#define ELF_BYTE					0x0005
#define ELF_UBYTE					0x0006

#define ELF_PROPERTY_INT				0x0001	// <mdoc> PROPERTY TYPES <mdocc> The property types returned by elf.GetPropertyType
#define ELF_PROPERTY_FLOAT				0x0002
#define ELF_PROPERTY_STRING				0x0003
#define ELF_PROPERTY_BOOL				0x0004

#define ELF_COLOR_MAP					0x0001	// <mdoc> TEXTURE TYPES <mdocc> The textures types
#define ELF_NORMAL_MAP					0x0002
#define ELF_HEIGHT_MAP					0x0004
#define ELF_SPECULAR_MAP				0x0008
#define ELF_DETAIL_MAP					0x0010
#define ELF_SHADOW_MAP					0x0020
#define ELF_COLOR_RAMP_MAP				0x0040
#define ELF_LIGHT_MAP					0x0080
#define ELF_CUBE_MAP					0x0100

#define ELF_TRANSPARENT					0x0001	// <mdoc> PARTICLE DRAW MODES <mdocc> The draw modes used by elf.SetParticlesDrawMode
#define ELF_ADD						0x0002

#define ELF_DIR						0x0001	// <mdoc> DIRECTORY ITEM TYPES <mdocc> The directory item types used by elf.GetDirectoryItemType
#define ELF_FILE					0x0002

#define ELF_CLICKED					0x0001	// <mdoc> GUI EVENTS <mdocc> The gui events triggered by gui objects. The gui events are automatically set to the "event" variable when in a gui action.
#define ELF_VALUE_CHANGED				0x0002
#define ELF_GAIN_FOCUS					0x0003
#define ELF_LOSE_FOCUS					0x0004
#define ELF_CHAR_INPUT					0x0005
#define ELF_SELECTION_CHANGED				0x0006
#define ELF_STATE_CHANGED				0x0007
#define ELF_DROP					0x0008

#define ELF_JOYSTICK_BUTTON_1				0x0000	// <mdoc> JOYSTICK BUTTONS <mdocc> The joystick buttons used by elf.GetJoystickButtonState
#define ELF_JOYSTICK_BUTTON_2				0x0001
#define ELF_JOYSTICK_BUTTON_3				0x0002
#define ELF_JOYSTICK_BUTTON_4				0x0003
#define ELF_JOYSTICK_BUTTON_5				0x0004
#define ELF_JOYSTICK_BUTTON_6				0x0005
#define ELF_JOYSTICK_BUTTON_7				0x0006
#define ELF_JOYSTICK_BUTTON_8				0x0007
#define ELF_JOYSTICK_BUTTON_9				0x0008
#define ELF_JOYSTICK_BUTTON_10				0x0009
#define ELF_JOYSTICK_BUTTON_11				0x000A
#define ELF_JOYSTICK_BUTTON_12				0x000B
#define ELF_JOYSTICK_BUTTON_13				0x000C
#define ELF_JOYSTICK_BUTTON_14				0x000D
#define ELF_JOYSTICK_BUTTON_15				0x000E
#define ELF_JOYSTICK_BUTTON_16				0x000F

#define ELF_LOC_X					0x0000	// <mdoc> BEZIER CURVE TYPES
#define ELF_LOC_Y					0x0001
#define ELF_LOC_Z					0x0002
#define ELF_ROT_X					0x0003
#define ELF_ROT_Y					0x0004
#define ELF_ROT_Z					0x0005
#define ELF_SCALE_X					0x0006
#define ELF_SCALE_Y					0x0007
#define ELF_SCALE_Z					0x0008
#define ELF_QUA_X					0x0009
#define ELF_QUA_Y					0x000A
#define ELF_QUA_Z					0x000B
#define ELF_QUA_W					0x000C

#define ELF_OGG						0x0001	// <mdoc> SOUND FILE TYPES <mdocc> The sound file types returned by elf.GetSoundFileType
#define ELF_WAV						0x0002

#define ELF_NO_ERROR					0x0000 // <mdoc> ERROR CODES <mdocc> error codes returned by elf.GetError
#define ELF_INVALID_FILE				0x0001
#define ELF_CANT_OPEN_FILE				0x0002
#define ELF_CANT_OPEN_DIRECTORY				0x0003
#define ELF_CANT_INITIALIZE				0x0004
#define ELF_CANT_RUN_STRING				0x0005
#define ELF_CANT_RUN_SCRIPT				0x0006
#define ELF_CANT_CREATE					0x0007
#define ELF_CANT_RESIZE					0x0008
#define ELF_INVALID_SIZE				0x0009
#define ELF_UNKNOWN_FORMAT				0x000A
#define ELF_UNKNOWN_TYPE				0x000B
#define ELF_INVALID_HANDLE				0x000C
#define ELF_MISSING_FEATURE				0x000D
#define ELF_INVALID_MESH				0x000E

// <!!
#define ELF_ARMATURE_MAGIC				179532122
#define ELF_CAMERA_MAGIC				179532111
#define ELF_ENTITY_MAGIC				179532112
#define ELF_LIGHT_MAGIC					179532113
#define ELF_MATERIAL_MAGIC				179532109
#define ELF_MODEL_MAGIC					179532110
#define ELF_PARTICLES_MAGIC				179532141
#define ELF_SCENE_MAGIC					179532120
#define ELF_SCRIPT_MAGIC				179532121
#define ELF_SPRITE_MAGIC				179532140
#define ELF_TEXTURE_MAGIC				179532108

#define ELF_NAME_LENGTH 128

#define ELF_DRAW_DEPTH					0x0000
#define ELF_DRAW_AMBIENT				0x0001
#define ELF_DRAW_WITHOUT_LIGHTING			0x0002
#define ELF_DRAW_WITH_LIGHTING				0x0003

#define ELF_PAK_VERSION					104
// !!>

typedef struct elfVec2i					elfVec2i;
typedef struct elfVec2f					elfVec2f;
typedef struct elfVec3f					elfVec3f;
typedef struct elfVec4f					elfVec4f;
typedef struct elfColor					elfColor;

typedef struct elfGeneral				elfGeneral;
typedef struct elfConfig				elfConfig;
typedef struct elfObject				elfObject;
typedef struct elfResource				elfResource;
typedef struct elfGuiObject				elfGuiObject;
typedef struct elfList					elfList;
typedef struct elfKeyEvent				elfKeyEvent;
typedef struct elfCharEvent				elfCharEvent;
typedef struct elfContext				elfContext;
typedef struct elfEngine				elfEngine;
typedef struct elfTimer					elfTimer;

typedef struct elfImage					elfImage;
typedef struct elfTexture				elfTexture;
typedef struct elfMaterial				elfMaterial;
typedef struct elfBezierPoint				elfBezierPoint;
typedef struct elfBezierCurve				elfBezierCurve;
typedef struct elfIpo					elfIpo;
typedef struct elfActor					elfActor;
typedef struct elfCamera				elfCamera;
typedef struct elfModel					elfModel;
typedef struct elfEntity				elfEntity;
typedef struct elfLight					elfLight;
typedef struct elfScene					elfScene;
typedef struct elfPakIndex				elfPakIndex;
typedef struct elfPak					elfPak;
typedef struct elfPostProcess				elfPostProcess;
typedef struct elfScript				elfScript;
typedef struct elfAudioDevice				elfAudioDevice;
typedef struct elfAudioSource				elfAudioSource;
typedef struct elfSound					elfSound;
typedef struct elfBone					elfBone;
typedef struct elfArmature				elfArmature;
typedef struct elfString				elfString;
typedef struct elfFont					elfFont;
typedef struct elfArea					elfArea;
typedef struct elfLabel					elfLabel;
typedef struct elfButton				elfButton;
typedef struct elfPicture				elfPicture;
typedef struct elfTextField				elfTextField;
typedef struct elfSlider				elfSlider;
typedef struct elfScreen				elfScreen;
typedef struct elfTextList				elfTextList;
typedef struct elfCheckBox				elfCheckBox;
typedef struct elfGui					elfGui;
typedef struct elfDirectoryItem				elfDirectoryItem;
typedef struct elfDirectory				elfDirectory;
typedef struct elfCollision				elfCollision;
typedef struct elfPhysicsTriMesh			elfPhysicsTriMesh;
typedef struct elfPhysicsObject				elfPhysicsObject;
typedef struct elfPhysicsWorld				elfPhysicsWorld;
typedef struct elfJoint					elfJoint;
typedef struct elfResources				elfResources;
typedef struct elfParticle				elfParticle;
typedef struct elfParticles				elfParticles;
typedef struct elfFramePlayer				elfFramePlayer;
typedef struct elfProperty				elfProperty;
typedef struct elfScripting				elfScripting;
typedef struct elfSprite				elfSprite;
typedef struct elfVideoMode				elfVideoMode;
typedef struct elfVertex				elfVertex;
typedef struct elfFace					elfFace;
typedef struct elfMeshData				elfMeshData;
typedef struct elfRenderStation				elfRenderStation;

// <!!
struct elfVec2i {
	int x;
	int y;
};

struct elfVec2f {
	float x;
	float y;
};

struct elfVec3f {
	float x;
	float y;
	float z;
};

struct elfVec4f {
	float x;
	float y;
	float z;
	float w;
};

struct elfColor {
	float r;
	float g;
	float b;
	float a;
};
// !!>

//////////////////////////////// GENERAL ////////////////////////////////

// <!!
elfGeneral* elfCreateGeneral();
void elfDestroyGeneral(elfGeneral* general);

void elfInitGeneral();
void elfDeinitGeneral();

void elfSetLogFilePath(const char* filePath);

void elfIncObj(int type);
void elfDecObj(int type);

void elfDumpRefTable();
void elfDumpObjTable();
// !!>

ELF_API void ELF_APIENTRY elfIncRef(elfObject* obj);	// <mdoc> OBJECT FUNCTIONS <mdocc> The object functions can be performed on any generic ELF objects.
ELF_API void ELF_APIENTRY elfDecRef(elfObject* obj);
ELF_API int ELF_APIENTRY elfGetObjectType(elfObject* obj);
ELF_API int ELF_APIENTRY elfGetObjectRefCount(elfObject* obj);
ELF_API int ELF_APIENTRY elfGetGlobalRefCount();
ELF_API int ELF_APIENTRY elfGetGlobalObjCount();
ELF_API unsigned char ELF_APIENTRY elfIsActor(elfObject* obj);
ELF_API unsigned char ELF_APIENTRY elfIsGuiObject(elfObject* obj);

//////////////////////////////// RESOURCE ////////////////////////////////

// <!!
elfResource* elfGetResource(elfList* resources, const char* name);
elfResource* elfGetResourceById(elfList* resources, int id);
void elfSetResourceUniqueName(elfList* namedObjects, elfResource* object);
// !!>

//////////////////////////////// STRING ////////////////////////////////

// <!!
elfString* elfCreateStringObject();
void elfDestroyStringObject(void* data);
char* elfCreateString(const char* str);
void elfDestroyString(char* str);
char* elfRemoveCharFromString(char* str, int idx);
char* elfAppendCharToString(char* str, char c);
char* elfInsertCharToString(char* str, int idx, char c);
char* elfMergeStrings(const char* str1, const char* str2);
char* elfMergeStrings3(const char* str1, const char* str2, const char* str3);
char* elfSubString(char* str, int start, int len);
unsigned char elfIsCharNumber(char c);
unsigned char elfIsStringNumber(const char* str);
unsigned char elfIsStringPositiveInt(const char* str);
int elfRFindCharFromString(char chr, const char* str);
int elfRFindCharsFromString(char* chrs, const char* str);
// !!>

//////////////////////////////// LIST ////////////////////////////////

ELF_API elfList* ELF_APIENTRY elfCreateList();	// <mdoc> LIST FUNCTIONS
/* <!> */ void elfDestroyList(void* data);
ELF_API int ELF_APIENTRY elfGetListLength(elfList* list);
ELF_API void ELF_APIENTRY elfInsertListObject(elfList* list, int idx, elfObject* obj);
ELF_API void ELF_APIENTRY elfAppendListObject(elfList* list, elfObject* obj);
ELF_API unsigned char ELF_APIENTRY elfRemoveListObject(elfList* list, elfObject* obj);
ELF_API elfObject* ELF_APIENTRY elfGetListObject(elfList* list, int idx);
ELF_API elfObject* ELF_APIENTRY elfBeginList(elfList* list);
ELF_API elfObject* ELF_APIENTRY elfGetListNext(elfList* list);
ELF_API elfObject* ELF_APIENTRY elfRBeginList(elfList* list);
ELF_API elfObject* ELF_APIENTRY elfGetListRNext(elfList* list);
/* <!> */void elfSetListCurPtr(elfList* list, elfObject* ptr);
ELF_API void ELF_APIENTRY elfSeekList(elfList* list, elfObject* ptr);
ELF_API void ELF_APIENTRY elfRSeekList(elfList* list, elfObject* ptr);

/////////////////////////////// CONFIG ///////////////////////////////

// <!!
elfConfig* elfCreateConfig();
void elfDestroyConfig(void* data);
// !!>

ELF_API elfConfig* ELF_APIENTRY elfReadConfig(const char* filePath);	// <mdoc> CONFIG FUNCTIONS

ELF_API void elfSetConfigWindowSize(elfConfig* config, int width, int height);
ELF_API void ELF_APIENTRY elfSetConfigMultisamples(elfConfig* config, int multisamples);
ELF_API void ELF_APIENTRY elfSetConfigFullscreen(elfConfig* config, unsigned char fullscreen);
ELF_API void ELF_APIENTRY elfSetConfigTextureCompress(elfConfig* config, unsigned char textureCompress);
ELF_API void ELF_APIENTRY elfSetConfigTextureAnisotropy(elfConfig* config, float textureAnisotropy);
ELF_API void ELF_APIENTRY elfSetConfigShadowMapSize(elfConfig* config, int shadowMapSize);
ELF_API void ELF_APIENTRY elfSetConfigStart(elfConfig* config, const char* start);
ELF_API void ELF_APIENTRY elfSetConfigLogPath(elfConfig* config, const char* logPath);

ELF_API elfVec2i ELF_APIENTRY elfGetConfigWindowSize(elfConfig* config);
ELF_API int ELF_APIENTRY elfGetConfigMultisamples(elfConfig* config);
ELF_API unsigned char ELF_APIENTRY elfGetConfigFullscreen(elfConfig* config);
ELF_API unsigned char ELF_APIENTRY elfGetConfigTextureCompress(elfConfig* config);
ELF_API float ELF_APIENTRY elfGetConfigTextureAnisotropy(elfConfig* config);
ELF_API int ELF_APIENTRY elfGetConfigShadowMapSize(elfConfig* config);
ELF_API const char* ELF_APIENTRY elfGetConfigStart(elfConfig* config);
ELF_API const char* ELF_APIENTRY elfGetConfigLogPath(elfConfig* config);

///////////////////////////////// LOG /////////////////////////////////

// <!!
void elfStartLog();
void elfLogWrite(const char* fmt, ...);
void elfSetError(int code, const char* fmt, ...);
// !!>

ELF_API void ELF_APIENTRY elfWriteLogLine(const char* str);	// <mdoc> LOG FUNCTIONS

/////////////////////////////// CONTEXT ///////////////////////////////

// <!!
elfVideoMode* elfCreateVideoMode();
void elfDestroyVideoMode(void* data);

elfKeyEvent* elfCreateKeyEvent();
void elfDestroyKeyEvent(void* data);

elfCharEvent* elfCreateCharEvent();
void elfDestroyCharEvent(void* data);

elfContext* elfCreateContext();
void elfDestroyContext(void* data);

unsigned char elfInitContext(int width, int height,
		const char* title, int multisamples, unsigned char fullscreen);
void elfCloseWindow();

unsigned char elfResizeContext(int width, int height);
// !!>

ELF_API void ELF_APIENTRY elfSetTitle(const char* title);	// <mdoc> CONTEXT FUNCTIONS

ELF_API int ELF_APIENTRY elfGetWindowWidth();
ELF_API int ELF_APIENTRY elfGetWindowHeight();
ELF_API int ELF_APIENTRY elfGetVideoModeCount();
ELF_API elfVec2i ELF_APIENTRY elfGetVideoMode(int idx);
ELF_API int ELF_APIENTRY elfGetMultisamples();
ELF_API unsigned char ELF_APIENTRY elfIsFullscreen();
ELF_API const char* ELF_APIENTRY elfGetTitle();
ELF_API double ELF_APIENTRY elfGetTime();
ELF_API void ELF_APIENTRY elfSleep(float time);
ELF_API unsigned char ELF_APIENTRY elfIsWindowOpened();
/* <!> */ void elfSwapBuffers();
ELF_API elfVec2i ELF_APIENTRY elfGetMousePosition();
ELF_API elfVec2i ELF_APIENTRY elfGetMouseForce();
ELF_API void ELF_APIENTRY elfSetMousePosition(int x, int y);
ELF_API void ELF_APIENTRY elfHideMouse(unsigned char hide);
ELF_API unsigned char ELF_APIENTRY elfIsMouseHidden();
ELF_API int ELF_APIENTRY elfGetMouseWheel();
ELF_API int ELF_APIENTRY elfGetMouseButtonState(int button);
ELF_API int ELF_APIENTRY elfGetKeyState(int key);
ELF_API unsigned char ELF_APIENTRY elfGetJoystickPresent(int joy);
ELF_API elfVec2f ELF_APIENTRY elfGetJoystickAxis(int joy);
ELF_API int ELF_APIENTRY elfGetJoystickButtonState(int joy, int but);
ELF_API int ELF_APIENTRY elfGetEventCount();
ELF_API elfObject* ELF_APIENTRY elfGetEvent(int idx);
ELF_API int ELF_APIENTRY elfGetKeyEventKey(elfKeyEvent* keyEvent);
ELF_API int ELF_APIENTRY elfGetKeyEventState(elfKeyEvent* keyEvent);

//////////////////////////////// ENGINE ///////////////////////////////

// <!!
void elfWriteToLog(const char* fmt, ...);
void elfSetError(int code, const char* fmt, ...);
void elfSetErrorNoSave(int code, const char* fmt, ...);

elfEngine* elfCreateEngine();
void elfDestroyEngine(void* data);

unsigned char elfInitEngine();
void elfDeinitEngine();
// !!>

ELF_API unsigned char ELF_APIENTRY elfInit(elfConfig* config);	// <mdoc> ENGINE FUNCTIONS
ELF_API void ELF_APIENTRY elfDeinit();

ELF_API void ELF_APIENTRY elfResizeWindow(int width, int height);

ELF_API const char* ELF_APIENTRY elfGetPlatform();

ELF_API int ELF_APIENTRY elfGetVersionMajor();
ELF_API int ELF_APIENTRY elfGetVersionMinor();
ELF_API const char* ELF_APIENTRY elfGetVersionRelease();
ELF_API const char* ELF_APIENTRY elfGetVersion();

ELF_API char* ELF_APIENTRY elfGetFileFromPath(const char* filePath);
ELF_API char* ELF_APIENTRY elfGetDirectoryFromPath(const char* filePath);
ELF_API const char* ELF_APIENTRY elfGetCurrentDirectory();

ELF_API const char* ELF_APIENTRY elfGetErrorString();
ELF_API int ELF_APIENTRY elfGetError();

ELF_API unsigned char ELF_APIENTRY elfRun();
ELF_API void ELF_APIENTRY elfQuit();

ELF_API void ELF_APIENTRY elfSetF10Exit(unsigned char exit);
ELF_API unsigned char ELF_APIENTRY elfGetF10Exit();

ELF_API elfScene* ELF_APIENTRY elfLoadScene(const char* filePath);
ELF_API void ELF_APIENTRY elfSetScene(elfScene* scene);
ELF_API elfScene* ELF_APIENTRY elfGetScene();

ELF_API void ELF_APIENTRY elfSetGui(elfGui* gui);
ELF_API elfGui* ELF_APIENTRY elfGetGui();

ELF_API float ELF_APIENTRY elfGetSync();
ELF_API int ELF_APIENTRY elfGetFps();

ELF_API unsigned char ELF_APIENTRY elfSaveScreenShot(const char* filePath);

ELF_API void ELF_APIENTRY elfSetFpsLimit(float fpsLimit);
ELF_API float ELF_APIENTRY elfGetFpsLimit();

ELF_API void ELF_APIENTRY elfSetTickRate(float tickRate);
ELF_API float ELF_APIENTRY elfGetTickRate();

ELF_API void ELF_APIENTRY elfSetSpeed(float speed);
ELF_API float ELF_APIENTRY elfGetSpeed();

ELF_API void ELF_APIENTRY elfSetTextureCompress(unsigned char compress);
ELF_API unsigned char ELF_APIENTRY elfGetTextureCompress();
ELF_API void ELF_APIENTRY elfSetTextureAnisotropy(float anisotropy);
ELF_API float ELF_APIENTRY elfGetTextureAnisotropy();

ELF_API void ELF_APIENTRY elfSetShadowMapSize(int size);
ELF_API int ELF_APIENTRY elfGetShadowMapSize();

ELF_API int ELF_APIENTRY elfGetPolygonsRendered();

ELF_API void ELF_APIENTRY elfSetBloom(float threshold);
ELF_API void ELF_APIENTRY elfDisableBloom();
ELF_API float ELF_APIENTRY elfGetBloomThreshold();

ELF_API void ELF_APIENTRY elfSetDof(float focalRange, float focalDistance);
ELF_API void ELF_APIENTRY elfDisableDof();
ELF_API float ELF_APIENTRY elfGetDofFocalRange();
ELF_API float ELF_APIENTRY elfGetDofFocalDistance();

ELF_API void ELF_APIENTRY elfSetSsao(float amount);
ELF_API void ELF_APIENTRY elfDisableSsao();
ELF_API float ELF_APIENTRY elfGetSsaoAmount();

ELF_API void ELF_APIENTRY elfSetLightShafts(float intensity);
ELF_API void ELF_APIENTRY elfDisableLightShafts();
ELF_API float ELF_APIENTRY elfGetLightShaftsIntensity();

ELF_API unsigned char ELF_APIENTRY elfIsBloom();
ELF_API unsigned char ELF_APIENTRY elfIsSsao();
ELF_API unsigned char ELF_APIENTRY elfIsDof();
ELF_API unsigned char ELF_APIENTRY elfIsLightShafts();

ELF_API elfObject* ELF_APIENTRY elfGetActor();

// <!!
elfDirectoryItem* elfCreateDirectoryItem();
void elfDestroyDirectoryItem(void* data);
elfDirectory* elfCreateDirectory();
void elfDestroyDirectory(void* data);
// !!>

ELF_API elfDirectory* ELF_APIENTRY elfReadDirectory(const char* path);

ELF_API const char* ELF_APIENTRY elfGetDirectoryPath(elfDirectory* directory);
ELF_API int ELF_APIENTRY elfGetDirectoryItemCount(elfDirectory* directory);
ELF_API elfDirectoryItem* ELF_APIENTRY elfGetDirectoryItem(elfDirectory* directory, int idx);
ELF_API const char* ELF_APIENTRY elfGetDirectoryItemName(elfDirectoryItem* dirItem);
ELF_API int ELF_APIENTRY elfGetDirectoryItemType(elfDirectoryItem* dirItem);

ELF_API elfColor ELF_APIENTRY elfCreateColor(float r, float g, float b, float a);
ELF_API elfVec2f ELF_APIENTRY elfCreateVec2f(float x, float y);
ELF_API elfVec3f ELF_APIENTRY elfCreateVec3f(float x, float y, float z);
ELF_API elfVec4f ELF_APIENTRY elfCreateQua(float x, float y, float z, float w);
ELF_API elfVec4f ELF_APIENTRY elfCreateQuaFromEuler(float x, float y, float z);
ELF_API elfVec4f ELF_APIENTRY elfCreateQuaFromAngleAxis(float angle, float x, float y, float z);
ELF_API elfVec2f ELF_APIENTRY elfAddVec2fVec2f(elfVec2f vec1, elfVec2f vec2);
ELF_API elfVec2f ELF_APIENTRY elfSubVec2fVec2f(elfVec2f vec1, elfVec2f vec2);
ELF_API elfVec2f ELF_APIENTRY elfMulVec2fVec2f(elfVec2f vec1, elfVec2f vec2);
ELF_API float ELF_APIENTRY elfGetVec2fLength(elfVec2f vec);
ELF_API elfVec3f ELF_APIENTRY elfAddVec3fVec3f(elfVec3f vec1, elfVec3f vec2);
ELF_API elfVec3f ELF_APIENTRY elfSubVec3fVec3f(elfVec3f vec1, elfVec3f vec2);
ELF_API elfVec3f ELF_APIENTRY elfMulVec3fVec3f(elfVec3f vec1, elfVec3f vec2);
ELF_API float ELF_APIENTRY elfGetVec3fLength(elfVec3f vec);
ELF_API elfVec3f ELF_APIENTRY elfRotateVec3f(elfVec3f vec, float x, float y, float z);
ELF_API elfVec3f ELF_APIENTRY elfMulQuaVec3f(elfVec4f qua, elfVec3f vec);
ELF_API elfVec4f ELF_APIENTRY elfMulQuaQua(elfVec4f qua1, elfVec4f qua2);
ELF_API elfVec4f ELF_APIENTRY elfGetQuaInverted(elfVec4f qua);

ELF_API unsigned char ELF_APIENTRY elfAboutSame(float v1, float v2);
ELF_API unsigned char ELF_APIENTRY elfAboutZero(float val);
ELF_API float ELF_APIENTRY elfFloatAbs(float val);
ELF_API float ELF_APIENTRY elfFloatMin(float a, float b);
ELF_API float ELF_APIENTRY elfFloatMax(float a, float b);
ELF_API float ELF_APIENTRY elfRandomFloat();
ELF_API float ELF_APIENTRY elfRandomFloatRange(float min, float max);
ELF_API int ELF_APIENTRY elfRandomInt();
ELF_API int ELF_APIENTRY elfRandomIntRange(int min, int max);

/////////////////////////// RENDER STATION ////////////////////////////

// <!!
elfRenderStation* elfCreateRenderStation();
void elfDestroyRenderStation(void *data);
unsigned char elfInitRenderStation();
void elfDeinitRenderStation();

void elfDraw2dQuad(float x, float y, float width, float height);
void elfDrawTextured2dQuad(float x, float y, float width, float height);
void elfDrawTextured2dQuadRegion(float x, float y, float width, float height, float tx, float ty, float twidth, float theight);
float elfGetAbsoluteValue(float val);
void elfDrawCircle(float x, float y, int vertices, float size);
void elfDrawBoundingBox(float min[3], float max[3]);
void elfDrawLines(int count, gfxVertexData* vertices);
void elfDrawLineLoop(int count, gfxVertexData* vertices);
void elfDrawHorGradient(int x, int y, int width, int height, elfColor col1, elfColor col2);
void elfDrawHorGradientBorder(int x, int y, int width, int height, elfColor col1, elfColor col2);
// !!>

////////////////////////////// RESOURCES //////////////////////////////

// <!!
elfResources* elfCreateResources();
void elfDestroyResources(void *data);
unsigned char elfInitResources();
void elfDeinitResources();
// !!>

ELF_API elfTexture* elfGetResourcesTexture(const char* filePath, const char* name);

ELF_API elfTexture* elfGetOrLoadResourcesTexture(const char* filePath, const char* name);

///////////////////////////// FRAME PLAYER ////////////////////////////

/* <!> */ void elfDestroyFramePlayer(void* data);

ELF_API elfFramePlayer* ELF_APIENTRY elfCreateFramePlayer();	// <mdoc> FRAME PLAYER FUNCTIONS
ELF_API void ELF_APIENTRY elfUpdateFramePlayer(elfFramePlayer* player);
ELF_API void ELF_APIENTRY elfSetFramePlayerFrame(elfFramePlayer* player, float frame);
ELF_API void ELF_APIENTRY elfPlayFramePlayer(elfFramePlayer* player, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfLoopFramePlayer(elfFramePlayer* player, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfStopFramePlayer(elfFramePlayer* player);
ELF_API void ELF_APIENTRY elfPauseFramePlayer(elfFramePlayer* player);
ELF_API void ELF_APIENTRY elfResumeFramePlayer(elfFramePlayer* player);
ELF_API float ELF_APIENTRY elfGetFramePlayerStart(elfFramePlayer* player);
ELF_API float ELF_APIENTRY elfGetFramePlayerEnd(elfFramePlayer* player);
ELF_API float ELF_APIENTRY elfGetFramePlayerSpeed(elfFramePlayer* player);
ELF_API float ELF_APIENTRY elfGetFramePlayerFrame(elfFramePlayer* player);
ELF_API unsigned char ELF_APIENTRY elfIsFramePlayerPlaying(elfFramePlayer* player);
ELF_API unsigned char ELF_APIENTRY elfIsFramePlayerPaused(elfFramePlayer* player);
// <!!
void elfSetFramePlayerUserData(elfFramePlayer* player, void* userData);
void* elfGetFramePlayerUserData(elfFramePlayer* player);
void elfSetFramePlayerCallback(elfFramePlayer* player, void (*callback)(elfFramePlayer*));
// !!>

//////////////////////////////// TIMER ////////////////////////////////

ELF_API elfTimer* ELF_APIENTRY elfCreateTimer();	// <mdoc> TIMER FUNCTIONS
/* <!> */ void elfDestroyTimer(void* data);
ELF_API void ELF_APIENTRY elfStartTimer(elfTimer* timer);
ELF_API double ELF_APIENTRY elfGetElapsedTime(elfTimer* timer);

//////////////////////////////// IMAGE ////////////////////////////////

/* <!> */ elfImage* elfCreateImage();
ELF_API elfImage* ELF_APIENTRY elfCreateEmptyImage(int width, int height, int bpp);	// IMAGE FUNCTIONS
ELF_API elfImage* ELF_APIENTRY elfCreateImageFromFile(const char* filePath);
/* <!> */ void elfDestroyImage(void* data);

ELF_API void ELF_APIENTRY elfSetImagePixel(elfImage* image, int x, int y, float r, float g, float b, float a);

ELF_API int ELF_APIENTRY elfGetImageWidth(elfImage* image);
ELF_API int ELF_APIENTRY elfGetImageHeight(elfImage* image);
ELF_API int ELF_APIENTRY elfGetImageBitsPerPixel(elfImage* image);
ELF_API elfColor ELF_APIENTRY elfGetImagePixel(elfImage* image, int x, int y);

// <!!
void* elfGetImageData(elfImage* image);
unsigned char elfSaveImageData(const char* filePath, int width, int height, unsigned char bpp, void* data);
// !!>

/////////////////////////////// TEXTURE ///////////////////////////////

// <!!
elfTexture* elfCreateTexture();
void elfDestroyTexture(void* data);
// !!>

ELF_API elfTexture* ELF_APIENTRY elfCreateTextureFromFile(const char* name, const char* filePath);	// <mdoc> TEXTURE FUNCTIONS
ELF_API elfTexture* ELF_APIENTRY elfCreateTextureFromImage(const char* name, elfImage* image);
ELF_API elfTexture* ELF_APIENTRY elfCreateCubeMapFromFiles(const char* name, const char* xpos, const char* xneg, const char* ypos, const char* yneg, const char* zpos, const char* zneg);

ELF_API void ELF_APIENTRY elfSetTextureName(elfTexture* texture, const char* name);

ELF_API const char* ELF_APIENTRY elfGetTextureName(elfTexture* texture);
ELF_API const char* ELF_APIENTRY elfGetTextureFilePath(elfTexture* texture);
ELF_API int ELF_APIENTRY elfGetTextureWidth(elfTexture* texture);
ELF_API int ELF_APIENTRY elfGetTextureHeight(elfTexture* texture);
ELF_API int ELF_APIENTRY elfGetTextureFormat(elfTexture* texture);
ELF_API int ELF_APIENTRY elfGetTextureDataFormat(elfTexture* texture);
// <!!
gfxTexture* elfGetGfxTexture(elfTexture* texture);
void elfSetTexture(int slot, elfTexture* texture, gfxShaderParams* shaderParams);
// !!>

//////////////////////////////// MATERIAL ////////////////////////////////

/* <!> */void elfDestroyMaterial(void* data);

ELF_API elfMaterial* ELF_APIENTRY elfCreateMaterial(const char* name);	// <mdoc> MATERIAL FUNCTIONS

ELF_API void ELF_APIENTRY elfSetMaterialDiffuseColor(elfMaterial* material, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetMaterialSpecularColor(elfMaterial* material, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetMaterialAmbientColor(elfMaterial* material, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetMaterialSpecularPower(elfMaterial* material, float power);
ELF_API void ELF_APIENTRY elfSetMaterialLighting(elfMaterial* material, unsigned char lighting);

ELF_API void ELF_APIENTRY elfSetMaterialName(elfMaterial* material, const char* name);
ELF_API const char* ELF_APIENTRY elfGetMaterialName(elfMaterial* material);
ELF_API const char* ELF_APIENTRY elfGetMaterialFilePath(elfMaterial* material);
ELF_API elfColor ELF_APIENTRY elfGetMaterialDiffuseColor(elfMaterial* material);
ELF_API elfColor ELF_APIENTRY elfGetMaterialSpecularColor(elfMaterial* material);
ELF_API elfColor ELF_APIENTRY elfGetMaterialAmbientColor(elfMaterial* material);
ELF_API float ELF_APIENTRY elfGetMaterialSpecularPower(elfMaterial* material);
ELF_API unsigned char ELF_APIENTRY elfGetMaterialLighting(elfMaterial* material);

ELF_API void ELF_APIENTRY elfSetMaterialDiffuseMap(elfMaterial* material, elfTexture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialNormalMap(elfMaterial* material, elfTexture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialHeightMap(elfMaterial* material, elfTexture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialSpecularMap(elfMaterial* material, elfTexture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialLightMap(elfMaterial* material, elfTexture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialCubeMap(elfMaterial* material, elfTexture* texture);

ELF_API void ELF_APIENTRY elfClearMaterialDiffuseMap(elfMaterial* material);
ELF_API void ELF_APIENTRY elfClearMaterialNormalMap(elfMaterial* material);
ELF_API void ELF_APIENTRY elfClearMaterialHeightMap(elfMaterial* material);
ELF_API void ELF_APIENTRY elfClearMaterialSpecularMap(elfMaterial* material);
ELF_API void ELF_APIENTRY elfClearMaterialLightMap(elfMaterial* material);
ELF_API void ELF_APIENTRY elfClearMaterialCubeMap(elfMaterial* material);

ELF_API elfTexture* ELF_APIENTRY elfGetMaterialDiffuseMap(elfMaterial* material);
ELF_API elfTexture* ELF_APIENTRY elfGetMaterialNormalMap(elfMaterial* material);
ELF_API elfTexture* ELF_APIENTRY elfGetMaterialHeightMap(elfMaterial* material);
ELF_API elfTexture* ELF_APIENTRY elfGetMaterialSpecularMap(elfMaterial* material);
ELF_API elfTexture* ELF_APIENTRY elfGetMaterialLightMap(elfMaterial* material);
ELF_API elfTexture* ELF_APIENTRY elfGetMaterialCubeMap(elfMaterial* material);

ELF_API void ELF_APIENTRY elfSetMaterialParallaxScale(elfMaterial* material, float scale);

ELF_API void ELF_APIENTRY elfSetMaterialAlphaTest(elfMaterial* material, unsigned char alphaTest);
ELF_API void ELF_APIENTRY elfSetMaterialAlphaThreshold(elfMaterial* material, float threshold);

ELF_API float ELF_APIENTRY elfGetMaterialParallaxScale(elfMaterial* material);

ELF_API unsigned char ELF_APIENTRY elfGetMaterialAlphaTest(elfMaterial* material);
ELF_API float ELF_APIENTRY elfGetMaterialAlphaThreshold(elfMaterial* material);

// <!!
void elfSetMaterial(elfMaterial* material, int mode, gfxShaderParams* shaderParams);
// !!>

//////////////////////////////// IPOS ////////////////////////////////

// <!!
void elfDestroyBezierPoint(void* data);
void elfDestroyBezierCurve(void* data);
void elfDestroyIpo(void* data);
// !!>

ELF_API elfBezierPoint* ELF_APIENTRY elfCreateBezierPoint();	// <mdoc> IPO FUNCTIONS
ELF_API void ELF_APIENTRY elfSetBezierPointPosition(elfBezierPoint* point, float x, float y);
ELF_API void ELF_APIENTRY elfSetBezierPointControl1(elfBezierPoint* point, float x, float y);
ELF_API void ELF_APIENTRY elfSetBezierPointControl2(elfBezierPoint* point, float x, float y);
ELF_API elfVec2f ELF_APIENTRY elfGetBezierPointPosition(elfBezierPoint* point);
ELF_API elfVec2f ELF_APIENTRY elfGetBezierPointControl1(elfBezierPoint* point);
ELF_API elfVec2f ELF_APIENTRY elfGetBezierPointControl2(elfBezierPoint* point);

ELF_API elfBezierCurve* ELF_APIENTRY elfCreateBezierCurve();
ELF_API void ELF_APIENTRY elfSetBezierCurveType(elfBezierCurve* curve, int type);
ELF_API int ELF_APIENTRY elfGetBezierCurveType(elfBezierCurve* curve);
ELF_API void ELF_APIENTRY elfAddBezierCurvePoint(elfBezierCurve* curve, elfBezierPoint* point);
ELF_API elfBezierPoint* ELF_APIENTRY elfGetPointFromBezierCurve(elfBezierCurve* curve, int idx);
ELF_API float ELF_APIENTRY elfGetBezierCurveValue(elfBezierCurve* curve, float x);

ELF_API elfIpo* ELF_APIENTRY elfCreateIpo();
ELF_API unsigned char ELF_APIENTRY elfAddIpoCurve(elfIpo* ipo, elfBezierCurve* curve);
ELF_API int ELF_APIENTRY elfGetIpoCurveCount(elfIpo* ipo);
ELF_API elfBezierCurve* ELF_APIENTRY elfGetCurveFromIpo(elfIpo* ipo, int idx);
ELF_API elfVec3f ELF_APIENTRY elfGetIpoLoc(elfIpo* ipo, float x);
ELF_API elfVec3f ELF_APIENTRY elfGetIpoRot(elfIpo* ipo, float x);
ELF_API elfVec3f ELF_APIENTRY elfGetIpoScale(elfIpo* ipo, float x);
ELF_API elfVec4f ELF_APIENTRY elfGetIpoQua(elfIpo* ipo, float x);

//////////////////////////////// PROPERTY ////////////////////////////////


ELF_API elfProperty* ELF_APIENTRY elfCreateProperty(const char* name);	// <mdoc> PROPERTY FUNCTIONS
/* <!> */ void elfDestroyProperty(void* data);

ELF_API int ELF_APIENTRY elfGetPropertyType(elfProperty* property);

ELF_API int ELF_APIENTRY elfGetPropertyInt(elfProperty* property);
ELF_API float ELF_APIENTRY elfGetPropertyFloat(elfProperty* property);
ELF_API const char* ELF_APIENTRY elfGetPropertyString(elfProperty* property);
ELF_API unsigned char ELF_APIENTRY elfGetPropertyBool(elfProperty* property);

ELF_API void ELF_APIENTRY elfSetPropertyInt(elfProperty* property, int ival);
ELF_API void ELF_APIENTRY elfSetPropertyFloat(elfProperty* property, float fval);
ELF_API void ELF_APIENTRY elfSetPropertyString(elfProperty* property, const char* sval);
ELF_API void ELF_APIENTRY elfSetPropertyBool(elfProperty* property, unsigned char bval);

//////////////////////////////// ACTOR ////////////////////////////////

// <!!
void elfInitActor(elfActor* actor, unsigned char camera);
void elfUpdateActor(elfActor* actor);
void elfActorPreDraw(elfActor* actor);
void elfActorPostDraw(elfActor* actor);
void elfCleanActor(elfActor* actor);
// !!>

ELF_API const char* ELF_APIENTRY elfGetActorName(elfActor* actor);	// <mdoc> ACTOR FUNCTIONS
ELF_API const char* ELF_APIENTRY elfGetActorFilePath(elfActor* actor);
ELF_API elfScript* ELF_APIENTRY elfGetActorScript(elfActor* actor);

ELF_API void ELF_APIENTRY elfSetActorName(elfActor* actor, const char* name);
ELF_API void ELF_APIENTRY elfSetActorScript(elfActor* actor, elfScript* script);
ELF_API void ELF_APIENTRY elfClearActorScript(elfActor* actor);

ELF_API void ELF_APIENTRY elfSetActorPosition(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorRotation(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorOrientation(elfActor* actor, float x, float y, float z, float w);
ELF_API void ELF_APIENTRY elfRotateActor(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfRotateActorLocal(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfMoveActor(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfMoveActorLocal(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorPositionRelativeTo(elfActor* actor, elfActor* to, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorRotationRelativeTo(elfActor* actor, elfActor* to, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorOrientationRelativeTo(elfActor* actor, elfActor* to, float x, float y, float z, float w);
ELF_API elfVec3f ELF_APIENTRY elfGetActorPosition(elfActor* actor);
ELF_API elfVec3f ELF_APIENTRY elfGetActorRotation(elfActor* actor);
ELF_API elfVec4f ELF_APIENTRY elfGetActorOrientation(elfActor* actor);

// <!!
void elfGetActorPosition_(elfActor* actor, float* params);
void elfGetActorRotation_(elfActor* actor, float* params);
void elfGetActorOrientation_(elfActor* actor, float* params);
// !!>

ELF_API void ELF_APIENTRY elfSetActorPhysics(elfActor* actor, unsigned char physics);
ELF_API void ELF_APIENTRY elfSetActorShape(elfActor* actor, int shape);
ELF_API void ELF_APIENTRY elfSetActorBoundingLengths(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorBoundingOffset(elfActor* actor, float x, float y, float z);
/* <!> */ void elfResetActorBoundingOffsetSetFlag(elfActor* actor);
ELF_API void ELF_APIENTRY elfSetActorMass(elfActor* actor, float mass);

ELF_API void ELF_APIENTRY elfSetActorDamping(elfActor* actor, float linDamp, float angDamp);
ELF_API void ELF_APIENTRY elfSetActorSleep(elfActor* actor, float linThrs, float angThrs);
ELF_API void ELF_APIENTRY elfSetActorRestitution(elfActor* actor, float restitution);
ELF_API void ELF_APIENTRY elfSetActorAnisotropicFriction(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorLinearFactor(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorAngularFactor(elfActor* actor, float x, float y, float z);

ELF_API void ELF_APIENTRY elfAddActorForce(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfAddActorForceLocal(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfAddActorTorque(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorLinearVelocity(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorLinearVelocityLocal(elfActor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorAngularVelocity(elfActor* actor, float x, float y, float z);

ELF_API unsigned char ELF_APIENTRY elfGetActorPhysics(elfActor* actor);
ELF_API elfVec3f ELF_APIENTRY elfGetActorBoundingLengths(elfActor* actor);
ELF_API elfVec3f ELF_APIENTRY elfGetActorBoundingOffset(elfActor* actor);
ELF_API int ELF_APIENTRY elfGetActorShape(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorMass(elfActor* actor);

ELF_API float ELF_APIENTRY elfGetActorLinearDamping(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorAngularDamping(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorLinearSleep(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorAngularSleep(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorRestitution(elfActor* actor);
ELF_API elfVec3f ELF_APIENTRY elfGetActorAnisotropicFriction(elfActor* actor);
ELF_API elfVec3f ELF_APIENTRY elfGetActorLinearFactor(elfActor* actor);
ELF_API elfVec3f ELF_APIENTRY elfGetActorAngularFactor(elfActor* actor);
ELF_API elfVec3f ELF_APIENTRY elfGetActorLinearVelocity(elfActor* actor);
ELF_API elfVec3f ELF_APIENTRY elfGetActorAngularVelocity(elfActor* actor);

ELF_API elfJoint* ELF_APIENTRY elfAddActorHingeJoint(elfActor* actor, elfActor* actor2, const char* name, float px, float py, float pz, float ax, float ay, float az);
ELF_API elfJoint* ELF_APIENTRY elfAddActorBallJoint(elfActor* actor, elfActor* actor2, const char* name, float px, float py, float pz);
ELF_API elfJoint* ELF_APIENTRY elfAddActorConeTwistJoint(elfActor* actor, elfActor* actor2, const char* name, float px, float py, float pz, float ax, float ay, float az);
ELF_API elfJoint* ELF_APIENTRY elfGetActorJoint(elfActor* actor, const char* name);
ELF_API elfJoint* ELF_APIENTRY elfGetActorJointByIndex(elfActor* actor, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorJoint(elfActor* actor, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorJointByIndex(elfActor* actor, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorJointByObject(elfActor* actor, elfJoint* joint);

ELF_API void ELF_APIENTRY elfSetActorIpo(elfActor* actor, elfIpo* ipo);
ELF_API elfIpo* ELF_APIENTRY elfGetActorIpo(elfActor* actor);

ELF_API void ELF_APIENTRY elfSetActorIpoFrame(elfActor* actor, float frame);
ELF_API void ELF_APIENTRY elfPlayActorIpo(elfActor* actor, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfLoopActorIpo(elfActor* actor, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfStopActorIpo(elfActor* actor);
ELF_API void ELF_APIENTRY elfPauseActorIpo(elfActor* actor);
ELF_API void ELF_APIENTRY elfResumeActorIpo(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorIpoStart(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorIpoEnd(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorIpoSpeed(elfActor* actor);
ELF_API float ELF_APIENTRY elfGetActorIpoFrame(elfActor* actor);
ELF_API unsigned char ELF_APIENTRY elfIsActorIpoPlaying(elfActor* actor);
ELF_API unsigned char ELF_APIENTRY elfIsActorIpoPaused(elfActor* actor);

ELF_API int ELF_APIENTRY elfGetActorCollisionCount(elfActor* actor);
ELF_API elfCollision* ELF_APIENTRY elfGetActorCollision(elfActor* actor, int idx);

ELF_API int ELF_APIENTRY elfGetActorPropertyCount(elfActor* actor);
ELF_API void ELF_APIENTRY elfAddPropertyToActor(elfActor* actor, elfProperty* property);
ELF_API elfProperty* ELF_APIENTRY elfGetActorPropertyByName(elfActor* actor, const char* name);
ELF_API elfProperty* ELF_APIENTRY elfGetActorPropertyByIndex(elfActor* actor, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorPropertyByName(elfActor* actor, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorPropertyByIndex(elfActor* actor, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorPropertyByObject(elfActor* actor, elfProperty* property);
ELF_API void ELF_APIENTRY elfRemoveActorProperties(elfActor* actor);

ELF_API void ELF_APIENTRY elfSetActorSelected(elfActor* actor, unsigned char selected);
ELF_API unsigned char ELF_APIENTRY elfGetActorSelected(elfActor* actor);

/* <!> */ void elfDrawActorDebug(elfActor* actor, gfxShaderParams* shaderParams);

//////////////////////////////// CAMERA ////////////////////////////////

// <!!
void elfUpdateCamera(elfCamera* camera);
void elfCameraPreDraw(elfCamera* camera);
void elfCamearPostDraw(elfCamera* camera);
void elfDestroyCamera(void* data);
// !!>

ELF_API elfCamera* ELF_APIENTRY elfCreateCamera(const char* name);	// <mdoc> CAMERA FUNCTIONS

ELF_API void ELF_APIENTRY elfSetCameraViewport(elfCamera* camera, int x, int y, int width, int height);
ELF_API void ELF_APIENTRY elfSetCameraOrthoViewport(elfCamera* camera, int x, int y, int width, int height);
ELF_API void ELF_APIENTRY elfSetCameraMode(elfCamera* camera, int mode);
ELF_API void ELF_APIENTRY elfSetCameraFov(elfCamera* camera, float fov);
ELF_API void ELF_APIENTRY elfSetCameraAspect(elfCamera* camera, float aspect);
ELF_API void ELF_APIENTRY elfSetCameraClip(elfCamera* camera, float clipNear, float clipFar);

ELF_API elfVec2i ELF_APIENTRY elfGetCameraViewportSize(elfCamera* camera);
ELF_API elfVec2i ELF_APIENTRY elfGetCameraViewportOffset(elfCamera* camera);
ELF_API elfVec2i ELF_APIENTRY elfGetCameraOrthoViewportSize(elfCamera* camera);
ELF_API elfVec2i ELF_APIENTRY elfGetCameraOrthoViewportOffset(elfCamera* camera);
ELF_API int ELF_APIENTRY elfGetCameraMode(elfCamera* camera);
ELF_API float ELF_APIENTRY elfGetCameraFov(elfCamera* camera);
ELF_API float ELF_APIENTRY elfGetCameraAspect(elfCamera* camera);
ELF_API elfVec2f ELF_APIENTRY elfGetCameraClip(elfCamera* camera);
ELF_API elfVec2f ELF_APIENTRY elfGetCameraFarPlaneSize(elfCamera* camera);

// <!!
float* elfGetCameraProjectionMatrix(elfCamera* camera);
float* elfGetCameraModelviewMatrix(elfCamera* camera);
void elfSetCamera(elfCamera* camera, gfxShaderParams* shaderParams);
unsigned char elfAabbInsideFrustum(elfCamera* camera, float* min, float* max);
unsigned char elfSphereInsideFrustum(elfCamera* camera, float* pos, float radius);
unsigned char elfCameraInsideAabb(elfCamera* camera, float* min, float* max);
unsigned char elfCameraInsideSphere(elfCamera* camera, float* pos, float radius);
void elfDrawCameraDebug(elfCamera* camera, gfxShaderParams* shaderParams);
// !!>

ELF_API elfVec3f ELF_APIENTRY elfProjectCameraPoint(elfCamera* camera, float x, float y, float z);
ELF_API elfVec3f ELF_APIENTRY elfUnProjectCameraPoint(elfCamera* camera, float x, float y, float z);

//////////////////////////////// MESH DATA ////////////////////////////////

ELF_API elfVertex* ELF_APIENTRY elfCreateVertex();	// <mdoc> MESH DATA FUNCTIONS
/* <!> */ void elfDestroyVertex(void* data);

ELF_API void ELF_APIENTRY elfSetVertexPosition(elfVertex* vertice, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetVertexNormal(elfVertex* vertice, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetVertexTexCoord(elfVertex* vertice, float u, float v);

ELF_API elfVec3f ELF_APIENTRY elfGetVertexPosition(elfVertex* vertice);
ELF_API elfVec3f ELF_APIENTRY elfGetVertexNormal(elfVertex* vertice);
ELF_API elfVec2f ELF_APIENTRY elfGetVertexTexCoord(elfVertex* vertice);

// <!!
elfFace* elfCreateFace();
void elfDestroyFace(void* data);
// !!>

ELF_API int ELF_APIENTRY elfGetFaceV1(elfFace* face);
ELF_API int ELF_APIENTRY elfGetFaceV2(elfFace* face);
ELF_API int ELF_APIENTRY elfGetFaceV3(elfFace* face);

ELF_API elfMeshData* ELF_APIENTRY elfCreateMeshData();
/* <!> */ void elfDestroyMeshData(void* data);

ELF_API int ELF_APIENTRY elfGetMeshDataVertexCount(elfMeshData* meshData);
ELF_API int ELF_APIENTRY elfGetMeshDataFaceCount(elfMeshData* meshData);

ELF_API void ELF_APIENTRY elfAddMeshDataVertex(elfMeshData* meshData, elfVertex* vertice);
ELF_API void ELF_APIENTRY elfAddMeshDataFace(elfMeshData* meshData, int v1, int v2, int v3);

ELF_API elfVertex* ELF_APIENTRY elfGetVertexFromMeshData(elfMeshData* meshData, int idx);
ELF_API elfFace* ELF_APIENTRY elfGetFaceFromMeshData(elfMeshData* meshData, int idx);

//////////////////////////////// MODEL ////////////////////////////////

// <!!
elfModel* elfCreateModel(const char* name);
void elfDestroyModel(void* data);
void elfGenerateModelTangents(elfModel* model);
// !!>

ELF_API elfModel* ELF_APIENTRY elfCreateModelFromMeshData(elfMeshData* data);	// <mdoc> MODEL FUNCTIONS

ELF_API void ELF_APIENTRY elfSetModelName(elfModel* model, const char* name);
ELF_API const char* ELF_APIENTRY elfGetModelName(elfModel* model);
ELF_API const char* ELF_APIENTRY elfGetModelFilePath(elfModel* model);
ELF_API int ELF_APIENTRY elfGetModelVertexCount(elfModel* model);
ELF_API int ELF_APIENTRY elfGetModelIndiceCount(elfModel* model);
ELF_API elfVec3f ELF_APIENTRY elfGetModelBoundingBoxMin(elfModel* model);
ELF_API elfVec3f ELF_APIENTRY elfGetModelBoundingBoxMax(elfModel* model);

// <!!
float* elfGetModelVertexs(elfModel* model);
float* elfGetModelNormals(elfModel* model);
float* elfGetModelTexCoords(elfModel* model);
float* elfGetModelTangents(elfModel* model);
unsigned int* elfGetModelIndices(elfModel* model);

void elfDrawModel(elfList* material, elfModel* model, int mode, gfxShaderParams* shaderParams);
void elfDrawModelBoudingBox(elfModel* model, gfxShaderParams* shaderParams);
// !!>

//////////////////////////////// ENTITY ////////////////////////////////

// <!!
void elfUpdateEntity(elfEntity* entity);
void elfEntityPreDraw(elfEntity* entity);
void elfEntityPostDraw(elfEntity* entity);
void elfDestroyEntity(void* data);
void elfCalcEntityAabb(elfEntity* entity);
void elfCalcEntityBoundingVolumes(elfEntity* entity, unsigned char newModel);
// !!>

ELF_API elfEntity* ELF_APIENTRY elfCreateEntity(const char* name);	// <mdoc> ENTITY FUNCTIONS
ELF_API void ELF_APIENTRY elfGenerateEntityTangents(elfEntity* entity);

ELF_API void ELF_APIENTRY elfSetEntityScale(elfEntity* entity, float x, float y, float z);
ELF_API elfVec3f ELF_APIENTRY elfGetEntityScale(elfEntity* entity);
/* <!> */ void elfGetEntityScale_(elfEntity* entity, float* scale);

ELF_API void ELF_APIENTRY elfSetEntityModel(elfEntity* entity, elfModel* model);
ELF_API void ELF_APIENTRY elfClearEntityModel(elfEntity* entity);
ELF_API elfModel* ELF_APIENTRY elfGetEntityModel(elfEntity* entity);
ELF_API int ELF_APIENTRY elfGetEntityMaterialCount(elfEntity* entity);
ELF_API void ELF_APIENTRY elfAddEntityMaterial(elfEntity* entity, elfMaterial* material);
ELF_API void ELF_APIENTRY elfSetEntityMaterial(elfEntity* entity, int idx, elfMaterial* material);
ELF_API void ELF_APIENTRY elfRemoveEntityMaterial(elfEntity* entity, int idx);
ELF_API elfMaterial* ELF_APIENTRY elfGetEntityMaterial(elfEntity* entity, int idx);

ELF_API void ELF_APIENTRY elfSetEntityVisible(elfEntity* entity, unsigned char visible);
ELF_API unsigned char ELF_APIENTRY elfGetEntityVisible(elfEntity* entity);

ELF_API void ELF_APIENTRY elfSetEntityOccluder(elfEntity* entity, unsigned char occluder);
ELF_API unsigned char ELF_APIENTRY elfGetEntityOccluder(elfEntity* entity);

ELF_API void ELF_APIENTRY elfSetEntityArmature(elfEntity* entity, elfArmature* armature);
ELF_API void ELF_APIENTRY elfSetEntityArmatureFrame(elfEntity* entity, float frame);
ELF_API void ELF_APIENTRY elfPlayEntityArmature(elfEntity* entity, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfLoopEntityArmature(elfEntity* entity, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfStopEntityArmature(elfEntity* entity);
ELF_API void ELF_APIENTRY elfPauseEntityArmature(elfEntity* entity);
ELF_API void ELF_APIENTRY elfResumeEntityArmature(elfEntity* entity);
ELF_API float ELF_APIENTRY elfGetEntityArmatureStart(elfEntity* entity);
ELF_API float ELF_APIENTRY elfGetEntityArmatureEnd(elfEntity* entity);
ELF_API float ELF_APIENTRY elfGetEntityArmatureSpeed(elfEntity* entity);
ELF_API float ELF_APIENTRY elfGetEntityArmatureFrame(elfEntity* entity);
ELF_API unsigned char ELF_APIENTRY elfIsEntityArmaturePlaying(elfEntity* entity);
ELF_API unsigned char ELF_APIENTRY elfIsEntityArmaturePaused(elfEntity* entity);

ELF_API elfArmature* ELF_APIENTRY elfGetEntityArmature(elfEntity* entity);

// <!!
void elfResetEntityDebugPhysicsObject(elfEntity* entity);
void elfDrawEntity(elfEntity* entity, int mode, gfxShaderParams* shaderParams);
void elfDrawEntityBoundingBox(elfEntity* entity, gfxShaderParams* shaderParams);
void elfDrawEntityDebug(elfEntity* entity, gfxShaderParams* shaderParams);
unsigned char elfCullEntity(elfEntity* entity, elfCamera* camera);
// !!>

ELF_API unsigned char ELF_APIENTRY elfGetEntityChanged(elfEntity* entity);

//////////////////////////////// LIGHT ////////////////////////////////

// <!!
void elfUpdateLight(elfLight* light);
void elfLightPreDraw(elfLight* light);
void elfLightPostDraw(elfLight* light);
void elfDestroyLight(void* data);
// !!>

ELF_API elfLight* ELF_APIENTRY elfCreateLight(const char* name);	// <mdoc> LIGHT FUNCTIONS

ELF_API void ELF_APIENTRY elfSetLightType(elfLight* light, int type);
ELF_API void ELF_APIENTRY elfSetLightColor(elfLight* light, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetLightRange(elfLight* light, float range, float fadeRange);
ELF_API void ELF_APIENTRY elfSetLightShadows(elfLight* light, unsigned char shadows);
ELF_API void ELF_APIENTRY elfSetLightVisible(elfLight* light, unsigned char visible);
ELF_API void ELF_APIENTRY elfSetLightCone(elfLight* light, float innerCone, float outerCone);
ELF_API void ELF_APIENTRY elfSetLightShaft(elfLight* light, unsigned char shaft);
ELF_API void ELF_APIENTRY elfSetLightShaftSize(elfLight* light, float size);
ELF_API void ELF_APIENTRY elfSetLightShaftIntensity(elfLight* light, float intensity);
ELF_API void ELF_APIENTRY elfSetLightShaftFadeOff(elfLight* light, float fadeOff);

ELF_API int ELF_APIENTRY elfGetLightType(elfLight* light);
ELF_API elfColor ELF_APIENTRY elfGetLightColor(elfLight* light);
ELF_API float ELF_APIENTRY elfGetLightRange(elfLight* light);
ELF_API float ELF_APIENTRY elfGetLightFadeRange(elfLight* light);
ELF_API unsigned char ELF_APIENTRY elfGetLightShadows(elfLight* light);
ELF_API unsigned char ELF_APIENTRY elfGetLightVisible(elfLight* light);
ELF_API float ELF_APIENTRY elfGetLightInnerCone(elfLight* light);
ELF_API float ELF_APIENTRY elfGetLightOuterCone(elfLight* light);
ELF_API unsigned char ELF_APIENTRY elfGetLightShaft(elfLight* light);
ELF_API float ELF_APIENTRY elfGetLightShaftSize(elfLight* light);
ELF_API float ELF_APIENTRY elfGetLightShaftIntensity(elfLight* light);
ELF_API float ELF_APIENTRY elfGetLightShaftFadeOff(elfLight* light);

// <!!
void elfSetLight(elfLight* light, elfCamera* camera, gfxShaderParams* shaderParams);
void elfDrawLightDebug(elfLight* light, gfxShaderParams* shaderParams);
unsigned char elfGetLightChanged(elfLight* light);
// !!>

//////////////////////////////// ARMATURE ////////////////////////////////

// <!!
elfBone* elfCreateBone(const char* name);
void elfDestroyBone(void* data);
// !!>

ELF_API elfArmature* ELF_APIENTRY elfGetBoneArmature(elfBone* bone);	// <mdoc> ARMATURE FUNCTIONS
ELF_API elfBone* ELF_APIENTRY elfGetBoneParent(elfBone* bone);
ELF_API elfBone* ELF_APIENTRY elfGetBoneChildByName(elfBone* bone, const char* name);
ELF_API elfBone* ELF_APIENTRY elfGetBoneChildById(elfBone* bone, int id);
ELF_API elfBone* ELF_APIENTRY elfGetBoneChildByIndex(elfBone* bone, int idx);
ELF_API elfVec3f ELF_APIENTRY elfGetBonePosition(elfBone* bone);
ELF_API elfVec3f ELF_APIENTRY elfGetBoneRotation(elfBone* bone);
ELF_API elfVec4f ELF_APIENTRY elfGetBoneOrientation(elfBone* bone);

// <!!
void elfUpdateArmature(elfArmature* armature);
void elfDestroyArmature(void* data);
// !!>

ELF_API elfArmature* ELF_APIENTRY elfCreateArmature(const char* name);

ELF_API elfBone* ELF_APIENTRY elfGetBoneFromArmatureByName(const char* name, elfArmature* armature);
ELF_API elfBone* ELF_APIENTRY elfGetBoneFromArmatureById(int id, elfArmature* armature);

// <!!
void elfAddRootBoneToArmature(elfArmature* armature, elfBone* bone);

void elfDeformEntityWithArmature(elfArmature* armature, elfEntity* entity, float frame);
void elfDrawArmatureDebug(elfArmature* armature, gfxShaderParams* shaderParams);
// !!>

//////////////////////////////// PARTICLES ////////////////////////////////

// <!!
elfParticle* elfCreateParticle();
void elfDestroyParticle(void* data);
void elfParticlesPreDraw(elfParticles* particles);
void elfParticlesPostDraw(elfParticles* particles);
void elfUpdateParticles(elfParticles* particles, float sync);
void elfDestroyParticles(void* data);
// !!>

ELF_API elfParticles* ELF_APIENTRY elfCreateParticles(const char* name, int maxCount);	// <mdoc> PARTICLE FUNCTIONS

ELF_API const char* ELF_APIENTRY elfGetParticlesName(elfParticles* particles);
ELF_API const char* ELF_APIENTRY elfGetParticlesFilePath(elfParticles* particles);

ELF_API void ELF_APIENTRY elfSetParticlesMaxCount(elfParticles* particles, int maxCount);
ELF_API void ELF_APIENTRY elfSetParticlesDrawMode(elfParticles* particles, int mode);
ELF_API void ELF_APIENTRY elfSetParticlesTexture(elfParticles* particles, elfTexture* texture);
ELF_API void ELF_APIENTRY elfClearParticlesTexture(elfParticles* particles);
ELF_API void ELF_APIENTRY elfSetParticlesModel(elfParticles* particles, elfModel* model);
ELF_API void ELF_APIENTRY elfClearParticlesModel(elfParticles* particles);
ELF_API void ELF_APIENTRY elfSetParticlesEntity(elfParticles* particles, elfEntity* entity);
ELF_API void ELF_APIENTRY elfClearParticlesEntity(elfParticles* particles);
ELF_API void ELF_APIENTRY elfSetParticlesGravity(elfParticles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesSpawnCount(elfParticles* particles, int perSecond);
ELF_API void ELF_APIENTRY elfSetParticlesSpawn(elfParticles* particles, unsigned char spawn);

ELF_API void ELF_APIENTRY elfSetParticlesSize(elfParticles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesSizeGrowth(elfParticles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesRotation(elfParticles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesRotationGrowth(elfParticles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesLifeSpan(elfParticles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesFadeSpeed(elfParticles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesPositionMin(elfParticles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesPositionMax(elfParticles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesVelocityMin(elfParticles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesVelocityMax(elfParticles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesColorMin(elfParticles* particles, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetParticlesColorMax(elfParticles* particles, float r, float g, float b, float a);

ELF_API int ELF_APIENTRY elfGetParticlesMaxCount(elfParticles* particles);
ELF_API int ELF_APIENTRY elfGetParticlesCount(elfParticles* particles);
ELF_API int ELF_APIENTRY elfGetParticlesDrawMode(elfParticles* particles);
ELF_API elfTexture* ELF_APIENTRY elfGetParticlesTexture(elfParticles* particles);
ELF_API elfModel* ELF_APIENTRY elfGetParticlesModel(elfParticles* particles);
ELF_API elfEntity* ELF_APIENTRY elfGetParticlesEntity(elfParticles* particles);
ELF_API elfVec3f ELF_APIENTRY elfGetParticlesGravity(elfParticles* particles);
ELF_API int ELF_APIENTRY elfGetParticlesSpawnCount(elfParticles* particles);
ELF_API unsigned char ELF_APIENTRY elfGetParticlesSpawn(elfParticles* particles);

ELF_API float ELF_APIENTRY elfGetParticlesSizeMin(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesSizeMax(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesSizeGrowthMin(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesSizeGrowthMax(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesRotationMin(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesRotationMax(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesRotationGrowthMin(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesRotationGrowthMax(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesLifeSpanMin(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesLifeSpanMax(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesFadeSpeedMin(elfParticles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesFadeSpeedMax(elfParticles* particles);
ELF_API elfVec3f ELF_APIENTRY elfGetParticlesPositionMin(elfParticles* particles);
ELF_API elfVec3f ELF_APIENTRY elfGetParticlesPositionMax(elfParticles* particles);
ELF_API elfVec3f ELF_APIENTRY elfGetParticlesVelocityMin(elfParticles* particles);
ELF_API elfVec3f ELF_APIENTRY elfGetParticlesVelocityMax(elfParticles* particles);
ELF_API elfColor ELF_APIENTRY elfGetParticlesColorMin(elfParticles* particles);
ELF_API elfColor ELF_APIENTRY elfGetParticlesColorMax(elfParticles* particles);

// <!!
void elfDrawParticlesDebug(elfParticles* particles, gfxShaderParams* shaderParams);
void elfDrawParticles(elfParticles* particles, elfCamera* camera, gfxShaderParams* shaderParams);
unsigned char elfCullParticles(elfParticles* particles, elfCamera* camera);
// !!>

//////////////////////////////// SPRITE ////////////////////////////////

// <!!
void elfUpdateSprite(elfSprite* sprite);
void elfSpritePreDraw(elfSprite* sprite, elfCamera* camera);
void elfSpritePostDraw(elfSprite* sprite);
void elfDestroySprite(void* data);
// !!>

ELF_API elfSprite* ELF_APIENTRY elfCreateSprite(const char* name);	// <mdoc> SPRITE FUNCTIONS

ELF_API void ELF_APIENTRY elfSetSpriteMaterial(elfSprite* sprite, elfMaterial* material);
ELF_API void ELF_APIENTRY elfSetSpriteScale(elfSprite* sprite, float x, float y);
ELF_API void ELF_APIENTRY elfSetSpriteFaceCamera(elfSprite* sprite, unsigned char faceCamera);

ELF_API elfMaterial* ELF_APIENTRY elfGetSpriteMaterial(elfSprite* sprite);
ELF_API elfVec2f ELF_APIENTRY elfGetSpriteScale(elfSprite* sprite);
ELF_API unsigned char ELF_APIENTRY elfGetSpriteFaceCamera(elfSprite* sprite);

ELF_API void ELF_APIENTRY elfSetSpriteVisible(elfSprite* sprite, unsigned char visible);
ELF_API unsigned char ELF_APIENTRY elfGetSpriteVisible(elfSprite* sprite);

ELF_API void ELF_APIENTRY elfSetSpriteOccluder(elfSprite* sprite, unsigned char occluder);
ELF_API unsigned char ELF_APIENTRY elfGetSpriteOccluder(elfSprite* sprite);

// <!!
unsigned char elfCullSprite(elfSprite* sprite, elfCamera* camera);
void elfDrawSprite(elfSprite* sprite, int mode, gfxShaderParams* shaderParams);
void elfDrawSpriteDebug(elfSprite* sprite, gfxShaderParams* shaderParams);
// !!>

//////////////////////////////// SCENE ////////////////////////////////

// <!!
void elfUpdateScene(elfScene* scene, float sync);
void elfScenePreDraw(elfScene* scene);
void elfScenePostDraw(elfScene* scene);
void elfDestroyScene(void* data);
// !!>

ELF_API const char* ELF_APIENTRY elfGetSceneName(elfScene* scene);
ELF_API const char* ELF_APIENTRY elfGetSceneFilePath(elfScene* scene);

ELF_API elfScene* ELF_APIENTRY elfCreateScene(const char* name);	// <mdoc> SCENE FUNCTIONS
ELF_API elfScene* ELF_APIENTRY elfCreateSceneFromFile(const char* name, const char* filePath);
ELF_API unsigned char ELF_APIENTRY elfSaveScene(elfScene* scene, const char* filePath);

ELF_API void ELF_APIENTRY elfSetScenePhysics(elfScene* scene, unsigned char physics);
ELF_API unsigned char ELF_APIENTRY elfGetScenePhysics(elfScene* scene);

ELF_API void ELF_APIENTRY elfSetSceneRunScripts(elfScene* scene, unsigned char runScripts);
ELF_API unsigned char ELF_APIENTRY elfGetSceneRunScripts(elfScene* scene);

ELF_API void ELF_APIENTRY elfSetSceneDebugDraw(elfScene* scene, unsigned char debugDraw);
ELF_API unsigned char ELF_APIENTRY elfGetSceneDebugDraw(elfScene* scene);

ELF_API void ELF_APIENTRY elfSetSceneOcclusionCulling(elfScene* scene, unsigned char occlusionCulling);
ELF_API unsigned char ELF_APIENTRY elfGetSceneOcclusionCulling(elfScene* scene);

ELF_API void ELF_APIENTRY elfSetSceneGravity(elfScene* scene, float x, float y, float z);
ELF_API elfVec3f ELF_APIENTRY elfGetSceneGravity(elfScene* scene);

ELF_API void ELF_APIENTRY elfSetSceneAmbientColor(elfScene* scene, float r, float g, float b, float a);
ELF_API elfColor ELF_APIENTRY elfGetSceneAmbientColor(elfScene* scene);

ELF_API void ELF_APIENTRY elfSetSceneFog(elfScene* scene, unsigned char fog);
ELF_API void ELF_APIENTRY elfSetSceneFogStart(elfScene* scene, float start);
ELF_API void ELF_APIENTRY elfSetSceneFogEnd(elfScene* scene, float end);
ELF_API void ELF_APIENTRY elfSetSceneFogColor(elfScene* scene, float r, float g, float b, float a);

ELF_API unsigned char ELF_APIENTRY elfGetSceneFog(elfScene* scene);
ELF_API float ELF_APIENTRY elfGetSceneFogStart(elfScene* scene);
ELF_API float ELF_APIENTRY elfGetFogEnd(elfScene* scene);
ELF_API elfColor ELF_APIENTRY elfGetFogColor(elfScene* scene);

ELF_API int ELF_APIENTRY elfGetSceneCameraCount(elfScene* scene);
ELF_API int ELF_APIENTRY elfGetSceneEntityCount(elfScene* scene);
ELF_API int ELF_APIENTRY elfGetSceneLightCount(elfScene* scene);
ELF_API int ELF_APIENTRY elfGetSceneArmatureCount(elfScene* scene);
ELF_API int ELF_APIENTRY elfGetSceneParticlesCount(elfScene* scene);
ELF_API int ELF_APIENTRY elfGetSceneSpriteCount(elfScene* scene);

ELF_API void ELF_APIENTRY elfAddSceneCamera(elfScene* scene, elfCamera* camera);
ELF_API void ELF_APIENTRY elfAddSceneEntity(elfScene* scene, elfEntity* entity);
ELF_API void ELF_APIENTRY elfAddSceneLight(elfScene* scene, elfLight* light);
ELF_API void ELF_APIENTRY elfAddSceneParticles(elfScene* scene, elfParticles* particles);
ELF_API void ELF_APIENTRY elfAddSceneSprite(elfScene* scene, elfSprite* sprite);

ELF_API void ELF_APIENTRY elfSetSceneActiveCamera(elfScene* scene, elfCamera* camera);
ELF_API elfCamera* ELF_APIENTRY elfGetSceneActiveCamera(elfScene* scene);
ELF_API elfCollision* ELF_APIENTRY elfGetSceneRayCastResult(elfScene* scene, float x, float y, float z, float dx, float dy, float dz);
ELF_API elfList* ELF_APIENTRY elfGetSceneRayCastResults(elfScene* scene, float x, float y, float z, float dx, float dy, float dz);
ELF_API elfCollision* ELF_APIENTRY elfGetDebugSceneRayCastResult(elfScene* scene, float x, float y, float z, float dx, float dy, float dz);
ELF_API elfList* ELF_APIENTRY elfGetDebugSceneRayCastResults(elfScene* scene, float x, float y, float z, float dx, float dy, float dz);

ELF_API elfCamera* ELF_APIENTRY elfGetSceneCameraByIndex(elfScene* scene, int idx);
ELF_API elfEntity* ELF_APIENTRY elfGetSceneEntityByIndex(elfScene* scene, int idx);
ELF_API elfLight* ELF_APIENTRY elfGetSceneLightByIndex(elfScene* scene, int idx);
ELF_API elfArmature* ELF_APIENTRY elfGetSceneArmatureByIndex(elfScene* scene, int idx);
ELF_API elfParticles* ELF_APIENTRY elfGetSceneParticlesByIndex(elfScene* scene, int idx);
ELF_API elfSprite* ELF_APIENTRY elfGetSceneSpriteByIndex(elfScene* scene, int idx);

ELF_API elfTexture* ELF_APIENTRY elfGetSceneTexture(elfScene* scene, const char* name);
ELF_API elfMaterial* ELF_APIENTRY elfGetSceneMaterial(elfScene* scene, const char* name);
ELF_API elfModel* ELF_APIENTRY elfGetSceneModel(elfScene* scene, const char* name);
ELF_API elfScript* ELF_APIENTRY elfGetSceneScript(elfScene* scene, const char* name);
ELF_API elfCamera* ELF_APIENTRY elfGetSceneCamera(elfScene* scene, const char* name);
ELF_API elfEntity* ELF_APIENTRY elfGetSceneEntity(elfScene* scene, const char* name);
ELF_API elfLight* ELF_APIENTRY elfGetSceneLight(elfScene* scene, const char* name);
ELF_API elfArmature* ELF_APIENTRY elfGetSceneArmature(elfScene* scene, const char* name);
ELF_API elfParticles* ELF_APIENTRY elfGetSceneParticles(elfScene* scene, const char* name);
ELF_API elfSprite* ELF_APIENTRY elfGetSceneSprite(elfScene* scene, const char* name);
ELF_API elfActor* ELF_APIENTRY elfGetSceneActor(elfScene* scene, const char* name);

// <!!
elfTexture* elfGetOrLoadTextureByName(elfScene* scene, const char* name);
elfModel* elfGetOrLoadModelByName(elfScene* scene, const char* name);
elfScript* elfGetOrLoadScriptByName(elfScene* scene, const char* name);
elfCamera* elfGetOrLoadCameraByName(elfScene* scene, const char* name);
elfEntity* elfGetOrLoadEntityByName(elfScene* scene, const char* name);
elfParticles* elfGetOrLoadParticlesByName(elfScene* scene, const char* name);
elfSprite* elfGetOrLoadSpriteByName(elfScene* scene, const char* name);
elfLight* elfGetOrLoadLightByName(elfScene* scene, const char* name);
elfArmature* elfGetOrLoadArmatureByName(elfScene* scene, const char* name);
elfMaterial* elfGetOrLoadMaterialByName(elfScene* scene, const char* name);
elfActor* elfGetOrLoadActorByName(elfScene* scene, const char* name);

void elfRemoveActor(elfActor* actor);
// !!>
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneCamera(elfScene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneEntity(elfScene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneLight(elfScene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneParticles(elfScene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneSprite(elfScene* scene, const char* name);

ELF_API unsigned char ELF_APIENTRY elfRemoveSceneCameraByIndex(elfScene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneEntityByIndex(elfScene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneLightByIndex(elfScene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneParticlesByIndex(elfScene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneSpriteByIndex(elfScene* scene, int idx);

ELF_API unsigned char ELF_APIENTRY elfRemoveSceneCameraByObject(elfScene* scene, elfCamera* camera);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneEntityByObject(elfScene* scene, elfEntity* entity);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneLightByObject(elfScene* scene, elfLight* light);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneParticlesByObject(elfScene* scene, elfParticles* particles);
ELF_API unsigned char ELF_APIENTRY elfRemoveSceneSpriteByObject(elfScene* scene, elfSprite* sprite);

ELF_API unsigned char ELF_APIENTRY elfRemoveSceneActorByObject(elfScene* scene, elfActor* actor);

// <!!
void elfDrawScene(elfScene* scene);
void elfDrawSceneDebug(elfScene* scene);
// !!>

ELF_API elfList* ELF_APIENTRY elfGetSceneScripts(elfScene* scene);
ELF_API elfList* ELF_APIENTRY elfGetSceneTextures(elfScene* scene);
ELF_API elfList* ELF_APIENTRY elfGetSceneMaterials(elfScene* scene);
ELF_API elfList* ELF_APIENTRY elfGetSceneModels(elfScene* scene);

//////////////////////////////// PAK ////////////////////////////////

// <!!
elfPakIndex* elfCreatePakIndex();
void elfDestroyPakIndex(void* data);
elfPak* elfCreatePakFromFile(const char* filePath);
void elfDestroyPak(void* data);

const char* elfGetPakFilePath(elfPak* pak);
int elfGetPakIndexCount(elfPak* pak);

elfPakIndex* elfGetPakIndexByName(elfPak* pak, const char* name, unsigned char type);
elfPakIndex* elfGetPakIndexByIndex(elfPak* pak, int idx);
unsigned char elfGetPakIndexType(elfPakIndex* index);
const char* elfGetPakIndexName(elfPakIndex* index);
int elfGetPakIndexOffset(elfPakIndex* index);

int elfGetActorHeaderSizeBytes(elfActor* actor);
int elfGetArmatureSizeBytes(elfArmature* armature);
int elfGetCameraSizeBytes(elfCamera* camera);
int elfGetEntitySizeBytes(elfEntity* entity);
int elfGetLightSizeBytes(elfLight* light);
int elfGetMaterialSizeBytes(elfMaterial* material);
int elfGetModelSizeBytes(elfModel* model);
int elfGetParticlesSizeBytes(elfParticles* particles);
int elfGetSceneSizeBytes(elfScene* scene);
int elfGetScriptSizeBytes(elfScript* script);
int elfGetSpriteSizeBytes(elfSprite* sprite);
int elfGetTextureSizeBytes(elfTexture* texture);

void elfReadActorHeader(elfActor* actor, FILE* file, elfScene* scene);
elfArmature* elfCreateArmatureFromPak(FILE* file, const char* name, elfScene* scene);
elfCamera* elfCreateCameraFromPak(FILE* file, const char* name, elfScene* scene);
elfEntity* elfCreateEntityFromPak(FILE* file, const char* name, elfScene* scene);
elfLight* elfCreateLightFromPak(FILE* file, const char* name, elfScene* scene);
elfMaterial* elfCreateMaterialFromPak(FILE* file, const char* name, elfScene* scene);
elfModel* elfCreateModelFromPak(FILE* file, const char* name, elfScene* scene);
elfParticles* elfCreateParticlesFromPak(FILE* file, const char* name, elfScene* scene);
elfScript* elfCreateScriptFromPak(FILE* file, const char* name, elfScene* scene);
elfSprite* elfCreateSpriteFromPak(FILE* file, const char* name, elfScene* scene);
elfTexture* elfCreateTextureFromPak(FILE* file, const char* name, elfScene* scene);
unsigned char elfLoadTextureDataFromPak(elfTexture* texture);

elfScene* elfCreateSceneFromPak(const char* name, elfPak* pak);

void elfWriteActorHeader(elfActor* actor, FILE* file);
void elfWriteArmatureToFile(elfArmature* armature, FILE* file);
void elfWriteCameraToFile(elfCamera* camera, FILE* file);
void elfWriteEntityToFile(elfEntity* entity, FILE* file);
void elfWriteLightToFile(elfLight* light, FILE* file);
void elfWriteMaterialToFile(elfMaterial* material, FILE* file);
void elfWriteModelToFile(elfModel* model, FILE* file);
void elfWriteParticlesToFile(elfParticles* particles, FILE* file);
void elfWriteScriptToFile(elfScript* script, FILE* file);
void elfWriteSpriteToFile(elfSprite* sprite, FILE* file);
void elfWriteTextureToFile(elfTexture* texture, FILE* file);

unsigned char elfSaveSceneToPak(elfScene* scene, const char* filePath);
// !!>

//////////////////////////////// POST PROCESS ////////////////////////////////

// <!!
elfPostProcess* elfCreatePostProcess();
void elfDestroyPostProcess(void* data);

void elfInitPostProcessBuffers(elfPostProcess* postProcess);

void elfRunPostProcess(elfPostProcess* postProcess, elfScene* scene);

void elfSetPostProcessBloom(elfPostProcess* postProcess, float threshold);
void elfDisablePostProcessBloom(elfPostProcess* postProcess);
float elfGetPostProcessBloomThreshold(elfPostProcess* postProcess);

void elfSetPostProcessDof(elfPostProcess* postProcess, float focalRange, float focalDistance);
void elfDisablePostProcessDof(elfPostProcess* postProcess);
float elfGetPostProcessDofFocalRange(elfPostProcess* postProcess);
float elfGetPostProcessDofFocalDistance(elfPostProcess* postProcess);

void elfSetPostProcessSsao(elfPostProcess* postProcess, float amount);
void elfDisablePostProcessSsao(elfPostProcess* postProcess);
float elfGetPostProcessSsaoAmount(elfPostProcess* postProcess);

void elfSetPostProcessLightShafts(elfPostProcess* postProcess, float intensity);
void elfDisablePostProcessLightShafts(elfPostProcess* postProcess);
float elfGetPostProcessLightShaftsIntensity(elfPostProcess* postProcess);

unsigned char elfIsPostProcessBloom(elfPostProcess* postProcess);
unsigned char elfIsPostProcessSsao(elfPostProcess* postProcess);
unsigned char elfIsPostProcessDof(elfPostProcess* postProcess);
unsigned char elfIsPostProcessLightShafts(elfPostProcess* postProcess);
// !!>

//////////////////////////////// SCRIPT ////////////////////////////////

// <!!
void elfDestroyScript(void* data);
// !!>

ELF_API elfScript* ELF_APIENTRY elfCreateScript(const char* name);	// <mdoc> SCRIPT FUNCTIONS
ELF_API elfScript* ELF_APIENTRY elfCreateScriptFromFile(const char* name, const char* filePath);

ELF_API void ELF_APIENTRY elfSetScriptName(elfScript* script, const char* name);

ELF_API const char* ELF_APIENTRY elfGetScriptName(elfScript* script);
ELF_API const char* ELF_APIENTRY elfGetScriptFilePath(elfScript* script);

ELF_API void ELF_APIENTRY elfSetScriptText(elfScript* script, const char* text);
ELF_API unsigned char ELF_APIENTRY elfIsScriptError(elfScript* script);

//////////////////////////////// SCRIPTING ////////////////////////////////

// <!!
elfScripting* elfCreateScripting();
void elfDestroyScripting(void* data);

unsigned char elfInitScripting();
void elfUpdateScripting();
void elfDeinitScripting();

void elfSetScriptError(int err, const char* msg);
// !!>

ELF_API unsigned char ELF_APIENTRY elfRunString(const char* str);	// <mdoc> SCRIPTING FUNCTIONS
ELF_API unsigned char ELF_APIENTRY elfRunScript(elfScript* script);

//////////////////////////////// AUDIO ////////////////////////////////

// <!!
elfAudioDevice* elfCreateAudioDevice();
void elfDestroyAudioDevice(void* data);
unsigned char elfInitAudio();
void elfUpdateAudio();
void elfDeinitAudio();
// !!>
ELF_API void ELF_APIENTRY elfSetAudioVolume(float volume);	// <mdoc> AUDIO FUNCTIONS
ELF_API float ELF_APIENTRY elfGetAudioVolume();
ELF_API void ELF_APIENTRY elfSetAudioRolloff(float rolloff);
ELF_API float ELF_APIENTRY elfGetAudioRolloff();
// <!!
void elfSetAudioListenerPosition(float x, float y, float z);
void elfSetAudioListenerOrientation(float* params);
// !!>

// <!!
elfSound* elfCreateSound();
void elfDestroySound(void* data);
// !!>

ELF_API elfSound* ELF_APIENTRY elfLoadSound(const char* filePath);
ELF_API elfSound* ELF_APIENTRY elfLoadStreamedSound(const char* filePath);
ELF_API int ELF_APIENTRY elfGetSoundFileType(elfSound* sound);

ELF_API elfAudioSource* ELF_APIENTRY elfPlaySound(elfSound* sound, float volume);
ELF_API elfAudioSource* ELF_APIENTRY elfPlayEntitySound(elfEntity* entity, elfSound* sound, float volume);
ELF_API elfAudioSource* ELF_APIENTRY elfLoopSound(elfSound* sound, float volume);
ELF_API elfAudioSource* ELF_APIENTRY elfLoopEntitySound(elfEntity* entity, elfSound* sound, float volume);
// <!!
elfAudioSource* elfCreateAudioSource();
void elfStreamAudioSource(elfAudioSource* source);
void elfDestroyAudioSource(void* data);
// !!>
ELF_API void ELF_APIENTRY elfSetSoundVolume(elfAudioSource* source, float volume);
ELF_API float ELF_APIENTRY elfGetSoundVolume(elfAudioSource* source);
ELF_API void ELF_APIENTRY elfPauseSound(elfAudioSource* source);
ELF_API void ELF_APIENTRY elfResumeSound(elfAudioSource* source);
ELF_API void ELF_APIENTRY elfStopSound(elfAudioSource* source);

ELF_API unsigned char ELF_APIENTRY elfIsSoundPlaying(elfAudioSource* source);
ELF_API unsigned char ELF_APIENTRY elfIsSoundPaused(elfAudioSource* source);
// <!!
void elfSetSoundPosition(elfAudioSource* source, float x, float y, float z);
// !!>

//////////////////////////////// PHYSICS ////////////////////////////////

// <!!
elfCollision* elfCreateCollision();
void elfDestroyCollision(void* data);

elfPhysicsWorld* elfCreatePhysicsWorld();
void elfDestroyPhysicsWorld(void* data);
void elfUpdatePhysicsWorld(elfPhysicsWorld* world, float time);

void elfSetPhysicsWorldGravity(elfPhysicsWorld* world, float x, float y, float z);
elfVec3f elfGetPhysicsWorldGravity(elfPhysicsWorld* world);

elfCollision* elfGetRayCastResult(elfPhysicsWorld* world, float x, float y, float z, float dx, float dy, float dz);
elfList* elfGetRayCastResults(elfPhysicsWorld* world, float x, float y, float z, float dx, float dy, float dz);
// !!>

ELF_API elfActor* ELF_APIENTRY elfGetCollisionActor(elfCollision* collision);	// <mdoc> COLLISION FUNCTIONS
ELF_API elfVec3f ELF_APIENTRY elfGetCollisionPosition(elfCollision* collision);
ELF_API elfVec3f ELF_APIENTRY elfGetCollisionNormal(elfCollision* collision);
ELF_API float ELF_APIENTRY elfGetCollisionDepth(elfCollision* collision);

// <!!
elfJoint* elfCreateJoint();
void elfSetJointWorld(elfJoint* joint, elfPhysicsWorld* world);
elfJoint* elfCreateHingeJoint(elfActor* actor1, elfActor* actor2, const char* name, float px, float py, float pz, float ax, float ay, float az);
elfJoint* elfCreateBallJoint(elfActor* actor1, elfActor* actor2, const char* name, float px, float py, float pz);
elfJoint* elfCreateConeTwistJoint(elfActor* actor1, elfActor* actor2, const char* name, float px, float py, float pz, float ax, float ay, float az);
void elfClearJoint(elfJoint* joint);
void elfDestroyJoint(void* data);
// !!>

ELF_API const char* ELF_APIENTRY elfGetJointName(elfJoint* joint);	// <mdoc> JOINT FUNCTIONS
ELF_API int ELF_APIENTRY elfGetJointType(elfJoint* joint);
ELF_API elfActor* ELF_APIENTRY elfGetJointActorA(elfJoint* joint);
ELF_API elfActor* ELF_APIENTRY elfGetJointActorB(elfJoint* joint);
ELF_API elfVec3f ELF_APIENTRY elfGetJointPivot(elfJoint* joint);
ELF_API elfVec3f ELF_APIENTRY elfGetJointAxis(elfJoint* joint);

// <!!
elfPhysicsTriMesh* elfCreatePhysicsTriMesh(float* verts, unsigned int* idx, int indiceCount);
void elfDestroyPhysicsTriMesh(void* data);

elfPhysicsObject* elfCreatePhysicsObject();
elfPhysicsObject* elfCreatePhysicsObjectMesh(elfPhysicsTriMesh* triMesh, float mass);
elfPhysicsObject* elfCreatePhysicsObjectSphere(float radius, float mass, float ox, float oy, float oz);
elfPhysicsObject* elfCreatePhysicsObjectBox(float hx, float hy, float hz, float mass, float ox, float oy, float oz);
elfPhysicsObject* elfCreatePhysicsObjectCapsule(unsigned char type, float length, float radius, float mass, float ox, float oy, float oz);
elfPhysicsObject* elfCreatePhysicsObjectCone(unsigned char type, float length, float radius, float mass, float ox, float oy, float oz);
void elfSetPhysicsObjectWorld(elfPhysicsObject* object, elfPhysicsWorld* world);
void elfDestroyPhysicsObject(void* data);

void elfSetPhysicsObjectActor(elfPhysicsObject* object, elfActor* actor);
void elfRemovePhysicsObjectCollisions(elfPhysicsObject* objects);
void elfClearPhysicsObjectCollisions(elfPhysicsObject* objects);

int elfGetPhysicsObjectCollisionCount(elfPhysicsObject* object);
elfCollision* elfGetPhysicsObjectCollision(elfPhysicsObject* object, int idx);

void elfSetPhysicsObjectPosition(elfPhysicsObject* object, float x, float y, float z);
void elfSetPhysicsObjectOrientation(elfPhysicsObject* object, float x, float y, float z, float w);
void elfSetPhysicsObjectScale(elfPhysicsObject* object, float x, float y, float z);

int elfGetPhysicsObjectShape(elfPhysicsObject* object);
float elfGetPhysicsObjectMass(elfPhysicsObject* object);
void elfGetPhysicsObjectPosition(elfPhysicsObject* object, float* params);
void elfGetPhysicsObjectOrientation(elfPhysicsObject* object, float* params);
void elfGetPhysicsObjectScale(elfPhysicsObject* object, float* params);
unsigned char elfIsPhysicsObjectStatic(elfPhysicsObject* object);

void elfSetPhysicsObjectDamping(elfPhysicsObject* object, float linDamp, float angDamp);
void elfSetPhysicsObjectAnisotropicFriction(elfPhysicsObject* object, float x, float y, float z);
void elfSetPhysicsObjectSleepThresholds(elfPhysicsObject* object, float linThrs, float angThrs);
void elfSetPhysicsObjectRestitution(elfPhysicsObject* object, float restitution);
void elfAddPhysicsObjectForce(elfPhysicsObject* object, float x, float y, float z);
void elfAddPhysicsObjectTorque(elfPhysicsObject* object, float x, float y, float z);
void elfSetPhysicsObjectLinearVelocity(elfPhysicsObject* object, float x, float y, float z);
void elfSetPhysicsObjectAngularVelocity(elfPhysicsObject* object, float x, float y, float z);
void elfSetPhysicsObjectLinearFactor(elfPhysicsObject* object, float x, float y, float z);
void elfSetPhysicsObjectAngularFactor(elfPhysicsObject* object, float x, float y, float z);

void elfGetPhysicsObjectLinearVelocity(elfPhysicsObject* object, float* params);
void elfGetPhysicsObjectAngularVelocity(elfPhysicsObject* object, float* params);
void elfGetPhysicsObjectLinearFactor(elfPhysicsObject* object, float* params);
void elfGetPhysicsObjectAngularFactor(elfPhysicsObject* object, float* params);
float elfGetPhysicsObjectLinearDamping(elfPhysicsObject* object);
float elfGetPhysicsObjectAngularDamping(elfPhysicsObject* object);
void elfGetPhysicsObjectAnisotropicFriction(elfPhysicsObject* object, float* params);
float elfGetPhysicsObjectLinearSleepThreshold(elfPhysicsObject* object);
float elfGetPhysicsObjectAngularSleepThreshold(elfPhysicsObject* object);
float elfGetPhysicsObjectRestitution(elfPhysicsObject* object);
// !!>

//////////////////////////////// FONT ////////////////////////////////

// <!!
elfFont* elfCreateFont();
void elfDestroyFont(void* data);
// !!>

ELF_API elfFont* ELF_APIENTRY elfCreateFontFromFile(const char* filePath, int size);	// <mdoc> FONT FUNCTIONS

ELF_API const char* ELF_APIENTRY elfGetFontName(elfFont* font);
ELF_API const char* ELF_APIENTRY elfGetFontFilePath(elfFont* font);
ELF_API int ELF_APIENTRY elfGetFontSize(elfFont* font);
ELF_API int ELF_APIENTRY elfGetStringWidth(elfFont* font, const char* str);
ELF_API int ELF_APIENTRY elfGetStringHeight(elfFont* font, const char* str);

/* <!> */ void elfDrawString(elfFont* font, const char* str, int x, int y, gfxShaderParams* shaderParams);

//////////////////////////////// GUI ////////////////////////////////

ELF_API const char* ELF_APIENTRY elfGetGuiObjectName(elfGuiObject* object);	// <mdoc> GUI OBJECT FUNCTIONS <mdocc> Gui object functions can be performed on any gui object.
ELF_API elfVec2i ELF_APIENTRY elfGetGuiObjectPosition(elfGuiObject* object);
ELF_API elfVec2i ELF_APIENTRY elfGetGuiObjectSize(elfGuiObject* object);
ELF_API elfColor ELF_APIENTRY elfGetGuiObjectColor(elfGuiObject* object);
ELF_API unsigned char ELF_APIENTRY elfGetGuiObjectVisible(elfGuiObject* object);
ELF_API unsigned char ELF_APIENTRY elfGetGuiObjectActive(elfGuiObject* object);
ELF_API elfScript* ELF_APIENTRY elfGetGuiObjectScript(elfGuiObject* object);
ELF_API int ELF_APIENTRY elfGetGuiObjectEvent(elfGuiObject* object);

ELF_API void ELF_APIENTRY elfSetGuiObjectPosition(elfGuiObject* object, float x, float y);
ELF_API void ELF_APIENTRY elfSetGuiObjectColor(elfGuiObject* object, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetGuiObjectVisible(elfGuiObject* object, unsigned char visible);
ELF_API void ELF_APIENTRY elfSetGuiObjectActive(elfGuiObject* object, unsigned char active);
ELF_API void ELF_APIENTRY elfSetGuiObjectScript(elfGuiObject* object, elfScript* script);

// <!!
void elfDestroyLabel(void* data);
void elfDrawLabel(elfLabel* label, gfxShaderParams* shaderParams);
void elfRecalcLabel(elfLabel* label);
// !!>

ELF_API elfLabel* ELF_APIENTRY elfCreateLabel(elfGuiObject* parent, const char* name, int x, int y, const char* text);	// <mdoc> LABEL FUNCTIONS

ELF_API elfFont* ELF_APIENTRY elfGetLabelFont(elfLabel* label);
ELF_API const char* ELF_APIENTRY elfGetLabelText(elfLabel* label);

ELF_API void ELF_APIENTRY elfSetLabelFont(elfLabel* label, elfFont* font);
ELF_API void ELF_APIENTRY elfSetLabelText(elfLabel* label, const char* text);

// <!!
void elfDestroyButton(void* data);
void elfDrawButton(elfButton* button, gfxShaderParams* shaderParams);
void elfRecalcButton(elfButton* button);
// !!>

ELF_API elfButton* ELF_APIENTRY elfCreateButton(elfGuiObject* parent, const char* name, int x, int y, int width, int height, const char* text);	// <mdoc> BUTTON FUNCTION

ELF_API unsigned char ELF_APIENTRY elfGetButtonState(elfButton* button);
ELF_API const char* ELF_APIENTRY elfGetButtonText(elfButton* button);
ELF_API elfFont* ELF_APIENTRY elfGetButtonFont(elfButton* button);
ELF_API elfTexture* ELF_APIENTRY elfGetButtonOffTexture(elfButton* button);
ELF_API elfTexture* ELF_APIENTRY elfGetButtonOverTexture(elfButton* button);
ELF_API elfTexture* ELF_APIENTRY elfGetButtonOnTexture(elfButton* button);

ELF_API void ELF_APIENTRY elfSetButtonText(elfButton* button, const char* text);
ELF_API void ELF_APIENTRY elfSetButtonFont(elfButton* button, elfFont* font);
ELF_API void ELF_APIENTRY elfSetButtonSize(elfButton* button, int width, int height);
ELF_API void ELF_APIENTRY elfSetButtonOffTexture(elfButton* button, elfTexture* off);
ELF_API void ELF_APIENTRY elfSetButtonOverTexture(elfButton* button, elfTexture* over);
ELF_API void ELF_APIENTRY elfSetButtonOnTexture(elfButton* button, elfTexture* on);

// <!!
void elfDestroyPicture(void* data);
void elfDrawPicture(elfPicture* picture, gfxShaderParams* shaderParams);
void elfRecalcPicture(elfPicture* picture);
// !!>

ELF_API elfPicture* ELF_APIENTRY elfCreatePicture(elfGuiObject* parent, const char* name, int x, int y, const char* filePath);	// <mdoc> PICTURE FUNCTIONS

ELF_API elfTexture* ELF_APIENTRY elfGetPictureTexture(elfPicture* picture);
ELF_API elfVec2f ELF_APIENTRY elfGetPictureScale(elfPicture* picture);

ELF_API void ELF_APIENTRY elfSetPictureTexture(elfPicture* picture, elfTexture* texture);
ELF_API void ELF_APIENTRY elfSetPictureScale(elfPicture* picture, float x, float y);

// <!!
void elfDestroyTextField(void* data);
void elfDrawTextField(elfTextField* textField, elfArea* area, gfxShaderParams* shaderParams);
void elfRecalcTextField(elfTextField* textField);
// !!>

ELF_API elfTextField* ELF_APIENTRY elfCreateTextField(elfGuiObject* parent, const char* name, int x, int y, int width, const char* text);	// <mdoc> TEXT FIELD FUNCTIONS

ELF_API elfTexture* ELF_APIENTRY elfGetTextFieldTexture(elfTextField* textField);
ELF_API elfFont* ELF_APIENTRY elfGetTextFieldFont(elfTextField* textField);
ELF_API elfColor ELF_APIENTRY elfGetTextFieldTextColor(elfTextField* textField);
ELF_API elfVec2i ELF_APIENTRY elfGetTextFieldOffset(elfTextField* textField);
ELF_API const char* ELF_APIENTRY elfGetTextFieldText(elfTextField* textField);

ELF_API void ELF_APIENTRY elfSetTextFieldFont(elfTextField* textField, elfFont* font);
ELF_API void ELF_APIENTRY elfSetTextFieldWidth(elfTextField* textField, int width);
ELF_API void ELF_APIENTRY elfSetTextFieldTexture(elfTextField* textField, elfTexture* texture);
ELF_API void ELF_APIENTRY elfSetTextFieldTextColor(elfTextField* textField, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetTextFieldOffset(elfTextField* textField, int offsetX, int offsetY);
ELF_API void ELF_APIENTRY elfSetTextFieldCursorPosition(elfTextField* textField, int idx);
ELF_API void ELF_APIENTRY elfSetTextFieldText(elfTextField* textField, const char* text);

// <!!
void elfDestroySlider(void* data);
void elfDrawSlider(elfSlider* slider, gfxShaderParams* shaderParams);
void elfRecalcSlider(elfSlider* slider);
// !!>

ELF_API elfSlider* ELF_APIENTRY elfCreateSlider(elfGuiObject* parent, const char* name, int x, int y, int width, int height, float value);	// <mdoc> SLIDER FUNCTIONS

ELF_API elfTexture* ELF_APIENTRY elfGetSliderBackgroundTexture(elfSlider* slider);
ELF_API elfTexture* ELF_APIENTRY elfGetSliderSliderTexture(elfSlider* slider);
ELF_API float ELF_APIENTRY elfGetSliderValue(elfSlider* slider);

ELF_API void ELF_APIENTRY elfSetSliderSize(elfSlider* slider, int width, int height);
ELF_API void ELF_APIENTRY elfSetSliderBackgroundTexture(elfSlider* slider, elfTexture* background);
ELF_API void ELF_APIENTRY elfSetSliderSliderTexture(elfSlider* slider, elfTexture* sliderTexture);
ELF_API void ELF_APIENTRY elfSetSliderValue(elfSlider* slider, float value);

// <!!
void elfDestroyScreen(void* data);
void elfDrawScreen(elfScreen* screen, elfArea* area, gfxShaderParams* shaderParams);
void elfRecalcScreen(elfScreen* screen);
// !!>

ELF_API elfScreen* ELF_APIENTRY elfCreateScreen(elfGuiObject* parent, const char* name, int x, int y, int width, int height);	// <mdoc> SCREEN FUCNTIONS

ELF_API void ELF_APIENTRY elfSetScreenSize(elfScreen* screen, int width, int height);
ELF_API elfTexture* ELF_APIENTRY elfGetScreenTexture(elfScreen* screen);
ELF_API void ELF_APIENTRY elfSetScreenTexture(elfScreen* screen, elfTexture* texture);
ELF_API void ELF_APIENTRY elfSetScreenToTop(elfScreen* screen);
ELF_API void ELF_APIENTRY elfForceScreenFocus(elfScreen* screen);
ELF_API void ELF_APIENTRY elfReleaseScreenFocus(elfScreen* screen);

// <!!
void elfDestroyTextList(void* data);
void elfDrawTextList(elfTextList* textList, elfArea* area, gfxShaderParams* shaderParams);
void elfRecalcTextList(elfTextList* textList);
// !!>

ELF_API elfTextList* ELF_APIENTRY elfCreateTextList(elfGuiObject* parent, const char* name, int x, int y, int rows, int width);	// <mdoc> TEXT LIST FUNCTIONS

ELF_API elfFont* ELF_APIENTRY elfGetTextListFont(elfTextList* textList);
ELF_API int ELF_APIENTRY elfGetTextListRowCount(elfTextList* textList);
ELF_API int ELF_APIENTRY elfGetTextListItemCount(elfTextList* textList);
ELF_API int ELF_APIENTRY elfGetTextListSelectionIndex(elfTextList* textList);
ELF_API int ELF_APIENTRY elfGetTextListOffset(elfTextList* textList);
ELF_API const char* ELF_APIENTRY elfGetTextListItem(elfTextList* textList, int idx);
ELF_API const char* ELF_APIENTRY elfGetTextListSelectedItem(elfTextList* textList);
ELF_API unsigned char ELF_APIENTRY elfGetTextListItemDrag(elfTextList* textList);

ELF_API void ELF_APIENTRY elfSetTextListFont(elfTextList* textList, elfFont* font);
ELF_API void ELF_APIENTRY elfSetTextListSize(elfTextList* textList, int rows, int width);
ELF_API void ELF_APIENTRY elfAddTextListItem(elfTextList* textList, const char* text);
ELF_API void ELF_APIENTRY elfSetTextListItem(elfTextList* textList, int idx, const char* text);
ELF_API unsigned char ELF_APIENTRY elfRemoveTextListItem(elfTextList* textList, int idx);
ELF_API void ELF_APIENTRY elfRemoveTextListItems(elfTextList* textList);
ELF_API void ELF_APIENTRY elfSetTextListOffset(elfTextList* textList, int offset);
ELF_API void ELF_APIENTRY elfSetTextListSelection(elfTextList* textList, int selection);
ELF_API void ELF_APIENTRY elfSetTextListItemDrag(elfTextList* textList, unsigned char itemDrag);

// <!!
void elfDestroyCheckBox(void* data);
void elfDrawCheckBox(elfCheckBox* checkBox, gfxShaderParams* shaderParams);
void elfRecalcCheckBox(elfCheckBox* checkBox);
// !!>

ELF_API elfCheckBox* ELF_APIENTRY elfCreateCheckBox(elfGuiObject* parent, const char* name, int x, int y, unsigned char state);	// <mdoc> CHECK BOX FUNCTIONS

ELF_API unsigned char ELF_APIENTRY elfGetCheckBoxState(elfCheckBox* checkBox);
ELF_API elfTexture* ELF_APIENTRY elfGetCheckBoxOffTexture(elfCheckBox* checkBox);
ELF_API elfTexture* ELF_APIENTRY elfGetCheckBoxOnTexture(elfCheckBox* checkBox);

ELF_API void ELF_APIENTRY elfSetCheckBoxOffTexture(elfCheckBox* checkBox, elfTexture* off);
ELF_API void ELF_APIENTRY elfSetCheckBoxOnTexture(elfCheckBox* checkBox, elfTexture* on);
ELF_API void ELF_APIENTRY elfSetCheckBoxState(elfCheckBox* checkBox, unsigned char state);

/* <!> */ void elfRecalcGuiObject(elfGuiObject* object);

// <!!
void elfDestroyGui(void* data);
void elfUpdateGui(elfGui* gui, float step);
void elfDrawGui(elfGui* gui);
// !!>

ELF_API elfGui* ELF_APIENTRY elfCreateGui();	// <mdoc> GUI FUNCTIONS

ELF_API unsigned char ELF_APIENTRY elfAddGuiObject(elfGuiObject* parent, elfGuiObject* object);
ELF_API elfGuiObject* ELF_APIENTRY elfGetGuiObjectByName(elfGuiObject* parent, const char* name);
ELF_API elfGuiObject* ELF_APIENTRY elfGetGuiObjectByIndex(elfGuiObject* parent, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveGuiObjectByName(elfGuiObject* parent, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveGuiObjectByIndex(elfGuiObject* parent, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveGuiObjectByObject(elfGuiObject* parent, elfGuiObject* object);

ELF_API elfGuiObject* ELF_APIENTRY elfGetGuiTrace(elfGui* gui);
ELF_API elfGuiObject* ELF_APIENTRY elfGetGuiFocus(elfGui* gui);
ELF_API elfGuiObject* ELF_APIENTRY elfGetGuiActiveTextField(elfGui* gui);
ELF_API unsigned char ELF_APIENTRY elfGetGuiDragging(elfGui* gui);
ELF_API elfGuiObject* ELF_APIENTRY elfGetGuiDragObject(elfGui* gui);
ELF_API const char* ELF_APIENTRY elfGetGuiDragContent(elfGui* gui);

ELF_API void ELF_APIENTRY elfEmptyGui(elfGui* gui);

//////////////////////////////// SST ////////////////////////////////

// <!!
char* elfReadSstNext(const char* text, int* pos, const char* sep);
char* elfReadSstText(const char* text, int* pos);
char* elfReadSstString(const char* text, int* pos);
float elfReadSstFloat(const char* text, int* pos);
void elfReadSstFloats(const char* text, int* pos, int n, float* params);
int elfReadSstInt(const char* text, int* pos);
void elfReadSstInts(const char* text, int* pos, int n, int* params);
unsigned char elfReadSstBool(const char* text, int* pos);
// !!>

// <!!
#ifdef __cplusplus
}
#endif

#endif	// BLENDELF_H
// !!>

