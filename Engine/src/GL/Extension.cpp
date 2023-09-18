#include <Platform/PlatformDefined.h>
#ifndef _PLATFORM_PSP
#include <stdio.h>
#include <GL/Extensions.h>

#ifndef GL_GLEXT_PROTOTYPES

GL_EXT(GLCOMPILESHADER) glCompileShader;
GL_EXT(GLCREATESHADER) glCreateShader;
GL_EXT(GLDELETESHADER) glDeleteShader;
GL_EXT(GLGETSHADERIV) glGetShaderiv;
GL_EXT(GLGETSHADERINFOLOG) glGetShaderInfoLog;
GL_EXT(GLSHADERSOURCE) glShaderSource;

GL_EXT(GLCREATEPROGRAM) glCreateProgram;
GL_EXT(GLDELETEPROGRAM) glDeleteProgram;
GL_EXT(GLUSEPROGRAM) glUseProgram;
GL_EXT(GLATTACHSHADER) glAttachShader;
GL_EXT(GLLINKPROGRAM) glLinkProgram;
GL_EXT(GLGETPROGRAMIV) glGetProgramiv;
GL_EXT(GLGETPROGRAMINFOLOG) glGetProgramInfoLog;
GL_EXT(GLGETATTRIBLOCATION) glGetAttribLocation;
GL_EXT(GLGETUNIFORMLOCATION) glGetUniformLocation;

GL_EXT(GLUNIFORM1F) glUniform1f;
GL_EXT(GLUNIFORM2F) glUniform2f;
GL_EXT(GLUNIFORM3F) glUniform3f;
GL_EXT(GLUNIFORM4F) glUniform4f;
GL_EXT(GLUNIFORM1I) glUniform1i;
GL_EXT(GLUNIFORM2I) glUniform2i;
GL_EXT(GLUNIFORM3I) glUniform3i;
GL_EXT(GLUNIFORM4I) glUniform4i;
GL_EXT(GLUNIFORM1UI) glUniform1ui;
GL_EXT(GLUNIFORM2UI) glUniform2ui;
GL_EXT(GLUNIFORM3UI) glUniform3ui;
GL_EXT(GLUNIFORM4UI) glUniform4ui;
GL_EXT(GLUNIFORM1FV) glUniform1fv;
GL_EXT(GLUNIFORM2FV) glUniform2fv;
GL_EXT(GLUNIFORM3FV) glUniform3fv;
GL_EXT(GLUNIFORM4FV) glUniform4fv;
GL_EXT(GLUNIFORM1IV) glUniform1iv;
GL_EXT(GLUNIFORM2IV) glUniform2iv;
GL_EXT(GLUNIFORM3IV) glUniform3iv;
GL_EXT(GLUNIFORM4IV) glUniform4iv;
GL_EXT(GLUNIFORM1UIV) glUniform1uiv;
GL_EXT(GLUNIFORM2UIV) glUniform2uiv;
GL_EXT(GLUNIFORM3UIV) glUniform3uiv;
GL_EXT(GLUNIFORM4UIV) glUniform4uiv;
GL_EXT(GLUNIFORMMATRIX2FV) glUniformMatrix2fv;
GL_EXT(GLUNIFORMMATRIX3FV) glUniformMatrix3fv;
GL_EXT(GLUNIFORMMATRIX4FV) glUniformMatrix4fv;
GL_EXT(GLUNIFORMMATRIX2X3FV) glUniformMatrix2x3fv;
GL_EXT(GLUNIFORMMATRIX3X2FV) glUniformMatrix3x2fv;
GL_EXT(GLUNIFORMMATRIX2X4FV) glUniformMatrix2x4fv;
GL_EXT(GLUNIFORMMATRIX4X2FV) glUniformMatrix4x2fv;
GL_EXT(GLUNIFORMMATRIX3X4FV) glUniformMatrix3x4fv;
GL_EXT(GLUNIFORMMATRIX4X3FV) glUniformMatrix4x3fv;

