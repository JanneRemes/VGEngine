/**
 * @file Main.cpp
 */

#include <array>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <android/asset_manager.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android_native_app_glue.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#define AT_CHECK_EGL_ERROR(result) \
	(result == EGL_FALSE) ? failEGLErrorCheck(__LINE__) : static_cast<void>(0);

#define AT_LOG_INFO(...) \
	__android_log_print(ANDROID_LOG_INFO, "Android Test", __VA_ARGS__)

#define AT_LOG_ERROR(...) \
	__android_log_print(ANDROID_LOG_WARN, "Android Test", __VA_ARGS__)

template<unsigned int Size>
using VertexData = std::array<float, Size>;

struct Application
{
	android_app* nativeApplication;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	unsigned int width;
	unsigned int height;

	bool isInitialised;
	bool canDraw;

	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint vertexBuffer;
	GLuint texture;
};

static const bool DESTROY_GRAPHICS_CONTEXT = true;

static const char* VERTEX_SOURCE =
	"attribute vec4 attrPosition;"
	"attribute vec2 attrTextureCoords;"

	"varying vec2 textureCoords;"

	"void main()"
	"{"
	"	textureCoords = attrTextureCoords;"
	"	gl_Position = attrPosition;"
	"}";

static const char* FRAGMENT_SOURCE =
	"precision mediump float;"
	
	"uniform sampler2D sampler;"
	"varying vec2 textureCoords;"

	"void main()"
	"{"
	"	float alpha = texture2D(sampler, textureCoords).a;"
	"	gl_FragColor = vec4(1.0, 0.0, 0.0, alpha);"
	"}";

static const VertexData<20u> VERTEX_DATA
{{
	-0.5f,	0.5f, 0.0f,    0.0f, -1.0f,
	-0.5f, -0.5f, 0.0f,    0.0f,  0.0f,
	 0.5f, -0.5f, 0.0f,    1.0f,  0.0f,
	 0.5f,	0.5f, 0.0f,    1.0f, -1.0f
}};

FT_Library freeType;
FT_Byte* fontData;
FT_Face fontFace;

static inline void failEGLErrorCheck(const unsigned int line)
{
	AT_LOG_ERROR("EGL error occurred on line %u with error 0x%X", line, eglGetError());
	std::abort();
}

//static void processFile(Application* application)
//{
//	std::FILE* fileStream = std::fopen("/sdcard/hello.txt", "r+");
//	assert(fileStream != nullptr);
//	int result = std::fseek(fileStream, 0, SEEK_SET);
//	assert(result == 0);
//
//	char value;
//	const unsigned int readCount = std::fread(&value, sizeof(value), 1u, fileStream);
//
//	if(readCount == 0u)
//	{
//		AT_LOG_INFO("No data exists in the file");
//		value = 'a';
//	}
//	else
//	{
//		AT_LOG_INFO("Data in the file: %c", value);
//		++value;
//	}
//
//	result = std::fseek(fileStream, 0, SEEK_SET);
//	assert(result == 0);
//
//	const unsigned int writeCount = std::fwrite(&value, sizeof(value), 1u, fileStream);
//	assert(writeCount > 0u);
//	AT_LOG_INFO("Wrote %i object(s) to the file", writeCount);
//
//	result = std::fclose(fileStream);
//	assert(result == 0);
//}

