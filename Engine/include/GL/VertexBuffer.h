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

#ifndef OOGL_VERTEXBUFFER_HPP
#define OOGL_VERTEXBUFFER_HPP

#include <Platform/PlatformDefined.h>
#include "GC.h"
#include "Extensions.h"
//#include <Application/GL/Util/Mesh.hpp>
#include <Math/Vec2.h>
#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <Math/Mat3.h>
#include <Math/Mat4.h>
#include <vector>
//#include <functional>
#include <stdint.h>

namespace GL
{
	/*
		Buffer usage types
	*/
	namespace BufferUsage
	{
		enum buffer_usage_t
		{
			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};
	}

	/*
		Helper class for building vertex data
	*/
	class VertexDataBuffer
	{
	public:
		void Float( float v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Int8( int8_t v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Int16( int16_t v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Int32( int32_t v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Uint8( uint8_t v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Uint16( uint16_t v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Uint32( uint32_t v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		
		void Vec2( const GL::Vec2& v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Vec3( const GL::Vec3& v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Vec4( const GL::Vec4& v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }

		void Matrix3x3( const GL::Mat3& v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		void Matrix4x4( const GL::Mat4& v ) { Bytes( (GLubyte*)&v, sizeof( v ) ); }
		
		void* Pointer() { return &data[0]; }
		void* Pointer(GLuint offset) { return &data[0]+offset; }
		int Size() { return data.size(); }

	private:
		std::vector<GLubyte> data;

		void Bytes( GLubyte* bytes, GLuint count ) {
			for ( GLuint i = 0; i < count; i++ )
				data.push_back( bytes[i] );
		}
	};

	/*
		Vertex Buffer
	*/
	class VertexBuffer
	{
	public:
		VertexBuffer( GLuint type = GL_ARRAY_BUFFER );
		VertexBuffer( const VertexBuffer& other, GLuint type = GL_ARRAY_BUFFER );
		VertexBuffer( const void* data, size_t length, BufferUsage::buffer_usage_t usage, GLuint type = GL_ARRAY_BUFFER );
#ifdef PFW32
		VertexBuffer( const Mesh& mesh, BufferUsage::buffer_usage_t usage, std::function<void ( const Vertex& v, VertexDataBuffer& data )> f, GLuint type = GL_ARRAY_BUFFER );
#endif

		~VertexBuffer();

		operator GLuint() const;
		const VertexBuffer& operator=( const VertexBuffer& other );

		void Data( const void* data, size_t length, BufferUsage::buffer_usage_t usage );
		void SubData( const void* data, size_t offset, size_t length );

		void GetSubData( void* data, size_t offset, size_t length );

	private:
		static GC gc;
		GLuint obj;
		GLuint type;
	};
}

#endif