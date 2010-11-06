
#define ELF_OBJECT_HEADER \
	int objType; \
	int objRefCount; \
	void (*objDestr)(void*)

#define ELF_RESOURCE_HEADER \
	ELF_OBJECT_HEADER; \
	int id; \
	char* name

#define ELF_ACTOR_HEADER \
	ELF_RESOURCE_HEADER; \
	char* filePath; \
	elfScene* scene; \
	gfxTransform* transform; \
	elfList* joints; \
	elfScript* script; \
	elfList* sources; \
	elfIpo* ipo; \
	elfFramePlayer* ipoPlayer; \
	elfList* properties; \
	elfPhysicsObject* object; \
	elfPhysicsObject* dobject; \
	unsigned char physics; \
	elfVec3f pbbLengths; \
	elfVec3f pbbOffset; \
	unsigned char pbbOffsetSet; \
	unsigned char shape; \
	float mass; \
	float linDamp; \
	float angDamp; \
	float linSleep; \
	float angSleep; \
	float restitution; \
	elfVec3f anisFric; \
	elfVec3f linFactor; \
	elfVec3f angFactor; \
	unsigned char moved; \
	unsigned char selected

#define ELF_GUI_OBJECT_HEADER \
	ELF_OBJECT_HEADER; \
	char* name; \
	elfVec2i pos; \
	elfVec2i relPos; \
	int width, height; \
	elfColor color; \
	unsigned char visible; \
	unsigned char active; \
	elfGui* root; \
	elfGuiObject* parent; \
	elfList* children; \
	elfList* screens; \
	elfScript* script; \
	int event

struct elfObject {
	ELF_OBJECT_HEADER;
};

struct elfResource {
	ELF_RESOURCE_HEADER;
};

struct elfString {
	ELF_OBJECT_HEADER;
	char* str;
};

typedef struct elfListPtr {
	struct elfListPtr* prev;
	struct elfListPtr* next;
	elfObject* obj;
} elfListPtr;

struct elfList {
	ELF_OBJECT_HEADER;
	elfListPtr* first;
	elfListPtr* last;
	elfListPtr* cur;
	elfListPtr* next;
	int length;
};

struct elfGeneral {
	ELF_OBJECT_HEADER;
	char* log;

	char* errStr;
	int errCode;

	int refCount;
	int objCount;
	int refTable[ELF_OBJECT_TYPE_COUNT];
	int objTable[ELF_OBJECT_TYPE_COUNT];
};

struct elfConfig {
	ELF_OBJECT_HEADER;
	elfVec2i windowSize;
	char* windowTitle;
	int multisamples;
	unsigned char fullscreen;
	unsigned char textureCompress;
	float textureAnisotropy;
	int shadowMapSize;
	char* start;
	char* logPath;
	float fpsLimit;
	float tickRate;
	float speed;
	unsigned char f10Exit;
};

struct elfKeyEvent {
	ELF_OBJECT_HEADER;
	int key;
	unsigned char state;
};

struct elfCharEvent {
	ELF_OBJECT_HEADER;
	int code;
	unsigned char state;
};

typedef struct elfJoystick {
	unsigned char present;
	float axisPos[2];
	unsigned char curButs[16];
	unsigned char prvButs[16];
} elfJoystick;

struct elfVideoMode {
	ELF_OBJECT_HEADER;
	elfVec2i reso;
};

struct elfContext {
	ELF_OBJECT_HEADER;
	int width;
	int height;
	unsigned char fullscreen;
	char* title;
	int multisamples;
	elfList* videoModes;
	unsigned char curKeys[256];
	unsigned char prvKeys[256];
	int mousePosition[2];
	int prvMousePosition[2];
	unsigned char hideMouse;
	int mouseWheel;
	unsigned char curMbuts[3];
	unsigned char prvMbuts[3];
	elfJoystick joysticks[16];
	elfList* events;
};

struct elfEngine {
	ELF_OBJECT_HEADER;

	elfConfig* config;

	char cwd[256];

	int fps;
	unsigned int frames;
	float sync;
	elfTimer* fpsTimer;
	elfTimer* fpsLimitTimer;
	elfTimer* timeSyncTimer;

	unsigned char freeRun;
	unsigned char quit;

	elfPostProcess* postProcess;

	elfFont* guiFont;

	elfScene* scene;
	elfGui* gui;
	elfObject* actor;
};

struct elfRenderStation {
	ELF_OBJECT_HEADER;

	gfxTexture* shadowMap;
	gfxRenderTarget* shadowTarget;

	gfxVertexData* quadVertexData;
	gfxVertexData* quadTexCoordData;
	gfxVertexData* quadNormalData;
	gfxVertexArray* quadVertexArray;

