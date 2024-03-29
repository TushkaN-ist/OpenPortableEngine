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

void Graphics::Clear( Buffer::buffer_t buffers){
	glClear(buffers);
}
void Graphics::ClearColor( float R,float G,float B,float A ){
	glClearColor(R,G,B,A);
}

void Graphics::DrawArrays( const GL::VertexArray& vao, Primitive::primitive_t mode, unsigned int offset, unsigned int vertices ){
	glBindVertexArray( vao );
	glDrawArrays( mode, offset, vertices );
}
void Graphics::DrawElements( const GL::VertexArray& vao, Primitive::primitive_t mode, intptr_t offset, unsigned int count, unsigned int type ){
	glBindVertexArray( vao );
	glDrawElements( mode, count, type, (const GLvoid*)offset );
}
void Graphics::Enable( Capability::capability_t capability )
{
	glEnable( capability );
}

void Graphics::Disable( Capability::capability_t capability )
{
	glDisable( capability );
}

void Graphics::BeginTransformFeedback( Primitive::primitive_t mode )
{
	glBeginTransformFeedback( mode );
}

void Graphics::EndTransformFeedback()
{
	glEndTransformFeedback();
}

void Graphics::DepthMask( bool writeEnabled )
{
	glDepthMask( writeEnabled ? GL_TRUE : GL_FALSE );
}

void Graphics::StencilMask( bool writeEnabled )
{
	glStencilMask( writeEnabled ? ~0 : 0 );
}

void Graphics::StencilMask( GLuint mask )
{
	glStencilMask( mask );
}

void Graphics::StencilFunc( TestFunction::test_function_t function, int reference, GLuint mask )
{
	glStencilFunc( function, reference, mask );
}

void Graphics::StencilOp( StencilAction::stencil_action_t fail, StencilAction::stencil_action_t zfail, StencilAction::stencil_action_t pass )
{
	glStencilOp( fail, zfail, pass );
}
#ifdef _PLATFORM_PSP
void Graphics::Bind(GL::Palette& palette)
{
	palette.Active();
}
#else
void Graphics::Bind( GL::Program& program )
{
	glUseProgram( program );
}
#endif

void Graphics::Bind( GL::Texture& texture, GLubyte unit )
{
	//glActiveTexture( GL_TEXTURE0 + unit );
	glBindTexture(texture.GetType(),texture);
}


//SPECIFIC EXT
#if defined(_PLATFORM_WINDOWS)
	
void Graphics::SetVerticalSync( bool enabled )
{
	wglSwapIntervalEXT( enabled ? 1 : 0 );
}
bool Graphics::GetVerticalSync()
{
	return wglGetSwapIntervalEXT();
}
#elif defined(_PLATFORM_LINUX)

#elif defined(_PLATFORM_PSP)

#endif