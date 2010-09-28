#ifndef ELF_BINDS_H
#define ELF_BINDS_H
#define ELF_NONE 0x0000
#define ELF_FALSE 0x0000
#define ELF_TRUE 0x0001
#define ELF_KEY_ESC 135
#define ELF_KEY_F1 136
#define ELF_KEY_F2 137
#define ELF_KEY_F3 138
#define ELF_KEY_F4 139
#define ELF_KEY_F5 140
#define ELF_KEY_F6 141
#define ELF_KEY_F7 142
#define ELF_KEY_F8 143
#define ELF_KEY_F9 144
#define ELF_KEY_F10 145
#define ELF_KEY_F11 146
#define ELF_KEY_F12 147
#define ELF_KEY_UP 148
#define ELF_KEY_DOWN 149
#define ELF_KEY_LEFT 150
#define ELF_KEY_RIGHT 151
#define ELF_KEY_LSHIFT 152
#define ELF_KEY_RSHIFT 153
#define ELF_KEY_LCTRL 154
#define ELF_KEY_RCTRL 155
#define ELF_KEY_LALT 156
#define ELF_KEY_RALT 157
#define ELF_KEY_TAB 158
#define ELF_KEY_ENTER 159
#define ELF_KEY_BACKSPACE 160
#define ELF_KEY_INSERT 161
#define ELF_KEY_DEL 162
#define ELF_KEY_PAGEUP 163
#define ELF_KEY_PAGEDOWN 164
#define ELF_KEY_HOME 165
#define ELF_KEY_END 166
#define ELF_KEY_KP_0 167
#define ELF_KEY_KP_1 168
#define ELF_KEY_KP_2 169
#define ELF_KEY_KP_3 170
#define ELF_KEY_KP_4 171
#define ELF_KEY_KP_5 172
#define ELF_KEY_KP_6 173
#define ELF_KEY_KP_7 174
#define ELF_KEY_KP_8 175
#define ELF_KEY_KP_9 176
#define ELF_KEY_KP_DIVIDE 177
#define ELF_KEY_KP_MULTIPLY 178
#define ELF_KEY_KP_SUBTRACT 179
#define ELF_KEY_KP_ADD 180
#define ELF_KEY_KP_DECIMAL 181
#define ELF_KEY_KP_EQUAL 182
#define ELF_KEY_KP_ENTER 183
#define ELF_KEY_SPACE 32
#define ELF_KEY_0 48
#define ELF_KEY_1 49
#define ELF_KEY_2 50
#define ELF_KEY_3 51
#define ELF_KEY_4 52
#define ELF_KEY_5 53
#define ELF_KEY_6 54
#define ELF_KEY_7 55
#define ELF_KEY_8 56
#define ELF_KEY_9 57
#define ELF_KEY_A 65
#define ELF_KEY_B 66
#define ELF_KEY_C 67
#define ELF_KEY_D 68
#define ELF_KEY_E 69
#define ELF_KEY_F 70
#define ELF_KEY_G 71
#define ELF_KEY_H 72
#define ELF_KEY_I 73
#define ELF_KEY_J 74
#define ELF_KEY_K 75
#define ELF_KEY_L 76
#define ELF_KEY_M 77
#define ELF_KEY_N 78
#define ELF_KEY_O 79
#define ELF_KEY_P 80
#define ELF_KEY_Q 81
#define ELF_KEY_R 82
#define ELF_KEY_S 83
#define ELF_KEY_T 84
#define ELF_KEY_U 85
#define ELF_KEY_V 86
#define ELF_KEY_W 87
#define ELF_KEY_X 88
#define ELF_KEY_Y 89
#define ELF_KEY_Z 90
#define ELF_UP 0x0000
#define ELF_PRESSED 0x0001
#define ELF_DOWN 0x0002
#define ELF_RELEASED 0x0003
#define ELF_OFF 0x0000
#define ELF_ON 0x0001
#define ELF_OVER 0x0002
#define ELF_BUTTON_LEFT 0x0000
#define ELF_BUTTON_MIDDLE 0x0001
#define ELF_BUTTON_RIGHT 0x0002
#define ELF_TEXTURE 0x0000
#define ELF_MATERIAL 0x0001
#define ELF_MODEL 0x0002
#define ELF_CAMERA 0x0003
#define ELF_ENTITY 0x0004
#define ELF_LIGHT 0x0005
#define ELF_SCENE 0x0006
#define ELF_LIST 0x0007
#define ELF_PAK 0x0008
#define ELF_PAK_INDEX 0x0009
#define ELF_KEY_EVENT 0x000A
#define ELF_CHAR_EVENT 0x000B
#define ELF_CONTEXT 0x000C
#define ELF_ENGINE 0x000D
#define ELF_TIMER 0x000E
#define ELF_IMAGE 0x000F
#define ELF_POST_PROCESS 0x0010
#define ELF_SCRIPT 0x0011
#define ELF_AUDIO_DEVICE 0x0012
#define ELF_AUDIO_SOURCE 0x0013
#define ELF_SOUND 0x0014
#define ELF_BONE 0x0015
#define ELF_ARMATURE 0x0016
#define ELF_STRING 0x0017
#define ELF_FONT 0x0018
#define ELF_LABEL 0x0019
#define ELF_BUTTON 0x001A
#define ELF_PICTURE 0x001B
#define ELF_TEXT_FIELD 0x001C
#define ELF_SLIDER 0x001D
#define ELF_SCREEN 0x001E
#define ELF_TEXT_LIST 0x001F
#define ELF_CHECK_BOX 0x0020
#define ELF_GUI 0x0021
#define ELF_DIRECTORY_ITEM 0x0022
#define ELF_DIRECTORY 0x0023
#define ELF_COLLISION 0x0034
#define ELF_PHYSICS_OBJECT 0x0035
#define ELF_PHYSICS_WORLD 0x0036
#define ELF_JOINT 0x0037
#define ELF_PARTICLE 0x0038
#define ELF_PARTICLES 0x0039
#define ELF_CONFIG 0x003A
#define ELF_BEZIER_POINT 0x003B
#define ELF_BEZIER_CURVE 0x003C
#define ELF_IPO 0x003D
#define ELF_FRAME_PLAYER 0x003E
#define ELF_PROPERTY 0x003F
#define ELF_CLIENT 0x0040
#define ELF_SCRIPTING 0x0041
#define ELF_PHYSICS_TRI_MESH 0x0042
#define ELF_SPRITE 0x0043
#define ELF_VIDEO_MODE 0x0044
#define ELF_GENERAL 0x0045
#define ELF_VERTICE 0x0046
#define ELF_FACE 0x0047
#define ELF_MESH_DATA 0x0048
#define ELF_LIST_PTR 0x0049
#define ELF_OBJECT_TYPE_COUNT 0x004A
#define ELF_PERSPECTIVE 0x0000
#define ELF_ORTHOGRAPHIC 0x0001
#define ELF_BOX 0x0001
#define ELF_SPHERE 0x0002
#define ELF_MESH 0x0003
#define ELF_CAPSULE_X 0x0004
#define ELF_CAPSULE_Y 0x0005
#define ELF_CAPSULE_Z 0x0006
#define ELF_CONE_X 0x0007
#define ELF_CONE_Y 0x0008
#define ELF_CONE_Z 0x0009
#define ELF_HINGE 0x0001
#define ELF_BALL 0x0002
#define ELF_CONE_TWIST 0x0003
#define ELF_POINT_LIGHT 0x0001
#define ELF_SUN_LIGHT 0x0002
#define ELF_SPOT_LIGHT 0x0003
#define ELF_LUMINANCE 0x0000
#define ELF_LUMINANCE_ALPHA 0x0001
#define ELF_RGB 0x0002
#define ELF_RGBA 0x0003
#define ELF_BGR 0x0004
#define ELF_BGRA 0x0005
#define ELF_RGB16F 0x0006
#define ELF_RGB32F 0x0007
#define ELF_RGBA16F 0x0008
#define ELF_RGBA32F 0x0009
#define ELF_ALPHA32F 0x000A
#define ELF_DEPTH_COMPONENT 0x000B
#define ELF_COMPRESSED_RGB 0x000C
#define ELF_COMPRESSED_RGBA 0x000D
#define ELF_FLOAT 0x0000
#define ELF_INT 0x0001
#define ELF_UINT 0x0002
#define ELF_SHORT 0x0003
#define ELF_USHORT 0x0004
#define ELF_BYTE 0x0005
#define ELF_UBYTE 0x0006
#define ELF_PROPERTY_INT 0x0001
#define ELF_PROPERTY_FLOAT 0x0002
#define ELF_PROPERTY_STRING 0x0003
#define ELF_PROPERTY_BOOL 0x0004
#define ELF_COLOR_MAP 0x0001
#define ELF_NORMAL_MAP 0x0002
#define ELF_HEIGHT_MAP 0x0004
#define ELF_SPECULAR_MAP 0x0008
#define ELF_DETAIL_MAP 0x0010
#define ELF_SHADOW_MAP 0x0020
#define ELF_COLOR_RAMP_MAP 0x0040
#define ELF_LIGHT_MAP 0x0080
#define ELF_CUBE_MAP 0x0100
#define ELF_TRANSPARENT 0x0001
#define ELF_ADD 0x0002
#define ELF_DIR 0x0001
#define ELF_FILE 0x0002
#define ELF_CLICKED 0x0001
#define ELF_VALUE_CHANGED 0x0002
#define ELF_GAIN_FOCUS 0x0003
#define ELF_LOSE_FOCUS 0x0004
#define ELF_CHAR_INPUT 0x0005
#define ELF_SELECTION_CHANGED 0x0006
#define ELF_STATE_CHANGED 0x0007
#define ELF_JOYSTICK_BUTTON_1 0x0000
#define ELF_JOYSTICK_BUTTON_2 0x0001
#define ELF_JOYSTICK_BUTTON_3 0x0002
#define ELF_JOYSTICK_BUTTON_4 0x0003
#define ELF_JOYSTICK_BUTTON_5 0x0004
#define ELF_JOYSTICK_BUTTON_6 0x0005
#define ELF_JOYSTICK_BUTTON_7 0x0006
#define ELF_JOYSTICK_BUTTON_8 0x0007
#define ELF_JOYSTICK_BUTTON_9 0x0008
#define ELF_JOYSTICK_BUTTON_10 0x0009
#define ELF_JOYSTICK_BUTTON_11 0x000A
#define ELF_JOYSTICK_BUTTON_12 0x000B
#define ELF_JOYSTICK_BUTTON_13 0x000C
#define ELF_JOYSTICK_BUTTON_14 0x000D
#define ELF_JOYSTICK_BUTTON_15 0x000E
#define ELF_JOYSTICK_BUTTON_16 0x000F
#define ELF_LOC_X 0x0000
#define ELF_LOC_Y 0x0001
#define ELF_LOC_Z 0x0002
#define ELF_ROT_X 0x0003
#define ELF_ROT_Y 0x0004
#define ELF_ROT_Z 0x0005
#define ELF_SCALE_X 0x0006
#define ELF_SCALE_Y 0x0007
#define ELF_SCALE_Z 0x0008
#define ELF_QUA_X 0x0009
#define ELF_QUA_Y 0x000A
#define ELF_QUA_Z 0x000B
#define ELF_QUA_W 0x000C
#define ELF_NET_NONE 0x0000
#define ELF_NET_CONNECT 0x0001
#define ELF_NET_RECEIVE 0x0002
#define ELF_NET_DISCONNECT 0x0003
#define ELF_OGG 0x0001
#define ELF_WAV 0x0002
#define ELF_NO_ERROR 0x0000
#define ELF_INVALID_FILE 0x0001
#define ELF_CANT_OPEN_FILE 0x0002
#define ELF_CANT_OPEN_DIRECTORY 0x0003
#define ELF_CANT_INITIALIZE 0x0004
#define ELF_CANT_RUN_STRING 0x0005
#define ELF_CANT_RUN_SCRIPT 0x0006
#define ELF_CANT_CREATE 0x0007
#define ELF_CANT_RESIZE 0x0008
#define ELF_INVALID_SIZE 0x0009
#define ELF_UNKNOWN_FORMAT 0x000A
#define ELF_UNKNOWN_TYPE 0x000B
#define ELF_INVALID_HANDLE 0x000C
#define ELF_MISSING_FEATURE 0x000D
#define ELF_INVALID_MESH 0x000E
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
typedef struct elf_vec2i				elf_vec2i;
typedef struct elf_vec2f				elf_vec2f;
typedef struct elf_vec3f				elf_vec3f;
typedef struct elf_vec4f				elf_vec4f;
typedef struct elf_color				elf_color;
typedef struct elf_general				elf_general;
typedef struct elf_config				elf_config;
typedef struct elf_object				elf_object;
typedef struct elf_resource				elf_resource;
typedef struct elf_gui_object				elf_gui_object;
typedef struct elf_list					elf_list;
typedef struct elf_key_event				elf_key_event;
typedef struct elf_char_event				elf_char_event;
typedef struct elf_context				elf_context;
typedef struct elf_engine				elf_engine;
typedef struct elf_timer				elf_timer;
typedef struct elf_image				elf_image;
typedef struct elf_texture				elf_texture;
typedef struct elf_material				elf_material;
typedef struct elf_bezier_point				elf_bezier_point;
typedef struct elf_bezier_curve				elf_bezier_curve;
typedef struct elf_ipo					elf_ipo;
typedef struct elf_actor				elf_actor;
typedef struct elf_camera				elf_camera;
typedef struct elf_model				elf_model;
typedef struct elf_entity				elf_entity;
typedef struct elf_light				elf_light;
typedef struct elf_scene				elf_scene;
typedef struct elf_pak_index				elf_pak_index;
typedef struct elf_pak					elf_pak;
typedef struct elf_post_process				elf_post_process;
typedef struct elf_script				elf_script;
typedef struct elf_audio_device				elf_audio_device;
typedef struct elf_audio_source				elf_audio_source;
typedef struct elf_sound				elf_sound;
typedef struct elf_bone					elf_bone;
typedef struct elf_armature				elf_armature;
typedef struct elf_string				elf_string;
typedef struct elf_font					elf_font;
typedef struct elf_area					elf_area;
typedef struct elf_label				elf_label;
typedef struct elf_button				elf_button;
typedef struct elf_picture				elf_picture;
typedef struct elf_text_field				elf_text_field;
typedef struct elf_slider				elf_slider;
typedef struct elf_screen				elf_screen;
typedef struct elf_text_list				elf_text_list;
typedef struct elf_check_box				elf_check_box;
typedef struct elf_gui					elf_gui;
typedef struct elf_directory_item			elf_directory_item;
typedef struct elf_directory				elf_directory;
typedef struct elf_collision				elf_collision;
typedef struct elf_physics_tri_mesh			elf_physics_tri_mesh;
typedef struct elf_physics_object			elf_physics_object;
typedef struct elf_physics_world			elf_physics_world;
typedef struct elf_joint				elf_joint;
typedef struct elf_resources				elf_resources;
typedef struct elf_particle				elf_particle;
typedef struct elf_particles				elf_particles;
typedef struct elf_frame_player				elf_frame_player;
typedef struct elf_property				elf_property;
typedef struct elf_server				elf_server;
typedef struct elf_client				elf_client;
typedef struct elf_scripting				elf_scripting;
typedef struct elf_sprite				elf_sprite;
typedef struct elf_video_mode				elf_video_mode;
typedef struct elf_vertice				elf_vertice;
typedef struct elf_face					elf_face;
typedef struct elf_mesh_data				elf_mesh_data;
struct elf_vec2i {
	int x;
	int y;
};
struct elf_vec2f {
	float x;
	float y;
};
struct elf_vec3f {
	float x;
	float y;
	float z;
};
struct elf_vec4f {
	float x;
	float y;
	float z;
	float w;
};
struct elf_color {
	float r;
	float g;
	float b;
	float a;
};
ELF_API int ELF_APIENTRY elfGetObjectType(elf_object* obj);
ELF_API int ELF_APIENTRY elfGetObjectRefCount(elf_object* obj);
ELF_API int ELF_APIENTRY elfGetGlobalRefCount();
ELF_API int ELF_APIENTRY elfGetGlobalObjCount();
ELF_API unsigned char ELF_APIENTRY elfIsActor(elf_object* obj);
ELF_API unsigned char ELF_APIENTRY elfIsGuiObject(elf_object* obj);
ELF_API elf_list* ELF_APIENTRY elfCreateList();
ELF_API int ELF_APIENTRY elfGetListLength(elf_list* list);
ELF_API void ELF_APIENTRY elfInsertToList(elf_list* list, int idx, elf_object* obj);
ELF_API void ELF_APIENTRY elfAppendToList(elf_list* list, elf_object* obj);
ELF_API unsigned char ELF_APIENTRY elfRemoveFromList(elf_list* list, elf_object* obj);
ELF_API elf_object* ELF_APIENTRY elfGetItemFromList(elf_list* list, int idx);
ELF_API elf_object* ELF_APIENTRY elfBeginList(elf_list* list);
ELF_API elf_object* ELF_APIENTRY elfNextInList(elf_list* list);
ELF_API elf_object* ELF_APIENTRY elfRbeginList(elf_list* list);
ELF_API elf_object* ELF_APIENTRY elfRnextInList(elf_list* list);
ELF_API void ELF_APIENTRY elfSeekList(elf_list* list, elf_object* ptr);
ELF_API void ELF_APIENTRY elfRseekList(elf_list* list, elf_object* ptr);
ELF_API elf_config* ELF_APIENTRY elfReadConfig(const char* file_path);
ELF_API int ELF_APIENTRY elfGetConfigWindowWidth(elf_config* config);
ELF_API int ELF_APIENTRY elfGetConfigWindowHeight(elf_config* config);
ELF_API int ELF_APIENTRY elfGetConfigMultisamples(elf_config* config);
ELF_API unsigned char ELF_APIENTRY elfGetConfigFullscreen(elf_config* config);
ELF_API unsigned char ELF_APIENTRY elfGetConfigTextureCompress(elf_config* config);
ELF_API float ELF_APIENTRY elfGetConfigTextureAnisotropy(elf_config* config);
ELF_API int ELF_APIENTRY elfGetConfigShadowMapSize(elf_config* config);
ELF_API const char* ELF_APIENTRY elfGetConfigStart(elf_config* config);
ELF_API const char* ELF_APIENTRY elfGetConfigLog(elf_config* config);
ELF_API void ELF_APIENTRY elfSetTitle(const char* title);
ELF_API int ELF_APIENTRY elfGetWindowWidth();
ELF_API int ELF_APIENTRY elfGetWindowHeight();
ELF_API int ELF_APIENTRY elfGetVideoModeCount();
ELF_API elf_vec2i ELF_APIENTRY elfGetVideoMode(int idx);
ELF_API int ELF_APIENTRY elfGetMultisamples();
ELF_API unsigned char ELF_APIENTRY elfIsFullscreen();
ELF_API const char* ELF_APIENTRY elfGetTitle();
ELF_API double ELF_APIENTRY elfGetTime();
ELF_API void ELF_APIENTRY elfSleep(float time);
ELF_API unsigned char ELF_APIENTRY elfIsWindowOpened();
ELF_API elf_vec2i ELF_APIENTRY elfGetMousePosition();
ELF_API elf_vec2i ELF_APIENTRY elfGetMouseForce();
ELF_API void ELF_APIENTRY elfSetMousePosition(int x, int y);
ELF_API void ELF_APIENTRY elfHideMouse(unsigned char hide);
ELF_API unsigned char ELF_APIENTRY elfIsMouseHidden();
ELF_API int ELF_APIENTRY elfGetMouseWheel();
ELF_API int ELF_APIENTRY elfGetMouseButtonState(int button);
ELF_API int ELF_APIENTRY elfGetKeyState(int key);
ELF_API unsigned char ELF_APIENTRY elfGetJoystickPresent(int joy);
ELF_API elf_vec2f ELF_APIENTRY elfGetJoystickAxis(int joy);
ELF_API int ELF_APIENTRY elfGetJoystickButtonState(int joy, int but);
ELF_API int ELF_APIENTRY elfGetEventCount();
ELF_API elf_object* ELF_APIENTRY elfGetEvent(int idx);
ELF_API unsigned char ELF_APIENTRY elfInit(int width, int height, const char* title, int multisamples, unsigned char fullscreen, const char* log);
ELF_API unsigned char ELF_APIENTRY elfInitWithConfig(const char* file_path);
ELF_API void ELF_APIENTRY elfDeinit();
ELF_API void ELF_APIENTRY elfResizeWindow(int width, int height);
ELF_API const char* ELF_APIENTRY elfGetPlatform();
ELF_API int ELF_APIENTRY elfGetVersionMajor();
ELF_API int ELF_APIENTRY elfGetVersionMinor();
ELF_API const char* ELF_APIENTRY elfGetVersionRelease();
ELF_API const char* ELF_APIENTRY elfGetVersion();
ELF_API const char* ELF_APIENTRY elfGetCurrentDirectory();
ELF_API const char* ELF_APIENTRY elfGetErrorString();
ELF_API int ELF_APIENTRY elfGetError();
ELF_API unsigned char ELF_APIENTRY elfRun();
ELF_API void ELF_APIENTRY elfQuit();
ELF_API void ELF_APIENTRY elfSetF10Exit(unsigned char exit);
ELF_API unsigned char ELF_APIENTRY elfGetF10Exit();
ELF_API elf_scene* ELF_APIENTRY elfLoadScene(const char* file_path);
ELF_API void ELF_APIENTRY elfSetScene(elf_scene* scene);
ELF_API elf_scene* ELF_APIENTRY elfGetScene();
ELF_API void ELF_APIENTRY elfSetGui(elf_gui* gui);
ELF_API elf_gui* ELF_APIENTRY elfGetGui();
ELF_API float ELF_APIENTRY elfGetSync();
ELF_API int ELF_APIENTRY elfGetFps();
ELF_API unsigned char ELF_APIENTRY elfSaveScreenShot(const char* file_path);
ELF_API void ELF_APIENTRY elfSetFpsLimit(int fps_limit);
ELF_API int ELF_APIENTRY elfGetFpsLimit();
ELF_API void ELF_APIENTRY elfSetTickRate(float tick_rate);
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
ELF_API void ELF_APIENTRY elfSetFog(float start, float end, float r, float g, float b);
ELF_API void ELF_APIENTRY elfDisableFog();
ELF_API float ELF_APIENTRY elfGetFogStart();
ELF_API float ELF_APIENTRY elfGetFogEnd();
ELF_API elf_color ELF_APIENTRY elfGetFogColor();
ELF_API void ELF_APIENTRY elfSetBloom(float threshold);
ELF_API void ELF_APIENTRY elfDisableBloom();
ELF_API float ELF_APIENTRY elfGetBloomThreshold();
ELF_API void ELF_APIENTRY elfSetDof(float focal_range, float focal_distance);
ELF_API void ELF_APIENTRY elfDisableDof();
ELF_API float ELF_APIENTRY elfGetDofFocalRange();
ELF_API float ELF_APIENTRY elfGetDofFocalDistance();
ELF_API void ELF_APIENTRY elfSetSsao(float amount);
ELF_API void ELF_APIENTRY elfDisableSsao();
ELF_API float ELF_APIENTRY elfGetSsaoAmount();
ELF_API void ELF_APIENTRY elfSetLightShafts(float intensity);
ELF_API void ELF_APIENTRY elfDisableLightShafts();
ELF_API float ELF_APIENTRY elfGetLightShaftsIntensity();
ELF_API unsigned char ELF_APIENTRY elfIsFog();
ELF_API unsigned char ELF_APIENTRY elfIsBloom();
ELF_API unsigned char ELF_APIENTRY elfIsSsao();
ELF_API unsigned char ELF_APIENTRY elfIsDof();
ELF_API unsigned char ELF_APIENTRY elfIsLightShafts();
ELF_API void ELF_APIENTRY elfSetOcclusionCulling(unsigned char cull);
ELF_API unsigned char ELF_APIENTRY elfIsOcclusionCulling();
ELF_API void ELF_APIENTRY elfSetDebugDraw(unsigned char debug_draw);
ELF_API unsigned char ELF_APIENTRY elfIsDebugDraw();
ELF_API elf_object* ELF_APIENTRY elfGetActor();
ELF_API elf_directory* ELF_APIENTRY elfReadDirectory(const char* path);
ELF_API const char* ELF_APIENTRY elfGetDirectoryPath(elf_directory* directory);
ELF_API int ELF_APIENTRY elfGetDirectoryItemCount(elf_directory* directory);
ELF_API elf_directory_item* ELF_APIENTRY elfGetDirectoryItem(elf_directory* directory, int idx);
ELF_API const char* ELF_APIENTRY elfGetDirectoryItemName(elf_directory_item* dir_item);
ELF_API int ELF_APIENTRY elfGetDirectoryItemType(elf_directory_item* dir_item);
ELF_API elf_vec3f ELF_APIENTRY elfCreateVec3f();
ELF_API elf_vec3f ELF_APIENTRY elfCreateVec3fFromValues(float x, float y, float z);
ELF_API elf_vec4f ELF_APIENTRY elfCreateQua();
ELF_API elf_vec4f ELF_APIENTRY elfCreateQuaFromEuler(float x, float y, float z);
ELF_API elf_vec4f ELF_APIENTRY elfCreateQuaFromAngleAxis(float angle, float x, float y, float z);
ELF_API elf_vec3f ELF_APIENTRY elfMulQuaVec3f(elf_vec4f qua, elf_vec3f vec);
ELF_API elf_vec4f ELF_APIENTRY elfMulQuaQua(elf_vec4f qua1, elf_vec4f qua2);
ELF_API elf_vec4f ELF_APIENTRY elfGetQuaInverted(elf_vec4f qua);
ELF_API elf_vec3f ELF_APIENTRY elfRotateVec3f(elf_vec3f vec, float x, float y, float z);
ELF_API elf_vec3f ELF_APIENTRY elfSubVec3fVec3f(elf_vec3f vec1, elf_vec3f vec2);
ELF_API elf_vec3f ELF_APIENTRY elfAddVec3fVec3f(elf_vec3f vec1, elf_vec3f vec2);
ELF_API float ELF_APIENTRY elfGetVec3fLength(elf_vec3f vec);
ELF_API unsigned char ELF_APIENTRY elfAboutZero(float val);
ELF_API float ELF_APIENTRY elfFloatAbs(float val);
ELF_API float ELF_APIENTRY elfFloatMin(float a, float b);
ELF_API float ELF_APIENTRY elfFloatMax(float a, float b);
ELF_API float ELF_APIENTRY elfRandomFloat();
ELF_API float ELF_APIENTRY elfRandomFloatRange(float min, float max);
ELF_API int ELF_APIENTRY elfRandomInt();
ELF_API int ELF_APIENTRY elfRandomIntRange(int min, int max);
ELF_API elf_frame_player* ELF_APIENTRY elfCreateFramePlayer();
ELF_API void ELF_APIENTRY elfUpdateFramePlayer(elf_frame_player* player);
ELF_API void ELF_APIENTRY elfSetFramePlayerFrame(elf_frame_player* player, float frame);
ELF_API void ELF_APIENTRY elfPlayFramePlayer(elf_frame_player* player, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfLoopFramePlayer(elf_frame_player* player, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfStopFramePlayer(elf_frame_player* player);
ELF_API void ELF_APIENTRY elfPauseFramePlayer(elf_frame_player* player);
ELF_API void ELF_APIENTRY elfResumeFramePlayer(elf_frame_player* player);
ELF_API float ELF_APIENTRY elfGetFramePlayerStart(elf_frame_player* player);
ELF_API float ELF_APIENTRY elfGetFramePlayerEnd(elf_frame_player* player);
ELF_API float ELF_APIENTRY elfGetFramePlayerSpeed(elf_frame_player* player);
ELF_API float ELF_APIENTRY elfGetFramePlayerFrame(elf_frame_player* player);
ELF_API unsigned char ELF_APIENTRY elfIsFramePlayerPlaying(elf_frame_player* player);
ELF_API unsigned char ELF_APIENTRY elfIsFramePlayerPaused(elf_frame_player* player);
ELF_API elf_timer* ELF_APIENTRY elfCreateTimer();
ELF_API void ELF_APIENTRY elfStartTimer(elf_timer* timer);
ELF_API double ELF_APIENTRY elfGetElapsedTime(elf_timer* timer);
ELF_API elf_image* ELF_APIENTRY elfCreateEmptyImage(int width, int height, int bpp);
ELF_API elf_image* ELF_APIENTRY elfCreateImageFromFile(const char* file_path);
ELF_API void ELF_APIENTRY elfSetImagePixel(elf_image* image, int x, int y, float r, float g, float b, float a);
ELF_API int ELF_APIENTRY elfGetImageWidth(elf_image* image);
ELF_API int ELF_APIENTRY elfGetImageHeight(elf_image* image);
ELF_API int ELF_APIENTRY elfGetImageBitsPerPixel(elf_image* image);
ELF_API elf_color ELF_APIENTRY elfGetImagePixel(elf_image* image, int x, int y);
ELF_API elf_texture* ELF_APIENTRY elfCreateTextureFromFile(const char* file_path);
ELF_API elf_texture* ELF_APIENTRY elfCreateTextureFromImage(elf_image* image);
ELF_API elf_texture* ELF_APIENTRY elfCreateCubeMapFromFiles(const char* xpos, const char* xneg, const char* ypos, const char* yneg, const char* zpos, const char* zneg);
ELF_API void ELF_APIENTRY elfSetTextureName(elf_texture* texture, const char* name);
ELF_API const char* ELF_APIENTRY elfGetTextureName(elf_texture* texture);
ELF_API const char* ELF_APIENTRY elfGetTextureFilePath(elf_texture* texture);
ELF_API int ELF_APIENTRY elfGetTextureWidth(elf_texture* texture);
ELF_API int ELF_APIENTRY elfGetTextureHeight(elf_texture* texture);
ELF_API int ELF_APIENTRY elfGetTextureFormat(elf_texture* texture);
ELF_API int ELF_APIENTRY elfGetTextureDataFormat(elf_texture* texture);
ELF_API elf_material* ELF_APIENTRY elfCreateMaterial(const char* name);
ELF_API void ELF_APIENTRY elfSetMaterialDiffuseColor(elf_material* material, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetMaterialSpecularColor(elf_material* material, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetMaterialAmbientColor(elf_material* material, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetMaterialSpecularPower(elf_material* material, float power);
ELF_API void ELF_APIENTRY elfSetMaterialLighting(elf_material* material, unsigned char lighting);
ELF_API void ELF_APIENTRY elfSetMaterialName(elf_material* material, const char* name);
ELF_API const char* ELF_APIENTRY elfGetMaterialName(elf_material* material);
ELF_API const char* ELF_APIENTRY elfGetMaterialFilePath(elf_material* material);
ELF_API elf_color ELF_APIENTRY elfGetMaterialDiffuseColor(elf_material* material);
ELF_API elf_color ELF_APIENTRY elfGetMaterialSpecularColor(elf_material* material);
ELF_API elf_color ELF_APIENTRY elfGetMaterialAmbientColor(elf_material* material);
ELF_API float ELF_APIENTRY elfGetMaterialSpecularPower(elf_material* material);
ELF_API unsigned char ELF_APIENTRY elfGetMaterialLighting(elf_material* material);
ELF_API void ELF_APIENTRY elfSetMaterialDiffuseMap(elf_material* material, elf_texture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialNormalMap(elf_material* material, elf_texture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialHeightMap(elf_material* material, elf_texture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialSpecularMap(elf_material* material, elf_texture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialLightMap(elf_material* material, elf_texture* texture);
ELF_API void ELF_APIENTRY elfSetMaterialCubeMap(elf_material* material, elf_texture* texture);
ELF_API void ELF_APIENTRY elfClearMaterialDiffuseMap(elf_material* material);
ELF_API void ELF_APIENTRY elfClearMaterialNormalMap(elf_material* material);
ELF_API void ELF_APIENTRY elfClearMaterialHeightMap(elf_material* material);
ELF_API void ELF_APIENTRY elfClearMaterialSpecularMap(elf_material* material);
ELF_API void ELF_APIENTRY elfClearMaterialLightMap(elf_material* material);
ELF_API void ELF_APIENTRY elfClearMaterialCubeMap(elf_material* material);
ELF_API elf_texture* ELF_APIENTRY elfGetMaterialDiffuseMap(elf_material* material);
ELF_API elf_texture* ELF_APIENTRY elfGetMaterialNormalMap(elf_material* material);
ELF_API elf_texture* ELF_APIENTRY elfGetMaterialHeightMap(elf_material* material);
ELF_API elf_texture* ELF_APIENTRY elfGetMaterialSpecularMap(elf_material* material);
ELF_API elf_texture* ELF_APIENTRY elfGetMaterialLightMap(elf_material* material);
ELF_API elf_texture* ELF_APIENTRY elfGetMaterialCubeMap(elf_material* material);
ELF_API void ELF_APIENTRY elfSetMaterialParallaxScale(elf_material* material, float scale);
ELF_API void ELF_APIENTRY elfSetMaterialAlphaTest(elf_material* material, unsigned char alpha_test);
ELF_API void ELF_APIENTRY elfSetMaterialAlphaThreshold(elf_material* material, float threshold);
ELF_API float ELF_APIENTRY elfGetMaterialParallaxScale(elf_material* material);
ELF_API unsigned char ELF_APIENTRY elfGetMaterialAlphaTest(elf_material* material);
ELF_API float ELF_APIENTRY elfGetMaterialAlphaThreshold(elf_material* material);
ELF_API elf_bezier_point* ELF_APIENTRY elfCreateBezierPoint();
ELF_API void ELF_APIENTRY elfSetBezierPointPosition(elf_bezier_point* point, float x, float y);
ELF_API void ELF_APIENTRY elfSetBezierPointControl1(elf_bezier_point* point, float x, float y);
ELF_API void ELF_APIENTRY elfSetBezierPointControl2(elf_bezier_point* point, float x, float y);
ELF_API elf_vec2f ELF_APIENTRY elfGetBezierPointPosition(elf_bezier_point* point);
ELF_API elf_vec2f ELF_APIENTRY elfGetBezierPointControl1(elf_bezier_point* point);
ELF_API elf_vec2f ELF_APIENTRY elfGetBezierPointControl2(elf_bezier_point* point);
ELF_API elf_bezier_curve* ELF_APIENTRY elfCreateBezierCurve();
ELF_API void ELF_APIENTRY elfSetBezierCurveType(elf_bezier_curve* curve, int type);
ELF_API int ELF_APIENTRY elfGetBezierCurveType(elf_bezier_curve* curve);
ELF_API void ELF_APIENTRY elfAddPointToBezierCurve(elf_bezier_curve* curve, elf_bezier_point* point);
ELF_API elf_bezier_point* ELF_APIENTRY elfGetPointFromBezierCurve(elf_bezier_curve* curve, int idx);
ELF_API float ELF_APIENTRY elfGetBezierCurveValue(elf_bezier_curve* curve, float x);
ELF_API elf_ipo* ELF_APIENTRY elfCreateIpo();
ELF_API unsigned char ELF_APIENTRY elfAddCurveToIpo(elf_ipo* ipo, elf_bezier_curve* curve);
ELF_API int ELF_APIENTRY elfGetIpoCurveCount(elf_ipo* ipo);
ELF_API elf_bezier_curve* ELF_APIENTRY elfGetCurveFromIpo(elf_ipo* ipo, int idx);
ELF_API elf_vec3f ELF_APIENTRY elfGetIpoLoc(elf_ipo* ipo, float x);
ELF_API elf_vec3f ELF_APIENTRY elfGetIpoRot(elf_ipo* ipo, float x);
ELF_API elf_vec3f ELF_APIENTRY elfGetIpoScale(elf_ipo* ipo, float x);
ELF_API elf_vec4f ELF_APIENTRY elfGetIpoQua(elf_ipo* ipo, float x);
ELF_API elf_property* ELF_APIENTRY elfCreateProperty(const char* name);
ELF_API int ELF_APIENTRY elfGetPropertyType(elf_property* property);
ELF_API int ELF_APIENTRY elfGetPropertyInt(elf_property* property);
ELF_API float ELF_APIENTRY elfGetPropertyFloat(elf_property* property);
ELF_API const char* ELF_APIENTRY elfGetPropertyString(elf_property* property);
ELF_API unsigned char ELF_APIENTRY elfGetPropertyBool(elf_property* property);
ELF_API void ELF_APIENTRY elfSetPropertyInt(elf_property* property, int ival);
ELF_API void ELF_APIENTRY elfSetPropertyFloat(elf_property* property, float fval);
ELF_API void ELF_APIENTRY elfSetPropertyString(elf_property* property, const char* sval);
ELF_API void ELF_APIENTRY elfSetPropertyBool(elf_property* property, unsigned char bval);
ELF_API const char* ELF_APIENTRY elfGetActorName(elf_actor* actor);
ELF_API const char* ELF_APIENTRY elfGetActorFilePath(elf_actor* actor);
ELF_API elf_script* ELF_APIENTRY elfGetActorScript(elf_actor* actor);
ELF_API void ELF_APIENTRY elfSetActorName(elf_actor* actor, const char* name);
ELF_API void ELF_APIENTRY elfSetActorScript(elf_actor* actor, elf_script* script);
ELF_API void ELF_APIENTRY elfClearActorScript(elf_actor* actor);
ELF_API void ELF_APIENTRY elfSetActorPosition(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorRotation(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorOrientation(elf_actor* actor, float x, float y, float z, float w);
ELF_API void ELF_APIENTRY elfRotateActor(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfRotateActorLocal(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfMoveActor(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfMoveActorLocal(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorPositionRelativeTo(elf_actor* actor, elf_actor* to, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorRotationRelativeTo(elf_actor* actor, elf_actor* to, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorOrientationRelativeTo(elf_actor* actor, elf_actor* to, float x, float y, float z, float w);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorPosition(elf_actor* actor);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorRotation(elf_actor* actor);
ELF_API elf_vec4f ELF_APIENTRY elfGetActorOrientation(elf_actor* actor);
ELF_API void ELF_APIENTRY elfSetActorBoundingLengths(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorBoundingOffset(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorPhysics(elf_actor* actor, int shape, float mass);
ELF_API unsigned char ELF_APIENTRY elfIsActorPhysics(elf_actor* actor);
ELF_API void ELF_APIENTRY elfDisableActorPhysics(elf_actor* actor);
ELF_API void ELF_APIENTRY elfSetActorDamping(elf_actor* actor, float lin_damp, float ang_damp);
ELF_API void ELF_APIENTRY elfSetActorSleepThresholds(elf_actor* actor, float lin_thrs, float ang_thrs);
ELF_API void ELF_APIENTRY elfSetActorRestitution(elf_actor* actor, float restitution);
ELF_API void ELF_APIENTRY elfSetActorAnisotropicFriction(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorLinearFactor(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorAngularFactor(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfAddForceToActor(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfAddForceToActorLocal(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfAddTorqueToActor(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorLinearVelocity(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorLinearVelocityLocal(elf_actor* actor, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetActorAngularVelocity(elf_actor* actor, float x, float y, float z);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorBoundingLengths(elf_actor* actor);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorBoundingOffset(elf_actor* actor);
ELF_API int ELF_APIENTRY elfGetActorShape(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorMass(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorLinearDamping(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorAngularDamping(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorLinearSleepThreshold(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorAngularSleepThreshold(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorRestitution(elf_actor* actor);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorAnisotropicFriction(elf_actor* actor);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorLinearFactor(elf_actor* actor);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorAngularFactor(elf_actor* actor);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorLinearVelocity(elf_actor* actor);
ELF_API elf_vec3f ELF_APIENTRY elfGetActorAngularVelocity(elf_actor* actor);
ELF_API elf_joint* ELF_APIENTRY elfAddHingeJointToActor(elf_actor* actor, elf_actor* actor2, const char* name, float px, float py, float pz, float ax, float ay, float az);
ELF_API elf_joint* ELF_APIENTRY elfAddBallJointToActor(elf_actor* actor, elf_actor* actor2, const char* name, float px, float py, float pz);
ELF_API elf_joint* ELF_APIENTRY elfAddConeTwistJointToActor(elf_actor* actor, elf_actor* actor2, const char* name, float px, float py, float pz, float ax, float ay, float az);
ELF_API elf_joint* ELF_APIENTRY elfGetActorJointByName(elf_actor* actor, const char* name);
ELF_API elf_joint* ELF_APIENTRY elfGetActorJointByIndex(elf_actor* actor, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorJointByName(elf_actor* actor, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorJointByIndex(elf_actor* actor, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorJointByObject(elf_actor* actor, elf_joint* joint);
ELF_API void ELF_APIENTRY elfSetActorIpo(elf_actor* actor, elf_ipo* ipo);
ELF_API elf_ipo* ELF_APIENTRY elfGetActorIpo(elf_actor* actor);
ELF_API void ELF_APIENTRY elfSetActorIpoFrame(elf_actor* actor, float frame);
ELF_API void ELF_APIENTRY elfPlayActorIpo(elf_actor* actor, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfLoopActorIpo(elf_actor* actor, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfStopActorIpo(elf_actor* actor);
ELF_API void ELF_APIENTRY elfPauseActorIpo(elf_actor* actor);
ELF_API void ELF_APIENTRY elfResumeActorIpo(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorIpoStart(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorIpoEnd(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorIpoSpeed(elf_actor* actor);
ELF_API float ELF_APIENTRY elfGetActorIpoFrame(elf_actor* actor);
ELF_API unsigned char ELF_APIENTRY elfIsActorIpoPlaying(elf_actor* actor);
ELF_API unsigned char ELF_APIENTRY elfIsActorIpoPaused(elf_actor* actor);
ELF_API int ELF_APIENTRY elfGetActorCollisionCount(elf_actor* actor);
ELF_API elf_collision* ELF_APIENTRY elfGetActorCollision(elf_actor* actor, int idx);
ELF_API int ELF_APIENTRY elfGetActorPropertyCount(elf_actor* actor);
ELF_API void ELF_APIENTRY elfAddPropertyToActor(elf_actor* actor, elf_property* property);
ELF_API elf_property* ELF_APIENTRY elfGetActorPropertyByName(elf_actor* actor, const char* name);
ELF_API elf_property* ELF_APIENTRY elfGetActorPropertyByIndex(elf_actor* actor, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorPropertyByName(elf_actor* actor, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorPropertyByIndex(elf_actor* actor, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorPropertyByObject(elf_actor* actor, elf_property* property);
ELF_API void ELF_APIENTRY elfRemoveActorProperties(elf_actor* actor);
ELF_API void ELF_APIENTRY elfSetActorSelected(elf_actor* actor, unsigned char selected);
ELF_API unsigned char ELF_APIENTRY elfGetActorSelected(elf_actor* actor);
ELF_API elf_camera* ELF_APIENTRY elfCreateCamera(const char* name);
ELF_API void ELF_APIENTRY elfSetCameraViewport(elf_camera* camera, int x, int y, int width, int height);
ELF_API void ELF_APIENTRY elfSetCameraPerspective(elf_camera* camera, float fov, float aspect, float clip_near, float clip_far);
ELF_API void ELF_APIENTRY elfSetCameraOrthographic(elf_camera* camera, int x, int y, int width, int height, float clip_near, float clip_far);
ELF_API elf_vec2i ELF_APIENTRY elfGetCameraViewportSize(elf_camera* camera);
ELF_API elf_vec2i ELF_APIENTRY elfGetCameraViewportOffset(elf_camera* camera);
ELF_API float ELF_APIENTRY elfGetCameraFov(elf_camera* camera);
ELF_API float ELF_APIENTRY elfGetCameraAspect(elf_camera* camera);
ELF_API elf_vec2f ELF_APIENTRY elfGetCameraClip(elf_camera* camera);
ELF_API elf_vec2f ELF_APIENTRY elfGetCameraFarPlaneSize(elf_camera* camera);
ELF_API elf_vec3f ELF_APIENTRY elfProjectCameraPoint(elf_camera* camera, float x, float y, float z);
ELF_API elf_vec3f ELF_APIENTRY elfUnProjectCameraPoint(elf_camera* camera, float x, float y, float z);
ELF_API elf_vertice* ELF_APIENTRY elfCreateVertice();
ELF_API void ELF_APIENTRY elfSetVerticePosition(elf_vertice* vertice, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetVerticeNormal(elf_vertice* vertice, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetVerticeTexCoord(elf_vertice* vertice, float u, float v);
ELF_API elf_vec3f ELF_APIENTRY elfGetVerticePosition(elf_vertice* vertice);
ELF_API elf_vec3f ELF_APIENTRY elfGetVerticeNormal(elf_vertice* vertice);
ELF_API elf_vec2f ELF_APIENTRY elfGetVerticeTexCoord(elf_vertice* vertice);
ELF_API int ELF_APIENTRY elfGetFaceV1(elf_face* face);
ELF_API int ELF_APIENTRY elfGetFaceV2(elf_face* face);
ELF_API int ELF_APIENTRY elfGetFaceV3(elf_face* face);
ELF_API elf_mesh_data* ELF_APIENTRY elfCreateMeshData();
ELF_API int ELF_APIENTRY elfGetMeshDataVerticeCount(elf_mesh_data* mesh_data);
ELF_API int ELF_APIENTRY elfGetMeshDataFaceCount(elf_mesh_data* mesh_data);
ELF_API void ELF_APIENTRY elfAddVerticeToMeshData(elf_mesh_data* mesh_data, elf_vertice* vertice);
ELF_API void ELF_APIENTRY elfAddFaceToMeshData(elf_mesh_data* mesh_data, int v1, int v2, int v3);
ELF_API elf_vertice* ELF_APIENTRY elfGetVerticeFromMeshData(elf_mesh_data* mesh_data, int idx);
ELF_API elf_face* ELF_APIENTRY elfGetFaceFromMeshData(elf_mesh_data* mesh_data, int idx);
ELF_API elf_model* ELF_APIENTRY elfCreateModelFromMeshData(elf_mesh_data* data);
ELF_API void ELF_APIENTRY elfSetModelName(elf_model* model, const char* name);
ELF_API const char* ELF_APIENTRY elfGetModelName(elf_model* model);
ELF_API const char* ELF_APIENTRY elfGetModelFilePath(elf_model* model);
ELF_API int ELF_APIENTRY elfGetModelVerticeCount(elf_model* model);
ELF_API int ELF_APIENTRY elfGetModelIndiceCount(elf_model* model);
ELF_API elf_vec3f ELF_APIENTRY elfGetModelBoundingBoxMin(elf_model* model);
ELF_API elf_vec3f ELF_APIENTRY elfGetModelBoundingBoxMax(elf_model* model);
ELF_API elf_entity* ELF_APIENTRY elfCreateEntity(const char* name);
ELF_API void ELF_APIENTRY elfGenerateEntityTangents(elf_entity* entity);
ELF_API void ELF_APIENTRY elfSetEntityScale(elf_entity* entity, float x, float y, float z);
ELF_API elf_vec3f ELF_APIENTRY elfGetEntityScale(elf_entity* entity);
ELF_API void ELF_APIENTRY elfSetEntityModel(elf_entity* entity, elf_model* model);
ELF_API void ELF_APIENTRY elfClearEntityModel(elf_entity* entity);
ELF_API elf_model* ELF_APIENTRY elfGetEntityModel(elf_entity* entity);
ELF_API int ELF_APIENTRY elfGetEntityMaterialCount(elf_entity* entity);
ELF_API void ELF_APIENTRY elfAddEntityMaterial(elf_entity* entity, elf_material* material);
ELF_API void ELF_APIENTRY elfSetEntityMaterial(elf_entity* entity, int idx, elf_material* material);
ELF_API void ELF_APIENTRY elfRemoveEntityMaterial(elf_entity* entity, int idx);
ELF_API elf_material* ELF_APIENTRY elfGetEntityMaterial(elf_entity* entity, int idx);
ELF_API void ELF_APIENTRY elfSetEntityVisible(elf_entity* entity, unsigned char visible);
ELF_API unsigned char ELF_APIENTRY elfGetEntityVisible(elf_entity* entity);
ELF_API void ELF_APIENTRY elfSetEntityOccluder(elf_entity* entity, unsigned char occluder);
ELF_API unsigned char ELF_APIENTRY elfGetEntityOccluder(elf_entity* entity);
ELF_API void ELF_APIENTRY elfSetEntityPhysics(elf_entity* entity, int type, float mass);
ELF_API void ELF_APIENTRY elfDisableEntityPhysics(elf_entity* entity);
ELF_API void ELF_APIENTRY elfSetEntityArmature(elf_entity* entity, elf_armature* armature);
ELF_API void ELF_APIENTRY elfSetEntityArmatureFrame(elf_entity* entity, float frame);
ELF_API void ELF_APIENTRY elfPlayEntityArmature(elf_entity* entity, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfLoopEntityArmature(elf_entity* entity, float start, float end, float speed);
ELF_API void ELF_APIENTRY elfStopEntityArmature(elf_entity* entity);
ELF_API void ELF_APIENTRY elfPauseEntityArmature(elf_entity* entity);
ELF_API void ELF_APIENTRY elfResumeEntityArmature(elf_entity* entity);
ELF_API float ELF_APIENTRY elfGetEntityArmatureStart(elf_entity* entity);
ELF_API float ELF_APIENTRY elfGetEntityArmatureEnd(elf_entity* entity);
ELF_API float ELF_APIENTRY elfGetEntityArmatureSpeed(elf_entity* entity);
ELF_API float ELF_APIENTRY elfGetEntityArmatureFrame(elf_entity* entity);
ELF_API unsigned char ELF_APIENTRY elfIsEntityArmaturePlaying(elf_entity* entity);
ELF_API unsigned char ELF_APIENTRY elfIsEntityArmaturePaused(elf_entity* entity);
ELF_API elf_armature* ELF_APIENTRY elfGetEntityArmature(elf_entity* entity);
ELF_API unsigned char ELF_APIENTRY elfGetEntityChanged(elf_entity* entity);
ELF_API elf_light* ELF_APIENTRY elfCreateLight(const char* name);
ELF_API int ELF_APIENTRY elfGetLightType(elf_light* light);
ELF_API elf_color ELF_APIENTRY elfGetLightColor(elf_light* light);
ELF_API float ELF_APIENTRY elfGetLightDistance(elf_light* light);
ELF_API float ELF_APIENTRY elfGetLightFadeSpeed(elf_light* light);
ELF_API unsigned char ELF_APIENTRY elfGetLightShadows(elf_light* light);
ELF_API unsigned char ELF_APIENTRY elfGetLightVisible(elf_light* light);
ELF_API elf_vec2f ELF_APIENTRY elfGetLightCone(elf_light* light);
ELF_API unsigned char ELF_APIENTRY elfIsLightShaft(elf_light* light);
ELF_API float ELF_APIENTRY elfGetLightShaftSize(elf_light* light);
ELF_API float ELF_APIENTRY elfGetLightShaftIntensity(elf_light* light);
ELF_API float ELF_APIENTRY elfGetLightShaftFadeOff(elf_light* light);
ELF_API void ELF_APIENTRY elfSetLightType(elf_light* light, int type);
ELF_API void ELF_APIENTRY elfSetLightColor(elf_light* light, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetLightDistance(elf_light* light, float distance);
ELF_API void ELF_APIENTRY elfSetLightFadeSpeed(elf_light* light, float fade_speed);
ELF_API void ELF_APIENTRY elfSetLightShadows(elf_light* light, unsigned char shadows);
ELF_API void ELF_APIENTRY elfSetLightVisible(elf_light* light, unsigned char visible);
ELF_API void ELF_APIENTRY elfSetLightCone(elf_light* light, float inner_cone, float outer_cone);
ELF_API void ELF_APIENTRY elfSetLightShaft(elf_light* light, float size, float intensity, float fade_off);
ELF_API void ELF_APIENTRY elfDisableLightShaft(elf_light* light);
ELF_API elf_armature* ELF_APIENTRY elfGetBoneArmature(elf_bone* bone);
ELF_API elf_bone* ELF_APIENTRY elfGetBoneParent(elf_bone* bone);
ELF_API elf_bone* ELF_APIENTRY elfGetBoneChildByName(elf_bone* bone, const char* name);
ELF_API elf_bone* ELF_APIENTRY elfGetBoneChildById(elf_bone* bone, int id);
ELF_API elf_bone* ELF_APIENTRY elfGetBoneChildByIndex(elf_bone* bone, int idx);
ELF_API elf_vec3f ELF_APIENTRY elfGetBonePosition(elf_bone* bone);
ELF_API elf_vec3f ELF_APIENTRY elfGetBoneRotation(elf_bone* bone);
ELF_API elf_vec4f ELF_APIENTRY elfGetBoneOrientation(elf_bone* bone);
ELF_API elf_armature* ELF_APIENTRY elfCreateArmature(const char* name);
ELF_API elf_bone* ELF_APIENTRY elfGetBoneFromArmatureByName(const char* name, elf_armature* armature);
ELF_API elf_bone* ELF_APIENTRY elfGetBoneFromArmatureById(int id, elf_armature* armature);
ELF_API elf_particles* ELF_APIENTRY elfCreateParticles(const char* name, int max_count);
ELF_API const char* ELF_APIENTRY elfGetParticlesName(elf_particles* particles);
ELF_API const char* ELF_APIENTRY elfGetParticlesFilePath(elf_particles* particles);
ELF_API void ELF_APIENTRY elfSetParticlesMaxCount(elf_particles* particles, int max_count);
ELF_API void ELF_APIENTRY elfSetParticlesDrawMode(elf_particles* particles, int mode);
ELF_API void ELF_APIENTRY elfSetParticlesTexture(elf_particles* particles, elf_texture* texture);
ELF_API void ELF_APIENTRY elfClearParticlesTexture(elf_particles* particles);
ELF_API void ELF_APIENTRY elfSetParticlesModel(elf_particles* particles, elf_model* model);
ELF_API void ELF_APIENTRY elfClearParticlesModel(elf_particles* particles);
ELF_API void ELF_APIENTRY elfSetParticlesEntity(elf_particles* particles, elf_entity* entity);
ELF_API void ELF_APIENTRY elfClearParticlesEntity(elf_particles* particles);
ELF_API void ELF_APIENTRY elfSetParticlesGravity(elf_particles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesSpawnDelay(elf_particles* particles, float delay);
ELF_API void ELF_APIENTRY elfSetParticlesSpawn(elf_particles* particles, unsigned char spawn);
ELF_API void ELF_APIENTRY elfSetParticlesSize(elf_particles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesSizeGrowth(elf_particles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesRotation(elf_particles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesRotationGrowth(elf_particles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesLifeSpan(elf_particles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesFadeSpeed(elf_particles* particles, float min, float max);
ELF_API void ELF_APIENTRY elfSetParticlesPositionMin(elf_particles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesPositionMax(elf_particles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesVelocityMin(elf_particles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesVelocityMax(elf_particles* particles, float x, float y, float z);
ELF_API void ELF_APIENTRY elfSetParticlesColorMin(elf_particles* particles, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetParticlesColorMax(elf_particles* particles, float r, float g, float b, float a);
ELF_API int ELF_APIENTRY elfGetParticlesMaxCount(elf_particles* particles);
ELF_API int ELF_APIENTRY elfGetParticlesCount(elf_particles* particles);
ELF_API int ELF_APIENTRY elfGetParticlesDrawMode(elf_particles* particles);
ELF_API elf_texture* ELF_APIENTRY elfGetParticlesTexture(elf_particles* particles);
ELF_API elf_model* ELF_APIENTRY elfGetParticlesModel(elf_particles* particles);
ELF_API elf_entity* ELF_APIENTRY elfGetParticlesEntity(elf_particles* particles);
ELF_API elf_vec3f ELF_APIENTRY elfGetParticlesGravity(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesSpawnDelay(elf_particles* particles);
ELF_API unsigned char ELF_APIENTRY elfGetParticlesSpawn(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesSizeMin(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesSizeMax(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesSizeGrowthMin(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesSizeGrowthMax(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesRotationMin(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesRotationMax(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesRotationGrowthMin(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesRotationGrowthMax(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesLifeSpanMin(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesLifeSpanMax(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesFadeSpeedMin(elf_particles* particles);
ELF_API float ELF_APIENTRY elfGetParticlesFadeSpeedMax(elf_particles* particles);
ELF_API elf_vec3f ELF_APIENTRY elfGetParticlesPositionMin(elf_particles* particles);
ELF_API elf_vec3f ELF_APIENTRY elfGetParticlesPositionMax(elf_particles* particles);
ELF_API elf_vec3f ELF_APIENTRY elfGetParticlesVelocityMin(elf_particles* particles);
ELF_API elf_vec3f ELF_APIENTRY elfGetParticlesVelocityMax(elf_particles* particles);
ELF_API elf_color ELF_APIENTRY elfGetParticlesColorMin(elf_particles* particles);
ELF_API elf_color ELF_APIENTRY elfGetParticlesColorMax(elf_particles* particles);
ELF_API elf_sprite* ELF_APIENTRY elfCreateSprite(const char* name);
ELF_API void ELF_APIENTRY elfSetSpriteMaterial(elf_sprite* sprite, elf_material* material);
ELF_API void ELF_APIENTRY elfSetSpriteScale(elf_sprite* sprite, float x, float y);
ELF_API void ELF_APIENTRY elfSetSpriteFaceCamera(elf_sprite* sprite, unsigned char face_camera);
ELF_API elf_material* ELF_APIENTRY elfGetSpriteMaterial(elf_sprite* sprite);
ELF_API elf_vec2f ELF_APIENTRY elfGetSpriteScale(elf_sprite* sprite);
ELF_API unsigned char ELF_APIENTRY elfGetSpriteFaceCamera(elf_sprite* sprite);
ELF_API void ELF_APIENTRY elfSetSpriteVisible(elf_sprite* sprite, unsigned char visible);
ELF_API unsigned char ELF_APIENTRY elfGetSpriteVisible(elf_sprite* sprite);
ELF_API void ELF_APIENTRY elfSetSpriteOccluder(elf_sprite* sprite, unsigned char occluder);
ELF_API unsigned char ELF_APIENTRY elfGetSpriteOccluder(elf_sprite* sprite);
ELF_API elf_scene* ELF_APIENTRY elfCreateScene(const char* name);
ELF_API elf_scene* ELF_APIENTRY elfCreateSceneFromFile(const char* file_path);
ELF_API unsigned char ELF_APIENTRY elfSaveScene(elf_scene* scene, const char* file_path);
ELF_API void ELF_APIENTRY elfSetSceneAmbientColor(elf_scene* scene, float r, float g, float b, float a);
ELF_API elf_color ELF_APIENTRY elfGetSceneAmbientColor(elf_scene* scene);
ELF_API void ELF_APIENTRY elfSetSceneGravity(elf_scene* scene, float x, float y, float z);
ELF_API elf_vec3f ELF_APIENTRY elfGetSceneGravity(elf_scene* scene);
ELF_API void ELF_APIENTRY elfSetScenePhysics(elf_scene* scene, unsigned char physics);
ELF_API unsigned char ELF_APIENTRY elfGetScenePhysics(elf_scene* scene);
ELF_API void ELF_APIENTRY elfSetSceneRunScripts(elf_scene* scene, unsigned char run_scripts);
ELF_API unsigned char ELF_APIENTRY elfGetSceneRunScripts(elf_scene* scene, unsigned char run_scripts);
ELF_API const char* ELF_APIENTRY elfGetSceneName(elf_scene* scene);
ELF_API const char* ELF_APIENTRY elfGetSceneFilePath(elf_scene* scene);
ELF_API int ELF_APIENTRY elfGetSceneCameraCount(elf_scene* scene);
ELF_API int ELF_APIENTRY elfGetSceneEntityCount(elf_scene* scene);
ELF_API int ELF_APIENTRY elfGetSceneLightCount(elf_scene* scene);
ELF_API int ELF_APIENTRY elfGetSceneArmatureCount(elf_scene* scene);
ELF_API int ELF_APIENTRY elfGetSceneParticlesCount(elf_scene* scene);
ELF_API int ELF_APIENTRY elfGetSceneSpriteCount(elf_scene* scene);
ELF_API void ELF_APIENTRY elfAddCameraToScene(elf_scene* scene, elf_camera* camera);
ELF_API void ELF_APIENTRY elfAddEntityToScene(elf_scene* scene, elf_entity* entity);
ELF_API void ELF_APIENTRY elfAddLightToScene(elf_scene* scene, elf_light* light);
ELF_API void ELF_APIENTRY elfAddParticlesToScene(elf_scene* scene, elf_particles* particles);
ELF_API void ELF_APIENTRY elfAddSpriteToScene(elf_scene* scene, elf_sprite* sprite);
ELF_API void ELF_APIENTRY elfSetSceneActiveCamera(elf_scene* scene, elf_camera* camera);
ELF_API elf_camera* ELF_APIENTRY elfGetSceneActiveCamera(elf_scene* scene);
ELF_API elf_collision* ELF_APIENTRY elfGetSceneRayCastResult(elf_scene* scene, float x, float y, float z, float dx, float dy, float dz);
ELF_API elf_list* ELF_APIENTRY elfGetSceneRayCastResults(elf_scene* scene, float x, float y, float z, float dx, float dy, float dz);
ELF_API elf_collision* ELF_APIENTRY elfGetDebugSceneRayCastResult(elf_scene* scene, float x, float y, float z, float dx, float dy, float dz);
ELF_API elf_list* ELF_APIENTRY elfGetDebugSceneRayCastResults(elf_scene* scene, float x, float y, float z, float dx, float dy, float dz);
ELF_API elf_camera* ELF_APIENTRY elfGetCameraByIndex(elf_scene* scene, int idx);
ELF_API elf_entity* ELF_APIENTRY elfGetEntityByIndex(elf_scene* scene, int idx);
ELF_API elf_light* ELF_APIENTRY elfGetLightByIndex(elf_scene* scene, int idx);
ELF_API elf_armature* ELF_APIENTRY elfGetArmatureByIndex(elf_scene* scene, int idx);
ELF_API elf_particles* ELF_APIENTRY elfGetParticlesByIndex(elf_scene* scene, int idx);
ELF_API elf_sprite* ELF_APIENTRY elfGetSpriteByIndex(elf_scene* scene, int idx);
ELF_API elf_texture* ELF_APIENTRY elfGetTextureByName(elf_scene* scene, const char* name);
ELF_API elf_material* ELF_APIENTRY elfGetMaterialByName(elf_scene* scene, const char* name);
ELF_API elf_model* ELF_APIENTRY elfGetModelByName(elf_scene* scene, const char* name);
ELF_API elf_script* ELF_APIENTRY elfGetScriptByName(elf_scene* scene, const char* name);
ELF_API elf_camera* ELF_APIENTRY elfGetCameraByName(elf_scene* scene, const char* name);
ELF_API elf_entity* ELF_APIENTRY elfGetEntityByName(elf_scene* scene, const char* name);
ELF_API elf_light* ELF_APIENTRY elfGetLightByName(elf_scene* scene, const char* name);
ELF_API elf_armature* ELF_APIENTRY elfGetArmatureByName(elf_scene* scene, const char* name);
ELF_API elf_particles* ELF_APIENTRY elfGetParticlesByName(elf_scene* scene, const char* name);
ELF_API elf_sprite* ELF_APIENTRY elfGetSpriteByName(elf_scene* scene, const char* name);
ELF_API elf_actor* ELF_APIENTRY elfGetActorByName(elf_scene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveCameraByName(elf_scene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveEntityByName(elf_scene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveLightByName(elf_scene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveParticlesByName(elf_scene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveSpriteByName(elf_scene* scene, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveCameraByIndex(elf_scene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveEntityByIndex(elf_scene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveLightByIndex(elf_scene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveParticlesByIndex(elf_scene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveSpriteByIndex(elf_scene* scene, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveCameraByObject(elf_scene* scene, elf_camera* camera);
ELF_API unsigned char ELF_APIENTRY elfRemoveEntityByObject(elf_scene* scene, elf_entity* entity);
ELF_API unsigned char ELF_APIENTRY elfRemoveLightByObject(elf_scene* scene, elf_light* light);
ELF_API unsigned char ELF_APIENTRY elfRemoveParticlesByObject(elf_scene* scene, elf_particles* particles);
ELF_API unsigned char ELF_APIENTRY elfRemoveSpriteByObject(elf_scene* scene, elf_sprite* sprite);
ELF_API unsigned char ELF_APIENTRY elfRemoveActorByObject(elf_scene* scene, elf_actor* actor);
ELF_API elf_list* ELF_APIENTRY elfGetSceneScripts(elf_scene* scene);
ELF_API elf_list* ELF_APIENTRY elfGetSceneTextures(elf_scene* scene);
ELF_API elf_list* ELF_APIENTRY elfGetSceneMaterials(elf_scene* scene);
ELF_API elf_list* ELF_APIENTRY elfGetSceneModels(elf_scene* scene);
ELF_API elf_script* ELF_APIENTRY elfCreateScript(const char* name);
ELF_API elf_script* ELF_APIENTRY elfCreateScriptFromFile(const char* file_path);
ELF_API void ELF_APIENTRY elfSetScriptName(elf_script* script, const char* name);
ELF_API const char* ELF_APIENTRY elfGetScriptName(elf_script* script);
ELF_API const char* ELF_APIENTRY elfGetScriptFilePath(elf_script* script);
ELF_API void ELF_APIENTRY elfSetScriptText(elf_script* script, const char* text);
ELF_API unsigned char ELF_APIENTRY elfIsScriptError(elf_script* script);
ELF_API unsigned char ELF_APIENTRY elfRunString(const char* str);
ELF_API unsigned char ELF_APIENTRY elfRunScript(elf_script* script);
ELF_API void ELF_APIENTRY elfSetAudioVolume(float volume);
ELF_API float ELF_APIENTRY elfGetAudioVolume();
ELF_API void ELF_APIENTRY elfSetAudioRolloff(float rolloff);
ELF_API float ELF_APIENTRY elfGetAudioRolloff();
ELF_API elf_sound* ELF_APIENTRY elfLoadSound(const char* file_path);
ELF_API elf_sound* ELF_APIENTRY elfLoadStreamedSound(const char* file_path);
ELF_API int ELF_APIENTRY elfGetSoundFileType(elf_sound* sound);
ELF_API elf_audio_source* ELF_APIENTRY elfPlaySound(elf_sound* sound, float volume);
ELF_API elf_audio_source* ELF_APIENTRY elfPlayEntitySound(elf_entity* entity, elf_sound* sound, float volume);
ELF_API elf_audio_source* ELF_APIENTRY elfLoopSound(elf_sound* sound, float volume);
ELF_API elf_audio_source* ELF_APIENTRY elfLoopEntitySound(elf_entity* entity, elf_sound* sound, float volume);
ELF_API void ELF_APIENTRY elfSetSoundVolume(elf_audio_source* source, float volume);
ELF_API float ELF_APIENTRY elfGetSoundVolume(elf_audio_source* source);
ELF_API void ELF_APIENTRY elfPauseSound(elf_audio_source* source);
ELF_API void ELF_APIENTRY elfResumeSound(elf_audio_source* source);
ELF_API void ELF_APIENTRY elfStopSound(elf_audio_source* source);
ELF_API unsigned char ELF_APIENTRY elfIsSoundPlaying(elf_audio_source* source);
ELF_API unsigned char ELF_APIENTRY elfIsSoundPaused(elf_audio_source* source);
ELF_API elf_actor* ELF_APIENTRY elfGetCollisionActor(elf_collision* collision);
ELF_API elf_vec3f ELF_APIENTRY elfGetCollisionPosition(elf_collision* collision);
ELF_API elf_vec3f ELF_APIENTRY elfGetCollisionNormal(elf_collision* collision);
ELF_API float ELF_APIENTRY elfGetCollisionDepth(elf_collision* collision);
ELF_API const char* ELF_APIENTRY elfGetJointName(elf_joint* joint);
ELF_API int ELF_APIENTRY elfGetJointType(elf_joint* joint);
ELF_API elf_actor* ELF_APIENTRY elfGetJointActorA(elf_joint* joint);
ELF_API elf_actor* ELF_APIENTRY elfGetJointActorB(elf_joint* joint);
ELF_API elf_vec3f ELF_APIENTRY elfGetJointPivot(elf_joint* joint);
ELF_API elf_vec3f ELF_APIENTRY elfGetJointAxis(elf_joint* joint);
ELF_API elf_font* ELF_APIENTRY elfCreateFontFromFile(const char* file_path, int size);
ELF_API const char* ELF_APIENTRY elfGetFontName(elf_font* font);
ELF_API const char* ELF_APIENTRY elfGetFontFilePath(elf_font* font);
ELF_API int ELF_APIENTRY elfGetFontSize(elf_font* font);
ELF_API int ELF_APIENTRY elfGetStringWidth(elf_font* font, const char* str);
ELF_API int ELF_APIENTRY elfGetStringHeight(elf_font* font, const char* str);
ELF_API const char* ELF_APIENTRY elfGetGuiObjectName(elf_gui_object* object);
ELF_API elf_vec2i ELF_APIENTRY elfGetGuiObjectPosition(elf_gui_object* object);
ELF_API elf_vec2i ELF_APIENTRY elfGetGuiObjectSize(elf_gui_object* object);
ELF_API elf_color ELF_APIENTRY elfGetGuiObjectColor(elf_gui_object* object);
ELF_API unsigned char ELF_APIENTRY elfGetGuiObjectVisible(elf_gui_object* object);
ELF_API elf_script* ELF_APIENTRY elfGetGuiObjectScript(elf_gui_object* object);
ELF_API int ELF_APIENTRY elfGetGuiObjectEvent(elf_gui_object* object);
ELF_API void ELF_APIENTRY elfSetGuiObjectPosition(elf_gui_object* object, float x, float y);
ELF_API void ELF_APIENTRY elfSetGuiObjectColor(elf_gui_object* object, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetGuiObjectVisible(elf_gui_object* object, unsigned char visible);
ELF_API void ELF_APIENTRY elfSetGuiObjectScript(elf_gui_object* object, elf_script* script);
ELF_API elf_label* ELF_APIENTRY elfCreateLabel(const char* name);
ELF_API elf_font* ELF_APIENTRY elfGetLabelFont(elf_label* label);
ELF_API const char* ELF_APIENTRY elfGetLabelText(elf_label* label);
ELF_API void ELF_APIENTRY elfSetLabelFont(elf_label* label, elf_font* font);
ELF_API void ELF_APIENTRY elfSetLabelText(elf_label* label, const char* text);
ELF_API elf_button* ELF_APIENTRY elfCreateButton(const char* name);
ELF_API unsigned char ELF_APIENTRY elfGetButtonState(elf_button* button);
ELF_API elf_texture* ELF_APIENTRY elfGetButtonOffTexture(elf_button* button);
ELF_API elf_texture* ELF_APIENTRY elfGetButtonOverTexture(elf_button* button);
ELF_API elf_texture* ELF_APIENTRY elfGetButtonOnTexture(elf_button* button);
ELF_API void ELF_APIENTRY elfSetButtonOffTexture(elf_button* button, elf_texture* off);
ELF_API void ELF_APIENTRY elfSetButtonOverTexture(elf_button* button, elf_texture* over);
ELF_API void ELF_APIENTRY elfSetButtonOnTexture(elf_button* button, elf_texture* on);
ELF_API elf_picture* ELF_APIENTRY elfCreatePicture(const char* name);
ELF_API elf_texture* ELF_APIENTRY elfGetPictureTexture(elf_picture* picture);
ELF_API elf_vec2f ELF_APIENTRY elfGetPictureScale(elf_picture* picture);
ELF_API void ELF_APIENTRY elfSetPictureTexture(elf_picture* picture, elf_texture* texture);
ELF_API void ELF_APIENTRY elfSetPictureScale(elf_picture* picture, float x, float y);
ELF_API elf_text_field* ELF_APIENTRY elfCreateTextField(const char* name);
ELF_API elf_texture* ELF_APIENTRY elfGetTextFieldTexture(elf_text_field* text_field);
ELF_API elf_font* ELF_APIENTRY elfGetTextFieldFont(elf_text_field* text_field);
ELF_API elf_color ELF_APIENTRY elfGetTextFieldTextColor(elf_text_field* text_field);
ELF_API elf_vec2i ELF_APIENTRY elfGetTextFieldOffset(elf_text_field* text_field);
ELF_API const char* ELF_APIENTRY elfGetTextFieldText(elf_text_field* text_field);
ELF_API void ELF_APIENTRY elfSetTextFieldTexture(elf_text_field* text_field, elf_texture* texture);
ELF_API void ELF_APIENTRY elfSetTextFieldFont(elf_text_field* text_field, elf_font* font);
ELF_API void ELF_APIENTRY elfSetTextFieldTextColor(elf_text_field* text_field, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetTextFieldOffset(elf_text_field* text_field, int offset_x, int offset_y);
ELF_API void ELF_APIENTRY elfSetTextFieldCursorPosition(elf_text_field* text_field, int idx);
ELF_API void ELF_APIENTRY elfSetTextFieldText(elf_text_field* text_field, const char* text);
ELF_API elf_slider* ELF_APIENTRY elfCreateSlider(const char* name);
ELF_API elf_texture* ELF_APIENTRY elfGetSliderBackgroundTexture(elf_slider* slider);
ELF_API elf_texture* ELF_APIENTRY elfGetSliderSliderTexture(elf_slider* slider);
ELF_API float ELF_APIENTRY elfGetSliderValue(elf_slider* slider);
ELF_API void ELF_APIENTRY elfSetSliderBackgroundTexture(elf_slider* slider, elf_texture* background);
ELF_API void ELF_APIENTRY elfSetSliderSliderTexture(elf_slider* slider, elf_texture* slider_texture);
ELF_API void ELF_APIENTRY elfSetSliderValue(elf_slider* slider, float value);
ELF_API elf_screen* ELF_APIENTRY elfCreateScreen(const char* name);
ELF_API elf_texture* ELF_APIENTRY elfGetScreenTexture(elf_screen* screen);
ELF_API void ELF_APIENTRY elfSetScreenTexture(elf_screen* screen, elf_texture* texture);
ELF_API void ELF_APIENTRY elfSetScreenToTop(elf_screen* screen);
ELF_API void ELF_APIENTRY elfForceFocusToScreen(elf_screen* screen);
ELF_API void ELF_APIENTRY elfReleaseFocusFromScreen(elf_screen* screen);
ELF_API elf_text_list* ELF_APIENTRY elfCreateTextList(const char* name);
ELF_API elf_font* ELF_APIENTRY elfGetTextListFont(elf_text_list* text_list);
ELF_API elf_color ELF_APIENTRY elfGetTextListSelectionColor(elf_text_list* text_list);
ELF_API elf_color ELF_APIENTRY elfGetTextListLightColor(elf_text_list* text_list);
ELF_API elf_color ELF_APIENTRY elfGetTextListDarkColor(elf_text_list* text_list);
ELF_API int ELF_APIENTRY elfGetTextListRowCount(elf_text_list* text_list);
ELF_API int ELF_APIENTRY elfGetTextListItemCount(elf_text_list* text_list);
ELF_API int ELF_APIENTRY elfGetTextListSelectionIndex(elf_text_list* text_list);
ELF_API int ELF_APIENTRY elfGetTextListOffset(elf_text_list* text_list);
ELF_API const char* ELF_APIENTRY elfGetTextListItem(elf_text_list* text_list, int idx);
ELF_API const char* ELF_APIENTRY elfGetTextListSelectedItem(elf_text_list* text_list);
ELF_API void ELF_APIENTRY elfSetTextListFont(elf_text_list* text_list, elf_font* font);
ELF_API void ELF_APIENTRY elfSetTextListSelectionColor(elf_text_list* text_list, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetTextListLightColor(elf_text_list* text_list, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetTextListDarkColor(elf_text_list* text_list, float r, float g, float b, float a);
ELF_API void ELF_APIENTRY elfSetTextListSize(elf_text_list* text_list, int rows, int width);
ELF_API void ELF_APIENTRY elfAddTextListItem(elf_text_list* text_list, const char* text);
ELF_API void ELF_APIENTRY elfSetTextListItem(elf_text_list* text_list, int idx, const char* text);
ELF_API unsigned char ELF_APIENTRY elfRemoveTextListItem(elf_text_list* text_list, int idx);
ELF_API void ELF_APIENTRY elfRemoveTextListItems(elf_text_list* text_list);
ELF_API void ELF_APIENTRY elfSetTextListOffset(elf_text_list* text_list, int offset);
ELF_API void ELF_APIENTRY elfSetTextListSelection(elf_text_list* text_list, int selection);
ELF_API elf_check_box* ELF_APIENTRY elfCreateCheckBox(const char* name);
ELF_API unsigned char ELF_APIENTRY elfGetCheckBoxState(elf_check_box* check_box);
ELF_API elf_texture* ELF_APIENTRY elfGetCheckBoxOffTexture(elf_check_box* check_box);
ELF_API elf_texture* ELF_APIENTRY elfGetCheckBoxOnTexture(elf_check_box* check_box);
ELF_API void ELF_APIENTRY elfSetCheckBoxOffTexture(elf_check_box* check_box, elf_texture* off);
ELF_API void ELF_APIENTRY elfSetCheckBoxOnTexture(elf_check_box* check_box, elf_texture* on);
ELF_API void ELF_APIENTRY elfSetCheckBoxState(elf_check_box* check_box, unsigned char state);
ELF_API elf_gui* ELF_APIENTRY elfCreateGui();
ELF_API unsigned char ELF_APIENTRY elfAddGuiObject(elf_gui_object* parent, elf_gui_object* object);
ELF_API elf_gui_object* ELF_APIENTRY elfGetGuiObjectByName(elf_gui_object* parent, const char* name);
ELF_API elf_gui_object* ELF_APIENTRY elfGetGuiObjectByIndex(elf_gui_object* parent, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveGuiObjectByName(elf_gui_object* parent, const char* name);
ELF_API unsigned char ELF_APIENTRY elfRemoveGuiObjectByIndex(elf_gui_object* parent, int idx);
ELF_API unsigned char ELF_APIENTRY elfRemoveGuiObjectByObject(elf_gui_object* parent, elf_gui_object* object);
ELF_API elf_gui_object* ELF_APIENTRY elfGetGuiTrace(elf_gui* gui);
ELF_API elf_gui_object* ELF_APIENTRY elfGetGuiFocus(elf_gui* gui);
ELF_API elf_gui_object* ELF_APIENTRY elfGetGuiActiveTextField(elf_gui* gui);
ELF_API void ELF_APIENTRY elfEmptyGui(elf_gui* gui);
ELF_API unsigned char ELF_APIENTRY elfCreateSession(const char* address, int port);
ELF_API unsigned char ELF_APIENTRY elfConnectSession(const char* address, int port);
ELF_API unsigned char ELF_APIENTRY elfDisconnectSession();
ELF_API void ELF_APIENTRY elfSendStringToClients(const char* message);
ELF_API void ELF_APIENTRY elfSendStringToServer(const char* message);
ELF_API const char* ELF_APIENTRY elfGetServerDataAsString();
ELF_API const char* ELF_APIENTRY elfGetClientDataAsString();
ELF_API int ELF_APIENTRY elfGetServerEvent();
ELF_API int ELF_APIENTRY elfGetClientEvent();
ELF_API int ELF_APIENTRY elfGetCurrentClient();
ELF_API unsigned char ELF_APIENTRY elfIsServer();
ELF_API unsigned char ELF_APIENTRY elfIsClient();
#endif
