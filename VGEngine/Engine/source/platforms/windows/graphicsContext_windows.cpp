#if defined(OS_WINDOWS)

#pragma once
#include "engine/assets/fileManager.h"
#include "engine\graphics\graphicsContext.h"
#include "engine\application.h"
#include "engine/graphics/opengl.h"
#include "engine/utility/logger.h"
#include "engine/application.h"
#include "engine/graphics/opengl.h"
#include <engine/graphics/graphics.h>
#include <Windows.h>
/*
#pragma comment( lib, "glew32d.lib" )
#pragma comment( lib, "glew32sd.lib" )
#pragma comment( lib, "opengl32.lib" )
*/
#include "../external/glew.h"
#include "engine\game\game.h"
using namespace vg::graphics;
using namespace vg::core;
unsigned int mWidth, mHeight; ///< Screen size in pixels

unsigned int mProgramId; //< OpenGL program id
using namespace vg::graphics::gl;

HGLRC renderingContext;

LRESULT CALLBACK WindowProc(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg){
	case WM_CREATE:
	{
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		DestroyWindow(handle);
		vg::Game::getInstance()->setIsRunning(false);
		return 0;
	}
	default:

		return DefWindowProc(handle, uMsg, wParam, lParam);

	}


}
GraphicsContext::GraphicsContext()
{
	mWidth = mHeight = 0;
}

GraphicsContext::~GraphicsContext()
{

}

void GraphicsContext::initialize()
{

	initializeGraphicsContext();
	initializeOpenGL();
}

void GraphicsContext::destroy()
{
}

void GraphicsContext::swapBuffers()
{
	HWND windowHandle = static_cast<HWND>(mWindowHandle);
	HDC windowHandle2 = GetDC(windowHandle);// 
	SwapBuffers(windowHandle2);
}

unsigned int GraphicsContext::getWidth()
{
	return mWidth;
}

unsigned int GraphicsContext::getHeight()
{
	return mHeight;
}

void GraphicsContext::initializeGraphicsContext()
{
	//WINDOW
	WNDCLASS wc = {};
	char* CLASS_NAME = "asd";
	std::string windowName = "VG Engine";
	mWidth = 1280;
	mHeight = 720;
	Graphics::setResolution(Vector2<int>(mWidth, mHeight));

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);
	checkError();
	mWindowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, CLASS_NAME, windowName.c_str(), WS_OVERLAPPEDWINDOW, 100, 100, mWidth, mHeight, //Windowhandle pointter creation
		NULL, NULL, GetModuleHandle(nullptr), NULL);
	checkError();
	if (mWindowHandle == nullptr)
	{

		Log("vgengine", "Window handle creation failed", "");

	}



	//OPENGL

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		24,                        //Colordepth of the framebuffer.		
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE
	};
	WORD  nSize = sizeof(PIXELFORMATDESCRIPTOR);
	WORD  nVersion = 1;
	DWORD dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cRedBits = 0;
	pfd.cRedShift = 0;
	pfd.cGreenBits = 0;
	pfd.cGreenShift = 0;
	pfd.cBlueBits = 0;
	pfd.cBlueShift = 0;
	pfd.cAlphaBits = 0;
	pfd.cAlphaShift = 0;
	pfd.cAccumBits = 0;
	pfd.cAccumRedBits = 0;
	pfd.cAccumGreenBits = 0;
	pfd.cAccumBlueBits = 0;
	pfd.cAccumAlphaBits = 0;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = 0;
	pfd.bReserved = 0;
	DWORD dwLayerMask = NULL;
	DWORD dwVisibleMask = NULL;
	DWORD dwDamageMask = NULL;


	HDC windowHandle = GetDC(static_cast<HWND>(mWindowHandle));// 
	if (windowHandle == nullptr || windowHandle == NULL)
	{
		Log("vgengine", "failed to set openglcontext");
	}
	checkError();
	int  pixelFormat;
	pixelFormat = ChoosePixelFormat(windowHandle, &pfd);
	checkError(); //ERROR CHECK
	Log("vgengine", "Pixelformat: %d",pixelFormat);
	if (!SetPixelFormat(windowHandle, pixelFormat, &pfd))
	{
		Log("vgengine", "Failed to set pixel format");
	}
	checkError(); //ERROR CHECK
	renderingContext = wglCreateContext(windowHandle);
	checkError(); //ERROR CHECK
	if (!wglMakeCurrent(windowHandle, renderingContext))
	{
		Log("vgengine", "Failed to make context current");
	}
	checkError(); //ERROR CHECK
	ShowWindow(static_cast<HWND>(mWindowHandle), SW_SHOWNORMAL);
	checkError(); //ERROR CHECK
}

void GraphicsContext::createGLProgram()
{
	mProgramId = createProgram();
	gl::checkError();
	
}

void GraphicsContext::initializeOpenGL()
{
	glewInit();
	const GLubyte* glVersion = glGetString(GL_VERSION);
	Log("vgengine", "OpenGL ES version: %s", glVersion);
	gl::checkError();

	// transparency
	glEnable(GL_BLEND);
	gl::checkError();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gl::checkError();

	// z-layer
	glEnable(GL_DEPTH_TEST);
	gl::checkError();
	glEnable(GL_CULL_FACE);
	gl::checkError();
	glCullFace(GL_BACK);
	gl::checkError();
	glFrontFace(GL_CCW);
	gl::checkError();
	glDepthFunc(GL_LESS);
	gl::checkError();
	glDepthMask(GL_TRUE);
	gl::checkError();
	glDepthRangef(0.0, 1.0);
	gl::checkError();

	// font
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	gl::checkError();
}

unsigned int GraphicsContext::getProgramId()
{
	return mProgramId;
}

void GraphicsContext::checkError()
{
	DWORD error = GetLastError();
	if (error != ERROR_SUCCESS)
		Log("vgengine", "Error initializing window, errorcode: %d!\n",error);
}
#endif