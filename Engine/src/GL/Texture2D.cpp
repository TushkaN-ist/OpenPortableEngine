/*
	Copyright (C) 2012 Alexander Overvoorde

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <GL/Texture2D.h>

#define PUSHSTATE() GLint restoreId; glGetIntegerv( GL_TEXTURE_BINDING_2D, &restoreId );
#define POPSTATE() glBindTexture( GL_TEXTURE_2D, restoreId );

namespace GL
{
	Texture2D::Texture2D():Texture(GL_TEXTURE_2D)
	{
		gc.Create( obj, glGenTextures, glDeleteTextures );
	}

	Texture2D::Texture2D( const Texture2D& other )
	{
		gc.Copy( other.obj, obj );
	}
	
	Texture2D::Texture2D( const GLvoid* data, GLushort width, GLushort height, InternalFormat::internal_format_t internalFormat, Format::format_t format, DataType::data_type_t type ):Texture(GL_TEXTURE_2D){
		PUSHSTATE()
		
		gc.Create( obj, glGenTextures, glDeleteTextures );
		
		this->width=width;
		this->height=height;
		
		glBindTexture( textureD, obj );
		glTexImage2D( textureD, 0, internalFormat, width, height, 0, format, type, data );
		
		Filter::filter_t filter=Filter::Nearest;
		
		glTexParameteri(textureD, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(textureD, GL_TEXTURE_MIN_FILTER, filter);
#if !defined(_PLATFORM_PSP)
		//glGenerateMipmap( textureD );
#endif
		POPSTATE()
	}

	Texture2D::~Texture2D()
	{
		gc.Destroy( obj );
	}

	Texture2D::operator GLuint() const
	{
		return obj;
	}

	const Texture2D& Texture2D::operator=( const Texture2D& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}

	void Texture2D::Image2D( const GLvoid* data, GLushort width, GLushort height, InternalFormat::internal_format_t internalFormat, Format::format_t format, DataType::data_type_t type )
	{
		PUSHSTATE()
		this->width=width;
		this->height=height;
		glBindTexture( textureD, obj );
		glTexImage2D( textureD, 0, internalFormat, width, height, 0, format, type, data );

		POPSTATE()
	}

	void Texture2D::SetWrapping( Wrapping::wrapping_t s )
	{
		PUSHSTATE()

		glBindTexture( textureD, obj );
		glTexParameteri( textureD, GL_TEXTURE_WRAP_S, s );

		//glBindTexture( textureD, restoreId );

		POPSTATE()
	}

	void Texture2D::SetWrapping( Wrapping::wrapping_t s, Wrapping::wrapping_t t )
	{
		PUSHSTATE()

		glBindTexture( textureD, obj );
		glTexParameteri( textureD, GL_TEXTURE_WRAP_S, s );
		glTexParameteri( textureD, GL_TEXTURE_WRAP_T, t );

		//glBindTexture( textureD, restoreId );

		POPSTATE()
	}

	void Texture2D::SetWrapping( Wrapping::wrapping_t s, Wrapping::wrapping_t t, Wrapping::wrapping_t r )
	{
		PUSHSTATE()

		glBindTexture( textureD, obj );
		glTexParameteri( textureD, GL_TEXTURE_WRAP_S, s );
		glTexParameteri( textureD, GL_TEXTURE_WRAP_T, t );
		glTexParameteri( textureD, GL_TEXTURE_WRAP_R, r );

		POPSTATE()
	}

	void Texture2D::SetFilters( Filter::filter_t min, Filter::filter_t mag )
	{
		PUSHSTATE()

		glBindTexture( textureD, obj );
		glTexParameteri( textureD, GL_TEXTURE_MIN_FILTER, min );
		glTexParameteri( textureD, GL_TEXTURE_MAG_FILTER, mag );

		POPSTATE()
	}

	void Texture2D::SetBorderColor( const Color& color )
	{
		PUSHSTATE()

		glBindTexture( textureD, obj );
		float col[4] = { color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f };
		glTexParameterfv( textureD, GL_TEXTURE_BORDER_COLOR, col );

		POPSTATE()
	}
	void Texture2D::SetBorderColor( const Color32& color )
	{
		PUSHSTATE()

		glBindTexture( textureD, obj );
		float col[4] = { color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f };
		glTexParameterfv( textureD, GL_TEXTURE_BORDER_COLOR, col );

		POPSTATE()
	}
	
	void Texture2D::GenerateMipmaps()
	{
		PUSHSTATE()

		glBindTexture( textureD, obj );
#if !defined(_PLATFORM_PSP)
		glGenerateMipmap( textureD );
#endif

		POPSTATE()
	}
	
	GLushort Texture2D::Width() const{
		return width; 
	}
	GLushort Texture2D::Height() const{
		return height;
	}
}