GL_EXT(GLGENBUFFERS) glGenBuffers;
GL_EXT(GLDELETEBUFFERS) glDeleteBuffers;
GL_EXT(GLBINDBUFFER) glBindBuffer;
GL_EXT(GLBUFFERDATA) glBufferData;
GL_EXT(GLBUFFERSUBDATA) glBufferSubData;
GL_EXT(GLGETBUFFERSUBDATA) glGetBufferSubData;

GL_EXT(GLGENVERTEXARRAYS) glGenVertexArrays;
GL_EXT(GLDELETEVERTEXARRAYS) glDeleteVertexArrays;
GL_EXT(GLBINDVERTEXARRAY) glBindVertexArray;

GL_EXT(GLENABLEVERTEXATTRIBARRAY) glEnableVertexAttribArray;
GL_EXT(GLVERTEXATTRIBPOINTER) glVertexAttribPointer;

GL_EXT(GLGENERATEMIPMAP) glGenerateMipmap;

//#ifndef GL_VERSION_1_3
	GL_EXT(GLACTIVETEXTURE) glActiveTexture;
//#endif

GL_EXT(GLGENFRAMEBUFFERS) glGenFramebuffers;
GL_EXT(GLDELETEFRAMEBUFFERS) glDeleteFramebuffers;
GL_EXT(GLFRAMEBUFFERTEXTURE2D) glFramebufferTexture2D;
GL_EXT(GLFRAMEBUFFERRENDERBUFFER) glFramebufferRenderbuffer;
GL_EXT(GLBINDFRAMEBUFFER) glBindFramebuffer;
GL_EXT(GLGETFRAMEBUFFERATTACHMENTPARAMETERIV) glGetFramebufferAttachmentParameteriv;
GL_EXT(GLCHECKFRAMEBUFFERSTATUS) glCheckFramebufferStatus;

GL_EXT(GLGENRENDERBUFFERS) glGenRenderbuffers;
GL_EXT(GLDELETERENDERBUFFERS) glDeleteRenderbuffers;
GL_EXT(GLRENDERBUFFERSTORAGE) glRenderbufferStorage;
GL_EXT(GLBINDRENDERBUFFER) glBindRenderbuffer;

GL_EXT(GLTRANSFORMFEEDBACKVARYINGS) glTransformFeedbackVaryings;
GL_EXT(GLBINDBUFFERBASE) glBindBufferBase;
GL_EXT(GLBEGINTRANSFORMFEEDBACK) glBeginTransformFeedback;
GL_EXT(GLENDTRANSFORMFEEDBACK) glEndTransformFeedback;

GL_EXT(GLCOLORTABLE) glColorTable;
GL_EXT(GLCOLORTABLEEXT) glColorTableEXT; 
GL_EXT(GLPIXELSTOREX) glPixelStorex;

GL_EXT(GLBLENDFUNCSEPARATE) glBlendFuncSeparate;

#else

PFNGLCOMPILESHADERPROC glCompileShader = NULL;

void *GetAnyGLFuncAddress(const char *name)
{
	void *p = (void *)wglGetProcAddress(name);
	if(p == 0 ||
		(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
		(p == (void*)-1) )
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}
	return p;
}

#endif

namespace GL
{
	bool extensionsLoaded = false;

	void* LoadExtension( const char* name )
	{
#if defined( _PLATFORM_WINDOWS )
		return (void*)wglGetProcAddress( name );
#elif defined( _PLATFORM_LINUX )
		return (void*)glXGetProcAddress( (const GLubyte*)name );
#endif
	}

#if defined(_PLATFORM_WINDOWS)
	bool WGLExtensionSupported(const char *extension_name) {
		PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;
		_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) LoadExtension("wglGetExtensionsStringEXT");
		if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL) {
			return false;
		}
		return true;
	}
