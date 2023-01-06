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

#pragma once

#include "Texture.h"
#include "Utils/Color.h"
//#include "Util/Image.hpp"

namespace GL
{
	/*
		Texture
	*/
	
	class Texture2D : public Texture
	{
	public:
		Texture2D();
		Texture2D( const Texture2D& other );
		Texture2D( const GLvoid* data, GLushort width, GLushort height, InternalFormat::internal_format_t internalFormat=InternalFormat::RGBA, Format::format_t format=Format::RGBA, DataType::data_type_t type=DataType::UnsignedByte );

		~Texture2D();

		operator GLuint() const;
		const Texture2D& operator=( const Texture2D& other );
		
		void Image2D( const GLvoid* data, GLushort width, GLushort height, InternalFormat::internal_format_t internalFormat=InternalFormat::RGBA, Format::format_t format=Format::RGBA, DataType::data_type_t type=DataType::UnsignedByte );
		
		void SetWrapping( Wrapping::wrapping_t s );
		void SetWrapping( Wrapping::wrapping_t s, Wrapping::wrapping_t t );
		void SetWrapping( Wrapping::wrapping_t s, Wrapping::wrapping_t t, Wrapping::wrapping_t r );

		void SetFilters( Filter::filter_t min, Filter::filter_t mag );
		void SetBorderColor( const Color& color );
		void SetBorderColor( const Color32& color );
		
		void GenerateMipmaps();
		GLushort Width() const;
		GLushort Height() const;
	private:
		GLushort width,height;
		GLuint obj;
	};
}
