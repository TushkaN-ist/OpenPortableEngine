#pragma once

#ifndef OOGL_EXTENSIONS_HPP
#define OOGL_EXTENSIONS_HPP

//#include <Platform/PlatformIncludes.hpp>
#include <Platform/PlatformOGL.h>

#ifndef _PLATFORM_PSP
namespace GL
{
	void LoadExtensions();
	void* LoadExtension( const char* name );
	template<typename T>
	void LoadExt(T& extension,const char* funcName){
		//printf(funcName);
		extension = (T)LoadExtension( funcName );
	}
	#define LoadExt(extensionName) LoadExt(extensionName,#extensionName)
}

//#define GL_GLEXT_PROTOTYPES
//#define GL_COREARB

#if defined(GL_COREARB)
#include <GL/glcorearb.h>
#else
#include <GL/glext.h>
#include <GL/wglext.h>
#endif

#define GL_EXTNAME(x) x
#define GL_EXT(x) PFN##x##PROC
#define GL_ARBEXT(x) PFN##x##ARBPROC

#ifndef GL_GLEXT_PROTOTYPES

#ifndef WGL_WGLEXT_PROTOTYPES && defined(_PLATFORM_WINDOWS)
typedef const char *(WINAPI * PFNWGLGETEXTENSIONSSTRINGEXTPROC) (void);
typedef HGLRC ( WINAPI * WGLCREATECONTEXTATTRIBSARB ) ( HDC hDC, HGLRC hShareContext, const int* attribList );
GLAPI WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;
typedef BOOL ( WINAPI * WGLCHOOSEPIXELFORMATARB ) ( HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats );
GLAPI WGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB;
typedef int (WINAPI * PFNWGLGETSWAPINTERVALEXTPROC) (void);
GLAPI PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;
typedef BOOL ( WINAPI * PFNWGLSWAPINTERVALEXTPROC ) ( int interval );
GLAPI PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
#endif

GLAPI GL_EXT(GLCOMPILESHADER) glCompileShader;
GLAPI GL_EXT(GLCREATESHADER) glCreateShader;
GLAPI GL_EXT(GLDELETESHADER) glDeleteShader;
GLAPI GL_EXT(GLGETSHADERIV) glGetShaderiv;
GLAPI GL_EXT(GLGETSHADERINFOLOG) glGetShaderInfoLog;
GLAPI GL_EXT(GLSHADERSOURCE) glShaderSource;

GLAPI GL_EXT(GLCREATEPROGRAM) glCreateProgram;
GLAPI GL_EXT(GLDELETEPROGRAM) glDeleteProgram;
GLAPI GL_EXT(GLUSEPROGRAM) glUseProgram;
GLAPI GL_EXT(GLATTACHSHADER) glAttachShader;
GLAPI GL_EXT(GLLINKPROGRAM) glLinkProgram;
GLAPI GL_EXT(GLGETPROGRAMIV) glGetProgramiv;
GLAPI GL_EXT(GLGETPROGRAMINFOLOG) glGetProgramInfoLog;
GLAPI GL_EXT(GLGETATTRIBLOCATION) glGetAttribLocation;
GLAPI GL_EXT(GLGETUNIFORMLOCATION) glGetUniformLocation;

/*
	Uniforms
*/
GLAPI GL_EXT(GLUNIFORM1F) glUniform1f;
GLAPI GL_EXT(GLUNIFORM2F) glUniform2f;
GLAPI GL_EXT(GLUNIFORM3F) glUniform3f;
GLAPI GL_EXT(GLUNIFORM4F) glUniform4f;
GLAPI GL_EXT(GLUNIFORM1I) glUniform1i;
GLAPI GL_EXT(GLUNIFORM2I) glUniform2i;
GLAPI GL_EXT(GLUNIFORM3I) glUniform3i;
GLAPI GL_EXT(GLUNIFORM4I) glUniform4i;
GLAPI GL_EXT(GLUNIFORM1UI) glUniform1ui;
GLAPI GL_EXT(GLUNIFORM2UI) glUniform2ui;
GLAPI GL_EXT(GLUNIFORM3UI) glUniform3ui;
GLAPI GL_EXT(GLUNIFORM4UI) glUniform4ui;
GLAPI GL_EXT(GLUNIFORM1FV) glUniform1fv;
GLAPI GL_EXT(GLUNIFORM2FV) glUniform2fv;
GLAPI GL_EXT(GLUNIFORM3FV) glUniform3fv;
GLAPI GL_EXT(GLUNIFORM4FV) glUniform4fv;
GLAPI GL_EXT(GLUNIFORM1IV) glUniform1iv;
GLAPI GL_EXT(GLUNIFORM2IV) glUniform2iv;
GLAPI GL_EXT(GLUNIFORM3IV) glUniform3iv;
GLAPI GL_EXT(GLUNIFORM4IV) glUniform4iv;
GLAPI GL_EXT(GLUNIFORM1UIV) glUniform1uiv;
GLAPI GL_EXT(GLUNIFORM2UIV) glUniform2uiv;
GLAPI GL_EXT(GLUNIFORM3UIV) glUniform3uiv;
GLAPI GL_EXT(GLUNIFORM4UIV) glUniform4uiv;
GLAPI GL_EXT(GLUNIFORMMATRIX2FV) glUniformMatrix2fv;
GLAPI GL_EXT(GLUNIFORMMATRIX3FV) glUniformMatrix3fv;
GLAPI GL_EXT(GLUNIFORMMATRIX4FV) glUniformMatrix4fv;
GLAPI GL_EXT(GLUNIFORMMATRIX2X3FV) glUniformMatrix2x3fv;
GLAPI GL_EXT(GLUNIFORMMATRIX3X2FV) glUniformMatrix3x2fv;
GLAPI GL_EXT(GLUNIFORMMATRIX2X4FV) glUniformMatrix2x4fv;
GLAPI GL_EXT(GLUNIFORMMATRIX4X2FV) glUniformMatrix4x2fv;
GLAPI GL_EXT(GLUNIFORMMATRIX3X4FV) glUniformMatrix3x4fv;
GLAPI GL_EXT(GLUNIFORMMATRIX4X3FV) glUniformMatrix4x3fv;
GLAPI GL_EXT(GLGENBUFFERS) glGenBuffers;
GLAPI GL_EXT(GLDELETEBUFFERS) glDeleteBuffers;
GLAPI GL_EXT(GLBINDBUFFER) glBindBuffer;
GLAPI GL_EXT(GLBUFFERDATA) glBufferData;
GLAPI GL_EXT(GLBUFFERSUBDATA) glBufferSubData;
GLAPI GL_EXT(GLGETBUFFERSUBDATA) glGetBufferSubData;