static void createGraphicsContext(Application* application)
{
	const EGLint configAttributes[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_RED_SIZE,		 8,
		EGL_GREEN_SIZE,		 8,
		EGL_BLUE_SIZE,		 8,
		EGL_SURFACE_TYPE,	 EGL_WINDOW_BIT,
		EGL_NONE
	};

	const EGLint contextAttributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	assert(display != EGL_NO_DISPLAY);

	EGLint versionMajor;
	EGLint versionMinor;
	EGLBoolean result = eglInitialize(display, &versionMajor, &versionMinor);
	AT_CHECK_EGL_ERROR(result);

	AT_LOG_INFO("EGL version: %i.%i", versionMajor, versionMinor);

	EGLConfig config;
	EGLint configCount;
	result = eglChooseConfig(display, configAttributes, &config, 1, &configCount);
	AT_CHECK_EGL_ERROR(result);

	EGLint attribute;
	result = eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &attribute);
	AT_CHECK_EGL_ERROR(result);
	EGLNativeWindowType windowHandle = application->nativeApplication->window;
	ANativeWindow_setBuffersGeometry(windowHandle, 0, 0, attribute);

	EGLSurface surface = eglCreateWindowSurface(display, config, windowHandle, nullptr);

	if(surface == EGL_NO_SURFACE)
		AT_CHECK_EGL_ERROR(EGL_FALSE);

	EGLContext context = application->context;

	if(context == EGL_NO_CONTEXT)
	{
		AT_LOG_INFO("eglCreateContext");
		context = eglCreateContext(display, config, nullptr, contextAttributes);

		if(context == EGL_NO_CONTEXT)
			AT_CHECK_EGL_ERROR(EGL_FALSE);
	}

	result = eglMakeCurrent(display, surface, surface, context);
	AT_CHECK_EGL_ERROR(result);

	EGLint width;
	result = eglQuerySurface(display, surface, EGL_WIDTH, &width);
	AT_CHECK_EGL_ERROR(result);

	EGLint height;
	result = eglQuerySurface(display, surface, EGL_HEIGHT, &height);
	AT_CHECK_EGL_ERROR(result);

	AT_LOG_INFO("Screen resolution: [%i, %i]", width, height);

	application->display = display;
	application->surface = surface;
	application->context = context;
	application->width = width;
	application->height = height;
}

static void initialiseOpenGL(Application* application)
{
	GLuint program = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VERTEX_SOURCE, nullptr);
	glCompileShader(vertexShader);

	GLint parameter;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &parameter);
	assert(parameter == GL_TRUE);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FRAGMENT_SOURCE, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &parameter);

	if(parameter == GL_FALSE)
	{
		GLchar buffer[1024];
		GLsizei charsWritten;
		glGetShaderInfoLog(fragmentShader, 1024, &charsWritten, buffer);
		AT_LOG_INFO("Failed to compile shader: %s", buffer);
		assert(false);
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glBindAttribLocation(program, 0, "attrPosition");
	glBindAttribLocation(program, 1, "attrTextureCoords");
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &parameter);
	assert(parameter == GL_TRUE);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VERTEX_DATA.size(), VERTEX_DATA.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	application->program = program;
	application->vertexShader = vertexShader;
	application->fragmentShader = fragmentShader;
	application->vertexBuffer = vertexBuffer;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void initialiseFreeType(Application* application)
{
	FT_Error error = FT_Init_FreeType(&freeType);
	assert(error == 0);

	AAssetManager* assetManager = application->nativeApplication->activity->assetManager;
	AAsset* asset = AAssetManager_open(assetManager, "arial.ttf", AASSET_MODE_UNKNOWN);
	assert(asset != nullptr);

	const off_t assetSize = AAsset_getLength(asset);
	fontData = new FT_Byte[assetSize];
	const int readSize = AAsset_read(asset, fontData, assetSize);
	assert(readSize == assetSize);
	AAsset_close(asset);

	error = FT_New_Memory_Face(freeType, fontData, assetSize, 0, &fontFace);
	assert(error == 0);
	error = FT_Set_Pixel_Sizes(fontFace, 50u, 50u);
	assert(error == 0);

	const FT_UInt glyphIndex = FT_Get_Char_Index(fontFace, 0x41);
	error = FT_Load_Glyph(fontFace, glyphIndex, FT_LOAD_RENDER);
	assert(error == 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &application->texture);
	glBindTexture(GL_TEXTURE_2D, application->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);
}

static void deinitialiseFreeType(Application* application)
{
	FT_Done_Face(fontFace);
	delete[] fontData;
}