	gfxVertexData* bbVertexData;
	gfxVertexData* bbIndexData;
	gfxVertexArray* bbVertexArray;
	gfxVertexIndex* bbVertexIndex;

	gfxVertexData* lines;
	gfxVertexArray* linesVertexArray;

	gfxVertexData* circleVertexData;
	gfxVertexArray* circleVertexArray;

	int prevCircleVerticeCount;
	float prevCircleSize;
	gfxVertexArray* spriteVertexArray;

	gfxVertexData* gradientVertexData;
	gfxVertexData* gradientColorData;
	gfxVertexArray* gradientVertexArray;
};

struct elfResources {
	ELF_OBJECT_HEADER;
	elfList* textures;

	int sceneIdCounter;
	int scriptIdCounter;
	int textureIdCounter;
	int materialIdCounter;
	int modelIdCounter;
	int cameraIdCounter;
	int entityIdCounter;
	int lightIdCounter;
	int armatureIdCounter;
	int particlesIdCounter;
	int spriteIdCounter;
};

struct elfDirectory {
	ELF_OBJECT_HEADER;
	char* path;
	elfList* items;
};

struct elfDirectoryItem {
	ELF_OBJECT_HEADER;
	char* name;
	unsigned char itemType;
};

struct elfFramePlayer {
	ELF_OBJECT_HEADER;
	float start;
	float end;
	float curFrame;
	float speed;
	unsigned char pause;
	unsigned char loop;
	void* userData;
	void (*callback)(elfFramePlayer* );
};

struct elfTimer {
	ELF_OBJECT_HEADER;
	double start;
};

struct elfImage {
	ELF_OBJECT_HEADER;
	int width;
	int height;
	unsigned char bpp;
	unsigned char* data;
};

struct elfTexture {
	ELF_RESOURCE_HEADER;
	char* filePath;
	gfxTexture* texture;

	void* data;
	int dataSize;
};

struct elfMaterial {
	ELF_RESOURCE_HEADER;
	char* filePath;
	elfColor diffuseColor;
	elfColor ambientColor;
	elfColor specularColor;
	float specPower;
	unsigned char lighting;

	elfTexture* diffuseMap;
	elfTexture* normalMap;
	elfTexture* heightMap;
	elfTexture* specularMap;
	elfTexture* lightMap;
	elfTexture* cubeMap;

	float parallaxScale;

	unsigned char alphaTest;
	float alphaThreshold;
};

struct elfBezierPoint {
	ELF_OBJECT_HEADER;
	elfVec2f c1;
	elfVec2f p;
	elfVec2f c2;
};

struct elfBezierCurve {
	ELF_OBJECT_HEADER;
	unsigned char curveType;
	unsigned char interpolation;
	elfList* points;
};

struct elfIpo {
	ELF_OBJECT_HEADER;
	elfList* curves;
	unsigned char loc;
	unsigned char rot;
	unsigned char scale;
	unsigned char qua;
};

struct elfProperty {
	ELF_OBJECT_HEADER;
	char* name;
	unsigned char propertyType;
	int ival;
	float fval;
	char* sval;
	unsigned char bval;
};

struct elfActor {
	ELF_ACTOR_HEADER;
};

struct elfCamera {
	ELF_ACTOR_HEADER;
	int mode;
	int viewpX, viewpY;
	int viewpWidth, viewpHeight;
	elfVec3f position;
	float fov;
	float aspect;
	int orthoX, orthoY;
	int orthoWidth, orthoHeight;
	float clipFar, clipNear;
	float farPlaneWidth, farPlaneHeight;
	float frustum[6][4];
	float projectionMatrix[16];
	float modelviewMatrix[16];
};

struct elfVertex {
	ELF_OBJECT_HEADER;
	elfVec3f position;
	elfVec3f normal;
	elfVec2f texCoord;
};

struct elfFace {
	ELF_OBJECT_HEADER;
	int v1, v2, v3;
};

struct elfMeshData {
	ELF_OBJECT_HEADER;
	elfList* vertices;
	elfList* faces;
};

typedef struct elfModelArea {
	int indiceCount;
	gfxVertexData* index;
	gfxVertexIndex* vertexIndex;
	unsigned int materialNumber;
} elfModelArea;

struct elfModel {
	ELF_RESOURCE_HEADER;
	char* filePath;
	int verticeCount;
	int frameCount;
	int areaCount;
	int indiceCount;
	gfxVertexArray* vertexArray;
	gfxVertexData* vertices;
	gfxVertexData* normals;
	gfxVertexData* texCoords;
	gfxVertexData* tangents;
	unsigned int* index;
	float* weights;
	int* boneids;
	elfPhysicsTriMesh* triMesh;
	elfModelArea* areas;
	elfVec3f bbMin;
	elfVec3f bbMax;
};

