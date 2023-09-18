#pragma once
#include <Platform/PlatformOGL.h>
#include <GL/Extensions.h>
#include <GL/VertexArray.h>
#include <GL/Texture.h>
#include <GL/Program.h>
#include <GL/Utils/Palette.h>

class Frame;
/*namespace GL{
	class Texture;
	class Palette;
	class Program;

#ifdef _PLATFORM_PSP
	void Bind(GL::Palette& palette);
#else
	class Program;
	void Bind(GL::Program& program);
#endif
	void Bind(GL::Texture& texture);
}*/

	/*
		Buffer types
	*/
	namespace Buffer
	{
		enum buffer_t
		{
			Color = GL_COLOR_BUFFER_BIT,
			Depth = GL_DEPTH_BUFFER_BIT,
			Stencil = GL_STENCIL_BUFFER_BIT
		};

		inline buffer_t operator|( buffer_t lft, buffer_t rht )
		{
			return (buffer_t)( (int)lft | (int)rht );
		}
	}
	
	/*
		Drawing mode
	*/
	namespace Primitive
	{
		enum primitive_t
		{
			Triangles = GL_TRIANGLES,
			TrianglesStrip = GL_TRIANGLE_STRIP,
			TrianglesFan = GL_TRIANGLE_FAN,
			Quads = GL_QUADS,
			Polygon = GL_POLYGON,
			Lines = GL_LINES,
			LinesLoop = GL_LINES,
			Points = GL_POINTS,
		};
	}

	/*
		Capabilities to enable/disable
	*/
	namespace Capability
	{
		enum capability_t
		{
#ifndef _PLATFORM_PSP
			RasterizerDiscard = GL_RASTERIZER_DISCARD,
#endif
			DepthTest = GL_DEPTH_TEST,
			StencilTest = GL_STENCIL_TEST,
			CullFace = GL_CULL_FACE
		};
	}

	/*
		Stencil test functions
	*/
	namespace TestFunction
	{
		enum test_function_t
		{
			Never = GL_NEVER,
			Less = GL_LESS,
			LessEqual = GL_LEQUAL,
			Greater = GL_GREATER,
			GreaterEqual = GL_GEQUAL,
			Equal = GL_EQUAL,
			NotEqual = GL_NOTEQUAL,
			Always = GL_ALWAYS
		};
	}

	/*
		Stencil operation
	*/
	namespace StencilAction
	{
		enum stencil_action_t
		{
			Keep = GL_KEEP,
			Zero = GL_ZERO,
			Replace = GL_REPLACE,
			Increase = GL_INCR,
			IncreaseWrap = GL_INCR_WRAP,
			Decrease = GL_DECR,
			DecreaseWrap = GL_DECR_WRAP,
			Invert = GL_INVERT
		};
	}
class Graphics
{
public:
	virtual ~Graphics(){};
	static Graphics* Create(Frame* frame,unsigned char color=24,unsigned char depth=24,unsigned char stencil=8,unsigned char version=GL_VERSION_TARGET);
	static bool TestInit(unsigned char color=24,unsigned char depth=24,unsigned char stencil=8);
	virtual bool InitIn(Frame*)=0;
	virtual void MakeCurrent(Frame* frame)=0;
	virtual void ViewPort(float x,float y,float width,float height)=0;
	virtual void ViewPort(short x, short y, short width, short height)=0;
	virtual void SwapBuffers()=0;
	
	static void Clear( Buffer::buffer_t buffers = Buffer::Color | Buffer::Depth );
	static void ClearColor( float R=.15f,float G=.15f,float B=.13f,float A=1.f );
	static void DrawArrays( const GL::VertexArray& vao, Primitive::primitive_t mode, GLuint offset, GLuint vertices );
	static void DrawElements( const GL::VertexArray& vao, Primitive::primitive_t mode, intptr_t offset, GLuint count, GLuint type );
	static void Enable( Capability::capability_t capability );
	static void Disable( Capability::capability_t capability );
	static void BeginTransformFeedback( Primitive::primitive_t mode );
	static void EndTransformFeedback();
	
	static void DepthMask( bool writeEnabled );
	static void StencilMask( bool writeEnabled );
	static void StencilMask( GLuint mask );
	static void StencilFunc( TestFunction::test_function_t function, int reference, GLuint mask );
	static void StencilOp( StencilAction::stencil_action_t fail, StencilAction::stencil_action_t zfail, StencilAction::stencil_action_t pass );
	static void SetVerticalSync( bool enabled );
	static bool GetVerticalSync();

#ifdef _PLATFORM_PSP
	static void Bind( GL::Palette& palette );
#else
	static void Bind( GL::Program& program );
#endif
	static void Bind( GL::Texture& texture, GLubyte unit );

private:
	
};