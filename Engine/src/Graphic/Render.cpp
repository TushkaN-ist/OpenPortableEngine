#include <Graphic/Render.h>

#ifdef _PLATFORM_PSP
void glActiveTexture (unsigned int texture){}
#endif

/*namespace GL{
#ifdef _PLATFORM_PSP
	void Bind(GL::Palette& palette){
		palette.Active();
	}
#else
	void Bind(GL::Program& program){
		glUseProgram( program );
	}
#endif
}*/
void Bind(GL::Texture& texture){
	glBindTexture(texture.GetType(),texture);
}

void OGL::Clear( Buffer::buffer_t buffers){
	glClear(buffers);
}
void OGL::ClearColor( float R,float G,float B,float A ){
	glClearColor(R,G,B,A);
}

void OGL::DrawArrays( const GL::VertexArray& vao, Primitive::primitive_t mode, unsigned int offset, unsigned int vertices ){
	glBindVertexArray( vao );
	glDrawArrays( mode, offset, vertices );
}
void OGL::DrawElements( const GL::VertexArray& vao, Primitive::primitive_t mode, intptr_t offset, unsigned int count, unsigned int type ){
	glBindVertexArray( vao );
	glDrawElements( mode, count, type, (const GLvoid*)offset );
}
void OGL::Enable( Capability::capability_t capability )
{
	glEnable( capability );
}

void OGL::Disable( Capability::capability_t capability )
{
	glDisable( capability );
}

void OGL::BeginTransformFeedback( Primitive::primitive_t mode )
{
	glBeginTransformFeedback( mode );
}

void OGL::EndTransformFeedback()
{
	glEndTransformFeedback();
}

void OGL::DepthMask( bool writeEnabled )
{
	glDepthMask( writeEnabled ? GL_TRUE : GL_FALSE );
}

void OGL::StencilMask( bool writeEnabled )
{
	glStencilMask( writeEnabled ? ~0 : 0 );
}

void OGL::StencilMask( GLuint mask )
{
	glStencilMask( mask );
}

void OGL::StencilFunc( TestFunction::test_function_t function, int reference, GLuint mask )
{
	glStencilFunc( function, reference, mask );
}

void OGL::StencilOp( StencilAction::stencil_action_t fail, StencilAction::stencil_action_t zfail, StencilAction::stencil_action_t pass )
{
	glStencilOp( fail, zfail, pass );
}
#ifdef _PLATFORM_PSP
void OGL::Bind(GL::Palette& palette)
{
	palette.Active();
}
#else
void OGL::Bind( GL::Program& program )
{
	glUseProgram( program );
}
#endif

void OGL::Bind( GL::Texture& texture, GLubyte unit )
{
	//glActiveTexture( GL_TEXTURE0 + unit );
	glBindTexture(texture.GetType(),texture);
}


//SPECIFIC EXT
#if defined(_PLATFORM_WINDOWS)
	
void OGL::SetVerticalSync( bool enabled )
{
	wglSwapIntervalEXT( enabled ? 1 : 0 );
}
bool OGL::GetVerticalSync()
{
	return wglGetSwapIntervalEXT();
}
#elif defined(_PLATFORM_LINUX)

#elif defined(_PLATFORM_PSP)

#endif