struct elfEntity {
	ELF_ACTOR_HEADER;

	elfModel* model;

	elfArmature* armature;
	gfxVertexData* vertices;
	gfxVertexData* normals;

	elfList* materials;
	elfFramePlayer* armaturePlayer;
	float prevArmatureFrame;

	elfVec3f position;
	elfVec3f scale;
	elfVec3f bbMin;
	elfVec3f bbMax;
	elfVec3f bbOffset;
	elfVec3f armBbMin;
	elfVec3f armBbMax;
	elfVec3f cullAabbMin;
	elfVec3f cullAabbMax;
	float cullRadius;

	gfxQuery* query;
	unsigned char visible;
	unsigned char occluder;
	unsigned char culled;
};

struct elfLight {
	ELF_ACTOR_HEADER;
	int lightType;
	elfColor color;
	float range;
	float fadeRange;
	float innerCone;
	float outerCone;
	unsigned char visible;
	unsigned char shaft;
	float shaftSize;
	float shaftIntensity;
	float shaftFadeOff;

	unsigned char shadows;
	elfCamera* shadowCamera;

	float projectionMatrix[16];
};

typedef struct elfBoneFrame {
	elfVec3f pos;
	elfVec4f qua;
	elfVec3f offsetPos;
	elfVec4f offsetQua;
} elfBoneFrame;

struct elfBone {
	ELF_RESOURCE_HEADER;
	elfBone* parent;
	elfVec3f pos;
	elfVec4f qua;
	elfVec3f curPos;
	elfVec4f curQua;
	elfVec3f curOffsetPos;
	elfVec4f curOffsetQua;
	elfBoneFrame* frames;
	elfList* children;
	elfArmature* armature;
};

struct elfArmature {
	ELF_RESOURCE_HEADER;
	char* filePath;
	int frameCount;
	int boneCount;
	elfList* rootBones;
	elfBone* *bones;
	float curFrame;
	elfVec3f bbMin;
	elfVec3f bbMax;
};

struct elfParticle {
	ELF_OBJECT_HEADER;
	float size;
	float sizeGrowth;
	float rotation;
	float rotationGrowth;
	elfColor color;
	float lifeSpan;
	float fadeSpeed;
	elfVec3f position;
	elfVec3f velocity;
};

struct elfParticles {
	ELF_ACTOR_HEADER;

	int maxCount;
	unsigned char drawMode;
	elfList* particles;
	elfTexture* texture;
	elfModel* model;
	elfEntity* entity;
	gfxVertexArray* vertexArray;
	gfxVertexData* vertices;
	gfxVertexData* texCoords;
	gfxVertexData* colors;

	int spawnCount;
	float spawnDelay;
	unsigned char spawn;
	float curTime;
	elfVec3f gravity;
	float sizeMin;
	float sizeMax;
	float sizeGrowthMin;
	float sizeGrowthMax;
	float rotationMin;
	float rotationMax;
	float rotationGrowthMin;
	float rotationGrowthMax;
	float lifeSpanMin;
	float lifeSpanMax;
	float fadeSpeedMin;
	float fadeSpeedMax;
	elfVec3f velocityMin;
	elfVec3f velocityMax;
	elfVec3f positionMin;
	elfVec3f positionMax;
	elfColor colorMin;
	elfColor colorMax;

	elfVec3f cullAabbMin;
	elfVec3f cullAabbMax;
};

struct elfSprite {
	ELF_ACTOR_HEADER;

	elfMaterial* material;
	elfFramePlayer* framePlayer;

	unsigned char faceCamera;

	elfVec3f position;
	elfVec2f scale;
	elfVec2f size;
	float cullRadius;

	gfxQuery* query;
	unsigned char visible;
	unsigned char occluder;
	unsigned char culled;
};

struct elfScene {
	ELF_RESOURCE_HEADER;
	char* filePath;

	unsigned char physics;
	unsigned char runScripts;
	unsigned char debugDraw;
	unsigned char occlusionCulling;

	elfColor ambientColor;

	unsigned char fog;
	float fogStart;
	float fogEnd;
	elfColor fogColor;

	elfList* scripts;
	elfList* textures;
	elfList* materials;
	elfList* models;
	elfList* cameras;
	elfList* entities;
	elfList* lights;
	elfList* armatures;
	elfList* particles;
	elfList* sprites;

	elfList* entityQueue;
	int entityQueueCount;

	elfList* spriteQueue;
	int spriteQueueCount;

	elfPhysicsWorld* world;
	elfPhysicsWorld* dworld;

	elfCamera* curCamera;

	gfxShaderParams shaderParams;