static void deinitialiseOpenGL(Application* application)
{
	AT_LOG_INFO("deinitialiseOpenGL");

	glDeleteTextures(1, &application->texture);
	glDeleteBuffers(1, &application->vertexBuffer);
	glDeleteShader(application->fragmentShader);
	glDeleteShader(application->vertexShader);
	glDeleteProgram(application->program);
}

static void unmakeEGLContextCurrent(Application* application)
{
	AT_LOG_INFO("unmakeEGLContextCurrent");
	EGLBoolean result = eglMakeCurrent(application->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	AT_CHECK_EGL_ERROR(result);
}

static void destroyEGLContext(Application* application)
{
	AT_LOG_INFO("destroyEGLContext");
	EGLBoolean result = eglDestroyContext(application->display, application->context);
	AT_CHECK_EGL_ERROR(result);
	application->context = EGL_NO_CONTEXT;
}

static void destroyEGLSurfaceAndDisplay(Application* application)
{
	AT_LOG_INFO("destroyEGLSurfaceAndDisplay");
	EGLBoolean result = eglDestroySurface(application->display, application->surface);
	AT_CHECK_EGL_ERROR(result);
	application->surface = EGL_NO_SURFACE;

	result = eglTerminate(application->display);
	AT_CHECK_EGL_ERROR(result);
	application->display = EGL_NO_DISPLAY;
}

static void draw(Application* application)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, application->vertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glUseProgram(application->program);
	glBindTexture(GL_TEXTURE_2D, application->texture);

	const GLbyte indices[] = { 0u, 1u, 2u, 0u, 2u, 3u };

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	glBindTexture(GL_TEXTURE_2D, 0u);
	glUseProgram(0u);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	const EGLBoolean result = eglSwapBuffers(application->display, application->surface);
	AT_CHECK_EGL_ERROR(result);
}

static void processCommand(android_app* nativeApplicaton, int32_t command)
{
	Application* application = reinterpret_cast<Application*>(nativeApplicaton->userData);

	switch(command)
	{
		case APP_CMD_INIT_WINDOW:
			AT_LOG_INFO("Creating graphics context...");
			createGraphicsContext(application);

			/*if(!application->isInitialised)
			{*/
				initialiseOpenGL(application);
				initialiseFreeType(application);
				application->isInitialised = true;
			//}

			application->canDraw = true;
			AT_LOG_INFO("Graphics context created");
			
			break;

		case APP_CMD_TERM_WINDOW:
			AT_LOG_INFO("Destroying graphics context...");
			application->canDraw = false;

			if(DESTROY_GRAPHICS_CONTEXT)
			{
				deinitialiseFreeType(application);
				deinitialiseOpenGL(application);
			}

			unmakeEGLContextCurrent(application);
			
			if(DESTROY_GRAPHICS_CONTEXT)
				destroyEGLContext(application);

			destroyEGLSurfaceAndDisplay(application);
			AT_LOG_INFO("Graphics context destroyed");

			break;
	}
}

static int32_t processInput(android_app* nativeApplicaton, AInputEvent* event)
{
	return 0;
}

void android_main(android_app* nativeApplication)
{
	Application application;
	application.nativeApplication = nativeApplication;
	application.display = EGL_NO_DISPLAY;
	application.surface = EGL_NO_SURFACE;
	application.context = EGL_NO_CONTEXT;
	application.width = 0u;
	application.height = 0u;
	application.isInitialised = false;
	application.canDraw = false;

	nativeApplication->onAppCmd = processCommand;
	nativeApplication->onInputEvent = processInput;
	nativeApplication->userData = &application;

	//processFile(&application);

	bool exit = false;
	int id;
	int events;
	android_poll_source* pollSource;

	while(!exit)
	{
		while((id = ALooper_pollAll(0, nullptr, &events, reinterpret_cast<void**>(&pollSource))) >= 0)
		{
			if (pollSource != nullptr)
				pollSource->process(nativeApplication, pollSource);

			if (nativeApplication->destroyRequested != 0)
			{
				AT_LOG_INFO("Application termination requested");
				exit = true;
				break;
			}
		}

		if(application.canDraw)
			draw(&application);
	}
}