/*
	VAOs
*/

GLAPI GL_EXT(GLGENVERTEXARRAYS) glGenVertexArrays;
GLAPI GL_EXT(GLDELETEVERTEXARRAYS) glDeleteVertexArrays;
GLAPI GL_EXT(GLBINDVERTEXARRAY) glBindVertexArray;
GLAPI GL_EXT(GLENABLEVERTEXATTRIBARRAY) glEnableVertexAttribArray;
GLAPI GL_EXT(GLVERTEXATTRIBPOINTER) glVertexAttribPointer;
GLAPI GL_EXT(GLGENERATEMIPMAP) glGenerateMipmap;

//#ifndef GL_VERSION_1_3
	GLAPI GL_EXT(GLACTIVETEXTURE) glActiveTexture;
//#endif


GLAPI GL_EXT(GLGENFRAMEBUFFERS) glGenFramebuffers;
GLAPI GL_EXT(GLDELETEFRAMEBUFFERS) glDeleteFramebuffers;
GLAPI GL_EXT(GLFRAMEBUFFERTEXTURE2D) glFramebufferTexture2D;
GLAPI GL_EXT(GLFRAMEBUFFERRENDERBUFFER) glFramebufferRenderbuffer;
GLAPI GL_EXT(GLBINDFRAMEBUFFER) glBindFramebuffer;
GLAPI GL_EXT(GLGETFRAMEBUFFERATTACHMENTPARAMETERIV) glGetFramebufferAttachmentParameteriv;
GLAPI GL_EXT(GLCHECKFRAMEBUFFERSTATUS) glCheckFramebufferStatus;

/*
	Render buffers
*/

GLAPI GL_EXT(GLGENRENDERBUFFERS) glGenRenderbuffers;
GLAPI GL_EXT(GLDELETERENDERBUFFERS) glDeleteRenderbuffers;
GLAPI GL_EXT(GLRENDERBUFFERSTORAGE) glRenderbufferStorage;
GLAPI GL_EXT(GLBINDRENDERBUFFER) glBindRenderbuffer;

/*
	Stencil test
*/

/*
	Transform feedback
*/

GLAPI GL_EXT(GLTRANSFORMFEEDBACKVARYINGS) glTransformFeedbackVaryings;
GLAPI GL_EXT(GLBINDBUFFERBASE) glBindBufferBase;
GLAPI GL_EXT(GLBEGINTRANSFORMFEEDBACK) glBeginTransformFeedback;
GLAPI GL_EXT(GLENDTRANSFORMFEEDBACK) glEndTransformFeedback;

/*
	Palette
*/

GLAPI GL_EXT(GLCOLORTABLE) glColorTable;
GLAPI GL_EXT(GLCOLORTABLEEXT) glColorTableEXT; 
GLAPI GL_EXT(GLPIXELSTOREX) glPixelStorex;

/*
	Blend and Transparent
*/
GLAPI GL_EXT(GLBLENDFUNCSEPARATE) glBlendFuncSeparate;
#else
void* GetAnyGLFuncAddress(const char* name);
//typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
#endif
#else
#include <GL/glext.h>
#define glColor3i glColor3ub
#define glColor4i glColor4ub

/*
	VBOs
*/

#define GL_STREAM_DRAW 0x88E0
#define GL_STREAM_READ 0x88E1
#define GL_STREAM_COPY 0x88E2
#define GL_STATIC_DRAW 0x88E4
#define GL_STATIC_READ 0x88E5
#define GL_STATIC_COPY 0x88E6
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_DYNAMIC_READ 0x88E9
#define GL_DYNAMIC_COPY 0x88EA

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

typedef void ( APIENTRYP GLGENBUFFERS ) ( GLsizei n, GLuint* buffers );
extern GLGENBUFFERS glGenBuffers;
typedef void ( APIENTRYP GLDELETEBUFFERS ) ( GLsizei n, const GLuint* buffers );
extern GLDELETEBUFFERS glDeleteBuffers;
typedef void ( APIENTRYP GLBINDBUFFER )  ( GLenum target, GLuint buffer );
extern GLBINDBUFFER glBindBuffer;
typedef void ( APIENTRYP GLBUFFERDATA ) ( GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage );
extern GLBUFFERDATA glBufferData;
typedef void ( APIENTRYP GLBUFFERSUBDATA ) ( GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data );
extern GLBUFFERSUBDATA glBufferSubData;
typedef void ( APIENTRYP GLGETBUFFERSUBDATA ) ( GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data );
extern GLGETBUFFERSUBDATA glGetBufferSubData;

#endif

#endif