	gfxShaderProgram* composeFogShdr;

	elfPak* pak;
};

struct elfPakIndex {
	ELF_OBJECT_HEADER;
	unsigned char indexType;
	char* name;
	unsigned int offset;
};

struct elfPak {
	ELF_OBJECT_HEADER;
	char* filePath;
	elfList* indexes;

	int textureCount;
	int materialCount;
	int modelCount;
	int cameraCount;
	int entityCount;
	int lightCount;
	int armatureCount;
	int sceneCount;
	int scriptCount;
};

struct elfPostProcess {
	ELF_OBJECT_HEADER;

	gfxTexture* mainRtColor[2];
	gfxTexture* mainRtDepth;
	gfxRenderTarget* mainRt;

	gfxTexture* rtTexHigh_1;
	gfxTexture* rtTexHigh_2;
	gfxTexture* rtTexHighDepth;
	gfxTexture* rtTexMed_1;
	gfxTexture* rtTexMed_2;
	gfxTexture* rtTexMed_3;
	gfxTexture* rtTexLow_1;
	gfxTexture* rtTexLow_2;
	gfxTexture* rtTexTiny_1;
	gfxTexture* rtTexTiny_2;

	gfxRenderTarget* rtHigh;
	gfxRenderTarget* rtMed;
	gfxRenderTarget* rtLow;
	gfxRenderTarget* rtTiny;
	
	gfxShaderProgram* hipassShdr;
	gfxShaderProgram* blurShdr;
	gfxShaderProgram* bloomCombineShdr;
	gfxShaderProgram* dofCombineShdr;
	gfxShaderProgram* ssaoShdr;
	gfxShaderProgram* ssaoCombineShdr;
	gfxShaderProgram* lightShaftShdr;

	unsigned char bloom;
	float bloomThreshold;

	unsigned char dof;
	float dofFocalRange;
	float dofFocalDistance;
	unsigned char dofAutoFocus;

	unsigned char ssao;
	float ssaoAmount;

	unsigned char lightShafts;
	float lightShaftsIntensity;
	gfxTransform* lightShaftTransform;

	int bufferWidth;
	int bufferHeight;

	gfxShaderParams shaderParams;
};

struct elfScript {
	ELF_RESOURCE_HEADER;
	char* filePath;
	char* text;
	unsigned char error;
};

typedef struct elfCharacter {
	char code;
	gfxTexture* texture;
	int offsetX, offsetY;
} elfCharacter;

struct elfFont {
	ELF_OBJECT_HEADER;
	char* name;
	char* filePath;
	int size;
	elfCharacter chars[128];
	int offsetY;
};

struct elfArea {
	elfVec2i pos;
	elfVec2i size;
};

struct elfGuiObject {
	ELF_GUI_OBJECT_HEADER;
};

struct elfLabel {
	ELF_GUI_OBJECT_HEADER;
	elfFont* font;
	char* text;
};

struct elfButton {
	ELF_GUI_OBJECT_HEADER;
	char *text;
	elfFont* font;
	unsigned char state;
	elfTexture* off;
	elfTexture* over;
	elfTexture* on;
};

struct elfPicture {
	ELF_GUI_OBJECT_HEADER;
	elfTexture* texture;
	elfVec2f scale;
};

struct elfTextField {
	ELF_GUI_OBJECT_HEADER;
	elfTexture* texture;
	elfFont* font;
	int offsetX, offsetY;
	elfColor textColor;
	int cursorPos;
	int drawPos;
	int drawOffset;
	char* text;
};

struct elfSlider {
	ELF_GUI_OBJECT_HEADER;
	elfTexture* background;
	elfTexture* slider;
	float value;
};

struct elfScreen {
	ELF_GUI_OBJECT_HEADER;
	elfTexture* texture;
};

struct elfTextList {
	ELF_GUI_OBJECT_HEADER;
	elfFont* font;
	elfList* items;
	int rows;
	int listWidth;
	int selection;
	int offset;
	unsigned char itemDrag;
};

struct elfCheckBox {
	ELF_GUI_OBJECT_HEADER;
	unsigned char state;
	elfTexture* off;
	elfTexture* on;
};

struct elfGui {
	ELF_GUI_OBJECT_HEADER;
	elfFont* defFont;
	gfxShaderParams shaderParams;
	elfGuiObject* trace;
	elfGuiObject* target;
	elfTextField* activeTextField;
	elfScreen* focusScreen;
	unsigned char dragging;
	char* dragContent;
	elfGuiObject* dragObject;

	unsigned char updateSize;

	int curKey;
	float keyStep;
	unsigned char keyRepeat;

	char curChar;
	float charStep;
	unsigned char charRepeat;
};