#endif

	void LoadExtensions()
	{
		if ( extensionsLoaded ) return;
			extensionsLoaded = true;

#if defined(_PLATFORM_WINDOWS)
#ifndef WGL_WGLEXT_PROTOTYPES
		LoadExt(wglCreateContextAttribsARB);
		LoadExt(wglChoosePixelFormatARB);
		if (WGLExtensionSupported("WGL_EXT_swap_control"))
		{
			LoadExt(wglSwapIntervalEXT);
			LoadExt(wglGetSwapIntervalEXT);
		}
#endif
#endif
#ifndef GL_GLEXT_PROTOTYPES
		LoadExt(glCompileShader);
		LoadExt(glCreateShader);
		LoadExt(glDeleteShader);
		LoadExt(glGetShaderiv);
		LoadExt(glGetShaderInfoLog);
		LoadExt(glShaderSource);

		LoadExt(glCreateProgram);
		LoadExt(glDeleteProgram);
		LoadExt(glUseProgram);
		LoadExt(glAttachShader);
		LoadExt(glLinkProgram);
		LoadExt(glGetProgramiv);
		LoadExt(glGetProgramInfoLog);
		LoadExt(glGetAttribLocation);
		LoadExt(glGetUniformLocation);

		LoadExt(glUniform1f);
		LoadExt(glUniform2f);
		LoadExt(glUniform3f);
		LoadExt(glUniform4f);
		LoadExt(glUniform1i);
		LoadExt(glUniform2i);
		LoadExt(glUniform3i);
		LoadExt(glUniform4i);
		LoadExt(glUniform1ui);
		LoadExt(glUniform2ui);
		LoadExt(glUniform3ui);
		LoadExt(glUniform4ui);
		LoadExt(glUniform1fv);
		LoadExt(glUniform2fv);
		LoadExt(glUniform3fv);
		LoadExt(glUniform4fv);
		LoadExt(glUniform1iv);
		LoadExt(glUniform2iv);
		LoadExt(glUniform3iv);
		LoadExt(glUniform4iv);
		LoadExt(glUniform1uiv);
		LoadExt(glUniform2uiv);
		LoadExt(glUniform3uiv);
		LoadExt(glUniform4uiv);
		LoadExt(glUniformMatrix2fv);
		LoadExt(glUniformMatrix3fv);
		LoadExt(glUniformMatrix4fv);
		LoadExt(glUniformMatrix2x3fv);
		LoadExt(glUniformMatrix3x2fv);
		LoadExt(glUniformMatrix2x4fv);
		LoadExt(glUniformMatrix4x2fv);
		LoadExt(glUniformMatrix3x4fv);
		LoadExt(glUniformMatrix4x3fv);

		LoadExt(glGenBuffers);
		LoadExt(glDeleteBuffers);
		LoadExt(glBindBuffer);
		LoadExt(glBufferData);
		LoadExt(glBufferSubData);
		LoadExt(glGetBufferSubData);

		LoadExt(glGenVertexArrays);
		LoadExt(glDeleteVertexArrays);
		LoadExt(glBindVertexArray);

		LoadExt(glEnableVertexAttribArray);
		LoadExt(glVertexAttribPointer);

		LoadExt(glGenerateMipmap);

		//#ifndef GL_VERSION_1_3
			LoadExt(glActiveTexture);
		//#endif

		LoadExt(glGenFramebuffers);
		LoadExt(glDeleteFramebuffers);
		LoadExt(glFramebufferTexture2D);
		LoadExt(glFramebufferRenderbuffer);
		LoadExt(glBindFramebuffer);
		LoadExt(glGetFramebufferAttachmentParameteriv);
		LoadExt(glCheckFramebufferStatus);

		LoadExt(glGenRenderbuffers);
		LoadExt(glDeleteRenderbuffers);
		LoadExt(glRenderbufferStorage);
		LoadExt(glBindRenderbuffer);

		LoadExt(glTransformFeedbackVaryings);
		LoadExt(glBindBufferBase);
		LoadExt(glBeginTransformFeedback);
		LoadExt(glEndTransformFeedback);
		
		LoadExt(glColorTable);
		
		LoadExt(glColorTableEXT);
		
		LoadExt(glPixelStorex);
		LoadExt(glBlendFuncSeparate);
#else
glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
//glCompileShader = (PFNGLCOMPILESHADERPROC)LoadExtension("glCompileShader");

#endif
	}
	//#undef LoadExt
}
#endif